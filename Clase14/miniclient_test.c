/*
   El cliente inicializa un socket, rellena la estructura de direcciones del 
   servidor de destino y abre una conexión directa con el oyente.
*/
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char *message = "Hello from Client";
    char buffer[1024] = {0};

    // 1. Create the stream socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) return -1;

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(8080); // Target port
    
    // Convert text IP address to binary format
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) return -1;

    // 2. Establish connection to the server
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) return -1;

    // 3. Send and Receive data
    send(sock, message, strlen(message), 0);
    recv(sock, buffer, 1024, 0);
    printf("Server response: %s\n", buffer);

    // 4. Teardown
    close(sock);
    return 0;
}