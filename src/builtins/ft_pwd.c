/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberduck <nberduck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 14:54:39 by nberduck          #+#    #+#             */
/*   Updated: 2024/03/19 15:33:51 by nberduck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_pwd(void)
{
	char *pwd;
	unsigned int len;
	
	len = 10;
	pwd = malloc(len*sizeof(char));
	if (!pwd)
		return (NULL);
	while (!getcwd(pwd, len))
	{ 
		len += 10;
		free(pwd);
		pwd = malloc(len*sizeof(char));
		if (!pwd)
			return (NULL);
	}
	//Caution errno is set to ERANGE in getcwd
	return (pwd);
}