#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

void encode(FILE* from, FILE* to, uint8_t* hash) {

    int n_ending_zero = 0;
    int encode_i = 0;
    uint8_t encoded = 0;

    while (1) {

        int src_byte = fgetc(from);
        if (src_byte == EOF) {
            if (encode_i != 0) {
                fputc(encoded, to);
            }
            return;
        }

        for (int i = 0; i < 8; i++) {
            unsigned bit = (src_byte >> (7 - i)) & 01;

            if (i == 0) {
                // dicard first bit
                n_ending_zero++;
            } else {
                // append bit
                encoded |= (bit << (7 - encode_i));
                encode_i++;

                if (encode_i == 8) {
                    encode_i = 0;
                    encoded = 0;
                    fputc(encoded, to);
                }
            }
        }
    }
}

int main(int argc, char const *argv[])
{
    FILE* from = fopen("from", "w+");
    fprintf(from, "%c", 0b01001000);
    fprintf(from, "%c", 0b01011000);
    rewind(from);

    FILE* to = fopen("to", "w");

    encode(from, to, NULL);

    fclose(from);
    fclose(to);

    to = fopen("to", "r");
    int ch;
    ch = fgetc(to);
    printf("%x\n", ch);
    ch = fgetc(to);
    printf("%x\n", ch);
    return 0;
}
