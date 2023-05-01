#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <algorithm>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

/*-*-*-*-*- IMPOSTAZIONI SERVER -*-*-*-*-*/
const int MAX_CONNECTIONS = 50;
const int BUFFER_SIZE = 1024;
const int SERVER_PORT = 6969;

using namespace std;

int start_server();

// Struttura per memorizzare i dati relativi a una connessione client
struct Connection {
    int socket;
    std::string address;
    bool active;
    std::thread thread;

    Connection(int socket, const std::string& address) :
        socket(socket), address(address), active(true), thread(&Connection::run, this) {}

    // Funzione che gestisce la comunicazione con il client
    void run() {
        char buffer[BUFFER_SIZE];
        while (active) {
            int bytes_received = recv(socket, buffer, BUFFER_SIZE, 0);
            if (bytes_received <= 0) {
                // Connessione chiusa dal client o errore di ricezione
                active = false;
            }
            else {
                // Messaggio ricevuto
                buffer[bytes_received] = '\0';
                std::cout << "Messaggio da " << address << ": " << buffer << std::endl;
            }
        }
        // Chiude la connessione
        close(socket);
        std::cout << "Connessione chiusa con " << address << std::endl;
    }

};

class Player {
public:

	Player(int, const string&);
	void listner();

	struct connection {
		string ip, nome;
		bool active;
		int socket;

	}Connection;

private:

	struct game {
		int team_id, punti, n_carte;
	}Game;

};
