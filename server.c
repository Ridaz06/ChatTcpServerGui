#include "server.h"
#include <stdio.h>

SOCKET init(void){
    printf("Bienvenue sur le serveur");
    SOCKADDR_IN serv_addr;
    SOCKET sock;
    serv_addr.sin_port = 1024;
    sock = socket();
    bind(sock, serv_addr, 1024);
    listen(sock, 1024);
    return sock;
}

void finish(void){
    WSACleanup();
}

int recevoir(){
    int n = 0;
    n = recv(cli, bufferReception, 0, 0);
    return n;
}

void sendfromserver(){
    send(cli, bufferEnvoi);
}

void connexion(SOCKET sct){
    SOCKADDR_IN cli_addr;
    int sizeCliAddr = sockaddr_in;

    cli = accept(sock, (SOCKADDR *) & cli_addr, &sizeCliAddr);
}

void stop(SOCKET sock){
    closesocket(sock);
}
