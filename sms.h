#ifndef SMS_H
#define SMS_H

#include <windows.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <conio.h>

// --- Data Structures ---
struct StudentInfo {
    char ID[10];
    char Name[20];
    char Email[30];
    char Phone[20];
    int  NumberOfCourse;
    float Percentage;
    char Grade;       
    char Result[10];
};

struct CourseInfo {
    char StudentID[10];
    char Code[10];
    char Name[20];
    int Marks;
};

// --- Global Variables (Extern declarations) ---
extern struct StudentInfo Students[100];
extern struct CourseInfo Courses[500];
extern int TotalStudents;
extern int TotalCourse;
extern bool IsRunning;

// --- Function Prototypes ---
// Authentication & Core
void AdminLogin();
void Menu();

// Student Operations
void AddNewStudent();
void ShowAllStudents();
void ShowResultReport();
int  SearchStudent(char StudentID[10]);
void EditStudent(int StudentFoundIndex);
void DeleteStudent(int StudentIndex);
void DeleteAllStudents();
void DeleteCourseByIndex(int CourseIndex);
void DeleteStudentByIndex(int CourseIndex);
void CalculateResult(int studentIndex);

// File & Database Operations
void SaveDataToFile();
void LoadDataFromFile();
void DataSeed();

// Utilities & Validation
int  IsAlreadyExists(char GivenLine[300],char InfoType, char StudentID[300]);
bool IsValidNameFormat(char* name);
bool IsValidPhoneFormat(char* phone);
void UserGuideline();
void AboutUs();
void GoBackOrExit();
void ExitProject();

#endif