/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/18 17:22:37 by dmoureu-          #+#    #+#             */
/*   Updated: 2016/01/19 00:32:48 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	draw_line(double perpwalldist, int x, t_env *e)
{
	int	lineheight;
	int	drawstart;
	int	drawend;
	int	s;

	s = 0;
	lineheight = abs((int)(HEIGHT / perpwalldist));
	drawstart = -lineheight / 2 + HEIGHT / 2;
	if (drawstart < 0)
		drawstart = 0;
	drawend = lineheight / 2 + HEIGHT / 2;
	if (drawend >= HEIGHT)
		drawend = HEIGHT - 1;

	while (s < HEIGHT)
	{
		if (s < drawstart)
			draw_dot(e, x, s, 150 + 150 * 256 + 150 * 256 * 256);
		else if (s >= drawstart && s <= drawend)
			draw_dot(e, x, s, 255);
		else
			draw_dot(e, x, s, 50 + 50 * 256 + 50 * 256 * 256);
		s++;
	}
}

void	raycast(t_player *player, t_map *map, t_env *e)
{
	int		x;
	double	camerax;
	t_coord	raypos;
	t_coord	raydir;
	t_coord	cmap;
	t_coord	sidedist;
	t_coord	deltadist;
	double	perpwalldist;
	t_coord	step;
	int		hit;
	int		side;

	x = 0;
	while (x < WIDTH)
	{
		camerax = 2 * x / (double)(WIDTH) - 1;
		raypos.x = player->pos->x;
		raypos.y = player->pos->y;
		raydir.x = player->dir->x + player->plane->x * camerax;
		raydir.y = player->dir->y + player->plane->y * camerax;

		cmap.x = (int)raypos.x;
		cmap.y = (int)raypos.y;

		deltadist.x = sqrt(1 + (raydir.y * raydir.y) / (raydir.x * raydir.x));
		deltadist.y = sqrt(1 + (raydir.x * raydir.x) / (raydir.y * raydir.y));

		hit = 0;
		if (raydir.x < 0)
		{
			step.x = -1;
			sidedist.x = (raypos.x - cmap.x) * deltadist.x;
		}
		else
		{
			step.x = 1;
			sidedist.x = (cmap.x + 1.0 - raypos.x) * deltadist.x;
		}
		if (raydir.y < 0)
		{
			step.y = -1;
			sidedist.y = (raypos.y - cmap.y) * deltadist.y;
		}
		else
		{
			step.y = 1;
			sidedist.y = (cmap.y + 1.0 - raypos.y) * deltadist.y;
		}

		while (hit == 0)
		{
			if (sidedist.x < sidedist.y)
			{
				sidedist.x += deltadist.x;
				cmap.x += step.x;
				side = 0;
			}
			else
			{
				sidedist.y += deltadist.y;
				cmap.y += step.y;
				side = 1;
			}
			if (map->wall[(int)cmap.x][(int)cmap.y] > 0)
				hit = 1;
		}

		if (side == 0)
			perpwalldist = fabs((cmap.x - raypos.x + (1 - step.x) / 2) / raydir.x);
		else
			perpwalldist = fabs((cmap.y - raypos.y + (1 - step.y) / 2) / raydir.y);

		//printf("dist: %f", perpwalldist);
		draw_line(perpwalldist, x, e);


		x++;
	}
}
