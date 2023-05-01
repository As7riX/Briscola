#include "gamemode.h"
#include "../client.h"

constexpr auto ai_diff = 0;

vector<Carta> carte_aq;

//npc per briscola
class NPC : public Player {
public:
	NPC(string nome) {
		set_name(nome);
	}

	int pickCard(vector<Carta> tavolo, bool first) {
		//bot stupido (random-pick)
		if (ai_diff == 0) {
			int id_carta;
			id_carta = ((rand() % get_ncard()) + 1);
			return id_carta;
		}

		//bot meno stupido
		if (ai_diff == 1) {

		}

		//minimax
		if (ai_diff == 2) {
			
		}

	}

};

//funzione controllo vittoria
int check_win(vector<Carta> carte) {

	map<Carta::valore, int> valore{
			{Carta::due, 0}, {Carta::quattro, 1}, {Carta::cinque, 2}, {Carta::sei, 3},
			{Carta::sette, 4}, {Carta::fante, 5}, {Carta::donna, 6}, {Carta::re, 7}, 
			{Carta::tre, 8}, {Carta::asso, 9},
	};

	//se sono entrambe briscole
	if (carte[1].get_seme() == carte[0].get_seme() && carte[2].get_seme() == carte[0].get_seme()) {
		if (valore[carte[1].get_valore()] > valore[carte[2].get_valore()]) return 1;
		else return 2;
	}

	//se solo uno dei 2 ha briscola
	if (carte[1].get_seme() == carte[0].get_seme()) return 1;
	if (carte[2].get_seme() == carte[0].get_seme()) return 2;

	//se hanno lo stesso seme
	if (carte[1].get_seme() == carte[2].get_seme()) {
		if (valore[carte[1].get_valore()] > valore[carte[2].get_valore()]) return 1;
		else return 2;
	}

	//se hanno semi diversi
	return 1;
}

//menu revisione partita
void menu_replay(Player p1, Player p2, int round) {
	system("cls");
	cout << "Replay Partita\n\n";
	cout << "Statistiche: N° round -> " << round << "  Punteggio -> " << p1.get_point() << " - " << p2.get_point() << "  Carte In Possesso -> " << p1.get_ncardacq() << " - " << p2.get_ncardacq();
	cout << "\n\nCarichi " << p1.get_name() << ": \n";
	print_card(p1.get_carteacq(), false, true);
	cout << "\n\nCarichi " << p2.get_name() << ": \n";
	print_card(p2.get_carteacq(), false, true);
	Sleep(5000);
	cout << "\n\nPremi invio per continuare...";
	cin.ignore(2);

}

//richiesta input carta
int input(Player p) {
	int s;

	cout << "\n\nInserisci il numero della carta da giocare: ";
	cin >> s;
	while (s > p.get_ncard() || s <= 0){
		cout << "\n\nInserisci il numero della carta da giocare: ";
		cin >> s;
	}
	return s;
}

//gamemode standard 1v1
void game_briscola() {
	string nome;
	int g_start = 1, round = 0;

	//crazione mazzo e assegnazione punteggio
	Mazzo mazzo(2); 
	int v_punteggi[14] = { 11, 0, 10, 0, 0, 0, 0, -1, -1, -1, 2, 3, 4, -1 };
	mazzo.set_punteggio(v_punteggi);
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
	for (int i = 0; i < 3; i++){
		p1.add_card(mazzo.get_firstcard());
		p2.add_card(mazzo.get_firstcard());
	}

	//get briscola card
	Carta briscola = mazzo.get_lastcardval();

	//inizio turni
	while (p1.get_ncard() != 0 && p2.get_ncard() != 0){
		round++;
		vector<Carta> tavolo;
		tavolo.push_back(briscola);

		//turno bimbo 1
		system("cls");

		(g_start == 1) ? cout << "E' il turno di " << p1.get_name() << "!\n\n" : cout << "E' il turno di " << p2.get_name() << "!\n\n";
		(g_start == 1) ? print_card(p2.get_mano(), true) : print_card(p1.get_mano(), true) ;

		cout << "*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/\n\n";
		(g_start == 1) ? cout << "Briscola\tCarta g1\tCarta g2\n" : cout << "Briscola\tCarta g2\tCarta g1\n";
		print_card(tavolo, false);
		cout << "\n\n*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/\n";

		(g_start == 1) ? print_card(p1.get_mano(), false) : print_card(p2.get_mano(), false);
		int q = ((g_start == 1) ? input(p1) : input(p2));

		(g_start == 1) ? tavolo.push_back(p1.get_card(q)) : tavolo.push_back(p2.get_card(q));
		
		//attesa
		system("cls");
		cout << "Attesa cambio giocatori... (premere un tasto per continuare)";
		cin.ignore(2);

		//turno bimbo 2
		system("cls");

		(g_start == 2) ? cout << "E' il turno di " << p1.get_name() << "!\n\n" : cout << "E' il turno di " << p2.get_name() << "!\n\n";
		(g_start == 2) ? print_card(p2.get_mano(), true) : print_card(p1.get_mano(), true);

		cout << "*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/\n\n";
		(g_start == 1) ? cout << "Briscola\tCarta g1\tCarta g2\n" : cout << "Briscola\tCarta g2\tCarta g1\n";
		print_card(tavolo, false);
		cout << "\n\n*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/\n";

		(g_start == 2) ? print_card(p1.get_mano(), false) : print_card(p2.get_mano(), false);
		q = ((g_start == 2) ? input(p1) : input(p2));

		(g_start == 2) ? tavolo.push_back(p1.get_card(q)) : tavolo.push_back(p2.get_card(q));

		//controllo carte giocate
		system("cls");
		cout << "*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/\n\n";
		(g_start == 1) ? cout << "Briscola\tCarta g1\tCarta g2\n" : cout << "Briscola\tCarta g2\tCarta g1\n";
		print_card(tavolo, false);
		cout << "\n\n*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/\n";
		
		//messaggio vincita e assegnazione punteggio
		int win = check_win(tavolo);
		if (g_start == 2) (win == 1) ? win = 2 : win = 1;
		
		(win == 1) ? cout << p1.get_name() << ", hai vinto la mano!" : cout << p2.get_name() << ", hai vinto la mano!";
		if (win == 1) {
			p1.add_point(tavolo[1].get_punteggio() + tavolo[2].get_punteggio());
			p1.add_carteacq(tavolo[1]);
			p1.add_carteacq(tavolo[2]);
		}else {
			p2.add_point(tavolo[1].get_punteggio() + tavolo[2].get_punteggio());
			p2.add_carteacq(tavolo[1]);
			p2.add_carteacq(tavolo[2]);
		}


		//reset e preparazione prossimo round
		tavolo.clear();
		if (!mazzo.is_empty()){
			if (win == 1) {
				p1.add_card(mazzo.get_firstcard());
				p2.add_card(mazzo.get_firstcard());
			}else {
				p2.add_card(mazzo.get_firstcard());
				p1.add_card(mazzo.get_firstcard());
			}
		}
		g_start = win;
		Sleep(1500);
		cout << "\n\nPremi invio per continuare...";
		cin.ignore(2);
		
	}

	system("cls");
	if (p1.get_point() > p2.get_point()) cout << "Bravo " << p1.get_name() << ", hai vinto! (" << p1.get_point() << " - " << p2.get_point() << ")\n";
	else if (p1.get_point() < p2.get_point()) cout << "Bravo " << p2.get_name() << ", hai vinto!(" << p1.get_point() << " - " << p2.get_point() << ")\n";
	else cout << "Pareggio! (" << p1.get_point() << " - " << p2.get_point() << ")\n";
	Sleep(4000);

	char s;
	cout << "\n\n1) Statistiche partita\n2) Torna al menu\n";
	cin >> s;
	switch (s){
	case '1': 
		menu_replay(p1, p2, round);
		break;
	case '2':
		break;
	}
	system("cls");
}

//restituisce il valore nella mano
int get_hand_point(vector<Carta> mazzo) {
	int point = 0;

	for (int i = 0; i < mazzo.size(); i++)
		point += mazzo[i].get_punteggio();

	return point;
}

int minimax(vector<Carta> mano, Carta::semi briscola, bool Turno, int depth, int alpha, int beta) {
	if (depth == 0 || mano.size() == 1) {
		return get_hand_point(mano);
	}
	if (Turno) {
		int bestScore = -100;
		for (int i = 0; i < mano.size(); i++) {
			vector<Carta> newHand = mano;
			newHand.erase(newHand.begin() + i);
			int score = minimax(newHand, briscola, false, depth - 1, alpha, beta);
			bestScore = max(bestScore, score);
			alpha = max(alpha, score);
			if (beta <= alpha) {
				break;
			}
		}
		return bestScore;
	}
	else {
		int worstScore = 100;
		for (int i = 0; i < mano.size(); i++) {
			vector<Carta> newHand = mano;
			newHand.erase(newHand.begin() + i);
			int score = minimax(newHand, briscola, true, depth - 1, alpha, beta);
			worstScore = min(worstScore, score);
			beta = min(beta, score);
			if (beta <= alpha) {
				break;
			}
		}
		return worstScore;
	}
}



//gamemode standard 1vNPC
void game_briscola_bot() {
	string nome;
	int g_start = 1, round = 0;

	//crazione mazzo e assegnazione punteggio
	Mazzo mazzo(2);
	int v_punteggi[14] = { 11, 0, 10, 0, 0, 0, 0, -1, -1, -1, 2, 3, 4, -1 };
	mazzo.set_punteggio(v_punteggi);
	mazzo.Randomizza();

	//creazione giocatori
	system("cls");
	cout << "Player 1, insersci il tuo nome: ";
	cin >> nome;
	Player player(nome);  //player
	NPC npc("Coap");  //npc

	//give card 1° round
	for (int i = 0; i < 3; i++) {
		player.add_card(mazzo.get_firstcard());
		npc.add_card(mazzo.get_firstcard());
	}

	//get briscola card
	Carta briscola = mazzo.get_lastcardval();

	//inizio turni
	while (player.get_ncard() != 0 && npc.get_ncard() != 0) {
		round++;
		vector<Carta> tavolo;
		tavolo.push_back(briscola);

		// turno bimbo 1 //
		system("cls");

		(g_start == 1) ? cout << "E' il turno di " << player.get_name() << "!\n\n" : cout << "E' il turno di " << npc.get_name() << "!\n\n";
		print_card(npc.get_mano(), true);

		cout << "*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/\n\n";
		(g_start == 1) ? cout << "Briscola\tCarta g1\tCarta npc\n" : cout << "Briscola\tCarta npc\tCarta g1\n";
		print_card(tavolo, false);
		cout << "\n\n*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/\n";

		print_card(player.get_mano(), false);
		int q = ((g_start == 1) ? input(player) : npc.pickCard(tavolo, true));
		if (g_start == 2) Sleep(1000);
		(g_start == 1) ? tavolo.push_back(player.get_card(q)) : tavolo.push_back(npc.get_card(q));

		//turno bimbo 2
		system("cls");

		(g_start == 2) ? cout << "E' il turno di " << player.get_name() << "!\n\n" : cout << "E' il turno di " << npc.get_name() << "!\n\n";
		print_card(npc.get_mano(), true);

		cout << "*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/\n\n";
		(g_start == 1) ? cout << "Briscola\tCarta g1\tCarta npc\n" : cout << "Briscola\tCarta npc\tCarta g1\n";
		print_card(tavolo, false);
		cout << "\n\n*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/\n";

		print_card(player.get_mano(), false);
		if (g_start == 1) Sleep(1000);
		q = ((g_start == 2) ? input(player) : npc.pickCard(tavolo, false));

		(g_start == 2) ? tavolo.push_back(player.get_card(q)) : tavolo.push_back(npc.get_card(q));

		//controllo carte giocate
		system("cls");
		cout << "*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/\n\n";
		(g_start == 1) ? cout << "Briscola\tCarta g1\tCarta npc\n" : cout << "Briscola\tCarta npc\tCarta g1\n";
		print_card(tavolo, false);
		cout << "\n\n*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/\n";

		//messaggio vincita e assegnazione punteggio
		int win = check_win(tavolo);
		if (g_start == 2) (win == 1) ? win = 2 : win = 1;

		(win == 1) ? cout << player.get_name() << ", hai vinto la mano!" : cout << npc.get_name() << ", hai vinto la mano!";
		if (win == 1) {
			player.add_point(tavolo[1].get_punteggio() + tavolo[2].get_punteggio());
			player.add_carteacq(tavolo[1]);
			player.add_carteacq(tavolo[2]);
		}
		else {
			npc.add_point(tavolo[1].get_punteggio() + tavolo[2].get_punteggio());
			npc.add_carteacq(tavolo[1]);
			npc.add_carteacq(tavolo[2]);
		}


		//reset e preparazione prossimo round
		tavolo.clear();
		if (!mazzo.is_empty()) {
			if (win == 1) {
				player.add_card(mazzo.get_firstcard());
				npc.add_card(mazzo.get_firstcard());
			}
			else {
				npc.add_card(mazzo.get_firstcard());
				player.add_card(mazzo.get_firstcard());
			}
		}
		g_start = win;
		Sleep(1500);
		cout << "\n\nPremi invio per continuare...";
		cin.ignore(2);

	}

	system("cls");
	if (player.get_point() > npc.get_point()) cout << "Bravo " << player.get_name() << ", hai vinto! (" << player.get_point() << " - " << npc.get_point() << ")\n";
	else if (player.get_point() < npc.get_point()) cout << "Bravo " << npc.get_name() << ", hai vinto!(" << player.get_point() << " - " << npc.get_point() << ")\n";
	else cout << "Pareggio! (" << player.get_point() << " - " << npc.get_point() << ")\n";
	Sleep(4000);

	char s;
	cout << "\n\n1) Statistiche partita\n2) Torna al menu\n";
	cin >> s;
	switch (s) {
	case '1':
		menu_replay(player, npc, round);
		break;
	case '2':
		break;
	}
	system("cls");
}