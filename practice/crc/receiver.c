#include <stdio.h>
#include <string.h>

#define SIZE 500

int main(void)
{
    char codeword[SIZE];
    printf("Codeword: ");
    scanf("%s", codeword);
    int n = strlen(codeword);

    char polynomial[SIZE];
    printf("Coefficients of generator polynomial: ");
    scanf("%s", polynomial);
    int k = strlen(polynomial);

    char buffer[k];
    strncpy(buffer, codeword, k);
    buffer[k] = '\0';

    for (int i = k; i < n + 1; ++i) {
        int r = buffer[0] - '0';
        for (int j = 1; j < k; ++j)
            buffer[j - 1] = '0' + (r * (polynomial[j] - '0')) ^ (buffer[j] - '0');
        buffer[k - 1] = codeword[i];
    }

    for (int i = 0; i < k - 1; ++i) {
        if (buffer[i] == '1') {
            printf("Codeword Rejected.\n");
            return -1;
        }
    }

    printf("Codeword accepted.\n");
    char dataword[SIZE];
    strncpy(dataword, codeword, n - k + 1);
    dataword[n - k + 1] = '\0';
    printf("Dataword: %s\n", dataword);

    return 0;
}