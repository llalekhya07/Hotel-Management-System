#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hotel.h"


struct Hotel{
    char name[50];
    char contact[20];
    char series;
    int roomno;
    int days;
    char checkin[20];
    char checkout[20];
    int roombill;
    int foodpref;
    int foodbill;
    int rating;
    int totalbill;
};


//login
int login() {
    char username[50], password[50];
    char name[100], fileUser[50], filePass[50];
    FILE *fp;

    int attempts = 3;

    while(attempts--) {

        printf("\n===== EMPLOYEE LOGIN =====\n");

        printf("Username: ");
        scanf("%s", username);

        printf("Password: ");
        scanf("%s", password);

        fp = fopen("employee.csv", "r");

        if(fp == NULL) {
            printf("File error!\n");
            return 0;
        }

        int success = 0;

        while(fscanf(fp, "%[^,],%[^,],%s", name, fileUser, filePass) != EOF) {

            if(strcmp(username, fileUser) == 0 &&
               strcmp(password, filePass) == 0) {

                printf("\nLogin Successful!\n");
                printf("Welcome, %s\n", name);

                success = 1;
                break;
            }
        }

        fclose(fp);

        if(success)
            return 1;

        printf("\n Invalid Username or Password!\n");
        printf("Attempts left: %d\n", attempts);
    }

    printf("\n Too many failed attempts! Access denied.\n");
    return 0;
}


//series
int isSeriesFull(char series) {
    struct Hotel h;
    FILE *fp;
    int count = 0;

    fp = fopen("hotel.txt", "r");

    if(fp != NULL) {
        while(fread(&h, sizeof(h), 1, fp)) {
            if(h.series == series) {
                count++;
            }
        }
        fclose(fp);
    }

    if(count<20) return 0;
    if(count>=20) return 1;
}


//isroomempty
int isRoomBooked(char series, int room) {

    struct Hotel h;
    FILE *fp = fopen("hotel.txt", "r");

    if(fp == NULL)
        return 0;

    while(fread(&h, sizeof(h), 1, fp)) {
        if(h.series == series && h.roomno == room) {
            fclose(fp);
            return 1; 
        }
    }

    fclose(fp);
    return 0; 
}


//Room allocation in order
int getNextRoom(char series) {
    int i;

    for(i = 1; i <= 20; i++) {
        if(!isRoomBooked(series, i)) {
            return i;  // first free room
        }
    }

    return -1; // full
}


//datevalidation
int isValidDate(char checkin[], char checkout[]) {
    int d1, m1, y1;
    int d2, m2, y2;

    sscanf(checkin, "%d-%d-%d", &d1, &m1, &y1);
    sscanf(checkout, "%d-%d-%d", &d2, &m2, &y2);

    if(y2 > y1) return 1;
    if(y2 == y1 && m2 > m1) return 1;
    if(y2 == y1 && m2 == m1 && d2 > d1) return 1;

    return 0; // invalid
}

//days
int calculateDays(char checkin[], char checkout[]) {
    int d1, m1, y1;
    int d2, m2, y2;

    sscanf(checkin, "%d-%d-%d", &d1, &m1, &y1);
    sscanf(checkout, "%d-%d-%d", &d2, &m2, &y2);

    // convert everything to total days (simple approximation)
    int total1 = y1*365 + m1*30 + d1;
    int total2 = y2*365 + m2*30 + d2;

    return total2 - total1;
}


//returncustomer
int isReturningCustomer(char phone[]) {
    struct Hotel h;
    FILE *fp = fopen("checkout.txt", "r");

    if(fp == NULL)
        return 0;

    while(fread(&h, sizeof(h), 1, fp)) {
        if(strcmp(h.contact, phone) == 0) {
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    return 0;
}


//checkoutclean
int isRoomClean(char series, int room) {
    FILE *fp = fopen("cleaning.txt", "r");
    char s;
    int r, status;

    if(fp == NULL)
        return 1;

    while(fscanf(fp, " %c %d %d", &s, &r, &status) != EOF) {
        if(s == series && r == room) {
            fclose(fp);
            return status == 0;
        }
    }

    fclose(fp);
    return 1;
}


//clean
void updateCleaningStatus(char series, int room, int newStatus) {
    FILE *fp = fopen("cleaning.txt", "r");
    FILE *temp = fopen("temp.txt", "w");

    char s;
    int r, status;
    int found = 0;

    if(fp != NULL) {
        while(fscanf(fp, " %c %d %d", &s, &r, &status) != EOF) {
            if(s == series && r == room) {
                status = newStatus;
                found = 1;
            }
            fprintf(temp, "%c %d %d\n", s, r, status);
        }
        fclose(fp);
    }

    if(!found)
        fprintf(temp, "%c %d %d\n", series, room, newStatus);

    fclose(temp);

    remove("cleaning.txt");
    rename("temp.txt", "cleaning.txt");
}


//checkin
void checkin() {
    struct Hotel h;
    FILE *fp1;
    int choice;

    printf("1.AC\n");
    printf("2.Non-AC\n");
    printf("Price is 2000/- per day for AC\n ");
    printf("Price is 1700/- per day for Non-AC\n ");
    printf("Enter Choice: ");
    scanf("%d", &choice);

    getchar();


    if(choice == 1) {
        
        int available = 0;

        printf("Available AC Series: ");

        if(!isSeriesFull('A')) { printf("A "); available = 1; }
        if(!isSeriesFull('B')) { printf("B "); available = 1; }
        if(!isSeriesFull('C')) { printf("C "); available = 1; }

        if(!available)
        printf("No AC rooms available");

        printf("\n");

        h.roombill = 2000;
        printf("\n");
    }
    if(choice == 2) {
        printf("Available Non-AC Series: ");

        int available = 0;

        if(!isSeriesFull('D')) { printf("D "); available = 1; }
        if(!isSeriesFull('E')) { printf("E "); available = 1; }

        if(!available)
            printf("No Non-AC rooms available");

        printf("\n");

        h.roombill = 1700;
        printf("\n");
    }
    if(choice<1 || choice>2){
        printf("\nXXXXXXXX INVALID CHOICE XXXXXXXX\n");
        return;
    }

    while(1) {
        printf("Enter Series: ");
        scanf(" %c", &h.series);

    // convert to uppercase
        if(h.series >= 'a' && h.series <= 'z') {
            h.series = h.series - 32;
        }

        if(choice == 1) {   // AC rooms
            if(h.series=='A' || h.series=='B' || h.series=='C') {
                break;
            }
            else {
                printf("\nXXXXXXXX INVALID SERIES FOR AC XXXXXXXX\n");
            }
        }

        else if(choice == 2) {   // Non-AC rooms
            if(h.series=='D' || h.series=='E') {
                break;
            }
            else {
                printf("\nXXXXXXXX INVALID SERIES FOR NON-AC XXXXXXXX\n");
            }
        }
    }


    h.roomno = getNextRoom(h.series);

    if(h.roomno == -1) {
    printf("\nXXXXXXXX NO ROOMS AVAILABLE XXXXXXXX\n");
    return;
    }

    if(!isRoomClean(h.series, h.roomno)) {
        printf("Room is dirty! Clean before booking.\n");
        return;
    }

    printf("Room Allocated: %c_%d\n", h.series, h.roomno);

    getchar();

    printf("Enter Name: ");
    fgets(h.name, sizeof(h.name), stdin);
    h.name[strcspn(h.name, "\n")] = 0;

    printf("Enter Contact Number: ");
    fgets(h.contact, sizeof(h.contact), stdin);
    h.contact[strcspn(h.contact, "\n")] = 0;

    printf("\nYou will get 10 percent discount if days of stay is more than 5\n");

    char temp[20];

    while(1) {
        printf("Enter Check-in Date (dd-mm-yyyy): ");
        fgets(h.checkin, sizeof(h.checkin), stdin);
        h.checkin[strcspn(h.checkin, "\n")] = 0;

        printf("Enter Check-out Date (dd-mm-yyyy): ");
        fgets(h.checkout, sizeof(h.checkout), stdin);
        h.checkout[strcspn(h.checkout, "\n")] = 0;

        if(isValidDate(h.checkin, h.checkout))
            break;

        printf("Invalid! Check-out must be after check-in.\n");
    }

    h.days = calculateDays(h.checkin, h.checkout);

    if(h.days <= 0) {
    printf("Invalid stay duration!\n");
    return;
    }

    printf("Total Days: %d\n", h.days);

    h.roombill = h.roombill*h.days;

    printf("\nRoom Booking Successful!\n");
    printf("Room Bill = %d\n", h.roombill);

    printf("------------------\n");

    printf("Food Preference:\n");
    printf("0. Not Required\n");
    printf("1. Veg\n");
    printf("2. Non-Veg\n");

    while(1) {
        printf("Enter choice: ");
        fgets(temp, sizeof(temp), stdin);
        sscanf(temp, "%d", &h.foodpref);

        if(h.foodpref >= 0 && h.foodpref <= 2)
            break;

        printf("\nXXXXXXXX INVALID CHOICE XXXXXXXX\n");
    }

    h.foodbill = 0;


    if(!h.foodpref){
        h.foodbill = 0;
    }

    else {
        int foodslot;

        printf("Food Slots:\n");
        printf("1: Breakfast\n");
        printf("2: Lunch\n");
        printf("3: Dinner\n");
        printf("4: Breakfast + Lunch\n");
        printf("5: Breakfast + Dinner\n");
        printf("6: Lunch + Dinner\n");
        printf("7: All Meals\n");

        while(1) {
            printf("Enter choice: ");
            fgets(temp, sizeof(temp), stdin);
            sscanf(temp, "%d", &foodslot);

            if(foodslot >= 1 && foodslot <= 7)
                break;

            printf("\nXXXXXXXX INVALID CHOICE XXXXXXXX\n");
        }

    // Veg pricing
        if(h.foodpref == 1) {
            int price[] = {0,160,300,250,450,400,550,700};
            h.foodbill = price[foodslot];
        }

    // Non-Veg pricing
        else if(h.foodpref == 2) {
            int price[] = {0,160,350,300,500,450,650,800};
            h.foodbill = price[foodslot];
        }

        printf("\nFood Booking Successful!\n");
    }

    h.rating = 0;
    h.foodbill = h.foodbill*h.days;

    printf("Food Bill: %d\n", h.foodbill);
    printf("----------------------\n");
    printf("\nBooking Successful!\n");

    h.totalbill = h.roombill + h.foodbill;
    if(h.days > 5) {
        int discount = h.totalbill * 0.10;
        h.totalbill -= discount;

        printf("\nDay Discount Applied: %d\n", discount);
    }

    if(isReturningCustomer(h.contact)) {
        printf("\n Returning Customer Discount Applied!\n");
        h.totalbill = h.totalbill * 0.9;  // 10% off
    }

    printf("Total Bill: %d\n", h.totalbill);
    printf("----------------------\n");


    fp1 = fopen("hotel.txt", "a");

    if(fp1 == NULL) {
        printf("File error!\n");
        return;
    }

    printf("\nSaving booking details...\n");

    fwrite(&h, sizeof(h), 1, fp1);

    fclose(fp1);

}

//checkout
void checkout() {
    struct Hotel h;
    FILE *fp, *temp, *checkout_file;
    char series;
    int room;
    int found = 0;
    char confirm;

    while(1) {
        printf("Enter Series: ");
        scanf(" %c", &series);

        // convert to uppercase
        if(series >= 'a' && series <= 'z') {
            series = series - 32;
        }

        if(series=='A' || series=='B' || series=='C'|| series=='D' || series=='E'){
            break;
        }
        else{
            printf("XXXXXXXX INVALID CHARACTER XXXXXXXX\n");
        }
    }

    printf("Enter Room Number: ");
    scanf("%d", &room);

    fp = fopen("hotel.txt", "r");
    temp = fopen("temp.txt", "w");
    checkout_file = fopen("checkout.txt", "a");

    if(fp == NULL || temp == NULL || checkout_file == NULL) {
        printf("File error!\n");
        return;
    }

    while(fread(&h, sizeof(h), 1, fp)) {

        if(h.series == series && h.roomno == room) {

            found = 1;

            //SHOW DETAILS
            printf("\nCustomer Found:\n");
            printf("Name   : %s\n", h.name);
            printf("Room   : %c_%d\n", h.series, h.roomno);
            printf("Days   : %d\n", h.days);
            printf("Total Bill : %d\n", h.totalbill);

            // CONFIRMATION
            printf("\nConfirm checkout? (Y/N): ");
            scanf(" %c", &confirm);

            if(confirm == 'Y' || confirm == 'y') {

                char tempInput[10];
                getchar(); // clear buffer before fgets

                // RATING
                printf("Rate our services (1 - 5): ");

                while(1) {
                    fgets(tempInput, sizeof(tempInput), stdin);
                    sscanf(tempInput, "%d", &h.rating);

                    if(h.rating >= 1 && h.rating <= 5)
                        break;

                    printf("Invalid rating! Enter between 1-5: ");
                }

                updateCleaningStatus(h.series, h.roomno, 1);

                //save to history
                fwrite(&h, sizeof(h), 1, checkout_file);

                printf("\nCustomer checked out successfully!\n");
            }
            else {
                //cancelled → keep record
                fwrite(&h, sizeof(h), 1, temp);
                printf("\nCheckout cancelled!\n");
            }

        } 
        else {
            fwrite(&h, sizeof(h), 1, temp);
        }
    }

    fclose(fp);
    fclose(temp);
    fclose(checkout_file);

    remove("hotel.txt");           
    rename("temp.txt", "hotel.txt");

    if(!found)
        printf("Record not found!\n");
}


//displaying current custoners
void displayCustomers() {
    struct Hotel h;
    FILE *fp;

    fp = fopen("hotel.txt", "r");

    if(fp == NULL) {
        printf("No records found!\n");
        return;
    }

    printf("\n===== CURRENT BOOKINGS ======\n");

    while(fread(&h, sizeof(h), 1, fp)) {
        printf("\nSeries    : %c", h.series);
        printf("\nRoom      : %d", h.roomno);
        printf("\nName      : %s", h.name);
        printf("\nPhone     : %s", h.contact);
        printf("\nDays      : %d", h.days);
        printf("\nCheck-in  : %s", h.checkin);
        printf("\nCheck-out : %s", h.checkout);
        printf("\nRoom Bill : %d", h.roombill);
        printf("\nFood Bill : %d", h.foodbill);
        printf("\nTotal Bill: %d", h.totalbill);
        printf("\n---------------------------\n");
    }

    fclose(fp);
}


//display all history
void displayCustomerHistory() {
    struct Hotel h;
    FILE *fp;
    int total = 0;
    int totalRating = 0;
    int count = 0;

    fp = fopen("checkout.txt", "r");

    if(fp == NULL) {
        printf("No records found!\n");
        return;
    }

    printf("\n===== BOOKING HISTORY =====\n");

    while(fread(&h, sizeof(h), 1, fp)) {
        printf("\nSeries    : %c", h.series);
        printf("\nRoom      : %d", h.roomno);
        printf("\nName      : %s", h.name);
        printf("\nPhone     : %s", h.contact);
        printf("\nDays      : %d", h.days);
        printf("\nCheck-in  : %s", h.checkin);
        printf("\nCheck-out : %s", h.checkout);
        printf("\nRoom Bill : %d", h.roombill);
        printf("\nFood Bill : %d", h.foodbill);
        printf("\nTotal Bill: %d", h.totalbill);
        printf("\nRating    : %d", h.rating);

        printf("\n---------------------------\n");
        total = total+h.totalbill;
        totalRating += h.rating;
        count++;
    }
    printf("Total income = %d\n", total);

    if(count > 0) {
        float avg = (float)totalRating / count;
        printf("\nAverage Rating: %.2f\n", avg);
    } else {
        printf("\nNo ratings available.\n");
    }


    printf("\n---------------------------\n");


    fclose(fp);
}