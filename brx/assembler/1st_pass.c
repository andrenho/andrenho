#include <stdio.h>
#include <stdlib.h>
#include "text.h"

int main()
{
	FILE* f = tx_open_file(NULL);
	do
	{
		// find next token
		tx_next_token(f);

		// label
		if(token.type == LABEL)
		{
		}

		// opcode
		else if(token.type == OPCODE)
		{
		}

		// ignore other tokens

	} while(token.type != _EOF);

	fclose(f);
	return EXIT_SUCCESS;
}
