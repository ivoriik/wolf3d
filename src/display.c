/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbespalk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/02 17:19:29 by vbespalk          #+#    #+#             */
/*   Updated: 2018/08/21 16:11:31 by vbespalk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

//int				put_to_window(t_mlx *mlx)
//{
//	if (move(mlx, mlx->map) || !mlx->init)
//	{
//		ft_bzero(mlx->img_add, (size_t)(SCR_HEI * mlx->s_line));
//		ft_bzero(mlx->map_add, (size_t)(MAP_HEI * mlx->maps_line));
//		mlx_clear_window(mlx->mlx_ptr, mlx->win_ptr);
//		skybox(mlx, (mlx->tex)[12]);
//		mlx->map->pl_mpos[0][0] = mlx->map->pl_pos[0] / (float)S_CELL * \
//		mlx->map->m_koef[1];
//		mlx->map->pl_mpos[0][1] = mlx->map->pl_pos[1] / (float)S_CELL * \
//		mlx->map->m_koef[0];
//		mult_threads(mlx);
//		draw_map(mlx, mlx->map);
//		mlx->init = 1;
//	}
//	is_sound(mlx);
//	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img_ptr, 0, 0);
//	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->map_ptr, 10, 10);
//	return (0);
//}

void			img_pixel_put(t_sdl *sdl, int x, int y, unsigned int color)
{
	if (!(x >= 0 && x < sdl->scr_wid && y >= 0 && y < sdl->scr_hei))
		return ;
	sdl->pixels[y * sdl->pitch + x] = color;
}


//void			img_pixel_put(t_mlx *mlx, t_vector p, unsigned int col, int fl)
//{
//	char	*data;
//	int		s_line;
//
//	if (!fl && !(p[0] >= 0 && p[0] < MAP_WID && p[1] >= 0 && p[1] < MAP_HEI))
//		return ;
//	if (!(p[0] >= 0 && p[0] < SCR_WID && p[1] >= 0 && p[1] < SCR_HEI))
//		return ;
//	if (fl)
//	{
//		data = mlx->img_add;
//		s_line = mlx->s_line;
//	}
//	else
//	{
//		data = mlx->map_add;
//		s_line = mlx->maps_line;
//	}
//	data += (int)p[1] * s_line + mlx->bpp / 8 * (int)p[0];
//	ft_memcpy(data, &col, sizeof(col));
//}

unsigned int	img_tex_col(t_mlx *mlx, SDL_Surface *tex, int x_tex, int y_tex)
{
	Uint32			*tex_data;
	unsigned int	color;

	if (y_tex < 0)
		y_tex = abs(y_tex);
	if (y_tex >= 64)
		y_tex %= 64;
	if (x_tex >= 64)
		y_tex %= 64;
	tex_data = (Uint32 *)tex->pixels + y_tex *
			(tex->pitch / sizeof(Uint32)) + x_tex;
	ft_memcpy(&color, tex_data, sizeof(Uint32));
	return (color);
}

unsigned int	rgb_to_hex(unsigned int red, unsigned int green, \
	unsigned int blue)
{
	unsigned int color;

	color = red;
	color = (color << 8) + green;
	color = (color << 8) + blue;
	return (color);
}

t_rgb			hex_to_rgb(unsigned int hex)
{
	t_rgb color;

	color.r = ((hex >> 16) & 0xFF);
	color.g = ((hex >> 8) & 0xFF);
	color.b = ((hex) & 0xFF);
	return (color);
}
