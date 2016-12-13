#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include <string>

using namespace std;

#define LATIME_HARTA 50
#define LUNGIME_HARTA 50

int harta[LUNGIME_HARTA][LATIME_HARTA];
int sfarsitJoc = 0;

struct nod {
	int x;
	int y;
	int caracter;
	bool valid=false;
	nod* urm;
	nod* prec;
};

struct sarpe {
	int directie = 2;
	nod* cap;
	nod* coada;
};

sarpe sarpe1;
sarpe sarpe2;

void initializare_harta()
{
	for (int i = 0; i < LUNGIME_HARTA; ++i)
		for (int j = 0; j < LATIME_HARTA; ++j)
			harta[i][j] = 0;
}

void dezvoltare_sarpe(sarpe& s)
{
	if (s.cap == NULL)
	{
		s.cap = new nod;
		s.cap->x = 5;
		s.cap->y = 5;
		s.cap->valid = true;
		s.cap->caracter = 1;

		s.cap->urm = 0;
		s.cap->prec = 0;
		s.coada = s.cap;
	}
	else
	{
		nod* fragment = new nod;
		fragment->x = s.coada->x;
		fragment->y = s.coada->y;
		fragment->caracter = 1;

		fragment->urm = 0;
		fragment->prec = s.coada;
		s.coada->urm = fragment;
		s.coada = fragment;
	}
}

void misca_sarpe(sarpe& s)
{
	nod* c = s.coada;
	while (c->prec)
	{
		c->x = c->prec->x;
		c->y = c->prec->y;
		c = c->prec;
	}

	switch (s.directie)
	{
	case 1:	--s.cap->y;
			break;
	case 2:	++s.cap->x;
			break;
	case 3:	++s.cap->y;
			break;
	case 4:	--s.cap->x;
			break;
	default:
		break;
	}
}

void schimba_directia(sarpe& s)
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'w':s.directie=1; break;
		case 'a':s.directie=4; break;
		case 's':s.directie=3; break;
		case 'd':s.directie=2; break;
		}
	}
}

void afisare_sarpe(sarpe s)
{
	nod* c = s.cap;
	while (c)
	{
		harta[c->y][c->x] = c->caracter;
		c = c->urm;
	}
}

void setare_font(int dimensiuneX,int dimensiuneY)
{
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = dimensiuneX;										 // Latime
	cfi.dwFontSize.Y = dimensiuneY;										 // Inaltime
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
}


void stergeEcran()			//pentru a elimina intreruperile scrierii (stergere eficienta)
{
	HANDLE h;
	COORD pozitie;

	h = GetStdHandle(STD_OUTPUT_HANDLE);

	pozitie.X = 0;
	pozitie.Y = 0;
	SetConsoleCursorPosition(h, pozitie);
}


void afisare_harta()
{
	stergeEcran();
	for (int i = 0; i < LUNGIME_HARTA; ++i)
	{
		for (int j = 0; j < LATIME_HARTA; ++j)
		{
			switch (harta[i][j])
			{
			case 0:printf("%c", (char)(32)); break;
			case 1:printf("%c", (char)(219)); break;
			default:printf("");
				break;
			}
		}
		printf("\n");
	}
	
}

void joc()
{
	int i = 0;
	while (!sfarsitJoc)
	{
		/*		Limitare directie
		if (sarpe1.cap->x==20 && sarpe1.directie == 2)
			sarpe1.directie = 3;
		else
			if (sarpe1.cap->y == 20 && sarpe1.directie == 3)
				sarpe1.directie = 4;
			else
				if (sarpe1.cap->x == 5 && sarpe1.directie == 4)
					sarpe1.directie = 1;
				else
					if (sarpe1.cap->y == 5 && sarpe1.directie == 1)
						sarpe1.directie = 2;
		*/

		initializare_harta();
		misca_sarpe(sarpe1);
		afisare_sarpe(sarpe1);
		afisare_harta();
		Sleep(50);
	}
}

void main()
{
	setare_font(12,12);
	dezvoltare_sarpe(sarpe1);
	dezvoltare_sarpe(sarpe1);
	dezvoltare_sarpe(sarpe1);
	joc();
}