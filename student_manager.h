#ifndef STUDENT_MANAGER_H
#define STUDENT_MANAGER_H

// ����ѧ���ṹ��
typedef struct Student {
    int id;
    char name[50];
    int age;
    float score;
    struct Student* next;
} Student;

// ���ļ�����ѧ������
void load_from_file(Student** head, const char* filename);

// ����ѧ�����ݵ��ļ�
void save_to_file(Student* head, const char* filename);

// ���ѧ��������
void add_student(Student** head, int id, char* name, int age, float score);

// ɾ��ѧ���ڵ�
void delete_student(Student** head, int id);

// ����ѧ���ڵ�
Student* find_student(Student* head, int id);

// ��ʾ����ѧ����Ϣ
void display_all_students(Student* head);

// �ͷ������ڴ�
void free_list(Student* head);

#endif