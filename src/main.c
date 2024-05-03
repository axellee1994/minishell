/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyongsi@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 13:37:14 by gyong-si          #+#    #+#             */
/*   Updated: 2024/05/03 17:12:48 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/***
for (int i = 0; s[i] != NULL; i++) {
	printf("av[%d]: %s\n", i, s[i]);
}; **/

t_shell	*init_shell(char **envp)
{
	t_shell	*shell;
	int		p_fd[2];

	shell = (t_shell *)malloc(sizeof(t_shell));
	if (!shell)
		return (NULL);
	if (pipe(p_fd) == -1)
	{
		free(shell);
		return (NULL);
	}
	shell->env_size = 0;
	shell->env = envp;
	shell->user = my_getenv("USER", envp);
	shell->pwd = my_getenv("PWD", envp);
	shell->home = my_getenv("HOME", envp);
	shell->prompt = PROMPT;
	shell->cmd_list = NULL;
	shell->data_fd[0] = p_fd[0];
	shell->data_fd[1] = p_fd[1];
	shell->last_return = 0;
	shell->end = false;
	return (shell);
}

int execute_builtin(t_shell *minishell)
{
	char	*s;

	s = minishell->cmd_list->token;
	if (ft_strcmp(s, "history") == 0)
	{
		print_history();
		return (1);
	}
	if (ft_strcmp(s, "history -c") == 0)
	{
		clear_history();
		return (1);
	}
	if (ft_strcmp(s, "echo") == 0)
	{
		minishell_echo(minishell);
		return (1);
	}
	if (ft_strcmp(s, "env") == 0)
	{
		minishell_env(minishell);
		return (1);
	}
	if (ft_strcmp(s, "pwd") == 0)
	{
		minishell_pwd(minishell);
		return (1);
	}
	return (0);
}

	//t_ast_node	*ast_tree;
	/**
	for (int i = 0; envp[i] != NULL; i++)
    {
        printf("%s\n", envp[i]);
    } **/

int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	char		*line;
	t_token		*token_lst;
	t_shell		*g_shell;

	g_shell = init_shell(envp);
	using_history();
	setup_signal_handler();
	while (1)
	{
		line = readline(PROMPT);
		if (line == NULL)
		{
			printf("exit\n");
			break;
		}
		if (*line == '\0')
			continue;
		//printf("This is user input: %s\n", line);
		add_history(line);
		token_lst = token_processor(line);
		print_tokenlst(token_lst);
		//if (token_lst != NULL)
		//	g_shell->cmd_list = token_lst;
		//if (execute_builtin(g_shell) == 1)
		//	continue ;
		//print_ast_tree(ast_tree);
		//pipex(token_lst, envp);
		//free_tokenlst(token_lst);
	}
	return (0);
}
