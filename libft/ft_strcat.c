/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbespalk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/26 18:00:36 by vbespalk          #+#    #+#             */
/*   Updated: 2017/12/26 18:00:38 by vbespalk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *dest, const char *src)
{
	char		*s1;
	const char	*s2;

	s1 = dest;
	s2 = src;
	while (*s1)
		s1++;
	while ((*s1++ = *s2++))
		;
	return (dest);
}
