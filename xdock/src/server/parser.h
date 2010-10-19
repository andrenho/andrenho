#ifndef PARSER_H
#define PARSER_H

#include "network.h"
#include "client.h"

int parse_data(char data[4096], Client* client);

#endif
