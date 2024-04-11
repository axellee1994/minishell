/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 13:37:14 by gyong-si          #+#    #+#             */
/*   Updated: 2024/04/11 10:18:20 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	prompt()
{
	printf("minishell$");
	fflush(stdout);
	usleep(500000);
	fflush(stdout);
	usleep(500000);
}

int	main()
{
	char	*input;

	while (1)
	{
		prompt();
		input = readline(" ");
		if (input == NULL)
			break ;
	}
	return (0);
}
