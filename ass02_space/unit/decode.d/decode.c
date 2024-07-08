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

void dec(char* content, uint64_t content_len, FILE* to) {

    int head = 0;
    int body = 0;
    int head_len = 7;

    for (uint64_t i = 0; i < content_len; i++) {

        uint8_t ch = content[i];
        int body_len = 8 - head_len;

        head = cut_head(ch, head_len);

        fputc(head | body, to);

        body = cut_body(ch, body_len);

        if (body_len == 7) {
            fputc(head | body, to);
            head_len = 7;
        } else {
            head_len--;
        }
    }
}

void test_dec() {
    
    char content[] = "xx";
    uint64_t content_len = 2;

    FILE* to = fopen("to", "w");

    dec(content, content_len, to);

    fclose(to);

    to = fopen("to", "r");

    int ch;
    ch = fgetc(to);
    printf("%x\n", ch);
    ch = fgetc(to);
    printf("%x\n", ch);
}

int main(int argc, char const *argv[])
{

    // test_dec();
    // return 0;

    FILE* from = fopen("from", "w+");
    fprintf(from, "%c", 'x');
    fprintf(from, "%c", 'x');
    rewind(from);

    FILE* to = fopen("to", "w");

    decode(from, to, 7, 0, 0);

    fclose(from);
    fclose(to);

    from = fopen("to", "r");

    int ch;
    while ((ch = fgetc(from)) != EOF) {
        printf("%c", ch);
    }

    fclose(from);

    return 0;
}
