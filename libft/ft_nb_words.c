/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nb_words.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbespalk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 19:34:37 by vbespalk          #+#    #+#             */
/*   Updated: 2018/02/05 19:35:03 by vbespalk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

size_t	ft_nb_words(char const *s, char c)
{
	size_t	words;
	short	is_word;

	words = 0;
	is_word = 0;
	while (*s)
	{
		if (*s != c && !is_word)
		{
			words++;
			is_word = 1;
		}
		else if (*s == c)
			is_word = 0;
		s++;
	}
	return (words);
}
