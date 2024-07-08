/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorlac <adorlac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 18:21:45 by tchartie          #+#    #+#             */
/*   Updated: 2024/07/05 11:48:58 by adorlac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

typedef struct s_input
{
	char	*str;
	int		i;
}			t_input;

typedef struct s_token
{
	int	start;
	int	end;
}			t_token;

#endif //LEXER_H