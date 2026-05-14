#include "sms.h"

void SaveDataToFile()
{
    FILE *fs = fopen("students.dat", "wb");
    if(fs != NULL) {
        fwrite(&TotalStudents, sizeof(int), 1, fs);
        fwrite(Students, sizeof(struct StudentInfo), TotalStudents, fs);
        fclose(fs);
    }

    FILE *fc = fopen("courses.dat", "wb");
    if(fc != NULL) {
        fwrite(&TotalCourse, sizeof(int), 1, fc);
        fwrite(Courses, sizeof(struct CourseInfo), TotalCourse, fc);
        fclose(fc);
    }
}

void LoadDataFromFile()
{
    FILE *fs = fopen("students.dat", "rb");
    FILE *fc = fopen("courses.dat", "rb");

    if(fs != NULL && fc != NULL) {
        fread(&TotalStudents, sizeof(int), 1, fs);
        fread(Students, sizeof(struct StudentInfo), TotalStudents, fs);
        fclose(fs);
        
        fread(&TotalCourse, sizeof(int), 1, fc);
        fread(Courses, sizeof(struct CourseInfo), TotalCourse, fc);
        fclose(fc);
    } else {
        printf("\n\t\tWARNING: Database files not found or corrupted.\n");
        printf("\t\tInitializing system with default dummy data...\n");
        Sleep(3000); 
        system("cls");
        DataSeed();
        SaveDataToFile();
    }
}

void DataSeed()
{
    strcpy(Students[0].ID,"S-1"); strcpy(Students[0].Name,"Student One"); strcpy(Students[0].Phone,"01611111111"); strcpy(Students[0].Email,"student-1@gmail.com"); Students[0].NumberOfCourse=1;
    strcpy(Courses[0].StudentID,"S-1"); strcpy(Courses[0].Code,"CSE-1"); strcpy(Courses[0].Name,"Course - 1"); Courses[0].Marks = 85;
    CalculateResult(0);

    strcpy(Students[1].ID,"S-2"); strcpy(Students[1].Name,"Student Two"); strcpy(Students[1].Phone,"01611111112"); strcpy(Students[1].Email,"student-2@gmail.com"); Students[1].NumberOfCourse=2;
    strcpy(Courses[1].StudentID,"S-2"); strcpy(Courses[1].Code,"CSE-1"); strcpy(Courses[1].Name,"Course - 1"); Courses[1].Marks = 92;
    strcpy(Courses[2].StudentID,"S-2"); strcpy(Courses[2].Code,"CSE-2"); strcpy(Courses[2].Name,"Course - 2"); Courses[2].Marks = 35; 
    CalculateResult(1);

    TotalStudents = 2;
    TotalCourse = 3;
}