#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MOD 1000000007
#define KMAX 4

void multiply_matrix(unsigned long long A[KMAX][KMAX],
	unsigned long long B[KMAX][KMAX],
	unsigned long long C[KMAX][KMAX]) {
    unsigned long long tmp[KMAX][KMAX];
    // tmp = A * B
    for (int i = 0; i < KMAX; ++i) {
        for (int j = 0; j < KMAX; ++j) {
            unsigned long long sum = 0;
            //  presupun că suma încape pe 64 de biți
            for (int k = 0; k < KMAX; ++k) {
                sum += 1LL * A[i][k] * B[k][j];
            }
            tmp[i][j] = sum % MOD;
        }
    }
    //  C = tmp
    memcpy(C, tmp, sizeof(tmp));
}
// R = C^p
void power_matrix(unsigned long long C[KMAX][KMAX], unsigned long long p,
	unsigned long long R[KMAX][KMAX]) {
    // tmp = I (matricea identitate)
    unsigned long long tmp[KMAX][KMAX];
    for (int i = 0; i < KMAX; ++i) {
        for (int j = 0; j < KMAX; ++j) {
            tmp[i][j] = (i == j) ? 1 : 0;
        }
    }
    while (p != 1) {
        if  (p % 2 == 0) {
            multiply_matrix(C, C, C);     // C = C*C
            p /= 2;                       // rămâne de calculat C^(p/2)
        } else {
            //  reduc la cazul anterior:
            multiply_matrix(tmp, C, tmp);  // tmp = tmp*C
            --p;                          // rămâne de calculat C^(p-1)
        }
    }
    // avem o parte din rezultat în C și o parte în tmp
    multiply_matrix(C, tmp, R);           // rezultat = tmp * C
}

int main() {
	FILE *fin, *fout;
	fin = fopen("trigigel.in", "r");
	fout = fopen("trigigel.out", "w");
	if (fin == NULL) {
		printf("input file doesnt exist\n");
		return -1;
	}
	if (fout == NULL) {
		printf("output file doesnt exist\n");
		return -1;
	}
	unsigned long long N;
	fscanf(fin, "%llu", &N);
	// construiesc matricea C
    long long C[KMAX][KMAX] = { {1, 0, 1, 1}, {1, 0, 0, 0},
    {0, 1, 0, 0}, {0, 0, 0, 1}};
	// vreau să aplic formula S_n = S_4 * C^(n-4)
	// C = C^(n-4)
	power_matrix(C, N - 3, C);
	// S0 = 0, S1 = 1, S2 = 3, S3 = 6, S4 = 10, S5 = 16
	// sol = S_4 * C = dp[n] (se află pe ultima poziție din S_n,
	// deci voi folosi ultima coloană din C)
	unsigned long long nr;
	if (N == 0) {
		nr = 0;
	} else if (N == 1) {
		nr = 1;
	} else if (N == 2) {
		nr = 3;
	} else {  // inmultim coeficientii din starea noastra
	// S4 = [ dp[i-1], dp[i-2], dp[i-3],constanta 3]
	// pentru i=4 avem S4=[6,3,1,3],cu prima linie din matrice
	nr = (6 * C[0][0]) % MOD + (3 * C[0][1]) % MOD
	+ (1 * C[0][2]) % MOD + (3 * C[0][3]) % MOD;
	}
	nr = nr % MOD;
	fprintf(fout, "%llu", nr);
	fclose(fin);
	fclose(fout);
	return 0;
}
