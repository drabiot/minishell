/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 16:06:31 by tchartie          #+#    #+#             */
/*   Updated: 2024/01/16 16:06:44 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

/*
** Generate keys to randomize the result
*/
static void	gen_bit_shift_rng(unsigned int seed, unsigned int keys[5])
{
	int	k1;
	int	k2;
	int	k3;

	k1 = (seed << 28) ^ (seed >> 7);
	k2 = (k1 >> 13) ^ ((seed >> 9) ^ k1);
	k3 = k1 ^ (k2 >> 12) ^ (seed << 24);
	keys[0] = (k3 >> 11) ^ (k2 << 1);
	keys[1] = (k1 >> 6) ^ ((k2 >> 9) ^ (k3 >> 16));
	keys[2] = k3 ^ (k1 >> 10);
	keys[3] = keys[1] ^ (k2 >> 27);
	keys[4] = (seed >> 14) ^ (k1 > 26);
}

/*
** Take the given seed and return a random number between
** the two provided numbers as arguments
*/
static unsigned int	ft_rrand(int init, unsigned int seed, unsigned int min,
		unsigned int max)
{
	static unsigned int	s_seed;
	unsigned int		key[5];
	int					range;

	range = max - min + 1;
	if (init)
	{
		s_seed = seed;
		return (s_seed);
	}
	gen_bit_shift_rng(s_seed, key);
	s_seed = key[0] ^ (key[1] << 13) ^ (key[2] >> 5) ^ key[3];
	s_seed ^= key[4] << (key[2] ^ key[1]) % 15;
	s_seed >>= 3;
	s_seed ^= key[2] ^ key[4];
	return ((s_seed % range) + min);
}

/*
** Initialize the given seed
*/
void	ft_srand(unsigned int seed)
{
	if (seed == 0)
		seed = 1;
	ft_rrand(1, seed, 0, 0);
}

/*
** Take two numbers and provide a random number between them
*/
int	ft_rand(int a, int b)
{
	unsigned int	umin;
	unsigned int	umax;

	if (a == b)
		return (a);
	if (a > b)
	{
		a += b;
		b = a - b;
		a = a - b;
	}
	if (a < 0)
	{
		umin = -a;
		umax = b + umin;
		return (ft_rrand(0, 0, 0, umax) - umin);
	}
	return (ft_rrand(0, 0, a, b));
}
