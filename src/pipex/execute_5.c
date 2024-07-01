/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_5.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:10:53 by gyong-si          #+#    #+#             */
/*   Updated: 2024/07/01 13:51:17 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*get_redir_token(t_token *curr)
{
	t_token	*redir_token;

	redir_token = NULL;
	if (curr->next && curr->next->next
		&& check_redirection_type(curr->next->next->next))
	{
		redir_token = curr->next->next;
	}
	return (redir_token);
}

void	handle_redir_child_process(t_token *curr, t_shell *minishell)
{
	t_token	*head;

	head = curr;
	signal(SIGINT, SIG_DFL);
	load_previous_fd_to_stdin(minishell);
	while (curr != NULL && curr->next != NULL
		&& check_redirection_type(curr->next))
	{
		minishell->redir_no += 1;
		handle_single_redirection(minishell, curr->next);
		if (curr->next->next != NULL)
			curr = curr->next->next;
		else
			break ;
	}
	exec_cmd(head, minishell);
}

void	handle_redir_parent_process(t_shell *minishell, int pid)
{
	signal(SIGINT, sigint_handler1);
	minishell->process_ids[minishell->process_count++] = pid;
	if (minishell->prev_fd != -1)
		close(minishell->prev_fd);
}

t_token	*execute_with_redir(t_token *curr, t_shell *minishell)
{
	int	pipe;
	int	num_of_redir;
	int	i;

	pipe = pipe_found(curr);
	num_of_redir = num_of_redirections(curr);
	i = num_of_args(curr);
	if (pipe == 0 && num_of_redir <= 3)
		execute_command_with_redir(curr, minishell);
	else
		execute_pipeline(curr, minishell);
	curr = update_curr_pointer(curr, minishell->redir_no, i);
	return (curr);
}

void	execute_command_with_redir(t_token *curr, t_shell *minishell)
{
	int	pid;

	pid = fork();
	if (!pid)
		handle_redir_child_process(curr, minishell);
	else
		handle_redir_parent_process(minishell, pid);
}
