#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>

struct Student
{
	int id;
	char* nume;
	int varsta;
	float medieGenerala;
	char* facultate;
};
struct Student initializare(int id, char* nume, int varsta, float medieGenerala, char* facultate)
{
	struct Student s;
	s.id = id;
	s.varsta = varsta;
	s.medieGenerala = medieGenerala;
	if (nume == NULL)
	{
		s.nume = NULL;
	}
	else
	{
		s.nume = (char*)malloc(strlen(nume) + 1);
		strcpy_s(s.nume, strlen(nume) + 1, nume);
	}
	if (facultate == NULL)
	{
		s.facultate = NULL;
	}
	else
	{
		s.facultate = (char*)malloc(strlen(facultate) + 1);
		strcpy_s(s.facultate, strlen(facultate) + 1, facultate);
	}
	return s;
}

void afisare(struct Student s)
{
	printf("Id: %d\n Varsta: %d\n Media generala: %.2f\n Numele: %s\n Facultatea: %s\n", s.id, s.varsta, s.medieGenerala, s.nume, s.facultate);
}

void afisareVector(struct Student* vector, int nrElem)
{
	for (int i = 0; i < nrElem; i++)
	{
		afisare(vector[i]);
	}
}

struct Student* copiazaPrimiiStudenti(struct Student* vector, int nrStudenti, int nrStudentiCopiati)
{
	if (nrStudentiCopiati > nrStudenti)
	{
		nrStudentiCopiati = nrStudenti;
	}

	struct Student* noulVector = NULL;
	noulVector = (struct Student*)malloc(nrStudentiCopiati * sizeof(struct Student));
	for (int i = 0; i < nrStudenti; i++)
	{
		noulVector[i] = initializare(vector[i].id, vector[i].nume, vector[i].varsta, vector[i].medieGenerala, vector[i].facultate);
	}

	return noulVector;
}

void dezaloca(struct Student** vector, int* nrStudenti)
{
	for (int i = 0; i < *nrStudenti; i++)
	{
		free((*vector)[i].nume);
		free((*vector)[i].facultate);
	}
	free(*vector);
	*vector = NULL;
	*nrStudenti = 0;
}

struct Student getPrimulStudentDupaNume(struct Student* vector, int nrStud, const char* conditie)
{
	for (int i = 0; i< nrStud; i++)
	{
		if  (strcmp(vector[i].nume, conditie) == 0)
			return vector[i];
	}
	
	return initializare(1, NULL, 1, 1.0, "-");
}

int main()
{
	struct Student s1 = initializare(1, "Ion", 20, 8.6, "CSIE");
	afisare(s1);


	struct Student* vector;
	int nrElem = 4;
	vector = (struct Student*)malloc(nrElem * sizeof(struct Student));
	vector[0] = initializare(2, "Ana", 21, 9.8, "CIG");
	vector[1] = initializare(3, "Andrei", 20, 6.8, "CIG");
	vector[2] = initializare(4, "Mihai", 22, 7.9, "Drept");
	vector[3] = initializare(5, "Marin", 20, 9.9, "CSIE");
	//afisareVector(vector, 4);


	int nrStudentiCopiati = 2;
	/*struct Student* vectorNou;
	vectorNou = (struct Student*)malloc(nrStudentiCopiati * sizeof(struct Student));
	vectorNou = copiazaPrimiiStudenti(vector, nrElem, nrStudentiCopiati);
	afisareVector(vectorNou, nrStudentiCopiati);*/

	struct Student st = getPrimulStudentDupaNume(&vector, nrElem, "Ana");
	afisareVector(vector, 4);
	dezaloca(&vector, &nrElem);
}