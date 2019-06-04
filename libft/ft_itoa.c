/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbespalk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/12 14:08:27 by vbespalk          #+#    #+#             */
/*   Updated: 2018/01/12 14:08:29 by vbespalk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_itoa(int n)
{
	unsigned int	len;
	unsigned int	nb;
	char			*num;

	len = 0;
	if (n < 0)
	{
		len++;
		nb = -n;
	}
	else
		nb = n;
	len++;
	while (n /= 10)
		len++;
	if (!(num = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	num[len] = '\0';
	num[--len] = nb % 10 + '0';
	while (nb /= 10)
		num[--len] = nb % 10 + '0';
	if (len)
		num[--len] = '-';
	return (num);
}
