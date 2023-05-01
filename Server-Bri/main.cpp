#include "server.h"

int main() {

    //start server
    int server_socket = start_server();
    if (server_socket == -1) return 1;

    std::vector<Connection*> connections;


    //attesa giocatori
    while (connections.size() < MAX_CONNECTIONS) {
        sockaddr_in client_address{};
        socklen_t client_address_size = sizeof(client_address);

        //accettazione nuovo client
        int client_socket = accept(server_socket, (sockaddr*)&client_address, &client_address_size);
        if (client_socket == -1) {
            std::cerr << "Errore accept" << std::endl;
            continue;
        }

        std::string address = inet_ntoa(client_address.sin_addr);

        Connection* conn = new Connection(client_socket, address);
        connections.push_back(conn);
        std::cout << "Connessione accettata con " << address << std::endl;

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