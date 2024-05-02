/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyongsi@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 12:16:40 by gyong-si          #+#    #+#             */
/*   Updated: 2024/05/02 16:16:24 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_wordlen(const char *s, char c)
{
	size_t	i;

	i = 0;
	while (*s && *s != c)
	{
		i++;
		s++;
	}
	return (i);
}

int	add_symbol_lst(char **line, t_token_type type, t_token **token_lst)
{
	t_token	*new_token;
	int	word_len;
	char	*symbol;

	word_len = ft_wordlen(*line, ' ');
	symbol = (char *)malloc(sizeof(char) + 1);
	if (!symbol)
		return (0);
	ft_copy(symbol, *line, word_len);
	new_token = create_token(symbol, type);
	if (!new_token)
		return (0);
	token_add_back(token_lst, symbol, type);
	if (type == T_LEFT_SHIFT || type == T_RIGHT_SHIFT)
		(*line) += 2;
	else
		(*line)++;
	return (1);
}

int	add_command_lst(char **line, t_token **token_lst)
{
	t_token	*new_token;
	size_t	word_len;
	size_t	semi_index;
	int		flag;
	char 	*semicolon_pos;
	char	*cmd;

	flag = 0;
	semicolon_pos = ft_strchr(*line, ';');
	semi_index = (semicolon_pos - *line);
	word_len = ft_wordlen(*line, ' ');
	if (semi_index < word_len)
	{
		flag = 1;
		word_len = semi_index;
	}
	cmd = (char *)malloc(word_len + 1);
	if (!cmd)
		return (0);
	ft_copy(cmd, *line, word_len);
	new_token = create_token(cmd, T_IDENTIFIER);
	if (!new_token)
		return (0);
	token_add_back(token_lst, cmd, T_IDENTIFIER);
	if (flag)
	{
		while (*line != NULL && **line != '\0')
			(*line)++;
	}
	(*line) += word_len;
	return (1);
}

static	char 	*concat_token(const char *token1, const char *token2)
{
	size_t	len1;
	size_t	len2;
	size_t	total_len;
	char	*joined_str;

	len1 = ft_strlen(token1);
	len2 = ft_strlen(token2);
	total_len = len1 + len2 + 2;
	joined_str = (char *)malloc(total_len);
	if (!joined_str)
		return (NULL);
	ft_copy(joined_str, token1, len1);
	ft_strcat(joined_str, " ");
	ft_strcat(joined_str, token2);
	return (joined_str);
}

t_token *token_parser(t_token *lst)
{
	char *joined;
	t_token *curr;
	t_token *next;
	int	merged;

	merged = 1;
	while (merged)
	{
		merged = 0;
		curr = lst;
		while (curr != NULL && curr->next != NULL)
		{
			if (curr->type == T_IDENTIFIER && curr->next->type == T_IDENTIFIER)
			{
				joined = concat_token(curr->token, curr->next->token);
				if (joined != NULL)
				{
					free(curr->token);
					free(curr->next->token);
					curr->token = joined;
					next = curr->next;
					curr->next = next->next;
					free(next);
				}
				merged = 1;
				break ;
			}
			curr = curr->next;
		}
	}
	return (lst);
}

t_token	*token_processor(char *line)
{
	t_token *token_lst;

	token_lst = NULL;
	while (*line != '\0')
	{
		if (ft_iswhitespace(line) || ft_isbackslash(line))
			line++;
		else if (!ft_strncmp(line, "|", 1))
			add_symbol_lst(&line, T_PIPE, &token_lst);
		else if (!ft_strncmp(line, "||", 2))
			add_symbol_lst(&line, T_OR, &token_lst);
		else if (!ft_strncmp(line, "&&", 2))
			add_symbol_lst(&line, T_AND, &token_lst);
		else if (!ft_strncmp(line, "<<", 2))
			add_symbol_lst(&line, T_LEFT_SHIFT, &token_lst);
		else if (!ft_strncmp(line, "<", 1))
			add_symbol_lst(&line, T_LESSER_THAN, &token_lst);
		else if (!ft_strncmp(line, ">>", 2))
			add_symbol_lst(&line, T_RIGHT_SHIFT, &token_lst);
		else if (!ft_strncmp(line, ">", 1))
			add_symbol_lst(&line, T_GREATER_THAN, &token_lst);
		else
			add_command_lst(&line, &token_lst);
	}
	token_lst = token_parser(token_lst);
	return (token_lst);
}
