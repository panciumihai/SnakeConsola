#include <stdio.h>
#include <conio.h>
#include <Windows.h>

using namespace std;

#define LATIME_HARTA 25
#define LUNGIME_HARTA 25

int harta[LUNGIME_HARTA][LATIME_HARTA];
int sfarsitJoc = 0;

void initializare_harta()
{
	for (int i = 0; i < LUNGIME_HARTA; ++i)
		for (int j = 0; j < LATIME_HARTA; ++j)
			harta[i][j] = 0;
}

void afisare_harta()
{
	system("cls");
	for (int i = 0; i < LUNGIME_HARTA; ++i)
	{
		for (int j = 0; j < LATIME_HARTA; ++j)
		{
			switch (harta[i][j])
			{
			case 0:printf(" "); break;
			default:printf("");
				break;
			}
		}
		printf("\n");
	}
}

void joc()
{
	while (!sfarsitJoc)
	{
		initializare_harta();
		afisare_harta();
	}
}

void main()
{
	joc();
}