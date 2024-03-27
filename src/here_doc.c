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

#include "libft.h"
#include "header.h"

#define HEREDOC_FILE "/tmp/here_doc"
#define HEREDOC_PROMPT "heredoc> "

static void	here_doc_read(char *marker)
{
	char	*line;
	int		len;
	int		fd;

	fd = open(HEREDOC_FILE, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd < 0)
		return (perror("minishell: open"));
	line = readline(HEREDOC_PROMPT);
	while (1)
	{
		len = ft_strlen(line);
		if (!line || ft_strncmp(line, marker, len + 1) == 0)
			break ;
		write(fd, line, len);
		write(fd, "\n", 1);
		free(line);
		line = readline(HEREDOC_PROMPT);
	}
	free(line);
	close(fd);
}

int	here_doc(char *marker)
{
	int		fd;

	here_doc_read(marker);
	fd = open(HEREDOC_FILE, O_RDONLY, 0644);
	if (fd == -1)
		perror("minishell: open");
	return (fd);
}
