/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_pipe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorlac <adorlac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 16:42:30 by adorlac           #+#    #+#             */
/*   Updated: 2024/07/09 15:06:29 by adorlac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// int	ft_execution_pipe_main(t_glob **t_envp, t_cmd *cmd, int len_pipe)
// {
// 	int		fd[2];
// 	pid_t	pid1;
// 	pid_t	pid2;

// 	(void)len_pipe;
// 	// (void)t_envp;
// 	// (void)cmd;
// 	// printf("len_pipe :%i\n", len_pipe);
// 	if (pipe(fd) == -1)
// 		return (1);	
// 	pid1 = fork();
// 	if (pid1 < 0)
// 	    return (1);
// 	if (pid1 == 0)
// 	{
// 	    dup2(fd[1], STDOUT_FILENO);
// 		close(fd[0]);
// 	    close(fd[1]);
// 		ft_start_execution(STDOUT_FILENO, t_envp, cmd, 1);
// 		// execlp("ping", "ping", "-c", "5", "google.com", NULL);
// 		// exit(0);
// 	}
// 	pid2 = fork();
// 	if (pid2 < 0)
// 	    return (1);
// 	if (pid2 == 0)
// 	{
// 	    dup2(fd[0], STDIN_FILENO);
// 	    close(fd[1]);
// 		close(fd[0]);
// 		ft_start_execution(STDIN_FILENO, t_envp, cmd, 2);
// 		// exit(0);
// 		// execlp("grep", "grep", "rtt", NULL);
// 	}
// 	close(fd[0]);
// 	close(fd[1]);
// 	waitpid(pid1, NULL, 0);
// 	waitpid(pid2, NULL, 0);
// 	return (0);
// }
