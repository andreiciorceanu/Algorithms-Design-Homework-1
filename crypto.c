#include <stdio.h>
#include <stdlib.h>

void merge(int arr[], int l, int m, int r, int vect[]) {
	int i, j, k;
	int n1 = m - l + 1;
	int n2 = r - m;
	int n3 = r - l + 1;
    int L[n1], R[n2];
	int P[r - l + 1];
	for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];
    for (i = 0; i < n3; i++)
    	P[i] = vect[l + i];
    i = 0;
	j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            vect[k] = P[i];
            i++;
        } else {
            arr[k] = R[j];
            vect[k] = P[n1 + j];
            j++;
        }
        k++;
    }
    while (i < n1) {
		arr[k] = L[i];
		vect[k] = P[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = R[j];
		vect[k] = P[n1 + j];
        j++;
        k++;
    }
}
void mergeSort(int arr[], int l, int r, int vect[]) {
	if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m, vect);
        mergeSort(arr, m + 1, r, vect);
        merge(arr, l, m, r, vect);
    }
}

int main() {
	FILE *fin, *fout;
	fin = fopen("crypto.in", "r");
	fout = fopen("crypto.out", "w");
	if (fin == NULL) {
		printf("input file doesnt exist\n");
		return -1;
	}
	if (fout == NULL) {
		printf("output file doesnt exist\n");
		return -1;
	}

	int N, B, i = 0, j;
	int sum = 0;
	int *P, *U;
	fscanf(fin, "%d %d", &N , &B);
	P = malloc(N * sizeof(int));
	U = malloc(N * sizeof(int));
	for(i = 0; i < N; i++) {
		fscanf(fin, "%d %d", &P[i], &U[i]);
	}
	mergeSort(P, 0 , N-1, U);
	int min = P[0], s = 0, k;
	while(sum < B) {
		if(P[i] == min) {  // cat timp vom gasi elemente la fel de ex
	// 2 2 2 2 4 4 vom incerca sa le updatam pe toate care sunt 2 daca B ne permite
			if(sum < B) {
				sum += U[i];
				if(sum > B)
				break;  // cand suma depaseste bugetul nu mai putem face update-uri
				P[i]++;
				i++;
			} else {
				break;
			}
		 } else {
			min = P[0];  // updatam noul minim,insemnand ca de la 2 2 2 4 4 6
	// am trecut la 4 4 4 4 4 6 si incepem din nou procedeul
			i = 0;
		}
	}
	mergeSort(P, 0 , N-1, U);
	// deoarece primul calculator produce nr minim de monede pe ora
	fprintf(fout, "%d\n", P[0]);
	fclose(fin);
	fclose(fout);
	free(P);
	free(U);
	return 0;
}
