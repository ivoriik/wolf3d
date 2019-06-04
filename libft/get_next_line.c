/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbespalk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 12:57:39 by vbespalk          #+#    #+#             */
/*   Updated: 2018/04/23 12:57:43 by vbespalk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

void	ft_lstdelnod(t_list **alst)
{
	t_list *tmp;

	if ((*alst) == NULL)
		return ;
	if ((*alst)->next)
	{
		tmp = *alst;
		*alst = (*alst)->next;
		free(tmp->content);
		free(tmp);
	}
	else
	{
		if ((*alst)->content)
			free((*alst)->content);
		free(*alst);
		*alst = NULL;
	}
}

t_fd	*get_node(t_fd **list, unsigned int fd)
{
	t_fd *prev;
	t_fd *tmp;

	tmp = *list;
	prev = NULL;
	while (tmp)
	{
		if (tmp->fd == fd)
			return (tmp);
		prev = tmp;
		tmp = tmp->next;
	}
	if (!(tmp = (t_fd *)malloc(sizeof(t_fd))))
		return (NULL);
	tmp->fd = fd;
	tmp->no_read = 0;
	tmp->flag = 0;
	tmp->buf = ft_lstnew(NULL, 0);
	tmp->next = NULL;
	if (prev)
		prev->next = tmp;
	if (!(*list))
		*list = tmp;
	return (tmp);
}

int		g_ln(char **ln, size_t *r_off, t_list **beg, void *end)
{
	size_t	length;
	t_list	*tmp;
	size_t	l_off;

	length = 0;
	l_off = *r_off;
	l_off > (*beg)->content_size ? l_off = 0 : l_off;
	if (!end || !(tmp = *beg))
		return (0);
	while (tmp && ((size_t)(end - tmp->content) > tmp->content_size))
	{
		length += (tmp->content_size);
		tmp = tmp->next;
	}
	tmp ? *r_off = (size_t)(end - tmp->content) : 0;
	tmp ? *ln = ft_strnew(length + *r_off - l_off) \
	: ft_strnew(length + BUFF_SIZE - l_off);
	while ((*beg) && (size_t)(end - (*beg)->content) > (*beg)->content_size)
	{
		ft_strncat(*ln, (*beg)->content + l_off, (*beg)->content_size - l_off);
		l_off = 0;
		ft_lstdelnod(beg);
	}
	*beg ? ft_strncat(*ln, (*beg)->content + l_off, (*r_off)++ - l_off) : *ln;
	return (1);
}

int		read_buf(t_fd *s, char **line, char **buffer, long long *red)
{
	t_list	*cur;
	t_list	*new;

	cur = s->buf;
	while ((*red = read(s->fd, *buffer, BUFF_SIZE)) > 0)
	{
		new = ft_lstnew((void *)*buffer, (size_t)*red);
		ft_lstaddend(&cur, new);
		if (g_ln(line, &(s->flag), &(s->buf), \
			ft_memchr(new->content, '\n', new->content_size)))
			return (1);
		cur = new;
	}
	if (*red == 0)
	{
		if (!(*red = cur == s->buf && s->flag >= cur->content_size))
			g_ln(line, &(s->flag), &(s->buf), cur->content + cur->content_size);
		s->no_read = 1;
		ft_lstdelnod(&(s->buf));
		return (*red) ? 0 : 1;
	}
	return (-1);
}

int		get_next_line(const int fd, char **line)
{
	static t_fd		*fd_st;
	t_fd			*cur;
	long long		red;
	char			*buffer;

	if (!(line) || fd < 0 || read(fd, &red, 0) < 0)
	{
		ft_perror(NULL);
		return (-1);
	}
	if (!(cur = get_node(&fd_st, (unsigned int)fd)))
		return (-1);
	if (cur->no_read)
		return (0);
	if (g_ln(line, &(cur->flag), &(cur->buf), ft_memchr(cur->buf->content \
		+ cur->flag, '\n', cur->buf->content_size - cur->flag)))
		return (1);
	if (!(buffer = ft_strnew(BUFF_SIZE)))
		return (-1);
	red = read_buf(cur, line, &buffer, &red);
	if (buffer)
		free(buffer);
	return ((int)red);
}
