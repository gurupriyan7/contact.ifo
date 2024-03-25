// C program for student management system
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h> 

// int variable used to keep track of the number of students
int num = 0;

// data structure to store student info
struct sinfo
{
       char fname[50];
       char lname[50];
       int roll;
       float cgpa;
       char cname[10];
} st[55];

bool isRollNumberExists(int rollNumber)
{
       FILE *fp = fopen("StudentsDetails.txt", "r");
       if (fp == NULL)
       {
              printf("Error in file opening\n");
              return false; // Assume roll number doesn't exist if file cannot be opened
       }

       struct sinfo temp;
       while (fscanf(fp, "%s %s %d %f %s\n", temp.fname, temp.lname, &temp.roll, &temp.cgpa, temp.cname) == 5)
       {
              if (temp.roll == rollNumber)
              {
                     fclose(fp);
                     return true; // Roll number found
              }
       }

       fclose(fp);
       return false; // Roll number not found
}

// function used to add a student
void addstud()
{
       FILE *fp;
       fp = fopen("StudentsDetails.txt", "a");

       if (fp == NULL)
       {
              printf("Error in file opening\n");
       }
       else
       {
              printf("Enter the number of students to be entered: ");
              scanf("%d", &num);

              for (int i = 0; i < num; i++)
              {
                     printf("Add Student Details\n");
                     printf(".......................\n");
                     printf("Enter the First name of the Student: ");
                     scanf("%s", st[i].fname);
                     printf("Enter the Last name of the Student: ");
                     scanf("%s", st[i].lname);
                     int roll;
                     bool isRollDuplicate;
                     do
                     {
                            isRollDuplicate = false;
                            printf("Enter the Roll Number: ");
                            scanf("%d", &roll);

                            // Check if roll number already exists in the file
                            if (isRollNumberExists(roll))
                            {
                                   printf("Roll Number already exists in the file. Please enter a different one.\n");
                                   isRollDuplicate = true; // Set flag to indicate duplicate
                                   continue;
                            }

                            // Check if roll number already exists in the entered data
                            for (int j = 0; j < i; j++)
                            {
                                   if (st[j].roll == roll)
                                   {
                                          printf("Roll Number already exists in the entered data. Please enter a different one.\n");
                                          isRollDuplicate = true;
                                          break;
                                   }
                            }
                     } while (isRollDuplicate);

                     st[i].roll = roll; // Assign roll number if not duplicate
                     printf("Enter CGPA of the Student: ");
                     scanf("%f", &st[i].cgpa);
                     printf("Enter Course name: ");
                     scanf("%s", st[i].cname);
                     fprintf(fp, "%s %s %d %f %s\n", st[i].fname, st[i].lname, st[i].roll, st[i].cgpa, st[i].cname);
              }

              fclose(fp);
       }
}

// function to find the student using Roll Number
void find_rl()
{
       FILE *fp;
       fp = fopen("StudentsDetails.txt", "r");

       if (fp == NULL)
       {
              printf("Error in file opening\n");
       }
       else
       {
              for (int i = 0; i < num; i++)
              {
                     fscanf(fp, "%s %s %d %f %s\n", st[i].fname, st[i].lname, &st[i].roll, &st[i].cgpa, st[i].cname);
              }

              int x;
              printf("Enter the Roll Number of the student: ");
              scanf("%d", &x);

              int found = 0;

              for (int i = 0; i < num; i++)
              {
                     if (x == st[i].roll)
                     {
                            printf("Student Details\n");
                            printf("First name: %s\n", st[i].fname);
                            printf("Last name: %s\n", st[i].lname);
                            printf("Roll Number: %d\n", st[i].roll);
                            printf("CGPA: %f\n", st[i].cgpa);
                            printf("Course Name: %s\n", st[i].cname);
                            found = 1;
                     }
              }

              if (!found)
              {
                     printf("Student not found\n");
              }

              fclose(fp);
       }
}

// function to print the total number of students
void tot_s()
{
       printf("The total number of Students is %d\n", num);
       printf("You can have a maximum of 50 students\n");
       printf("You can have %d more students\n", 50 - num);
}

// function to delete a student's info using their roll number
void del_s()
{
       FILE *fp;
       fp = fopen("StudentsDetails.txt", "w");

       if (fp == NULL)
       {
              printf("Error in file opening\n");
       }
       else
       {
              int a;
              printf("Enter the Roll Number you want to delete: ");
              scanf("%d", &a);

              int found = 0;

              for (int i = 0; i < num; i++)
              {
                     if (a == st[i].roll)
                     {
                            for (int k = i; k < num - 1; k++)
                            {
                                   st[k] = st[k + 1];
                            }
                            num--;
                            found = 1;
                     }
              }

              if (!found)
              {
                     printf("Roll Number not found\n");
              }

              for (int i = 0; i < num; i++)
              {
                     fprintf(fp, "%s %s %d %f %s\n", st[i].fname, st[i].lname, st[i].roll, st[i].cgpa, st[i].cname);
              }

              fclose(fp);
       }
}

// function to update a student's data
void up_s()
{
       FILE *fp;
       fp = fopen("StudentsDetails.txt", "w");

       if (fp == NULL)
       {
              printf("Error in file opening\n");
       }
       else
       {
              printf("Enter the roll number to update the entry: ");
              int x;
              scanf("%d", &x);

              int found = 0;

              for (int i = 0; i < num; i++)
              {
                     if (st[i].roll == x)
                     {
                            printf("1. First name\n"
                                   "2. Last name\n"
                                   "3. Roll no.\n"
                                   "4. CGPA\n"
                                   "5. Course\n");

                            int z;
                            scanf("%d", &z);

                            switch (z)
                            {
                            case 1:
                                   printf("Enter the new first name: ");
                                   scanf("%s", st[i].fname);
                                   break;
                            case 2:
                                   printf("Enter the new last name: ");
                                   scanf("%s", st[i].lname);
                                   break;
                            case 3:
                                   printf("Enter the new roll number: ");
                                   scanf("%d", &st[i].roll);
                                   break;
                            case 4:
                                   printf("Enter the new CGPA: ");
                                   scanf("%f", &st[i].cgpa);
                                   break;
                            case 5:
                                   printf("Enter the new course: ");
                                   scanf("%s", st[i].cname);
                                   break;
                            }

                            found = 1;
                     }

                     fprintf(fp, "%s %s %d %f %s\n", st[i].fname, st[i].lname, st[i].roll, st[i].cgpa, st[i].cname);
              }

              if (!found)
              {
                     printf("Roll Number not found\n");
              }

              fclose(fp);
       }

       printf("Updated successfully.\n");
}

// driver code
int main()
{
       int choice;

       // Read existing data from file
       FILE *fp_read = fopen("StudentsDetails.txt", "r");
       if (fp_read != NULL)
       {
              while (fscanf(fp_read, "%s %s %d %f %s\n", st[num].fname, st[num].lname, &st[num].roll, &st[num].cgpa, st[num].cname) == 5)
              {
                     num++;
              }
              fclose(fp_read);
       }

       while (1)
       {
              printf("\n\t\tThe Task you want to perform\n");
              printf("\t1. Add Student Details\n");
              printf("\t2. Find Student Details by Roll Number\n");
              printf("\t3. Find the Total number of Students\n");
              printf("\t4. Delete Student Details by Roll Number\n");
              printf("\t5. Update Student Details by Roll Number\n");
              printf("\t6. To Exit\n");

              printf("\nEnter your choice to perform the task: ");
              scanf("%d", &choice);

              switch (choice)
              {
              case 1:
                     addstud();
                     break;
              case 2:
                     find_rl();
                     break;
              case 3:
                     tot_s();
                     break;
              case 4:
                     del_s();
                     break;
              case 5:
                     up_s();
                     break;
              case 6:
                     exit(0);
                     break;
              default:
                     printf("Invalid choice! Please enter a number between 1 and 6.\n");
              }
       }

       return 0;
}