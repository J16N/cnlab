#include <stdio.h>
#include <string.h>

#define SIZE 500

int main(void)
{
    char dataword[SIZE];
    printf("Dataword: ");
    scanf("%s", dataword);
    int n = strlen(dataword);

    char odd_codeword[n + 2];
    char even_codeword[n + 2];
    strcpy(odd_codeword, dataword);
    strcpy(even_codeword, dataword);

    int ones = 0;
    for (int i = 0; i < n; ++i)
        ones ^= (dataword[i] - '0');

    odd_codeword[n] = '0' + !ones;
    even_codeword[n] = '0' + ones;
    odd_codeword[n + 1] = '\0';
    even_codeword[n + 1] = '\0';

    printf("Odd codeword: %s\n", odd_codeword);
    printf("Even codeword: %s\n", even_codeword);

    return 0;
}