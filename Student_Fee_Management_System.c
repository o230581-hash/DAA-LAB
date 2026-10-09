#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 1000
#define STUDENT_FILE "students.csv"
#define YEAR1_TUITION 40000
#define YEAR1_HOSTEL  20000
#define YEAR1_MESS    18000
#define YEAR1_EXAM     2000

#define YEAR2_TUITION 42000
#define YEAR2_HOSTEL  21000
#define YEAR2_MESS    18500
#define YEAR2_EXAM     2000

#define YEAR3_TUITION 45000
#define YEAR3_HOSTEL  22000
#define YEAR3_MESS    19000
#define YEAR3_EXAM     2500

#define YEAR4_TUITION 48000
#define YEAR4_HOSTEL  23000
#define YEAR4_MESS    20000
#define YEAR4_EXAM     2500

typedef struct
{
    char id[25];
    char name[50];
    char branch[20];
    int year;

    float tuitionFee;
    float hostelFee;
    float messFee;
    float examFee;
    float totalFee;

    int scholarship;          // 1 = Yes, 0 = No
    float scholarshipAmount;

    float feePaid;
    float pendingFee;

} Student;

Student students[MAX_STUDENTS];
int studentCount = 0;

/* ---------- Function Prototypes ---------- */

void loadStudents(void);
void saveStudents(void);

void showDashboard(void);
void showMenu(void);

void assignFees(Student *s);
void calculateFees(Student *s);

void addStudent(void);
void searchByID(void);
void searchByName(void);
void displayStudents(void);
void updateStudent(void);
void deleteStudent(void);

void displayPendingStudents(void);
void displayScholarshipStudents(void);
void displayNonScholarshipStudents(void);

void sortByPendingFee(void);
void sortByStudentName(void);

int comparePendingFeeDesc(const void *a,const void *b);
int compareNameAsc(const void *a,const void *b);

int main(void)
{
    int choice;

    loadStudents();

    do
    {
        showDashboard();
        showMenu();

        printf("\nEnter your choice: ");
        if (scanf("%d", &choice) != 1)
{
    printf("Invalid input!\n");

    while (getchar() != '\n');   // Clear input buffer
    continue;
}

        switch(choice)
        {
            case 1: addStudent(); break;
            case 2: searchByID(); break;
            case 3: searchByName(); break;
            case 4: displayStudents(); break;
            case 5: updateStudent(); break;
            case 6: deleteStudent(); break;
            case 7: displayPendingStudents(); break;
            case 8: displayScholarshipStudents(); break;
            case 9: displayNonScholarshipStudents(); break;
            case 10: sortByPendingFee(); break;
            case 11: sortByStudentName(); break;
            case 12:
                saveStudents();
                printf("\nThank you for using Student Fee Management System.\n");
                break;
            default:
                printf("\nInvalid Choice!\n");
        }

    }while(choice != 12);

    return 0;
}
/*==============================================================
                        MENU
==============================================================*/

void showMenu(void)
{
    printf("\n==============================================================\n");
    printf("              STUDENT FEE MANAGEMENT SYSTEM\n");
    printf("==============================================================\n");
    printf("1.  Add New Student Fee Record\n");
    printf("2.  Search Student by ID\n");
    printf("3.  Search Student by Name\n");
    printf("4.  Display All Student Records\n");
    printf("5.  Update Fee / Student Details\n");
    printf("6.  Delete Student Record\n");
    printf("7.  Display Pending Fee Students\n");
    printf("8.  Display Scholarship Students\n");
    printf("9.  Display Non-Scholarship Students\n");
    printf("10. Sort Records by Pending Fee\n");
    printf("11. Sort Records by Student Name\n");
    printf("12. Exit\n");
    printf("==============================================================\n");
}

/*==============================================================
                ASSIGN FEES AUTOMATICALLY
==============================================================*/

void assignFees(Student *s)
{
    switch(s->year)
    {
        case 1:
            s->tuitionFee = YEAR1_TUITION;
            s->hostelFee  = YEAR1_HOSTEL;
            s->messFee    = YEAR1_MESS;
            s->examFee    = YEAR1_EXAM;
            break;

        case 2:
            s->tuitionFee = YEAR2_TUITION;
            s->hostelFee  = YEAR2_HOSTEL;
            s->messFee    = YEAR2_MESS;
            s->examFee    = YEAR2_EXAM;
            break;

        case 3:
            s->tuitionFee = YEAR3_TUITION;
            s->hostelFee  = YEAR3_HOSTEL;
            s->messFee    = YEAR3_MESS;
            s->examFee    = YEAR3_EXAM;
            break;

        case 4:
            s->tuitionFee = YEAR4_TUITION;
            s->hostelFee  = YEAR4_HOSTEL;
            s->messFee    = YEAR4_MESS;
            s->examFee    = YEAR4_EXAM;
            break;

        default:
            s->tuitionFee = 0;
            s->hostelFee  = 0;
            s->messFee    = 0;
            s->examFee    = 0;
    }
}

/*==============================================================
                CALCULATE TOTAL & PENDING FEES
==============================================================*/

void calculateFees(Student *s)
{
    s->totalFee = s->tuitionFee +
                  s->hostelFee +
                  s->messFee +
                  s->examFee;

    s->pendingFee = s->totalFee -
                    s->scholarshipAmount -
                    s->feePaid;

    if(s->pendingFee < 0)
        s->pendingFee = 0;
}

/*==============================================================
                    SAVE RECORDS
==============================================================*/

void saveStudents(void)
{
    FILE *fp = fopen(STUDENT_FILE,"w");

    if(fp == NULL)
    {
        printf("\nUnable to save records!\n");
        return;
    }

    fprintf(fp,"ID,Name,Branch,Year,TuitionFee,HostelFee,MessFee,ExamFee,TotalFee,Scholarship,ScholarshipAmount,FeePaid,PendingFee\n");

    for(int i=0;i<studentCount;i++)
    {
        fprintf(fp,
        "%s,%s,%s,%d,%.2f,%.2f,%.2f,%.2f,%.2f,%d,%.2f,%.2f,%.2f\n",

        students[i].id,
        students[i].name,
        students[i].branch,
        students[i].year,
        students[i].tuitionFee,
        students[i].hostelFee,
        students[i].messFee,
        students[i].examFee,
        students[i].totalFee,
        students[i].scholarship,
        students[i].scholarshipAmount,
        students[i].feePaid,
        students[i].pendingFee);
    }

    fclose(fp);
}

/*==============================================================
                    LOAD RECORDS
==============================================================*/

void loadStudents(void)
{
    FILE *fp = fopen(STUDENT_FILE,"r");

    if(fp == NULL)
        return;

    char header[300];
    fgets(header,sizeof(header),fp);

    studentCount = 0;

    while(fscanf(fp,
   "%24[^,],%49[^,],%19[^,],%d,%f,%f,%f,%f,%f,%d,%f,%f,%f",
    students[studentCount].id,
    students[studentCount].name,
    students[studentCount].branch,
    &students[studentCount].year,
    &students[studentCount].tuitionFee,
    &students[studentCount].hostelFee,
    &students[studentCount].messFee,
    &students[studentCount].examFee,
    &students[studentCount].totalFee,
    &students[studentCount].scholarship,
    &students[studentCount].scholarshipAmount,
    &students[studentCount].feePaid,
    &students[studentCount].pendingFee) == 13)
    {
        studentCount++;

        if(studentCount >= MAX_STUDENTS)
            break;
    }

    fclose(fp);
}

/*==============================================================
                    DASHBOARD
==============================================================*/

void showDashboard(void)
{
    int scholarshipStudents = 0;
    int nonScholarshipStudents = 0;
    int pendingStudents = 0;

    float totalCollected = 0;
    float totalPending = 0;

    for(int i=0;i<studentCount;i++)
    {
        totalCollected += students[i].feePaid;
        totalPending += students[i].pendingFee;

        if(students[i].scholarship)
            scholarshipStudents++;
        else
            nonScholarshipStudents++;

        if(students[i].pendingFee > 0)
            pendingStudents++;
    }

    printf("\n==============================================================\n");
    printf("                 STUDENT FEE MANAGEMENT SYSTEM\n");
    printf("==============================================================\n");
    printf("Total Students            : %d\n",studentCount);
    printf("Scholarship Students      : %d\n",scholarshipStudents);
    printf("Non-Scholarship Students  : %d\n",nonScholarshipStudents);
    printf("Pending Fee Students      : %d\n",pendingStudents);
    printf("Total Fee Collected       : %.2f\n",totalCollected);
    printf("Total Pending Amount      : %.2f\n",totalPending);
    printf("==============================================================\n");
}
/*==============================================================
                        ADD NEW STUDENT
==============================================================*/

void addStudent(void)
{
    Student s;
    int found = 0;

    if(studentCount >= MAX_STUDENTS)
    {
        printf("\nDatabase is Full!\n");
        return;
    }

    printf("\n=========== ADD NEW STUDENT ===========\n");

    printf("Enter Student ID : ");
    scanf("%24s", s.id);

    /* Check Duplicate ID */
    for(int i = 0; i < studentCount; i++)
    {
        if(strcmp(students[i].id, s.id) == 0)
        {
            found = 1;
            break;
        }
    }

    if(found)
    {
        printf("\nStudent ID already exists!\n");
        return;
    }

    getchar();

    printf("Enter Student Name : ");
    fgets(s.name, sizeof(s.name), stdin);
    s.name[strcspn(s.name, "\n")] = '\0';

    printf("Enter Branch : ");
    fgets(s.branch, sizeof(s.branch), stdin);
    s.branch[strcspn(s.branch, "\n")] = '\0';

    do
    {
        printf("Enter Year (1-4) : ");
        scanf("%d", &s.year);

        if(s.year < 1 || s.year > 4)
            printf("Invalid Year! Please enter between 1 and 4.\n");

    }while(s.year < 1 || s.year > 4);

    assignFees(&s);

    printf("\nScholarship Available?\n");
    printf("1. Yes\n");
    printf("0. No\n");
    printf("Enter Choice : ");
    scanf("%d", &s.scholarship);

    if(s.scholarship == 1)
    {
        printf("Enter Scholarship Amount : ");
        scanf("%f", &s.scholarshipAmount);
    }
    else
    {
        s.scholarshipAmount = 0;
    }

    printf("Enter Fee Paid : ");
    scanf("%f", &s.feePaid);

    calculateFees(&s);

    students[studentCount++] = s;

    saveStudents();

    printf("\nStudent Added Successfully.\n");
}


/*==============================================================
                    DISPLAY ALL STUDENTS
==============================================================*/

void displayStudents(void)
{
    if(studentCount == 0)
    {
        printf("\nNo Student Records Found.\n");
        return;
    }

    printf("\n=============================================================================================================================================================================\n");

    printf("%-5s %-20s %-10s %-4s %-10s %-10s %-10s %-10s %-10s %-10s %-12s %-12s %-12s %-10s\n",
           "ID",
           "Name",
           "Branch",
           "Yr",
           "Tuition",
           "Hostel",
           "Mess",
           "Exam",
           "Total",
           "Scholar",
           "Sch.Amount",
           "Fee Paid",
           "Pending",
           "Status");

    printf("=============================================================================================================================================================================\n");

    for(int i = 0; i < studentCount; i++)
    {
        printf("%-5s %-20s %-10s %-4d %-10.2f %-10.2f %-10.2f %-10.2f %-10.2f %-10s %-12.2f %-12.2f %-12.2f %-10s\n",

               students[i].id,
               students[i].name,
               students[i].branch,
               students[i].year,

               students[i].tuitionFee,
               students[i].hostelFee,
               students[i].messFee,
               students[i].examFee,

               students[i].totalFee,

               students[i].scholarship ? "Yes" : "No",
               students[i].scholarshipAmount,

               students[i].feePaid,
               students[i].pendingFee,

               students[i].pendingFee > 0 ? "Pending" : "Paid");
    }

    printf("=============================================================================================================================================================================\n");

    printf("\nTotal Students : %d\n", studentCount);
}
/*==============================================================
                    SEARCH STUDENT BY ID
==============================================================*/

void searchByID(void)
{
    char id[25];
    int found = 0;

    printf("\n=========== SEARCH STUDENT BY ID ===========\n");
    printf("Enter Student ID : ");
    scanf("%24s", id);

    for(int i = 0; i < studentCount; i++)
    {
        if(strcmp(students[i].id, id) == 0)
        {
            found = 1;

            printf("\nStudent Found Successfully\n");
            printf("=========================================\n");
            printf("Student ID          : %s\n", students[i].id);
            printf("Student Name        : %s\n", students[i].name);
            printf("Branch              : %s\n", students[i].branch);
            printf("Year                : %d\n", students[i].year);

            printf("\n----------- Fee Details -----------\n");
            printf("Tuition Fee         : %.2f\n", students[i].tuitionFee);
            printf("Hostel Fee          : %.2f\n", students[i].hostelFee);
            printf("Mess Fee            : %.2f\n", students[i].messFee);
            printf("Exam Fee            : %.2f\n", students[i].examFee);

            printf("-----------------------------------\n");
            printf("Total Fee           : %.2f\n", students[i].totalFee);

            printf("Scholarship         : %s\n",
                    students[i].scholarship ? "Yes" : "No");

            printf("Scholarship Amount  : %.2f\n",
                    students[i].scholarshipAmount);

            printf("Fee Paid            : %.2f\n",
                    students[i].feePaid);

            printf("Pending Fee         : %.2f\n",
                    students[i].pendingFee);

            printf("=========================================\n");

            return;
        }
    }

    if(!found)
        printf("\nStudent ID Not Found.\n");
}


/*==============================================================
                  SEARCH STUDENT BY NAME
==============================================================*/

void searchByName(void)
{
    char name[50];
    int found = 0;

    getchar();

    printf("\n=========== SEARCH STUDENT BY NAME ===========\n");
    printf("Enter Student Name : ");

    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';

    printf("\n");

    for(int i = 0; i < studentCount; i++)
    {
        if(strcmp(students[i].name, name) == 0)
        {
            found = 1;

            printf("=========================================\n");
            printf("Student ID          : %s\n", students[i].id);
            printf("Student Name        : %s\n", students[i].name);
            printf("Branch              : %s\n", students[i].branch);
            printf("Year                : %d\n", students[i].year);

            printf("\n----------- Fee Details -----------\n");
            printf("Tuition Fee         : %.2f\n", students[i].tuitionFee);
            printf("Hostel Fee          : %.2f\n", students[i].hostelFee);
            printf("Mess Fee            : %.2f\n", students[i].messFee);
            printf("Exam Fee            : %.2f\n", students[i].examFee);

            printf("-----------------------------------\n");
            printf("Total Fee           : %.2f\n",
                    students[i].totalFee);

            printf("Scholarship         : %s\n",
                    students[i].scholarship ? "Yes" : "No");

            printf("Scholarship Amount  : %.2f\n",
                    students[i].scholarshipAmount);

            printf("Fee Paid            : %.2f\n",
                    students[i].feePaid);

            printf("Pending Fee         : %.2f\n",
                    students[i].pendingFee);

            printf("=========================================\n\n");
        }
    }

    if(!found)
        printf("Student Name Not Found.\n");
}
/*==============================================================
                    UPDATE STUDENT
==============================================================*/

void updateStudent(void)
{
    char id[25];
    int choice, found = 0;

    printf("\n=========== UPDATE STUDENT ===========\n");
    printf("Enter Student ID : ");
    scanf("%24s", id);

    for(int i = 0; i < studentCount; i++)
    {
        if(strcmp(students[i].id, id) == 0)
        {
            found = 1;

            do
            {
                printf("\n=========== UPDATE MENU ===========\n");
                printf("1. Update Name\n");
                printf("2. Update Branch\n");
                printf("3. Update Year\n");
                printf("4. Update Scholarship\n");
                printf("5. Update Fee Paid\n");
                printf("6. Back\n");
                printf("Enter Choice : ");

                scanf("%d", &choice);
                getchar();

                switch(choice)
                {
                    case 1:
                        printf("Enter New Name : ");
                        fgets(students[i].name,
                              sizeof(students[i].name),
                              stdin);

                        students[i].name[strcspn(
                            students[i].name,"\n")] = '\0';
                        break;

                    case 2:
                        printf("Enter New Branch : ");
                        fgets(students[i].branch,
                              sizeof(students[i].branch),
                              stdin);

                        students[i].branch[strcspn(
                            students[i].branch,"\n")] = '\0';
                        break;

                    case 3:
                        do
                        {
                            printf("Enter New Year (1-4): ");
                            scanf("%d",&students[i].year);

                            if(students[i].year < 1 ||
                               students[i].year > 4)
                            {
                                printf("Invalid Year!\n");
                            }

                        }while(students[i].year < 1 ||
                               students[i].year > 4);

                        assignFees(&students[i]);
                        calculateFees(&students[i]);
                        break;

                    case 4:

                        do
                        {
                            printf("Scholarship (1-Yes / 0-No): ");
                            scanf("%d",
                                  &students[i].scholarship);

                            if(students[i].scholarship != 0 &&
                               students[i].scholarship != 1)
                            {
                                printf("Invalid Choice!\n");
                            }

                        }while(students[i].scholarship != 0 &&
                               students[i].scholarship != 1);

                        if(students[i].scholarship == 1)
                        {
                            printf("Enter Scholarship Amount : ");
                            scanf("%f",
                                  &students[i].scholarshipAmount);
                        }
                        else
                        {
                            students[i].scholarshipAmount = 0;
                        }

                        calculateFees(&students[i]);
                        break;

                    case 5:

                        printf("Enter Total Fee Paid : ");
                        scanf("%f",&students[i].feePaid);

                        calculateFees(&students[i]);
                        break;

                    case 6:
                        printf("\nReturning to Main Menu...\n");
                        break;

                    default:
                        printf("\nInvalid Choice!\n");
                }

            }while(choice != 6);

            saveStudents();

            printf("\nRecord Updated Successfully.\n");
            return;
        }
    }

    if(!found)
    {
        printf("\nStudent ID Not Found.\n");
    }
}

/*==============================================================
                    DELETE STUDENT
==============================================================*/

void deleteStudent(void)
{
    char id[25];
    int index = -1;
    char ch;

    printf("\n=========== DELETE STUDENT ===========\n");
    printf("Enter Student ID : ");
    scanf("%24s", id);

    /* Search Student */
    for(int i = 0; i < studentCount; i++)
    {
        if(strcmp(students[i].id, id) == 0)
        {
            index = i;
            break;
        }
    }

    if(index == -1)
    {
        printf("\nStudent ID Not Found.\n");
        return;
    }

    printf("\nStudent Found:\n");
    printf("ID     : %s\n", students[index].id);
    printf("Name   : %s\n", students[index].name);
    printf("Branch : %s\n", students[index].branch);

    printf("\nAre you sure you want to delete this record? (Y/N): ");
    scanf(" %c", &ch);

    if(ch == 'Y' || ch == 'y')
    {
        for(int i = index; i < studentCount - 1; i++)
        {
            students[i] = students[i + 1];
        }

        studentCount--;

        saveStudents();

        printf("\nRecord Deleted Successfully.\n");
    }
    else
    {
        printf("\nDeletion Cancelled.\n");
    }
}
/*==============================================================
            DISPLAY PENDING FEE STUDENTS
==============================================================*/

void displayPendingStudents(void)
{
    int found = 0;

    printf("\n================ PENDING FEE STUDENTS ================\n");

    printf("%-5s %-20s %-10s %-12s %-12s\n",
           "ID","Name","Branch","Fee Paid","Pending");

    printf("--------------------------------------------------------------\n");

    for(int i=0;i<studentCount;i++)
    {
        if(students[i].pendingFee > 0)
        {
            found = 1;

            printf("%-5s %-20s %-10s %-12.2f %-12.2f\n",
                   students[i].id,
                   students[i].name,
                   students[i].branch,
                   students[i].feePaid,
                   students[i].pendingFee);
        }
    }

    if(!found)
        printf("No Pending Fee Students.\n");
}


/*==============================================================
            DISPLAY SCHOLARSHIP STUDENTS
==============================================================*/

void displayScholarshipStudents(void)
{
    int found = 0;

    printf("\n================ SCHOLARSHIP STUDENTS ================\n");

    printf("%-5s %-20s %-10s %-15s %-12s\n",
           "ID","Name","Branch","Scholarship","Pending");

    printf("-----------------------------------------------------------------\n");

    for(int i=0;i<studentCount;i++)
    {
        if(students[i].scholarship)
        {
            found = 1;

            printf("%-5s %-20s %-10s %-15.2f %-12.2f\n",
                   students[i].id,
                   students[i].name,
                   students[i].branch,
                   students[i].scholarshipAmount,
                   students[i].pendingFee);
        }
    }

    if(!found)
        printf("No Scholarship Students Found.\n");
}


/*==============================================================
        DISPLAY NON-SCHOLARSHIP STUDENTS
==============================================================*/

void displayNonScholarshipStudents(void)
{
    int found = 0;

    printf("\n============= NON-SCHOLARSHIP STUDENTS =============\n");

    printf("%-5s %-20s %-10s %-12s %-12s\n",
           "ID","Name","Branch","Fee Paid","Pending");

    printf("-------------------------------------------------------------\n");

    for(int i=0;i<studentCount;i++)
    {
        if(!students[i].scholarship)
        {
            found = 1;

            printf("%-5s %-20s %-10s %-12.2f %-12.2f\n",
                   students[i].id,
                   students[i].name,
                   students[i].branch,
                   students[i].feePaid,
                   students[i].pendingFee);
        }
    }

    if(!found)
        printf("No Non-Scholarship Students Found.\n");
}
/*==============================================================
                qsort() COMPARISON FUNCTIONS
==============================================================*/

int comparePendingFeeDesc(const void *a, const void *b)
{
    Student *s1 = (Student *)a;
    Student *s2 = (Student *)b;

    if(s1->pendingFee < s2->pendingFee)
        return 1;
    else if(s1->pendingFee > s2->pendingFee)
        return -1;
    else
        return 0;
}

int compareNameAsc(const void *a, const void *b)
{
    Student *s1 = (Student *)a;
    Student *s2 = (Student *)b;

    return strcmp(s1->name, s2->name);
}


/*==============================================================
            SORT BY PENDING FEE (DESCENDING)
==============================================================*/

void sortByPendingFee(void)
{
    if(studentCount == 0)
    {
        printf("\nNo Records Found.\n");
        return;
    }

    qsort(students,
          studentCount,
          sizeof(Student),
          comparePendingFeeDesc);

    printf("\nRecords Sorted by Pending Fee (Descending).\n");

    displayStudents();
}


/*==============================================================
            SORT BY STUDENT NAME (ASCENDING)
==============================================================*/

void sortByStudentName(void)
{
    if(studentCount == 0)
    {
        printf("\nNo Records Found.\n");
        return;
    }

    qsort(students,
          studentCount,
          sizeof(Student),
          compareNameAsc);

    printf("\nRecords Sorted by Student Name (Ascending).\n");

    displayStudents();
}