#ifndef TRANSACTION_H
#define TRANSACTION_H

typedef struct {
    int transactionID;
    int type; // withdrawal, deposit, transfer
    double amount;
    char date[20];
    char time[20];
} Transaction;

void recordTransaction(int cardNumber, Transaction transaction);
Transaction* fetchTransactionHistory(int cardNumber);

#endif
