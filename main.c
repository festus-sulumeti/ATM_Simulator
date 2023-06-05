#include "atm.h"
#include <stdio.h>

/**
 * main - The current Project start
 * 
 * return: The project end 
 */
int main() {
    // Initialize the ATM system
    
    int cardNumber, pin;
    // Authenticate user and get card number and PIN

    while (1) {
        displayMainMenu();
        int choice;
        // Get user input for choice

        switch (choice) {
            case 1:
                displayBalance(cardNumber);
                break;
            case 2:
                int amount;
                // Get withdrawal amount from user
                withdrawFunds(cardNumber, amount);
                break;
            case 3:
                int amount;
                // Get deposit amount from user
                depositFunds(cardNumber, amount);
                break;
            case 4:
                int targetAccount;
                // Get target account number and transfer amount from user
                transferFunds(cardNumber, targetAccount, amount);
                break;
            case 5:
               int  newPIN;
                // Get new PIN from user
                changePIN(cardNumber, newPIN);
                break;
            case 6:
                // Show transaction history
                displayTransactionHistory(cardNumber);
                break;
            case 7:
                // Logout user
                logout();
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    }

    return 0;
}
