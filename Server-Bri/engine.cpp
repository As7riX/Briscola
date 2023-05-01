#include "server.h"


/*########################################*/
/*                                        */
/*			 Funzioni Giocatore           */
/*                                        */
/*########################################*/

Player::Player(int socket, const string& address) {
    Connection.ip = address;
    Connection.active = true;
    Connection.socket = socket;
}

void Player::listner() {
    char buffer[BUFFER_SIZE];
    while (Connection.active) {
        int bytes_received = recv(Connection.socket, buffer, BUFFER_SIZE, 0);
        if (bytes_received <= 0) {
            // Connessione chiusa dal client o errore di ricezione
            Connection.active = false;
        }
        else {
            // Messaggio ricevuto
            buffer[bytes_received] = '\0';
            cout << "Messaggio da " << Connection.ip << ": " << buffer << endl;
            // Invia una risposta
            string reply = "Hai detto: ";
            reply.append(buffer);
            send(Connection.socket, reply.c_str(), reply.size(), 0);
        }
    }

    // Chiude la connessione
    close(Connection.socket);
    cout << "Connessione chiusa con " << Connection.ip << endl;
}

//void Player::stop() {
//    Connection.active = false;
//    thread_id.join();
//    close(Connection.socket);
//}


/*########################################*/
/*                                        */
/*			  Funzioni Server             */
/*                                        */
/*########################################*/

int start_server() {
    //creazione socket
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        std::cerr << "Errore creazione socket" << std::endl;
        return -1;
    }

    //impostazioni server
    sockaddr_in server_address{};
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(SERVER_PORT);

    //bindings
    if (bind(server_socket, (sockaddr*)&server_address, sizeof(server_address)) == -1) {
        std::cerr << "Errore bind" << std::endl;
        return -1;
    }

    //listner
    if (listen(server_socket, MAX_CONNECTIONS) == -1) {
        std::cerr << "Errore listen" << std::endl;
        return -1;
    }

    //end
    std::cout << "Server in ascolto sulla porta 8080" << std::endl;
    return server_socket;
}

void send_package(vector<Connection*> connections, string package) {
    for (int i = 0; i < connections.size(); i++)
        send(connections[i]->socket, package.c_str(), package.size(), 0);
}

void send_package(vector<Connection*> connections, string package, int id) {
    send(connections[id]->socket, package.c_str(), package.size(), 0);
}

void package_listner() {

}

/*
void stop_server(int server_socket, vector<Player::connection*> connections) {
    // Chiude tutte le connessioni rimanenti
    for (auto conn : connections) {
        conn->active = false;
        conn->thread.join();
        close(conn->socket);
        delete conn;
    }

    // Chiude il socket del server
    close(server_socket);
}
*/