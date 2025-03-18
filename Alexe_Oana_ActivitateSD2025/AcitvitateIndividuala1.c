//#include<stdio.h>
//#include<stdlib.h>
//#include<malloc.h>
//
//struct Student
//{
//	int id;
//	char* nume;
//	int varsta;
//	float medieGenerala;
//	char* facultate;
//};
//struct Student initializare(int id, char* nume, int varsta, float medieGenerala, char* facultate)
//{
//	struct Student s;
//	s.id = id;
//	s.varsta = varsta;
//	s.medieGenerala = medieGenerala;
//	if (nume == NULL)
//	{
//		s.nume = NULL;
//	}
//	else
//	{
//		s.nume = (char*)malloc(strlen(nume) + 1);
//		strcpy_s(s.nume, strlen(nume) + 1, nume);
//	}
//	if (facultate == NULL)
//	{
//		s.facultate = NULL;
//	}
//	else
//	{
//		s.facultate = (char*)malloc(strlen(facultate) + 1);
//		strcpy_s(s.facultate, strlen(facultate) + 1, facultate);
//	}
//	return s;
//}
//
//void afisare(struct Student s)
//{
//	printf("Id: %d\n Varsta: %d\n Media generala: %.2f\n Numele: %s\n Facultatea: %s\n", s.id, s.varsta, s.medieGenerala, s.nume, s.facultate);
//}
//
//void afisareVector(struct Student* vector, int nrElem)
//{
//	for (int i = 0; i < nrElem; i++)
//	{
//		afisare(vector[i]);
//	}
//}
//
//
//int main()
//{
//	struct Student s1 = initializare(1, "Ion", 20, 8.6, "CSIE");
//	afisare(s1);
//
//}