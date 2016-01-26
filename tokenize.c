#include "tokenize.h"

static
YYSTYPE _curr_token;

static
int _la_exists;

static
int _curr_token_type;

int
tokenize_init ()
{
	_la_exists = FALSE;
	return XSM_SUCCESS;
}

int
tokenize_next_token (YYSTYPE &token_info)
{
	int token_type;

	if (_la_exists)
	{
		*token_info = _curr_token;
		_la_exists = FALSE;
		return _curr_token_type;
	}
	else
	{
		token_type = yylex ();
		*token_info = yylval;
		return token_type;
	}
}

int
tokenize_peek (YYSTYPE &token_info)
{
	if (_la_exists)
	{
		*token_info = _curr_token;
		return _curr_token_type;
	}
	else
	{
		_curr_token_type = yylex ();
		_curr_token = yylval;
		*token_info = _curr_token;
		_la_exists = TRUE;
		return _curr_token_type;
	}
}

int
tokenize_close ()
{
	/* Nothing to do. */
	return XSM_SUCCESS;
}