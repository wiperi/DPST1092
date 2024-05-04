//! simple example which launches two threads of execution
//! which increment a global variable

#include <pthread.h>
#include <stdio.h>

int andrews_bank_account = 200;
pthread_mutex_t andrews_bank_account_lock = PTHREAD_MUTEX_INITIALIZER;

int xaviers_bank_account = 100;
pthread_mutex_t xaviers_bank_account_lock = PTHREAD_MUTEX_INITIALIZER;

// Andrew sends Xavier all his money dollar by dollar
void *andrew_send_xavier_money(void *argument) {
    for (int i = 0; i < 100000; i++) {
        pthread_mutex_lock(&andrews_bank_account_lock);
        pthread_mutex_lock(&xaviers_bank_account_lock);

        if (andrews_bank_account > 0) {
            andrews_bank_account--;
            xaviers_bank_account++;
        }

        pthread_mutex_unlock(&xaviers_bank_account_lock);
        pthread_mutex_unlock(&andrews_bank_account_lock);
    }

    return NULL;
}

// Xavier sends Andrew all his money dollar by dollar
void *xavier_send_andrew_money(void *argument) {
    for (int i = 0; i < 100000; i++) {
        pthread_mutex_lock(&xaviers_bank_account_lock);
        pthread_mutex_lock(&andrews_bank_account_lock);

        if (xaviers_bank_account > 0) {
            xaviers_bank_account--;
            andrews_bank_account++;
        }

        pthread_mutex_unlock(&andrews_bank_account_lock);
        pthread_mutex_unlock(&xaviers_bank_account_lock);
    }

    return NULL;
}

int main(void) {
    // create two threads sending each other money

    pthread_t thread_id1;
    pthread_create(&thread_id1, NULL, andrew_send_xavier_money, NULL);

    pthread_t thread_id2;
    pthread_create(&thread_id2, NULL, xavier_send_andrew_money, NULL);

    // threads will probably never finish
    // deadlock will likely likely occur
    // with one thread holding  andrews_bank_account_lock
    // and waiting for xaviers_bank_account_lock
    // and the other thread holding  xaviers_bank_account_lock
    // and waiting for andrews_bank_account_lock

    pthread_join(thread_id1, NULL);
    pthread_join(thread_id2, NULL);

    return 0;
}
