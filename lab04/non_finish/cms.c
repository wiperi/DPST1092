// A simple program to manage student marks.
#include <stdio.h>

// Constants
#define CLASS_SIZE 6
#define UNKNOWN_MARK -1

struct student {
    int id;
    int mark;
};

struct student students[CLASS_SIZE] = {
    {5123456, UNKNOWN_MARK},
    {5308310, UNKNOWN_MARK},
    {5417087, UNKNOWN_MARK},
    {3456789, UNKNOWN_MARK},
    {5345678, UNKNOWN_MARK},
    {5234567, UNKNOWN_MARK},
};

struct student *find_student_by_id(int id) {
    for (int i = 0; i < CLASS_SIZE; i++) {
        if (students[i].id == id) {
            return &students[i];
        }
    }
    return NULL;
}

void update_student_mark(void) {
    int id;
    printf("Please enter the student ID: ");
    scanf("%d", &id);

    struct student *student = find_student_by_id(id);
    if (student == NULL) {
        printf("Student not found in class!\n");
        return;
    }

    printf("Please enter the student mark: ");
    scanf("%d", &student->mark);
}

void print_report(void) {
    printf("ID\tMark\n");
    for (int i = 0; i < CLASS_SIZE; i++) {
        printf("%d\t", students[i].id);

        if (students[i].mark == UNKNOWN_MARK) {
            printf("?\n");
        } else {
            printf("%d\n", students[i].mark);
        }
    }
}

// Options for selection
#define OPTION_UPDATE_MARK 1
#define OPTION_PRINT_REPORT 2
#define OPTION_EXIT 3

int main(void) {
    printf("=== Welcome to the Class Management System ===\n");
    while (1) {
        printf("Options:\n");
        printf("%d. Update student mark\n", OPTION_UPDATE_MARK);
        printf("%d. Print class report\n", OPTION_PRINT_REPORT);
        printf("%d. Exit\n", OPTION_EXIT);
        printf("Please select an option [1-3]: ");

        int option;
        scanf("%d", &option);

        if (option == OPTION_UPDATE_MARK) {
            update_student_mark();
        } else if (option == OPTION_PRINT_REPORT) {
            print_report();
        } else if (option == OPTION_EXIT) {
            break;
        } else {
            printf("Invalid option!\n");
        }
    }

    printf("=== Exiting cms. Goodbye! ===\n");

    return 0;
}
