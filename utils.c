#include "sms.h"

bool IsValidNameFormat(char* name) {
    for(int k=0; k<strlen(name); k++) {
        if(isdigit(name[k])) return false;
    }
    return true;
}

bool IsValidPhoneFormat(char* phone) {
    for(int k=0; k<strlen(phone); k++) {
        if(!isdigit(phone[k])) return false;
    }
    return true;
}

int IsAlreadyExists(char GivenLine[300],char InfoType, char StudentID[300])
{
    int IDExists = 0, EmailExists = 0, PhoneExists = 0;
    for(int ep=0; ep<TotalStudents; ep++) {
        if(strcmp(GivenLine,Students[ep].ID) == 0) IDExists++;
        if(strcmp(GivenLine,Students[ep].Email) == 0 && strcmp(StudentID,Students[ep].ID) != 0 ) EmailExists++;
        if(strcmp(GivenLine,Students[ep].Phone) == 0 && strcmp(StudentID,Students[ep].ID) != 0) PhoneExists++;
    }
    if(InfoType == 'i') return IDExists;
    if(InfoType == 'e') return EmailExists;
    if(InfoType == 'p') return PhoneExists;
    return 0;
}

void UserGuideline()
{
    printf("\n\t\t **** How it Works? ****\n\n");
    printf(" -> Admin Login is required (admin / admin123).\n");
    printf(" -> Data is saved automatically to students.dat and courses.dat.\n");
    printf(" -> Pass mark is 40 per subject. Failing any subject results in an overall FAIL.\n");
    printf(" -> Letter Grades: A (>=75%%), B (>=60%%), C (>=50%%), D (>=40%%), F (<40%%).\n");
    printf(" -> Student Name must not contain numbers.\n");
    printf(" -> Student Phone must only contain digits.\n\n");
    printf(" ->> Project developed for UNIVERSITY OF MYSORE <<-\n\n");
}

void AboutUs()
{
    printf("\n\t\t **** About US? ****\n\n");
    printf(" -> This is a persistent Student Management System project.\n");
    printf(" -> Database architecture uses dual binary files for relational tracking.\n\n");
    printf(" ->> Project developed for UNIVERSITY OF MYSORE <<-\n\n");
}

void GoBackOrExit()
{
    getchar();
    char Option;
    printf(" Go back(b)? or Exit(0)?: ");
    scanf("%c",&Option);
    if(Option == '0') ExitProject();
    else system("cls");
}

void ExitProject()
{
    system("cls");
    printf(" ========= Thank You =========\n");
    printf(" ========= See You Soon ======\n");
    exit(0);
}