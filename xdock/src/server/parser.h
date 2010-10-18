#ifndef PARSER_H
#define PARSER_H

#include "network.h"

typedef struct {
} Command;

typedef struct CommandQueue {
	Command command;
	struct CommandQueue* next;
} CommandQueue;

int parse_data(char data[4096], CommandQueue** queue);

#endif
