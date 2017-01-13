#include "functii.h"

RECT dimensiuneOriginala;

int sfarsitJoc = 0;
int joc = 0;
bool sunet = false;

tipHarta harta[INALTIME_HARTA][LATIME_HARTA];

sarpe sarpe1;
sarpe sarpe2;
fruct f;

scoruri clasament[5];
scoruri actual;

int contor=0;

void porneste_sunet()
{
	if (sunet == false)
	{
		PlaySound(TEXT("muzica.wav"), NULL, SND_LOOP | SND_ASYNC);
		sunet = true;
	}
	else
	{
		PlaySound(NULL, NULL, 0);
		sunet = false;
	}
}

void schimba_directia(sarpe& s)
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'w':if (s.directie != 3)
			s.directie = 1; break;
		case 'a':if (s.directie != 2)
			s.directie = 4; break;
		case 's':if (s.directie != 1)
			s.directie = 3; break;
		case 'd':if (s.directie != 4)
			s.directie = 2; break;
		case 'p':
			pozitionare_cursor(0, 50);
			system("pause");
			pozitionare_cursor(0, 50);
			printf("                                 ");
			pozitionare_cursor(0, 0); break;
		case 'r': sfarsitJoc = 1;
			break;
		case 'm': porneste_sunet();
			break;
		}
	}
}

void putere(sarpe& s)
{
	if(s.timpPutere1>0)
		--s.timpPutere1;

	if (s.timpPutere2>0)
		--s.timpPutere2;

	if (s.timpPutere3>0)
		--s.timpPutere3;
}

void joc_singur()
{
	while (!sfarsitJoc)
	{
		schimba_directia(sarpe1);

		colectare_fruct(sarpe1, f, harta);

		misca_sarpe(sarpe1, harta, sfarsitJoc);

		initializare_harta(harta);

		f.tip = 10;
		afisare_fruct(harta, f);
		afisare_sarpe(sarpe1, harta);
		actualizare_legenda(sarpe1, sarpe2);

		Sleep(60);
	}
	pozitionare_cursor(0, 50);
}

void joc_dublu()
{
	afisare_puteri();
	explicatie_puteri();
	while (!sfarsitJoc)
	{
		schimba_directia(sarpe1);

		bot_sarpe(sarpe2, f, harta);

		colectare_fruct(sarpe1, f, harta);
		colectare_fruct(sarpe2, f, harta);

		actualizeaza_puteri(sarpe1, sarpe2);

		if(!sarpe2.timpPutere3)
			misca_sarpe(sarpe1, harta, sfarsitJoc);

		if (!sarpe1.timpPutere3)
			misca_sarpe(sarpe2, harta, sfarsitJoc);

		putere(sarpe1);
		putere(sarpe2);

		initializare_harta(harta);

		afisare_fruct(harta, f);

		schimba_culoare_sarpe(sarpe1, sarpe2);
		afisare_sarpe(sarpe1, harta);
		afisare_sarpe(sarpe2, harta);

		if ((!sarpe1.timpPutere1 && !sarpe2.timpPutere2) && sarpe1.cap->x == sarpe2.cap->x && sarpe1.cap->y == sarpe2.cap->y)
			sfarsitJoc = 3;

		actualizare_legenda(sarpe1,sarpe2);
		Sleep(60+sarpe1.timpPutere2+sarpe2.timpPutere2);
	}
	pozitionare_cursor(0, 50);
	joc = 0;
}

void start_joc()
{
	curata_ecran();
	afisare_scor(clasament);
	if (joc == 1)
	{
		generare_fruct(f, harta);

		dezvoltare_sarpe(sarpe1);
		dezvoltare_sarpe(sarpe1);
		dezvoltare_sarpe(sarpe1);

		sarpe1.lungime -= 3;

		initializare_harta(harta);

		afisare_harta(harta);
		afisare_legenda(sarpe1, sarpe2);

		joc_singur();
	}
	else
	{
		generare_fruct(f, harta);

		dezvoltare_sarpe(sarpe1);
		dezvoltare_sarpe(sarpe1);
		dezvoltare_sarpe(sarpe1);

		dezvoltare_sarpe(sarpe2);
		dezvoltare_sarpe(sarpe2);
		dezvoltare_sarpe(sarpe2);

		sarpe1.lungime -= 3;
		sarpe2.lungime -= 3;

		initializare_harta(harta);

		afisare_harta(harta);
		afisare_legenda(sarpe1, sarpe2);

		joc_dublu();
	}
}

void meniu(int& joc)
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'w':if (joc == 1)
			joc = 3;
				 else
					 joc--;
			afisare_meniu(joc); break;
		case 's':if (joc == 3)
			joc = 1;
				 else
					 joc++;
			afisare_meniu(joc); break;
		case '\r': if (joc != 3)start_joc();
				   else
					   exit(0);
			joc = 0; break;
		}
	}
}

void prima_pagina(sarpe& s1, sarpe& s2, int& tipJoc)
{
	if (s1.cap)
	{
		s1.cap = 0;
		delete s1.cap;
		s1.lungime = 0;
		s1.timpPutere1 = 0;
		s1.timpPutere2 = 0;
		s1.timpPutere3 = 0;
	}
	if (s2.cap)
	{
		s2.cap = 0;
		delete s2.cap;
		s2.lungime = 0;
		s2.timpPutere1 = 0;
		s2.timpPutere2 = 0;
		s2.timpPutere3 = 0;
	}

	tipJoc = 1;
	sfarsitJoc = 0;
	afisare_meniu(tipJoc);

	while (tipJoc)
	{
		meniu(tipJoc);
	}
}

int main()
{                                                                          
	setare_font(14, 12);
	ascunde_cursor();
	redimensionare_consola(dimensiuneOriginala);

	sarpe1.numar_sarpe = 1;
	sarpe1.culoareSarpe = 10;

	sarpe2.numar_sarpe = 2;
	sarpe2.culoareSarpe = 12;

	importare_scor(clasament);
	porneste_sunet();

	while (!joc)
	{
		prima_pagina(sarpe1, sarpe2, joc);
		afisare_joc_terminat(sfarsitJoc);
		
		if (sarpe1.lungime >= clasament[4].scor)
		{
			inregistrare_scor(actual, sarpe1);
			actualizare_scor(clasament, actual);
			salvare_scor(clasament);
		}
		else
		{
			system("pause");
		}
		curata_ecran();
	}

	restabileste_setari(dimensiuneOriginala);
	return EXIT_SUCCESS;
}