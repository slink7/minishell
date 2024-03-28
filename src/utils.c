/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 17:25:27 by scambier          #+#    #+#             */
/*   Updated: 2024/03/28 17:57:38 by scambier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	exitstatus(int status)
{
	return ((status & 0xFF00) >> 8);
}

int	perror2(int ret, char *prompt)
{
	perror(prompt);
	return (ret);
}
