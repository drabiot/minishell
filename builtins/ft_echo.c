/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorlac <adorlac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 14:22:53 by adorlac           #+#    #+#             */
/*   Updated: 2024/07/08 16:30:45 by adorlac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_echo(int fd, char *str, int option)
{
	int	i;

	if (!str || (option != 1 && option != 0))
		return (1);
	i = 0;
	while (str[i])
	{
		write(fd, &str[i], 1);
		i++;
	}
	//For option -n
	if (option == 1)
		write(fd, "\n", 1);
	return (0);
}
