/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 17:30:18 by marvin            #+#    #+#             */
/*   Updated: 2024/02/06 17:30:18 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>

//#include <stdio.h>

#include "libft.h"
#include "header.h"

static void	here_doc_read(char *marker)
{
	char	*line;
	int		len_line;
	int		fd;

	fd = open("/tmp/here_doc", O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd < 0)
	{
		return perror("minishell: open");
	}
	line = readline("heredoc> ");
	while (ft_strncmp(line, marker, ft_strlen(line)) != 0 || ft_strlen(line) == 0)
	{
		if (ft_strncmp(line, marker, ft_strlen(line)) != 0 || ft_strlen(line) == 0)
		{
			write(fd, line, ft_strlen(line));
			write(fd, "\n", 1);
		}
		len_line = ft_strlen(line);
		line[len_line] = '\0';
		free(line);
		line = readline("heredoc> ");
	}
	free(line);
	close(fd);
}

int	here_doc(char *marker)
{
	int		fd;

	here_doc_read(marker);
	fd = open("/tmp/here_doc", O_RDONLY, 0644);
	if (fd == -1)
		perror("minishell: open");
	return (fd);
}