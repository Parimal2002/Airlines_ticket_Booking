#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PASSPORT_LEN 10
#define MAX_NAME_LEN 30
#define MAX_DESTINATION_LEN 30
#define MAX_EMAIL_LEN 50
#define MAX_SEATS 15

struct Passenger
{
    char passport[MAX_PASSPORT_LEN];
    char name[MAX_NAME_LEN];
    char destination[MAX_DESTINATION_LEN];
    int seatNum;
    char email[MAX_EMAIL_LEN];
    struct Passenger *next;
};

struct Passenger *head = NULL;

void clearInputBuffer()
{
    while (getchar() != '\n')
    {
    }
}

void displayPassenger(const struct Passenger *passenger)
{
    printf("\nPassport Number: %s", passenger->passport);
    printf("\nName: %s", passenger->name);
    printf("\nEmail: %s", passenger->email);
    printf("\nSeat Number: A-%d", passenger->seatNum);
    printf("\nDestination: %s", passenger->destination);
    printf("\n*=====================================================*\n");
}

void reserveSeat(int seatNum)
{
    if (seatNum < 1 || seatNum > MAX_SEATS)
    {
        printf("Invalid seat number.\n");
        return;
    }

    if (head != NULL)
    {
        struct Passenger *temp = head;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = (struct Passenger *)malloc(sizeof(struct Passenger));
        temp = temp->next;
        temp->next = NULL;

        printf("\nEnter passport number: ");
        fgets(temp->passport, MAX_PASSPORT_LEN, stdin);
        printf("Enter name: ");
        fgets(temp->name, MAX_NAME_LEN, stdin);
        printf("Enter email: ");
        fgets(temp->email, MAX_EMAIL_LEN, stdin);
        printf("Enter destination: ");
        fgets(temp->destination, MAX_DESTINATION_LEN, stdin);
        temp->seatNum = seatNum;

        printf("\nSeat booking successful!\n");
    }
    else
    {
        head = (struct Passenger *)malloc(sizeof(struct Passenger));
        head->next = NULL;

        printf("\nEnter passport number: ");
        fgets(head->passport, MAX_PASSPORT_LEN, stdin);
        printf("Enter name: ");
        fgets(head->name, MAX_NAME_LEN, stdin);
        printf("Enter email: ");
        fgets(head->email, MAX_EMAIL_LEN, stdin);
        printf("Enter destination: ");
        fgets(head->destination, MAX_DESTINATION_LEN, stdin);
        head->seatNum = seatNum;

        printf("\nSeat booking successful!\n");
    }
}

void cancelReservation()
{
    if (head == NULL)
    {
        printf("No reservations to cancel.\n");
        return;
    }

    char passport[MAX_PASSPORT_LEN];
    printf("Enter passport number to cancel reservation: ");
    fgets(passport, MAX_PASSPORT_LEN, stdin);
    clearInputBuffer();

    struct Passenger *current = head;
    struct Passenger *previous = NULL;

    while (current != NULL)
    {
        if (strcmp(current->passport, passport) == 0)
        {
            if (previous == NULL)
            {
                head = current->next;
            }
            else
            {
                previous->next = current->next;
            }
            free(current);
            printf("Reservation has been canceled.\n");
            return;
        }
        previous = current;
        current = current->next;
    }

    printf("No reservation found with the given passport number.\n");
}

void displayAllPassengers()
{
    struct Passenger *current = head;
    while (current != NULL)
    {
        displayPassenger(current);
        current = current->next;
    }
}

void saveToFile()
{
    FILE *file = fopen("passenger_records.txt", "w");
    if (file == NULL)
    {
        printf("Error opening file for writing.\n");
        return;
    }

    struct Passenger *current = head;
    while (current != NULL)
    {
        fprintf(file, "%s,%s,%s,A-%d,%s\n", current->passport, current->name, current->destination, current->seatNum, current->email);
        current = current->next;
    }

    fclose(file);
    printf("Passenger records saved to file.\n");
}

int main()
{
    int choice;
    int seatNum = 1;

    do
    {
        printf("\n\n\t\t ***************************************************");
        printf("\n\t\t            Welcome To JetHorizon Airlines Booking     ");
        printf("\n\t\t ***************************************************");
        printf("\n\n\n\t\t Please enter your choice from below (1-4):");
        printf("\n\n\t\t 1. Book a Seat");
        printf("\n\n\t\t 2. Cancel Reservation");
        printf("\n\n\t\t 3. Display Passengers");
        printf("\n\n\t\t 4. Exit");
        printf("\n\n\t\t Enter your choice: ");
        scanf("%d", &choice);
        clearInputBuffer();

        switch (choice)
        {
        case 1:
            if (seatNum <= MAX_SEATS)
            {
                reserveSeat(seatNum);
                seatNum++;
            }
            else
            {
                printf("All seats are booked.\n");
            }
            break;

        case 2:
            cancelReservation();
            break;

        case 3:
            displayAllPassengers();
            break;

        case 4:
            saveToFile();
            printf("Thank you for using JetHorizon Airlines booking system.\n");
            break;

        default:
            printf("Invalid choice. Please choose from 1-4.\n");
        }
    } while (choice != 4);

    struct Passenger *current = head;
    while (current != NULL)
    {
        struct Passenger *next = current->next;
        free(current);
        current = next;
    }

    return 0;
}

