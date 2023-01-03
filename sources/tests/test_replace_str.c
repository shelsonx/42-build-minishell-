#include "../../includes/minishell.h"

int count_occurrences(const char *s, const char *old, const char *new)
{
    int     i;
    int     count;
    int     new_len;
    int     old_len;

    i = 0;
    count = 0;
    new_len = strlen(new);
    old_len = strlen(old);
    while (s[i])
    {
        if (ft_strnstr(&s[i], old, ft_strlen(s)) == &s[i])
        {
            count++;
            i += old_len - 1;
        }
        i++;
    }
    return (count);
}

char    *replace_word(const char *s, const char *old, const char *new)
{
    char    *result;
    int     i;
    int     new_len;
    int     old_len;

    new_len = ft_strlen(new);
    old_len = ft_strlen(old);
    result = malloc(ft_strlen(s) + 
        count_occurrences(s, old, new) * (new_len - old_len) + 1);
    i = 0;
    while (*s)
    {
        if (ft_strnstr(s, old, ft_strlen(s)) == s)
        {
            ft_strcpy(&result[i], (char *) new);
            i += new_len;
            s += old_len;
        }
        else
            result[i++] = *s++;
    }
    result[i] = '\0';
    return result;
}

int main(void)
{
    char str[] = "this project is minishell. The minishell is beautiful!"; 
    char old[] = "shell"; 
    char new[] = "-hell"; 
  
    char* result = NULL; 
  
    // oldW string 
    printf("Old string: %s\n", str); 
  
    result = replace_word(str, old, new); 
    printf("New String: %s\n", result); 
  
    free(result); 
    return 0; 
}