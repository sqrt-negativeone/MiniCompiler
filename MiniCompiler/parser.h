#pragma once
#include "scanner.h"

token_list* current_token;

//definitions
void program_rule();
void block_rule();
void consts_rule();
void vars_rule();
void insts_rule();
void inst_rule();
void affect_rule();
void if_rule();
void while_rule();
void write_rule();
void read_rule();
void cond_rule();
void expr_rule();
void term_rule();
void fact_rule();
void read_next();
bool test_token(TOKEN token);



//function implementation
bool test_token(TOKEN token)
{
	if (current_token->token == token)
	{
		read_next();
		return true;
	}
	//ERROR

	return false;
}
void read_next()
{
	current_token = current_token->next;
}
void start_parser()
{
	current_token = &tokens;
	program_rule();
}

void program_rule()
{
	test_token(PROGRAM_TOKEN);
	test_token(IDENTIFIER_TOKEN);
	test_token(SEMICOLON_TOKEN);

	block_rule();
	
	test_token(PERIOD_TOKEN);
}

void block_rule()
{
	consts_rule();
	vars_rule();
	insts_rule();
}

void consts_rule()
{
	if (test_token(CONST_TOKEN))
	{
		while (test_token(IDENTIFIER_TOKEN))
		{
			test_token(EQUAL_TOKEN);
			test_token(NUMBER_TOKEN);
			test_token(SEMICOLON_TOKEN);
		}
	}
}

void vars_rule()
{
	if (test_token(VAR_TOKEN))
	{
		test_token(IDENTIFIER_TOKEN);
		while (test_token(COMMA_TOKEN))
		{
			test_token(IDENTIFIER_TOKEN);
		}
		test_token(SEMICOLON_TOKEN);
	}
}

void insts_rule()
{
	test_token(BEGIN_TOKEN);
	inst_rule();
	while (test_token(SEMICOLON_TOKEN))
	{
		inst_rule();
	}
	test_token(END_TOKEN);
}

void inst_rule()
{
	switch (current_token->token)
	{
	case BEGIN_TOKEN:
		insts_rule();
		break;
	case IF_TOKEN:
		if_rule();
		break;
	case WHILE_TOKEN:
		while_rule();
		break;
	case READ_TOKEN:
		read_rule();
		break;
	case WRITE_TOKEN:
		write_rule();
		break;
	case IDENTIFIER_TOKEN:
		affect_rule();
		break;
	default:
		break;
	}
}
void if_rule()
{
	test_token(IF_TOKEN);
	cond_rule();
	test_token(THEN_TOKEN);
	inst_rule();

	//TODO : Add else rule
}

void while_rule()
{
	test_token(WHILE_TOKEN);
	cond_rule();
	test_token(DO_TOKEN);
	inst_rule();
}

void read_rule()
{
	test_token(READ_TOKEN);
	test_token(LEFT_PARENTHESIS_TOKEN);
	test_token(IDENTIFIER_TOKEN);
	while (test_token(COMMA_TOKEN))
	{
		test_token(IDENTIFIER_TOKEN);
	}
	test_token(RIGHT_PARENTHESIS_TOKEN);
}
void write_rule()
{
	test_token(READ_TOKEN);
	test_token(LEFT_PARENTHESIS_TOKEN);
	expr_rule();
	while (test_token(COMMA_TOKEN))
	{
		expr_rule();
	}
	test_token(RIGHT_PARENTHESIS_TOKEN);
}
void affect_rule()
{
	test_token(IDENTIFIER_TOKEN);
	test_token(AFFECT_TOKEN);
	expr_rule();
}

void cond_rule()
{
	expr_rule();
	if (test_token(EQUAL_TOKEN) || test_token(DIFF_TOKEN) || test_token(LESS_TOKEN) || test_token(GREATER_TOKEN)
		|| test_token(LESS_EQ_TOKEN) || test_token(GREATER_EQ_TOKEN))
	{
		expr_rule();
	}
	else
	{
		//ERROR
	}
}

void expr_rule()
{
	term_rule();
	if (test_token(PLUS_TOKEN) || test_token(MINUS_TOKEN))
	{
		term_rule();
	}
}

void term_rule()
{
	fact_rule();
	if (test_token(MULT_TOKEN) || test_token(MULT_TOKEN))
	{
		fact_rule();
	}
}

void fact_rule()
{
	if (test_token(IDENTIFIER_TOKEN)) return;
	if (test_token(NUMBER_TOKEN)) return;

	test_token(LEFT_PARENTHESIS_TOKEN);
	expr_rule();
	test_token(RIGHT_PARENTHESIS_TOKEN);
}