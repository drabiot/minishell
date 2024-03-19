/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberduck <nberduck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 14:22:53 by nberduck          #+#    #+#             */
/*   Updated: 2024/03/19 15:33:43 by nberduck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_echo(char *str, int option)
{
	if (!str || (option != 1 && option != 0))
		return (1);
	printf("%s", str);
	//For option -n
	if (option == 1)
		printf("\n");
	return (0);
}