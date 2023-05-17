#include <stdio.h>
#include <string.h>

#define SIZE 500

int convert_to_decimal(int n, char *bstring)
{
    int result = 0;
    for (int i = n - 1, p = 0; i >= 0; --i, ++p)
        result += (bstring[i] - '0') * (1 << p);

    return result;
}

int main(void)
{
    char codeword[SIZE];
    printf("Codeword: ");
    scanf("%s", codeword);
    int n = strlen(codeword);

    int r = 0;
    while (n > (1 << r) - 1) ++r;

    int k = n - r;
    char parity_bits[r + 1];
    memset(parity_bits, '0', r);
    parity_bits[r] = '\0';

    for (int i = 0; i < r; ++i) {
        int p = 1 << i;
        int parity_bit = 0;
        int parity_pos = n - p;
        
        for (int j = parity_pos; j >= 0; j -= p)
            for (int k = 0; k < p && j >= 0; ++k, --j)
                parity_bit ^= codeword[j] - '0';

        parity_bits[r - i - 1] = '0' + parity_bit;
    }

    int error_pos = convert_to_decimal(r, parity_bits);
    if (error_pos) {
        printf("Wrong codeword received.\n");
        printf("Error at position: %d\n", n - error_pos + 1);
        codeword[n - error_pos] = codeword[n - error_pos] == '0' ? '1' : '0';
        printf("Corrected codeword: %s\n", codeword);
        return -1;
    }

    printf("Actual data received.\n");
    return 0;
}