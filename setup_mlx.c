/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_mlx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/18 22:54:49 by dmoureu-          #+#    #+#             */
/*   Updated: 2016/01/21 00:55:13 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"


int		expose_hook(t_env *e)
{
	render(e);
	return (0);
}

void	key_up_down(t_env *e)
{
	if (e->key.up)
	{
		if (e->map->wall[(int)(e->player->pos->y + e->player->dir->y
			* MOVESPEED)][(int)e->player->pos->x] == 0)
			e->player->pos->y += e->player->dir->y * MOVESPEED;
		if (e->map->wall[(int)e->player->pos->y][(int)(e->player->pos->x
			+ e->player->dir->x * MOVESPEED)] == 0)
			e->player->pos->x += e->player->dir->x * MOVESPEED;
	}
	if (e->key.down)
	{
		if (e->map->wall[(int)(e->player->pos->y - e->player->dir->y
			* MOVESPEED)][(int)e->player->pos->x] == 0)
			e->player->pos->y -= e->player->dir->y * MOVESPEED;
		if (e->map->wall[(int)e->player->pos->y][(int)(e->player->pos->x
			- e->player->dir->x * MOVESPEED)] == 0)
			e->player->pos->x -= e->player->dir->x * MOVESPEED;
	}
}

void	key_left_right(t_env *e)
{
	double olddirx;
	double oldplanex;

	olddirx = e->player->dir->x;
	oldplanex = e->player->plane->x;
	if (e->key.left)
	{
		e->player->dir->x = e->player->dir->x * C_R - e->player->dir->y * S_R;
		e->player->dir->y = olddirx * S_R + e->player->dir->y * C_R;
		e->player->plane->x = e->player->plane->x
			* C_R - e->player->plane->y * S_R;
		e->player->plane->y = oldplanex * S_R + e->player->plane->y * C_R;
	}
	if (e->key.right)
	{
		e->player->dir->x = e->player->dir->x * CR - e->player->dir->y * SR;
		e->player->dir->y = olddirx * SR + e->player->dir->y * CR;
		e->player->plane->x = e->player->plane->x
			* CR - e->player->plane->y * SR;
		e->player->plane->y = oldplanex * SR + e->player->plane->y * CR;
	}
}

int	get_loop(t_env *e)
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
	mlx_loop_hook(e.mlx, &get_loop, &e);
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
	mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);
	mlx_destroy_image(e->mlx, e->img);
}

int		key_press_hook(int keycode, t_env *e)
{
	key_press(&e->key, keycode);
	if (keycode == KEY_ESC)
		exit(EXIT_SUCCESS);
	return (0);
}

int		key_release_hook(int keycode, t_env *e)
{
	key_release(&e->key, keycode);
	return (0);
}

