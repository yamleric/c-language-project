#ifndef STUDENT_MANAGER_H
#define STUDENT_MANAGER_H

// 定义学生结构体
typedef struct Student {
    int id;
    char name[50];
    int age;
    float score;
    struct Student* next;
} Student;

// 从文件加载学生数据
void load_from_file(Student** head, const char* filename);

// 保存学生数据到文件
void save_to_file(Student* head, const char* filename);

// 添加学生到链表
void add_student(Student** head, int id, char* name, int age, float score);

// 删除学生节点
void delete_student(Student** head, int id);

// 查找学生节点
Student* find_student(Student* head, int id);

// 显示所有学生信息
void display_all_students(Student* head);

// 释放链表内存
void free_list(Student* head);

#endif