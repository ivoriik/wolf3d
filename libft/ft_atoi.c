/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbespalk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 12:32:34 by vbespalk          #+#    #+#             */
/*   Updated: 2017/09/25 13:32:40 by vbespalk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_atoi(const char *str)
{
	unsigned long int	nb;
	int					mult;

	nb = 0;
	mult = 1;
	while (ft_isspace(*str))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			mult = -1;
		str++;
	}
	while (ft_isdigit(*str))
	{
		nb = nb * 10 + (*str - '0');
		if (nb >= 9223372036854775807 && mult == 1)
			return (-1);
		else if (nb > 9223372036854775807 && mult == -1)
			return (0);
		str++;
	}
	return ((int)(nb * mult));
}
