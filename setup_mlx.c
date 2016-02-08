/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_mlx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/18 22:54:49 by dmoureu-          #+#    #+#             */
/*   Updated: 2016/01/22 16:02:27 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	draw_gun(t_env *e)
{
	int	x;
	int	y;

	if (e->hud[0].c >= 3)
		e->hud[0].c = 0;
	x = e->hud[0].camx;
	while (x < e->hud[0].w + e->hud[0].camx)
	{
		y = e->hud[0].camy;
		while (y < e->hud[0].h + e->hud[0].camy)
		{
			draw_dot(e, x + 50, y, getcolor(e->spr[3],
				x - e->hud[0].camx + e->hud[0].c * e->hud[0].w,
				y - e->hud[0].camy, 0));
			y++;
		}
		x++;
	}
	if (e->hud[0].c > 0)
		e->hud[0].c++;
}

int		get_loop_hook(t_env *e)
{
	render(e);
	usleep(5000);
	return (0);
}

void	setup_mlx(t_player *player, t_map *map)
{
	t_env	e;

	e.map = map;
	e.player = player;
	e.mlx = mlx_init();
	e.win = mlx_new_window(e.mlx, WIDTH, HEIGHT, "Wolf3d");
	texture_load(&e);
	load_sprites(&e);
	initkeyboard(&e);
	e.bpp = 0;
	e.size_line = 0;
	e.endian = 0;
	mlx_hook(e.win, 2, 1, key_press_hook, &e);
	mlx_hook(e.win, 3, 1, key_release_hook, &e);
	mlx_expose_hook(e.win, expose_hook, &e);
	mlx_loop_hook(e.mlx, &get_loop_hook, &e);
	mlx_loop(e.mlx);
}

void	render(t_env *e)
{
	key_up_down(e);
	key_left_right(e);
	e->img = mlx_new_image(e->mlx, WIDTH, HEIGHT);
	e->imgpx = mlx_get_data_addr(e->img,
	&(e->bpp), &(e->size_line), &(e->endian));
	raycast(e);
	draw_gun(e);
	mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);
	mlx_destroy_image(e->mlx, e->img);
}
