// Reads a 4-byte value and reverses the byte order, then prints it

#include <stdint.h>
#include <stdio.h>

#define BYTE_MASK 0xFF

int main(void) {
    int32_t network_bytes;
    scanf("%d", &network_bytes);

    int32_t computer_bytes = 0;
    uint32_t byte_mask = BYTE_MASK;

    computer_bytes |= (network_bytes & byte_mask) << 24;
    computer_bytes |= (network_bytes & (byte_mask << 8)) << 8;
    computer_bytes |= (network_bytes & (byte_mask << 16)) >> 8;
    computer_bytes |= (network_bytes & (byte_mask << 24)) >> 24;

    printf("%d\n", computer_bytes);

    return 0;
}

int simplified() {
    int32_t s0;
    scanf("%d", &s0);

    int32_t s1 = 0;
    uint32_t s2 = BYTE_MASK;

    s1 |= (s0 & s2) << 24;
    s1 |= (s0 & (s2 << 8)) << 8;
    s1 |= (s0 & (s2 << 16)) >> 8;
    s1 |= (s0 & (s2 << 24)) >> 24;

    printf("%d\n", s1);

    return 0;
}
