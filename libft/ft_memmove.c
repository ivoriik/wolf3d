/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbespalk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/21 16:47:19 by vbespalk          #+#    #+#             */
/*   Updated: 2017/12/21 16:49:36 by vbespalk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <string.h>

void	*ft_memmove(void *s1, const void *s2, size_t n)
{
	unsigned char	*str1;
	size_t			i;

	if ((unsigned char *)s1 == (unsigned char *)s2 || n == 0)
		return (s1);
	if ((size_t)(s1 - s2) >= n)
		ft_memcpy(s1, s2, n);
	else
	{
		i = 0;
		str1 = (unsigned char *)malloc(n * sizeof(unsigned char));
		if (str1 != NULL)
		{
			while (i < n)
			{
				str1[i] = ((unsigned char *)s2)[i];
				i++;
			}
			ft_memcpy(s1, str1, n);
			free(str1);
		}
	}
	return (s1);
}
