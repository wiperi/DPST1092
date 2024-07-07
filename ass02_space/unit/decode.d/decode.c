#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

uint8_t cut_head(uint8_t ch, int head_len) {
    return (ch >> (8 - head_len));
}

uint8_t cut_body(uint8_t ch, int body_len) {
    uint32_t mask = (1 << body_len) - 1;
    return (ch & mask) << (7 - body_len);
}

void decode(FILE* from, FILE* to, int head_len, uint8_t head, uint8_t body) {

    int body_len = 8 - head_len;

    int ch = fgetc(from);
    if (ch == EOF) {
        return;
    }

    head = cut_head(ch, head_len);
    printf("%x\n", head);

    fputc(head | body, to);

    body = cut_body(ch, body_len);
    printf("%x\n", body);

    if (body_len == 7) {
        fputc(head | body, to);
        decode(from, to, 7, 0, 0);
    } else {
        decode(from, to , head_len - 1, head, body);
    }
}

int main(int argc, char const *argv[])
{
    FILE* from = fopen("from", "w+");
    fprintf(from, "%c", 'a');
    fprintf(from, "%c", 'a');
    rewind(from);

    FILE* to = fopen("to", "w");

    decode(from, to, 7, 0, 0);

    return 0;
}
