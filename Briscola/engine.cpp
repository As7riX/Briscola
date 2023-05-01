#include "client.h"

/*########################################*/
/*                                        */
/*			   Funzioni Mazzo             */
/*                                        */
/*########################################*/

//funzione chiamata mazzo
Mazzo::Mazzo(int type) {
	//creazione mazzo
	switch (type){

	//mazzo singolo completo
	case 0: {
		for (int i = Carta::cuori; i <= Carta::picche; ++i)
			for (int k = Carta::asso; k <= Carta::jolly; k++)
				carte_mazzo.push_back(Carta(static_cast<Carta::semi>(i), static_cast<Carta::valore>(k)));
	}

	//mazzo doppio completo
	case 1: {
		for (int l = 0; l < 2; l++)
			for (int i = Carta::cuori; i <= Carta::picche; ++i)
				for (int k = Carta::asso; k <= Carta::jolly; k++)
					carte_mazzo.push_back(Carta(static_cast<Carta::semi>(i), static_cast<Carta::valore>(k)));
	}

	//mazzo A, 2, 3, 4, 5, 6, 7, J, Q, K (briscola)
	case 2: {
		for (int i = Carta::cuori; i <= Carta::picche; i++) {
			carte_mazzo.push_back(Carta(static_cast<Carta::semi>(i), Carta::asso));
			carte_mazzo.push_back(Carta(static_cast<Carta::semi>(i), Carta::due));
			carte_mazzo.push_back(Carta(static_cast<Carta::semi>(i), Carta::tre));
			carte_mazzo.push_back(Carta(static_cast<Carta::semi>(i), Carta::quattro));
			carte_mazzo.push_back(Carta(static_cast<Carta::semi>(i), Carta::cinque));
			carte_mazzo.push_back(Carta(static_cast<Carta::semi>(i), Carta::sei));
			carte_mazzo.push_back(Carta(static_cast<Carta::semi>(i), Carta::sette));
			carte_mazzo.push_back(Carta(static_cast<Carta::semi>(i), Carta::fante));
			carte_mazzo.push_back(Carta(static_cast<Carta::semi>(i), Carta::donna));
			carte_mazzo.push_back(Carta(static_cast<Carta::semi>(i), Carta::re));
		}
	}

	default:
		break;
	}
}

//funzione randomizzazione mazzo
void Mazzo::Randomizza() {
	srand(time(0));
	random_shuffle(carte_mazzo.begin(), carte_mazzo.end());
}

//funzione distribuisci prima carta
Carta Mazzo::get_firstcard() {
	Carta temp = carte_mazzo.back();
	carte_mazzo.pop_back();

	return temp;
}

//funzione distribuisci ultima carta
Carta Mazzo::get_lastcard() {
	Carta temp = carte_mazzo.front();
	carte_mazzo.erase(carte_mazzo.begin());

	return temp;
}

//funzione valore prima carta
Carta Mazzo::get_firstcardval() {
	Carta temp = carte_mazzo.back();
	return temp;
}

//funzione valore ultima carta
Carta Mazzo::get_lastcardval() {
	Carta temp = carte_mazzo.front();
	return temp;
}

//funzione check se vuoto
bool Mazzo::is_empty() {
	if (carte_mazzo.size() == 0) return true;
	else return false;
}

//funzione impostazione punteggio
void Mazzo::set_punteggio(int point[14]) {
	for (int i = 0; i < carte_mazzo.size(); i++)
		carte_mazzo[i].set_punteggio(point[carte_mazzo[i].get_valore()]);
}

//ricevi numero carte
int Mazzo::get_ncard() {
	return carte_mazzo.size();
}

//aggiungi carta mazzo
void Mazzo::add_card(Carta c, int p) {
	carte_mazzo.insert(carte_mazzo.begin() + p, c);
}

//aggiungi carta cima mazzo
void Mazzo::add_cardup(Carta c) {
	carte_mazzo.push_back(c);
}

//aggiungi carta fondo mazzo
void Mazzo::add_carddown(Carta c) {
	carte_mazzo.insert(carte_mazzo.begin(), c);
}

/*########################################*/
/*                                        */
/*			 Funzioni Giocatore           */
/*                                        */
/*########################################*/

//creazione gicatore
Player::Player(string name) {
	
	//dati
	punteggio = 0;
	team_id = -1;
	Player::name = name;
	carte_mano.clear();

}

//reset Impostazioni
void Player::reset() {
	punteggio = 0;	//reset punteggio 
	team_id = -1;	//reset team id
	carte_mano.clear();	//clear carte
}

//get mazzo
vector<Carta> Player::get_mano() {
	return carte_mano;
}

//get carte acquisite
vector<Carta> Player::get_carteacq() {
	return carte_acquisite;
}

//get numero carte
int Player::get_ncard() {
	return carte_mano.size();
}

//get numero carte ac
int Player::get_ncardacq() {
	return carte_acquisite.size();
}

//get punteggio carte mano
int Player::get_hand_point() {
	int point = 0;

	for (int i = 0; i < carte_mano.size(); i++)
		point += carte_mano[i].get_punteggio();

	return point;
}

//add carte acquisite
void Player::add_carteacq(Carta carte) {
	carte_acquisite.push_back(carte);
}

//add card
void Player::add_card(Carta c) {
	carte_mano.push_back(c);
}

//remove card in mano
Carta Player::get_card(int i) {
	Carta temp = carte_mano[i - 1];
	carte_mano.erase(carte_mano.begin() + (i - 1));
	return temp;
}

//aggiungi al punteggio
void Player::add_point(int p) {
	punteggio += p;
}

//rimuovi dal punteggio
void Player::sub_point(int p) {
	punteggio -= p;
}

//imposta il punteggio
void Player::set_point(int p) {
	punteggio = p;
}

//get numero punti
int Player::get_point() {
	return punteggio;
}


/*########################################*/
/*                                        */
/*			   Funzioni Varie             */
/*                                        */
/*########################################*/

//stampa le carte
void print_card(vector<Carta> carte, bool cop) {
	string print[9];
	
	if (cop) {
		for (int i = 0; i < carte.size(); i++){
			print[0].append("-----------\t");
			print[1].append("|*.*.*.*.*|\t");
			print[2].append("|.*.*.*.*.|\t");
			print[3].append("|*.*.*.*.*|\t");
			print[4].append("|.*.*.*.*.|\t");
			print[5].append("|*.*.*.*.*|\t");
			print[6].append("|.*.*.*.*.|\t");
			print[7].append("|*.*.*.*.*|\t");
			print[8].append("-----------\t");
		}

		for (int i = 0; i < 9; i++) {
			cout << print[i] << endl;
		}

		return;
	}

	for (int i = 0; i < carte.size(); i++){
		map<int, string> valore{
			{0, "A"}, {1, "2"}, {2, "3"}, {3, "4"}, {4, "5"}, {5, "6"}, {6, "7"}, {7, "8"}, {8, "9"}, {9, "10"}, {10, "J"}, {11, "Q"}, {12, "K"}, {13, "Y"},
		};

		map<int, string> seme{
			{0, "C"}, {1, "Q"}, {2, "F"}, {3, "P"},
		};

		print[0].append("-----------\t");
		print[1].append("|"); print[1].append(seme[carte[i].get_seme()]); print[1].append("        |\t");
		print[2].append("|         |\t");
		print[3].append("|         |\t");
		print[4].append("|    "); print[4].append(valore[carte[i].get_valore()]); print[4].append("    |\t");
		print[5].append("|         |\t");
		print[6].append("|         |\t");
		print[7].append("|        "); print[7].append(seme[carte[i].get_seme()]); print[7].append("|\t");
		print[8].append("-----------\t");
	}

	for (int i = 0; i < 9; i++){
		cout << print[i] << endl;
	}

}

//stampa solo carte con valore
void print_card(vector<Carta> carte, bool cop, bool only) {
	string print[9];

	for (int i = 0; i < carte.size(); i++) {
		if (carte[i].get_punteggio() != 0){
			map<int, string> valore{
			{0, "A"}, {1, "2"}, {2, "3"}, {3, "4"}, {4, "5"}, {5, "6"}, {6, "7"}, {7, "8"}, {8, "9"}, {9, "10"}, {10, "J"}, {11, "Q"}, {12, "K"}, {13, "Y"},
			};

			map<int, string> seme{
				{0, "C"}, {1, "Q"}, {2, "F"}, {3, "P"},
			};

			print[0].append("-----------\t");
			print[1].append("|"); print[1].append(seme[carte[i].get_seme()]); print[1].append("        |\t");
			print[2].append("|         |\t");
			print[3].append("|         |\t");
			print[4].append("|    "); print[4].append(valore[carte[i].get_valore()]); print[4].append("    |\t");
			print[5].append("|         |\t");
			print[6].append("|         |\t");
			print[7].append("|        "); print[7].append(seme[carte[i].get_seme()]); print[7].append("|\t");
			print[8].append("-----------\t");
		}
	}
		

	for (int i = 0; i < 9; i++) {
		std::cout << print[i] << endl;
	}

}