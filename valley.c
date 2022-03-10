#include <stdio.h>
#include <stdlib.h>

int main() {
	FILE *fin, *fout;
	fin = fopen("valley.in", "r");
	fout = fopen("valley.out", "w");

	if (fin == NULL) {
		printf("input file doesnt exist\n");
		return -1;
	}

	if (fout == NULL) {
		printf("output file doesnt exist\n");
		return -1;
	}

	int N, i , j, k, k2;
	long long min = 1000000000;
	unsigned long long hours = 0;
	long *p, x;
	fscanf(fin, "%d", &N);
	// Am alocat memorie pentru vectorul de inaltimi de dim N
	p = malloc(N * sizeof(long));
	for(i = 0; i < N; i++) {
		fscanf(fin, "%ld", &p[i]);
	}
	// gasim minimul din vect de inaltimi
	// punctul in care se formeaza valea,daca sunt mai multe minime
	// retinem pozitiile la primul si la ultimul
	for(i = 0 ; i < N; i++) {
		if(p[i] < min) {
			min = p[i];
			k = k2 = i;
		}

		if(p[i] == min) {
			k2 = i;
		}
	}
	// tratam separat cazurile in care minimul se afla pe prima sau ultima pozitie
	// si facem urmatorul element din p noul minim
	if(k == N-1) {
		hours = hours + p[N-2] - p[N-1];
		p[N-2] = p[N-1];
		k = N-2;
	}

	if(k == 0) {
		hours = hours + p[1] - p[0];
		p[1] = p[0];
		k = 1;
	}
	// parcurgem toate elementele pana la minim
	// updatam hours daca trebuie modificate elemente
	// a.i sa respecte conditia de vale
	for(i = 0; i < k; i++) {
		if(p[i] < p[i + 1]) {
			x = p[i + 1] - p[i];
			p[i + 1] = p[i];
			hours = hours + x;
		}
	}
	// procedam al fel si pentru elementele de la minim pana la sfarsit
	// acestea trebuie sa fie in ordine crescatoare
	for(i = N -1; i > k; i--) {
		if(p[i] < p[i - 1]) {
			x = p[i - 1] - p[i];
			p[i - 1] = p[i];
			hours = hours + x;
		}
	}


	fprintf(fout, "%lld", hours);
	free(p);
	fclose(fin);
	fclose(fout);

	return 0;
}
