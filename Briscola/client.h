#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <io.h>
#include <fcntl.h>
#include <map>
#include <Windows.h>
#include "gamemode/gamemode.h"
//#include "lib/ColorConsole.hpp"

using namespace std;

class Carta {

public:
	enum semi { cuori, quadri, fiori, picche };	//semi
	enum valore { asso, due, tre, quattro, cinque, sei, sette, otto, nove, dieci, fante, donna, re, jolly }; //valori

	//creazione carta e attribuzione punteggio
	Carta(semi s = semi::cuori, valore v = valore::asso, int p = 0) {
		Seme = s;
		Valore = v;
		punteggio = p;
	}

	//metodi get info
	valore get_valore() { return Valore; }
	semi get_seme() { return Seme; }
	int get_punteggio() { return punteggio; }
	void set_punteggio(int p) { punteggio = p; }

private:
	semi Seme;
	valore Valore;
	int punteggio = 0;
};

class Mazzo {
private:
	vector<Carta> carte_mazzo;

public:
	Mazzo(int);
	void Randomizza();
	bool is_empty();
	void set_punteggio(int[14]);
	Carta get_lastcard();
	Carta get_firstcard();
	Carta get_lastcardval();
	Carta get_firstcardval();
	int get_ncard();
	void add_card(Carta, int);
	void add_cardup(Carta);
	void add_carddown(Carta);
};

class Player{
public:
	int card_style = 0, text_color = 0;
	Player(string = "Franco");
	void reset();

	void add_card(Carta); //aggiungi carta alla mano
	Carta get_card(int); //rimuovi carta dalla mano

	void add_carteacq(Carta); //aggiungi carta mazzo acquisito
	vector<Carta> get_mano(); //get valori mazzo mano
	vector<Carta> get_carteacq(); //get valori mazzo acquisito

	int get_ncard();	//get numero carte in mano
	int get_ncardacq();	//get numero carte acquisite
	int get_hand_point(); //get punteggio carte in mano

	void add_point(int); //aggiungi al punteggio
	void sub_point(int); //rimuovi al punteggio
	void set_point(int); //imposta punteggio
	int get_point(); //get punteggio
	string get_name() { return name; }
	void set_name(string names) { name = names; }
	
private:
	int punteggio, team_id;
	string name;
	vector<Carta> carte_mano, carte_acquisite;
};

void print_card(vector<Carta>, bool);
void print_card(vector<Carta>, bool, bool);