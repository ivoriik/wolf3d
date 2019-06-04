/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbespalk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/12 11:50:52 by vbespalk          #+#    #+#             */
/*   Updated: 2018/01/12 11:50:55 by vbespalk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <string.h>

static char		*words(char const *s, char c)
{
	size_t	len;
	char	*word;

	len = 0;
	while (*s && *s != c)
	{
		len++;
		s++;
	}
	if (!(word = (ft_strnew(len + 1))))
		return (NULL);
	word = ft_strncpy(word, s - len, len);
	return (word);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**fresh;
	size_t	row;
	size_t	num_words;

	if (!s || !(*s))
		return (NULL);
	num_words = ft_nb_words(s, c);
	if (!(fresh = (char **)malloc(sizeof(char **) * (num_words + 1))))
		return (NULL);
	row = 0;
	while (row < num_words && *s)
	{
		if (*s != c)
		{
			fresh[row] = words(s, c);
			s += ft_strlen(fresh[row]);
			row++;
			continue;
		}
		s++;
	}
	fresh[row] = NULL;
	return (fresh);
}
