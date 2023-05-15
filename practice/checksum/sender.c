#include <stdio.h>
#include <string.h>

#define SIZE 500

int main(void)
{
    char dataword[SIZE];
    printf("Dataword: ");
    scanf("%s", dataword);
    int n = strlen(dataword);

    int slen = 0;
    printf("Segment Length: ");
    scanf("%d", &slen);

    int rem = n % slen;
    if (rem) {  // do the necessary padding
        char temp[n];
        strcpy(temp, dataword);
        memset(dataword, '0', rem * sizeof(char));
        strcpy(dataword + rem, temp);
        n += rem;
    }

    char buffer[slen];
    strncpy(buffer, dataword, slen);
    buffer[slen] = '\0';

    for (int i = slen; i + slen <= n; i += slen) {
        int carry = 0;
        for (int j = slen - 1; j >= 0; --j) {
            int a = buffer[j] - '0';
            int b = dataword[i + j] - '0';
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

    for (int i = 0; i < slen; ++i)
        buffer[i] = buffer[i] == '1' ? '0' : '1';

    printf("Checksum: %s\n", buffer);
    char codeword[n + slen];
    strcpy(codeword, dataword);
    strcat(codeword, buffer);
    codeword[n + slen] = '\0';
    printf("Codeword: %s\n", codeword);

    return 0;
}