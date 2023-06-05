#include "account.h"
#include "database.h"

/**
 * Fetches an account from the database based on the card number.
 *
 * @param cardNumber The card number of the account to fetch.
 * @return The account with the specified card number.
 */
Account fetchAccount(int cardNumber) {
    return fetchAccountFromDatabase(cardNumber);
}

/**
 * Updates the account balance in the database.
 *
 * @param account The account to update.
 */
void updateAccountBalance(Account account) {
    updateAccountBalanceInDatabase(account);
}
