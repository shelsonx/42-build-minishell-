#include "../../includes/minishell.h"

char    *get_name_token(int type_token)
{
    if (type_token == TK_WORD)
        return "WORD";
    if (type_token == TK_PARENTHESIS)
        return "PARENTHESIS";
    if (type_token == TK_GREAT)
        return "GREAT";
    if (type_token == TK_LESS)
        return "LESS";
    if (type_token == TK_DGREAT)
        return "DGREAT";
    if (type_token == TK_DLESS)
        return "DLESS";
    if (type_token == TK_PIPE)
        return "PIPE";
     if (type_token == TK_EOF)
        return "EOF";
    return NULL;
}

int main(void)
{
    t_parser parser_data;
    parser_data.index = 0;
    parser_data.table = create_table(5000);
    parser_data.table_redirection = create_table(1000);
    parser_data.current_token = malloc(sizeof(t_token));
    parser_data.tokenizer = malloc(sizeof(t_tokenizer *));
    parser_data.tokenizer->content = malloc(sizeof(char *));
    //"(ls) a112 -ab-c1 | >> > < << ( a123"

    while ((parser_data.tokenizer->content = 
        ft_get_next_line(STDIN_FILENO)) != NULL)
    {
        init_tokenizer(parser_data.tokenizer);
    /*  int i = 0;
        while (i++ < 12) */
        parser(&parser_data);
        ft_printf("Table Redirection: ");
        ft_printf("%d-> %s \n",0, ht_search(parser_data.table_redirection, ft_itoa(0)));
        free(parser_data.tokenizer->characteres);
        parser_data.tokenizer->characteres = ft_strdup("");
    }
    int i = 0;
    while (i < parser_data.index)
    {
        ft_printf("%d-> %s \n",i, ht_search(parser_data.table, ft_itoa(i)));
        i++;
    }

    return (0);
}