#include <stdio.h>

struct Sub {
    float marks;
    int grade;
    int credits;
};

struct Sem {
    struct Sub subjects[4];
    int semNum;
    float sgpa;
};

struct Student {
    char firstName[30];
    char secondName[30];
    char lastName[30];
    struct Sem semesters[2];
    int rollNum;
};

float calculateSGPA(struct Sem *sem) {
    float totalGradestarts = 0;
    int totalCredits = 0;

    for (int i = 0; i < 4; i++) {
        float marks = sem->subjects[i].marks;
        int credits = sem->subjects[i].credits;

        if (85 <= marks && marks <= 100) {
            sem->subjects[i].grade = 10;
        } else if (75 <= marks && marks < 85) {
            sem->subjects[i].grade = 9;
        } else if (65 <= marks && marks < 75) {
            sem->subjects[i].grade = 8;
        } else if (55 <= marks && marks < 65) {
            sem->subjects[i].grade = 7;
        } else if (45 <= marks && marks < 55) {
            sem->subjects[i].grade = 6;
        } else if (40 <= marks && marks < 45) {
            sem->subjects[i].grade = 5;
        } else {
            sem->subjects[i].grade = 0;
        }

        totalGradestarts += sem->subjects[i].grade * credits;
        totalCredits += credits;
    }

    return totalGradestarts / totalCredits;
}

void inputSemester(struct Student *student, int semIndex) {
    printf("Enter semester number: ");
    scanf("%d", &(student->semesters[semIndex].semNum));

    printf("Enter marks and credits for MATHEMATICS-I: ");
    scanf("%f %d", &(student->semesters[semIndex].subjects[0].marks), &(student->semesters[semIndex].subjects[0].credits));

    printf("Enter marks and credits for BASICS OF ELECTRICAL ENGINEERING: ");
    scanf("%f %d", &(student->semesters[semIndex].subjects[1].marks), &(student->semesters[semIndex].subjects[1].credits));

    printf("Enter marks and credits for BASICS OF MECHANICAL ENGINEERING: ");
    scanf("%f %d", &(student->semesters[semIndex].subjects[2].marks), &(student->semesters[semIndex].subjects[2].credits));

    printf("Enter marks and credits for CHEMISTRY: ");
    scanf("%f %d", &(student->semesters[semIndex].subjects[3].marks), &(student->semesters[semIndex].subjects[3].credits));

    student->semesters[semIndex].sgpa = calculateSGPA(&(student->semesters[semIndex]));
}

int main() {
        printf ("*****************************************************");
    printf ("\n Roll number: 23B-CO-010\n");
    printf (" PR Number - 202311390\n");
    printf("*****************************************************\n\n\n");
    
    struct Student student;

    printf("Enter student's first name: ");
    scanf("%s", student.firstName);

    printf("Enter student's second name: ");
    scanf("%s", student.secondName);

    printf("Enter student's last name: ");
    scanf("%s", student.lastName);

    printf("Enter student's roll number: ");
    scanf("%d", &student.rollNum);

    inputSemester(&student, 0);

    printf("Enter semester number .: ");
    scanf("%d", &(student.semesters[1].semNum));

    printf("Enter marks and credits for MATHEMATICS-II: ");
    scanf("%f %d", &(student.semesters[1].subjects[0].marks), &(student.semesters[1].subjects[0].credits));

    printf("Enter marks and credits for PHYSICS: ");
    scanf("%f %d", &(student.semesters[1].subjects[1].marks), &(student.semesters[1].subjects[1].credits));

    printf("Enter marks and credits for CIVIL ENGINEERING: ");
    scanf("%f %d", &(student.semesters[1].subjects[2].marks), &(student.semesters[1].subjects[2].credits));

    printf("Enter marks and credits for COMPUTER PROGRAMMING: ");
    scanf("%f %d", &(student.semesters[1].subjects[3].marks), &(student.semesters[1].subjects[3].credits));

    student.semesters[1].sgpa = calculateSGPA(&(student.semesters[1]));

    float cgpa = (student.semesters[0].sgpa + student.semesters[1].sgpa) / 2;

    printf("\nRESULTS\n\n");
    printf("Student Name: %s %s %s\n", student.firstName, student.secondName, student.lastName);
    printf("Roll Number: %d\n", student.rollNum);

    for (int i = 0; i < 2; i++) {
        if (i==0){
        printf ("Semesters 1 RESULTS : \n") ;
        printf ("---------------------------------------------------------------------\n");
        printf(" :       SUBJECT                     :   MARKS   : CREDITS  :   GRADE : \n ") ;
        printf ("---------------------------------------------------------------------\n") ;
        printf(" : MATHEMATICS %d                     :   %.1f    :   %d     :  %2d      :\n ", i + 1, student.semesters[i].subjects[0].marks, student.semesters[i].subjects[0].credits, student.semesters[i].subjects[0].grade);
        printf(": BASICS OF ELECTRICAL ENGINEERING  :   %.1f    :   %d     :  %2d      :\n ", student.semesters[i].subjects[2].marks, student.semesters[i].subjects[2].credits, student.semesters[i].subjects[2].grade);
        printf(": BASICS OF MECHANICAL ENGINEERING  :   %.1f    :   %d     :  %2d      :\n", student.semesters[i].subjects[3].marks, student.semesters[i].subjects[3].credits, student.semesters[i].subjects[3].grade);
        printf(" : CHEMISTRY                         :   %.1f    :   %d     :  %2d      :\n ", student.semesters[i].subjects[1].marks, student.semesters[i].subjects[1].credits, student.semesters[i].subjects[1].grade);
        printf ("---------------------------------------------------------------------\n");
        printf("SGPA: %.2f\n", student.semesters[i].sgpa); 
        printf ("\n\n\n") ;
        }
        else {
 
      printf ("Semesters 2 RESULTS : \n") ;
        printf ("---------------------------------------------------------------------\n");
        printf(" :       SUBJECT                    :   MARKS   : CREDITS  :   GRADE : \n ") ;
        printf ("---------------------------------------------------------------------\n") ;
        printf(" : MATHEMATICS %d                     :   %.1f    :   %d     :  %2d     :\n ", i + 1, student.semesters[i].subjects[0].marks, student.semesters[i].subjects[0].credits, student.semesters[i].subjects[0].grade);
        printf(": INTRODUCTION TO CIVIL ENGINEERING :   %.1f    :   %d     :  %2d     :\n ", student.semesters[i].subjects[2].marks, student.semesters[i].subjects[2].credits, student.semesters[i].subjects[2].grade);
        printf(": COMPUTER PROGRAMMING              :   %.1f    :   %d     :  %2d     :\n", student.semesters[i].subjects[3].marks, student.semesters[i].subjects[3].credits, student.semesters[i].subjects[3].grade);
        printf(" : PHYSICS                           :   %.1f    :   %d     :  %2d     :\n ", student.semesters[i].subjects[1].marks, student.semesters[i].subjects[1].credits, student.semesters[i].subjects[1].grade);
        printf ("---------------------------------------------------------------------\n");
        printf("SGPA: %.2f\n", student.semesters[i].sgpa);
       }
    }

    printf("\nCGPA: %.2f\n", cgpa);

    return 0;
}