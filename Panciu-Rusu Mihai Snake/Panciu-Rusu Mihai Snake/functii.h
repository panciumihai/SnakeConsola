#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include <ctime>
#include <fstream>
#include <string.h>
#include <mmsystem.h>

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
	int culoareNod = 15;
	nod* urm;
	nod* prec;
};

struct sarpe {
	int directie;
	int lungime = 0;
	int numar_sarpe;
	int culoareSarpe = 15;
	nod* cap;
	nod* coada;

	int timpPutere1 = 0;
	int timpPutere2 = 0;
	int timpPutere3 = 0;
};

struct fruct {
	int x;
	int y;
	int tip = 10;
};

struct scoruri {
	char nume[15]="ANONIM";
	unsigned short scor;
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
	cfi.dwFontSize.X = dimensiuneX;										 // Latime
	cfi.dwFontSize.Y = dimensiuneY;										 // Inaltime
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	cfi.nFont = 0;
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
}

void culoare(unsigned short c)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, c);
}

void creare_chenar(int x1 = 0, int y1 = 0, int x2 = 0, int y2 = 0, int nrCuloare = 15)
{
	culoare(nrCuloare);
	for (int i = y1; i <= y2; ++i)
	{
		pozitionare_cursor(x1, i);
		printf("%c", (char)(186));
		pozitionare_cursor(x2, i);
		printf("%c", (char)(186));
	}

	for (int i = x1; i <= x2; ++i)
	{
		pozitionare_cursor(i, y1);
		printf("%c", (char)(205));
		pozitionare_cursor(i, y2);
		printf("%c", (char)(205));
	}

	pozitionare_cursor(x1, y1);
	printf("%c", (char)(201));

	pozitionare_cursor(x2, y1);
	printf("%c", (char)(187));

	pozitionare_cursor(x1, y2);
	printf("%c", (char)(200));

	pozitionare_cursor(x2, y2);
	printf("%c", (char)(188));
}

void dezvoltare_sarpe(sarpe& s)
{
	if (s.cap == NULL)
	{
		s.cap = new nod;
		if (s.numar_sarpe == 1)
		{
			s.cap->x = 10;
			s.cap->y = 10;
			s.directie = 2;
		}
		else
		{
			s.cap->x = 40;
			s.cap->y = 40;
			s.directie = 4;
		}
		s.cap->valid = true;
		s.cap->caracter = (char)219;
		s.cap->orientare = s.directie;
		s.cap->culoareNod = s.culoareSarpe;

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
		fragment->culoareNod = s.culoareSarpe;

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

void afiseaza_cursor()
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = TRUE;
	SetConsoleCursorInfo(h, &info);
}

void afisare_meniu(int selectat)
{
	if (selectat == 1)
	{
		pozitionare_cursor(0);
		culoare(10);
		printf("\n\n");
		printf("\t      *********  *      *     *     *      *  ******    \n"); culoare(9);
		printf("\t      *       *  **     *    * *    *     *   *    *    \n"); culoare(11);
		printf("\t      *       *  * *    *   *   *   *    *    *         \n"); culoare(15);
		printf("\t      *       *  *  *   *  *     *  *   *     *         \n"); culoare(14);
		printf("\t      *          *   *  *  *     *  *  *      *         \n"); culoare(13);
		printf("\t      *          *    * *  *     *  * * *     ******    \n"); culoare(12);
		printf("\t      *          *     **  *     *  **   *    *         \n"); culoare(11);
		printf("\t      *********  *      *  *******  *     *   *         \n"); culoare(10);
		printf("\t              *  *      *  *     *  *      *  *         \n"); culoare(9);
		printf("\t              *  *      *  *     *  *      *  *         \n"); culoare(11);
		printf("\t      *       *  *      *  *     *  *      *  *         \n"); culoare(15);
		printf("\t      *       *  *      *  *     *  *      *  *    *    \n"); culoare(14);
		printf("\t      *********  *      *  *     *  *      *  ******    \n"); culoare(13);
		printf("\t                                                        \n"); culoare(12);

		culoare(15);
		printf("\t                                                        \n");
		printf("\t                                                        \n");
		printf("\t                              W                         \n");
		printf("\t                            (SUS)                       \n");


		culoare(10);
		printf("\t                                                        \n");
		printf("\t                                                        \n");
		printf("\t                    >      SINGUR      <                \n"); culoare(11);
		printf("\t                                                        \n");
		printf("\t                           CONTRA                       \n"); culoare(12);
		printf("\t                                                        \n");
		printf("\t                           IESIRE                       \n");

		culoare(15);
		printf("\t                                                        \n");
		printf("\t                                                        \n");
		printf("\t                            (JOS)                       \n");
		printf("\t                              S                         \n");
	}

	if (selectat == 2)
	{
		pozitionare_cursor(0);
		culoare(15);
		printf("\n\n");
		printf("\t      *********  *      *     *     *      *  ******    \n"); culoare(11);
		printf("\t      *       *  **     *    * *    *     *   *    *    \n"); culoare(15);
		printf("\t      *       *  * *    *   *   *   *    *    *         \n"); culoare(14);
		printf("\t      *       *  *  *   *  *     *  *   *     *         \n"); culoare(13);
		printf("\t      *          *   *  *  *     *  *  *      *         \n"); culoare(12);
		printf("\t      *          *    * *  *     *  * * *     ******    \n"); culoare(11);
		printf("\t      *          *     **  *     *  **   *    *         \n"); culoare(10);
		printf("\t      *********  *      *  *******  *     *   *         \n"); culoare(9);
		printf("\t              *  *      *  *     *  *      *  *         \n"); culoare(11);
		printf("\t              *  *      *  *     *  *      *  *         \n"); culoare(15);
		printf("\t      *       *  *      *  *     *  *      *  *         \n"); culoare(14);
		printf("\t      *       *  *      *  *     *  *      *  *    *    \n"); culoare(13);
		printf("\t      *********  *      *  *     *  *      *  ******    \n"); culoare(12);
		printf("\t                                                        \n"); culoare(9);

		culoare(15);
		printf("\t                                                        \n");
		printf("\t                                                        \n");
		printf("\t                              W                         \n");
		printf("\t                            (SUS)                       \n");

		culoare(10);
		printf("\t                                                        \n");
		printf("\t                                                        \n");
		printf("\t                           SINGUR                       \n"); culoare(11);
		printf("\t                                                        \n");
		printf("\t                    >      CONTRA      <                \n"); culoare(12);
		printf("\t                                                        \n");
		printf("\t                           IESIRE                       \n");

		culoare(15);
		printf("\t                                                        \n");
		printf("\t                                                        \n");
		printf("\t                            (JOS)                       \n");
		printf("\t                              S                         \n");
	}

	if (selectat == 3)
	{
		pozitionare_cursor(0);
		culoare(12);
		printf("\n\n");
		printf("\t      *********  *      *     *     *      *  ******    \n"); culoare(10);
		printf("\t      *       *  **     *    * *    *     *   *    *    \n"); culoare(9);
		printf("\t      *       *  * *    *   *   *   *    *    *         \n"); culoare(11);
		printf("\t      *       *  *  *   *  *     *  *   *     *         \n"); culoare(15);
		printf("\t      *          *   *  *  *     *  *  *      *         \n"); culoare(13);
		printf("\t      *          *    * *  *     *  * * *     ******    \n"); culoare(14);
		printf("\t      *          *     **  *     *  **   *    *         \n"); culoare(11);
		printf("\t      *********  *      *  *******  *     *   *         \n"); culoare(10);
		printf("\t              *  *      *  *     *  *      *  *         \n"); culoare(9);
		printf("\t              *  *      *  *     *  *      *  *         \n"); culoare(11);
		printf("\t      *       *  *      *  *     *  *      *  *         \n"); culoare(12);
		printf("\t      *       *  *      *  *     *  *      *  *    *    \n"); culoare(13);
		printf("\t      *********  *      *  *     *  *      *  ******    \n"); culoare(10);
		printf("\t                                                        \n"); culoare(9);

		culoare(15);
		printf("\t                                                        \n");
		printf("\t                                                        \n");
		printf("\t                              W                         \n");
		printf("\t                            (SUS)                       \n");

		culoare(10);
		printf("\t                                                        \n");
		printf("\t                                                        \n");
		printf("\t                           SINGUR                       \n"); culoare(11);
		printf("\t                                                        \n");
		printf("\t                           CONTRA                       \n"); culoare(12);
		printf("\t                                                        \n");
		printf("\t                    >      IESIRE      <                \n");

		culoare(15);
		printf("\t                                                        \n");
		printf("\t                                                        \n");
		printf("\t                            (JOS)                       \n");
		printf("\t                              S                         \n");
	}

	pozitionare_cursor(1, 50);
	culoare(15);
	printf("REALIZAT DE: PANCIU-RUSU MIHAI");

	pozitionare_cursor(65, 50);
	printf("AN: 2016-2017");
}

void afisare_legenda(sarpe s1, sarpe s2)
{
	creare_chenar(54,2,75,7,5);
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
	else
	{
		pozitionare_cursor(55, 6);
		printf("           ");
	}

	creare_chenar(54, 34, 75, 49,3);

	pozitionare_cursor(61, 34);
	culoare(15);
	printf("COMENZI");

	pozitionare_cursor(55, 36);
	culoare(9);
	printf(" M - MUT / PORNIT");

	pozitionare_cursor(55, 38);
	culoare(14);
	printf(" P - PAUZA");

	pozitionare_cursor(55, 40);
	culoare(10);
	printf(" R - RESTART");

	pozitionare_cursor(55, 42);
	culoare(12);
	printf(" W - SUS");

	pozitionare_cursor(55, 44);
	culoare(13);
	printf(" A - STANGA");

	pozitionare_cursor(55, 46);
	culoare(11);
	printf(" S - JOS");

	pozitionare_cursor(55, 48);
	culoare(15);
	printf(" D - DREAPTA");
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
	
	switch (f.tip)
	{
	case 11:
		culoare(15);
		printf("F");
		break;
	case 15:
		culoare(11);
		printf("I");
		break;
	case 17:
		culoare(13);
		printf("B");
		break;
	default:
		culoare(14);
		printf("M");
		break;
	}
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

	uniform_int_distribution<> tipFruct(0, 20);
	f.tip = 10+tipFruct(gen);
}

int coliziune(sarpe s, tipHarta harta[][LATIME_HARTA], int supraPunere = 0)				//daca acesta se loveste de sine returneaza orientarea partii de care s-a lovit
{
	if (!s.timpPutere1)
	{
		if (supraPunere != 0)
			return harta[s.cap->y][s.cap->x].info;

		nod* c = s.cap;
		c = c->urm;

		while (c)
		{
			if (c->x == s.cap->x && c->y == s.cap->y)
				return c->orientare;

			if (harta[s.cap->y][s.cap->x].info < 5 && harta[s.cap->y][s.cap->x].info > 0)
				return harta[s.cap->y][s.cap->x].info;
			c = c->urm;
		}
	}
	return 0;
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
		c->caracter = c->prec->caracter;
		c = c->prec;
	}

	s.coada->caracter = (char)(176);
	s.coada->prec->caracter = (char)(177);
	if(s.lungime>3)
		s.coada->prec->prec->caracter = (char)(178);

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
	
	if (s.cap->x == LATIME_HARTA)
		s.cap->x = 0;
	else
	if (s.cap->x == -1)
		s.cap->x = LATIME_HARTA-1;

	if (s.cap->y == INALTIME_HARTA)
		s.cap->y = 0;
	else
	if (s.cap->y == -1)
		s.cap->y = INALTIME_HARTA-1;

	if(!s.timpPutere1)
	if (harta[s.cap->y][s.cap->x].info != 0 && coliziune(s, harta, harta[s.cap->y][s.cap->x].info) < 5)
		sfarsitJoc = s.numar_sarpe;

	s.cap->orientare = s.directie;
}

void afisare_sarpe(sarpe s, tipHarta harta[][LATIME_HARTA])
{
	nod* c = s.cap;
	culoare(s.culoareSarpe);
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

	if (s.timpPutere1)
		return;

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
		if (f.tip == 11)
			s.timpPutere1 += 100;
		
		if (f.tip == 15)
			s.timpPutere2 += 50;

		if (f.tip == 17)
			s.timpPutere3 += 100;

		generare_fruct(f,harta);
	}
}

void importare_scor(scoruri s[])
{
	ifstream f;
	f.open("scor.txt");
	if (f.good())
	{
		unsigned short k = 0;
		while (!f.eof())
		{
			f >> s[k].nume;
			f >> s[k].scor;
			++k;
		}
	}
	else
	{
		ofstream g;
		g.open(("scor.txt"));
		unsigned short k = 0;
		while (k<5)
		{
			g << "nimeni";
			g << "\n";
			g << 0;
			g << "\n";
			++k;
		}
		g.close();
	}
	f.close();
}

void salvare_scor(scoruri s[])
{
	ofstream f;
	f.open("scor.txt", ios::out | ios::trunc);
	unsigned short k = 0;
	while (k<5)
	{
		_strupr(s[k].nume);
		f << s[k].nume;
		f << "\n";
		f << s[k].scor;
		f << "\n";
		++k;
	}
	f.close();
}

void afisare_scor(scoruri s[])
{
	creare_chenar(54, 23, 75, 30,6);
	pozitionare_cursor(61, 23);
	culoare(15);
	printf("RECORDURI");

	unsigned short k = 0;
	while (k < 5)
	{
		pozitionare_cursor(55, 25 + k);
		culoare(14 - k);
		if (strlen(s[k].nume)<7)
			printf("%d.%s\t\t%d\n", k + 1, s[k].nume, s[k].scor);
		else
			printf("%d.%s\t%d\n", k + 1, s[k].nume, s[k].scor);
		++k;
	}
}

void actualizare_scor(scoruri s[], scoruri nou)
{
	scoruri aux;

	unsigned short k = 0;
	while (s[k].scor >= nou.scor)
		++k;

	for (int i = 4; i > k; --i)
	{
		s[i] = s[i - 1];
	}

	s[k] = nou;
}

void inregistrare_scor(scoruri &a, sarpe s)
{
	creare_chenar(54, 31, 75, 33,8);
	pozitionare_cursor(55, 32);
	culoare(15);
	printf("NUME:");
	culoare(10);
	afiseaza_cursor();
	a.scor = s.lungime;
	
		
	pozitionare_cursor(60, 32);
	printf("          ");
	pozitionare_cursor(60, 32);

		//scanf("%14s", a.nume);
	fgets(a.nume, 14, stdin);

	a.nume[strlen(a.nume) - 1] = '\0';

	for (int i = 0; i < 15; ++i)
		if (a.nume[i] == ' ')
			strcpy(a.nume + i, "\0");

	if (a.nume[0] == '\0')
		strcpy(a.nume, "ANONIM");

	
	ascunde_cursor();
}

void curata_ecran()
{
	pozitionare_cursor(0,0);
	for (int i = 0; i <= 52; ++i)
		printf("                                                                                  ");
}

void afisare_puteri()
{
	creare_chenar(54, 8, 64, 15, 2);
	creare_chenar(65, 8, 75, 15, 4);
	pozitionare_cursor(57,8);
	culoare(15);
	printf("PUTERI");
	pozitionare_cursor(67, 8);
	printf("PUTERI");

	pozitionare_cursor(56, 10);
	printf("F:");
	pozitionare_cursor(67, 10);
	printf("F:");

	culoare(11);
	pozitionare_cursor(56, 12);
	printf("I:");
	pozitionare_cursor(67, 12);
	printf("I:");

	culoare(13);
	pozitionare_cursor(56, 14);
	printf("B:");
	pozitionare_cursor(67, 14);
	printf("B:");
}

void actualizeaza_puteri(sarpe s1, sarpe s2)
{
	culoare(15);
	if (s1.timpPutere1)
	{
		pozitionare_cursor(59, 10);
		printf("   ");
		pozitionare_cursor(59, 10);
		printf("%d", s1.timpPutere1);
	}
	else
	{
		pozitionare_cursor(59, 10);
		printf("0  ");
	}

	if (s2.timpPutere1)
	{
		pozitionare_cursor(70, 10);
		printf("   ");
		pozitionare_cursor(70, 10);
		printf("%d", s2.timpPutere1);
	}
	else
	{
		pozitionare_cursor(70, 10);
		printf("0  ");
	}

	culoare(11);
	if (s1.timpPutere2)
	{
		pozitionare_cursor(59, 12);
		printf("   ");
		pozitionare_cursor(59, 12);
		printf("%d", s1.timpPutere2);
	}
	else
	{
		pozitionare_cursor(59, 12);
		printf("0  ");
	}

	if (s2.timpPutere2)
	{
		pozitionare_cursor(70, 12);
		printf("   ");
		pozitionare_cursor(70, 12);
		printf("%d", s2.timpPutere2);
	}
	else
	{
		pozitionare_cursor(70, 12);
		printf("0  ");
	}

	culoare(13);

	if (s1.timpPutere3)
	{
		pozitionare_cursor(59, 14);
		printf("   ");
		pozitionare_cursor(59, 14);
		printf("%d", s1.timpPutere3);
	}
	else
	{
		pozitionare_cursor(59, 14);
		printf("0  ");
	}

	if (s2.timpPutere3)
	{
		pozitionare_cursor(70, 14);
		printf("   ");
		pozitionare_cursor(70, 14);
		printf("%d", s2.timpPutere3);
	}
	else
	{
		pozitionare_cursor(70, 14);
		printf("0  ");
	} 
}

void afisare_joc_terminat(int sfarsitJoc)
{
	pozitionare_cursor(0,10);
	culoare(11);

	printf("                                                  \n");
	printf("        ___   __                 _  _     _       \n");
	printf("       / __| / _| __ _  _ _  ___(_)| |_  | |      \n");
	printf("       \\__ \\|  _|/ _` || '_|(_-<| ||  _| |_|      \n");
	printf("       |___/|_|  \\__,_||_|  /__/|_| \\__| (_)      \n");
	printf("                                                   \n");
	printf("                                                   \n");
	printf("                                                   \n");
	printf("                                                   \n");

	if (sfarsitJoc == 1)
	{
		pozitionare_cursor(20, 16);
		culoare(12);
		printf("AI PIERDUT!");
	}

	if (sfarsitJoc == 2)
	{
		pozitionare_cursor(20, 16);
		culoare(10);
		printf("AI CASTIGAT!");
	}

	if (sfarsitJoc == 3)
	{
		pozitionare_cursor(23, 16);
		culoare(14);
		printf("REMIZA!");
	}

	pozitionare_cursor(0, 50);
}

void schimba_culoare_sarpe(sarpe& s1, sarpe& s2)
{
	if (s2.timpPutere3 != 0 && s2.timpPutere3 % 10 == 0)
		if (s1.culoareSarpe == 10)
			s1.culoareSarpe = 13;
		else
			s1.culoareSarpe = 10;
	else
	if (s1.timpPutere1!=0 && s1.timpPutere1 % 10 == 0)
		if (s1.culoareSarpe == 10)
			s1.culoareSarpe = 15;
		else
			s1.culoareSarpe = 10;

	if (!s1.timpPutere1 && !s2.timpPutere3)
		s1.culoareSarpe = 10;


	if (s1.timpPutere3!=0 && s1.timpPutere3 % 10 == 0)
		if (s2.culoareSarpe == 12)
			s2.culoareSarpe = 13;
		else
			s2.culoareSarpe = 12;
	else
	if (s2.timpPutere1 != 0 && s2.timpPutere1 % 10 == 0)
		if (s2.culoareSarpe == 12)
			s2.culoareSarpe = 15;
		else
			s2.culoareSarpe = 12;

	if (!s2.timpPutere1 && !s1.timpPutere3)
		s2.culoareSarpe = 12;
}

void explicatie_puteri()
{
	creare_chenar(54, 16, 75, 22, 8);
	pozitionare_cursor(61, 16);
	culoare(15);
	printf("DENUMIRI");

	pozitionare_cursor(56, 18);
	printf("F - FANTOMA");

	pozitionare_cursor(56, 19);
	culoare(11);
	printf("I - INCETINESTE");

	pozitionare_cursor(56, 20);
	culoare(13);
	printf("B - BLOCHEAZA");

	pozitionare_cursor(56, 21);
	culoare(14);
	printf("M - MANCARE");
}