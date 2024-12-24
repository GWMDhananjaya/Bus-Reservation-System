#include <stdio.h>
#include <string.h>

// Function prototypes
void adminMenu();
void userMenu();
int login();

int main()
{
    int userType = login(); // Perform login

    if (userType == 1)
    {
        printf("\nWelcome Admin!\n");
        adminMenu(); // Admin menu
    }
    else if (userType == 2)
    {
        printf("\nWelcome User!\n");
        userMenu(); // Regular user menu
    }
    else
    {
        printf("Invalid login. Exiting program.\n");
    }

    return 0;
}

// Login function
int login()
{
    char username[50], password[50];
    FILE *file = fopen("login.txt", "r"); // Open login file
    if (!file)
    {
        printf("Error: Could not open login file.\n");
        return -1;
    }

    char fileUsername[50], filePassword[50];
    int userType = 0; // 0 for invalid, 1 for admin, 2 for user

    printf("Welcome to Bus Reservation System!\n");
    printf("Please enter your username: ");
    scanf("%s", username);
    printf("Please enter your password: ");
    scanf("%s", password);

    // Check credentials
    while (fscanf(file, "%s %s", fileUsername, filePassword) != EOF)
    {
        if (strcmp(username, fileUsername) == 0 && strcmp(password, filePassword) == 0)
        {
            if (strcmp(username, "admin") == 0)
            {
                userType = 1; // Admin user
            }
            else
            {
                userType = 2; // Regular user
            }
            break;
        }
    }

    fclose(file);
    return userType;
}

// Admin menu function
void adminMenu()
{
    int choice;

    do
    {
        printf("\nAdmin Menu:\n");
        printf("1. Check bus schedule\n");
        printf("2. Add new bus trip\n");
        printf("3. Delete bus trip\n");
        printf("4. Edit bus trip\n");
        printf("5. Print Most Expensive trip\n");
        printf("6. Filter by arrival time\n");
        printf("7. Update File\n");
        printf("8. Exit\n");
        printf("Please select an option: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Checking bus schedule...\n");
            break;
        case 2:
            printf("Adding new bus trip...\n");
            break;
        case 3:
            printf("Deleting bus trip...\n");
            break;
        case 4:
            printf("Editing bus trip...\n");
            break;
        case 5:
            printf("Printing most expensive trip...\n");
            break;
        case 6:
            printf("Filtering by arrival time...\n");
            break;
        case 7:
            printf("Updating file...\n");
            break;
        case 8:
            printf("Exiting admin menu...\n");
            break;
        default:
            printf("Invalid option. Please try again.\n");
        }
    } while (choice != 8);
}

// Regular user menu function
void userMenu()
{
    int choice;

    do
    {
        printf("\nUser Menu:\n");
        printf("1. List bus trips\n");
        printf("2. Book tickets\n");
        printf("3. Cancel reservation\n");
        printf("4. Update File\n");
        printf("5. Exit\n");
        printf("Please select an option: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Listing bus trips...\n");
            break;
        case 2:
            printf("Booking tickets...\n");
            break;
        case 3:
            printf("Canceling reservation...\n");
            break;
        case 4:
            printf("Updating file...\n");
            break;
        case 5:
            printf("Exiting user menu...\n");
            break;
        default:
            printf("Invalid option. Please try again.\n");
        }
    } while (choice != 5);
}
