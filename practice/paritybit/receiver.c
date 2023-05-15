#include <stdio.h>
#include <string.h>

#define SIZE 500

int main(void)
{
    char codeword[SIZE];
    printf("Codeword: ");
    scanf("%s", codeword);
    int n = strlen(codeword);

    int mode = 0;
    printf("Select MODE: \n");
    printf("<1> Odd Parity Scheme\n");
    printf("<2> Even Parity Scheme\n");
    printf("Mode: ");
    scanf("%d", &mode);

    int parity = 0;
    for (int i = 0; i < n; ++i)
        parity ^= (codeword[i] - '0');

    if ((parity + mode) % 2) {
        printf("Codeword rejected.\n");
        return 1;
    }

    printf("Codeword accepted.\n");
    return 0;
}