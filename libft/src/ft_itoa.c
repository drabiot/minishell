/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 16:09:08 by tchartie          #+#    #+#             */
/*   Updated: 2023/11/05 13:21:29 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

/*
** Calculate the power of a given integer
*/
static int	ft_find_power(int nb)
{
	int	pow;

	pow = 1;
	while (nb / 10 != 0)
	{
		nb /= 10;
		pow *= 10;
	}
	return (pow);
}

/*
** Transform an integer into a string
*/
static char	*ft_putnbr(int nb, char *arr)
{
	int	pow;
	int	i;

	i = 0;
	pow = ft_find_power(nb);
	if (nb < 0)
	{
		arr[i] = '-';
		nb *= -1;
		i++;
	}
	while (pow >= 1)
	{
		arr[i] = (nb / pow) + '0';
		nb %= pow;
		pow /= 10;
		i++;
	}
	arr[i] = 0;
	return (arr);
}

/*
** Calculate the len of the given integer
*/
static int	ft_size(int nb)
{
	int	i;

	i = 1;
	if (nb < 0)
		i++;
	while (nb / 10 != 0)
	{
		nb /= 10;
		i++;
	}
	return (i);
}

/*
** Allocates & returns a string
** representing the integer received as an argument.
** Negative numbers must be handled
*/
char	*ft_itoa(int n)
{
	int		i;
	char	*arr;

	i = ft_size(n);
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	else
	{
		arr = (char *)malloc(sizeof(char) * (i + 1));
		if (!arr)
			return (NULL);
		arr = ft_putnbr(n, arr);
		return (arr);
	}
}
