#ifndef HEADER_FILE
#define HEADER_FILE



typedef struct Date
{
    int day;
    int month;
    int year;
}Date;


typedef struct User
{
    char username[50];
    char password[50];
}User;


typedef struct Task
{
    int task_number;
    char task_name[100];
    char task_category[100];
    char task_duedate[20];
    char task_status[20];

}Task;


int compareDates(char[], char[]);
char toLower(char);
int getNumOfLines(char[]);
void userInterface(void);
int loginPage(void);
int createAccount(void);
int initialScreen(void);
int dashboard(char[]);
int checkUserName(char[]);
int passwordChecker(char[]);
int addTask(char[]);
int deleteTask(Task[], int, char[]);
int viewTask(Task[],int);
int updateTask(Task[],int,char[]);
int dateValidator(char*);
int selectCategory(void);
int longestString(char[]);
int tasknameValidator(char*);
void sortTasks(Task[],int);
void viewAllTasks(Task[],int);
void filterTasks(Task[],int);
void viewSpecificTask(Task[],int);
void getTasks(Task*, char[]);




#endif
