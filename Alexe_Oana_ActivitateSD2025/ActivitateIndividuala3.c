//#define _CRT_SECURE_NO_WARINGNS
//#include<stdio.h>
//#include<stdlib.h>
//#include<malloc.h>
//
// struct StructuraPrajitura {
//		int id;
//		char* nume;
//		float pret;
//		float greutate;
//		char* aroma;
//		int nrFelii;
//	};
// typedef struct StructuraPrajitura Prajitura;
//
// void afisarePrajitura(Prajitura prajitura)
//	 {
//	 	printf("Id: %d\n Nume: %s\n Pret: %.2f\n Greutatea: %.2f\n Aroma: %s\n Numar felii: %d ", prajitura.id, prajitura.nume, prajitura.pret, prajitura.greutate, prajitura.aroma, prajitura.nrFelii);
//	 }
//
//	 Prajitura citirePrajituraDinFisier(FILE* fisier)
//	 {
//	 	char buffer[100]; //buffer stocheaza o linie citita din fisier pentru a o procesa mai tarziu
//	 	char sep[3] = ",\n";
//	 	fgets(buffer, 100, fisier); //citesc intreaga linie si o stochez in buffer
//	 	char* aux;
//	 	Prajitura p1;
//	 	aux = strtok(buffer, sep);
//	 	p1.id = atoi(aux);
//	 	aux = strtok(NULL, sep);
//	 	p1.nume = (char*)malloc(strlen(aux) + 1);
//	 	strcpy_s(p1.nume, strlen(aux) + 1, aux);
//	 	aux = strtok(NULL, sep);
//	 	p1.pret = atof(aux);
//	 	aux = strtok(NULL, sep);
//	 	p1.greutate = atof(aux);
//	 	aux=strtok(NULL, sep);
//	 	p1.aroma = (char*)malloc(strlen(aux) + 1);
//	 	strcpy_s(p1.aroma, strlen(aux) + 1, aux);
//	 	aux = strtok(NULL, sep);
//	 	p1.nrFelii = atoi(aux);
//	 	return p1;
//	 
//	 }
//	
//	
//	typedef struct Nod Nod;
//
//	struct Nod {
//		Prajitura info;
//		Nod* urm;
//	};
//
//	void afisareListaPrajituri(Nod* cap)
//	{
//		while (cap!=NULL)
//		{
//			afisarePrajitura(cap->info);
//			cap=cap->urm;
//		}
//	}
//
//	void adaugaPrajituraInLista(Nod** cap, Prajitura prajituraNoua)
//	{
//		Nod* nou = (Nod*)malloc(sizeof(Nod));
//		nou->info = prajituraNoua;
//		nou->urm = NULL;
//		if ((*cap) == NULL)
//		{
//			*cap = nou;
//		}
//		else
//		{
//			Nod* p = *cap;
//			p->info = prajituraNoua;
//			p->urm = nou;
//		}
//	}
//
//	void adaugaLaInceputInLista(Nod** cap, Prajitura prajituraNoua)
//	{
//		Nod* nou = (Nod*)malloc(sizeof(Nod));
//		nou->info = prajituraNoua;
//		nou->urm = *cap;
//		*cap = nou;
//	}
//
//	Nod* citireListaPrajituriDinFisier(const char* numeFisier)
//	{
//		FILE* f = fopen(numeFisier, "r");
//		Nod* lista = NULL;
//		while (!feof(f))
//		{
//			adaugaPrajituraInLista(&lista, citirePrajituraDinFisier((f)));
//
//		}
//		fclose(f);
//		return lista;
//	}
//
//	void dezalocareListaPrajituri(Nod** cap)
//	{
//		while (*cap != NULL)
//		{
//			Nod* aux = (*cap);
//			*cap = (*cap)->urm;
//			free(aux->info.nume);
//			free(aux->info.aroma);
//			free(aux);
//		}
//	}
//
//	float calculeazaPretMediu(Nod* lista)
//	{
//		if (!lista) return 0;
//		float suma = 0;
//		int contor = 0;
//		while (lista)
//		{
//			suma = lista->info.pret;
//			contor++;
//			lista = lista->urm;
//		}
//		return (contor > 0) ? suma / contor : 0;
//	}
//
//	float calculeazaPretulPrajiturilorDupaAroma(Nod* lista, const char* aroma)
//	{
//		float suma = 0;
//		while (lista)
//		{
//			
//			if (strcmp(aroma, lista->info.aroma) == 0)
//			{
//				suma += lista->info.pret;
//			}
//			lista=lista->urm;
//		}
//		return suma;
//	}
//
//	char* getCeaMaiScumpaPrajitura(Nod* lista)
//	{
//		float pretMax = 0;
//		char* prajituraScumpa = NULL;
//		while (lista)
//		{
//			if (lista->info.pret > pretMax)
//			{
//				pretMax = lista->info.pret;
//				prajituraScumpa = lista->info.nume;
//			}
//			lista->urm;
//		}
//		if (pretMax > 0)
//		{
//			char* nou = malloc(strlen(prajituraScumpa) + 1);
//			strcpy_s(nou, strlen(prajituraScumpa) + 1, prajituraScumpa);
//			return nou;
//		}
//		return NULL;
//	}
//	void stergePrajituriDupaNrFelii(Nod** cap, int nrFeliiCautate) {
//		while ((*cap) && (*cap)->info.nrFelii == nrFeliiCautate) {
//			Nod* aux = *cap;
//			*cap = aux->urm;
//			if (aux->info.aroma) {
//				free(aux->info.aroma);
//			}
//			if (aux->info.nume) {
//				free(aux->info.nume);
//			}
//			free(aux);
//		}
//		if ((*cap)) {
//			Nod* p = *cap;
//			while (p) {
//				while (p->urm && p->urm->info.nrFelii!=nrFeliiCautate) {
//					p = p->urm;
//				}
//				if (p->urm) {
//					Nod* aux = *cap;
//					*cap = aux->urm;
//					if (aux->info.aroma) {
//						free(aux->info.aroma);
//					}
//					if (aux->info.nume) {
//						free(aux->info.nume);
//					}
//					free(aux);
//				}
//				else {
//					p = NULL;
//				}
//			}
//		}
//}
// 
// 
//int main()
//{
//	Nod* cap = NULL;
//	cap = citireListaPrajituriDinFisier("prajituri.txt");//daca lasam void*, trebuia sa facem cast
//	afisareListaPrajituri(cap);
//	printf("%f", calculeazaPretMediu(cap));
//	printf("%f", calculeazaPretulPrajiturilorDupaAroma(cap, "ciocolata"));
//	printf("Sterge prajituri cu 2 felii");
//	stergePrajituriDupaNrFelii(&cap, 2);
//	afisareListaPrajituri(cap);
//	printf("Sterge prajituri cu 6 felii");
//	stergePrajituriDupaNrFelii(&cap, 6);
//	afisareListaPrajituri(cap);
//	dezalocareListaPrajituri(&cap);
//	return 0;
//}