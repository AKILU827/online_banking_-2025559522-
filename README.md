Online Banking System – C Programming

Student: Paul Lubwika
Student Number: 2025559522
Course: C Programming
Institution: Rockview University
Term: 3 – January Intake


 Project Overview

This project is a fully functional Online Banking System developed in C programming.
It demonstrates core programming concepts such as:

Conditional statements

Loops

Switch-case menus

Functions

File handling

Input validation and error handling


The system allows users to register accounts, deposit/withdraw money, transfer funds, and manage their account securely.



 Objectives

Build a complete banking system using C fundamentals

Apply clean coding practices and program structure

Demonstrate mastery of functions, loops, conditions, and file handling

Implement basic authentication and user account management




 Features Implemented

 1. User Registration

Creates a new bank account

Stores:

Full Name

Account Number

Password

Initial Deposit


Saves account details to a file using file handling


 2. Login System

User enters account number + password

System validates using stored file data


 3. Deposit Funds

Deposits money into a valid account

Updates balance in real time

Writes updated balance back to file


 4. Withdraw Funds

Allows withdrawal if balance is sufficient

Updates balance

Error message for insufficient funds


 5. Online Fund Transfer

Transfer money between two registered accounts

Validates:

Source account

Destination account

Sufficient funds


Updates file after transfer

 6. Change Password

Allows secure password update

Passwords are never displayed in plain text


7. Display Account Details

Shows:

Account Holder Name

Account Number
Current Balance


Password remains hidden


 File Handling (Implemented)

This program uses file handling to:

Store account data

Load accounts at login

Update balances after transactions

Write back updated records


This ensures data persistence even when the program is closed.


 Extra Features

Login authentication

Input validation

Clear error messages

Organized menu using switch-case

Proper code commenting and indentation

./banking

On Windows (MinGW):
