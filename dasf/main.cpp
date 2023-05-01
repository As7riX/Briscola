#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <atomic>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

const int MAX_CONNECTIONS = 50;
const int BUFFER_SIZE = 1024;
const int SERVER_PORT = 6969;

using namespace std;

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

class Player {
public:
    Player();



private:
    struct Connection {
        string ip, nome;
        bool active;
        int socket;
    };

    struct Game {
        int team_id, point;
    };
   
    thread thread;

}