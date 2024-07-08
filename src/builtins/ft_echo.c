/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorlac <adorlac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 14:22:53 by tchartie          #+#    #+#             */
/*   Updated: 2024/07/05 12:59:12 by adorlac          ###   ########.fr       */
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
