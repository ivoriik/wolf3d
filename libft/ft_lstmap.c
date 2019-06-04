/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbespalk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 17:38:52 by vbespalk          #+#    #+#             */
/*   Updated: 2018/02/05 17:38:54 by vbespalk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(f)(t_list *elem))
{
	t_list *new_lst;
	t_list *tmp;

	if (!lst || !f)
		return (NULL);
	if (!(new_lst = f(lst)))
		return (NULL);
	tmp = new_lst;
	while (lst->next != NULL)
	{
		lst = lst->next;
		if (!(tmp->next = f(lst)))
			return (NULL);
	}
	return (new_lst);
}
