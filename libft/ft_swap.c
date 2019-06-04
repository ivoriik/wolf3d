/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbespalk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 12:32:34 by vbespalk          #+#    #+#             */
/*   Updated: 2017/09/25 13:32:40 by vbespalk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_swap(void *nb1, void *nb2, size_t size)
{
	unsigned char	swap_tmp[size];

	ft_memcpy(&(*swap_tmp), (nb1), size);
	ft_memcpy((nb1), (nb2), size);
	ft_memcpy((nb2), &(*swap_tmp), size);
}
