/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_mlx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/18 22:54:49 by dmoureu-          #+#    #+#             */
/*   Updated: 2016/01/19 16:18:15 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	render(t_env *e)
{
	e->img = mlx_new_image(e->mlx, WIDTH, HEIGHT);
	e->imgpx = mlx_get_data_addr(e->img, &(e->bpp), &(e->size_line), &(e->endian));
	raycast(e->map, e);
	mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);
	mlx_destroy_image(e->mlx, e->img);
}

int	expose_hook(t_env *e)
{
	render(e);
	return (0);
}

int	key_hook(int keycode, t_env *e)
{
	double	movespeed;
	double	rotspeed;

	rotspeed = 0.1;
	movespeed = 0.1;
	if (keycode == KEY_UP)
	{
		if (e->map->wall[(int)(e->player->pos->x + e->player->dir->x * movespeed)][(int)e->player->pos->y] == 0)
			e->player->pos->x += e->player->dir->x * movespeed;
		if (e->map->wall[(int)e->player->pos->x][(int)(e->player->pos->y + e->player->dir->y * movespeed)] == 0)
			e->player->pos->y += e->player->dir->y * movespeed;
	}
	if (keycode == KEY_DOWN)
	{
		if (e->map->wall[(int)(e->player->pos->x - e->player->dir->x * movespeed)][(int)e->player->pos->y] == 0)
			e->player->pos->x -= e->player->dir->x * movespeed;
		if (e->map->wall[(int)e->player->pos->x][(int)(e->player->pos->y - e->player->dir->y * movespeed)] == 0)
			e->player->pos->y -= e->player->dir->y * movespeed;
	}

    if (keycode == KEY_LEFT)
    {
      double oldDirX = e->player->dir->x;
      e->player->dir->x = e->player->dir->x * cos(-rotspeed) - e->player->dir->y * sin(-rotspeed);
      e->player->dir->y = oldDirX * sin(-rotspeed) + e->player->dir->y * cos(-rotspeed);
      double oldPlaneX = e->player->plane->x;
      e->player->plane->x = e->player->plane->x * cos(-rotspeed) - e->player->plane->y * sin(-rotspeed);
      e->player->plane->y = oldPlaneX * sin(-rotspeed) + e->player->plane->y * cos(-rotspeed);
    }
    if (keycode == KEY_RIGHT)
    {
      double oldDirX = e->player->dir->x;
      e->player->dir->x = e->player->dir->x * cos(rotspeed) - e->player->dir->y * sin(rotspeed);
      e->player->dir->y = oldDirX * sin(rotspeed) + e->player->dir->y * cos(rotspeed);
      double oldPlaneX = e->player->plane->x;
      e->player->plane->x = e->player->plane->x * cos(rotspeed) - e->player->plane->y * sin(rotspeed);
      e->player->plane->y = oldPlaneX * sin(rotspeed) + e->player->plane->y * cos(rotspeed);
    }

	render(e);
	return (0);
}

void	setup_mlx(t_player *player, t_map *map)
{
	t_env e;

	e.map = map;
	e.player = player;
	
	e.mlx = mlx_init();
	e.win = mlx_new_window(e.mlx, WIDTH, HEIGHT, "Wolf3d");
	e.bpp = 0;
	e.size_line = 0;
	e.endian = 0;
	mlx_hook(e.win, 2, 1, key_hook, &e);
	mlx_expose_hook(e.win, expose_hook, &e);
	mlx_loop(e.mlx);
}
