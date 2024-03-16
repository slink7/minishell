/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_command.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 03:50:36 by scambier          #+#    #+#             */
/*   Updated: 2024/03/14 16:02:28 by scambier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_COMMAND_H
# define T_COMMAND_H

typedef struct s_command {
	char	**cmd;
	int		fd_in;
	int		fd_out;
}	t_command;

#endif