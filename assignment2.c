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
void edit();
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
        printf("\t\t\t\t4. Edit Student\n");
        printf("\t\t\t\t5. Delete Student\n");
        printf("\t\t\t\t6. Exit\n");
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
        case 4:
            edit();
            break;
        case 5:
            delete();
            break;
        default:
            break;
        }
    } while (choice != 6);

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
        fgets(stu.ID, sizeof(stu.ID), stdin);
        stu.ID[strcspn(stu.ID, "\n")] = '\0';

        for (size_t i = 0; i < strlen(stu.ID); i++)
        {
            stu.ID[i] = toupper(stu.ID[i]);
        }

        printf("\n\t\t\tEnter Birth(Day-Month-Year) : ");
        fgets(stu.Birth, sizeof(stu.Birth), stdin);
        stu.Birth[strcspn(stu.Birth, "\n")] = '\0';

        printf("\n\t\t\tEnter Class : ");
        fgets(stu.Chuyen_Nganh, sizeof(stu.Chuyen_Nganh), stdin);
        stu.Chuyen_Nganh[strcspn(stu.Chuyen_Nganh, "\n")] = '\0';

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
                      &stu.LAB, &stu.PT, &stu.AS, &stu.PE, &stu.FE, &stu.Avg, stu.XepLoai) != EOF)
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

    char userInput[20];

    if (fi == NULL)
    {
        fprintf(stderr, "Could not open file.\n");
    }
    else
       {
        printf("\t\t\t\t****Search Student Information****\n");
        printf("\t\t\t\t_________________________________\n");
        printf("\t\t\t\tEnter student ID: ");
        fgets(userInput, sizeof(userInput), stdin);
        userInput[strcspn(userInput, "\n")] = '\0';
        strupr(userInput); 

        int found = 0;

        while (fscanf(fi, "%29s %29s %29s %9s %lf %lf %lf %lf %lf %lf %9s",
                      stu.Name, stu.ID, stu.Birth, stu.Chuyen_Nganh,
                      &stu.LAB, &stu.PT, &stu.AS, &stu.PE, &stu.FE, &stu.Avg, stu.XepLoai) != EOF)
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

void edit()
{
    FILE *fi = fopen("input.txt", "r");
    FILE *fi1 = fopen("temp.txt", "w");
    struct Student stu;
    char newID[30];

    if (fi == NULL)
    {
        fprintf(stderr, "Could not open file.\n");
    }
    else
    {
        printf("\t\t\t\t****Edit Student Information****\n");
        printf("\t\t\t\t_________________________________\n");
        printf("\t\t\t\tEnter student ID to edit: ");
        fgets(newID, sizeof(newID), stdin);
        newID[strcspn(newID, "\n")] = '\0';
        strupr(newID);

        int found = 0;

        while (fscanf(fi, "%29s %29s %29s %9s %lf %lf %lf %lf %lf %lf %9s",
                      stu.Name, stu.ID, stu.Birth, stu.Chuyen_Nganh,
                      &stu.LAB, &stu.PT, &stu.AS, &stu.PE, &stu.FE, &stu.Avg, stu.XepLoai) == 11)
        {
            if (strcmp(stu.ID, newID) == 0)
            {
                found = 1;
                printf("\t\t\t\tWhat do you want to update?\n");
                printf("\t\t\t\t1. Name\n");
                printf("\t\t\t\t2. ID\n");
                printf("\t\t\t\t3. Birth\n");
                printf("\t\t\t\t4. Class\n");
                printf("\t\t\t\t5. Grades\n");
                printf("\t\t\t\t6. Exit\n");
                printf("\t\t\t\t_________________________________\n");

                int updateChoice;
                scanf("%d", &updateChoice);
                getchar(); // Consume the newline character left in the input buffer

                switch (updateChoice)
                {
                case 1:
                    printf("\t\t\t\tEnter new Name: ");
                    fgets(stu.Name, sizeof(stu.Name), stdin);
                    stu.Name[strcspn(stu.Name, "\n")] = '\0';
                    break;
                case 2:
                    printf("\t\t\t\tEnter new ID: ");
                    fgets(stu.ID, sizeof(stu.ID), stdin);
                    stu.ID[strcspn(stu.ID, "\n")] = '\0';
                    break;
                case 3:
                    printf("\t\t\t\tEnter new Birth: ");
                    fgets(stu.Birth, sizeof(stu.Birth), stdin);
                    stu.Birth[strcspn(stu.Birth, "\n")] = '\0';
                    break;
                case 4:
                    printf("\t\t\t\tEnter new Class: ");
                    fgets(stu.Chuyen_Nganh, sizeof(stu.Chuyen_Nganh), stdin);
                    stu.Chuyen_Nganh[strcspn(stu.Chuyen_Nganh, "\n")] = '\0';
                    break;
                case 5:
                    // Inner switch for updating specific grades
                    printf("\t\t\t\tWhich grade do you want to update?\n");
                    printf("\t\t\t\t1. LAB\n");
                    printf("\t\t\t\t2. PT\n");
                    printf("\t\t\t\t3. AS\n");
                    printf("\t\t\t\t4. PE\n");
                    printf("\t\t\t\t5. FE\n");
                    printf("\t\t\t\t6. Exit\n");
                    printf("\t\t\t\t_________________________________\n");

                    int gradeChoice;
                    scanf("%d", &gradeChoice);
                    getchar(); // Consume the newline character left in the input buffer

                    switch (gradeChoice)
                    {
                    case 1:
                        printf("\t\t\t\tEnter new LAB grade: ");
                        scanf("%lf", &stu.LAB);
                        break;
                    case 2:
                        printf("\t\t\t\tEnter new PT grade: ");
                        scanf("%lf", &stu.PT);
                        break;
                    case 3:
                        printf("\t\t\t\tEnter new AS grade: ");
                        scanf("%lf", &stu.AS);
                        break;
                    case 4:
                        printf("\t\t\t\tEnter new PE grade: ");
                        scanf("%lf", &stu.PE);
                        break;
                    case 5:
                        printf("\t\t\t\tEnter new FE grade: ");
                        scanf("%lf", &stu.FE);
                        break;
                    case 6:
                        // Exit the update grades switch
                        break;
                    default:
                        printf("\t\t\t\tInvalid choice for updating grades.\n");
                        break;
                    }
                    break;
                case 6:
                    // Exit the update options switch
                    break;
                default:
                    printf("\t\t\t\tInvalid choice for updating information.\n");
                    break;
                }
            }

            // Write the record to the temporary file
            fprintf(fi1, "%s %s %s %s %lf %lf %lf %lf %lf %lf %s\n",
                    stu.Name, stu.ID, stu.Birth, stu.Chuyen_Nganh,
                    stu.LAB, stu.PT, stu.AS, stu.PE, stu.FE, stu.Avg, stu.XepLoai);
        }

        fclose(fi);
        fclose(fi1);

        // Replace the original file with the temporary file
        remove("input.txt");
        rename("temp.txt", "input.txt");

        if (found)
        {
            printf("\t\t\t\tStudent with ID updated successfully.\n", newID);
        }
        else
        {
            printf("\t\t\t\tStudent with ID not found.\n", newID);
        }
    }
}



void delete()
{
    FILE *fi = fopen("input.txt", "r");
    FILE *fi1 = fopen("temp.txt", "w");
    struct Student stu;
    
    char deleteinput[20];
    int found = 0;
    if (fi == NULL)
    {
        fprintf(stderr, "Could not open file.\n");
    }
    else
    {
        printf("\t\t\t\t****Delete Student Information****\n");
        printf("\t\t\t\t_________________________________\n");
        printf("\t\t\t\tEnter student ID to be deleted: ");
        fgets(deleteinput, 20, stdin);
        deleteinput[strcspn(deleteinput, "\n")] = '\0';
        strupr(deleteinput);
        while (fscanf(fi, "%29s %29s %29s %9s %lf %lf %lf %lf %lf %lf %9s",
                      stu.Name, stu.ID, stu.Birth, stu.Chuyen_Nganh,
                      &stu.LAB, &stu.PT, &stu.AS, &stu.PE, &stu.FE, &stu.Avg, stu.XepLoai) != EOF)
        {
            if (strcmp(stu.ID, deleteinput) == 0) 
            {
                found = 1;
            }
            else
            {
               fprintf(fi1, "%s %s %s %s %lf %lf %lf %lf %lf %lf %s\n",
                    stu.Name, stu.ID, stu.Birth, stu.Chuyen_Nganh, stu.LAB, stu.PT, stu.AS, stu.PE, stu.FE, stu.Avg, stu.XepLoai);
            }
        }
        fclose(fi);
        fclose(fi1);
        if (found)
        {
            remove("input.txt");
            rename("temp.txt","input.txt");
            printf("\t\t\t\tDeleted successfully!\n");
        }
        else
        {
            printf("\t\t\t\tDeleted unsuccessfully cause Student not found!\n");
        }
    }
}
