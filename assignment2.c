#include <stdio.h>
#include <string.h>
#include <ctype.h>

struct Student
{
    char Name[30];
    char ID[30];
    char Birth[30];
    char Chuyen_Nganh[10];
    char XepLoai[10];
    double LAB, PE, FE, AS, PT, Avg;
};

void addstudent();
void display();
void search();
void delete();

int main()
{
    int choice;
    do
    {
        printf("\t\t\t\t****STUDENT MANAGEMENT SYSTEM****\n");
        printf("\t\t\t\t______________________________________\n");
        printf("\n\n\t\t\t\t1. Add Student\n");
        printf("\t\t\t\t2. Display Student\n");
        printf("\t\t\t\t3. Search Student\n");
        printf("\t\t\t\t4. Delete Student\n");
        printf("\t\t\t\t5. Exit\n");
        printf("\t\t\t\t______________________________________\n");
        scanf("%d", &choice);
        getchar(); // Consume the newline character left in the input buffer

        switch (choice)
        {
        case 1: // Add student
            addstudent();
            break;
        case 2:
            display();
            break;
        case 3:
            search();
            break;

        default:
            break;
        }
    } while (choice != 5);

    return 0;
}

void addstudent()
{
    char another_choice;
    FILE *fi;
    struct Student stu;

    do
    {
        printf("\t\t\t\t****Add Student Information****\n\n\n\n");
        fi = fopen("input.txt", "a");

        printf("\n\t\t\tEnter Name : ");
        fgets(stu.Name, sizeof(stu.Name), stdin);
        stu.Name[strcspn(stu.Name, "\n")] = '\0';

        printf("\n\t\t\tEnter ID (e.g., HE190300) : ");
        scanf("%s", stu.ID);

        for (size_t i = 0; i < strlen(stu.ID); i++)
        {
            stu.ID[i] = toupper(stu.ID[i]);
        }

        printf("\n\t\t\tEnter Birth(Day-Month-Year) : ");
        scanf("%s", stu.Birth);

        printf("\n\t\t\tEnter Class : ");
        scanf("%s", stu.Chuyen_Nganh);

        for (size_t i = 0; i < strlen(stu.Chuyen_Nganh); i++)
        {
            stu.Chuyen_Nganh[i] = toupper(stu.Chuyen_Nganh[i]);
        }

        printf("\n\t\t\tEnter Your Grades : ");
        printf("\n\t\t\tYour LAB : ");
        scanf("%lf", &stu.LAB);

        printf("\n\t\t\tYour PT : ");
        scanf("%lf", &stu.PT);

        printf("\n\t\t\tYour AS : ");
        scanf("%lf", &stu.AS);

        printf("\n\t\t\tYour PE : ");
        scanf("%lf", &stu.PE);

        printf("\n\t\t\tYour FE : ");
        scanf("%lf", &stu.FE);
        printf("\n\t\t\t_____________________________\n");

        stu.Avg = 0.1 * stu.AS + 0.1 * stu.LAB + 0.1 * stu.PT + 0.4 * stu.PE + 0.3 * stu.FE;

        if (stu.Avg < 5)
        {
            strcpy(stu.XepLoai, "Not Pass!");
        }
        else if (stu.Avg >= 5)
        {
            strcpy(stu.XepLoai, "Pass!");
        }

        if (fi == NULL)
        {
            fprintf(stderr, "\n\t\t\tCannot open file\n");
        }
        else
        {
            printf("\t\t\tStored successfully\n");
            // Writing student data to file
            fprintf(fi, "%s %s %s %s %lf %lf %lf %lf %lf %lf %s\n",
                    stu.Name, stu.ID, stu.Birth, stu.Chuyen_Nganh, stu.LAB, stu.PT, stu.AS, stu.PE, stu.FE, stu.Avg, stu.XepLoai);
            fclose(fi);
        }

        printf("Do you want to add another student? (Y/N): ");
        scanf(" %c", &another_choice); // Use a space before %c to skip whitespace characters
        getchar(); // Consume the newline character left in the input buffer
    } while (another_choice == 'Y' || another_choice == 'y');
}

void display()
{
    FILE *fi = fopen("input.txt", "r");
    struct Student stu;

    if (fi == NULL)
    {
        fprintf(stderr, "Could not open file.\n");
    }
    else
    {
        printf("\t\t\t\t****Display Student Information****\n");
        printf("\t\t\t\t_________________________________\n");

        while (fscanf(fi, "%29s %29s %29s %9s %lf %lf %lf %lf %lf %lf %9s",
                      stu.Name, stu.ID, stu.Birth, stu.Chuyen_Nganh,
                      &stu.LAB, &stu.PT, &stu.AS, &stu.PE, &stu.FE, &stu.Avg, stu.XepLoai) == 11)
        {
            printf("\n\t\t\t\tStudent's Name: %s \n", stu.Name);
            printf("\t\t\t\tStudent's ID: %s \n", stu.ID);
            int day, month, year;
            sscanf(stu.Birth, "%2d%2d%4d", &day, &month, &year);
            printf("\t\t\t\tStudent's Birth: %02d/%02d/%4d \n", day, month, year);
            printf("\t\t\t\tStudent's Class: %s \n", stu.Chuyen_Nganh);
            printf("\t\t\t\tStudent's LAB: %.2lf \n", stu.LAB);
            printf("\t\t\t\tStudent's PT: %.2lf \n", stu.PT);
            printf("\t\t\t\tStudent's AS: %.2lf \n", stu.AS);
            printf("\t\t\t\tStudent's PE: %.2lf \n", stu.PE);
            printf("\t\t\t\tStudent's FE: %.2lf \n", stu.FE);
            printf("\t\t\t\tStudent's AVG: %.2lf \n", stu.Avg);
            printf("\t\t\t\tStudent's Status: %s \n", stu.XepLoai);
            printf("\n\t\t\t\t_________________________________\n");
        }

        fclose(fi);
    }
}

void search()
{
    FILE *fi = fopen("input.txt", "r");
    struct Student stu;

    char userInput[30];

    if (fi == NULL)
    {
        fprintf(stderr, "Could not open file.\n");
    }
    else
       {
        printf("\t\t\t\t****Search Student Information****\n");
        printf("\t\t\t\t_________________________________\n");
        printf("\t\t\t\tEnter student ID: ");
        scanf("%s", userInput);

        int found = 0;

        while (fscanf(fi, "%29s %29s %29s %9s %lf %lf %lf %lf %lf %lf %9s",
                      stu.Name, stu.ID, stu.Birth, stu.Chuyen_Nganh,
                      &stu.LAB, &stu.PT, &stu.AS, &stu.PE, &stu.FE, &stu.Avg, stu.XepLoai) == 11)
        {

            // Check if the user input matches the student ID
            if (strcmp(userInput, stu.ID) == 0)
            {
                found = 1;
                printf("\n\t\t\t\tStudent's Name: %s \n", stu.Name);
                printf("\t\t\t\tStudent's ID: %s \n", stu.ID);
                int day, month, year;
                sscanf(stu.Birth, "%2d%2d%4d", &day, &month, &year);
                printf("\t\t\t\tStudent's Birth: %02d/%02d/%4d \n", day, month, year);
                printf("\t\t\t\tStudent's Class: %s \n", stu.Chuyen_Nganh);
                printf("\t\t\t\tStudent's LAB: %.2lf \n", stu.LAB);
                printf("\t\t\t\tStudent's PT: %.2lf \n", stu.PT);
                printf("\t\t\t\tStudent's AS: %.2lf \n", stu.AS);
                printf("\t\t\t\tStudent's PE: %.2lf \n", stu.PE);
                printf("\t\t\t\tStudent's FE: %.2lf \n", stu.FE);
                printf("\t\t\t\tStudent's AVG: %.2lf \n", stu.Avg);
                printf("\n\t\t\t\t_________________________________\n");
                break;
            }
        }

        if (!found)
        {
            printf("\t\t\t\tStudent not found!\n");
        }
        else
        {
            printf("\t\t\tStudent Found!!!!");
        }

        fclose(fi);
    }
}

void delete()
{
    
}
