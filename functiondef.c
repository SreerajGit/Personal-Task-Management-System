#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include "functionproto.h"





// function to validate task name
int tasknameValidator(char *task)
{
    int val = 1;

    for (int i=0; (*(task+i))!='\0';i++)
    {
        if (isspace(*(task+i)) > 0)
            continue;
        if (isalnum(*(task+i)) == 0)
        {
            val = 0;
            break;
        }
    }

    if (val==1)
        return 1;
    else
        return 0;
}




//Function to convert uppercase letter to lowercase
char toLower(char chr_to_convert)
{
    char converted_chr;

    if ((int)chr_to_convert >= 65 && (int)chr_to_convert <= 90)
            converted_chr = chr_to_convert + 32;
    else
            converted_chr = chr_to_convert;

    return converted_chr;
}




//Function to compare two dates
int compareDates(char date1[],char date2[])
{
    Date d1 = {0,0,0}, d2 = {0,0,0};
    int date1_len, date2_len, cnt=0, cmp=0;
    date1_len = strlen(date1);
    date2_len = strlen(date2);

    for (int i=0; i<date1_len;i++)
    {
        if (date1[i]=='/')
        {
            cnt++;
            continue;
        }
        if (cnt==0)
        {
            d1.day *= 10;
            d1.day += (date1[i] - '0');
        }
        if (cnt==1)
        {
            d1.month *= 10;
            d1.month += (date1[i] - '0');
        }
        if (cnt==2)
        {
            d1.year *= 10;
            d1.year += (date1[i] - '0');
        }

    }

    cnt=0;

    for (int j=0; j<date2_len;j++)
    {
        if (date2[j]=='/')
        {
            cnt++;
            continue;
        }
        if (cnt==0)
        {
            d2.day *= 10;
            d2.day += (date2[j] - '0');
        }
        if (cnt==1)
        {
            d2.month *= 10;
            d2.month += (date2[j] - '0');
        }
        if (cnt==2)
        {
            d2.year *= 10;
            d2.year += (date2[j] - '0');
        }

    }

    if (d1.year != d2.year)
    {
        if (d1.year > d2.year)
            cmp = 1;
        else
            cmp = -1;
    } else if (d1.month != d2.month)
    {
        if (d1.month > d2.month)
            cmp = 1;
        else
            cmp = -1;

    } else if (d1.day != d2.day)
    {
        if (d1.day > d2.day)
            cmp = 1;
        else
            cmp = -1;

    }

    return cmp;
}








//Function to find the number of lines in a given file
int getNumOfLines (char file_name[])
{
    FILE *fh1;
    fh1 = fopen(file_name,"r");
    int line_cnt = 0;
    char x;
    if (fh1 != NULL)
    {
        while (!feof(fh1))
        {
            x = fgetc(fh1);
            if (x == '\n')
                line_cnt++;


        }
        fclose(fh1);
    } else
    {
        fclose(fh1);
        return -1;
    }

    return line_cnt;

}



//dd/mm/yyyy

//function to validate date
int dateValidator(char *date_input)
{
    Date dt;
    time_t now;
    time(&now);
    struct tm *local = localtime(&now);
    dt.day = local->tm_mday;
    dt.month = local->tm_mon + 1;
    dt.year = local->tm_year + 1900;
    char curdate[20];
    int chr_cnt = 0, digit_cnt = 0;
    strftime(curdate, sizeof(curdate)-1, "%d/%m/%Y", local);
    for (int i=0; *(date_input+i)!='\0';i++)
    {
        if (isdigit(*(date_input+i)))
            digit_cnt++;

        if (*(date_input+i)=='/')
            chr_cnt++;

    }

    if (chr_cnt == 2 && digit_cnt == 8 && compareDates(date_input,curdate)>=0)
        return 1;
    else
        return 0;
}




//function to verify the uniqueness of username
int checkUserName(char usname[])
{
    FILE *fh;
    fh = fopen("users.txt","r");
    User user;
    int lines = getNumOfLines("users.txt"), match = 0;
    if (fh != NULL && lines > 0)
    {
        while (!feof(fh))
        {
            fscanf(fh,"%s%s",user.username,user.password);
            if (strcmp(user.username, usname)== 0)
            {
                match = 1;
                break;
            }
        }
        fclose(fh);

        if (match==1)
            return 1;

    } else
    {
        fclose(fh);
        if (lines == 0)
            return 0;
        else
            printf("\nSomething went wrong\n");

    }
}




//function to get the length of the longest string from the file
int longestString(char filename[])
{
    FILE *fh;
    fh = fopen(filename,"r");
    int longest = 0, length = 0;
    char temp;
    if (fh!=NULL)
    {
        while (!feof(fh))
        {
            temp = fgetc(fh);
            if (temp == '\n')
            {
                if (length > longest)
                    longest = length;
                length = 0;
            }else
                length++;
        }
    } else
    {
        fclose(fh);
        return -1;
    }

    fclose(fh);
    return longest;

}




//function to validate password
int passwordChecker(char pwd[])
{
    int pwdlen = strlen(pwd);

    if (pwdlen < 8)
    {
        printf("Password should contain at least 8 characters!\n");
        return 0;
    } else
        return 1;
};





//function to authenticate users
int loginPage(void)
{
    system("cls");
    printf("###### Login Page ######\n");
    FILE *f5;
    User user, data_from_file;
    int match = 0, access = 1;
    char *file;
    if (getNumOfLines("users.txt") < 1)
        access = 0;
    else
        f5 = fopen("users.txt","r");
    if (access==1)
    {
        printf("Enter username: ");
        scanf("%s",user.username);
        printf("Enter password: ");
        scanf("%s", user.password);

        while (!feof(f5))
        {
            fscanf(f5,"%s%s",data_from_file.username, data_from_file.password);
            if (strcmp(data_from_file.username,user.username) == 0)
            {
                if (strcmp(data_from_file.password, user.password) == 0)
                {
                    match = 1;
                    break;
                }
            }
        }
        if (match==1)
        {
            printf("\nAcccess Granted\n");
            system("pause");
            file = (char*)(malloc(sizeof(char) * (strlen(user.username) + 1)));
            strcpy(file,user.username);
            strcat(file,".txt");
            if (dashboard(file) == 1)
            {
                free(file);
                return 1;
            }

            else
            {
                free(file);
                printf("\nSomething Went Wrong\n");
            }

        } else
        {
            printf("\nInvalid Credentials!\n");
            system("pause");
            return 0;
        }


    } else
    {
        printf("Enter username: ");
        scanf("%s",user.username);
        printf("Enter password: ");
        scanf("%s", user.password);
        printf("\nInvalid Credentials!\n");
        system("pause");
        return 0;
    }

    fclose(f5);
}




//function to allow users to create new account
int createAccount(void)
{
    system("cls");
    FILE *f1, *f2;
    User new_user;
    int sent = 1;
    char *newfile_name;
    if (getNumOfLines("users.txt")>0)
        f1 = fopen("users.txt","a");
    else
        f1 = fopen("users.txt","w");

    if (f1 != NULL)
    {
        while (sent==1)
        {
            printf("Enter username: ");
            fflush(stdin);
            scanf("%s",new_user.username);
            if (checkUserName(new_user.username))
                printf("Username already exists!\n");
            else
                sent = 0;

        }
        sent = 1;
        while (sent==1)
        {
            printf("Enter password: ");
            fflush(stdin);
            scanf("%s",new_user.password);
            if (passwordChecker(new_user.password))
                sent = 0;
        }
        fprintf(f1,"%s %s\n",new_user.username,new_user.password);
        fclose(f1);
        newfile_name = (char*)(malloc(sizeof(char) * (strlen(new_user.username) + 1)));
        strcpy(newfile_name,new_user.username);
        strcat(newfile_name,".txt");
        f2 = fopen(newfile_name,"w");
        fclose(f2);
        printf("\nAccount Has Been Successfully Created!\n");
        system("pause");
        free(newfile_name);
        return 1;
    } else
        return 0;

}




//function to print welcome page of the program
void userInterface(void)
{
    printf("\t~~~~~~~~~~~~~~~~~~~~~"
           "~~~~~~~~~~~~~~~~~~~~~~~~"
           "~~~~~~~~~~~~~~~~~~~~~~~~"
           "~~~~~~~~~~~~~~~~~~~~~~~"
           "~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("\t~~~~~~~~~~~~~~~~~~~~~~"
           "~~~~~~~~~~~~~~~~~~~~~~~"
           "~~~~~~~~~~~~~~~~~~~~~~~"
           "~~~~~~~~~~~~~~~~~~~~~~~~"
           "~~~~~~~~~~~~~~~~~~~~~~\n\n");
    printf("\t) : ) : ) : ) : ) : ) "
           ": ) : ) : ) :   "
           "WELCOME TO YOUR TASK MANAGEMENT SYSTEM "
           "  : ( : ( : ( : ( : ( "
           ": ( : ( : ( : (\n\n");
    printf("\t~~~~~~~~~~~~~~~~~~~~~"
           "~~~~~~~~~~~~~~~~~~~~~~~~"
           "~~~~~~~~~~~~~~~~~~~~~~~~~"
           "~~~~~~~~~~~~~~~~~~~~~~"
           "~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("\t~~~~~~~~~~~~~~~~~~~~~~"
           "~~~~~~~~~~~~~~~~~~~~~~~"
           "~~~~~~~~~~~~~~~~~~~~~~~"
           "~~~~~~~~~~~~~~~~~~~~~~~~"
           "~~~~~~~~~~~~~~~~~~~~~~");
    printf("\n\n\t\t\t\t\t\t\t"
           "\t\t\t\t\t        "
           "@SreerajNagarajan\n\n\n\n"
           "\n\n\n");

}




//function to prompt users with dashboard
int dashboard(char filenm[])
{

    int user_option, cont=1, rep = 1, line_num, prs;
    char inp;
    while (rep)
    {
        system("cls");
        prs = 1;
        line_num = getNumOfLines(filenm);
        Task tasks[line_num];
        if (line_num > 0)
            getTasks(tasks, filenm);
        else
            prs = 0;
        user_option = NULL;
        printf("####### Dashboard #######\n"
               "Select An Option\n"
               "(1)Add Task\n"
               "(2)View Task\n"
               "(3)Update Task\n"
               "(4)Delete Task\n"
               "(5)Exit Program\n"
               "Enter option: ");
        fflush(stdin);
        scanf("%d",&user_option);
        switch(user_option)
        {
            case 1:
                do
                {
                    if (addTask(filenm))
                    {
                        while (1)
                        {
                            printf("\nDo you want to add more tasks? "
                                   "Press 'y' for Yes and 'n' for No\n");
                            fflush(stdin);
                            scanf("%c",&inp);
                            if (toLower(inp) == 'y')
                                break;

                            else if (toLower(inp) == 'n')
                            {
                                cont = 0;
                                break;
                            }
                            else
                                printf("Invalid Input!\n");
                        }
                        system("pause");
                    } else
                    {
                        printf("Something Went Wrong\n");
                        cont = 0;
                    }
                }while (cont);

                break;
            case 2:
                if (prs == 0)
                {
                    printf("\n\nNo tasks to display\n\n");
                    system("pause");
                }

                else
                {
                    if (viewTask(tasks,line_num) == 0)
                        printf("Something went wrong\n");
                }

                break;
            case 3:
                if (prs == 0)
                {
                   printf("\n\nNo tasks available to update\n\n");
                   system("pause");
                }

                else
                {
                    if (updateTask(tasks,line_num,filenm) == 0)
                        printf("Something went wrong\n");
                }
                break;
            case 4:
                if (prs == 0)
                {
                    printf("\n\nNo tasks available to delete\n\n");
                    system("pause");
                }
                else
                {
                    if (deleteTask(tasks,line_num,filenm) == 0)
                        printf("Something went wrong\n");
                }
                break;
            case 5:
                printf("\n");
                system("pause");
                rep = 0;
                break;
            default:
                printf("\nInvalid Option!\n");
                system("pause");

        }

    }
    return 1;

}



//function to get tasks from file and add into array
void getTasks(Task *task, char filename[])
{
    FILE *fhr;
    int size = longestString(filename) + 2;
    char data[size];
    int task_num, task_loc = 0,delimeter_cnt = 0, taskname_loc = 0, taskdate_loc = 0, taskcategory_loc = 0, taskstatus_loc = 0, line_num;
    line_num = getNumOfLines(filename);
    fhr = fopen(filename,"r");
    if (line_num > 0)
    {
        for(int k=0;k<line_num;k++)
        {
            fgets(data,size,fhr);
            delimeter_cnt = 0;
            taskname_loc = 0;
            taskdate_loc = 0;
            taskcategory_loc = 0;
            taskstatus_loc = 0;
            (*(task+task_loc)).task_number = 0;
            for (int i=0;data[i]!='\n';i++)
            {

                if (data[i] == '|')
                {
                     delimeter_cnt++;
                     continue;
                }

                if (delimeter_cnt == 0)
                {
                    (*(task+task_loc)).task_number *= 10;
                    (*(task+task_loc)).task_number += (data[i] - '0');
                }
                if (delimeter_cnt == 1)
                {
                    (*(task+task_loc)).task_name[taskname_loc] = data[i];
                    (*(task+task_loc)).task_name[taskname_loc+1] = '\0';
                    taskname_loc++;
                }

                if (delimeter_cnt == 2)
                {
                    (*(task+task_loc)).task_category[taskcategory_loc] = data[i];
                    (*(task+task_loc)).task_category[taskcategory_loc+1] = '\0';
                    taskcategory_loc++;

                }

                if (delimeter_cnt == 3)
                {
                    (*(task+task_loc)).task_duedate[taskdate_loc] = data[i];
                    (*(task+task_loc)).task_duedate[taskdate_loc+1] = '\0';
                    taskdate_loc++;

                }

                if (delimeter_cnt == 4)
                {
                    (*(task+task_loc)).task_status[taskstatus_loc] = data[i];
                    (*(task+task_loc)).task_status[taskstatus_loc+1] = '\0';
                    taskstatus_loc++;

                }

            }

            task_loc++;

        }

    }else
        return 0;
}



//function for category selection
int selectCategory(void)
{
    int category;
    printf("\nSelect A Category\n"
           "(1)Work\n"
           "(2)Personal\n"
           "(3)Household\n"
           "(4)Other\n"
           "Enter option: ");
    fflush(stdin);
    scanf("%d",&category);
    return category;

}


//function to add task
int addTask(char filename[])
{
    system("cls");
    FILE *fh3;
    Task t1;
    int ctg, val = 1,line_num;
    line_num = getNumOfLines(filename);
    if (line_num>0)
        fh3 = fopen(filename,"a");
    else
        fh3 = fopen(filename,"w");

    if (fh3 != NULL)
    {
       printf("--Enter Task Details--\n\n");
       t1.task_number = line_num+1;
       while (1)
       {
           printf("Enter Task Name: ");
           fflush(stdin);
           scanf("%[^\n]s",t1.task_name);
           if (tasknameValidator(t1.task_name))
                break;
           else
                printf("Task Name should contain only alphabets and numbers!\n");
       }

       while (val == 1)
       {
           ctg = selectCategory();
           switch (ctg)
           {
               case 1:
                   strcpy(t1.task_category,"Work");
                   val = 0;
                   break;
               case 2:
                   strcpy(t1.task_category,"Personal");
                   val = 0;
                   break;
               case 3:
                   strcpy(t1.task_category,"Household");
                   val = 0;
                   break;
               case 4:
                   strcpy(t1.task_category,"Other");
                   val = 0;
                   break;
               default:
                   printf("Invalid Option!\n");

           }

        }

        while (1)
        {
            printf("Enter Task Due Date (DD/MM/YYYY): ");
            fflush(stdin);
            scanf("%s",t1.task_duedate);
            if (dateValidator(t1.task_duedate))
                break;
            else
                printf("Invalid Date!\n");

        }


        while (1)
        {
            printf("Enter Task Status (Done/Not Done): ");
            fflush(stdin);
            scanf("%[^\n]s",t1.task_status);
            if (strcmp(t1.task_status,"Done") == 0 || strcmp(t1.task_status,"Not Done") == 0)
                break;
            else
                printf("Invalid Input!\n");
        }


        fprintf(fh3,"%d|%s|%s|%s|%s\n",t1.task_number,t1.task_name,t1.task_category,t1.task_duedate,t1.task_status);
        printf("\nTask has been added successfully");
        fclose(fh3);

        return 1;
       } else
            return 0;

    }

//function to delete task
int deleteTask(Task task[], int line_num, char filename[])
{
    system("cls");
    FILE *fhw;
    fhw = fopen(filename,"w");
    int found = 0, task_num;
    printf("Enter Task Number: ");
    fflush(stdin);
    scanf("%d",&task_num);
    if (fhw != NULL)
    {
        int newnum = 1;

        for (int j=0;j<line_num;j++)
        {
            if(task[j].task_number == task_num)
            {
                found = 1;
                continue;
            }

            else
            {
                fprintf(fhw,"%d|%s|%s|%s|%s\n",newnum,task[j].task_name,task[j].task_category,task[j].task_duedate,task[j].task_status);
                newnum++;
            }

        }

        fclose(fhw);
        if (found==1)
            printf("\nTask Has Been Deleted!\n\n");
        else
            printf("\nNo Tasks Found\n\n");
        system("pause");
        return 1;

    } else
        return 0;


    fclose(fhw);

}



//function to view task
int viewTask(Task tasks[], int line_nums)
{
    system("cls");
    int option, val = 1;
    while (val==1)
    {
        printf("Select An Option\n(1)View All Tasks\n(2)View Specific Task\n(3)Sort Tasks\n(4)Filter Tasks\nEnter option:");
        fflush(stdin);
        scanf("%d",&option);
        switch (option)
        {
            case 1:
                viewAllTasks(tasks,line_nums);
                val = 0;
                break;
            case 2:
                viewSpecificTask(tasks,line_nums);
                val = 0;
                break;
            case 3:
                sortTasks(tasks,line_nums);
                val = 0;
                break;
            case 4:
                filterTasks(tasks,line_nums);
                val = 0;
                break;
            default:
                printf("Invalid Option!\n");

        }

    }

    system("pause");
    return 1;
}




//function to view all tasks
void viewAllTasks(Task *task_lst,int size)
{
    for (int i=0;i<size;i++)
    {
        printf("\nTask Number: %d\n"
               "Task Name: %s\n"
               "Task Category: %s\n"
               "Task Due Date: %s\n"
               "Task Status: %s\n\n",
               task_lst[i].task_number,
               task_lst[i].task_name,
               task_lst[i].task_category,
               task_lst[i].task_duedate,
               task_lst[i].task_status);
    }
}




//function to display specific task
void viewSpecificTask(Task task_lst[], int size)
{
    system("cls");
    int task_num, found = 0;
    printf("Enter Task Number: ");
    fflush(stdin);
    scanf("%d",&task_num);
    for (int i=0; i<size; i++)
    {
      if (((task_lst+i) -> task_number) == task_num)
      {
        found = 1;
        printf("\nTask Number: %d\n"
               "Task Name: %s\n"
               "Task Category: %s\n"
               "Task Due Date: %s\n"
               "Task Status: %s\n\n",
               task_lst[i].task_number,
               task_lst[i].task_name,
               task_lst[i].task_category,
               task_lst[i].task_duedate,
               task_lst[i].task_status);
        break;
      }

    }
    if (!found)
        printf("\nTask Not Found!\n");

}


//function to sort tasks
void sortTasks(Task task_list[],int size)
{
    int opt, val = 1, swapped = 1;
    Task temp;
    while (val==1)
    {
        printf("\nSelect An Option\n"
               "(1)Sort in Ascending Order by Category\n"
               "(2)Sort in Descending Order by Category\n"
               "(3)Sort in Ascending Order by Due Date\n"
               "(4)Sort in Descending Order by Due Date\nEnter option: ");
        fflush(stdin);
        scanf("%d",&opt);
        switch (opt)
        {
            case 1:

                while (1)
                {
                    swapped = 1;
                    for (int i=0;i<size-1;i++)
                    {
                        if (strcmp(task_list[i].task_category,task_list[i+1].task_category) > 0)
                        {
                            swapped = 0;
                            temp = task_list[i];
                            task_list[i] = task_list[i+1];
                            task_list[i+1] = temp;

                        }

                    }
                    if (swapped)
                        break;

                }


                val = 0;

                break;
            case 2:

                while (1)
                {
                    swapped = 1;
                    for (int i=0;i<size-1;i++)
                    {
                        if (strcmp(task_list[i].task_category,task_list[i+1].task_category) < 0)
                        {
                            swapped = 0;
                            temp = task_list[i];
                            task_list[i] = task_list[i+1];
                            task_list[i+1] = temp;

                        }

                    }
                    if (swapped)
                        break;

                }
                val = 0;
                break;

            case 3:
                while (1)
                {
                    swapped = 1;
                    for (int i=0;i<size-1;i++)
                    {
                        if (compareDates(task_list[i].task_duedate,task_list[i+1].task_duedate) > 0)
                        {
                            swapped = 0;
                            temp = task_list[i];
                            task_list[i] = task_list[i+1];
                            task_list[i+1] = temp;

                        }

                    }
                    if (swapped)
                        break;
                }
                val = 0;
                break;
            case 4:
                while (1)
                {
                    swapped = 1;
                    for (int i=0;i<size-1;i++)
                    {
                        if (compareDates(task_list[i].task_duedate,task_list[i+1].task_duedate) < 0)
                        {
                            swapped = 0;
                            temp = task_list[i];
                            task_list[i] = task_list[i+1];
                            task_list[i+1] = temp;

                        }

                    }
                    if (swapped)
                        break;
                }
                val = 0;
                break;

            default:
                printf("Invalid Option!");
        }



    }
    printf("\n");
    for (int j=0;j<size;j++)
    {
        printf("Task Number: %d\n"
               "Task Name: %s\n"
               "Task Category: %s\n"
               "Task Due Date: %s\n"
               "Task Status: %s\n\n",
               task_list[j].task_number,
               task_list[j].task_name,
               task_list[j].task_category,
               task_list[j].task_duedate,
               task_list[j].task_status);

    }


}

//function to update task
int updateTask(Task tasks_lst[],int line_num, char file_name[])
{
    system("cls");
    FILE *fhw;
    fhw = fopen(file_name,"w");
    int found = 0, task_num;
    printf("Enter Task Number: ");
    fflush(stdin);
    scanf("%d",&task_num);
    if (fhw != NULL)
    {
        char option;

        for (int j=0;j<line_num;j++)
        {
            if (tasks_lst[j].task_number == task_num)
            {
                found = 1;
                while (1)
                {
                    printf("\nDo you want to edit Task Name? Press 'y' for Yes and 'n' for No\n");
                    fflush(stdin);
                    scanf("%c",&option);
                    if (toLower(option) == 'y')
                    {
                        while (1)
                        {
                            printf("Enter Task Name: ");
                            fflush(stdin);
                            scanf("%[^\n]s",tasks_lst[j].task_name);
                            if (tasknameValidator(tasks_lst[j].task_name))
                                break;
                            else
                                printf("Task Name should contain only alphabets and numbers!\n");
                        }

                        break;
                    }
                    else if (tolower(option) == 'n')
                        break;
                    else
                        printf("\nInvalid Input!");

                }
                while (1)
                {
                    int catg,vald = 1;
                    printf("\nDo you want to edit Task Category? Press 'y' for Yes and 'n' for No\n");
                    fflush(stdin);
                    scanf("%c",&option);
                    if (toLower(option) == 'y')
                    {
                       while (vald)
                       {
                           catg = selectCategory();
                           switch (catg)
                           {
                               case 1:
                                   strcpy(tasks_lst[j].task_category,"Work");
                                   vald = 0;
                                   break;
                               case 2:
                                   strcpy(tasks_lst[j].task_category,"Personal");
                                   vald = 0;
                                   break;
                               case 3:
                                   strcpy(tasks_lst[j].task_category,"Household");
                                   vald = 0;
                                   break;
                               case 4:
                                   strcpy(tasks_lst[j].task_category,"Other");
                                   vald = 0;
                                   break;
                               default:
                                   printf("Invalid Option!\n");

                           }

                       }


                       break;

                    }
                    else if (tolower(option) == 'n')
                        break;
                    else
                        printf("\nInvalid Input!");
                }
                while (1)
                {
                    printf("\nDo you want to edit Task Due Date? Press 'y' for Yes and 'n' for No\n");
                    fflush(stdin);
                    scanf("%c",&option);
                    if (toLower(option) == 'y')
                    {
                        while (1)
                        {
                           printf("Enter Task Due Date: ");
                           fflush(stdin);
                           scanf("%[^\n]s",tasks_lst[j].task_duedate);
                           if (dateValidator(tasks_lst[j].task_duedate) == 1)
                              break;
                           else
                              printf("Invalid Date!\n");
                        }


                        break;
                    }
                    else if (tolower(option) == 'n')
                        break;
                    else
                        printf("\nInvalid Input!");
                }
                while (1)
                {
                    printf("\nDo you want to edit Task Status? Press 'y' for Yes and 'n' for No\n");
                    fflush(stdin);
                    scanf("%c",&option);
                    if (toLower(option) == 'y')
                    {
                        while (1)
                        {
                            printf("Enter \"Done\" or \"Not Done\": ");
                            fflush(stdin);
                            scanf("%[^\n]s",tasks_lst[j].task_status);
                            if (strcmp(tasks_lst[j].task_status,"Done")==0 || strcmp(tasks_lst[j].task_status,"Not Done")==0)
                                break;
                            else
                                printf("Invalid Input!\n");

                        }
                        break;
                    }
                    else if (tolower(option) == 'n')
                        break;
                    else
                        printf("\nInvalid Input!");
                }
            }

            fprintf(fhw,"%d|%s|%s|%s|%s\n",
                        tasks_lst[j].task_number,
                        tasks_lst[j].task_name,
                        tasks_lst[j].task_category,
                        tasks_lst[j].task_duedate,
                        tasks_lst[j].task_status);

        }

        fclose(fhw);
        if (found==1)
            printf("\nTask Has Been Updated!\n");
        else
            printf("\nTask Not Found!\n");
        system("pause");
        return 1;

    } else
        return 0;

}





//function to filter tasks

void filterTasks(Task tsklist[],int size)
{
    system("cls");
    int vld = 1, val = 1,opt,ctg,sts;
    char category[20], status[20];
    while (vld==1)
    {
        printf("Select An Option\n(1)Filter by Category\n(2)Filter by Status\nEnter Option: ");
        fflush(stdin);
        scanf("%d",&opt);
        printf("\n");
        switch(opt)
        {
            case 1:

                while (val)
                {
                    ctg = selectCategory();
                    switch (ctg)
                    {
                       case 1:
                           strcpy(category,"Work");
                           val = 0;
                           break;
                       case 2:
                           strcpy(category,"Personal");
                           val = 0;
                           break;
                       case 3:
                           strcpy(category,"Household");
                           val = 0;
                           break;
                       case 4:
                           strcpy(category,"Other");
                           val = 0;
                           break;
                       default:
                           printf("Invalid Option!\n");

                    }
                }
                for (int i=0; i<size; i++)
                {
                    if (strcmp((tsklist+i)->task_category,category) == 0)
                        {
                           printf("\nTask Number: %d\n"
                                   "Task Name: %s\n"
                                   "Task Category: %s\n"
                                   "Task Due Date: %s\n"
                                   "Task Status: %s\n\n",
                                   tsklist[i].task_number,
                                   tsklist[i].task_name,
                                   tsklist[i].task_category,
                                   tsklist[i].task_duedate,
                                   tsklist[i].task_status);

                        }
                }
                vld = 0;
                break;
            case 2:
                val = 1;
                while (val)
                {
                    printf("Select An Option\n(1)Done\n(2)Not Done\nEnter Option: ");
                    fflush(stdin);
                    scanf("%d",&sts);
                    switch(sts)
                    {
                        case 1:
                            strcpy(status,"Done");
                            val = 0;
                            break;
                        case 2:
                            strcpy(status,"Not Done");
                            val = 0;
                            break;
                        default:
                            printf("\nInvalid Option!\n\n");

                    }

                }

                for (int j=0; j<size; j++)
                {
                    if (strcmp((tsklist+j) -> task_status,status) == 0)
                        {
                           printf("\nTask Number: %d\n"
                                   "Task Name: %s\n"
                                   "Task Category: %s\n"
                                   "Task Due Date: %s\n"
                                   "Task Status: %s\n\n",
                                   tsklist[j].task_number,
                                   tsklist[j].task_name,
                                   tsklist[j].task_category,
                                   tsklist[j].task_duedate,
                                   tsklist[j].task_status);

                        }

                }
                vld = 0;
                break;
            default:
                printf("Invalid Option!\n\n");

        }
    }
}

