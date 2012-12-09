#!/bin/sh

valgrind --leak-check=full --show-reachable=yes --suppressions=suppressions.txt ./newhope
