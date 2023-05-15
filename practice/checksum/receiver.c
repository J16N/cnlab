#include <stdio.h>
#include <string.h>

#define SIZE 500

int main(void)
{
    char codeword[SIZE];
    printf("Codeword: ");
    scanf("%s", codeword);
    int n = strlen(codeword);

    int slen = 0;
    printf("Segment Length: ");
    scanf("%d", &slen);

    int rem = n % slen;
    if (rem) {
        printf("Codeword rejected.\n");
        return -1;
    }

    char buffer[slen];
    strncpy(buffer, codeword, slen);
    buffer[slen] = '\0';

    for (int i = slen; i + slen <= n; i += slen) {
        int carry = 0;
        for (int j = slen - 1; j >= 0; --j) {
            int a = buffer[j] - '0';
            int b = codeword[i + j] - '0';
            int result = a + b + carry;

            switch (result) {
                case 0:
                    buffer[j] = '0';
                    carry = 0;
                    break;

                case 1:
                    buffer[j] = '1';
                    carry = 0;
                    break;

                case 2:
                    buffer[j] = '0';
                    carry = 1;
                    break;

                case 3:
                    buffer[j] = '1';
                    carry = 1;
                    break;
            }
        }

        for (int j = slen - 1; carry != 0 && j >= 0; --j) {
            int result = carry + (buffer[j] - '0');

            switch (result) {
                case 1:
                    buffer[j] = '1';
                    carry = 0;
                    break;

                case 2:
                    buffer[j] = '0';
                    carry = 1;
                    break;
            }
        }
    }

    for (int i = 0; i < slen; ++i) {
        if (buffer[i] == '0') {
            printf("Codeword rejected.\n");
            return -1;
        }
    }

    printf("Codeword accepted.\n");
    char dataword[n - slen];
    strncpy(dataword, codeword, n - slen);
    dataword[n - slen] = '\0';
    printf("Dataword: %s\n", dataword);

    return 0;
}