#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include <string>
#include <ctime>

#include <random>

using namespace std;

#define LATIME_HARTA 50
#define INALTIME_HARTA 50

struct tipHarta {
	int info;
	char caracter;
};

struct nod {
	int x;
	int y;
	int caracter;
	int orientare = 0;
	bool valid = false;
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

void pozitionare_cursor(int x = 0, int y = 0)			//pentru a elimina intreruperile scrierii (stergere eficienta)
{
	HANDLE h;
	COORD pozitie;

	h = GetStdHandle(STD_OUTPUT_HANDLE);

	pozitie.X = x;
	pozitie.Y = y;
	SetConsoleCursorPosition(h, pozitie);
}

void setare_font(int dimensiuneX, int dimensiuneY)
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

void culoare(unsigned short c)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, c);
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

void ascunde_cursor()
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(h, &info);
}

void afisare_meniu(int selectat)
{
	if (selectat == 1)
	{
		pozitionare_cursor(0);
		culoare(10);
		printf("\n\n");
		printf("     *********  *     *     *     *      *  ******                    \n"); culoare(9);
		printf("     *       *  **    *    * *    *     *   *                         \n"); culoare(11);
		printf("     *       *  * *   *   *   *   *    *    *                         \n"); culoare(15);
		printf("     *       *  *  ** *  *     *  *   *     *                         \n"); culoare(14);
		printf("     *          *    **  *     *  *  *      *                         \n"); culoare(13);
		printf("     *          *     *  *     *  * * *     ******                    \n"); culoare(12);
		printf("     *          *     *  *     *  **   *    *                         \n"); culoare(11);
		printf("     *********  *     *  *******  *     *   *                         \n"); culoare(10);
		printf("             *  *     *  *     *  *      *  *                         \n"); culoare(9);
		printf("             *  *     *  *     *  *      *  *                         \n"); culoare(11);
		printf("     *       *  *     *  *     *  *      *  *                         \n"); culoare(15);
		printf("     *       *  *     *  *     *  *      *  *                         \n"); culoare(14);
		printf("     *********  *     *  *     *  *      *  ******                    \n"); culoare(13);
		printf("                                                                      \n"); culoare(12);

		culoare(10);

		printf("                                                                      \n");
		printf("                                                                      \n");
		printf("                >      SINGUR      <                                  \n"); culoare(11);
		printf("                                                                      \n");
		printf("                       CONTRA                                         \n"); culoare(12);
		printf("                                                                      \n");
		printf("                       IESIRE                                         \n");
	}

	if (selectat == 2)
	{
		pozitionare_cursor(0);
		culoare(10);
		printf("\n\n");
		printf("     *********  *     *     *     *      *  ******                    \n"); culoare(9);
		printf("     *       *  **    *    * *    *     *   *                         \n"); culoare(11);
		printf("     *       *  * *   *   *   *   *    *    *                         \n"); culoare(15);
		printf("     *       *  *  ** *  *     *  *   *     *                         \n"); culoare(14);
		printf("     *          *    **  *     *  *  *      *                         \n"); culoare(13);
		printf("     *          *     *  *     *  * * *     ******                    \n"); culoare(12);
		printf("     *          *     *  *     *  **   *    *                         \n"); culoare(11);
		printf("     *********  *     *  *******  *     *   *                         \n"); culoare(10);
		printf("             *  *     *  *     *  *      *  *                         \n"); culoare(9);
		printf("             *  *     *  *     *  *      *  *                         \n"); culoare(11);
		printf("     *       *  *     *  *     *  *      *  *                         \n"); culoare(15);
		printf("     *       *  *     *  *     *  *      *  *                         \n"); culoare(14);
		printf("     *********  *     *  *     *  *      *  ******                    \n"); culoare(13);
		printf("                                                                      \n"); culoare(12);

		culoare(10);

		printf("                                                                      \n");
		printf("                                                                      \n");
		printf("                       SINGUR                                         \n"); culoare(11);
		printf("                                                                      \n");
		printf("                >      CONTRA      <                                  \n"); culoare(12);
		printf("                                                                      \n");
		printf("                       IESIRE                                         \n");
	}

	if (selectat == 3)
	{
		pozitionare_cursor(0);
		culoare(10);
		printf("\n\n");
		printf("     *********  *     *     *     *      *  ******                    \n"); culoare(9);
		printf("     *       *  **    *    * *    *     *   *                         \n"); culoare(11);
		printf("     *       *  * *   *   *   *   *    *    *                         \n"); culoare(15);
		printf("     *       *  *  ** *  *     *  *   *     *                         \n"); culoare(14);
		printf("     *          *    **  *     *  *  *      *                         \n"); culoare(13);
		printf("     *          *     *  *     *  * * *     ******                    \n"); culoare(12);
		printf("     *          *     *  *     *  **   *    *                         \n"); culoare(11);
		printf("     *********  *     *  *******  *     *   *                         \n"); culoare(10);
		printf("             *  *     *  *     *  *      *  *                         \n"); culoare(9);
		printf("             *  *     *  *     *  *      *  *                         \n"); culoare(11);
		printf("     *       *  *     *  *     *  *      *  *                         \n"); culoare(15);
		printf("     *       *  *     *  *     *  *      *  *                         \n"); culoare(14);
		printf("     *********  *     *  *     *  *      *  ******                    \n"); culoare(13);
		printf("                                                                      \n"); culoare(12);

		culoare(10);

		printf("                                                                      \n");
		printf("                                                                      \n");
		printf("                       SINGUR                                         \n"); culoare(11);
		printf("                                                                      \n");
		printf("                       CONTRA                                         \n"); culoare(12);
		printf("                                                                      \n");
		printf("                >      IESIRE      <                                  \n");
	}
}

void afisare_legenda(sarpe s1, sarpe s2)
{
	pozitionare_cursor(60, 2);
	culoare(15);
	printf("SCOR ACTUAL");

	pozitionare_cursor(55, 4);
	culoare(10);
	printf(" TU: %d", s1.lungime);

	if (s2.cap)
	{
		pozitionare_cursor(55, 6);
		culoare(12);
		printf("BOT: %d", s2.lungime);
	}

	pozitionare_cursor(55, 37);
	culoare(14);
	printf("P - PAUZA");

	pozitionare_cursor(55, 39);
	culoare(10);
	printf("R - RESTART");

	pozitionare_cursor(55, 41);
	culoare(12);
	printf("W - SUS");

	pozitionare_cursor(55, 43);
	culoare(13);
	printf("A - STANGA");

	pozitionare_cursor(55, 45);
	culoare(11);
	printf("S - JOS");

	pozitionare_cursor(55, 47);
	culoare(15);
	printf("D - DREAPTA");
}

void actualizare_legenda(sarpe s1, sarpe s2)
{
	pozitionare_cursor(60, 4);
	culoare(10);
	printf("%d", s1.lungime);

	if (s2.cap)
	{
		pozitionare_cursor(60, 6);
		culoare(12);
		printf("%d", s2.lungime);
	}
}

void redimensionare_consola(RECT& dimensiuneOriginala)
{
	HWND consola = GetConsoleWindow();

	GetWindowRect(consola, &dimensiuneOriginala);											 //salvam dimensiunea originala a consolei
	MoveWindow(consola, dimensiuneOriginala.left, dimensiuneOriginala.top, 1000, 660, TRUE); //setam dimensiunea consolei 1000,660
}

void restabileste_setari(RECT dimensiuneOriginala)
{
	HWND consola = GetConsoleWindow();
	MoveWindow(consola, dimensiuneOriginala.left, dimensiuneOriginala.top, dimensiuneOriginala.right, dimensiuneOriginala.bottom, TRUE);
}

void initializare_harta(tipHarta harta[][LATIME_HARTA])
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

void completare_harta(int x, int y, tipHarta harta[][LATIME_HARTA])
{
	if (y == 0)
	{
		harta[y][x].info = 2;
		harta[y][x].caracter = (char)194;
	}
	else
		if (y == INALTIME_HARTA - 1)
		{
			harta[y][x].info = 4;
			harta[y][x].caracter = (char)193;
		}
		else
			if (x == 0)
			{
				harta[y][x].info = 1;
				harta[y][x].caracter = (char)195;
			}
			else
				if (x == LATIME_HARTA - 1)
				{
					harta[y][x].info = 3;
					harta[y][x].caracter = (char)180;
				}
				else
				{
					harta[y][x].info = 0;
					harta[y][x].caracter = (char)197;
				}

	pozitionare_cursor(x, y);
	culoare(1);
	printf("%c", harta[y][x].caracter);
}

void afisare_fruct(tipHarta harta[][LATIME_HARTA], fruct f)
{
	harta[f.y][f.x].info = f.tip;
	harta[f.y][f.x].caracter = (char)178;
	pozitionare_cursor(f.x, f.y);
	culoare(14);
	printf("M");
}

void generare_fruct(fruct& f, tipHarta harta[][LATIME_HARTA], int tip=10)
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

	f.tip = tip;
}

int coliziune(sarpe s, tipHarta harta[][LATIME_HARTA], int supraPunere = 0)				//daca acesta se loveste de sine returneaza orientarea partii de care s-a lovit
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

void afisare_sarpe(sarpe s, tipHarta harta[][LATIME_HARTA])
{
	nod* c = s.cap;
	if (s.numar_sarpe == 1)
		culoare(10);
	else
		culoare(12);

	while (c)
	{
		harta[c->y][c->x].caracter = c->caracter;
		harta[c->y][c->x].info = c->orientare;
		pozitionare_cursor(c->x, c->y);
		printf("%c", c->caracter);
		c = c->urm;
	}
}

int predictie_coliziune(sarpe s, tipHarta harta[][LATIME_HARTA], int x = 0, int y = 0)
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
		if (c->x == s.cap->x + x && c->y == s.cap->y + y)
			return c->orientare;

		if (harta[s.cap->y + y][s.cap->x + x].info < 5 && harta[s.cap->y][s.cap->x].info != 0)
			return harta[s.cap->y + y][s.cap->x + x].info;

		c = c->urm;
	}
	return 0;
}

void bot_sarpe(sarpe& s, fruct fct, tipHarta harta[][LATIME_HARTA])
{
	// ETAPA 1		salveaza opusul positizie din care vine pentru a nu se intoarce 180 de grate
	int d[5] = { 0,0,0,0,0 };
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

	int p = predictie_coliziune(s,harta);


	//	ETAPA 3		verificare coliziuni frontale
	if (p == 3 && s.directie == 1 || p == 1 && s.directie == 3)
	{
		if (predictie_coliziune(s,harta, 1) && predictie_coliziune(s,harta, -1))
		{
			s.directie = s.cap->urm->orientare;
		}
		else
			if (predictie_coliziune(s,harta, 1))
				s.directie = 4;
			else
				s.directie = 2;
	}
	else
		if (p == 4 && s.directie == 2 || p == 2 && s.directie == 4)
		{
			if (predictie_coliziune(s, harta,0, 1) && predictie_coliziune(s,harta, 0, -1))
			{
				s.directie = s.cap->urm->orientare;
			}
			else
				if (predictie_coliziune(s,harta, 0, 1))
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
	p = predictie_coliziune(s,harta);
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

void afisare_harta(tipHarta harta[][LATIME_HARTA])
{
	pozitionare_cursor();
	for (int i = 0; i < INALTIME_HARTA; ++i)
	{
		for (int j = 0; j < LATIME_HARTA; ++j)
		{
			culoare(1);
			printf("%c", harta[i][j].caracter);
		}
		printf("\n");
	}
}

void colectare_fruct(sarpe& s, fruct& f, tipHarta harta[][LATIME_HARTA])
{
	if (s.cap->x == f.x && s.cap->y == f.y)
	{
		dezvoltare_sarpe(s);

		generare_fruct(f,harta);
	}
}

void misca_sarpe(sarpe& s, tipHarta harta[][LATIME_HARTA], int& sfarsitJoc)
{
	nod* c = s.coada;

	completare_harta(c->x, c->y, harta);

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

	if (harta[s.cap->y][s.cap->x].info != 0 && coliziune(s, harta, harta[s.cap->y][s.cap->x].info) < 5)
		sfarsitJoc = s.numar_sarpe;

	s.cap->orientare = s.directie;
}

