#ifndef WINDOW_H
#define WINDOW_H

typedef struct Client {
	int socket_fd;
	struct Client* next;
} Client;

void win_create();
void win_loop_events();
Client* win_new_client(int socket_fd);
void win_remove_client(Client* c);

#endif
