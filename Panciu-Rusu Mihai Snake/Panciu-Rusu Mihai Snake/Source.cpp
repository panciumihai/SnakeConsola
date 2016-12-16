#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include <string>
#include <ctime>

#include <random>

using namespace std;

#define LATIME_HARTA 50
#define INALTIME_HARTA 50

int sfarsitJoc = 0;

struct tipHarta {
	int info;
	char caracter;
};

struct nod {
	int x;
	int y;
	int caracter;
	int orientare=0;
	bool valid=false;
	nod* urm;
	nod* prec;
};

struct sarpe {
	int directie = 2;
	int lungime = 0;
	int numar_sarpe;
	nod* cap;
	nod* coada;
};

struct fruct {
	int x;
	int y;
	int tip = 10;
};

tipHarta harta[INALTIME_HARTA][LATIME_HARTA];

sarpe sarpe1;
sarpe sarpe2;
fruct f;

RECT dimensiuneOriginala;

int contor=0;

void initializare_harta()
{
	for (int i = 0; i < INALTIME_HARTA; ++i)
		for (int j = 0; j < LATIME_HARTA; ++j)
			if (i == 0)
			{
				harta[i][j].info = 2;
				harta[i][j].caracter = (char)194;
			}
			else
				if (i == INALTIME_HARTA - 1)
				{
					harta[i][j].info = 4;
					harta[i][j].caracter = (char)193;
				}
				else
					if (j == 0)
					{
						harta[i][j].info = 1;
						harta[i][j].caracter = (char)195;
					}
					else
						if (j == LATIME_HARTA - 1)
						{
							harta[i][j].info = 3;
							harta[i][j].caracter = (char)180;
						}
						else
						{
							harta[i][j].info = 0;
							harta[i][j].caracter = (char)197;
						}
}

void generare_fruct(int tip)
{
	random_device rd;

	mt19937 gen(rd());
	uniform_int_distribution<> randX(1, LATIME_HARTA - 2);
	uniform_int_distribution<> randY(1, INALTIME_HARTA - 2);
	f.x = randX(gen);
	f.y = randY(gen);

	while (harta[f.y][f.y].info != 0)
	{
		f.x = randX(gen);
		f.y = randY(gen);
	}

	++contor;
	f.tip = tip;
}

void afisare_fruct()
{
	harta[f.y][f.x].info = f.tip;
	harta[f.y][f.x].caracter = (char)178;
}

void dezvoltare_sarpe(sarpe& s)
{
	if (s.cap == NULL)
	{
		s.cap = new nod;
		s.cap->x = 1;
		s.cap->y = 1;
		s.cap->valid = true;
		s.cap->caracter = (char)219;
		s.cap->orientare = s.directie;

		s.cap->urm = 0;
		s.cap->prec = 0;
		s.coada = s.cap;
	}
	else
	{
		nod* fragment = new nod;
		fragment->x = s.coada->x;
		fragment->y = s.coada->y;
		fragment->caracter = (char)219;
		fragment->orientare = s.coada->orientare;

		fragment->urm = 0;
		fragment->prec = s.coada;
		s.coada->urm = fragment;
		s.coada = fragment;
	}
	++s.lungime;
}

void colectare_fruct(sarpe& s)
{
	if (s.cap->x == f.x && s.cap->y == f.y)
	{
		dezvoltare_sarpe(s);
		generare_fruct(10);
	}
}

void terminare_joc(int pierzator)
{
	sfarsitJoc = 1;
	printf("\nA murit sarpele:%d", pierzator);
}

int coliziune(sarpe s, int supraPunere = 0)				//daca acesta se loveste de sine returneaza orientarea partii de care s-a lovit
{
	if (supraPunere != 0)
		return harta[s.cap->y][s.cap->x].info;

	nod* c = s.cap;
	c = c->urm;
	while (c)
	{
		if (c->x == s.cap->x && c->y == s.cap->y)
			return c->orientare;

		if (harta[s.cap->y][s.cap->x].info < 5 && harta[s.cap->y][s.cap->x].info != 0)
			return harta[s.cap->y][s.cap->x].info;
		c = c->urm;
	}
	return 0;
}

void misca_sarpe(sarpe& s)
{
	nod* c = s.coada;
	while (c->prec)
	{
		c->x = c->prec->x;
		c->y = c->prec->y;
		c->orientare = c->prec->orientare;
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

	if (harta[s.cap->y][s.cap->x].info != 0 && coliziune(s, harta[s.cap->y][s.cap->x].info) < 5)
		terminare_joc(s.numar_sarpe);

	s.cap->orientare = s.directie;
}

void schimba_directia(sarpe& s)
{
	if (_kbhit())
	{
		switch (_getch())
		{
			case 'w':if (s.directie != 3)
				s.directie=1; break;
			case 'a':if (s.directie != 2)
				s.directie=4; break;
			case 's':if (s.directie != 1)
				s.directie=3; break;
			case 'd':if (s.directie != 4)
				s.directie=2; break;
		}
	}
}

void afisare_sarpe(sarpe s)
{
	nod* c = s.cap;
	while (c)
	{
		harta[c->y][c->x].caracter = c->caracter;

		harta[c->y][c->x].info = c->orientare;
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

int predictie_coliziune(sarpe s, int x=0,int y=0)
{
	nod* c = s.cap;

	switch (s.directie)
	{
	case 1:	--y;
		break;
	case 2:	++x;
		break;
	case 3:	++y;
		break;
	case 4:	--x;
		break;
	default:
		break;
	}

	c = c->urm;
	while (c)
	{
		if (c->x == s.cap->x+x && c->y == s.cap->y+y)
			return c->orientare;

		if (harta[s.cap->y + y][s.cap->x + x].info < 5 && harta[s.cap->y][s.cap->x].info != 0)
			return harta[s.cap->y + y][s.cap->x + x].info;

		c = c->urm;
	}
	return 0;
}

void bot_sarpe(sarpe& s, fruct fct)
{	
	// ETAPA 1		salveaza opusul positizie din care vine pentru a nu se intoarce 180 de grate
	int d[5] = {0,0,0,0,0};
	int daux = s.directie + 2;
	if (daux > 4)
		daux -= 4;

	++d[daux];

	// ETAPA 2		orientarea catre tinta
	if (s.cap->x < fct.x && s.directie != 4)
		s.directie = 2;
	else
	if (s.cap->x > fct.x && s.directie != 2)
		s.directie = 4;
	else
	if (s.cap->y < fct.y && s.directie != 1)
		s.directie = 3;
	else
	if (s.cap->y > fct.y && s.directie != 3)
		s.directie = 1;

	++d[s.directie];
	int p = predictie_coliziune(s);


	//	ETAPA 3		verificare coliziuni frontale
	if (p == 3 && s.directie == 1 || p == 1 && s.directie == 3)
	{
		if (predictie_coliziune(s, 1) && predictie_coliziune(s, -1))
		{
			s.directie = s.cap->urm->orientare;
		}
		else
			if (predictie_coliziune(s, 1))
				s.directie = 4;
			else
				s.directie = 2;
	}
	else
		if (p == 4 && s.directie == 2 || p == 2 && s.directie == 4)
		{
			if (predictie_coliziune(s, 0, 1) && predictie_coliziune(s, 0, -1))
			{
						s.directie = s.cap->urm->orientare;
			}
			else
				if (predictie_coliziune(s, 0, 1))
					s.directie = 1;
				else
					s.directie = 3;
		}
		else
		{
			if (p)
			{
				s.directie = p + 2;
				if (s.directie > 4)
					s.directie -= 4;
			}
		}
	
	++d[s.directie];

	//	ETAPA 4		Alege ultima directie pe care o mai are
	p = predictie_coliziune(s);
	if (p)
	{
		for (int i = 1; i <= 4; ++i)
			if (d[i] == 2)
			{
				for (int j = 1; j <= 4; ++j)
					if (d[j] == 1)
						s.directie = j + 2;
				if (s.directie > 4)
					s.directie -= 4;
			}
			else
			{
				if (!d[i])
					s.directie = i;
			}
	}

}

HANDLE hConsole;
CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
WORD saved_attributes;

void tiparie_element(char c, int culoare)
{
	//SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);

	printf("%c", c);
	//SetConsoleTextAttribute(hConsole, saved_attributes);
}

void restabileste_setari()
{
	HWND consola = GetConsoleWindow();
	MoveWindow(consola, dimensiuneOriginala.left, dimensiuneOriginala.top, dimensiuneOriginala.right, dimensiuneOriginala.bottom, TRUE);
}

void afisare_harta()
{
	sterge_ecran();
	//system("COLOR 0A");
	for (int i = 0; i < INALTIME_HARTA; ++i)
	{
		for (int j = 0; j < LATIME_HARTA; ++j)
		{
			int culoare = 0;
			if (harta[i][j].caracter >= 180 && harta[i][j].caracter <= 197)
				culoare = 23;
			
			printf("%c", harta[i][j].caracter);
		}
		printf("\n");
	}
	printf("Contor: %d", contor);
}

void joc()
{
	int i = 0;
	while (!sfarsitJoc)
	{
		schimba_directia(sarpe1);
		bot_sarpe(sarpe2,f);

		colectare_fruct(sarpe1);
		colectare_fruct(sarpe2);

		misca_sarpe(sarpe1);
		misca_sarpe(sarpe2);
		initializare_harta();
		
		afisare_fruct();
		afisare_sarpe(sarpe1);
		afisare_sarpe(sarpe2);
		afisare_harta();
		
		Sleep(60);
	}
}

void main()
{
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);


	GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
	saved_attributes = consoleInfo.wAttributes;
	

	setare_font(14, 12);
	ascunde_cursor();
	redimensionare_consola();

	sarpe1.numar_sarpe = 1;
	sarpe2.numar_sarpe = 2;

	generare_fruct(10);
	dezvoltare_sarpe(sarpe1);
	dezvoltare_sarpe(sarpe1);
	dezvoltare_sarpe(sarpe1);

	dezvoltare_sarpe(sarpe2);
	dezvoltare_sarpe(sarpe2);
	dezvoltare_sarpe(sarpe2);
	sarpe2.cap->x = 40;
	sarpe2.cap->y = 5;
	sarpe2.directie = 4;

	joc();
}