#include<iostream>//wypsiywanie
#include<time.h>// losowanie
#include <string.h>

using namespace std;
///////////////////
const int TRUE = 1;
const int FALSE = 0;
const int ILOSC_KART = 13;
const int ILOSC_KOLOR = 4;
const int STALA_PKT = 2;
const int STALA_WIEKSZA = 10;
const int STALA_NAJWIEKSZA = 11;
const int TASOWANIE_MAX = 1000;
const int BLACK_JACK = 21;
const int ZETON = 10;
const int STARTER = 100;
const int HAND = 100;
const int KARTA_WYS = 10;
const int KARTA_SZER = 10;
const int NAZWA_DL = 10;
const int ILOSC_TALI = 3;
/*
2/10 karty = 0-8 ilosc pkt

walet 9
dama 10  rowna ilosc pkt = 10
krol 11

as 12 elastyczna ilosc pkt

kiery 0
piki  1
trefl 2
karo 3
*/


struct Karta {
	int numer;
	int kolor;
	int pkt;
	char nazwa[NAZWA_DL];
};

struct Gracz {
	Karta hand[HAND];          ///przechowuje dobrane karty
	int iloscKart = 0;
	int cash = STARTER;
	int points = 0;
	bool npc = FALSE;
	bool pokazKarty = TRUE;
};
void podajKolor(Karta &karta) {
	if (karta.kolor == 0) {
		strcpy_s(karta.nazwa,5, "KIER");
	}
	else if (karta.kolor == 1) {
		strcpy_s(karta.nazwa,4, "PIK");
	}
	else if (karta.kolor == 2) {
		strcpy_s(karta.nazwa,6, "TREFL");
	}
	else if (karta.kolor == 3) {
		strcpy_s(karta.nazwa, 5,"KARO");
	}
}
int zwrocPunkty(Karta karta) {
	return karta.pkt;
}
void sortujKarty(Gracz gracz){
	for (int i = 0; i < gracz.iloscKart; i++){
		for (int j = 0; j < gracz.iloscKart-1; j++){
			if (gracz.hand[j].numer > gracz.hand[j + 1].numer){
				Karta temp = gracz.hand[j];
				gracz.hand[j] = gracz.hand[j + 1];
				gracz.hand[j + 1] = temp;
			}
		}
	}
}
char zwrocNumerKarty(Karta karta) {//mowi jaka to jest karta
	if (karta.numer >= 0 && karta.numer < 9) return char(karta.numer + 50); //odczytujemy z tablicy asci wartosc charow
	else if (karta.numer == 9) return 'J';
	else if (karta.numer == 10) return 'Q';
	else if (karta.numer == 11) return 'K';
	else if (karta.numer == 12) return 'A';

}
int punktyGracza(Gracz &gracz) { //oblicza laczna ilosc pkt gracza
	sortujKarty(gracz);
	gracz.points = 0;
	for (int i = 0; i < gracz.iloscKart; i++) {
		if (gracz.points + STALA_NAJWIEKSZA <= BLACK_JACK && gracz.hand[i].numer == 12) {
			gracz.points += zwrocPunkty(gracz.hand[i]);
		}
		else if (gracz.points + STALA_NAJWIEKSZA > BLACK_JACK && gracz.hand[i].numer == 12) {
			gracz.points += 1;
		}
		else {
			gracz.points += zwrocPunkty(gracz.hand[i]);
		}
	}
	return gracz.points;
}

//Dobranie
void dobierzKarte(Gracz &gracz, Karta talia[], bool dobrane[]) {
	int index = 0;
	while (dobrane[index] == TRUE) {// TRUE TO DOBRANA KARTA sprawdza czy wartosc w tablicy jest tru
		index++;
	}
	gracz.hand[gracz.iloscKart] = talia[index];
	gracz.iloscKart++;
	dobrane[index] = TRUE;

}



void zapiszKarte(Karta karta, char tab[KARTA_WYS][KARTA_SZER]) {//zapisujemy karte do tablicy
	for (int i = 0; i < KARTA_WYS; i++) {
		for (int j = 0; j < KARTA_SZER; j++) {
			if (i == 0 || i == KARTA_WYS - 1) {
				tab[i][j] = '-';
			}
			else if (j == 0 || j == KARTA_SZER - 1) {
				tab[i][j] = '|';
			}
			else if ((i == 1 && j == 1) || (j == KARTA_SZER - 2 && i == KARTA_WYS - 2)) {
				tab[i][j] = zwrocNumerKarty(karta);
			}
			else if (i == KARTA_WYS / 2 && j == 2) {
				int k = 0;
				while (karta.nazwa[k] != '\0') {
					tab[i][j] = karta.nazwa[k];
					j++;
					k++;
				}
				tab[i][j] = ' ';
			}
			else {
				tab[i][j] = ' ';
			}
		}
	}
}






//ta funkcja definuje karte
void ustawKarte(Karta &karta, int nr, int clr) { //karta musi zostac zapisana 
	karta.kolor = clr;
	karta.numer = nr;

	if (karta.numer >= 0 && karta.numer < 9) {
		karta.pkt = nr + STALA_PKT;
	}
	else if (karta.numer >= 9 && karta.numer < 12) {
		karta.pkt = STALA_WIEKSZA;
	}
	else if (karta.numer == 12) {
		karta.pkt = STALA_NAJWIEKSZA;
	}
}


void generujTalie(Karta talia[]) {
	int iteracja = 0;//karta na ktorej pracujemy 
	for (int i = 0; i < ILOSC_KOLOR; i++) {
		for (int j = 0; j < ILOSC_KART; j++, iteracja++) {
			ustawKarte(talia[iteracja], j, i);
		}
	}
}

void wypiszKarte(Karta talia[]) {
	for (int i = 0; i < ILOSC_KART * ILOSC_KOLOR; i++) {
		cout << talia[i].kolor << " " << talia[i].numer << " " << talia[i].pkt << endl;
	}
}
void zamienMiejscem(Karta talia[]) {
	int ind1 = rand() % (ILOSC_KART*ILOSC_KOLOR);
	int ind2 = rand() % (ILOSC_KART*ILOSC_KOLOR);
	while (ind1 == ind2) {
		ind2 = rand() % (ILOSC_KART*ILOSC_KOLOR);
	}


	Karta temp = talia[ind1];       //zamiana miejscami kart
	talia[ind1] = talia[ind2];
	talia[ind2] = temp;
}
void tasowanieTali(Karta talia[]) {
	int tas = (rand() % TASOWANIE_MAX) + 1;
	for (int i = 0; i < tas; i++) {
		zamienMiejscem(talia);
	}
}

void zerujTablice(bool tab[]) {//zerujemy zeby kazda karta byla niedobrana
	for (int i = 0; i < ILOSC_KART * ILOSC_KOLOR; i++) {
		tab[i] = FALSE;
	}
}

void wypiszKarty(Gracz gracz) {
	char karta[KARTA_WYS][KARTA_SZER]; //pomocnicza tablica do ktorej zapisujemy kolor i karte
	if (gracz.npc == FALSE){
		cout << "karty czlowieka gracza" << endl;
		cout << endl;
	}
	else cout << "karty nalezace do npc" << endl;
	for (int i = 0; i < gracz.iloscKart; i++) {
		podajKolor(gracz.hand[i]);
		zapiszKarte(gracz.hand[i], karta);
		for (int j = 0; j < KARTA_WYS; j++) {
			for (int k = 0; k < KARTA_SZER; k++) {
				cout << karta[j][k];
			}
			cout << endl;
		}
		if (gracz.pokazKarty == FALSE)break;
	}
	if (gracz.npc == FALSE ||(gracz.npc == TRUE &&gracz.pokazKarty == TRUE)){
		cout << endl;
		cout << "punkty gracza: " << endl;
		cout << punktyGracza(gracz) << endl;
	}
}


void ustawTalie(Karta talia[][ILOSC_KART * ILOSC_KOLOR], bool dobrane[][ILOSC_KART * ILOSC_KOLOR]) {
	for (int i = 0; i < ILOSC_TALI; i++) {
		zerujTablice(dobrane[i]);
		generujTalie(talia[i]);
		tasowanieTali(talia[i]);
	}
}
void rozdanie(int ilosc, Gracz &gracz, Karta talia[][ILOSC_KART * ILOSC_KOLOR], bool dobrane[][ILOSC_KART * ILOSC_KOLOR]) { // ilosc to iilos cdobranych kart
	int losuj = 0;
	for (int i = 0; i < ilosc; i++) {
		losuj = rand() % ILOSC_TALI;
		dobierzKarte(gracz, talia[losuj], dobrane[losuj]);
	}
}
bool postawMoney(Gracz &gracz,int &stawka){
		int a = -1;
	if (gracz.cash == 0) {
		system("cls");
		cout << "NIE MASZ PIENIEDZY" << endl;
		cin >> a;
		return FALSE;
	}
	else{
		system("cls");
		while (a > gracz.cash || a ==-1){
			cout << "WITAJ GRACZU!" << endl;
			cout << "ILE POSTAWISZ ZETONOW!" << endl;
			cout << "postawienie 0 rownoa sie porazce :(!" << endl;
			cout << "Twoje wszystkie zetony to lacznie: " << gracz.cash << endl;
			cin >> a;
			if (a == 0) {
				return FALSE;
				gracz.cash = 0;
			}
		}
	}
	stawka = a;
	gracz.cash -= a;
	return TRUE;
}
void krupier(Gracz &npc, Karta talia[][ILOSC_KART * ILOSC_KOLOR], bool dobrane[][ILOSC_KART * ILOSC_KOLOR]){
	if (punktyGracza(npc) < 16){
	rozdanie(1, npc, talia, dobrane);;
	}
	npc.pokazKarty = TRUE;
}
void sterowanie(Gracz &gracz, Gracz &NPC, bool &split, Karta talia[][ILOSC_KART * ILOSC_KOLOR], bool dobrane[][ILOSC_KART * ILOSC_KOLOR],bool &play,bool &game,int &stawka,bool &splitDobrane){
		int input;
		system("cls");
		wypiszKarty(gracz);
		cout <<"stawka gracza to "<<stawka << endl;
		cout << "monety gracza to " << gracz.cash << endl;
		cout << "-----------------------" << endl;
		wypiszKarty(NPC);
		if (gracz.iloscKart >= 2 && splitDobrane== FALSE){
			cout << "Dobierz karte = 1" << endl;
		}
		cout << "Nie dobieraj i pasuj = 2" << endl;
		if (gracz.iloscKart ==2 && gracz.cash >= stawka){
			cout << "Podwoj stawke = 3" << endl;
		}
		if (gracz.iloscKart >=2 && gracz.hand[0].numer == gracz.hand[1].numer)
			cout << "Rozdwoj karty = 4" << endl;
		cin >> input;
		
		if (input == 1 && gracz.iloscKart >= 2 && splitDobrane == FALSE) {
			rozdanie(1, gracz, talia, dobrane);
			if (split == TRUE)
			splitDobrane = TRUE;
		}
		else if (input == 2){
			play = TRUE;
			game = FALSE;
		}
		else if (input == 3 && gracz.iloscKart ==2 && gracz.cash >= stawka){
			split = TRUE;
			gracz.cash -= stawka;
			stawka += stawka;
		}
}
bool EndTurn(Gracz &gracz, Gracz &NPC, bool &game, int &stawka){
	char a;
	if (punktyGracza(gracz) >= punktyGracza(NPC)&& punktyGracza(NPC)<=BLACK_JACK && punktyGracza(gracz)<=BLACK_JACK){
		gracz.cash +=stawka * 2;
		cout << "BRAWO WYGRALES!!!"<<endl;
	}
	else if (punktyGracza(NPC) < punktyGracza(NPC) && punktyGracza(NPC) <= BLACK_JACK && punktyGracza(gracz)<=BLACK_JACK){

	}
	else if (punktyGracza(NPC) > BLACK_JACK){
		gracz.cash += stawka * 2;
		cout << "BRAWO WYGRALES!!!" << endl;
	}
	else {
		cout << "przegrales;(" << endl;
	}

	stawka = 0;
	while (1){
		cout << "Twoje pieniadze to " << gracz.cash << endl;
		cout << "Czy chcesz kontynuowas gre (T/N)?" << endl;
		cin >> a;
		if (toupper(a) == 'T')return TRUE;
		else if (toupper(a) == 'N') return FALSE;
	}
}
bool ponadBLACK_JACK(Gracz gracz){
	char a;
	if (punktyGracza(gracz) > BLACK_JACK){
		cout << "masz ponad 21 pkt przykro nam " << endl;
		cin >> a;
		system("cls");
		return FALSE;
	}
	else {
	system("cls");
		return TRUE;
	}
}
/////////////////////
int main() {
	srand(time(NULL));
	Karta talia[ILOSC_TALI][ILOSC_KART * ILOSC_KOLOR];
	bool dobrane[ILOSC_TALI][ILOSC_KART * ILOSC_KOLOR];
	bool split = FALSE;
	bool splitDobrane = FALSE;
	bool startGry;
	bool play = FALSE;
	int stawka;
	Gracz gracz;
	Gracz NPC;
	NPC.npc = TRUE;
	NPC.pokazKarty = FALSE;


	cout << gracz.points;
	cout << endl;
	
	bool Gra = TRUE;
	while (gracz.cash != 0){
		gracz.points = 0;
		NPC.points = 0;
		gracz.iloscKart = 0;
		NPC.iloscKart = 0;
		Gra = postawMoney(gracz, stawka);
		NPC.pokazKarty = FALSE;
		startGry = FALSE;
		splitDobrane = FALSE;
		split = FALSE;
		while (Gra){
			if (startGry == FALSE){
				ustawTalie(talia, dobrane);
				rozdanie(2, gracz, talia, dobrane);
				rozdanie(2, NPC, talia, dobrane);
				splitDobrane = FALSE;
				startGry = TRUE;

			}
			if (!ponadBLACK_JACK(gracz)) break;
			sterowanie(gracz, NPC, split, talia, dobrane,play,Gra,stawka,splitDobrane);
			if (play == TRUE){
				krupier(NPC, talia, dobrane);
				NPC.pokazKarty = TRUE;
				play = FALSE;
				Gra = FALSE;
			}
			system("cls");
		}
		wypiszKarty(gracz);
		wypiszKarty(NPC);
		if (!EndTurn(gracz,NPC,Gra,stawka))break;
	}
}