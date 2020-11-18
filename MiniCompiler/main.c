#include "scanner.h"

void main()
{
	init_scanner();
	
	FILE* file;
	fopen_s(&file, "test1.txt", "r");
	if (file && scan_tokens(file))
	{
		print_tokens();
	}

}