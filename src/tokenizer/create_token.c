/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 19:36:29 by gyong-si          #+#    #+#             */
/*   Updated: 2024/05/06 09:59:28 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// create a new node
t_token	*create_token(char *token, t_token_type type)
{
	t_token	*new_node;

	new_node = malloc(sizeof(t_token));
	if (!new_node)
		return (NULL);
	new_node->token = ft_strdup(token);
	if (!new_node->token)
	{
		free(new_node);
		return (NULL);
	}
	new_node->type = type;
	new_node->next = NULL;
	new_node->prev = NULL;
	return (new_node);
}

void	token_add_back(t_token **head, char *token, t_token_type type)
{
	t_token	*current_node;
	t_token	*prev_node;
	t_token	*new_node;

	new_node = create_token(token, type);
	if (!new_node)
		return ;
	current_node = *head;
	prev_node = NULL;
	while (current_node != NULL)
	{
		prev_node = current_node;
		current_node = current_node->next;
	}
	if (prev_node == NULL)
		*head = new_node;
	else
	{
		new_node->prev = prev_node;
		prev_node->next = new_node;
	}
}

// free the memory for linked list
void free_tokenlst(t_token *head)
{
    t_token *current_node;
    t_token *tmp;

    current_node = head;
    while (current_node != NULL)
    {
        tmp = current_node;
        current_node = current_node->next;
        if (tmp->token != NULL)
        {
            free(tmp->token);
            tmp->token = NULL;
        }
        free(tmp);
    }
    head = NULL;
}
