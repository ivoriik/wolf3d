/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbespalk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 16:34:15 by vbespalk          #+#    #+#             */
/*   Updated: 2018/01/09 16:34:18 by vbespalk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t i;
	size_t j;

	i = 0;
	while (i < size && dst[i])
		i++;
	j = i;
	while ((i + 1) < size && src[i - j])
	{
		dst[i] = src[i - j];
		i++;
	}
	if (i < size)
		dst[i] = '\0';
	return (j + ft_strlen(src));
}
