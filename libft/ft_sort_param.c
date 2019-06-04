/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_param.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbespalk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 19:42:09 by vbespalk          #+#    #+#             */
/*   Updated: 2018/02/05 19:42:11 by vbespalk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**sort_param(int argc, char **argv)
{
	char	**tmp;
	int		i;
	int		j;

	tmp = argv;
	i = 1;
	while (i < argc - 1)
	{
		j = i + 1;
		while (j < argc)
		{
			if (ft_strcmp(argv[i], argv[j]) > 0)
			{
				*tmp = argv[i];
				argv[i] = argv[j];
				argv[j] = *tmp;
			}
			j++;
		}
		i++;
	}
	return (argv);
}
