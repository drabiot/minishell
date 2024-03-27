/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:58:00 by tchartie          #+#    #+#             */
/*   Updated: 2024/03/26 16:02:08 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "lexer.h"

typedef struct s_cmd
{
	char            *arg;
    int             type;
    int             index;
    struct s_cmd   *next;
}			        t_cmd;

int prompt(void);
char	**lexer(char *input);
void	tokenizer(t_input *cmd);

#endif //MINISHELL_H