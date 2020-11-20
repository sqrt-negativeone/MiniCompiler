#pragma once
#include "scanner.h"
#include "errors.h"

token_list* current_token;

//definitions
//return true if okey, return false if an error occured
bool program_rule();
bool block_rule();
bool consts_rule();
bool vars_rule();
bool insts_rule();
bool inst_rule();
bool affect_rule();
bool if_rule();
bool while_rule();
bool write_rule();
bool read_rule();
bool cond_rule();
bool expr_rule();
bool term_rule();
bool fact_rule();
bool read_next();
//return true if current token matches token
bool test_token(TOKEN token, ERRORS error);

ERRORS last_error;

//function implementation
bool test_token(TOKEN token, ERRORS error)
{
	if (current_token->token == token)
	{
		read_next();
		return true;
	}
	last_error = error;
	return false;
}
bool read_next()
{
	current_token = current_token->next;
}
bool start_parser()
{
	current_token = tokens.next;
	return program_rule();
}

bool program_rule()
{
	if (!test_token(PROGRAM_TOKEN, ERR_PROGRAM) ||
		!test_token(IDENTIFIER_TOKEN, ERR_ID) ||
		!test_token(SEMICOLON_TOKEN, ERR_SEMICOLON) ||

		!block_rule() ||

		!test_token(PERIOD_TOKEN, ERR_PERIOD))
	{
		return false;
	}
	return true;
}

bool block_rule()
{
	if (!consts_rule() ||
		!vars_rule() ||
		!insts_rule() )
	{
		return false;
	}
	return true;
}

bool consts_rule()
{
	if (test_token(CONST_TOKEN, ERR_COMMA))
	{
		if (!test_token(IDENTIFIER_TOKEN, ERR_ID) ||
			!test_token(EQUAL_TOKEN, ERR_EQUAL) ||
			!test_token(NUMBER_TOKEN, ERR_NUM) ||
			!test_token(SEMICOLON_TOKEN, ERR_SEMICOLON))
		{
			return false;
		}

		while (test_token(IDENTIFIER_TOKEN, ERR_ID))
		{
			if (!test_token(EQUAL_TOKEN, ERR_ID) ||
				!test_token(NUMBER_TOKEN, ERR_NUM) ||
				!test_token(SEMICOLON_TOKEN, ERR_SEMICOLON))
			{
				return false;
			}
		}
	}
	return true;
}

bool vars_rule()
{
	if (test_token(VAR_TOKEN, ERR_VAR))
	{
		if (!test_token(IDENTIFIER_TOKEN, ERR_ID))
			return false;

		while (test_token(COMMA_TOKEN, ERR_COMMA))
		{
			if (!test_token(IDENTIFIER_TOKEN, ERR_ID))
			{
				return false;
			}
		}
		if (!test_token(SEMICOLON_TOKEN, ERR_SEMICOLON)) return false;
	}
	return true;
}

bool insts_rule()
{
	if (!test_token(BEGIN_TOKEN, ERR_BEGIN) ||
		!inst_rule())
	{
		return false;
	}
	while (test_token(SEMICOLON_TOKEN, ERR_SEMICOLON))
	{
		if (!inst_rule()) return false;
	}
	if (!test_token(END_TOKEN, ERR_END)) return false;
}

bool inst_rule()
{
	switch (current_token->token)
	{
	case BEGIN_TOKEN:
		return insts_rule();
	case IF_TOKEN:
		return if_rule();
	case WHILE_TOKEN:
		return while_rule();
	case READ_TOKEN:
		return read_rule();
	case WRITE_TOKEN:
		return write_rule();
	case IDENTIFIER_TOKEN:
		return affect_rule();
	}
	return true;
}
bool if_rule()
{
	if (!test_token(IF_TOKEN, ERR_IF) ||
		!cond_rule() ||
		!test_token(THEN_TOKEN, ERR_THEN) ||
		!inst_rule())
	{
		return false;
	}
	
	//TODO : Add else rule
	return true;
}

bool while_rule()
{
	if (!test_token(WHILE_TOKEN, ERR_WHILE) ||
		!cond_rule() ||
		!test_token(DO_TOKEN,ERR_DO) ||
		!inst_rule())
	{
		return false;
	}
	return true;
}

bool read_rule()
{
	if (!test_token(READ_TOKEN, ERR_READ) ||
		!test_token(LEFT_PARENTHESIS_TOKEN, ERR_LEFT_PARENT) ||
		!test_token(IDENTIFIER_TOKEN, ERR_ID))
	{
		return false;
	}
	while (test_token(COMMA_TOKEN, ERR_COMMA))
	{
		if (!test_token(IDENTIFIER_TOKEN, ERR_ID)) return false;
	}
	return test_token(RIGHT_PARENTHESIS_TOKEN, ERR_RIGHT_PARENT);
}
bool write_rule()
{
	if (!test_token(WRITE_TOKEN, ERR_WRITE) ||
		!test_token(LEFT_PARENTHESIS_TOKEN, ERR_LEFT_PARENT) ||
		!expr_rule())
	{
		return false;
	}
	while (test_token(COMMA_TOKEN, ERR_COMMA))
	{
		if (!expr_rule()) return false;
	}
	return test_token(RIGHT_PARENTHESIS_TOKEN, ERR_RIGHT_PARENT);
}
bool affect_rule()
{
	if (!test_token(IDENTIFIER_TOKEN, ERR_ID) ||
		!test_token(AFFECT_TOKEN, ERR_AFFECT) ||
		!expr_rule())
	{
		return false;
	}
	return true;
}

bool cond_rule()
{
	expr_rule();
	if (test_token(EQUAL_TOKEN, ERR_EQUAL) || test_token(DIFF_TOKEN, ERR_DIFF) || test_token(LESS_TOKEN , ERR_LESS) || 
		test_token(GREATER_TOKEN, ERR_GREATER) || test_token(LESS_EQ_TOKEN, ERR_LESS_EQ) || test_token(GREATER_EQ_TOKEN, ERR_GREATER_EQ))
	{
		return expr_rule();
	}
	else
	{
		last_error = ERR_COMPARISON;
		return false;
	}
}

bool expr_rule()
{
	if (!term_rule()) return false;
	if (test_token(PLUS_TOKEN, ERR_PLUS) || test_token(MINUS_TOKEN, ERR_MINUS))
	{
		return term_rule();
	}
	return true;
}

bool term_rule()
{
	if (!fact_rule()) return false;
	if (test_token(MULT_TOKEN, ERR_MULT) || test_token(SLASH_TOKEN, ERR_DIV))
	{
		return fact_rule();
	}
	return true;
}

bool fact_rule()
{
	if (test_token(IDENTIFIER_TOKEN, ERR_ID) ||
		test_token(NUMBER_TOKEN, ERR_NUM))
	{
		return true;
	}

	if (!test_token(LEFT_PARENTHESIS_TOKEN, ERR_LEFT_PARENT) ||
		!expr_rule() ||
		!test_token(RIGHT_PARENTHESIS_TOKEN, ERR_RIGHT_PARENT))
	{
		return false;
	}
	return true;
}