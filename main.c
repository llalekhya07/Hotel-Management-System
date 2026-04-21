#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hotel.h"


int main() {

    //login to access details
    if(!login()) {
        return 0;   
    }

    int choice;

    while(1) {
        printf("\n===== HOTEL MANAGEMENT SYSTEM =====\n");
        printf("1. Customer Check-in\n");
        printf("2. Customer Check-out\n");
        printf("3. Display Customers\n");
        printf("4. Display Customers History\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                checkin();
                break;
            case 2:
                checkout();
                break;
            case 3:
                displayCustomers();
                break; 
            case 4:
                displayCustomerHistory();
                break;    
            case 5:
                exit(0);
                break;              
            default:
                printf("\nXXXXXXXX INVALID CHOICE XXXXXXXX\n");
        }
    }

    return 0;
}

