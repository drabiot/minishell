/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_here_doc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nberduck <nberduck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 00:14:12 by nberduck          #+#    #+#             */
/*   Updated: 2024/06/10 12:07:39 by nberduck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*generate_random_file(char *tmp_file)
{
	int		c_rand;
	char	*suff;
	char	*final_file;

	c_rand = ft_rand(0, 51);
	suff = ft_substr("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ",
			c_rand, 1);
	final_file = ft_strjoin(suff, tmp_file);
	if (tmp_file)
		free(tmp_file);
	if (suff)
		free(suff);
	return (final_file);
}

static char	*create_file(int *tmp_fd)
{
	char	*tmp_file;

	tmp_file = ft_strdup("tmp");
	if (!tmp_file)
		return (NULL);
	*tmp_fd = open(tmp_file, O_EXCL | O_CREAT, S_IRWXU);
	while (*tmp_fd == -1)
	{
		tmp_file = generate_random_file(tmp_file);
		*tmp_fd = open(tmp_file, O_EXCL | O_WRONLY | O_CREAT, S_IRWXU);
	}
	return (tmp_file);
}

static void	set_infile(t_glob **t_envp, int *tmp_fd, char *limiter, int have_quote)
{
	char	*line;
	int		len_limiter;

	len_limiter = ft_strlen(limiter);
	ft_putstr_fd("> ", STDOUT_FILENO);
	line = get_next_line(STDIN_FILENO);
	if (have_quote)
		line = ft_expand_line(t_envp , line);
	while (line && ft_strncmp(line, limiter, len_limiter + 1))
	{
		ft_putstr_fd(line, *tmp_fd);
		free(line);
		ft_putstr_fd("> ", STDOUT_FILENO);
		line = get_next_line(STDIN_FILENO);
		if (have_quote)
			line = ft_expand_line(t_envp , line);
	}
	if (line)
		free(line);
	close(*tmp_fd);
}
static char	*ft_delete_quote(char *arg)
{
	char	*line;
	int		i;
	int		len;
	
	len = ft_strlen(arg);
	line = malloc((len - 2) * sizeof(char));
	if (!line)
		return (NULL);
	i = 1;
	while (i < len - 1)
	{
		line[i - 1] = arg[i];
		i++;
	}
	line[i - 1] = '\0';
	return (line);
}
int	ft_here_doc(t_glob **t_envp, t_cmd *cmd)
{
	int		tmp_fd;
	char	*tmp_name;
	char	*line;
	char	*limiter;
	int		have_quote;

	tmp_name = create_file(&tmp_fd);
	if (!tmp_name)
		return (1);
	have_quote = 0;
	if (cmd->next->arg[0] == '"' || cmd->next->arg[0] == '\'')
	{
		have_quote = 1;
		line = ft_delete_quote(cmd->next->arg);
		free(cmd->next->arg);
		cmd->next->arg = line;
	}
	limiter = ft_strjoin(cmd->next->arg, "\n");
	set_infile(t_envp, &tmp_fd, limiter, have_quote);
	tmp_fd = open(tmp_name, O_RDONLY);
	line = get_next_line(tmp_fd);
	while (line)
	{
		free(cmd->next->arg);
		cmd->next->arg = line;
		ft_start_execution(1, t_envp, cmd, 1);
		free(line);
		line = get_next_line(tmp_fd);
	}
	close(tmp_fd);
	unlink(tmp_name);
	return (0);
}
