#include <stdio.h>
#include <stdlib.h>
#include "student_manager.h"

int main() {
    Student* head = NULL;
    int choice, id, age;
    char name[50];
    float score;
    const char* filename = "students.csv";

    // 加载已有数据
    load_from_file(&head, filename);

    while (1) {
        printf("\n学生信息管理系统\n");
        printf("1. 添加学生\n");
        printf("2. 删除学生\n");
        printf("3. 查找学生\n");
        printf("4. 显示所有学生\n");
        printf("5. 保存到文件\n");
        printf("6. 退出\n");
        printf("请选择操作: ");
        scanf_s("%d", &choice);

        switch (choice) {
        case 1: {
            printf("输入学号: ");
            scanf_s("%d", &id);
            printf("输入姓名: ");
            scanf_s("%s", name, (unsigned)_countof(name));
            printf("输入年龄: ");
            scanf_s("%d", &age);
            printf("输入成绩: ");
            scanf_s("%f", &score);
            add_student(&head, id, name, age, score);
            break;
        }
        case 2: {
            printf("输入要删除的学生学号: ");
            scanf_s("%d", &id);
            delete_student(&head, id);
            break;
        }
        case 3: {
            printf("输入要查找的学生学号: ");
            scanf_s("%d", &id);
            Student* found = find_student(head, id);
            if (found) {
                printf("找到学生: 学号=%d, 姓名=%s, 年龄=%d, 成绩=%.2f\n",
                    found->id, found->name, found->age, found->score);
            }
            else {
                printf("未找到学号为 %d 的学生\n", id);
            }
            break;
        }
        case 4: {
            display_all_students(head);
            break;
        }
        case 5: {
            save_to_file(head, filename);
            break;
        }
        case 6: {
            save_to_file(head, filename); // 自动保存数据
            free_list(head);
            printf("退出系统。\n");
            exit(0);
        }
        default: {
            printf("无效选择，请重试。\n");
            break;
        }
        }
    }

    return 0;
}