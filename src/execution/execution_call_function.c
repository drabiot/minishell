/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_call_function.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorlac <adorlac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 11:45:27 by nberduck          #+#    #+#             */
/*   Updated: 2024/07/09 14:54:46 by adorlac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	have_call_function(char *line)
{
	int	i;
	int	j;
	int	start;

	i = 0;
	start = 0;
	while (line[i] && line[i + 1])
	{
		if (line[i] == '$' && line[i + 1] == '(')
		{
			start--;
			j = i;
			while (line[j])
			{
				if (line[j] == ')' && start == -1)
					return (i);
				else if (line[j] == ')')
					start++;
				j++;
			}
		}
		i++;
	}
	return (-1);
}

int	ft_get_end_call_function(char *line)
{
	int	i;
	int	j;
	int	start;

	i = 0;
	start = 0;
	while (line[i] && line[i + 1])
	{
		if (line[i] == '$' && line[i + 1] == '(')
		{
			start--;
			j = i;
			while (line[j])
			{
				if (line[j] == ')' && start == -1)
					return (j);
				else if (line[j] == ')')
					start++;
				j++;
			}
		}
		i++;
	}
	return (-1);
}

static t_cmd	*ft_tokenized(t_input *cmd, t_glob **t_envp)
{
	unsigned int		index = 0;
	t_token				token;
	t_cmd				*start;
	char				*arg;
	char				c;

	start = NULL;
	token = (t_token){0};
	while (cmd->str[cmd->i])
	{
		grab_token(cmd, &token);
		c = cmd->str[token.end + 1];
		cmd->str[token.end + 1] = 0;
		// printf("start: %d, end: %d (%s)\n", token.start, token.end, &cmd->str[token.start]);
		arg = ft_substr(cmd->str, token.start, token.end - token.start + 1);
		ft_lstadd_back_cmd(&start, ft_cmd_creation(arg, index, start));
		cmd->str[token.end + 1] = c;
		cmd->i++;
		index++;
	}
	ft_expand(&start, *t_envp);
	return (start);
}

static t_cmd	*execution_lexer(char *input, t_glob **t_envp)
{
	t_input	cmd;
	t_cmd	*return_value;

	cmd = (t_input){0};
	cmd.str = input;
	cmd.i = 0;
	return_value = ft_tokenized(&cmd, t_envp);
	return (return_value);
}

static int	ft_get_len_string(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == ')')
			return (i);
		i++;
	}
	return (0);
}

static int	ft_get_string(char **line_cut, char *line, int start)
{
	int		i;
	int		len;

	len = ft_get_len_string(&line[start]);
	if (len < 3)
		return (2);
	*line_cut = malloc((len + 1) * sizeof (char));
	if (!*line_cut)
		return (1);
	i = 0;
	while (line[i + start] && line[i + start] != ')')
	{
		line_cut[0][i] = line[i + start];
		i++;
	}
	line_cut[0][i] = '\0';
	return (0);
}

static char	*ft_strndup(char *line, int len)
{
	char	*tmp;
	int		i;
	
	tmp = malloc((len + 1) * sizeof(char));
	if (!tmp)
		return (NULL);
	i = 0;
	while (i < len)
	{
		tmp[i] = line[i];
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}

static char	*ft_join_line(char *line, char *fd_name, int start_call)
{
	char	*start;
	char	*tmp;
	char	*line_tmp;
	int		fd;
	int		len_end;
	int		len;

	// printf("%i\n", fd);
	start = ft_strndup(line, start_call - 2);
	if (!start)
		return (NULL);
	fd = open(fd_name, O_RDWR);
	line_tmp = get_next_line(fd);
	printf("%s,%s.\n", start, line_tmp);
	while (line_tmp)
	{
		printf("%s,\n", line_tmp);
		tmp = ft_strjoin(start, line_tmp);
		free(start);
		free(line_tmp);
		start = tmp;
		line_tmp = get_next_line(fd);
	}
	// printf("%s.\n", start);
	len_end = ft_get_end_call_function(line);
	if (!line[len_end + 1])
		return (start);
	len = ft_strlen(&line[len_end + 1]);
	line_tmp = ft_strndup(&line[len_end + 1], len);
	printf("%s;\n", line_tmp);
	tmp = ft_strjoin(start, line_tmp);
	if (!tmp)
		return (NULL);
	free(start);
	free(line_tmp);
	close(fd);
	return (tmp);
}

char	*ft_call_function_main(char *line, t_glob **t_envp)
{
	int		start;
	int		return_value;
	int		call_fd;
	char	*fd_name;
	char	*line_cut;
	t_cmd	*cmd;

	printf("%s\n", line);
	start = have_call_function(line) + 2;
	if (!line[start] && !line[start + 1] && !line[start + 2])
		return (line);
	return_value = ft_get_string(&line_cut, line, start);
	if (return_value == 2)
		return (line);
	if (return_value == 1)
		return (NULL);
	cmd = execution_lexer(line_cut, t_envp);
	fd_name = create_file(&call_fd);
	// printf("%i\n", call_fd);
	ft_execution_cmd(call_fd, t_envp, cmd);
	line = ft_join_line(line, fd_name, start);
	// close(call_fd);
	// free(cmd);
	return (line);
}
