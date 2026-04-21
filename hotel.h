#ifndef HOTEL_H
#define HOTEL_H

#include <stdio.h>

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

// function declarations

int login();

int isSeriesFull(char series);
int isRoomBooked(char series, int room);
int getNextRoom(char series);

int isValidDate(char checkin[], char checkout[]);
int calculateDays(char checkin[], char checkout[]);

int isReturningCustomer(char phone[]);

int isRoomClean(char series, int room);
void updateCleaningStatus(char series, int room, int newStatus);

void checkin();
void checkout();

void displayCustomers();
void displayCustomerHistory();

#endif