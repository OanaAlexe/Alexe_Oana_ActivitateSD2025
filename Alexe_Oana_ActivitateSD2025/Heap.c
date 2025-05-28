#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>




typedef struct Carte Carte;
struct Carte {
	int id;
	char* titlu;
	int nrPagini;
};

typedef struct Heap Heap;
struct Heap {
	int lungime;
	Carte* carte;
	int nrCarti;
};


Carte citireCarteDinFisier(FILE* numeFisier) {
	char buffer[100];
	char sep[3] = ",\n";
	char* aux;
	Carte c;
	fgets(buffer, 100, numeFisier);
	aux = strtok(buffer, sep);
	c.id = atoi(aux);
	aux = strtok(NULL, sep);
	c.titlu = (char*)malloc(strlen(aux) + 1);
	strcpy_s(c.titlu, strlen(aux) + 1, aux);
	aux = strtok(NULL, sep);
	c.nrPagini = atoi(aux);
	return c;
}


void afisareCarte(Carte c) {
	printf("ID: %d\n Titlu: %s\n Numar pagini: %d\n\n\n\n", c.id, c.titlu, c.nrPagini);
}

Heap initializareHeap(int dim) {
	Heap heap;
	heap.lungime = dim;
	heap.nrCarti = 0;
	heap.carte = (char*)malloc(sizeof(Carte) * dim);
	return heap;

}


void filtreazaHeap(Heap heap, int poz) {
	int stg = 2 * poz + 1;
	int dr = 2 * poz + 2;
	int max = poz;
	if (stg<heap.nrCarti && heap.carte[stg].nrPagini>heap.carte[max].nrPagini) {
		max = stg;
	}
	else if (dr<heap.nrCarti && heap.carte[dr].nrPagini>heap.carte[max].nrPagini) {
		max = dr;
	}
	if (max!=poz) {
		Carte aux = heap.carte[poz];
		heap.carte[poz] = heap.carte[max];
		heap.carte[max] = aux;
		filtreazaHeap(heap, max);
	}
}

Heap citireHeapCarti(const char* numeFisier) {
	FILE* file = fopen(numeFisier, "r");
	Heap heap = initializareHeap(3);
	int index = 0;
	while (!feof(file)) {
		heap.carte[index] = citireCarteDinFisier(file);
		index++;
	}
	heap.nrCarti = index;
	fclose(file);
	for (int i = (heap.nrCarti - 1) / 2; i >= 0; i--) {
		filtreazaHeap(heap, i);
	}
	return heap;
}


void afisareHeapCarti(Heap heap) {
	for (int i = 0; i < (heap.nrCarti - 1) / 2; i++) {
		afisareCarte(heap.carte[i]);
	}
}

Carte extragereCarte(Heap* heap) {
	Carte c = heap->carte[0];
	heap->carte[0] = heap->carte[heap->nrCarti - 1];
	heap->nrCarti--;
	for (int i = (heap->nrCarti - 1) / 2; i >= 0; i--) {
		filtreazaHeap((*heap), i);
	}
	return c;
}


void dezalocareHeap(Heap* heap) {
	for (int i = 0; i < (heap->nrCarti - 1) / 2; i++) {
		free(heap->carte[i].titlu);
	}
	free(heap->carte);
	heap->carte = NULL;
	heap->lungime = 0;
	heap->nrCarti = 0;
}

int main() {
	Heap h = citireHeapCarti("carti.txt");
	printf("Elemente vizibile:\n");
	afisareHeapCarti(h);
	extragereCarte(&h);
	dezalocareHeap(&h);
}