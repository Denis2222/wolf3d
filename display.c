/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/21 16:03:36 by dmoureu-          #+#    #+#             */
/*   Updated: 2016/01/21 16:04:11 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	draw_ray_wall(t_env *e, t_raycast *rc, t_ray *ray)
{
	int	d;
	int	wall;

	wall = e->map->wall[(int)rc->mapy][(int)rc->mapx];
	while (ray->y < ray->drawend)
	{
		d = ray->y * 256 - HEIGHT * 128 + ray->lineheight * 128;
		ray->texy = ((d * 64) / ray->lineheight) / 256;
		draw_dot(e, ray->x, ray->y, getcolor(e->wall[wall + 1],
					ray->texx, ray->texy, rc->perpwalldist));
		ray->y++;
	}
}

void	draw_ray_floor_size(t_raycast *rc, t_ray *ray)
{
	if (rc->side == 0 && rc->raydirx > 0)
	{
		ray->floorxwall = rc->mapx;
		ray->floorywall = rc->mapy + ray->wallx;
	}
	else if (rc->side == 0 && rc->raydirx < 0)
	{
		ray->floorxwall = rc->mapx + 1.0;
		ray->floorywall = rc->mapy + ray->wallx;
	}
	else if (rc->side == 1 && rc->raydiry > 0)
	{
		ray->floorxwall = rc->mapx + ray->wallx;
		ray->floorywall = rc->mapy;
	}
	else
	{
		ray->floorxwall = rc->mapx + ray->wallx;
		ray->floorywall = rc->mapy + 1.0;
	}
	ray->distwall = rc->perpwalldist;
	ray->distplayer = 0.0;
}

void	draw_ray_floor(t_env *e, t_raycast *rc, t_ray *ray)
{
	draw_ray_floor_size(rc, ray);
	while (ray->y < HEIGHT)
	{
		ray->currentdist = HEIGHT / (2.0 * ray->y - HEIGHT);
		ray->weight = (ray->currentdist - ray->distplayer)
			/ (ray->distwall - ray->distplayer);
		ray->currentfloorx = ray->weight * ray->floorxwall
			+ (1.0 - ray->weight) * e->player->pos->x;
		ray->currentfloory = ray->weight * ray->floorywall
			+ (1.0 - ray->weight) * e->player->pos->y;
		ray->floortexx = (int)(ray->currentfloorx * 64) % 64;
		ray->floortexy = (int)(ray->currentfloory * 64) % 64;
		draw_dot(e, ray->x, ray->y,
				getcolor(e->wall[0], ray->floortexx, ray->floortexy, 0));
		draw_dot(e, ray->x, HEIGHT - ray->y,
				getcolor(e->wall[1], ray->floortexx, ray->floortexy, 0));
		ray->y++;
	}
}
