/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/18 17:22:37 by dmoureu-          #+#    #+#             */
/*   Updated: 2016/01/21 00:47:54 by dmoureu-         ###   ########.fr       */
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
	ray->y = 0;
}

void	draw_ray_ceil(t_env *e, t_ray *ray)
{
	while (ray->y < ray->drawstart)
		draw_dot(e, ray->x, ray->y++, 0x333333);
}

void	draw_ray_wall(t_env *e, t_raycast *rc, t_ray *ray)
{
	int	d;
	int	wall;

	wall = e->map->wall[(int)rc->mapy][(int)rc->mapx];
	while (ray->y < ray->drawend)
	{
		d = ray->y * 256 - HEIGHT * 128 + ray->lineheight * 128;
		ray->texy = ((d * 64) / ray->lineheight) / 256;
		draw_dot(e, ray->x, ray->y, getcolor(e->wall[wall + 1], ray->texx, ray->texy, rc->perpwalldist));
		ray->y++;
	}
}

void	draw_ray_floor(t_env *e, t_raycast *rc, t_ray *ray)
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
	while (ray->y < HEIGHT)
	{
		ray->currentdist = HEIGHT / (2.0 * ray->y - HEIGHT);
		ray->weight = (ray->currentdist - ray->distplayer) / (ray->distwall - ray->distplayer);
		ray->currentfloorx = ray->weight * ray->floorxwall + (1.0 - ray->weight) * e->player->pos->x;
		ray->currentfloory = ray->weight * ray->floorywall + (1.0 - ray->weight) * e->player->pos->y;
		ray->floortexx = (int)(ray->currentfloorx * 64) % 64;
		ray->floortexy = (int)(ray->currentfloory * 64) % 64;
		draw_dot(e, ray->x, ray->y, getcolor(e->wall[0], ray->floortexx, ray->floortexy, 0));
		draw_dot(e, ray->x, HEIGHT - ray->y, getcolor(e->wall[1], ray->floortexx, ray->floortexy, 0));
		ray->y++;
	}
}

void	draw_sprite(t_env *e, t_raycast *rc)
{
	int	i;
	double	spritex;
	double	spritey;
	double	invdet;
	double	tx;
	double	ty;
	int		spritescreenx;
	int		spriteheight;
	int		drawstarty;
	int		drawendy;
	int		spritewidth;
	int		drawstartx;
	int		drawendx;
	int		stripe;
	int		y;
	int		texx;
	int		d;
	int		texy;

	i = 0;
	while (i < NBSPRITE)
	{
		spritex = e->sprite[i].x - e->player->pos->x;
		spritey = e->sprite[i].y - e->player->pos->y;
		invdet = 1.0 / (e->player->plane->x * e->player->dir->y
			- e->player->dir->x * e->player->plane->y);
		tx = invdet * (e->player->dir->y * spritex - e->player->dir->x * spritey);
		ty = invdet * (-e->player->plane->y * spritex + e->player->plane->x * spritey);
		spritescreenx = (int)((WIDTH / 2) * (1 + tx / ty));
		spriteheight = abs((int)(HEIGHT / ty));
		drawstarty = -spriteheight / 2 + HEIGHT / 2;
		if (drawstarty < 0)
			drawstarty = 0;
		drawendy = spriteheight / 2 + HEIGHT / 2;
		if (drawendy >= HEIGHT)
			drawendy = HEIGHT - 1;
		spritewidth = abs((int)(HEIGHT / ty));
		drawstartx = -spritewidth / 2 + spritescreenx;
		if (drawstartx < 0)
			drawstartx = 0;
		drawendx = spritewidth / 2 + spritescreenx;
		if (drawendx >= WIDTH)
			drawendx = WIDTH - 1;
		stripe = drawstartx;
		while (stripe < drawendx)
		{
			texx = (int)(256 * (stripe - (-spritewidth / 2 + spritescreenx)) * 64 / spritewidth) / 256;
			if (ty > 0 && stripe > 0 && stripe < WIDTH && ty < rc->zbuffer[stripe])
			{
				y = drawstarty;
				while ( y < drawendy)
				{
					d = (y) * 256 - HEIGHT * 128 + spriteheight * 128;
					texy = ((d * 64) / spriteheight) / 256;
					draw_dot(e, stripe, y, getcolor(e->spr[0],texx, texy, 0 ));
					y++;
				}
			}
			stripe++;
		}
		i++;
	}
}

void	draw_ray(t_raycast *rc, int x, t_env *e)
{
	t_ray	ray;

	ray_delimiter(rc, &ray);
	ray.x = x;
	rc->zbuffer[x] = rc->perpwalldist;
	draw_ray_ceil(e, &ray);
	draw_ray_wall(e, rc, &ray);
	draw_ray_floor(e, rc, &ray);
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
	rc->deltadistx = sqrt(1 + (rc->raydiry * rc->raydiry)
			/ (rc->raydirx * rc->raydirx));
	rc->deltadisty = sqrt(1 + (rc->raydirx * rc->raydirx) 
			/ (rc->raydiry * rc->raydiry));
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
		rc->perpwalldist = fabs(
				(rc->mapx - rc->rayposx + (1 - rc->stepx) / 2) / rc->raydirx);
	else
		rc->perpwalldist = fabs(
				(rc->mapy - rc->rayposy + (1 - rc->stepy) / 2) / rc->raydiry);
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
	draw_sprite(e, &rc);
}
