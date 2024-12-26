#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define structures
typedef struct
{
    char departureTime[10];
    char arrivalTime[10];
    char destination[50];
    float price;
    int tripNumber;
} BusTrip;

typedef struct
{
    int pnr;
    int tripNumber;
    char departureTime[10];
    char arrivalTime[10];
    char date[15];
    char destination[50];
} Booking;

// Function prototypes
void loadBusTrips(BusTrip **trips, int *size);
void saveBusTrips(BusTrip *trips, int size);
void adminMenu(BusTrip **trips, int *size);
void userMenu(BusTrip *trips, int size);
void listBusTrips(BusTrip *trips, int size);
void addBusTrip(BusTrip **trips, int *size);
void deleteBusTrip(BusTrip **trips, int *size);
void editBusTrip(BusTrip *trips, int size);
void mostExpensiveTrip(BusTrip *trips, int size);
void filterByArrivalTime(BusTrip *trips, int size);
void bookTicket(BusTrip *trips, int size);
void cancelReservation();

// Main function
int main()
{
    char username[50], password[20];
    BusTrip *trips = NULL;
    int tripSize = 0;

    printf("Welcome to Bus Reservation System!\n");
    printf("Please enter your username: ");
    scanf("%s", username);
    printf("Please enter your password: ");
    scanf("%s", password);

    // Check login credentials
    if (strcmp(username, "salman.albedaiwi") == 0 && strcmp(password, "62175") == 0)
    {
        loadBusTrips(&trips, &tripSize);
        adminMenu(&trips, &tripSize);
    }
    else if (strcmp(username, "user01") == 0 && strcmp(password, "user123") == 0)
    {
        loadBusTrips(&trips, &tripSize);
        userMenu(trips, tripSize);
    }
    else if (strcmp(username, "user02") == 0 && strcmp(password, "user1234") == 0)
    {
        loadBusTrips(&trips, &tripSize);
        userMenu(trips, tripSize);
    }
    else
    {
        printf("Invalid credentials.\n");
        return 0;
    }

    // Free memory and exit
    free(trips);
    return 0;
}

void loadBusTrips(BusTrip **trips, int *size)
{
    FILE *file = fopen("data.txt", "r");
    if (!file)
    {
        printf("Could not open data.txt.\n");
        return;
    }

    fscanf(file, "%d", size);
    *trips = (BusTrip *)malloc((*size) * sizeof(BusTrip));

    for (int i = 0; i < *size; i++)
    {
        fscanf(file, "%s %s %s %f %d", (*trips)[i].departureTime, (*trips)[i].arrivalTime,
               (*trips)[i].destination, &(*trips)[i].price, &(*trips)[i].tripNumber);
    }

    fclose(file);
}

void saveBusTrips(BusTrip *trips, int size)
{
    FILE *file = fopen("data.txt", "w");
    if (!file)
    {
        printf("Could not open data.txt.\n");
        return;
    }

    fprintf(file, "%d\n", size);
    for (int i = 0; i < size; i++)
    {
        fprintf(file, "%s %s %s %.2f %d\n", trips[i].departureTime, trips[i].arrivalTime,
                trips[i].destination, trips[i].price, trips[i].tripNumber);
    }

    fclose(file);
}

void adminMenu(BusTrip **trips, int *size)
{
    int choice;
    do
    {
        printf("\nAdmin Menu:\n");
        printf("1. Check bus schedule\n");
        printf("2. Add new bus trip\n");
        printf("3. Delete bus trip\n");
        printf("4. Edit bus trip\n");
        printf("5. Print most expensive trip\n");
        printf("6. Filter by arrival time\n");
        printf("7. Update file\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            listBusTrips(*trips, *size);
            break;
        case 2:
            addBusTrip(trips, size);
            break;
        case 3:
            deleteBusTrip(trips, size);
            break;
        case 4:
            editBusTrip(*trips, *size);
            break;
        case 5:
            mostExpensiveTrip(*trips, *size);
            break;
        case 6:
            filterByArrivalTime(*trips, *size);
            break;
        case 7:
            saveBusTrips(*trips, *size);
            break;
        case 8:
            printf("Exiting admin menu.\n");
            break;
        default:
            printf("Invalid choice.\n");
        }
    } while (choice != 8);
}

void userMenu(BusTrip *trips, int size)
{
    int choice;
    do
    {
        printf("\nUser Menu:\n");
        printf("1. List bus trips\n");
        printf("2. Book tickets\n");
        printf("3. Cancel reservation\n");
        printf("4. Update file\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            listBusTrips(trips, size);
            break;
        case 2:
            bookTicket(trips, size);
            break;
        case 3:
            cancelReservation();
            break;
        case 4:
            saveBusTrips(trips, size);
            break;
        case 5:
            printf("Exiting user menu.\n");
            break;
        default:
            printf("Invalid choice.\n");
        }
    } while (choice != 5);
}

void listBusTrips(BusTrip *trips, int size)
{
    printf("\nBus Schedule:\n");
    for (int i = 0; i < size; i++)
    {
        printf("Trip Number: %d\nDeparture: %s\nArrival: %s\nDestination: %s\nPrice: %.2f\n\n",
               trips[i].tripNumber, trips[i].departureTime, trips[i].arrivalTime, trips[i].destination, trips[i].price);
    }
}
void addBusTrip(BusTrip **trips, int *size)
{
    *trips = (BusTrip *)realloc(*trips, (*size + 1) * sizeof(BusTrip));

    printf("Enter departure time: ");
    scanf("%s", (*trips)[*size].departureTime);
    printf("Enter arrival time: ");
    scanf("%s", (*trips)[*size].arrivalTime);
    printf("Enter destination: ");
    scanf("%s", (*trips)[*size].destination);
    printf("Enter price: ");
    scanf("%f", &(*trips)[*size].price);
    printf("Enter trip number: ");
    scanf("%d", &(*trips)[*size].tripNumber);

    (*size)++;

    // Append the new trip to the file
    FILE *file = fopen("data.txt", "a");
    if (file)
    {
        fprintf(file, "%s %s %s %.2f %d\n", // Add '\n' to ensure each record is on a new line
                (*trips)[*size - 1].departureTime,
                (*trips)[*size - 1].arrivalTime,
                (*trips)[*size - 1].destination,
                (*trips)[*size - 1].price,
                (*trips)[*size - 1].tripNumber);
        fclose(file);
    }
    else
    {
        printf("Error updating the data file.\n");
    }

    printf("Bus trip added successfully.\n");
}

void deleteBusTrip(BusTrip **trips, int *size)
{
    int tripNumber, index = -1;
    printf("Enter trip number to delete: ");
    scanf("%d", &tripNumber);

    for (int i = 0; i < *size; i++)
    {
        if ((*trips)[i].tripNumber == tripNumber)
        {
            index = i;
            break;
        }
    }

    if (index == -1)
    {
        printf("Trip not found.\n");
        return;
    }

    for (int i = index; i < *size - 1; i++)
    {
        (*trips)[i] = (*trips)[i + 1];
    }

    (*size)--;
    *trips = (BusTrip *)realloc(*trips, (*size) * sizeof(BusTrip));

    FILE *file = fopen("data.txt", "w");
    if (file)
    {
        fprintf(file, "%d\n", *size);
        for (int i = 0; i < *size; i++)
        {
            fprintf(file, "%s %s %s %.2f %d\n",
                    (*trips)[i].departureTime,
                    (*trips)[i].arrivalTime,
                    (*trips)[i].destination,
                    (*trips)[i].price,
                    (*trips)[i].tripNumber);
        }
        fclose(file);
    }
    else
    {
        printf("Error updating the data file.\n");
    }

    printf("Bus trip deleted successfully.\n");
}

void editBusTrip(BusTrip *trips, int size)
{
    int tripNumber, index = -1;
    printf("Enter trip number to edit: ");
    scanf("%d", &tripNumber);

    for (int i = 0; i < size; i++)
    {
        if (trips[i].tripNumber == tripNumber)
        {
            index = i;
            break;
        }
    }

    if (index == -1)
    {
        printf("Trip not found.\n");
        return;
    }

    printf("Enter new departure time: ");
    scanf("%s", trips[index].departureTime);
    printf("Enter new arrival time: ");
    scanf("%s", trips[index].arrivalTime);
    printf("Enter new destination: ");
    scanf("%s", trips[index].destination);
    printf("Enter new price: ");
    scanf("%f", &trips[index].price);

    FILE *file = fopen("data.txt", "w");
    if (file)
    {
        fprintf(file, "%d\n", size);
        for (int i = 0; i < size; i++)
        {
            fprintf(file, "%s %s %s %.2f %d\n",
                    trips[i].departureTime,
                    trips[i].arrivalTime,
                    trips[i].destination,
                    trips[i].price,
                    trips[i].tripNumber);
        }
        fclose(file);
    }
    else
    {
        printf("Error updating the data file.\n");
    }

    printf("Bus trip edited successfully.\n");
}

void mostExpensiveTrip(BusTrip *trips, int size)
{
    int index = 0;
    for (int i = 1; i < size; i++)
    {
        if (trips[i].price > trips[index].price)
        {
            index = i;
        }
    }

    printf("\nMost Expensive Trip:\n");
    printf("Trip Number: %d\nDeparture: %s\nArrival: %s\nDestination: %s\nPrice: %.2f\n",
           trips[index].tripNumber, trips[index].departureTime, trips[index].arrivalTime, trips[index].destination, trips[index].price);
}

void filterByArrivalTime(BusTrip *trips, int size)
{
    char startTime[10], endTime[10];
    printf("Enter start arrival time: ");
    scanf("%s", startTime);
    printf("Enter end arrival time: ");
    scanf("%s", endTime);

    printf("Trips between %s and %s:\n", startTime, endTime);
    for (int i = 0; i < size; i++)
    {
        if (strcmp(trips[i].arrivalTime, startTime) >= 0 && strcmp(trips[i].arrivalTime, endTime) <= 0)
        {
            printf("Trip Number: %d\nDeparture: %s\nArrival: %s\nDestination: %s\nPrice: %.2f\n\n",
                   trips[i].tripNumber, trips[i].departureTime, trips[i].arrivalTime, trips[i].destination, trips[i].price);
        }
    }
}

void bookTicket(BusTrip *trips, int size)
{
    int tripNumber, found = 0;
    Booking booking;

    printf("Enter the trip number to book: ");
    scanf("%d", &tripNumber);

    for (int i = 0; i < size; i++)
    {
        if (trips[i].tripNumber == tripNumber)
        {
            found = 1;
            booking.tripNumber = tripNumber;
            strcpy(booking.departureTime, trips[i].departureTime);
            strcpy(booking.arrivalTime, trips[i].arrivalTime);
            strcpy(booking.destination, trips[i].destination);

            printf("Enter booking date (DD/MM/YYYY): ");
            scanf("%s", booking.date);

            // Generate a unique PNR
            booking.pnr = rand() % 9000 + 1000; // Random 4-digit number

            // Append the booking to the booking.txt file
            FILE *file = fopen("booking.txt", "a");
            if (file)
            {
                fprintf(file, "%d %d %s %s %s %s\n", booking.pnr, booking.tripNumber, booking.departureTime,
                        booking.arrivalTime, booking.date, booking.destination);
                fclose(file);
                printf("Booking successful! Your PNR is %d\n", booking.pnr);
            }
            else
            {
                printf("Error saving booking.\n");
            }
            break;
        }
    }

    if (!found)
    {
        printf("Trip not found.\n");
    }
}

void cancelReservation()
{
    int pnr, found = 0;
    printf("Enter PNR to cancel reservation: ");
    scanf("%d", &pnr);

    FILE *file = fopen("booking.txt", "r");
    FILE *tempFile = fopen("temp.txt", "w");
    if (!file || !tempFile)
    {
        printf("Error opening files.\n");
        return;
    }

    Booking booking;
    while (fscanf(file, "%d %d %s %s %s %s", &booking.pnr, &booking.tripNumber, booking.departureTime,
                  booking.arrivalTime, booking.date, booking.destination) != EOF)
    {
        if (booking.pnr == pnr)
        {
            found = 1;
            printf("Reservation with PNR %d canceled successfully.\n", pnr);
        }
        else
        {
            fprintf(tempFile, "%d %d %s %s %s %s\n", booking.pnr, booking.tripNumber, booking.departureTime,
                    booking.arrivalTime, booking.date, booking.destination);
        }
    }

    fclose(file);
    fclose(tempFile);

    remove("booking.txt");
    rename("temp.txt", "booking.txt");

    if (!found)
    {
        printf("Reservation with PNR %d not found.\n", pnr);
    }
}
