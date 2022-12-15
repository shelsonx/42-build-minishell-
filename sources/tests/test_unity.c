#include "../../Unity/src/unity.h"
#include "../../includes/minishell.h"
#include "unity_tests.h"

char **env;

void setUp(void)
{
   //
}

void tearDown(void)
{
   //
}

void test_env(void)
{
    t_builtin_vars builtins;
    init_env(&builtins, env);
    char *var = "SHELL";
    char *result = get_env_path(var, &builtins);
    TEST_ASSERT_EQUAL_CHAR_ARRAY("/bin/bash", result, 7);
    free(result);
}

void test_token_word(void)
{
    //cc test_unity.c unity_tests.c ../lexer/lexical_analyzer.c ../lexer/lexical_resources.c ../lexer/get_token.c ../../Unity/src/unity.c ../utils/ht_functions.c ../utils/ht_utils.c ../utils/linkedlist_utils.c ../../libs/libft/libft.a 
    t_token token;
    t_tokenizer tokenizer;

    
    tokenizer.content = ft_strdup("echo");
    init_tokenizer(&tokenizer);
    token = next_token(&tokenizer);
    TEST_ASSERT_EQUAL_CHAR_ARRAY("echo", token.value, 4);
    TEST_ASSERT_EQUAL(TK_WORD, token.type);
}

void test_token_redirections(void)
{
    //cc test_unity.c unity_tests.c ../lexer/lexical_analyzer.c ../lexer/lexical_resources.c ../lexer/get_token.c ../../Unity/src/unity.c ../utils/ht_functions.c ../utils/ht_utils.c ../utils/linkedlist_utils.c ../../libs/libft/libft.a 
    t_token token;
    t_tokenizer tokenizer;

    tokenizer.content = ft_strdup("> file");
    init_tokenizer(&tokenizer);
    token = next_token(&tokenizer);
    TEST_ASSERT_EQUAL_CHAR_ARRAY(">", token.value, 1);
    TEST_ASSERT_EQUAL(TK_GREAT, token.type);

    tokenizer.content = ft_strdup("< file");
    init_tokenizer(&tokenizer);
    token = next_token(&tokenizer);
    TEST_ASSERT_EQUAL_CHAR_ARRAY("<", token.value, 1);
    TEST_ASSERT_EQUAL(TK_LESS, token.type);

    tokenizer.content = ft_strdup(">> file");
    init_tokenizer(&tokenizer);
    token = next_token(&tokenizer);
    TEST_ASSERT_EQUAL_CHAR_ARRAY(">>", token.value, 1);
    TEST_ASSERT_EQUAL(TK_DGREAT, token.type);

    tokenizer.content = ft_strdup("<< file");
    init_tokenizer(&tokenizer);
    token = next_token(&tokenizer);
    TEST_ASSERT_EQUAL_CHAR_ARRAY("<<", token.value, 1);
    TEST_ASSERT_EQUAL(TK_DLESS, token.type);
}

void test_lexer_module(void)
{
    int fd_out, fd_in;
    char *line = ft_strdup("");
    char *out = ft_strdup("");
    char *expected = ft_strdup("");

    test_lexer();
    fd_out = open("out", O_RDONLY, 0777);
    fd_in = open("expected", O_RDONLY, 0777);
    while (line = ft_get_next_line(fd_out))
        out = ft_strjoin(out, line);
    line = ft_strdup("");
     while (line = ft_get_next_line(fd_in))
        expected = ft_strjoin(expected, line);
    TEST_ASSERT_EQUAL_CHAR_ARRAY(expected, out, ft_strlen(expected)-1);
    pid_t pid = fork();
    if (pid == 0)
    {
        char *args[] = {"/bin/rm", "out", NULL};
        execve(args[0], args, NULL);
    }
    waitpid(pid, NULL, 0);
    close(fd_out);
}

void test_execute_minishell(void)
{
    pid_t pid = fork();
    if (pid == 0)
    {
        char *args[] = {"/bin/ls", "-l", NULL};
        int file_fd = open("files/out_origem", O_WRONLY | O_CREAT | O_TRUNC, 0777);
        dup2(file_fd, STDOUT_FILENO);
        execve(args[0], args, NULL);
    }
    waitpid(pid, NULL, 0);

    pid = fork();
    if (pid == 0)
    {
        char *args[] = {"./minishell",  NULL};
        execve(args[0], args, NULL);
        int file_fd = open("files/out_minishell", O_WRONLY | O_CREAT | O_TRUNC, 0777);
        dup2(file_fd, STDOUT_FILENO);
    }
    waitpid(pid, NULL, 0);

   /*  pid = fork();
    if (pid == 0)
    {
        char *args[] = {"/bin/ls", "-l", NULL};
        int file_fd = open("files/out_minishell", O_WRONLY | O_CREAT | O_TRUNC, 0777);
        dup2(file_fd, STDOUT_FILENO);
        execve(args[0], args, NULL);
    }
    waitpid(pid, NULL, 0); */

    char *lines_minishell = get_join_lines("files/out_minishell");
    char *lines_origem = get_join_lines("files/out_origem");
    TEST_ASSERT_EQUAL_CHAR_ARRAY(lines_minishell, lines_origem, ft_strlen(lines_origem)-1);
}

int main(int argc, char **argv, char **envp)
{
    env = envp;
    UNITY_BEGIN();
    RUN_TEST(test_env);
    RUN_TEST(test_token_word);
    RUN_TEST(test_token_redirections);
    RUN_TEST(test_lexer_module);
    RUN_TEST(test_execute_minishell);
    return UNITY_END();
}
