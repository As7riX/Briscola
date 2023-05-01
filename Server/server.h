/*
#pragma once

#include <stdlib.h>
#include <iostream>
#include <vector>
#include <random>
#include <time.h>
#include <cstdlib>
#include <algorithm> 

using namespace std;

//Classe carta
class Carta {

public:
	enum semi { cuori, quadri, fiori, picche };	//semi
	enum valore { asso, due, tre, quattro, cinque, sei, sette, fante, donna, re }; //valori

	//creazione carta e attribuzione punteggio
	Carta(semi, valore);

	//metodi get info
	valore get_valore() { return Valore; }
	semi get_seme() { return Seme; }
	int get_punteggio() { return punteggio; }

private:
	semi Seme;
	valore Valore;
	int punteggio = 0;
};


//Classe mazzo
class Mazzo {
private:
	vector<Carta> carte_mazzo; //mazzo
	int carte_rim = 0;

public:
	Mazzo();
	void Randomizza();
	Carta get_carta();
};
*/