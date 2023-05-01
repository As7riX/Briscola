#include "gamemode.h"
#include "../client.h"

void scala40() {
	string nome;
	Mazzo mazzo(1);
	vector<Carta> pozzo;

	mazzo.Randomizza();

	//creazione giocatori
	system("cls");
	cout << "Player 1, insersci il tuo nome: ";
	cin >> nome;
	Player p1(nome);  //player 1

	system("cls");
	cout << "Player 2, insersci il tuo nome: ";
	cin >> nome;
	Player p2(nome);  //player 2

	//give card 1° round
	for (int i = 0; i < 13; i++) {
		p1.add_card(mazzo.get_firstcard());
		p2.add_card(mazzo.get_firstcard());
	}

	//carta pozzo
	do{
		Carta temp = mazzo.get_firstcard();
		if (temp.get_valore() != Carta::jolly)
			pozzo.push_back(temp);
		else
			mazzo.add_card(temp, (rand() % mazzo.get_ncard()));

	} while (pozzo.size() == 0);




	system("cls");
}