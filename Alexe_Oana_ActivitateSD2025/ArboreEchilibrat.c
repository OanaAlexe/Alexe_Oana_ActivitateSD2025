#define _CRT_SECURE_NO_WARNINGS
#include<stdlib.h>
#include<string.h>
#include<stdio.h>

typedef struct Produs Produs;
struct Produs {
	int id;
	char* nume;
	float pret;
};

typedef struct Nod Nod;
struct Nod {
	Produs info;
	Nod* stg;
	Nod* dr;
};

Produs citireProdusDinFisier(FILE* file) {
	Produs p1;
	char buffer[100];
	char sep[3] = ",\n";
	char* aux;
	fgets(buffer, 100, file);
	aux = strtok(buffer, sep);
	p1.id = atoi(aux);
	aux = strtok(NULL, sep);
	p1.nume = (char*)malloc(strlen(aux) + 1);
	strcpy_s(p1.nume, strlen(aux) + 1, aux);
	aux = strtok(NULL, sep);
	p1.pret = atof(aux);
	return p1;
}

void afisareProdus(Produs produs) {
	printf("ID: %d\n Nume: %s\n Pret: %.2f\n\n\n\n", produs.id, produs.nume, produs.pret);
}

int calculeazaInaltimeArbore(Nod* radacina) {
	if ((radacina) == NULL) {
		return 0;
	}
	else {
		int inaltimeSTG = calculeazaInaltimeArbore(radacina->stg);
		int inaltimeDR = calculeazaInaltimeArbore(radacina->dr);
		return 1 + (inaltimeDR > inaltimeSTG ? inaltimeDR : inaltimeSTG);
	}
}

void rotireStanga(Nod** radacina) {
	Nod* nod;
	nod = (*radacina)->dr;
	(*radacina)->dr = nod->stg;
	nod->stg = (*radacina);
	(*radacina) = nod;
}

void rotireDreapta(Nod** radacina) {
	Nod* nod;
	nod = (*radacina)->stg;
	(*radacina)->stg = nod->dr;
	nod->dr = (*radacina);
	(*radacina) = nod;
}

int calculeazaGardEchilibru(Nod* radacina) {
	if (radacina == NULL) {
		return 0;
	}
	else {
		return (calculeazaInaltimeArbore(radacina->stg) - calculeazaInaltimeArbore(radacina->dr));
	}
}

void adaugaProdusInArboreEchilibrat(Nod** radacina, Produs produsNou) {
	if((*radacina)) {
		if ((*radacina)->info.id > produsNou.id) {
			adaugaProdusInArboreEchilibrat(&((*radacina)->stg), produsNou);
		}
		if ((*radacina)->info.id < produsNou.id) {
			adaugaProdusInArboreEchilibrat(&((*radacina)->dr), produsNou);
		}
		else {
			int grad = calculeazaGardEchilibru((*radacina));
			if (grad == 2) {
				if (calculeazaGardEchilibru((*radacina)->stg) == 1) {
					rotireDreapta(radacina);
				}
				else {
					rotireStanga(&((*radacina)->stg));
					rotireDreapta(radacina);
				}
			}
			else if (grad == -2) {
				if (calculeazaGardEchilibru((*radacina)->stg) == 1) {
					rotireDreapta(radacina);
				}
				rotireStanga(radacina);
			}
			else {
				Nod* nod = (Nod*)malloc(sizeof(Nod));
				nod->dr = NULL;
				nod->stg = NULL;
				nod->info = produsNou;
				(*radacina) = nod;
			}
		}
	}
}


Nod* citireArboreDeProduseDinFisier(const char* numeFisier) {
	FILE* file = fopen(numeFisier, "r");
	Nod* radacina = NULL;
	while (!feof(file)) {
		Produs p = citireProdusDinFisier(file);
		adaugaProdusInArboreEchilibrat(&radacina, p);
	}
	fclose(file);
	return radacina;
}

void afisareArborePreordine(Nod* radacina) {
	if (radacina) {
		afisareProdus(radacina->info);
		afisareArborePreordine(radacina->stg);
		afisareArborePreordine(radacina->dr);
	}
}

Produs getProdusByID(Nod* radacina, int id) {
	Produs p1;
	p1.id = -1;
	if (radacina == NULL) {
		return;
	}
	else {
		if (radacina->info.id > id) {
			return getProdusByID(radacina->stg, id);
		}
		else if (radacina->info.id < id) {
			return getProdusByID(radacina->dr, id);
		}
		else {
			p1 = radacina->info;
			p1.nume = (char*)malloc(strlen(radacina->info.nume) + 1);
			strcpy_s(p1.nume, strlen(radacina->info.nume) + 1, radacina->info.nume);
			return p1;
		}
		return p1;
	}
}


int determinaNumarNoduri(Nod* radacina) {
	if (radacina == NULL) {
		return 0;
	}
	else {
		return 1 + determinaNumarNoduri(radacina->stg) + determinaNumarNoduri(radacina->dr);
	}
}

float calculeazaPetTotal(Nod* radacina) {
	if (radacina == NULL) {
		return 0;
	}
	else {
		float pretSTG = calculeazaPetTotal(radacina->stg);
		float pretDR = calculeazaPetTotal(radacina->dr);
		float pretTotal = radacina->info.pret + pretDR + pretSTG;
		return pretTotal;
	}
}


int main() {
	Nod* arbore = citireArboreDeProduseDinFisier("produse.txt");
	afisareArborePreordine(arbore);
	printf("Pretul total al produselor este: %.2f", calculeazaPetTotal(arbore));
	calculeazaGardEchilibru(arbore);

}