/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbespalk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/17 18:45:11 by vbespalk          #+#    #+#             */
/*   Updated: 2018/01/17 18:45:16 by vbespalk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_lstdelone(t_list **alst, void (*del)(void *, size_t))
{
	if ((*alst) == NULL || alst == NULL)
		return ;
	del((*alst)->content, (*alst)->content_size);
	ft_memdel((void **)(alst));
}
