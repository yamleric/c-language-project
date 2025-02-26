#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student_manager.h"

// �ڲ�������������ѧ���ڵ�
static Student* create_student(int id, char* name, int age, float score) {
    Student* new_student = (Student*)malloc(sizeof(Student));
    if (new_student == NULL) {
        printf("�ڴ����ʧ��\n");
        exit(1);
    }
    new_student->id = id;
    strcpy_s(new_student->name, sizeof(new_student->name), name);
    new_student->age = age;
    new_student->score = score;
    new_student->next = NULL;
    return new_student;
}

// ���ѧ��������
void add_student(Student** head, int id, char* name, int age, float score) {
    Student* new_student = create_student(id, name, age, score);
    if (*head == NULL) {
        *head = new_student;
    }
    else {
        Student* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = new_student;
    }
}

// ɾ��ѧ���ڵ�
void delete_student(Student** head, int id) {
    if (*head == NULL) {
        printf("����Ϊ�գ��޷�ɾ��\n");
        return;
    }
    Student* temp = *head;
    Student* prev = NULL;

    // ���ͷ�ڵ��Ƿ�ΪҪɾ���Ľڵ�
    if (temp->id == id) {
        *head = temp->next;
        free(temp);
        printf("ѧ��ѧ�� %d ��ɾ��\n", id);
        return;
    }

    // �����������Ŀ��ڵ�
    while (temp != NULL && temp->id != id) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("δ�ҵ�ѧ��Ϊ %d ��ѧ��\n", id);
        return;
    }

    prev->next = temp->next;
    free(temp);
    printf("ѧ��ѧ�� %d ��ɾ��\n", id);
}

// ����ѧ���ڵ�
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

// ��ʾ����ѧ����Ϣ
void display_all_students(Student* head) {
    if (head == NULL) {
        printf("����Ϊ��\n");
        return;
    }
    Student* temp = head;
    printf("ѧ��\t����\t����\t�ɼ�\n");
    while (temp != NULL) {
        printf("%d\t%s\t%d\t%.2f\n", temp->id, temp->name, temp->age, temp->score);
        temp = temp->next;
    }
}

// ����ѧ�����ݵ��ļ���CSV��ʽ��
void save_to_file(Student* head, const char* filename) {
    FILE* file;
    if (fopen_s(&file, filename, "w") != 0) {
        printf("�޷����ļ� %s\n", filename);
        return;
    }
    Student* temp = head;
    fprintf(file, "ѧ��,����,����,�ɼ�\n");
    while (temp != NULL) {
        fprintf(file, "%d,%s,%d,%.2f\n", temp->id, temp->name, temp->age, temp->score);
        temp = temp->next;
    }
    fclose(file);
    printf("�����ѱ��浽�ļ� %s\n", filename);
}

// ���ļ�����ѧ������
void load_from_file(Student** head, const char* filename) {
    FILE* file;
    if (fopen_s(&file, filename, "r") != 0) {
        printf("�޷����ļ� %s\n", filename);
        return;
    }

    // ����������
    char buffer[256];
    fgets(buffer, sizeof(buffer), file);

    int id, age;
    char name[50];
    float score;

    while (fscanf_s(file, "%d,%49[^,],%d,%f", &id, name, (unsigned)_countof(name), &age, &score) == 4) {
        add_student(head, id, name, age, score);
    }
    fclose(file);
    printf("�����Ѵ��ļ� %s ����\n", filename);
}

// �ͷ������ڴ�
void free_list(Student* head) {
    Student* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}