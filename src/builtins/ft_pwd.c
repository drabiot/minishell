/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorlac <adorlac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 14:54:39 by tchartie          #+#    #+#             */
/*   Updated: 2024/07/05 12:57:40 by adorlac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_pwd(void)
{
	char			*pwd;
	unsigned int	len;

	len = 10;
	pwd = malloc(len * sizeof(char));
	if (!pwd)
		return (NULL);
	while (!getcwd(pwd, len))
	{
		len += 10;
		free(pwd);
		pwd = malloc(len * sizeof(char));
		if (!pwd)
			return (NULL);
	}
	//Caution errno is set to ERANGE in getcwd
	return (pwd);
}
