
//#include "server.h"

/*########################################*/
/*                                        */
/*			   Funzioni Carte             */
/*                                        */
/*########################################*/
/*
//creazione carta e attribuzione punteggio
Carta::Carta(semi s, valore v) {
	Seme = s;
	Valore = v;

	switch (v) {
	case Carta::due:
	case Carta::quattro:
	case Carta::cinque:
	case Carta::sei:
	case Carta::sette:
		punteggio = 0;
		break;
	case Carta::fante:
		punteggio = 2;
		break;
	case Carta::donna:
		punteggio = 3;
		break;
	case Carta::re:
		punteggio = 4;
		break;
	case Carta::tre:
		punteggio = 10;
		break;
	case Carta::asso:
		punteggio = 11;
		break;
	default:
		break;
	}
}

/*########################################*/
/*                                        */
/*			   Funzioni Mazzo             */
/*                                        */
/*########################################*/
/*
//funzione chiamata mazzo
Mazzo::Mazzo() {
	//creazione mazzo
	for (int i = Carta::cuori; i <= Carta::picche; ++i) { //semi
		for (int k = Carta::asso; k < Carta::re; k++) { //valori
			carte_mazzo.push_back(Carta(static_cast<Carta::semi>(i), static_cast<Carta::valore>(k)));
		}
	}

	//reset carte rimaste
	carte_rim = 50;
}

//funzione randomizzazione mazzo
void Mazzo::Randomizza() {
	int g = time(0);
	g = g * rand() % 10;
	random_shuffle(carte_mazzo.begin(), carte_mazzo.end(), g);
}

//funzione distribuzione carte
Carta Mazzo::get_carta() {
	Carta temp(Carta::cuori, Carta::asso);

	temp = carte_mazzo.back();
	carte_mazzo.pop_back();
	carte_rim--;

	return temp;

}
*/