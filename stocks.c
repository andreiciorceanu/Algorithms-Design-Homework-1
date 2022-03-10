#include <stdio.h>
#include <stdlib.h>
#define max(a, b) \
	({ __typeof__(a) _a = (a); \
       __typeof__(b) _b = (b); \
     _a > _b ? _a : _b; })

struct action {
	int currentValue;
	int minValue;
	int maxValue;
};


int main() {
	FILE *fin, *fout;
	fin = fopen("stocks.in", "r");
	fout = fopen("stocks.out", "w");

	if (fin == NULL) {
		printf("input file doesnt exist\n");
		return -1;
	}

	if (fout == NULL) {
		printf("output file doesnt exist\n");
		return -1;
	}
	int N, B, L;
	int i, j;
	int bud, loss;
	struct action *A;
	fscanf(fin, "%d %d %d", &N, &B, &L);
	A = malloc((N + 1) * sizeof(struct action));
	// vecttorul de actiuni pe care le poate cumpara Gigel
	for (i = 1; i <= N ; i++) {
		fscanf(fin, "%d %d %d", &A[i].currentValue, &A[i].minValue, &A[i].maxValue);
	}
	// deoarece for-ul nostru din dp porneste de la 1 am initializat A[0] cu 0
	A[0].minValue = 0;
	A[0].currentValue = 0;
	A[0].maxValue = 0;
	int ***dp;
	// alocarea de memorie pentru pointerul 3D
	dp = malloc((N + 1) * sizeof(int **));
	for (i = 0; i <= N; i++) {
		dp[i] = malloc((B+1) * sizeof(int *));
		for (j =0; j <= B; j++) {
			dp[i][j] = malloc((L+1) * sizeof(int));
		}
	}
	// cazul de baza in care initializam vectorul cu 0
	for (i = 0; i <= N; i++) {
		for (j = 0; j <= B; j++) {
		dp[0][i][j] = 0;
		}
	}
	// N = nr de obiecte din colectie
	// B = bugetul lui Gigel L = pierderile maxime
	// dp[*][0][0] pentru situatia in care nu a cumparat actiuni si
	// nu are pierderi/profit nu a cheltuit din buget
	for (i = 1; i <= N; i++) {
		for (bud = 0; bud <= B; bud++) {
			for (loss = 0; loss <= L ; loss++) {
				// daca nu folosim obiectul i => solutia = solutia de la pasul i-1
				dp[i][bud][loss] = dp[i-1][bud][loss];
				int profit = A[i].maxValue - A[i].currentValue;
				int pierdere = A[i].currentValue - A[i].minValue;
				if ((bud - A[i].currentValue >= 0) && (loss - pierdere >= 0)) {
					// folosim obiectul curent rezerv A[i].currentValue din buget
					// rezerv pierdere din totalul de L de pierderi
					int sol_aux = dp[i-1][bud -A[i].currentValue][loss - pierdere] + profit;
					dp[i][bud][loss] = max(dp[i][bud][loss], sol_aux);
				}
			}
		}
	}
	fprintf(fout, "%d", dp[N][B][L]);
	free(A);
	free(dp);
	fclose(fin);
	fclose(fout);
	return 0;
}
