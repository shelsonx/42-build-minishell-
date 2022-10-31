#include "../libs/libft/libft.h"

typedef struct s_token
{
    char    type;
    char    *object;
}   t_token;

int main(int argc, char **argv)
{
    t_token token;
    int i;

    token.type = 'c';
    token.object = "ls";
    //ft_printf("type: %c object: %s\n", token.type, token.object);

   char **splitted = ft_split("ls -la | grep c", ' ');
   i = 0;
   while (splitted[i])
    ft_printf("%s\n", splitted[i++]);
}