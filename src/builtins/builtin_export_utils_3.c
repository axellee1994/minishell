/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 22:45:07 by gyong-si          #+#    #+#             */
/*   Updated: 2024/05/23 17:08:13 by axlee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	print_invalid_identifier(char *content)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(content, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	return (1);
}

static char	*process_quotes(char *var_value)
{
	char	quote_type;
	char	*end_quote;

	quote_type = *var_value;
	var_value++;
	end_quote = ft_strrchr(var_value, quote_type);
	if (end_quote)
	{
		*end_quote = '\0';
	}
	return (var_value);
}

static void	create_and_set_env_entry(t_shell *minishell, char *var_name,
		char *var_value, int var_index)
{
	char	*new_entry;

	new_entry = (char *)malloc(ft_strlen(var_name) + ft_strlen(var_value) + 2);
	if (!new_entry)
	{
		free(var_name);
		return ;
	}
	ft_strcpy(new_entry, var_name);
	ft_strcat(new_entry, "=");
	ft_strcat(new_entry, var_value);
	create_env_entry(new_entry, var_name, var_value);
	set_env_entry(minishell, new_entry, var_index);
	free(var_name);
}

static int	validate_and_extract_var(char *content, char **var_name,
		char **var_value)
{
	if (ft_strchr(content, '=') == NULL)
	{
		if (!is_valid_identifier(content))
			return (print_invalid_identifier(content));
		return (0);
	}
	*var_name = get_var_name(content);
	if (!(*var_name) || !is_valid_identifier(*var_name))
	{
		return (print_invalid_identifier(content));
	}
	*var_value = ft_strchr(content, '=') + 1;
	if (**var_value == '\"' || **var_value == '\'')
	{
		*var_value = process_quotes(*var_value);
	}
	return (-1);
}

int	save_var(t_shell *minishell, char *content)
{
	char	*var_name;
	char	*var_value;
	int		var_index;
	int		result;

	result = validate_and_extract_var(content, &var_name, &var_value);
	if (result != -1)
	{
		minishell->last_return = result;
		return (1);
	}
	var_index = search_env(minishell, var_name);
	if (var_index == -1)
		var_index = env_len(minishell);
	create_and_set_env_entry(minishell, var_name, var_value, var_index);
	return (0);
}
