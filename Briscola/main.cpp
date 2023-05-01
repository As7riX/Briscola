#include "client.h"

using namespace std;

void sp_menu();
void mp_menu();
void imp_menu();

int main() {

	char s;

	do{
		//system("cls");

		cout << "*-*-*-*-*-*-*-*- Card Game v0.3 -*-*-*-*-*-*-*-*" << endl << endl
			<< "1) Single Player" << endl
			<< "2) Multi Player" << endl
			<< "3) Impostazioni" << endl
			<< "x) Esci" << endl;
		cin >> s;	

		switch (s) {
		case '1':
			sp_menu();
			break;

		case '2':
			mp_menu();
			break;

		case '3':
			imp_menu();
			break;

		case 'x':
			break;

		default:
			break;
		}
	} while (s != 'x');
	

}

void sp_menu() {
	char s;

	system("cls");
	cout << "*-*-*-*-*-*-*-*- Seleziona Una Modalità -*-*-*-*-*-*-*-*" << endl << endl
		<< "1) Player" << endl
		<< "2) Bot" << endl
		<< "3) -----" << endl;
	cin >> s;

	switch (s) {
	case '1':
		game_briscola();
		break;

	case '2':
		game_briscola_bot();
		break;

	case '3':
		break;

	default:
		break;
	}

	


}

void mp_menu() {
	string ip;
	system("cls");

	cout << "*-*-*-*-*-*-*-*- Card Game v0.3 -*-*-*-*-*-*-*-*" << endl
		<< "Inserisci ip server: "; 
	cin >> ip;

}

void imp_menu() {
	char s;

	do{
		system("cls");
		cout << "*-*-*-*-*-*-*-*- Impostazioni -*-*-*-*-*-*-*-*" << endl << endl
			<< "1) Stile Carte: " << endl
			<< "2) Colore Testo: " << endl
			<< "3) " << endl
			<< "x) Esci" << endl;
		cin >> s;

		switch (s) {
		case '1':
			
			break;

		case '2':
			
			break;

		case '3':
			
			break;

		case 'x':
			break;

		default:
			break;
		}
	} while (s != 'x');
	
}
