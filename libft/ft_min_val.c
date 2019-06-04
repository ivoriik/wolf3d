/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_min_val.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbespalk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 19:04:55 by vbespalk          #+#    #+#             */
/*   Updated: 2018/02/05 19:04:57 by vbespalk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

int		ft_min_val(int *array, size_t size)
{
	int min;
	int i;

	i = -1;
	min = *array;
	while (++i < (int)(size / sizeof(int)))
	{
		if (*array < min)
			min = *array;
		array++;
	}
	return (min);
}
