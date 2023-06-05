#include <stdio.h>
#include <stdlib.h>
#include "database.h"

static int callback(void* data, int argc, char** argv, char** azColName) {
    return 0;
}

Database* db; 

/**
 * Connects to the database.
 *
 * @return A pointer to the connected database instance, or NULL if connection fails.
 */
Database* connectDatabase() {
    db = malloc(sizeof(Database));
    int rc = sqlite3_open(":memory:", &db->db);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db->db));
        sqlite3_close(db->db);
        return NULL;
    }

    
    char* createAccountsTableQuery = "CREATE TABLE IF NOT EXISTS Accounts (CardNumber INT, Pin INT, Balance REAL);";
    rc = sqlite3_exec(db->db, createAccountsTableQuery, callback, 0, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to create Accounts table: %s\n", sqlite3_errmsg(db->db));
        sqlite3_close(db->db);
        free(db);
        return NULL;
    }

    char* createTransactionsTableQuery = "CREATE TABLE IF NOT EXISTS Transactions (TransactionID INT, CardNumber INT, Type INT, Amount REAL, Date TEXT, Time TEXT);";
    rc = sqlite3_exec(db->db, createTransactionsTableQuery, callback, 0, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to create Transactions table: %s\n", sqlite3_errmsg(db->db));
        sqlite3_close(db->db);
        free(db);
        return NULL;
    }

    return db;
}


/**
 * Closes the database connection and performs necessary cleanup.
 *
 * @param db The database to close.
 */
void closeDatabase(Database* db) {
    if (db) {
        sqlite3_close(db->db);
        free(db);
    }
}

/**
 * Fetches an account from the database based on the card number.
 *
 * @param cardNumber The card number of the account to fetch.
 * @return The account with the specified card number.
 */
Account fetchAccountFromDatabase(int cardNumber) {
     Account account;
    char query[100];
    sprintf(query, "SELECT * FROM Accounts WHERE CardNumber = %d;", cardNumber);

    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db->db, query, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to fetch account: %s\n", sqlite3_errmsg(db->db));
        return account;
    }

    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        account.cardNumber = sqlite3_column_int(stmt, 0);
        account.pin = sqlite3_column_int(stmt, 1);
        account.balance = sqlite3_column_double(stmt, 2);
    }

    sqlite3_finalize(stmt);
    return account;
}


/**
 * Updates the account balance in the database.
 *
 * @param account The account with the updated balance.
 */
void updateAccountBalanceInDatabase(Account account) {
     char query[100];
    sprintf(query, "UPDATE Accounts SET Balance = %.2lf WHERE CardNumber = %d;", account.balance, account.cardNumber);

    int rc = sqlite3_exec(db->db, query, callback, 0, NULL);
    if (rc != SQLITE_OK) 
    {
        fprintf(stderr, "Failed to update account balance: %s\n", sqlite3_errmsg(db->db));
    }
}

/**
 * Inserts a transaction into the database.
 *
 * @param cardNumber The card number associated with the transaction.
 * @param transaction The transaction to insert.
 */
void insertTransactionToDatabase(int cardNumber, Transaction transaction) {
    char query[200];
    sprintf(query, "INSERT INTO Transactions (CardNumber, Type, Amount, Date, Time) VALUES (%d, %d, %.2lf, '%s', '%s');",
            cardNumber, transaction.type, transaction.amount, transaction.date, transaction.time);

    int rc = sqlite3_exec(db->db, query, callback, 0, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to insert transaction: %s\n", sqlite3_errmsg(db->db));
    }
}

/**
 * Fetches the transaction history for an account from the database.
 *
 * @param cardNumber The card number of the account.
 * @return An array of transactions representing the transaction history.
 *         The array is dynamically allocated and should be freed after use.
 */
Transaction* fetchTransactionHistoryFromDatabase(int cardNumber) {
   char query[100];
    sprintf(query, "SELECT * FROM Transactions WHERE CardNumber = %d;", cardNumber);

    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db->db, query, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to fetch transaction history: %s\n", sqlite3_errmsg(db->db));
        return NULL;
    }

    Transaction* transactions = malloc(100 * sizeof(Transaction));
    int count = 0;

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        transactions[count].transactionID = sqlite3_column_int(stmt, 0);
        transactions[count].type = sqlite3_column_int(stmt, 2);
        transactions[count].amount = sqlite3_column_double(stmt, 3);
        strcpy(transactions[count].date, sqlite3_column_text(stmt, 4));
        strcpy(transactions[count].time, sqlite3_column_text(stmt, 5));
        count++;
    }

    sqlite3_finalize(stmt);

    // Resize the transactions array to the actual number of transactions fetched
    transactions = realloc(transactions, count * sizeof(Transaction));

    return transactions;
}
