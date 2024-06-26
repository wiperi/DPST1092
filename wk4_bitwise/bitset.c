// Andrew Taylor - andrewt@unsw.edu.au
// 16/9/2019
// Represent set of small non-negative integers using bit-operations

/*```
$ dcc bitset.c print_bits.c -o bitset
$ ./bitset
Set members can be 0-63, negative number to finish
Enter set a: 1 2 4 8 16 32 -1
Enter set b: 5 4 3 33 -1
a = 0000000000000000000000000000000100000000000000010000000100010110 = 0x100010116 = 4295033110
b = 0000000000000000000000000000001000000000000000000000000000111000 = 0x200000038 = 8589934648
a = {1,2,4,8,16,32}
b = {3,4,5,33}
a union b = {1,2,3,4,5,8,16,32,33}
a intersection b = {4}
cardinality(a) = 6
is_member(42, a) = 0
```*/

#include "print_bits.h"
#include <assert.h>
#include <stdint.h>
#include <stdio.h>

typedef uint64_t set;

#define MAX_SET_MEMBER ((int) (8 * sizeof(set) - 1))
#define EMPTY_SET 0

set set_add(int x, set a);
set set_union(set a, set b);
set set_intersection(set a, set b);
int set_ismember(int x, set a);
int set_cardinality(set a);
set set_read(char* prompt);
void set_print(char* description, set a);

void print_bits_hex(char* description, set n);

int main(void) {
    printf("Set members can be 0-%d, negative number to finish\n", MAX_SET_MEMBER);
    set a = set_read("Enter set a: ");
    set b = set_read("Enter set b: ");

    print_bits_hex("a = ", a);
    print_bits_hex("b = ", b);
    set_print("a = ", a);
    set_print("b = ", b);
    set_print("a union b = ", set_union(a, b));
    set_print("a intersection b = ", set_intersection(a, b));
    printf("cardinality(a) = %d\n", set_cardinality(a));
    printf("is_member(42, a) = %d\n", (int) set_ismember(42, a));

    return 0;
}

/**
 * Adds an element to the set.
 *
 * This function adds the element 'x' to the set 'a'.
 *
 * @param x The element to be added to the set.
 * @param a The set to which the element will be added.
 * @return The updated set after adding the element.
 */
set set_add(int x, set a) {
    return a | ((set) 1 << x);
}

set set_union(set a, set b) {
    return a | b;
}

set set_intersection(set a, set b) {
    return a & b;
}

// return 1 iff x is a member of a, 0 otherwise
int set_ismember(int x, set a) {
    assert(x >= 0 && x < MAX_SET_MEMBER);
    return (a >> x) & 1;
}

// return size of set
int set_cardinality(set a) {
    int n_members = 0;
    while (a != 0) {
        n_members += a & 1;
        a >>= 1;
    }
    return n_members;
}

/**
 * Reads a set from user input.
 *
 * @param prompt The prompt message to display to the user.
 * @return The set read from user input.
 */
set set_read(char* prompt) {
    printf("%s", prompt);
    set a = EMPTY_SET;
    int x;
    while (scanf("%d", &x) == 1 && x >= 0) {
        a = set_add(x, a);
    }
    return a;
}

// print out member of the set in increasing order
// for example {5,11,56}
void set_print(char* description, set a) {
    printf("%s", description);
    printf("{");
    int n_printed = 0;
    for (int i = 0; i < MAX_SET_MEMBER; i++) {
        if (set_ismember(i, a)) {
            if (n_printed > 0) {
                printf(",");
            }
            printf("%d", i);
            n_printed++;
        }
    }
    printf("}\n");
}

// print description then binary, hex and decimal representation of value
void print_bits_hex(char* description, set value) {
    printf("%s", description);
    print_bits(value, 8 * sizeof value);
    printf(" = 0x%08jx = %jd\n", (intmax_t) value, (intmax_t) value);
}