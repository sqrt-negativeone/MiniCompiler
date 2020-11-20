#include "scanner.h"
#include "parser.h"
#include "errors.h"


void main()
{
	init_error_messages();
	init_scanner();
	
	FILE* file;
	fopen_s(&file, "test1.txt", "r");
	if (file && scan_tokens(file))
	{
		print_tokens();
		if (start_parser)
		{
			printf("\nPROGRAM WELL PARSED!\n");
		}
		else
		{
			printf("\nTHERE WAS A SYNTAX ERROR\nERROR: %s\n", erro_messages[last_error]);
		}
	}

}