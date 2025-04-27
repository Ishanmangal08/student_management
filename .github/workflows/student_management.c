#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
    int roll;
    char name[50];
    float marks;
};

// Function declarations
void addStudent();
void viewStudents();
void searchStudent();
void updateStudent();
void deleteStudent();

int main() {
    int choice;

    while (1) {
        printf("\n=== Student Record Management System ===\n");
        printf("1. Add Record\n");
        printf("2. View All Records\n");
        printf("3. Search Record\n");
        printf("4. Update Record\n");
        printf("5. Delete Record\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                viewStudents();
                break;
            case 3:
                searchStudent();
                break;
            case 4:
                updateStudent();
                break;
            case 5:
                deleteStudent();
                break;
            case 6:
                printf("Exiting the program. Thank you!\n");
                exit(0);
            default:
                printf("Invalid Choice! Please try again.\n");
        }
    }
    return 0;
}

// Function to add a student record
void addStudent() {
    struct Student s;
    FILE *fp;

    fp = fopen("student.dat", "ab"); // Append binary
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    printf("Enter roll number: ");
    scanf("%d", &s.roll);

    getchar(); // Clear input buffer

    printf("Enter name: ");
    fgets(s.name, sizeof(s.name), stdin);
    s.name[strcspn(s.name, "\n")] = 0; // Remove newline

    printf("Enter marks: ");
    scanf("%f", &s.marks);

    fwrite(&s, sizeof(s), 1, fp);
    fclose(fp);

    printf("Record added successfully!\n");
}

// Function to view all student records
void viewStudents() {
    struct Student s;
    FILE *fp;

    fp = fopen("student.dat", "rb");
    if (fp == NULL) {
        printf("No records found.\n");
        return;
    }

    printf("\n=== List of Students ===\n");
    while (fread(&s, sizeof(s), 1, fp)) {
        printf("Roll No: %d | Name: %s | Marks: %.2f\n", s.roll, s.name, s.marks);
    }

    fclose(fp);
}

// Function to search for a student by roll number
void searchStudent() {
    struct Student s;
    FILE *fp;
    int roll, found = 0;

    printf("Enter roll number to search: ");
    scanf("%d", &roll);

    fp = fopen("student.dat", "rb");
    if (fp == NULL) {
        printf("No records found.\n");
        return;
    }

    while (fread(&s, sizeof(s), 1, fp)) {
        if (s.roll == roll) {
            printf("Record Found!\n");
            printf("Roll No: %d | Name: %s | Marks: %.2f\n", s.roll, s.name, s.marks);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Record not found.\n");
    }

    fclose(fp);
}

// Function to update a student's record
void updateStudent() {
    struct Student s;
    FILE *fp, *temp;
    int roll, found = 0;

    printf("Enter roll number to update: ");
    scanf("%d", &roll);

    fp = fopen("student.dat", "rb");
    temp = fopen("temp.dat", "wb");

    if (fp == NULL || temp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    while (fread(&s, sizeof(s), 1, fp)) {
        if (s.roll == roll) {
            printf("Enter new name: ");
            getchar(); // Clear buffer
            fgets(s.name, sizeof(s.name), stdin);
            s.name[strcspn(s.name, "\n")] = 0;

            printf("Enter new marks: ");
            scanf("%f", &s.marks);
            found = 1;
        }
        fwrite(&s, sizeof(s), 1, temp);
    }

    fclose(fp);
    fclose(temp);

    remove("student.dat");
    rename("temp.dat", "student.dat");

    if (found)
        printf("Record updated successfully!\n");
    else
        printf("Record not found.\n");
}

// Function to delete a student's record
void deleteStudent() {
    struct Student s;
    FILE *fp, *temp;
    int roll, found = 0;

    printf("Enter roll number to delete: ");
    scanf("%d", &roll);

    fp = fopen("student.dat", "rb");
    temp = fopen("temp.dat", "wb");

    if (fp == NULL || temp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    while (fread(&s, sizeof(s), 1, fp)) {
        if (s.roll != roll) {
            fwrite(&s, sizeof(s), 1, temp);
        } else {
            found = 1;
        }
    }

    fclose(fp);
    fclose(temp);

    remove("student.dat");
    rename("temp.dat", "student.dat");

    if (found)
        printf("Record deleted successfully!\n");
    else
        printf("Record not found.\n");
}
