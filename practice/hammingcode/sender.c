#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define SIZE 500
#define GETVAL(n) ((n) == 'P' ? 0 : (n) - '0')

bool power_of_two(int i)
{
    return (i & (i - 1)) == 0;
}

int main(void)
{
    char dataword[SIZE];
    printf("Dataword: ");
    scanf("%s", dataword);
    int k = strlen(dataword);

    int r = 0;
    while (k + r > (1 << r) - 1) ++r;

    int n = k + r;
    char codeword[n + 1];
    codeword[n] = '\0';

    for (int i = n - 1, l = k - 1; i >= 0; --i)
        codeword[i] = power_of_two(n - i) ? 'P' : dataword[l--];

    for (int i = 0; i < r; ++i) {
        int p = 1 << i;
        int parity_bit = 0;
        int parity_pos = n - p;
        
        for (int j = parity_pos; j >= 0; j -= p)
            for (int k = 0; k < p && j >= 0; ++k, --j)
                parity_bit ^= GETVAL(codeword[j]);

        codeword[parity_pos] = '0' + parity_bit;
    }

    printf("Redundant Bits: %d\n", r);
    printf("Codeword: %s\n", codeword);
    return 0;
}