#ifndef PARSER_H
#define PARSER_H

#include "network.h"

typedef struct {
} Command;

typedef struct CommandQueue {
	Command command;
	struct CommandQueue* next;
} CommandQueue;

void parse_data(UnprocessedData** data, CommandQueue** queue);

#endif
