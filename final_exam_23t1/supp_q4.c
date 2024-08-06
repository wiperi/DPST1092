// DPST1092 23T1 ... supp exam, question 4

#include <stdint.h>

int supp_q4(uint32_t x) {
    // TODO: complete this function

    int is_window = 0;
    int win_len = 0;
    int max_len = 0;

    for (int i = 0; i < 32; i++) {
        uint32_t bit = (x >> i) & 01;

        if (bit == 1) {
            if (is_window == 0) {
                is_window = 1;
            }
            if (is_window) {
                win_len++;
            }
        } else {
            // if bit == 0
            if (!is_window) {
                ;
            }
            if (is_window) {
                if (win_len > max_len) {
                    max_len = win_len;
                }
                win_len = 0;
            }
        }
    }

    if (is_window) {
        if (win_len > max_len) {
            max_len = win_len;
        }
        win_len = 0;
    }

    return max_len;
}
