#include "../../includes/minishell.h"

	char isDigit(char c) 
    {
		if (c >= '0' && c <= '9')
        {
            printf("print - %c\n", c);
            return c;
        } else {
            return FALSE;
        }
	}
	
	char isChar(char c) 
    {
		if ((c >= 'a' && c <= 'z') || (c>='A' && c <= 'Z'))
        {
            printf("print - %c\n", c);
            return c;
        } else {
            return FALSE;
        }
	}
	
	char isOperator(char c) 
    {
		if (c == '=' || c == '!' || c == '+' || c == '-' || c == '*' || c == '/')
	    {
            printf("print - %c\n", c);
            return c;
        } else {
            return FALSE;
        }
    }

    char isRedirection(char c) 
    {
		if (c == '>' || c == '<' || c == '>>' || c == '<<')
        {
            printf("print - %c\n", c);
            return c;
        } else {
            return FALSE;
        }
    }

    char isPipe(char c) 
    {
		if (c == '|'  || c == '||')
        {
            printf("print - %c\n", c);
            return c;
        } else {
            return FALSE;
        }
    }

    char isQuote(char c) 
    {
		if (c == '\''  || c == '\"')
        {
            printf("print - %c\n", c);
            return c;
        } else {
            return FALSE;
        }
    }
	
     char isSpace(char c) 
    {
		if (c == '\n' || c== '\r' || c == ' ' || c == '\t')
            {
                printf("print - %c\n", c);
                return c;
            } else {
                return FALSE;
            }
	}

    char lexical_scanner(char *string)
    {
        int i = 0; 
        while(i <= ft_strlen(string))
        {
            isDigit(string[i]);
            isChar(string[i]);
            isOperator(string[i]);
            isRedirection(string[i]);
            isPipe(string[i]);
            isQuote(string[i]);
            isSpace(string[i]);
            i++;
        }

        return 0;
    }