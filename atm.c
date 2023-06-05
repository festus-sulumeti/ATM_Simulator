#include <stdio.h>
#include "atm.h"
#include "account.h"
#include "transaction.h"
#include "database.h"

void displayMainMenu() {
    /*Display the main menu options*/
    printf("Main Menu:\n");
    printf("1. Display Balance\n");
    printf("2. Withdraw Funds\n");
    printf("3. Deposit Funds\n");
    printf("4. Transfer Funds\n");
    printf("5. Change PIN\n");
    printf("6. Display Transaction History\n");
    printf("7. Logout\n");
}

int authenticateUser(int cardNumber, int pin) {
     Account account = fetchAccountFromDatabase(cardNumber);
    if (account.cardNumber == cardNumber && account.pin == pin) {
        return 1; // Authentication successful
    } else {
        return 0; // Authentication failed
    }
}

void displayBalance(int cardNumber) {
    Account account = fetchAccount(cardNumber);
    printf("Account Balance: $%.2lf\n", account.balance);
}

void withdrawFunds(int cardNumber, double amount) {
    Account account = fetchAccount(cardNumber);
    
    // Check if sufficient balance is available
    if (account.balance >= amount) {
        account.balance -= amount;
        updateAccountBalance(account);
        printf("Amount $%.2lf withdrawn successfully.\n", amount);
        
        // Record the transaction
        Transaction transaction;
        // Set transaction details
        recordTransaction(cardNumber, transaction);
    } else {
        printf("Insufficient balance.\n");
    }
}

void depositFunds(int cardNumber, double amount) {
    Account account = fetchAccount(cardNumber);
    
    account.balance += amount;
    updateAccountBalance(account);
    printf("Amount $%.2lf deposited successfully.\n", amount);
    
    // Record the transaction
    Transaction transaction;
    // Set transaction details
    recordTransaction(cardNumber, transaction);
}

void transferFunds(int cardNumber, int targetAccount, double amount) {
    Account account = fetchAccount(cardNumber);
    Account target = fetchAccount(targetAccount);
    
    // Check if sufficient balance is available for transfer
    if (account.balance >= amount) {
        account.balance -= amount;
        target.balance += amount;
        updateAccountBalance(account);
        updateAccountBalance(target);
        printf("Amount $%.2lf transferred successfully to Account %d.\n", amount, targetAccount);
        
        // Record the transaction for both accounts
        Transaction transactionFrom;
        Transaction transactionTo;
        // Set transaction details
        recordTransaction(cardNumber, transactionFrom);
        recordTransaction(targetAccount, transactionTo);
    } else {
        printf("Insufficient balance for transfer.\n");
    }
}

void changePIN(int cardNumber, int newPIN) {
    Account account = fetchAccount(cardNumber);
    account.pin = newPIN;
    updateAccountBalance(account);
    printf("PIN changed successfully.\n");
    
    // Record the transaction
    Transaction transaction;
    // Set transaction details
    recordTransaction(cardNumber, transaction);
}

void displayTransactionHistory(int cardNumber) {
    Account account = fetchAccount(cardNumber);
    
    // Retrieve and display transaction history for the account
    Transaction* transactions = fetchTransactionHistory(cardNumber);
    // Display transaction details
}

void logout() {
    // Perform logout operations
      // Perform any necessary cleanup or logging out procedures
    
    // Clear the card number and PIN
    cardNumber = 0;
    pin = 0;
    
    // Display a goodbye message
    printf("You have successfully logged out. Goodbye!\n");
}
