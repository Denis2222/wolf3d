/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/18 17:22:37 by dmoureu-          #+#    #+#             */
/*   Updated: 2016/01/19 22:22:40 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ray_delimiter(t_raycast *rc, t_ray *ray)
{
	ray->lineheight = abs((int)(HEIGHT / rc->perpwalldist));
	ray->drawstart = -ray->lineheight / 2 + HEIGHT / 2;
	if (ray->drawstart < 0)
		ray->drawstart = 0;
	ray->drawend = ray->lineheight / 2 + HEIGHT / 2;
	if (ray->drawend >= HEIGHT)
		ray->drawend = HEIGHT - 1;
	if (rc->side == 1)
		ray->wallx = rc->rayposx + ((rc->mapy - rc->rayposy +
		(1 - rc->stepy) / 2) / rc->raydiry) * rc->raydirx;
	else
		ray->wallx = rc->rayposy + ((rc->mapx - rc->rayposx +
		(1 - rc->stepx) / 2) / rc->raydirx) * rc->raydiry;
	ray->wallx -= floor(ray->wallx);
	ray->texx = (int)(ray->wallx * (double)64);
	ray->texx = 64 - ray->texx - 1;
}

void	draw_ray(t_raycast *rc, int x, t_env *e)
{
	t_ray	ray;
	int	d;

	ray_delimiter(rc, &ray);
	ray.y = 0;
	while (ray.y < HEIGHT)
	{
		if (ray.y < ray.drawstart)
			draw_dot(e, x, ray.y, 0x0000FF);
		else if (ray.y >= ray.drawstart && ray.y < ray.drawend)
		{
			d = ray.y * 256 - HEIGHT * 128 + ray.lineheight * 128;
			ray.texy = ((d * 64) / ray.lineheight) / 256;
			draw_dot(e, x, ray.y, getcolor(e->wall, ray.texx, ray.texy, rc->perpwalldist));
			/* affichage par face de cube
			if (rc->raydiry > 0 && rc->side)
				draw_dot(e, x, s, 0xFF0000);
			if (rc->raydiry < 0 && rc->side)
				draw_dot(e, x, s, 0x00FF00);
			if (rc->raydirx > 0 && rc->side == 0)
				draw_dot(e, x, s, 0x0000FF);
			if (rc->raydirx < 0 && rc->side == 0)
				draw_dot(e, x, s, 0xAA00BB);
			*/
		}
		else
			draw_dot(e, x, ray.y, 0x000077); 
		ray.y++;
	}
}

void	rayinit(t_env *e, t_raycast *rc, int x)
{
	rc->camerax = 2 * x / (double)(WIDTH) - 1;
	rc->rayposx = e->player->pos->x;
	rc->rayposy = e->player->pos->y;
	rc->raydirx = e->player->dir->x + e->player->plane->x * rc->camerax;
	rc->raydiry = e->player->dir->y + e->player->plane->y * rc->camerax;
	rc->mapx = (int)rc->rayposx;
	rc->mapy = (int)rc->rayposy;
	rc->deltadistx = sqrt(1 + (rc->raydiry * rc->raydiry) / (rc->raydirx * rc->raydirx));
	rc->deltadisty = sqrt(1 + (rc->raydirx * rc->raydirx) / (rc->raydiry * rc->raydiry));
}

void	rayfindside(t_raycast *rc)
{
	if (rc->raydirx < 0)
	{
		rc->stepx = -1;
		rc->sidedistx = (rc->rayposx - rc->mapx) * rc->deltadistx;
	}
	else
	{
		rc->stepx = 1;
		rc->sidedistx = (rc->mapx + 1.0 - rc->rayposx) * rc->deltadistx;
	}
	if (rc->raydiry < 0)
	{
		rc->stepy = -1;
		rc->sidedisty = (rc->rayposy - rc->mapy) * rc->deltadisty;
	}
	else
	{
		rc->stepy = 1;
		rc->sidedisty = (rc->mapy + 1.0 - rc->rayposy) * rc->deltadisty;
	}
}

void	raydda(t_raycast *rc, t_env *e)
{
	while (rc->hit == 0)
	{
		if (rc->sidedistx < rc->sidedisty)
		{
			rc->sidedistx += rc->deltadistx;
			rc->mapx += rc->stepx;
			rc->side = 0;
		}
		else
		{
			rc->sidedisty += rc->deltadisty;
			rc->mapy += rc->stepy;
			rc->side = 1;
		}
		if (e->map->wall[(int)rc->mapy][(int)rc->mapx] > 0)
			rc->hit = 1;
	}
}

void	raydist(t_raycast *rc)
{
	if (rc->side == 0)
		rc->perpwalldist = fabs((rc->mapx - rc->rayposx + (1 - rc->stepx) / 2) / rc->raydirx);
	else
		rc->perpwalldist = fabs((rc->mapy - rc->rayposy + (1 - rc->stepy) / 2) / rc->raydiry);
}

void	raycast(t_env *e)
{
	t_raycast	rc;
	int			x;

	x = 0;
	while (x < WIDTH)
	{
		rayinit(e, &rc, x);
		rc.hit = 0;
		rayfindside(&rc);
		raydda(&rc, e);
		raydist(&rc);
		draw_ray(&rc, x, e);
		x++;
	}
}
