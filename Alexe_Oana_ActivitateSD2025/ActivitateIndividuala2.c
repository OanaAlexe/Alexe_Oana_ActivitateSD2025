//#define _CRT_SECURE_NO_WARNINGS
//#include<stdio.h>
//#include<stdlib.h>
//#include<malloc.h>
//
//struct StructuraPrajitura {
//	int id;
//	char* nume;
//	float pret;
//	float greutate;
//	char* aroma;
//	int nrFelii;
//};
//
//typedef struct StructuraPrajitura Prajitura;
//
//void afisarePrajitura(Prajitura prajitura)
//{
//	printf("Id: %d\n Nume: %s\n Pret: %.2f\n Greutatea: %.2f\n Aroma: %s\n Numar felii: %d ", prajitura.id, prajitura.nume, prajitura.pret, prajitura.greutate, prajitura.aroma, prajitura.nrFelii);
//}
//
//void afisareVectorPrajitura(Prajitura* prajituri, int nrPrajituri)
//{
//	for (int i = 0; i < nrPrajituri; i++)
//	{
//		afisarePrajitura(prajituri[i]);
//	}
//}
//
//
//void adaugaPrajituraInVector(Prajitura** prajitura, int* prajituri, Prajitura PrajituraNoua)
//{
//	Prajitura* aux = (Prajitura*)malloc(((*prajituri)+1) * sizeof(Prajitura));
//	for (int i = 0; i < *prajituri; i++)
//	{
//		aux[i] = (*prajitura)[i];
//	}
//	aux[(*prajituri)] = PrajituraNoua;
//	(*prajituri)++;
//	free(*prajitura);
//	(*prajitura) = aux;
//
//}
//
//
//Prajitura citirePrajituraDinFisier(FILE* fisier)
//{
//	char buffer[100]; //buffer stocheaza o linie citita din fisier pentru a o procesa mai tarziu
//	char sep[3] = ",\n";
//	fgets(buffer, 100, fisier); //citesc intreaga linie si o stochez in buffer
//	char* aux;
//	Prajitura p1;
//	aux = strtok(buffer, sep);
//	//p1.id = atoi(aux);
//	aux = strtok(NULL, sep);
//	p1.nume = malloc(strlen(aux) + 1);
//	strcpy_s(p1.nume, strlen(aux) + 1, aux);
//	aux = strtok(NULL, sep);
//	p1.pret = atof(aux);
//	aux = strtok(NULL, sep);
//	p1.greutate = atof(aux);
//	aux=strtok(NULL, sep);
//	p1.aroma = malloc(strlen(aux) + 1);
//	strcpy_s(p1.aroma, strlen(aux) + 1, aux);
//	aux = strtok(NULL, sep);
//	p1.nrFelii = atoi(aux);
//	return p1;
//
//}
//
//Prajitura* CitireVectorPrajituriFisier(const char* numeFisier, int* nrPrajituriCitite)
//{
//	FILE* file = fopen(numeFisier, "r");
//	Prajitura* prajituri = NULL;
//	do {
//		adaugaPrajituraInVector(&prajituri, nrPrajituriCitite, citirePrajituraDinFisier(file));
//	} while (!feof(file));
//	fclose(file);
//	return prajituri;
//}
//
//void dezalocareVectorPrajituri(Prajitura** vector, int* nrPrajituri)
//{
//	for (int i = 0; i < *nrPrajituri; i++)
//	{
//		free((*vector)[i].nume);
//		free((*vector)[i].aroma);
//
//	}
//	free(*vector);
//	*vector = NULL;
//	*nrPrajituri = 0;
//}
//
//float calculeazaPretMediuDupaNrFelii(Prajitura* vector, int nrPrajituri, int nrFelii)
//{
//	int suma = 0;
//	int contor = 0;
//	for (int i = 0; i < nrFelii; i++)
//	{
//		if (vector[i].nrFelii == nrFelii)
//		{
//			suma += nrFelii;
//			contor++;
//		}
//	}
//	if (contor > 0)
//	{
//		return suma / contor;
//	}
//	else
//	{
//		return 0;
//	}
//}
//
//int main()
//{
//	Prajitura* prajituri = NULL;
//	int nrPrajituri = 0;
//	prajituri = CitireVectorPrajituriFisier("prajituri.txt", &nrPrajituri);
//	afisareVectorPrajitura(prajituri, nrPrajituri);
//	float medie = calculeazaPretMediuDupaNrFelii(&prajituri, nrPrajituri, 4);
//	printf("Media: %.2f", medie);
//	dezalocareVectorPrajituri(&prajituri, nrPrajituri);
//	return 0;
//}