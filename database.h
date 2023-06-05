#ifndef DATABASE_H
#define DATABASE_H

#include "account.h"
#include "transaction.h"
#include <sqlite3.h>

typedef struct {
    sqlite3* db;
} Database;

Database* connectDatabase();
void closeDatabase(Database* db);
Account fetchAccountFromDatabase(int cardNumber);
void updateAccountBalanceInDatabase(Account account);
void insertTransactionToDatabase(int cardNumber, Transaction transaction);
Transaction* fetchTransactionHistoryFromDatabase(int cardNumber);

#endif
