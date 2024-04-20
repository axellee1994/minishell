/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 11:29:14 by gyong-si          #+#    #+#             */
/*   Updated: 2024/04/20 19:37:10 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

// token types
typedef enum s_token_type
{
	T_COMMAND,
	T_PIPE,
	T_OR,
	T_AND
}	t_token_type;

// token structure
typedef struct	s_token
{
	char			*token;
	t_token_type	type;
	struct s_token	*next;
}	t_token;

t_token *create_token(char *token, t_token_type type);

void	token_add_back(t_token **head, char *token, t_token_type type);
void	free_tokenlst(t_token *head);

int	ft_iswhitespace(char *line);
int	add_symbol_lst(char **line, t_token_type type, t_token **token_lst);
int	add_command_lst(char **line, t_token **token_lst);
t_token	*token_processor(char *line);
void	print_tokenlst(t_token *token_lst);
char	*ft_copy(char *dest, const char *src, size_t n);
char	*ft_strcat(char *dest, const char *src);
size_t	ft_wordlen(const char *s, char c);
t_token *reprocess_tokenlst(t_token *lst);


#endif