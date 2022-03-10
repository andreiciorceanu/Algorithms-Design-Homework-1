#include <stdio.h>
#include <stdlib.h>
#define MIN(a, b) (((a) < (b))?(a):(b))
#define P 999999999999999
	// in cazul in care inaltimea muntelui curent nu >= 2
	// pentru a nu influenta minimul din matricea de minime din dp
	// minim pentru 3 elemente
long long min(long long a, long long b, long long c) {
	if ( (a < b) && (a < c) ) {
      return a;
	} else if (b < c) {
      return b;
	} else {
      return c;
	}
}

int main() {
	FILE *fin, *fout;
	fin = fopen("ridge.in", "r");
	fout = fopen("ridge.out", "w");

	if (fin == NULL) {
		printf("input file doesnt exist\n");
		return -1;
	}

	if (fout == NULL) {
		printf("output file doesnt exist\n");
		return -1;
	}

	long long N;
	long long i, j;
	long long *H, *C;
	fscanf(fin, "%lld", &N);
	H = malloc(N * sizeof(long long));
	C = malloc(N * sizeof(long long));
	// initializam un vector de inaltimi si de costuri de dim N
	for (i = 0; i < N; i++) {
		fscanf(fin, "%lld %lld", &H[i], &C[i]);
	}
	// alocam matricea pentru a folosi programarea dinamica
	// pentru a gasi minimul de cost si
	// secventa de munti sa respecte conditia din enunt
	long long **dp;
	dp = malloc(N * sizeof(long long *));
	for (i = 0; i < N; i++) {
		dp[i] = malloc(3 * sizeof(long long));
	}
	// caz de baza
	dp[0][0] = 0;
	dp[0][1] = C[0];
	if (H[0] >= 2) {
	dp[0][2] = 2 * C[0];
	} else {
	dp[0][2] = P;
	}

	for (i = 1; i < N; i++) {
		// cazul in care distanta dintre 2 munti este diferita de -2,-1,0,1,2
		dp[i][0] = min(dp[i-1][0], dp[i-1][1], dp[i-1][2]);
		dp[i][1] = C[i] + min(dp[i-1][0], dp[i-1][1], dp[i-1][2]);
		if (H[i] >= 2) {
			dp[i][2] = 2 * C[i] + min(dp[i-1][0], dp[i-1][1], dp[i-1][2]);
		} else {
			dp[i][2] = P;  // initializam cu un numar
			// foarte mare pentru a nu influenta min
		}
		// luam toate cazurile cu diferentele
		// care pot exista intre 2 munti consecutivi
		if ((H[i - 1] - H[i]) == -2) {
			dp[i][0] = min(dp[i-1][0], dp[i-1][1], dp[i-1][2]);
	// alegem minimul in functie de cap puteam scadea din
	// muntele curent a.i sa nu fie egal cu cel anterior
			dp[i][1] = C[i] + min(dp[i-1][0], dp[i-1][1], dp[i-1][2]);
			if (H[i] >= 2) {
				dp[i][2] = C[i] * 2 + MIN(dp[i-1][1], dp[i-1][2]);
			} else {
				dp[i][2] = P;
			}
		}
		if ((H[i - 1] - H[i])== -1) {
			dp[i][0] = min(dp[i-1][1], dp[i-1][2], dp[i-1][0]);
			dp[i][1] = C[i] + MIN(dp[i-1][1], dp[i-1][2]);
			if (H[i] >= 2) {
				dp[i][2] =  2 * C[i] + MIN(dp[i-1][0], dp[i-1][2]);
			} else {
				dp[i][2] = P;
			}
		}

		if ((H[i - 1] - H[i])== 1) {
			dp[i][0] = MIN(dp[i-1][0], dp[i-1][2]);
			dp[i][1] = C[i] + MIN(dp[i-1][0], dp[i-1][1]);
			if (H[i] >= 2) {
			dp[i][2] =  2 * C[i] + min(dp[i-1][1], dp[i-1][2], dp[i-1][0]);
			} else {
				dp[i][2] = P;
			}
		}

		if ((H[i - 1] - H[i]) == 2) {
			dp[i][0] = MIN(dp[i-1][1], dp[i-1][0]);
			dp[i][1] = C[i] + min(dp[i-1][0], dp[i-1][1], dp[i-1][2]);
			if (H[i] >= 2) {
			dp[i][2] = 2 * C[i] + min(dp[i-1][0], dp[i-1][1], dp[i-1][2]);
			} else {
				dp[i][2] = P;
			}
		}

		if ((H[i - 1] - H[i]) == 0) {
			dp[i][0] = MIN(dp[i-1][1], dp[i-1][2]);
			dp[i][1] = C[i] + MIN(dp[i-1][0], dp[i-1][2]);
			if (H[i] >= 2) {  // verificam daca este mai mare ca 2 in cazul in care facem
				// o scadere de 2 acesta sa nu ajunga la dimensiuni negative
			dp[i][2] = MIN(dp[i-1][0], dp[i-1][1]) + 2 * C[i];
			} else {
				dp[i][2] = P;
			}
		}
	}


	long long minim;
	minim = min(dp[N-1][0], dp[N-1][1], dp[N-1][2]);
	// afisare minim cost
	fprintf(fout, "%lld\n", minim);

	for (i = 0; i < N; i++) {
		free(dp[i]);
	}
	// inchidere fisiere
	free(dp);
	free(H);
	free(C);
	fclose(fin);
	fclose(fout);
	return 0;
}
