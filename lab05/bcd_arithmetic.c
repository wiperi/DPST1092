#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//
// Store an arbitray length Binary Coded Decimal number
// bcd points to an array of size n_bcd
// each array element contains 1 decimal digit
//

typedef struct big_bcd {
    unsigned char* bcd;
    int n_bcd;
} big_bcd_t;

void bcd_print(big_bcd_t* number);
void bcd_free(big_bcd_t* number);
big_bcd_t* bcd_from_string(char* string);

big_bcd_t* expression(char*** tokens);
big_bcd_t* term(char*** tokens);

int max(int a, int b) {
    if (a > b) {
        return a;
    } else {
        return b;
    }
}

int bcd_compare(big_bcd_t* x, big_bcd_t* y) {
    if (x->n_bcd > y->n_bcd) {
        return 1;
    } else if (x->n_bcd < y->n_bcd) {
        return -1;
    } else {
        for (int i = x->n_bcd - 1; i >= 0; i--) {
            if (x->bcd[i] > y->bcd[i]) {
                return 1;
            } else if (x->bcd[i] < y->bcd[i]) {
                return -1;
            }
        }
        return 0;
    }
}

int main(int argc, char* argv[]) {
    char** tokens = argv + 1;

    // tokens points in turn to each of the elements of argv
    // as the expression is evaluated.

    if (*tokens) {
        big_bcd_t* result = expression(&tokens);
        bcd_print(result);
        printf("\n");
        bcd_free(result);
    }

    return 0;
}

// DO NOT CHANGE THE CODE ABOVE HERE

big_bcd_t* bcd_add(big_bcd_t* x, big_bcd_t* y) {
    // PUT YOUR CODE HERE

    // malloc res
    big_bcd_t* res = (big_bcd_t*) malloc(sizeof(big_bcd_t));
    res->n_bcd = max(x->n_bcd, y->n_bcd);
    res->bcd = (unsigned char*) malloc(res->n_bcd * sizeof(unsigned char));

    unsigned char sum = 0, carry = 0;
    for (int i = 0; i < res->n_bcd; i++) {

        if (i < x->n_bcd && i < y->n_bcd) {
            sum = carry + x->bcd[i] + y->bcd[i];
        } else if (i < x->n_bcd) {
            sum = carry + x->bcd[i];
        } else {
            sum = carry + y->bcd[i];
        }

        res->bcd[i] = sum % 10;
        carry = sum / 10;
    }

    if (carry != 0) {
        // extend res
        res->n_bcd++;
        res->bcd = (unsigned char*) realloc(res->bcd,
                                            res->n_bcd * sizeof(unsigned char));
        assert(res->bcd);

        res->bcd[res->n_bcd - 1] = carry;
    }

    return res;
}

big_bcd_t* bcd_subtract(big_bcd_t* x, big_bcd_t* y) {
    // PUT YOUR CODE HERE

    // malloc res
    big_bcd_t* res = (big_bcd_t*) malloc(sizeof(big_bcd_t));
    res->n_bcd = max(x->n_bcd, y->n_bcd);
    res->bcd = (unsigned char*) malloc(res->n_bcd * sizeof(unsigned char));

    int sum = 0, carry = 0;
    for (int i = 0; i < res->n_bcd; i++) {

        if (i < x->n_bcd && i < y->n_bcd) {
            sum = carry + x->bcd[i] - y->bcd[i];
        } else if (i < x->n_bcd) {
            sum = carry + x->bcd[i];
        } else {
            sum = carry - y->bcd[i];
        }

        res->bcd[i] = (sum + 10) % 10;
        carry = sum < 0 ? -1 : 0;
    }

    while (res->n_bcd > 1 && res->bcd[res->n_bcd - 1] == 0) {
        // shrink res
        res->n_bcd--;
        res->bcd = (unsigned char*) realloc(res->bcd,
                                            res->n_bcd * sizeof(unsigned char));

        if (res->n_bcd > 0) assert(res->bcd);
    }

    return res;
}

big_bcd_t* bcd_multiply(big_bcd_t* x, big_bcd_t* y) {
    // PUT YOUR CODE HERE

    if (x->n_bcd == 1 && x->bcd[0] == 1) {
        return y;
    } else if (y->n_bcd == 1 && y->bcd[0] == 1) {
        return x;
    }

    big_bcd_t* res = NULL;

    // malloc for number 1
    big_bcd_t* one = (big_bcd_t*) malloc(sizeof(big_bcd_t));
    one->n_bcd = 1;
    one->bcd = (unsigned char*) malloc(1 * sizeof(unsigned char));
    one->bcd[0] = 1;

    int times = 0;
    if (x->n_bcd < y->n_bcd) {
        // x as iterator
        res = y;
        while (1) {
            // x == 0, break;
            if (x->n_bcd == 1 && x->bcd[0] == 1) break;

            if (times == 1) {
                // x -= 1
                big_bcd_t* prev_x = x;
                x = bcd_subtract(x, one);
                free(prev_x);

                big_bcd_t* prev_res = res;
                res = bcd_add(res, y);
                free(prev_res);
            } else {
                // tiems == 0
                x = bcd_subtract(x, one);
                res = bcd_add(res, y);
                times = 1;
            }
        }
    } else {
        // y as iterator
        res = x;
        while (1) {
            // y == 0, break;
            if (y->n_bcd == 1 && y->bcd[0] == 1) break;

            if (times == 1) {
                // y -= 1
                big_bcd_t* prev_y = y;
                y = bcd_subtract(y, one);
                free(prev_y);

                big_bcd_t* prev_res = res;
                res = bcd_add(res, x);
                free(prev_res);
            } else {
                // tiems == 0
                y = bcd_subtract(y, one);
                res = bcd_add(res, x);
                times = 1;
            }
        }
    }

    bcd_free(one);

    return res;
}

big_bcd_t* bcd_divide(big_bcd_t* x, big_bcd_t* y) {
    // PUT YOUR CODE HERE

    // general:
    // use substraction to implement division
    //  5 / 3 is 5 - 3 = 2, 2 - 3 = -1, abort.

    // psuedo code:
    // while (x = bcd_subtract(x, y) > 0) {
    //     res++;
    // }
    // return res;

    // res = 0;
    big_bcd_t* res = bcd_from_string("0");
    big_bcd_t* one = bcd_from_string("1");
    // deep copy x to q
    big_bcd_t* q = (big_bcd_t*) malloc(sizeof(big_bcd_t));
    q->bcd = (unsigned char*) malloc(x->n_bcd * sizeof(unsigned char));
    memcpy(q->bcd, x->bcd, x->n_bcd * sizeof(unsigned char));
    q->n_bcd = x->n_bcd;

    while (1) {

        if (bcd_compare(q, y) < 0) {
            break;
        }
        q = bcd_subtract(q, y);

        res = bcd_add(res, one);
    }

    bcd_free(one);
    bcd_free(q);
    return res;
}

// DO NOT CHANGE THE CODE BELOW HERE

// print a big_bcd_t number
void bcd_print(big_bcd_t* number) {
    // if you get an error here your bcd_arithmetic is returning an invalid
    // big_bcd_t
    assert(number->n_bcd > 0);
    for (int i = number->n_bcd - 1; i >= 0; i--) {
        putchar(number->bcd[i] + '0');
    }
}

// DO NOT CHANGE THE CODE BELOW HERE

// free storage for big_bcd_t number
void bcd_free(big_bcd_t* number) {
    // if you get an error here your bcd_arithmetic is returning an invalid
    // big_bcd_t or it is calling free for the numbers it is given
    free(number->bcd);
    free(number);
}

// convert a string to a big_bcd_t number
big_bcd_t* bcd_from_string(char* string) {
    big_bcd_t* number = malloc(sizeof *number);
    assert(number);

    int n_digits = strlen(string);
    assert(n_digits);
    number->n_bcd = n_digits;

    number->bcd = malloc(n_digits * sizeof number->bcd[0]);
    assert(number->bcd);

    for (int i = 0; i < n_digits; i++) {
        int digit = string[n_digits - i - 1];
        assert(isdigit(digit));
        number->bcd[i] = digit - '0';
    }

    return number;
}

// simple recursive descent evaluator for  big_bcd_t expressions
big_bcd_t* expression(char*** tokens) {

    big_bcd_t* left = term(tokens);
    assert(left);

    if (!**tokens || (***tokens != '+' && ***tokens != '-')) {
        return left;
    }

    char* operator= ** tokens;
    (*tokens)++;

    big_bcd_t* right = expression(tokens);
    assert(right);

    big_bcd_t* result;
    if (operator[0] == '+') {
        result = bcd_add(left, right);
    } else {
        assert(operator[0] == '-');
        result = bcd_subtract(left, right);
    }
    assert(result);

    bcd_free(left);
    bcd_free(right);
    return result;
}

// evaluate a term of a big_bcd_t expression
big_bcd_t* term(char*** tokens) {

    big_bcd_t* left = bcd_from_string(**tokens);
    assert(left);
    (*tokens)++;

    if (!**tokens || (***tokens != '*' && ***tokens != '/')) {
        return left;
    }

    char* operator= ** tokens;
    (*tokens)++;

    big_bcd_t* right = term(tokens);
    assert(right);

    big_bcd_t* result;
    if (operator[0] == '*') {
        result = bcd_multiply(left, right);
    } else {
        result = bcd_divide(left, right);
    }
    assert(result);

    bcd_free(left);
    bcd_free(right);
    return result;
}