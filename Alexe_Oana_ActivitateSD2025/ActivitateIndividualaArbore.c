#define _CRT_SECURE_NO_WARNINGS
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<malloc.h>

typedef struct Produs Produs;
struct Produs {
	int id;
	char* nume;
	float pret;
};

typedef struct Nod Nod;
struct Nod {
	Nod* stg;
	Nod* dr;
	Produs info;
};

Produs citireProdusDinFisier(FILE* file) {
	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, file);
	char* aux;
	Produs p1;
	aux = strtok(buffer, sep);
	p1.id = atoi(aux);
	aux = strtok(NULL, sep);
	p1.nume = malloc(strlen(aux) + 1);
	strcpy_s(p1.nume, strlen(aux) + 1, aux);
	aux = strtok(NULL, sep);
	p1.pret = atof(aux);
	return p1;
}

void afisareProdus(Produs produs) {
	printf("Id: %d\n Nume: %s\n Pret: %.2f\n\n\n\n", produs.id, produs.nume, produs.pret);
}

void adaugaProdusInArbore(Nod** radacina, Produs produsNou) {

	if ((*radacina)) {
		if (produsNou.id < (*radacina)->info.id) {
			adaugaProdusInArbore((*radacina)->stg, produsNou);
		}
		else if (produsNou.id > (*radacina)->info.id) {
			adaugaProdusInArbore((*radacina)->dr, produsNou);
		}
		else {
			if ((*radacina)->info.nume) {
				free((*radacina)->info.nume);
			}
			(*radacina)->info.id = produsNou.id;
			(*radacina)->info.nume = malloc(strlen((produsNou.nume) + 1));
			strcpy_s((*radacina)->info.nume, strlen(produsNou.nume) + 1, produsNou.nume);
			((*radacina)->info.pret) = produsNou.pret;
		}
	}
	else {
		(*radacina) = malloc(sizeof(Nod));
		(*radacina)->info = produsNou;
		(*radacina)->info.nume = malloc(strlen(produsNou.nume) + 1);
		strcpy_s((*radacina)->info.nume, strlen(produsNou.nume) + 1, produsNou.nume);
		(*radacina)->dr = NULL;
		(*radacina)->stg = NULL;

	}
	
}

Nod* citireArboreDeProduseDinFisier(const char* numeFisier) {
	FILE* file = fopen(numeFisier, "r");
	Nod* radacina = NULL;
	while (!feof(file)) {
		Produs p1 = citireProdusDinFisier(file);
		adaugaProdusInArbore(&radacina, p1);
		free(p1.nume);
	}
	fclose(file);
	return radacina;
}

void afisareProduseInOrdine(Nod* radacina) {
	if (radacina) {
		afisareProduseInOrdine((radacina)->stg);
		afisareProdus(radacina->info);
		afisareProduseInOrdine((radacina)->stg);
	}
}

void afisareProdusePreOrdine(Nod* radacina) {
	if (radacina) {
		afisareProdus(radacina->info);
		afisareProdusePreOrdine((radacina)->stg);
		afisareProdusePreOrdine((radacina)->dr);

	}
}

void afisareProdusePostOrdine(Nod* radacina) {
	if (radacina) {
		afisareProdusePostOrdine((radacina)->stg);
		afisareProdusePostOrdine((radacina)->dr);
		afisareProdus(radacina->info);
	}
}

void dezalocareProduse(Nod** radacina) {
	if ((*radacina)) {
		dezalocareProduse(&((*radacina)->stg));
		dezalocareProduse(&((*radacina)->dr));
		free((*radacina)->info.nume);
		free(*radacina);
		*radacina = NULL;
	}
}


Produs getProdusByID(Nod* radacina, int id) {
	Produs p;
	p.id = -1;
	if (id > radacina->info.id) {
		return getProdusByID(radacina->dr, id);
	}
	else if (id < radacina->info.id) {
		return getProdusByID(radacina->stg, id);
	}
	else {
		p = radacina->info;
		p.nume = (char*)malloc(strlen(radacina->info.nume) + 1);
		strcpy_s(p.nume, strlen(radacina->info.nume) + 1, radacina->info.nume);
		return p;
	}
	return p;
}

int determinaNumarulDeNoduri(Nod* radacina) {
	if (radacina) {
		return 1 + determinaNumarulDeNoduri(radacina->dr) + determinaNumarulDeNoduri(radacina->stg);
	}
}

int calculeazaInaltime(Nod* radacina) {
	if (radacina == NULL) {
		return 0;
	}
	else {
		int inaltimeSTG = calculeazaInaltime(radacina->stg);
		int inaltimeDR = calculeazaInaltime(radacina->dr);
		return (1 + inaltimeSTG > inaltimeDR ? inaltimeSTG : inaltimeDR);
	}
}


float calculeazaPretTotal(Nod* radacina) {
	if (radacina) {
		return 0;
	}
	else {
		float pretSTG = calculeazaPretTotal(radacina->stg);
		float pretDR = calculeazaPretTotal(radacina->dr);
		float pretTotal = radacina->info.pret + pretDR + pretSTG;
		return pretTotal;
	}
	
}

int main() {

	Nod* arbore = citireArboreDeProduseDinFisier("produse.txt");
	//afisareProduseInOrdine(arbore);
	afisareProdusePreOrdine(arbore);
	Produs p = getProdusByID(arbore, 1);
	printf("\n\n\n");
	afisareProdus(p);
	int i = determinaNumarulDeNoduri(arbore);
	printf("Numarul de noduri este: %d", i);
	dezalocareProduse(&arbore);
	return 0;

	
}
