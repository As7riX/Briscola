#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <atomic>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

const int MAX_CONNECTIONS = 10;
const int BUFFER_SIZE = 1024;

// Struttura per memorizzare i dati relativi a una connessione client
struct Connection {
    int socket;
    std::string address;
    std::atomic<bool> active;
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
                // Invia una risposta
                std::string reply = "Hai detto: ";
                reply.append(buffer);
                send(socket, reply.c_str(), reply.size(), 0);
            }
        }
        // Chiude la connessione
        close(socket);
        std::cout << "Connessione chiusa con " << address << std::endl;
    }
};

int main() {
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        std::cerr << "Errore creazione socket" << std::endl;
        return 1;
    }

    sockaddr_in server_address{};
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(8080);

    if (bind(server_socket, (sockaddr*)&server_address, sizeof(server_address)) == -1) {
        std::cerr << "Errore bind" << std::endl;
        return 1;
    }

    if (listen(server_socket, MAX_CONNECTIONS) == -1) {
        std::cerr << "Errore listen" << std::endl;
        return 1;
    }

    std::vector<Connection*> connections;

    std::cout << "Server in ascolto sulla porta 8080" << std::endl;

    while (true) {
        sockaddr_in client_address{};
        socklen_t client_address_size = sizeof(client_address);
        int client_socket = accept(server_socket, (sockaddr*)&client_address, &client_address_size);
        if (client_socket == -1) {
            std::cerr << "Errore accept" << std::endl;
            continue;
        }

        std::string address = inet_ntoa(client_address.sin_addr);

        if (connections.size() >= MAX_CONNECTIONS) {
            // Troppe connessioni attive, chiude la connessione
            std::cout << "Connessione rifiutata con " << address << " (raggiunto il numero massimo di connessioni)" << std::endl;
            close(client_socket);
        }
        else {
            Connection* conn = new Connection(client_socket, address);
            connections.push_back(conn);
            std::cout << "Connessione accettata con " << address << std::endl;
        }

        // Rimuove le connessioni terminate
        for (auto it = connections.begin(); it != connections.end(); ) {
            if (!(*it)->active) {
                (*it)->thread.join();
                delete* it;
                it = connections.erase(it);
            }
            else {
                ++it;
            }
        }
    }

    // Chiude tutte le connessioni rimanenti
    for (auto conn : connections) {
        conn->active = false;
        conn->thread.join();
        close(conn->socket);
        delete conn;
    }

    // Chiude il socket del server
    close(server_socket);

    return 0;
}