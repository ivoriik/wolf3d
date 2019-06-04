/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbespalk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 14:16:33 by vbespalk          #+#    #+#             */
/*   Updated: 2018/10/29 14:16:35 by vbespalk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		del_content(void *content, size_t size)
{
	if (size && content)
		ft_memdel(&content);
}

void		clear_mem(char ***mem, int nb)
{
	while (--nb >= 0)
		ft_memdel((void **)&(*mem)[nb]);
	ft_memdel((void **)(mem));
}

void		split_del(char ***ptr, void (*f)(void **))
{
	char **s;

	s = *ptr;
	if (s == NULL || f == NULL)
		return ;
	while (*s)
		f((void **)s++);
	f((void **)ptr);
}

int			clear_grid(unsigned int ***mem, int nb, char *err)
{
	while (--nb >= 0 && (*mem)[nb])
		ft_memdel((void **)&(*mem)[nb]);
	ft_memdel((void **)(mem));
	if (err != NULL)
		return (ft_perror(err));
	return (0);
}
