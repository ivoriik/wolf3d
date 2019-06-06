/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbespalk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 18:43:12 by vbespalk          #+#    #+#             */
/*   Updated: 2018/10/10 18:43:14 by vbespalk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		check_map(t_map *m)
{
	unsigned int	i[2];
	int				is_space;

	i[0] = 0;
	is_space = 0;
	while (i[0] < m->wid && !(i[1] = 0))
	{
		while (i[1] < m->hei)
		{
			if ((i[0] == 0 || i[0] == m->wid - 1 || i[1] == 0 ||
				i[1] == m->hei - 1) \
				&& !(m->grid[i[1]][i[0]]))
				return (clear_grid(&m->grid, m->hei, "Invalid or empty map\n"));
			if (!is_space && m->grid[i[1]][i[0]] == 0)
			{
				m->pos[0] = i[1];
				m->pos[1] = i[0];
				is_space = 1;
			}
			++i[1];
		}
		++i[0];
	}
	if (!is_space)
		return (clear_grid(&m->grid, m->hei, "Invalid or empty map\n"));
	return (0);
}

int		parse_str(const char *s, unsigned int *grid, unsigned int size)
{
	char			**ar;
	int				j;
	unsigned int	num;
	unsigned int	tex_nb;

	j = -1;
	ar = ft_strsplit(s, ' ');
	tex_nb = 0;
	while (ar[++j])
	{
		if (!ft_isnum(ar[j]) || ((num = (unsigned int)
				ft_atoi(ar[j])) > 3))
		{
			clear_mem(&ar, size);
			return (-1);
		}
		if (num > tex_nb)
			tex_nb = num;
		grid[j] = num;
	}
	clear_mem(&ar, size);
	return (0);
}

int		parse_lst(t_map *map, unsigned int ***grid, t_list *lst)
{
	int	i;

	if (!(*grid = (unsigned int **)malloc(sizeof(unsigned int *) * map->hei)))
		ft_perror(NULL);
	i = -1;
	while (lst)
	{
		if (!((*grid)[++i] = (unsigned int *)malloc(sizeof(unsigned int) * \
			map->wid)))
			ft_perror(NULL);
		if (parse_str((const char *)lst->content, (*grid)[i], map->wid + 1))
			return (ft_perror("Invalid or empty map\n"));
		lst = lst->next;
	}
	return (0);
}

int		read_to_lst(int fd, t_list **lst, t_map *map)
{
	int		res;
	size_t	len;
	char	*str;
	t_list	*new;

	len = 0;
	while ((res = get_next_line(fd, &str)) > 0)
	{
		if (!map->wid)
		{
			len = ft_strlen(str);
			map->wid = ft_nb_words(str, ' ');
		}
		if (map->wid != ft_nb_words(str, ' ') || len != ft_strlen(str) || !len)
		{
			ft_memdel((void **)&str);
			return (ft_perror("Invalid or empty map\n"));
		}
		if (!(new = ft_lstnew((void *)str, ft_strlen(str))))
			ft_perror(NULL);
		ft_lstaddend(lst, new);
		++map->hei;
		ft_memdel((void **)&str);
	}
	return (res);
}

int		init_map(int fd, t_map *map)
{
	t_list	*lst;

	lst = NULL;
	if (read_to_lst(fd, &lst, map))
	{
		ft_lstdel(&lst, del_content);
		return (-1);
	}
	if (parse_lst(map, &(map->grid), lst) || check_map(map))
	{
		ft_lstdel(&lst, del_content);
		return (-1);
	}
	ft_lstdel(&lst, del_content);
	map->pp_cnt = SCR_HEI / 2;
	map->vw_ang = VW_ANG;
	map->pl_pos = (t_vector){map->pos[1] * S_CELL + OFSET, \
		map->pos[0] * S_CELL + OFSET};
	map->m_koef = (t_vector){MAP_HEI / (float)map->hei, MAP_WID \
		/ (float)map->wid};
	map->pl_mpos[0][0] = map->pl_pos[0] / (float)S_CELL * map->m_koef[1];
	map->pl_mpos[0][1] = map->pl_pos[1] / (float)S_CELL * map->m_koef[0];
	close(fd);
	return (0);
}
