/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 10:23:30 by gyong-si          #+#    #+#             */
/*   Updated: 2024/05/06 09:51:44 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Returns the message directed to stderror and then exits out*/
void	exit_handler(int exit_code)
{
	if (exit_code == 1)
		ft_putstr_fd("infile cmd cmd outfile\n", 2);
	exit(EXIT_FAILURE);
}

/* Returns file_descriptor based on the return value of the open function.
    Non-negative  = file descriptor
    -1 = File unable to open -> exit_handler is called
    0777 = Owners, Group of File and Others permission to read, write and
    execute
*/
int	open_file(const char *file, int mode)
{
	int	return_fd;

	if (mode == 0)
		return_fd = open(file, O_RDONLY, 0777);
	else
		return_fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (return_fd == -1)
		exit_handler(1);
	return (return_fd);
}

/* Frees the memory of each element until it reaches the null
terminator before freeing the memory allocated to the entire array. */

void	ft_free_tab(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

/* Searches system's PATH where commands can be found, the split this into
individual paths. Then seperates the commands into different paths

Searches through each location in path adding the naem of the command to
the end to make a full address (/usr/bin/command). Check if command at
address exists. F_OK = Exsist, X_OK = Executable. If does, cleans up
the memory used to split path and the command, gives back full
address of the command.

If doesn't moves to the next location. If all locations does not contain the
command, frees the memory and gives back the original command.*/

char	*get_path(char *cmd, t_shell *minishell)
{
	int		i;
	char	*exec;
	char	*path_part;
	char	**all_path;
	char	**s_cmd;

	i = -1;
	all_path = ft_split(get_env_value(minishell, "PATH"), ':');
	s_cmd = ft_split(cmd, ' ');
	while (all_path[++i])
	{
		path_part = ft_strjoin(all_path[i], "/");
		exec = ft_strjoin(path_part, s_cmd[0]);
		free(path_part);
		if (access(exec, F_OK | X_OK) == 0)
		{
			ft_free_tab(s_cmd);
			ft_free_tab(all_path);
			return (exec);
		}
		free(exec);
	}
	ft_free_tab(all_path);
	ft_free_tab(s_cmd);
	return (cmd);
}