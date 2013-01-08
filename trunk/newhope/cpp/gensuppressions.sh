#!/bin/sh

valgrind --leak-check=full --show-reachable=yes --gen-suppressions=all ./newhope 2>&1 >/dev/null | grep -v "=.*" > suppressions.txt
