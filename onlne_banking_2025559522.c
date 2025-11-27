#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "students.dat"

typedef struct {
    char name[50];
    int id;
    float grades[5];
    float average;
} Student;

 // this part is known as function declarations
void addStudent();
void displayStudents();
void searchStudent();
void deleteStudent();
void updateStudent();
void showTopStudent();
float calculateAverage(float grades[], int size);

// This part tells the computer to display input
int main() {
    int choice;
    while (1) {
        printf("\n《======STUDENT MANAGEMENT SYSTEM======》\n");
        printf("1. Add New Student\n");
        printf("2. Display All Students\n");
        printf("3. Search for Student by ID\n");
        printf("4. Delete Student Record\n");
        printf("5. Update Student Grades\n");
        printf("6. Show Top Student\n");
        printf("0. Exit\n");
        
        printf("ENTER YOUR CHOICE!!: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: addStudent();
            case 2: displayStudents();
            case 3: searchStudent(); 
            case 4: deleteStudent(); 
            case 5: updateStudent(); 
            case 6: showTopStudent();
           case 0: exit(0);
            default: printf("Invalid choice. Try again.\n");
        }
    }
}
// Ask's the user to enter their name
void addStudent() {
    Student s;
    printf("Enter student name: ");
    getchar(); // clear newline
    fgets(s.name, sizeof(s.name), stdin);
    s.name[strcspn(s.name, "\n")] = '\0'; // remove newline

// Ask's the user to enter ID number
    printf("Enter student ID: ");
    scanf("%d", &s.id);

// Makes sure that the numbers entered are less that 5
    printf("Enter 5 grades :\n");
    for (int i = 0; i < 5; i++) {
        printf("Grade %d: ", i + 1);
        scanf("%f", &s.grades[i]);
    }
    s.average = calculateAverage(s.grades, 5);

    FILE *fp = fopen(FILE_NAME, "ab");
    if (!fp) {
        perror("Error opening file");
        return;
    }

    fwrite(&s, sizeof(Student), 1, fp);
    fclose(fp);
    printf("Student added successfully!\n");
}

void displayStudents() {
    FILE *fp = fopen(FILE_NAME, "rb");
    if (!fp) {
        perror("Error opening file");
        return;
    }

    Student s;
    printf("\n--- Student Records ---\n");
    while (fread(&s, sizeof(Student), 1, fp)) {
        printf("Name: %s\nID: %d\nGrades: ", s.name, s.id);
        for (int i = 0; i < 5; i++)
            printf("%.2f ", s.grades[i]);
        printf("\nAverage: %.2f\n\n", s.average);
    }

    fclose(fp);
}

void searchStudent() {
    int id;
    printf("Enter student ID to search: ");
    scanf("%d", &id);
    
    FILE *fp = fopen(FILE_NAME, "rb");
    if (!fp) {
        perror("Error opening file");
        return;
    }

    Student s;
    int found = 0;
    while (fread(&s, sizeof(Student), 1, fp)) {
        if (s.id == id) {
            printf("\nStudent Found:\n");
            printf("Name: %s\nID: %d\nGrades: ", s.name, s.id);
            for (int i = 0; i < 5; i++)
                printf("%.2f ", s.grades[i]);
            printf("\nAverage: %.2f\n", s.average);
            found = 1;
            break;
        }
    }

    if (!found) printf("Student with ID %d not found.\n", id);
    fclose(fp);
}

void deleteStudent() {
    int id;
    printf("Enter student ID to delete: ");
    scanf("%d", &id);

    FILE *fp = fopen(FILE_NAME, "rb");
    FILE *temp = fopen("temp.dat", "wb");
    if (!fp || !temp) {
        perror("Error opening files");
        return;
    }

    Student s;
    int found = 0;
    while (fread(&s, sizeof(Student), 1, fp)) {
        if (s.id == id) {
            found = 1;
            continue;
        }
        fwrite(&s, sizeof(Student), 1, temp);
    }

    fclose(fp);
    fclose(temp);
    remove(FILE_NAME);
    rename("temp.dat", FILE_NAME);

    if (found) printf("Student deleted successfully.\n");
    else printf("Student with ID %d not found.\n", id);
}

void updateStudent() {
    int id;
    printf("Enter student ID to update: ");
    scanf("%d", &id);

    FILE *fp = fopen(FILE_NAME, "rb+");
    if (!fp) {
        perror("Error opening file");
        return;
    }

    Student s;
    int found = 0;
    while (fread(&s, sizeof(Student), 1, fp)) {
        if (s.id == id) {
            printf("Enter new 5 grades:\n");
            for (int i = 0; i < 5; i++) {
                printf("Grade %d: ", i + 1);
                scanf("%f", &s.grades[i]);
            }
            s.average = calculateAverage(s.grades, 5);
            fseek(fp, -sizeof(Student), SEEK_CUR);
            fwrite(&s, sizeof(Student), 1, fp);
            found = 1;
            printf("Grades updated successfully.\n");
            break;
        }
    }

    if (!found) printf("Student with ID %d not found.\n", id);
    fclose(fp);
}

void showTopStudent() {
    FILE *fp = fopen(FILE_NAME, "rb");
    if (!fp) {
        perror("Error opening file");
        return;
    }

    Student s, topStudent;
    int first = 1;
    while (fread(&s, sizeof(Student), 1, fp)) {
        if (first || s.average > topStudent.average) {
            topStudent = s;
            first = 0;
        }
    }
    fclose(fp);

    if (first)
        printf("No student records found.\n");
    else {
        printf("\nTop Student:\n");
        printf("Name: %s\nID: %d\nGrades: ", topStudent.name, topStudent.id);
        for (int i = 0; i < 5; i++)
            printf("%.2f ", topStudent.grades[i]);
        printf("\nAverage: %.2f\n", topStudent.average);
    }
}

float calculateAverage(float grades[], int size) {
    float sum = 0;
    for (int i = 0; i < size; i++)
        sum += grades[i];
    return sum / size;
}
