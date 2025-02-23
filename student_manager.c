#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student_manager.h"

// 内部函数：创建新学生节点
static Student* create_student(int id, char* name, int age, float score) {
    Student* new_student = (Student*)malloc(sizeof(Student));
    if (new_student == NULL) {
        printf("内存分配失败\n");
        exit(1);
    }
    new_student->id = id;
    strcpy(new_student->name, name);
    new_student->age = age;
    new_student->score = score;
    new_student->next = NULL;
    return new_student;
}

// 添加学生到链表
void add_student(Student** head, int id, char* name, int age, float score) {
    Student* new_student = create_student(id, name, age, score);
    if (*head == NULL) {
        *head = new_student;
    } else {
        Student* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = new_student;
    }
}

// 删除学生节点
void delete_student(Student** head, int id) {
    if (*head == NULL) {
        printf("链表为空，无法删除\n");
        return;
    }
    Student* temp = *head;
    Student* prev = NULL;

    // 检查头节点是否为要删除的节点
    if (temp->id == id) {
        *head = temp->next;
        free(temp);
        printf("学生学号 %d 已删除\n", id);
        return;
    }

    // 遍历链表查找目标节点
    while (temp != NULL && temp->id != id) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("未找到学号为 %d 的学生\n", id);
        return;
    }

    prev->next = temp->next;
    free(temp);
    printf("学生学号 %d 已删除\n", id);
}

// 查找学生节点
Student* find_student(Student* head, int id) {
    Student* temp = head;
    while (temp != NULL) {
        if (temp->id == id) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

// 显示所有学生信息
void display_all_students(Student* head) {
    if (head == NULL) {
        printf("链表为空\n");
        return;
    }
    Student* temp = head;
    printf("学号\t姓名\t年龄\t成绩\n");
    while (temp != NULL) {
        printf("%d\t%s\t%d\t%.2f\n", temp->id, temp->name, temp->age, temp->score);
        temp = temp->next;
    }
}

// 保存学生数据到文件（CSV格式）
void save_to_file(Student* head, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("无法打开文件 %s\n", filename);
        return;
    }
    Student* temp = head;
    fprintf(file, "学号,姓名,年龄,成绩\n");
    while (temp != NULL) {
        fprintf(file, "%d,%s,%d,%.2f\n", temp->id, temp->name, temp->age, temp->score);
        temp = temp->next;
    }
    fclose(file);
    printf("数据已保存到文件 %s\n", filename);
}

// 从文件加载学生数据
void load_from_file(Student** head, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("无法打开文件 %s\n", filename);
        return;
    }

    // 跳过标题行
    char buffer[256];
    fgets(buffer, sizeof(buffer), file);

    int id, age;
    char name[50];
    float score;

    while (fscanf(file, "%d,%[^,],%d,%f", &id, name, &age, &score) == 4) {
        add_student(head, id, name, age, score);
    }
    fclose(file);
    printf("数据已从文件 %s 加载\n", filename);
}

// 释放链表内存
void free_list(Student* head) {
    Student* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}