/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbespalk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/17 18:44:15 by vbespalk          #+#    #+#             */
/*   Updated: 2018/01/17 18:44:41 by vbespalk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list *lst;

	lst = NULL;
	if (!(lst = (t_list *)malloc(sizeof(t_list))))
		return (NULL);
	if (!content)
	{
		lst->content = NULL;
		lst->content_size = 0;
	}
	else
	{
		if (!(lst->content = malloc(content_size + 1)))
		{
			free(lst);
			return (NULL);
		}
		lst->content = ft_memcpy(lst->content, content, content_size + 1);
		lst->content_size = content_size;
	}
	lst->next = NULL;
	return (lst);
}
