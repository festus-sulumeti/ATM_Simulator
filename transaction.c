#include <stdio.h>
#include <stdlib.h>
#include "transaction.h"
#include "database.h"

/**
 * Records a transaction in the database.
 *
 * @param cardNumber The card number associated with the transaction.
 * @param transaction The transaction to record.
 */
void recordTransaction(int cardNumber, Transaction transaction) {
    // Record the transaction in the database
    insertTransactionToDatabase(cardNumber, transaction);
}

Transaction* fetchTransactionHistory(int cardNumber) {
    // Retrieve the transaction history for the account from the database
    return fetchTransactionHistoryFromDatabase(cardNumber);
}
