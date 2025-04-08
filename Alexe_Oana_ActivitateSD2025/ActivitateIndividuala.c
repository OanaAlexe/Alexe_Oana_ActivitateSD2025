#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>


struct Carte {
	int id;
	char* titlu;
	char* autor;
	float pret;
	unsigned char categorie; //D=dramatic, I=istoric, T=teatru, N=non-fictiune
};

typedef struct Carte Carte;
typedef struct Nod Nod;

struct Nod {
	Carte info;
	Nod* urmator;
};


void afisareCarte(Carte carte) {
	printf("Id: %d\n Titlu: %s\n Autor: %s\n Pret: %.2f\n Categorie: %c", carte.id, carte.titlu, carte.autor, carte.pret, carte.categorie);
}


Carte citireCarteDinFisier(FILE* file) {
	Carte c1;
	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, file);
	char* aux;
	aux = strtok(buffer, sep);
	c1.id = atoi(aux);
	aux = strtok(NULL, sep);
	c1.titlu = malloc(strlen(aux) + 1);
	strcpy_s(c1.titlu, strlen(aux) + 1, aux);
	aux = strtok(NULL, sep);
	c1.autor = malloc(strlen(aux) + 1);
	strcpy_s(c1.autor, strlen(aux) + 1, aux);
	c1.pret = atof(strtok(NULL, sep));
	c1.categorie = strtok(NULL, sep);
	return c1;
}


void afisareListaCarti(Nod* cap) {
	while (cap) {
		afisareCarte(cap->info);
		cap = cap->urmator;
	}
}

void adaugaCarteInLista(Nod** cap, Carte carteNoua)
{
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = carteNoua;
	nou->urmator = NULL;
	if ((*cap==NULL)) {
		*cap = nou;
	}
	else
	{
		Nod* p = *cap;
		while (p->urmator) {
			p = p->urmator;
		}
		p->urmator = nou;
	}
}

void adaugaLaInceputInLista(Nod** cap, Carte carteNoua) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = carteNoua;
	nou->urmator = *cap;
	*cap = nou;
}

Nod* citireListaCartiDinFIasier(FILE* file) {
	FILE* f = fopen(file, "r");
	Nod* lista = NULL;
	while (!feof(f)) {
		adaugaCarteInLista(&lista, citireCarteDinFisier(f));
	}
	fclose(f);
	return lista;
}

void dezalocareListaCarti(Nod** cap) {
	while ((*cap)!=NULL) {
		Nod* aux = *cap;
		(*cap) = (*cap)->urmator;
		free(aux->info.titlu);
		free(aux->info.autor);
		free(aux);
	}	
}

float calculeazaPretMediuCarte(Nod* lista) {
	float suma = 0;
	int contor = 0;
	while (lista) {
		suma += lista->info.pret;
		lista = lista->urmator;
		contor++;
	}
	return (suma > 0) ? suma / contor : 0;
}

void stergeCartiDinCategoria(Nod** cap, char categoriaCautata) {
	while((*cap) && (*cap)->info.categorie == categoriaCautata) {
		Nod* aux = *cap;
		*cap = aux->urmator;
		if (aux->info.titlu) {
			free(aux->info.titlu);
		}
		if (aux->info.autor) {
			free(aux->info.autor);
		}
		free(aux);
	}
	if ((*cap)) {
		Nod* p = *cap;
		while(p) {
			while (p->urmator && p->info.categorie != categoriaCautata)
			{
				p = p->urmator;
			}
			if (p->urmator) {
				Nod* aux = *cap;
				*cap = aux->urmator;
				if (aux->info.titlu) {
					free(aux->info.titlu);
				}
				if (aux->info.autor) {
					free(aux->info.autor);
				}
				free(aux);
			}
			else
			{
				p = NULL;
			}
		}
	}
}

float cacluleazaPretulCartilorDupaAutor(Nod* lista, char autorulDorit) {
	float suma = 0;
	while (lista) {
		if (strcmp(lista->info.autor, autorulDorit) == 0) {
			suma += lista->info.pret;
		}
		lista = lista->urmator;
	}
	return suma;
}


char* getCeaMaiScumpaCarte(Nod* lista) {
	float pretMax = 0;
	char* carteScumpa = NULL;
	while (lista) {
		if (lista->info.pret > pretMax) {
			carteScumpa = lista->info.titlu;
		}
		lista = lista->urmator;
	}
	if (pretMax > 0) {
		char* nou = (char*)malloc(strlen(carteScumpa) + 1);
		strcpy_s(nou, strlen(carteScumpa) + 1, carteScumpa);
		return nou;
	}
	return NULL;
}

int main() 
{
	Nod* cap = NULL;
	cap = citireListaCartiDinFIasier("carti.txt");
	afisareListaCarti(cap);
	printf("%f", calculeazaPretMediuCarte(cap));
	printf("%f", cacluleazaPretulCartilorDupaAutor(cap, "Rebreanu"));
	printf("Sterge carti din categoria N");
	stergeCartiDinCategoria(&cap, 'N');
	afisareListaCarti(cap);
	stergeCartiDinCategoria(&cap, 'I');
	afisareListaCarti(cap);
	dezalocareListaCarti(&cap);
	return 0;
}