// swap pairs of bits of a 64-bit value, using bitwise operators

#include <stdio.h>
#include <pthread.h>


void *alice_withdraw(void *data);
void *bob_withdraw(void *data);
void *alice_deposit(void *data);
void *bob_deposit(void *data);
void *alice_send_bob(void *data);
void *bob_send_alice(void *data);
int bank_account_balance(void);
int alice_wallet_balance(void);
int bob_wallet_balance(void);


int main(int argc, char *argv[]) {
    void *(*functions[])(void *) = {
        alice_withdraw, bob_withdraw,
        alice_deposit,  bob_deposit,
        alice_send_bob, bob_send_alice,
    };

    // spawn each of the six functions
    // as a thread
    pthread_t threads[6];
    for (int i = 0; i < 6; i++) {
        pthread_create(&threads[i], NULL, functions[i], NULL);
    }

    // wait for all 6 threads to finish
    for (int i = 0; i < 6; i++) {
        pthread_join(threads[i], NULL);
    }

    // print the final values out
    int bank_account_cents = bank_account_balance();
    int alice_wallet_cents = alice_wallet_balance();
    int bob_wallet_cents   = bob_wallet_balance();

    printf("bank account balance: $%d.%02d\n", bank_account_cents / 100, bank_account_cents % 100);
    printf("alice wallet balance: $%d.%02d\n", alice_wallet_cents / 100, alice_wallet_cents % 100);
    printf("bob   wallet balance: $%d.%02d\n", bob_wallet_cents   / 100, bob_wallet_cents   % 100);
}
