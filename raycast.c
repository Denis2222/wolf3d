/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/18 17:22:37 by dmoureu-          #+#    #+#             */
/*   Updated: 2016/01/18 21:14:16 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	draw_line(double perpwalldist)
{
	int	lineheight;
	int	drawstart;
	int	drawend;

	lineheight = abs((int)(HEIGHT / perpwalldist));
	drawstart = -lineheight / 2 + HEIGHT / 2;
	if (drawstart < 0)
		drawstart = 0;
	drawend = lineheight / 2 + HEIGHT / 2;
	if (drawend >= HEIGHT)
		drawend = HEIGHT - 1;
}

void	raycast(t_player *player, t_map *map)
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

		printf("[%f:%f]", raydir.x, raydir.y);

		cmap.x = (int)raypos.x;
		cmap.y = (int)raypos.y;

		deltadist.x = sqrt(1 + (raydir.y * raydir.y) / (raydir.x * raydir.x));
		deltadist.y = sqrt(1 + (raydir.x * raydir.x) / (raydir.y * raydir.y));

//		printf("deltadist[%f:%f]", deltadist.x, deltadist.y);

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
//		printf("ray %d sidedist[%f:%f]\n", x, sidedist.x, sidedist.y);

		if (side == 0)
			perpwalldist = fabs((cmap.x - raypos.x + (1 - step.x) / 2) / raydir.x);
		else
			perpwalldist = fabs((cmap.y - raypos.y + (1 - step.y) / 2) / raydir.y);

//		printf("dist: %f", perpwalldist);

		x++;
	}
}
