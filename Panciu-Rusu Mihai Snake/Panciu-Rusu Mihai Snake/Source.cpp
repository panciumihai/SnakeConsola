#include "functii.h"

HANDLE hConsole;
CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
WORD saved_attributes;

RECT dimensiuneOriginala;

int sfarsitJoc = 0;
int joc = 0;

tipHarta harta[INALTIME_HARTA][LATIME_HARTA];

sarpe sarpe1;
sarpe sarpe2;
fruct f;

int contor=0;

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
		case 'b': //prima_pagina(sarpe1,sarpe2,joc);
			break;
		}
	}
}

void joc_singur()
{
	while (!sfarsitJoc)
	{
		schimba_directia(sarpe1);

		colectare_fruct(sarpe1, f, harta);

		misca_sarpe(sarpe1, harta, sfarsitJoc);

		initializare_harta(harta);

		afisare_fruct(harta, f);
		afisare_sarpe(sarpe1, harta);
		actualizare_legenda(sarpe1, sarpe2);

		Sleep(60);
	}
	pozitionare_cursor(0, 50);
}

void joc_dublu()
{
	while (!sfarsitJoc)
	{
		schimba_directia(sarpe1);

		bot_sarpe(sarpe2, f, harta);

		colectare_fruct(sarpe1, f, harta);
		colectare_fruct(sarpe2, f, harta);

		misca_sarpe(sarpe1, harta, sfarsitJoc);
		misca_sarpe(sarpe2, harta, sfarsitJoc);

		initializare_harta(harta);

		afisare_fruct(harta, f);
		afisare_sarpe(sarpe1, harta);
		afisare_sarpe(sarpe2, harta);
		actualizare_legenda(sarpe1,sarpe2);

		Sleep(60);
	}
	pozitionare_cursor(0, 50);
}

void start_joc()
{
	if (joc == 1)
	{
		sarpe1.numar_sarpe = 1;

		generare_fruct(f, harta);
		dezvoltare_sarpe(sarpe1);
		dezvoltare_sarpe(sarpe1);
		dezvoltare_sarpe(sarpe1);

		initializare_harta(harta);
		afisare_harta(harta);

		afisare_legenda(sarpe1, sarpe2);
		joc_singur();
	}
	else
	{
		sarpe1.numar_sarpe = 1;
		sarpe2.numar_sarpe = 2;

		generare_fruct(f, harta);
		dezvoltare_sarpe(sarpe1);
		dezvoltare_sarpe(sarpe1);
		dezvoltare_sarpe(sarpe1);

		dezvoltare_sarpe(sarpe2);
		dezvoltare_sarpe(sarpe2);
		dezvoltare_sarpe(sarpe2);
		sarpe2.cap->x = 40;
		sarpe2.cap->y = 5;
		sarpe2.directie = 4;

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
	s1.cap = 0;
	s1.coada = 0;
	s2.cap = 0;
	s2.cap = 0;
	tipJoc = 1;
	afisare_meniu(tipJoc);

	while (tipJoc)
	{
		meniu(tipJoc);
	}
}

/*
void craniu()
{
	printf("_______________________________________________________");
	printf("	/ \");
printf(" | Ha ha, you're dead                    |");
printf("		\_________              _______________________________ /");
	printf("	\_         __ / ___-------- - __");
		printf("	\      _ / / \_");
			printf("	\ / / \");
	printf("	| / | _    _ \          \");
				printf("	| | / / \ / \ | \");
	printf("	| | || || || |");
					printf("		| | | \_//\\_/ |           |        ");
						printf("		| | | _ | (|| ) | _______ | |");
							printf("	| | | || | _ / / |");
								printf("	\ \ | _________ || \ / / /");
									printf("	\ \_ | _ | _ | _ | _ | / | _ / ___ /");
										printf("	\__>       _ _ / _ _ / |");
											printf("	. | _ | _ | _ | _ | |");
												printf("	| /");
												printf("	| __________ /");

}
*/
void main()
{                                                                          

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
	saved_attributes = consoleInfo.wAttributes;
	

	setare_font(14, 12);
	ascunde_cursor();
	redimensionare_consola(dimensiuneOriginala);

//	joc = 1;
//	start_joc();
	prima_pagina(sarpe1,sarpe2,joc);
}