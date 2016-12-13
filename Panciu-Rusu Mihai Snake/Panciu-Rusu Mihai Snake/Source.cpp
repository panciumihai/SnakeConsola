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

struct fruct {
	int x;
	int y;
	int tip = 10;
};

sarpe sarpe1;
sarpe sarpe2;
fruct f;

RECT dimensiuneOriginala;

void initializare_harta()
{
	for (int i = 0; i < LUNGIME_HARTA; ++i)
		for (int j = 0; j < LATIME_HARTA; ++j)
			harta[i][j] = 0;
}

void generare_fruct(int tip)
{
	f.x = rand() % LATIME_HARTA;
	f.y = rand() % LUNGIME_HARTA;
	f.tip = tip;
}

void afisare_fruct()
{
	harta[f.y][f.x] = f.tip;
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

void colectare_fruct(sarpe& s)
{
	if (s.cap->x == f.x && s.cap->y == f.y)
	{
		dezvoltare_sarpe(s);
		generare_fruct(10);
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

void sterge_ecran()			//pentru a elimina intreruperile scrierii (stergere eficienta)
{
	HANDLE h;
	COORD pozitie;

	h = GetStdHandle(STD_OUTPUT_HANDLE);

	pozitie.X = 0;
	pozitie.Y = 0;
	SetConsoleCursorPosition(h, pozitie);
}

void ascunde_cursor()
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(h, &info);
}

void redimensionare_consola()
{
	HWND consola = GetConsoleWindow();
	GetWindowRect(consola, &dimensiuneOriginala);											 //salvam dimensiunea originala a consolei
	MoveWindow(consola, dimensiuneOriginala.left, dimensiuneOriginala.top, 1000, 660, TRUE); //setam dimensiunea consolei 1000,660
}

void restabileste_setari()
{
	HWND consola = GetConsoleWindow();
	MoveWindow(consola, dimensiuneOriginala.left, dimensiuneOriginala.top, dimensiuneOriginala.right, dimensiuneOriginala.bottom, TRUE);
}

void afisare_harta()
{
	sterge_ecran();
	for (int i = 0; i < LUNGIME_HARTA; ++i)
	{
		for (int j = 0; j < LATIME_HARTA; ++j)
		{
			switch (harta[i][j])
			{
			case 0:printf("%c", (char)(32)); break;
			case 1:printf("%c", (char)(219)); break;
			case 10:printf("%c", (char)(210)); break;
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
		schimba_directia(sarpe1);

		colectare_fruct(sarpe1);
		initializare_harta();
		misca_sarpe(sarpe1);
		afisare_fruct();
		afisare_sarpe(sarpe1);
		afisare_harta();
		Sleep(50);
	}
}

void main()
{
	setare_font(14, 12);
	ascunde_cursor();
	redimensionare_consola();

	generare_fruct(10);
	dezvoltare_sarpe(sarpe1);
	dezvoltare_sarpe(sarpe1);
	dezvoltare_sarpe(sarpe1);
	joc();
}