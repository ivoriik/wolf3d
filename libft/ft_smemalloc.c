/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_smemalloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbespalk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 17:15:37 by vbespalk          #+#    #+#             */
/*   Updated: 2018/01/23 17:42:47 by vbespalk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <errno.h>
#include <stdio.h>

void	*ft_smemalloc(size_t size, char *ft_name)
{
	void	*mem;

	if (!(mem = ft_memalloc(size)))
	{
		ft_putstr("Error: memory allocation fails at ");
		ft_putendl(ft_name);
		exit(EXIT_FAILURE);
	}
	return (mem);
}
