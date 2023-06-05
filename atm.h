#ifndef ATM_H
#define ATM_H

#include "account.h"
#include "transaction.h"

void displayMainMenu();
int authenticateUser(int cardNumber, int pin);
void displayBalance(int cardNumber);
void withdrawFunds(int cardNumber, double amount);
void depositFunds(int cardNumber, double amount);
void transferFunds(int cardNumber, int targetAccount, double amount);
void changePIN(int cardNumber, int newPIN);
void displayTransactionHistory(int cardNumber);
void logout();

#endif
