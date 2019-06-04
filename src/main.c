/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbespalk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 17:31:41 by vbespalk          #+#    #+#             */
/*   Updated: 2018/10/10 17:32:12 by vbespalk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

//int		init_mlx(t_mlx *mlx, t_map *map)
//{
//	ft_bzero(mlx, sizeof(t_mlx));
//	if (!(mlx->mlx_ptr = mlx_init()))
//		return (ft_perror("Connection to the X server failed\n"));
//	if (!(mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, SCR_WID, \
//		SCR_HEI, "Wolf3d")))
//		return (ft_perror("Impossible to create new window\n"));
//	if (!(mlx->img_ptr = mlx_new_image(mlx->mlx_ptr, SCR_WID, SCR_HEI)))
//		return (ft_perror("Impossible to set up image\n"));
//	if (!(mlx->map_ptr = mlx_new_image(mlx->mlx_ptr, MAP_WID, MAP_HEI)))
//		return (ft_perror("Impossible to set up image\n"));
//	mlx->img_add = mlx_get_data_addr(mlx->img_ptr, \
//		&mlx->bpp, &mlx->s_line, &mlx->endian);
//	mlx->map_add = mlx_get_data_addr(mlx->map_ptr, \
//		&mlx->bpp, &mlx->maps_line, &mlx->endian);
//	ft_bzero(mlx->img_add, SCR_HEI * SCR_WID);
//	ft_bzero(mlx->map_add, MAP_HEI * MAP_WID);
//	mlx->map = map;
//	if (!(load_textures(mlx)))
//		return (ft_perror("Impossible to load textures\n"));
//	return (0);
//}

static uint32_t	sdl_draw_screen(t_mlx *e, t_sdl *sdl, uint32_t btn_id,
								   uint32_t status)
{

	skybox(e, (e->tex)[12]);
//	mlx->map->pl_mpos[0][0] = mlx->map->pl_pos[0] / (float)S_CELL * \
//		mlx->map->m_koef[1];
//	mlx->map->pl_mpos[0][1] = mlx->map->pl_pos[1] / (float)S_CELL * \
//		mlx->map->m_koef[0];
	mult_threads(e);
//	draw_map(e, e->map);
	e->init = 1;
	printf("REDRAW\n");
	SDL_UpdateTexture(
			sdl->screen, NULL, sdl->pixels, sdl->scr_wid * sizeof(Uint32));
	SDL_RenderClear(sdl->renderer);
	SDL_RenderCopy(sdl->renderer, sdl->screen, NULL, NULL);
	SDL_RenderPresent(sdl->renderer);
	return (0);
}

static void		main_loop(t_mlx *e)
{
	t_sdl		*sdl;
	uint32_t	btn_id;
	int32_t		status;
	int32_t		btn_status;
	Uint32		start_time;
	Uint32		current_fps = 0;
	float		average_fps;



	sdl = e->sdl;
	sdl->event_loop = 1;
	start_time = SDL_GetTicks();
	++current_fps;
	sdl_draw_screen(e, e->sdl, 0, 1);
	while (sdl->event_loop)
	{
		event_handler(e, &btn_id);
//		average_fps = (float)current_fps / ((SDL_GetTicks() - start_time) / 1000.f);
//		start_time = SDL_GetTicks();
//		if (current_fps < 1000)
//		printf("fps %f\n", average_fps);
		if (move(e, e->map))
		{
			sdl_draw_screen(e, e->sdl, 0, 1);
		}
		++current_fps;
//		if (btn_status)
//		{
//			sdl_draw_screen(e, e->sdl, 0, 1);
//			btn_status = 0;
//		}
	}
}

int		main(int argc, char **argv)
{
	t_mlx	mlx;
	t_sdl	sdl;
	t_map	map;
	int		fd;

	if (argc != 2)
		ft_usage("wolf3d map\n");
	if ((fd = open(argv[1], O_RDONLY)) == -1)
		ft_error(NULL);
	ft_bzero(&map, sizeof(t_map));
	if (init_map(fd, &map))
		exit(-1);
	if (sdl_init(&sdl))
		exit(-1);
	ft_bzero(&mlx, sizeof(t_mlx));
	mlx.sdl = &sdl;
	mlx.map = &map;
	if (!(load_textures(&mlx)))
		return (ft_perror("Impossible to load textures\n"));
	main_loop(&mlx);
//	mlx_hook(mlx.win_ptr, KEYEXIT, KEYEXITMASK, exit_x, (void *)&mlx);
//	mlx_hook(mlx.win_ptr, KEYPRESS, KEYPRESSMASK, key_press, (void *)&mlx);
//	mlx_hook(mlx.win_ptr, KEYRELEASE, KEYRELEASEMASK, key_release, \
//		(void *)&mlx);
//	mlx_hook(mlx.win_ptr, MOUSE, MOUSEMASK, mouse_hook, (void *)&mlx);
//	mlx_loop_hook(mlx.mlx_ptr, put_to_window, &mlx);
//	mlx_loop(mlx.mlx_ptr);
}
