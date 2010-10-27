#ifndef PARSER_H
#define PARSER_H

#include "network.h"
#include "client.h"

#define API_VERSION 2

int parse_data(char data[4096], Client* client);

#endif
