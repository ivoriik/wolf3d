/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbespalk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/18 14:26:28 by vbespalk          #+#    #+#             */
/*   Updated: 2018/08/18 14:26:32 by vbespalk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	ft_error(const char *message)
{
	ft_putstr_fd("Error: ", 2);
	if (message)
		ft_putstr_fd(message, 2);
	else
		perror(NULL);
	exit(-1);
}

int		ft_perror(const char *message)
{
	ft_putstr_fd("Error: ", 2);
	if (message)
		ft_putstr_fd(message, 2);
	else
		perror(NULL);
	return (-1);
}

void	ft_usage(const char *message)
{
	ft_putstr_fd("usage: ", 2);
	if (message)
		ft_putstr_fd(message, 2);
	exit(-1);
}
