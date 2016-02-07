#ifndef SERVER_H
#define SERVER_H

#include <winsock.h>
#include "client.h"

/* Prototypes */
SOCKET init();
void finish(void);
int recevoir();
void sendfromserver();
void connexion(SOCKET);
void stop(SOCKET sock);

/* Declarations */

char bufferReception[1024], tmpBuffer[1024], bufferEnvoi[1024];
SOCKET sock, cli;
Client c;
FILE *f;
#endif // SERVER_H
