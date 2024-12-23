#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define structures
typedef struct {
    int tripNumber;
    char departureTime[20];
    char arrivalTime[20];
    char destination[50];
    float price;
} BusTrip;

typedef struct {
    int PNR;
    int tripNumber;
    char departureTime[20];
    char arrivalTime[20];
    char date[20];
    char destination[50];
} Booking;

// Function declarations
void adminMenu();
void userMenu();
void loadBusData(BusTrip **trips, int *count);
void saveBusData(BusTrip *trips, int count);
void addBusTrip(BusTrip **trips, int *count);
void listBusTrips(BusTrip *trips, int count);
void deleteBusTrip(BusTrip **trips, int *count);
void bookTicket(Booking **bookings, int *bookingCount);
void cancelReservation(Booking **bookings, int *bookingCount);
void updateFile(BusTrip *trips, int count);
int authenticate(const char *username, const char *password);

int main() {
    char username[50], password[50];

    printf("Welcome to Bus Reservation System!\n");
    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    if (authenticate(username, password)) {
        if (strcmp(username, "admin") == 0) {
            adminMenu();
        } else {
            userMenu();
        }
    } else {
        printf("Invalid credentials. Exiting...\n");
    }

    return 0;
}

// Authentication
int authenticate(const char *username, const char *password) {
    FILE *file = fopen("login.txt", "r");
    if (!file) {
        printf("Error: Unable to open login file.\n");
        return 0;
    }

    char storedUsername[50], storedPassword[50];
    while (fscanf(file, "%s %s", storedUsername, storedPassword) != EOF) {
        if (strcmp(username, storedUsername) == 0 && strcmp(password, storedPassword) == 0) {
            fclose(file);
            return 1;
        }
    }

    fclose(file);
    return 0;
}

// Admin Menu
void adminMenu() {
    int choice;
    BusTrip *trips = NULL;
    int tripCount = 0;

    loadBusData(&trips, &tripCount);

    do {
        printf("\nAdmin Menu:\n");
        printf("1. Check bus schedule\n");
        printf("2. Add new bus trip\n");
        printf("3. Delete bus trip\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                listBusTrips(trips, tripCount);
                break;
            case 2:
                addBusTrip(&trips, &tripCount);
                break;
            case 3:
                deleteBusTrip(&trips, &tripCount);
                break;
            case 4:
                updateFile(trips, tripCount);
                printf("Exiting admin menu...\n");
                break;
            default:
                printf("Invalid choice. Try again.\n");
        }
    } while (choice != 4);

    free(trips);
}

// User Menu
void userMenu() {
    int choice;
    Booking *bookings = NULL;
    int bookingCount = 0;

    do {
        printf("\nUser Menu:\n");
        printf("1. List bus trips\n");
        printf("2. Book tickets\n");
        printf("3. Cancel reservation\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                // Function to list bus trips (you can load the trips here)
                break;
            case 2:
                bookTicket(&bookings, &bookingCount);
                break;
            case 3:
                cancelReservation(&bookings, &bookingCount);
                break;
            case 4:
                printf("Exiting user menu...\n");
                break;
            default:
                printf("Invalid choice. Try again.\n");
        }
    } while (choice != 4);

    free(bookings);
}

// Load bus data from file
void loadBusData(BusTrip **trips, int *count) {
    FILE *file = fopen("data.txt", "r");
    if (!file) {
        printf("Error: Unable to open data file.\n");
        return;
    }

    fscanf(file, "%d", count);  // Read the number of trips
    *trips = (BusTrip *)malloc((*count) * sizeof(BusTrip));

    for (int i = 0; i < *count; i++) {
        fscanf(file, "%d %s %s %s %f",
               &(*trips)[i].tripNumber,
               (*trips)[i].departureTime,
               (*trips)[i].arrivalTime,
               (*trips)[i].destination,
               &(*trips)[i].price);
    }

    fclose(file);
}

// Save bus data to file
void saveBusData(BusTrip *trips, int count) {
    FILE *file = fopen("data.txt", "w");
    if (!file) {
        printf("Error: Unable to open data file.\n");
        return;
    }

    fprintf(file, "%d\n", count);
    for (int i = 0; i < count; i++) {
        fprintf(file, "%d %s %s %s %.2f\n",
                trips[i].tripNumber,
                trips[i].departureTime,
                trips[i].arrivalTime,
                trips[i].destination,
                trips[i].price);
    }

    fclose(file);
}

// Add a new bus trip
void addBusTrip(BusTrip **trips, int *count) {
    *trips = (BusTrip *)realloc(*trips, (*count + 1) * sizeof(BusTrip));

    printf("Enter trip number: ");
    scanf("%d", &(*trips)[*count].tripNumber);
    printf("Enter departure time: ");
    scanf("%s", (*trips)[*count].departureTime);
    printf("Enter arrival time: ");
    scanf("%s", (*trips)[*count].arrivalTime);
    printf("Enter destination: ");
    scanf("%s", (*trips)[*count].destination);
    printf("Enter price: ");
    scanf("%f", &(*trips)[*count].price);

    (*count)++;
    printf("Bus trip added successfully.\n");
}

// List bus trips
void listBusTrips(BusTrip *trips, int count) {
    printf("Bus Trips:\n");
    for (int i = 0; i < count; i++) {
        printf("%d %s %s %s %.2f\n",
               trips[i].tripNumber,
               trips[i].departureTime,
               trips[i].arrivalTime,
               trips[i].destination,
               trips[i].price);
    }
}

// Delete a bus trip
void deleteBusTrip(BusTrip **trips, int *count) {
    int tripNumber, found = 0;

    printf("Enter trip number to delete: ");
    scanf("%d", &tripNumber);

    for (int i = 0; i < *count; i++) {
        if ((*trips)[i].tripNumber == tripNumber) {
            found = 1;
            for (int j = i; j < *count - 1; j++) {
                (*trips)[j] = (*trips)[j + 1];
            }
            (*count)--;
            *trips = (BusTrip *)realloc(*trips, (*count) * sizeof(BusTrip));
            printf("Bus trip deleted successfully.\n");
            break;
        }
    }

    if (!found) {
        printf("Bus trip not found.\n");
    }
}

// Book a ticket
void bookTicket(Booking **bookings, int *bookingCount) {
    *bookings = (Booking *)realloc(*bookings, (*bookingCount + 1) * sizeof(Booking));
    printf("Enter trip number: ");
    scanf("%d", &(*bookings)[*bookingCount].tripNumber);
    // Add other details here (PNR generation, date, etc.)
    (*bookingCount)++;
    printf("Ticket booked successfully.\n");
}

// Cancel a reservation
void cancelReservation(Booking **bookings, int *bookingCount) {
    int PNR, found = 0;
    printf("Enter PNR to cancel: ");
    scanf("%d", &PNR);

    for (int i = 0; i < *bookingCount; i++) {
        if ((*bookings)[i].PNR == PNR) {
            found = 1;
            for (int j = i; j < *bookingCount - 1; j++) {
                (*bookings)[j] = (*bookings)[j + 1];
            }
            (*bookingCount)--;
            *bookings = (Booking *)realloc(*bookings, (*bookingCount) * sizeof(Booking));
            printf("Reservation canceled successfully.\n");
            break;
        }
    }

    if (!found) {
        printf("Reservation not found.\n");
    }
}

// Update the file
void updateFile(BusTrip *trips, int count) {
    saveBusData(trips, count);
    printf("Data saved to file successfully.\n");
}
