#include "sms.h"

void AddNewStudent()
{
    char StudentID[300], Name[300], Phone[300], Email[300], CourseCode[300], CourseName[300];
    int NumberOfCourses, Marks;

    int IsValidID = 0;
    while(!IsValidID) {
        printf(" Enter The ID (e.g. S-1): ");
        scanf("%s",&StudentID);
        if(IsAlreadyExists(StudentID,'i',StudentID) > 0) printf(" Error: This ID is already exists.\n\n");
        else if(strlen(StudentID) > 10) printf(" Error: ID can not be more than 10 characters.\n\n");
        else IsValidID = 1;
    }

    int IsValidName = 0;
    while(!IsValidName) {
        printf(" Enter The Name: ");
        scanf(" %[^\n]s",&Name);
        if(strlen(Name) > 19) printf(" Error: Name can not be more than 19 characters.\n\n");
        else if(!IsValidNameFormat(Name)) printf(" Error: Name cannot contain numbers.\n\n");
        else IsValidName = 1;
    }

    int IsValidEmail = 0;
    while(!IsValidEmail) {
        printf(" Enter The Email: ");
        scanf("%s",&Email);
        if(IsAlreadyExists(Email,'e',StudentID) > 0) printf(" This Email is Already Exists.\n");
        else IsValidEmail = 1;
    }

    int IsValidPhone = 0;
    while(!IsValidPhone) {
        printf(" Enter The Phone: ");
        scanf("%s",&Phone);
        if(IsAlreadyExists(Phone,'p',StudentID) > 0) printf(" This Phone Number is Already Exists\n");
        else if(!IsValidPhoneFormat(Phone)) printf(" Error: Phone must contain only digits.\n\n");
        else IsValidPhone = 1;
    }

    int IsValidNumberOfCourse = 0;
    while(!IsValidNumberOfCourse) {
        printf(" Number of courses: ");
        if(scanf("%d",&NumberOfCourses) == 1 && NumberOfCourses > 0 && NumberOfCourses <= 4) {
            IsValidNumberOfCourse = 1;
        } else {
            printf(" Error: Min 1, Max 4 courses allowed.\n\n");
            while(getchar() != '\n'); 
        }
    }

    strcpy(Students[TotalStudents].ID,StudentID);
    strcpy(Students[TotalStudents].Name,Name);
    strcpy(Students[TotalStudents].Phone,Phone);
    strcpy(Students[TotalStudents].Email,Email);
    Students[TotalStudents].NumberOfCourse = NumberOfCourses;

    for(int i=0; i<NumberOfCourses; i++) {
        printf(" Enter Course %d Code: ",i+1); scanf("%s",&CourseCode);
        printf(" Enter Course %d Name: ",i+1); scanf(" %[^\n]s",&CourseName);
        
        int IsValidMarks = 0;
        while(!IsValidMarks) {
            printf(" Enter Course %d Marks (0-100): ", i+1);
            if(scanf("%d", &Marks) == 1 && Marks >= 0 && Marks <= 100) {
                IsValidMarks = 1;
            } else {
                printf(" Error: Marks must be a valid number between 0 and 100.\n\n");
                while(getchar() != '\n'); 
            }
        }

        strcpy(Courses[TotalCourse].StudentID,StudentID);
        strcpy(Courses[TotalCourse].Code,CourseCode);
        strcpy(Courses[TotalCourse].Name,CourseName);
        Courses[TotalCourse].Marks = Marks;
        TotalCourse++;
    }
    
    CalculateResult(TotalStudents); 
    TotalStudents++;
    printf("\n Student Added Successfully.\n\n");
}

void ShowAllStudents()
{
    printf("|==========|======================|======================|=========|=======|========|\n");
    printf("|    ID    |         Name         |        Phone         | Percent | Grade | Result |\n");
    printf("|==========|======================|======================|=========|=======|========|\n");

    for(int i=0; i<TotalStudents; i++) {
        printf("| %-8s | %-20s | %-20s | %-6.2f%% |   %-3c | %-6s |\n", 
            Students[i].ID, Students[i].Name, Students[i].Phone, Students[i].Percentage, Students[i].Grade, Students[i].Result);
        printf("|----------|----------------------|----------------------|---------|-------|--------|\n");
    }
    printf("\n");
}

void ShowResultReport()
{
    printf("|==========|======================|=========|=======|========|\n");
    printf("|    ID    |         Name         | Percent | Grade | Result |\n");
    printf("|==========|======================|=========|=======|========|\n");

    for(int i=0; i<TotalStudents; i++) {
        printf("| %-8s | %-20s | %-6.2f%% |   %-3c | %-6s |\n", 
            Students[i].ID, Students[i].Name, Students[i].Percentage, Students[i].Grade, Students[i].Result);
        printf("|----------|----------------------|---------|-------|--------|\n");
    }
    printf("\n");
}

int SearchStudent(char StudentID[10])
{
    system("cls");
    int StudentFoundIndex = -1;

    for(int i=0; i<TotalStudents; i++) {
        if(strcmp(StudentID,Students[i].ID) == 0) {
            StudentFoundIndex = i;
            printf("\n One Student Found for ID: %s\n\n",StudentID);
            printf(" Student Informations\n");
            printf("-------------------------\n");
            printf(" ID:     %s\n",Students[i].ID);
            printf(" Name:   %s\n",Students[i].Name);
            printf(" Email:  %s\n",Students[i].Email);
            printf(" Phone:  %s\n",Students[i].Phone);
            printf(" Result: %.2f%% | Grade: %c | %s\n", Students[i].Percentage, Students[i].Grade, Students[i].Result);
            printf("\n Total Number of Courses: %d\n",Students[i].NumberOfCourse);
        }
    }
    int CourseCount = 0;
    for(int j=0; j<TotalCourse; j++) {
        if(strcmp(StudentID,Courses[j].StudentID) == 0) {
            CourseCount++;
            printf(" Course %d Code: %s | Name: %s | Marks: %d\n",CourseCount,Courses[j].Code, Courses[j].Name, Courses[j].Marks);
        }
    }
    return StudentFoundIndex;
}

void EditStudent(int StudentFoundIndex)
{
    printf("\n\t\t **** Update The New Student ****\n\n");

    char NewName[300], NewPhone[300], NewEmail[300], StudentID[300];
    int NewNumberOfCourses;
    strcpy(StudentID, Students[StudentFoundIndex].ID);
    int OldTotalCourse = Students[StudentFoundIndex].NumberOfCourse;

    int IsValidName = 0;
    while(!IsValidName) {
        printf(" Enter The New Name(0 for skip): ");
        scanf(" %[^\n]s",&NewName);
        if(strcmp(NewName,"0") == 0) break;
        if(strlen(NewName) > 19) printf(" Error: Name can not be more than 19 characters.\n\n");
        else if(!IsValidNameFormat(NewName)) printf(" Error: Name cannot contain numbers.\n\n");
        else { strcpy(Students[StudentFoundIndex].Name,NewName); IsValidName = 1; }
    }

    int IsValidEmail = 0;
    while(!IsValidEmail) {
        printf(" Enter The New Email(0 for skip): ");
        scanf("%s",&NewEmail);
        if(strcmp(NewEmail,"0") == 0) break;
        if(IsAlreadyExists(NewEmail,'e',StudentID) > 0) printf(" Error: This Email Already Exists.\n\n");
        else { strcpy(Students[StudentFoundIndex].Email,NewEmail); IsValidEmail = 1; }
    }

    int IsValidPhone = 0;
    while(!IsValidPhone) {
        printf(" Enter The New Phone(0 for skip): ");
        scanf("%s",&NewPhone);
        if(strcmp(NewPhone,"0") == 0) break;
        if(IsAlreadyExists(NewPhone,'p',StudentID) > 0) printf(" Error: This Phone Number is Already Exists.\n\n");
        else if(!IsValidPhoneFormat(NewPhone)) printf(" Error: Phone must contain only digits.\n\n");
        else { strcpy(Students[StudentFoundIndex].Phone,NewPhone); IsValidPhone = 1; }
    }

    int IsValidCourses = 0;
    while(!IsValidCourses) {
        printf(" Number of New courses(0 for skip): ");
        if(scanf("%d",&NewNumberOfCourses) == 1) {
            if(NewNumberOfCourses == 0) break;
            if(NewNumberOfCourses > 0 && NewNumberOfCourses <= 4) IsValidCourses = 1;
            else printf(" Error: Max 4 courses allowed.\n\n");
        } else {
            printf(" Error: Invalid input.\n\n");
            while(getchar() != '\n'); 
        }
    }

    if(NewNumberOfCourses > 0 && NewNumberOfCourses <= 4) {
        Students[StudentFoundIndex].NumberOfCourse = NewNumberOfCourses;
        int FirstCourseIndex;
        for(int dc=0; dc<TotalCourse; dc++) {
            if(strcmp(StudentID,Courses[dc].StudentID) == 0) { FirstCourseIndex = dc; break; }
        }
        for(int dc=1; dc<=OldTotalCourse; dc++) DeleteCourseByIndex(FirstCourseIndex);

        char CourseCode[300], CourseName[300];
        int Marks;
        for(int i=1; i<=NewNumberOfCourses; i++) {
            printf(" Enter New Course %d Code: ",i); scanf("%s",&CourseCode);
            printf(" Enter New Course %d Name: ",i); scanf(" %[^\n]s",&CourseName);
            
            int IsValidMarks = 0;
            while(!IsValidMarks) {
                printf(" Enter New Course %d Marks (0-100): ", i);
                if(scanf("%d", &Marks) == 1 && Marks >= 0 && Marks <= 100) IsValidMarks = 1;
                else { printf(" Error: Marks must be a valid number between 0 and 100.\n\n"); while(getchar() != '\n'); }
            }
            strcpy(Courses[TotalCourse].StudentID,StudentID);
            strcpy(Courses[TotalCourse].Code,CourseCode);
            strcpy(Courses[TotalCourse].Name,CourseName);
            Courses[TotalCourse].Marks = Marks;
            TotalCourse++;
        }
    }
    CalculateResult(StudentFoundIndex);
    printf(" Student Updated Successfully.\n\n");
}

void DeleteStudent(int StudentIndex)
{
    int FirstCourseIndexs;
    struct StudentInfo ThisStudents = Students[StudentIndex];
    for(int d=0; d<TotalCourse; d++) {
        if(strcmp(ThisStudents.ID,Courses[d].StudentID) == 0) { FirstCourseIndexs = d; break; }
    }
    for(int d=1; d<=ThisStudents.NumberOfCourse; d++) DeleteCourseByIndex(FirstCourseIndexs);
    DeleteStudentByIndex(StudentIndex);
    printf(" Student Deleted Successfully.\n\n");
    GoBackOrExit();
}

void DeleteAllStudents()
{
    TotalStudents = 0;
    TotalCourse = 0;
    printf(" All Students Deleted Successfully.\n\n");
    GoBackOrExit();
}

void DeleteCourseByIndex(int CourseIndex)
{
    for(int c=CourseIndex; c<TotalCourse-1; c++) Courses[c] = Courses[c+1];
    TotalCourse--;
}

void DeleteStudentByIndex(int CourseIndex)
{
    for(int s=CourseIndex; s<TotalStudents-1; s++) Students[s] = Students[s+1];
    TotalStudents--;
}

void CalculateResult(int studentIndex) {
    int totalMarks = 0;
    int maxMarks = Students[studentIndex].NumberOfCourse * 100;
    bool hasFailed = false;

    for(int c=0; c<TotalCourse; c++) {
        if(strcmp(Students[studentIndex].ID, Courses[c].StudentID) == 0) {
            totalMarks += Courses[c].Marks;
            if(Courses[c].Marks < 40) hasFailed = true;
        }
    }

    if(maxMarks > 0) Students[studentIndex].Percentage = ((float)totalMarks / maxMarks) * 100;
    else Students[studentIndex].Percentage = 0.0;

    if(hasFailed || Students[studentIndex].Percentage < 40.0) {
        strcpy(Students[studentIndex].Result, "FAIL");
        Students[studentIndex].Grade = 'F';
    } else {
        strcpy(Students[studentIndex].Result, "PASS");
        if(Students[studentIndex].Percentage >= 75.0) Students[studentIndex].Grade = 'A';
        else if(Students[studentIndex].Percentage >= 60.0) Students[studentIndex].Grade = 'B';
        else if(Students[studentIndex].Percentage >= 50.0) Students[studentIndex].Grade = 'C';
        else Students[studentIndex].Grade = 'D';
    }
}