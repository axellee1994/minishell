/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 13:35:24 by axlee             #+#    #+#             */
/*   Updated: 2024/06/12 15:34:02 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_token_pointers(t_token *tokens)
{
	t_token	*prev_token;
	t_token	*curr_token;

	prev_token = NULL;
	curr_token = tokens;
	while (curr_token != NULL)
	{
		curr_token->prev = prev_token;
		if (prev_token != NULL)
			prev_token->next = curr_token;
		prev_token = curr_token;
		curr_token = curr_token->next;
	}
	if (prev_token != NULL)
		prev_token->next = NULL;
}

static void parse_unclosed(t_token *token, t_shell *minishell)
{
	char	*input;
	char	*command;
	int		inside_quote;
	int		len;
	int		i;
	char	*trimmed_command;

	i = 0;
	input = token->token;
	len = ft_strlen(input);
	command = ft_strdup("");
	inside_quote = 0;
	minishell->flag = 1;
	while (i < len || inside_quote)
	{
        if (i < len)
		{
            if (input[i] == '"')
                inside_quote = !inside_quote;
            command = realloc(command, ft_strlen(command) + 2);
            ft_strncat(command, &input[i], 1);
        }
        if (inside_quote && i == len - 1)
		{
            char *delimiter = "\"";
            if (here_doc(minishell, delimiter) == -1)
			{
				fprintf(stderr, "Error in here_doc\n");
				free(command);
				return ;
			}
			inside_quote = 0;
		}
		i++;
	}
	trimmed_command = ft_strtrim(command, "\"");
	free(command);
	free(token->token);
	token->token = ft_strdup(trimmed_command);
	free(trimmed_command);
}

/** *
static void	parse_unclosed_quote(t_token *token, t_shell *minishell)
{
	char	opening_quote;
	char	ending_quote;
	int		flag;
	char	*str;
	char buffer[1024];
	ssize_t bytes_read;

	str = token->token;
	flag = 0;
	opening_quote = str[0];
	ending_quote = str[ft_strlen(str) - 1];
	if (opening_quote != ending_quote)
		flag = 1;
	if (flag)
	{
		if (here_doc(minishell, &opening_quote) == -1)
		{
			ft_putstr_fd("Error in here_doc\n", 2);
			return ;
		}
		while ((bytes_read = read(minishell->input_fd, buffer, sizeof(buffer) - 1)) > 0)
		{
			buffer[bytes_read] = '\0';
			command = ft_realloc(command, ft_strlen(command), ft_strlen(command) + bytes_read + 1);
			ft_strcat(command, buffer);
		}
	}
} **/

static int check_unclosed(t_token *token)
{
	char *str;
	int len;
	int i;
	int inside_quote = 0;

	i = 0;
	str = token->token;
	len = ft_strlen(str);
	while (i < len)
	{
		if (str[i] == '"')
			inside_quote = !inside_quote;
		i++;
	}
	return (inside_quote);
}


void	parse_token(t_token *token, t_shell *minishell)
{
	char	*str;
	int		len;

	str = token->token;
	len = ft_strlen(str);
	if (str[0] == '\0' || (str[0] == '\\' && str[1] == '\0'))
	{
		free(token->token);
		token->token = ft_strdup(" ");
	}
	if (len > 1)
	{
		if (str[0] == '\'' && str[len - 1] == '\'')
			parse_single_quotes(token);
		else if (str[0] == '\"' && str[len - 1] == '\"')
			parse_double_quotes(token, minishell);
		else if (check_unclosed(token) == 1)
		{
			parse_unclosed(token, minishell);
		}
		else
			remove_embedded_quotes(token);
	}
	str = token->token;
	len = ft_strlen(str);
	if (minishell->flag)
	{
		if (ft_strchr(token->token, '$') && !token->is_single_quoted)
			parse_value(token, minishell);
	}
}

t_token	*token_parser(t_token *token_lst, t_shell *minishell)
{
	t_token	*curr;

	curr = token_lst;
	while (curr != NULL)
	{
		parse_token(curr, minishell);
		curr = curr->next;
	}
	set_token_pointers(token_lst);
	join_identifier_tokens(token_lst);
	return (token_lst);
}