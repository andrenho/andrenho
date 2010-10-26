#ifndef NETWORK_H
#define NETWORK_H

typedef struct {
	char** xpm;
	int current_line;
	int max_lines;
	char* name;
} XPM_File;

typedef struct {
	int socket_fd;
	int authorized;
	char unprocessed_data[4096];

	// parser
	XPM_File xpm_file;
	enum { COMMAND=0, XPM } mode;
} ClientNetwork;

void net_startup();
void net_check_for_clients();
void net_receive_data();
int net_send_client_data(ClientNetwork* net, char* fmt, ...);
void net_disconnect_client(int socket_fd);
void net_quit();

#endif
