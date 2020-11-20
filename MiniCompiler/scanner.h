#pragma once
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

#define NICE 69
#define MAX_ID_LENGTH 20
#define VALID_CHAR_SIZE ('_' - '\'' + 1)

typedef enum bool bool;
typedef enum TOKEN TOKEN;
typedef enum ERRORS ERRORS;
typedef struct node node;
typedef struct token_list token_list;

enum bool
{
	true = '\1',
	false = '\0'
};

enum TOKEN
{
	//PASCAL RESETVED KEYWORDS
	AND_TOKEN, ARRAY_TOKEN, BEGIN_TOKEN, CASE_TOKEN, CONST_TOKEN,
	DIV_TOKEN, DO_TOKEN, DOWNTO_TOKEN, ELSE_TOKEN, END_TOKEN,
	FILE_TOKEN, FOR_TOKEN, FUNCTION_TOKEN, GOTO_TOKEN, IF_TOKEN,
	IN_TOKEN, LABEL_TOKEN, MOD_TOKEN, NIL_TOKEN, NOT_TOKEN,
	OF_TOKEN, OR_TOKEN, PACKED_TOKEN, PROCEDURE_TOKEN, PROGRAM_TOKEN,
	RECORD_TOKEN, REPEAT_TOKEN, SET_TOKEN, THEN_TOKEN, TO_TOKEN,
	TYPE_TOKEN, UNTIL_TOKEN, VAR_TOKEN, WHILE_TOKEN, WITH_TOKEN,

	//SPECIAL SYMBOLES
	APOSTROPHE_TOKEN, MINUS_TOKEN, PLUS_TOKEN, MULT_TOKEN, SLASH_TOKEN, AFFECT_TOKEN,
	COMMA_TOKEN, PERIOD_TOKEN, SEMICOLON_TOKEN, EQUAL_TOKEN, LESS_TOKEN,
	GREATER_TOKEN, LESS_EQ_TOKEN, GREATER_EQ_TOKEN, DIFF_TOKEN, PLUS_EQ_TOKEN,
	MINUS_EQ_TOKEN, MULT_EQ_TOKEN, DIV_EQ_TOKEN, SHL_TOKEN, SHR_TOKEN, EOF_TOKEN, LEFTBRACKET_TOKEN,
	RIGHTBRACKET_TOKEN, COLON_TOKEN, POINTER_TOKEN, LEFT_PARENTHESIS_TOKEN, RIGHT_PARENTHESIS_TOKEN,

	//OTHERS
	EMPTY_TOKEN, INVALID_TOKEN, IDENTIFIER_TOKEN, NUMBER_TOKEN, READ_TOKEN, WRITE_TOKEN
};
char* token_name[NICE];
enum ERRORS
{
	GENERAL_ERROR, NOT_VALID_ID, ID_LENGTH_TOO_LONG
};
//The tokens are stored in a Trie data structure
struct node
{
	TOKEN type;
	node* next[VALID_CHAR_SIZE];
};
struct token_list
{
	TOKEN token;
	token_list* next;
	token_list* last;
};

node scanner;
token_list tokens;
char current_char = '\0';

void add_token_to_scanner(char* token, TOKEN type);
node* get_scanner_node();
void init_scanner();

void init_token_name()
{
	token_name[AND_TOKEN] = "AND_TOKEN";
	token_name[ARRAY_TOKEN] = "ARRAY_TOKEN";
	token_name[BEGIN_TOKEN] = "BEGIN_TOKEN";
	token_name[CASE_TOKEN] = "CASE_TOKEN";
	token_name[CONST_TOKEN] = "CONST_TOKEN";
	token_name[DIV_TOKEN] = "DIV_TOKEN";
	token_name[DO_TOKEN] = "DO_TOKEN";
	token_name[DOWNTO_TOKEN] = "DOWNTO_TOKEN";
	token_name[ELSE_TOKEN] = "ELSE_TOKEN";
	token_name[END_TOKEN] = "END_TOKEN";
	token_name[FILE_TOKEN] = "FILE_TOKEN";
	token_name[FOR_TOKEN] = "FOR_TOKEN";
	token_name[FUNCTION_TOKEN] = "FUNCTION_TOKEN";
	token_name[GOTO_TOKEN] = "GOTO_TOKEN";
	token_name[IF_TOKEN] = "IF_TOKEN";
	token_name[IN_TOKEN] = "IN_TOKEN";
	token_name[LABEL_TOKEN] = "LABEL_TOKEN";
	token_name[MOD_TOKEN] = "MOD_TOKEN";
	token_name[NIL_TOKEN] = "NIL_TOKEN";
	token_name[NOT_TOKEN] = "NOT_TOKEN";
	token_name[OF_TOKEN] = "OF_TOKEN";
	token_name[OR_TOKEN] = "OR_TOKEN";
	token_name[PACKED_TOKEN] = "PACKED_TOKEN";
	token_name[PROCEDURE_TOKEN] = "PROCEDURE_TOKEN";
	token_name[PROGRAM_TOKEN] = "PROGRAM_TOKEN";
	token_name[RECORD_TOKEN] = "RECORD_TOKEN";
	token_name[REPEAT_TOKEN] = "REPEAT_TOKEN";
	token_name[SET_TOKEN] = "SET_TOKEN";
	token_name[THEN_TOKEN] = "THEN_TOKEN";
	token_name[TO_TOKEN] = "TO_TOKEN";
	token_name[TYPE_TOKEN] = "TYPE_TOKEN";
	token_name[UNTIL_TOKEN] = "UNTIL_TOKEN";
	token_name[VAR_TOKEN] = "VAR_TOKEN";
	token_name[WHILE_TOKEN] = "WHILE_TOKEN";
	token_name[WITH_TOKEN] = "WITH_TOKEN";
	token_name[APOSTROPHE_TOKEN] = "APOSTROPHE_TOKEN";
	token_name[MINUS_TOKEN] = "MINUS_TOKEN";
	token_name[PLUS_TOKEN] = "PLUS_TOKEN";
	token_name[MULT_TOKEN] = "MULT_TOKEN";
	token_name[SLASH_TOKEN] = "SLASH_TOKEN";
	token_name[AFFECT_TOKEN] = "AFFECT_TOKEN";
	token_name[COMMA_TOKEN] = "COMMA_TOKEN";
	token_name[PERIOD_TOKEN] = "PERIOD_TOKEN";
	token_name[SEMICOLON_TOKEN] = "SEMICOLON_TOKEN";
	token_name[EQUAL_TOKEN] = "EQUAL_TOKEN";
	token_name[LESS_TOKEN] = "LESS_TOKEN";
	token_name[GREATER_TOKEN] = "GREATER_TOKEN";
	token_name[LESS_EQ_TOKEN] = "LESS_EQ_TOKEN";
	token_name[GREATER_EQ_TOKEN] = "GREATER_EQ_TOKEN";
	token_name[DIFF_TOKEN] = "DIFF_TOKEN";
	token_name[PLUS_EQ_TOKEN] = "PLUS_EQ_TOKEN";
	token_name[MINUS_EQ_TOKEN] = "MINUS_EQ_TOKEN";
	token_name[MULT_EQ_TOKEN] = "MULT_EQ_TOKEN";
	token_name[DIV_EQ_TOKEN] = "DIV_EQ_TOKEN";
	token_name[SHL_TOKEN] = "SHL_TOKEN";
	token_name[SHR_TOKEN] = "SHR_TOKEN";
	token_name[EOF_TOKEN] = "EOF_TOKEN";
	token_name[LEFTBRACKET_TOKEN] = "LEFTBRACKET_TOKEN";
	token_name[RIGHTBRACKET_TOKEN] = "RIGHTBRACKET_TOKEN";
	token_name[COLON_TOKEN] = "COLON_TOKEN";
	token_name[POINTER_TOKEN] = "POINTER_TOKEN";
	token_name[LEFT_PARENTHESIS_TOKEN] = "LEFT_PARENTHESIS_TOKEN";
	token_name[RIGHT_PARENTHESIS_TOKEN] = "RIGHT_PARENTHESIS_TOKEN";
	token_name[EMPTY_TOKEN] = "EMPTY_TOKEN";
	token_name[INVALID_TOKEN] = "INVALID_TOKEN";
	token_name[IDENTIFIER_TOKEN] = "IDENTIFIER_TOKEN";
	token_name[NUMBER_TOKEN] = "NUMBER_TOKEN";
	token_name[READ_TOKEN] = "READ_TOKEN";
	token_name[WRITE_TOKEN] = "WRITE_TOKEN";
}

void init_scanner()
{
	init_token_name();

	scanner.type = EMPTY_TOKEN;
	for (int i = 0; i < VALID_CHAR_SIZE; i++)
	{
		scanner.next[i] = NULL;
	}
	tokens.last = &tokens;
	tokens.next = NULL;
	//add keywords tokens
	add_token_to_scanner("AND", AND_TOKEN);
	add_token_to_scanner("ARRAY", ARRAY_TOKEN);
	add_token_to_scanner("BEGIN", BEGIN_TOKEN);
	add_token_to_scanner("CASE", CASE_TOKEN);
	add_token_to_scanner("CONST", CONST_TOKEN);
	add_token_to_scanner("DIV", DIV_TOKEN);
	add_token_to_scanner("DO", DO_TOKEN);
	add_token_to_scanner("DOWNTO", DOWNTO_TOKEN);
	add_token_to_scanner("ELSE", ELSE_TOKEN);
	add_token_to_scanner("END", END_TOKEN);
	add_token_to_scanner("FILE", FILE_TOKEN);
	add_token_to_scanner("FOR", FOR_TOKEN);
	add_token_to_scanner("FUNTION", FUNCTION_TOKEN);
	add_token_to_scanner("IF", IF_TOKEN);
	add_token_to_scanner("IN", IN_TOKEN);
	add_token_to_scanner("LABEL", LABEL_TOKEN);
	add_token_to_scanner("MOD", MOD_TOKEN);
	add_token_to_scanner("NI;", NIL_TOKEN);
	add_token_to_scanner("NOT", NOT_TOKEN);
	add_token_to_scanner("OF", OF_TOKEN);
	add_token_to_scanner("OR", OR_TOKEN);
	add_token_to_scanner("PACKED", PACKED_TOKEN);
	add_token_to_scanner("PROCEDURE", PROCEDURE_TOKEN);
	add_token_to_scanner("PROGRAM", PROGRAM_TOKEN);
	add_token_to_scanner("RECORD", RECORD_TOKEN);
	add_token_to_scanner("REPEAT", REPEAT_TOKEN);
	add_token_to_scanner("SET", SET_TOKEN);
	add_token_to_scanner("THEN", THEN_TOKEN);
	add_token_to_scanner("TO", TO_TOKEN);
	add_token_to_scanner("TYPE", TYPE_TOKEN);
	add_token_to_scanner("UNTIL", UNTIL_TOKEN);
	add_token_to_scanner("VAR", VAR_TOKEN);
	add_token_to_scanner("WHILE", WHILE_TOKEN);
	add_token_to_scanner("WITH", WITH_TOKEN);
	add_token_to_scanner("READ", READ_TOKEN);
	add_token_to_scanner("WRITE", WRITE_TOKEN);

	//add special symboles tokens
	add_token_to_scanner("'", APOSTROPHE_TOKEN);
	add_token_to_scanner("-", MINUS_TOKEN);
	add_token_to_scanner("+", PLUS_TOKEN);
	add_token_to_scanner("*", MULT_TOKEN);
	add_token_to_scanner("/", SLASH_TOKEN);
	add_token_to_scanner(":=", AFFECT_TOKEN);
	add_token_to_scanner(",", COMMA_TOKEN);
	add_token_to_scanner(".", PERIOD_TOKEN);
	add_token_to_scanner(";", SEMICOLON_TOKEN);
	add_token_to_scanner("=", EQUAL_TOKEN);
	add_token_to_scanner("<", LESS_TOKEN);
	add_token_to_scanner(">", GREATER_TOKEN);
	add_token_to_scanner("<=", LESS_EQ_TOKEN);
	add_token_to_scanner(">=", GREATER_EQ_TOKEN);
	add_token_to_scanner("<>", DIFF_TOKEN);
	add_token_to_scanner("+=", PLUS_EQ_TOKEN);
	add_token_to_scanner("-=", MINUS_EQ_TOKEN);
	add_token_to_scanner("*=", MULT_EQ_TOKEN);
	add_token_to_scanner("/=", DIV_EQ_TOKEN);
	add_token_to_scanner("<<", SHL_TOKEN);
	add_token_to_scanner(">>", SHR_TOKEN);
	add_token_to_scanner("[", LEFTBRACKET_TOKEN);
	add_token_to_scanner("]", RIGHTBRACKET_TOKEN);
	add_token_to_scanner(":", COLON_TOKEN);
	add_token_to_scanner("^", POINTER_TOKEN);
	add_token_to_scanner("(", LEFT_PARENTHESIS_TOKEN);
	add_token_to_scanner(")", RIGHT_PARENTHESIS_TOKEN);

}
void add_token_to_scanner(char* token, TOKEN type)
{
	node* tmp = NULL;
	tmp = &scanner;
	while (*token != '\0')
	{
		char c = *token - '\'';
		token++;
		if (!tmp->next[c])
		{
			tmp->next[c] = get_scanner_node();
		}
		tmp = tmp->next[c];
	}
	tmp->type = type;
}
node* get_scanner_node()
{
	node* scanner_node = NULL;
	scanner_node = (node*)malloc(sizeof(node));
	for (int i = 0; i < 57; i++)
	{
		scanner_node->next[i] = NULL;
	}
	scanner_node->type = INVALID_TOKEN;
	return scanner_node;
}

TOKEN get_id_or_keyword_token(char* token)
{
	node tmp = scanner;

	while (*token != '\0')
	{
		char c = *token;
		if (!isalnum(c))
		{
			return INVALID_TOKEN;
		}
		if ('0' <= c && c <= '9')
		{
			break;
		}
		c -= '\'';
		if (tmp.next[c] == NULL)
		{
			break;
		}
		else
		{
			tmp = *tmp.next[c];
			token++;
		}
	}
	if (*token != '\0')
	{
		while (*token != '\0' && isalnum(*token))
		{
			token++;
		}
		if (*token != '\0') return INVALID_TOKEN;
		else return IDENTIFIER_TOKEN;
	}
	return tmp.type;
}

TOKEN get_number_token(char* token)
{
	while ('0' <= *token && *token <= '9') token++;
	if (*token == '\0') return NUMBER_TOKEN;
	return INVALID_TOKEN;
}

TOKEN get_special_symbol_token(char* token)
{
	if ('\'' <= *token && *token <= '_')
	{
		if (scanner.next[*token - '\''] == NULL) return INVALID_TOKEN;
		return scanner.next[*token - '\'']->type;
	}
	return INVALID_TOKEN;
}

char* read_word(FILE* file)
{
	
	int len = 0;
	char* buffer = (char*)malloc(20*sizeof(char));

	if (current_char == '\0' || isalnum(current_char) || current_char == '_')
	{
		while (len<20)
		{
			if (current_char == '\0')
			{
				if ((current_char = fgetc(file)) == EOF)
				{
					break;
				}
			}
			if ('a' <= current_char && current_char <= 'z') current_char += 'A' - 'a';
			if (isalnum(current_char) || current_char == '_')
			{
				buffer[len++] = current_char;
				current_char = '\0';
			}
			else
			{
				break;
			}
		}
	}
	else
	{
		buffer[len++] = current_char;
		current_char = fgetc(file);
	}
	while (isspace(current_char))
	{
		if ((current_char = fgetc(file)) == EOF)
		{
			break;
		}
	}
	buffer[len] = '\0';
	return buffer;
}
token_list* make_token_list_item(TOKEN token)
{
	token_list* item = (token_list*)malloc(sizeof(token_list));
	item->next = NULL;
	item->last = NULL;
	item->token = token;
	return item;
}
void insert_to_tokens_list(TOKEN token)
{
	tokens.last->next = make_token_list_item(token);
	tokens.last = tokens.last->next;
}

void merge_tokens()
{
	token_list* tmp = &tokens;

	while (tmp->next && tmp->next->next)
	{
		token_list* tmp2 = tmp->next;
		//LESS_EQ_TOKEN
		if (tmp->next->token == LESS_TOKEN && tmp->next->next->token == EQUAL_TOKEN)
		{
			tmp->next = tmp->next->next;
			tmp->next->token = LESS_EQ_TOKEN;
			free(tmp2);
		}
		//GREATER_EQ_TOKEN
		else if (tmp->next->token == GREATER_TOKEN && tmp->next->next->token == EQUAL_TOKEN)
		{
			tmp->next = tmp->next->next;
			tmp->next->token = GREATER_EQ_TOKEN;
			free(tmp2);
		}
		//DIFF_TOKEN
		else if (tmp->next->token == LESS_TOKEN && tmp->next->next->token == GREATER_TOKEN)
		{
			tmp->next = tmp->next->next;
			tmp->next->token = DIFF_TOKEN;
			free(tmp2);
		}
		//AFFECT_TOKEN
		else if (tmp->next->token == COLON_TOKEN && tmp->next->next->token == EQUAL_TOKEN)
		{
			tmp->next = tmp->next->next;
			tmp->next->token = AFFECT_TOKEN;
			free(tmp2);
		}
		//MINUS_EQ_TOKEN
		else if (tmp->next->token == MINUS_TOKEN && tmp->next->next->token == EQUAL_TOKEN)
		{
			tmp->next = tmp->next->next;
			tmp->next->token = MINUS_EQ_TOKEN;
			free(tmp2);
		}
		//PLUS_EQ_TOKEN
		else if (tmp->next->token == PLUS_TOKEN && tmp->next->next->token == EQUAL_TOKEN)
		{
			tmp->next = tmp->next->next;
			tmp->next->token = PLUS_EQ_TOKEN;
			free(tmp2);
		}
		//MULT_EQ_TOKEN
		else if (tmp->next->token == MULT_TOKEN && tmp->next->next->token == EQUAL_TOKEN)
		{
			tmp->next = tmp->next->next;
			tmp->next->token = MULT_EQ_TOKEN;
			free(tmp2);
		}
		//DIV_EQ_TOKEN
		else if (tmp->next->token == SLASH_TOKEN && tmp->next->next->token == EQUAL_TOKEN)
		{
			tmp->next = tmp->next->next;
			tmp->next->token = DIV_EQ_TOKEN;
			free(tmp2);
		}
		//SHL_TOKEN
		else if (tmp->next->token == LESS_TOKEN && tmp->next->next->token == LESS_TOKEN)
		{
			tmp->next = tmp->next->next;
			tmp->next->token = SHL_TOKEN;
			free(tmp2);
		}
		//SHR_TOKEN
		else if (tmp->next->token == GREATER_TOKEN && tmp->next->next->token == GREATER_TOKEN)
		{
			tmp->next = tmp->next->next;
			tmp->next->token = SHR_TOKEN;
			free(tmp2);
		}
		tmp = tmp->next;
	}
}

bool scan_tokens(FILE* file)
{
	char* token = read_word(file);
	while (*token != EOF)
	{
		if ('0'<= *token && *token <= '9')
		{
			insert_to_tokens_list(get_number_token(token));
		}
		else if ('A' <= *token && *token <= 'Z')
		{
			insert_to_tokens_list(get_id_or_keyword_token(token));
		}
		else
		{
			if (*token == '{')
			{
				//skip the comment
				while (*token != EOF && *token != '}')
				{
					token = read_word(file);
				}
				if (token == EOF) break;
			}
			else insert_to_tokens_list(get_special_symbol_token(token));
		}
		if (tokens.last->token == INVALID_TOKEN)
		{
			return false;
		}
		token = read_word(file);
	}
	insert_to_tokens_list(EOF_TOKEN);
	merge_tokens();
	return true;
}
void print_tokens()
{
	token_list* tmp = &tokens;
	tmp = tmp->next;
	while (tmp)
	{
		printf("%s\n",token_name[tmp->token]);
		tmp = tmp->next;
	}
}
