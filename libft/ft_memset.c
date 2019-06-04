/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbespalk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/17 15:08:31 by vbespalk          #+#    #+#             */
/*   Updated: 2018/01/17 15:08:34 by vbespalk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char *str;

	if (n == 0)
		return (s);
	str = (unsigned char *)s;
	while (n != 0)
	{
		*str = (unsigned char)c;
		n--;
		str++;
	}
	return (s);
}
