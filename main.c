#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct uAccounts {
    char userName[30];
    char userPass[30];
};
struct uAccounts userAccounts[1000 + 1];
int totalAccounts = 1;

struct uEmployees {
    char eName[20];
    char eDept[20];
    int eSalary;
};

struct uEmployees userEmployees[1000 + 1] = { {"", "", 0} };
int totalEmployees = 0;

void getEmployees() {
    FILE* ptr = fopen("employees.txt", "r");

    if(ptr == NULL)
        return 0;

    fscanf(ptr, "%d\n", &totalEmployees);
    for(int i = 1; i <= totalEmployees; i++)
        fscanf(ptr, " %[^\n]\n %[^\n]\n%d\n\n", userEmployees[i].eName, userEmployees[i].eDept, &userEmployees[i].eSalary);

    fclose(ptr);
}

void saveEmployees() {
    FILE* ptr = fopen("employees.txt", "w");

    if(ptr == NULL)
        return 0;

    fprintf(ptr, "%d\n", totalEmployees);
    for(int i = 1; i <= totalEmployees; i++)
        fprintf(ptr, "%s\n%s\n%d\n\n", userEmployees[i].eName, userEmployees[i].eDept, userEmployees[i].eSalary);

    fclose(ptr);
}

int showApp(int index)
{
    system("cls");
    switch(index)
    {
        case 1: {
            int n;
            printf("========================================\n");
            printf("\tEMPLOYEE MANAGEMENT SYSTEM\n");
            printf("========================================\n\n");

            printf("\tDeveloped in C Language\n\n");

            printf("----------------------------------------\n");

            printf("1. Login\n");
            printf("2. Exit\n");
            printf("----------------------------------------\n");

            printf("Enter your choice: ");
            scanf("%d", &n);

            if(n == 2)
                return showApp(10);

            if(n < 1 || n > 2)
                showApp(1);

            showApp(2);
            break;
        }

        case 2: {
            printf("========================================\n");
            printf("\tLOGIN PANEL\n");
            printf("========================================\n\n");

            char loginUser[32], loginPass[32];
            printf("Username: "); scanf("%s", &loginUser);
            printf("Password: "); scanf("%s", &loginPass);

            for(int i = 1; i <= totalAccounts; i++)
                if(!strcmp(loginUser, userAccounts[i].userName)  && !strcmp(loginPass, userAccounts[i].userPass))
                    return showApp(3);

            showApp(2);
            break;
        }

        case 3: {
            int n;
            printf("========================================\n");
            printf("\tMAIN MENU\n");
            printf("========================================\n\n");

            printf("1. Add New Employee\n2. View All Employees\n3. Search Employee\n4. Update Employee Details\n5. Delete Employee\n6. Reports / Statistics\n7. Exit\n\n");
            printf("----------------------------------------\n");
            printf("Enter your choice: ");
            scanf("%d", &n);

            if(n < 1 || n > 7)
                return showApp(3);

            showApp(3 + n);
            break;
        }

        case 4: {
            printf("========================================\n");
            printf("\tADD NEW EMPLOYEE\n");
            printf("========================================\n\n");

            char eName[20], eDept[20];
            int eSalary;
            getchar();
            printf("Enter Name: "); fgets(eName, sizeof(eName), stdin);
            printf("Enter Department: "); fgets(eDept, sizeof(eDept), stdin);
            printf("Enter Salary: "); scanf("%d", &eSalary);

            eName[strcspn(eName, "\n")] = 0;
            eDept[strcspn(eDept, "\n")] = 0;

            int n;
            printf("\n----------------------------------------\n");
            printf("1. Save Employee\n");
            printf("2. Cancel\n");
            printf("----------------------------------------\n\n");

            printf("Enter your choice: "); scanf("%d", &n);

            while(n < 1 || n > 2)
                scanf("%d", &n);

            if(n == 1) {
                totalEmployees++;
                strcpy(userEmployees[totalEmployees].eName, eName);
                strcpy(userEmployees[totalEmployees].eDept, eDept);
                userEmployees[totalEmployees].eSalary = eSalary;

                saveEmployees();
                printf("Employee added successfully!\n");
            }

            showApp(3);
            break;
        }

        case 5: {
            char n;
            printf("========================================\n");
            printf("\tEMPLOYEE LIST\n");
            printf("========================================\n\n");

            printf("ID\tName\tDept\tSalary\n");
            printf("----------------------------------------\n");

            for(int i = 1; i <= totalEmployees; i++)
                printf("%d\t%s\t%s\t%d\n", i, userEmployees[i].eName, userEmployees[i].eDept, userEmployees[i].eSalary);

            printf("----------------------------------------\n\n");
            printf("Total Employees: %d\n\n", totalEmployees);

            printf("Press any key to return to Main Menu...");
            scanf("%c", &n); scanf("%c", &n);

            showApp(3);
            break;
        }

        case 6: {
            printf("========================================\n");
            printf("\tSEARCH EMPLOYEE\n");
            printf("========================================\n\n");

            int n;
            printf("Search Employee by ID: "); scanf("%d", &n);
            while(n < 1 || n > totalEmployees)
                scanf("%d", &n);

            system("cls");

            printf("Employee Found!\n\n");
            printf("ID: %d\nName: %s\nDept: %s\nSalary: %d\n\n", n, userEmployees[n].eName, userEmployees[n].eDept, userEmployees[n].eSalary);

            char c;
            printf("Press any key to continue...");
            scanf("%c", &c); scanf("%c", &c);

            showApp(3);
            break;
        }

        case 7: {
            printf("========================================\n");
            printf("\tUPDATE EMPLOYEE\n");
            printf("========================================\n");

            int n;
            printf("Enter Employee ID to update: "); scanf("%d", &n);
            while(n < 1 || n > totalEmployees)
                scanf("%d", &n);

            printf("=== Current Details: ===\nName: %s\nDept: %s\nSalary: %d\n\n", userEmployees[n].eName, userEmployees[n].eDept, userEmployees[n].eSalary);
            printf("What do you want to update?\n");
            printf("----------------------------------------\n");
            printf("1. Update Name\n2. Update Department\n3. Update Salary\n4. Back\n");
            printf("----------------------------------------\n\n");

            int choice;
            printf("Enter your choice: "); scanf("%d", &choice);
            while(choice < 1 || choice > 4)
                scanf("%d", &choice);
           
            switch(choice) {
                case 1: {
                    printf("Enter new name: "); 
                    scanf(" %[^\n]", userEmployees[n].eName);
                    break;
                }

                case 2: {
                    printf("Enter new department: "); 
                    scanf(" %[^\n]", userEmployees[n].eDept);
                    break;
                }

                case 3: {
                    printf("Enter new salary: "); 
                    scanf("%d", &userEmployees[n].eSalary);
                    break;
                }

                case 4:
                    break;
            }
            
            showApp(3);
            break;
        }

        case 8: {
            printf("========================================\n");
            printf("\tDELETE EMPLOYEE\n");
            printf("========================================\n\n");

            int n;
            printf("Enter Employee ID to delete: "); scanf("%d", &n);

            while(n < 1 || n > totalEmployees)
                scanf("%d", &n);

            int choice;
            printf("Are you sure you want to delete this employee?\n");
            printf("1. Yes\n2. No\n\nEnter your choice: ");
            scanf("%d", &n);

            while(n < 1 || n > 2)
                scanf("%d", &n);

            if(n == 1) {
                for(int i = n; i < totalEmployees; i++) {
                    strcpy(userEmployees[i].eName, userEmployees[i+1].eName);
                    strcpy(userEmployees[i].eDept, userEmployees[i+1].eDept);
                    userEmployees[i].eSalary = userEmployees[i+1].eSalary;
                }
                totalEmployees--;

                saveEmployees();
            }

            showApp(3);
            break;
        }

        case 9: {
            return 0;
            break;
        }

        case 10: {
            printf("========================================\n");
            printf("\tTHANK YOU FOR USING EMS\n");
            printf("========================================\n\n");

            printf("Have a great day!\n\n");
            printf("Press any key to exit...");
            char n;
            scanf("%c", &n); scanf("%c", &n);
            break; 
        }   
    }
    return 0;
}

int main() {
    strcpy(userAccounts[totalAccounts].userName, "nusuntandy");
    strcpy(userAccounts[totalAccounts].userPass, "test");

    getEmployees();
    showApp(1);
    return 0;
}