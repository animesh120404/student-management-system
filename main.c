#include "sms.h"

// --- Global Variable Instantiation ---
struct StudentInfo Students[100];
struct CourseInfo Courses[500];
int TotalStudents = 0;
int TotalCourse = 0;
bool IsRunning = true;

int main()
{
    AdminLogin();
    LoadDataFromFile();

    while(IsRunning)
    {
        Menu();
        int Option;
        if(scanf("%d",&Option) != 1) { 
            while(getchar() != '\n'); 
            Option = -1;
        }

        char StudentID[10]; // Localized variable for safety

        switch(Option)
        {
        case 0:
            IsRunning = false;
            ExitProject();
            break;
        case 1:
            system("cls");
            printf("\n\t\t **** Add A New Student ****\n\n");
            AddNewStudent();
            SaveDataToFile(); 
            GoBackOrExit();
            break;
        case 2:
            system("cls");
            printf("\n\t\t **** All Students ****\n\n");
            ShowAllStudents();
            GoBackOrExit();
            break;
        case 3:
            system("cls");
            printf("\n\t\t **** Search Students ****\n\n");
            printf(" Enter The Student ID: ");
            scanf("%s",StudentID);
            if(SearchStudent(StudentID) < 0) {
                printf(" No Student Found\n\n");
            }
            printf("\n");
            GoBackOrExit();
            break;
        case 4:
            system("cls");
            printf("\n\t\t **** Edit a Student ****\n\n");
            printf(" Enter The Student ID: ");
            scanf("%s",StudentID);
            int StudentFoundIndex = SearchStudent(StudentID);
            if(StudentFoundIndex >= 0) {
                EditStudent(StudentFoundIndex);
                SaveDataToFile(); 
            } else {
                printf(" No Student Found\n\n");
            }
            GoBackOrExit();
            break;
        case 5:
            system("cls");
            printf("\n\t\t **** Delete a Student ****\n\n");
            printf(" Enter The Student ID: ");
            scanf("%s",StudentID);
            int DeleteStudentFoundIndex = SearchStudent(StudentID);
            if(DeleteStudentFoundIndex >= 0) {
                char Sure = 'N';
                getchar();
                printf("\n\n Are you sure want to delete this student? (Y/N): ");
                scanf("%c",&Sure);
                if(Sure == 'Y' || Sure == 'y') {
                    DeleteStudent(DeleteStudentFoundIndex);
                    SaveDataToFile(); 
                } else {
                    printf(" Your Data is Safe.\n\n");
                    GoBackOrExit();
                }
            } else {
                printf(" No Student Found\n\n");
                GoBackOrExit();
            }
            break;
        case 6:
        {
            char Sure = 'N';
            getchar();
            system("cls");
            printf("\n\t\t **** Delete ALL Students ****\n\n");
            printf(" Are you sure want to delete all the students? (Y/N): ");
            scanf("%c",&Sure);
            if(Sure == 'Y' || Sure == 'y') {
                DeleteAllStudents();
                SaveDataToFile(); 
            } else {
                printf(" Your Data is Safe.\n\n");
                GoBackOrExit();
            }
            break;
        }
        case 7:
            system("cls");
            break;
        case 8:
            system("cls");
            UserGuideline();
            GoBackOrExit();
            break;
        case 9:
            system("cls");
            AboutUs();
            GoBackOrExit();
            break;
        case 10:
            system("cls");
            printf("\n\t\t **** Academic Result Report ****\n\n");
            ShowResultReport();
            GoBackOrExit();
            break;
        default:
            printf("\n\t\t Invalid Option. Please try again.\n");
            Sleep(1000);
            system("cls");
            break;
        }
    }
    return 0;
}

void AdminLogin()
{
    char username[20];
    char password[20];
    int attempts = 3;

    while(attempts > 0)
    {
        system("cls");
        printf("\n\n\t*** Student Management System Login ***\n\n");
        printf("\t\tUsername: ");
        scanf("%s", username);
        printf("\t\tPassword: ");
        
        int p = 0;
        char ch;
        while(1) {
            ch = getch();
            if(ch == 13) { 
                password[p] = '\0';
                break;
            } else if(ch == 8) { 
                if(p > 0) {
                    p--;
                    printf("\b \b");
                }
            } else {
                password[p++] = ch;
                printf("*");
            }
        }

        if(strcmp(username, "admin") == 0 && strcmp(password, "admin123") == 0) {
            printf("\n\n\t\tLogin Successful! Welcome Admin.\n");
            Sleep(1000);
            system("cls");
            return;
        } else {
            attempts--;
            printf("\n\n\t\tInvalid Credentials! %d attempts remaining.\n", attempts);
            Sleep(1500);
        }
    }
    printf("\n\t\tToo many failed attempts. Exiting program...\n");
    exit(0);
}

void Menu()
{
    int passed = 0;
    int failed = 0;
    for(int k=0; k<TotalStudents; k++) {
        if(strcmp(Students[k].Result, "PASS") == 0) passed++;
        else failed++;
    }

    printf("\n\n\t*** Student Management System Using C ***\n\n");
    printf("\t\t[ SYSTEM DASHBOARD ]\n");
    printf("\t\tTotal Enrolled : %d\n", TotalStudents);
    printf("\t\tTotal Courses  : %d\n", TotalCourse);
    printf("\t\tPassed/Failed  : %d / %d\n", passed, failed);
    printf("\t\t=======================\n");
    printf("\t\t\tMAIN MENU\n");
    printf("\t\t=======================\n");
    printf("\t\t[1] Add A New student.\n");
    printf("\t\t[2] Show All students.\n");
    printf("\t\t[3] Search A student.\n");
    printf("\t\t[4] Edit A student.\n");
    printf("\t\t[5] Delete A student.\n");
    printf("\t\t[6] Delete All students.\n");
    printf("\t\t[7] Clear The window.\n");
    printf("\t\t[8] User Guideline.\n");
    printf("\t\t[9] About Us.\n");
    printf("\t\t[10] View Result Report.\n");
    printf("\t\t[0] Exit the Program.\n");
    printf("\t\t=======================\n");
    printf("\t\tEnter The Choice: ");
}