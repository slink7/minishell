/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 14:48:42 by scambier          #+#    #+#             */
/*   Updated: 2024/04/02 10:47:19 by scambier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#include "libft.h"
#include "header.h"

#define TYPE_IN1 1
#define TYPE_OUT1 2
#define TYPE_IN2 4
#define TYPE_OUT2 8

#define TYPE_DOUBLE 12

static int	replace_fd(int *fd, int new_fd)
{
	if (!fd)
		return (0);
	if (*fd < 0 || *fd > 2)
		close(*fd);
	*fd = new_fd;
	return (1);
}

static int	replace_fd_file(int *fd, char *file, int flags, int perms)
{
	int	new_fd;

	if (!file || !*file)
		return (1);
	new_fd = open(file, flags, perms);
	if (new_fd == -1)
		return (perror2(0, ERR_OPEN));
	return (replace_fd(fd, new_fd));
}

static int	next_redir(char *str, char **out, int type)
{
	char	*temp;

	*out = ft_strchr(str, '<');
	if (*out)
		type = TYPE_IN1;
	temp = ft_strchr(str, '>');
	if (temp && (temp < *out || !*out))
	{
		*out = temp;
		type = TYPE_OUT1;
	}
	temp = ft_strnstr(str, "<<", ft_strlen(str));
	if (temp && (temp <= *out || !*out))
	{
		*out = temp;
		type = TYPE_IN2;
	}
	temp = ft_strnstr(str, ">>", ft_strlen(str));
	if (temp && (temp <= *out || !*out))
	{
		*out = temp;
		type = TYPE_OUT2;
	}
	return (type);
}

static int	set_cmd_fd(t_command *cmd, int type, char *file)
{
	int	out;

	out = 0;
	if (type == TYPE_IN1)
		out = replace_fd_file(&cmd->fd_in, file, O_RDONLY, 0777);
	else if (type == TYPE_IN2)
		out = replace_fd(&cmd->fd_in, here_doc(file));
	else if (type == TYPE_OUT1)
		out = replace_fd_file(&cmd->fd_out, file, 577, 0644);
	else if (type == TYPE_OUT2)
		out = replace_fd_file(&cmd->fd_out, file, 1089, 0644);
	return (out);
}

int	set_command_from_str(t_command *cmd, char *str)
{
	char	*nr;
	char	*temp;
	int		type;

	type = next_redir(str, &nr, 0);
	while (type)
	{
		temp = get_next_word(nr + 1 + !!(type & TYPE_DOUBLE), s);
		if (!temp && ft_printf_fd(2, "Error : wrong file name"))
			return (0);
		unescape(temp);
		set_cmd_fd(cmd, type, temp);
		free(temp);
		temp = nr + 1 + !!(type & TYPE_DOUBLE);
		goto_falling_edge(&temp, s);
		ft_strlcpy(nr, temp + 1, ft_strlen(temp));
		type = next_redir(nr, &nr, 0);
	}
	cmd->cmd = ft_splitf(str, s);
	type = -1;
	while (cmd->cmd[++type])
		unescape(cmd->cmd[type]);
	return (1);
}
