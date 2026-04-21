# Hotel-Management-System

A console-based Hotel Management System developed in C that simulates real-world hotel operations such as booking, checkout, billing, and customer management. The system is designed using file handling and modular programming to ensure efficient data storage and retrieval.

Employee Authentication:
Secure login system using employee.csv
Limited login attempts for security

Room Booking (Check-in):
AC (A, B, C) and Non-AC (D, E) room categorization
Automatic room allocation based on availability

Input validation for dates and customer details:
Auto calculation of stay duration

Billing System:

Room charges based on type and duration:

Food selection (Veg / Non-Veg with multiple meal options):

Automatic bill calculation:

Smart Pricing:
Discount system for stays longer than 5 days
Loyalty system for returning customers

Room Cleaning Management:
Rooms marked dirty after checkout
Booking allowed only if room is clean

Ensures realistic hotel workflow:

Checkout System:
Displays customer details before checkout
Confirmation-based checkout process

Customer rating collection (1–5):
Stores completed records in checkout.txt

Data Management:
Active bookings stored in hotel.txt
Checkout history stored in checkout.txt
Average rating and total revenue calculated dynamically

Display Features:
View all current customers
View complete booking history
Displays total income and average ratings

Technologies Used:
C Programming
File Handling (.txt, .csv)
Modular Programming (.h, .c files)
Makefile (for compilation)

Concepts Implemented:
Structures
File I/O (binary & text)
Data validation
Modular design
Basic authentication system
