#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>

typedef struct Produs Produs;
struct Produs {
	int id;
	char* nume;
	float pret;
};

typedef struct Heap Heap;
struct Heap {
	int lungime; //numarul produselor vizibile
	Produs* produse;
	int nrProduse; //totalul profuselor
};

Produs citireProdusDinFisier(FILE* numeFisier) {
	char buffer[100];
	char sep[3] = ",\n";
	char* aux;
	Produs p;
	fgets(buffer, 100, numeFisier);
	aux = strtok(buffer, sep);
	p.id = atoi(aux);
	aux = strtok(NULL, sep);
	p.nume = malloc(strlen(aux) + 1);
	strcpy_s(p.nume, strlen(aux) + 1, aux);
	aux = strtok(NULL, sep);
	p.pret = atof(aux);
	return p;
}

void afisareProdus(Produs produs) {
	printf("ID: %d\n Nume: %s\n Pret: %.2f\n\n\n", produs.id, produs.nume, produs.pret);
}

Heap initializeazaHeap(int lungime) {
	Heap heap;
	heap.lungime = lungime;
	heap.produse = (Produs*)malloc(sizeof(Produs) * lungime);
	heap.nrProduse = 0;
	return heap;
}

void filtreazHeap(Heap heap, int pozitieNod) { 
	int pozStg = 2 * pozitieNod + 1;
	int pozDr = 2 * pozitieNod + 2;
	int pozMax = pozitieNod;
	if (pozStg<heap.nrProduse && heap.produse[pozStg].id>heap.produse[pozMax].id) {
		pozMax = pozStg;
	}
	else if (pozDr<heap.nrProduse && heap.produse[pozDr].id>heap.produse[pozMax].id) {
		pozMax = pozDr;
	}
	if (pozMax != pozitieNod) {
		Produs aux;
		aux = heap.produse[pozMax];
		heap.produse[pozMax] = heap.produse[pozitieNod];
		heap.produse[pozitieNod] = aux;
		if (pozMax < (heap.nrProduse - 1) / 2) {
			filtreazHeap(heap, pozMax);
		}
	}
}

Heap citireHeapProduseDinFIsier(const char* numeFisier) {
	Heap heap = initializeazaHeap(3);
	FILE* file = fopen(numeFisier, "r");
	int index = 0;
	while (!feof(file)) {
		heap.produse[index] = citireProdusDinFisier(file);
		index++;
	}
	heap.nrProduse = index;
	fclose(file);
	for (int i = (heap.nrProduse - 1) / 2; i >= 0; i--) {
		filtreazHeap(heap, i);
	}
	return heap;
}

void afisareHeap(Heap heap) {
	for (int i = 0; i < heap.nrProduse; i++) {
		afisareProdus(heap.produse[i]);
	}
}

void afisareHeapAscuns(Heap heap) {
	for (int i = heap.nrProduse; i < heap.lungime; i++) {
		afisareProdus(heap.produse[i]);
	}
}

Produs extragereProdus(Heap* heap) {
	Produs gol = heap->produse[0];
	heap->produse[0] = heap->produse[heap->nrProduse - 1];
	heap->produse[heap->nrProduse - 1] = gol;
	for (int i = (heap->nrProduse - 2) / 2; i >= 0; i--) {
		filtreazHeap(*heap, i);
	}
	return gol;
}

void dezalocareHeap(Heap* heap) {
	for (int i = 0; i < heap->lungime; i++) {
		free(heap->produse[i].nume);
	}
	free(heap->produse);
	heap->produse = NULL;
	heap->lungime = 0;
	heap->nrProduse = 0;
}


int main() {
	Heap heap;
	heap = citireHeapProduseDinFIsier("produse.txt");
	Produs produs;
	produs = extragereProdus(&heap);
	afisareHeap(heap);
	dezalocareHeap(&heap);
}