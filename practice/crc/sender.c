#include <stdio.h>
#include <string.h>

#define SIZE 500

int main(void)
{
    char dataword[SIZE];
    printf("Dataword: ");
    scanf("%s", dataword);
    int n = strlen(dataword);

    char polynomial[SIZE];
    printf("Coefficients of generator polynomial: ");
    scanf("%s", polynomial);
    int k = strlen(polynomial);

    char codeword[n + k - 1];
    strcpy(codeword, dataword);
    memset(codeword + n, '0', (k - 1) * sizeof(char));
    codeword[n + k - 1] = '\0';
    printf("Updated dividend: %s\n", codeword);

    char buffer[k];
    strncpy(buffer, dataword, k);
    buffer[k] = '\0';

    for (int i = k; i < n + k; ++i) {
        int r = buffer[0] - '0';
        for (int j = 1; j < k; ++j)
            buffer[j - 1] = '0' + (r * (polynomial[j] - '0')) ^ (buffer[j] - '0');
        buffer[k - 1] = codeword[i];
    }
    
    strcpy(codeword + n, buffer);
    printf("Codeword: %s\n", codeword);
    return 0;
}