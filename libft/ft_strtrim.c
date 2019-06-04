/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbespalk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/17 17:59:48 by vbespalk          #+#    #+#             */
/*   Updated: 2018/01/17 17:59:50 by vbespalk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int		is_space(char x)
{
	return (x == ' ' || x == '\n' || x == '\t');
}

static size_t	ft_trim_len(const char *s)
{
	size_t	len;

	len = 0;
	while (is_space(*s))
		s++;
	while (s[len])
		len++;
	if (len)
		while (is_space(s[len - 1]))
			len--;
	return (len);
}

char			*ft_strtrim(char const *s)
{
	char	*str;
	char	*tmp;
	size_t	len;

	if (s == NULL)
		return (NULL);
	len = ft_trim_len(s);
	if (!(str = ft_strnew(len)))
		return (NULL);
	while (is_space(*s))
		s++;
	tmp = str;
	while (*s && len--)
		*tmp++ = *s++;
	return (str);
}
