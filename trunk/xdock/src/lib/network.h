#ifndef NETWORK_H
#define NETWORK_H

int net_connect(char* address, int port);
int net_send(int sock, char* fmt, ...);
int net_recv(int sock, char msg[4096]);
void net_disconnect(int sock);

#endif
