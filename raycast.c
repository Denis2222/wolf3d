/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/18 17:22:37 by dmoureu-          #+#    #+#             */
/*   Updated: 2016/01/21 17:50:26 by dmoureu-         ###   ########.fr       */
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

void	ray_sprite(t_env *e, t_raysprite *rs)
{
	rs->spritex = e->sprite[rs->i].x - e->player->pos->x;
	rs->spritey = e->sprite[rs->i].y - e->player->pos->y;
	rs->invdet = 1.0 / (e->player->plane->x * e->player->dir->y
		- e->player->dir->x * e->player->plane->y);
	rs->tx = rs->invdet *
		(e->player->dir->y * rs->spritex - e->player->dir->x * rs->spritey);
	rs->ty = rs->invdet * (-e->player->plane->y
		* rs->spritex + e->player->plane->x * rs->spritey);
	rs->spritescreenx = (int)((WIDTH / 2) * (1 + rs->tx / rs->ty));
	rs->spriteheight = abs((int)(HEIGHT / rs->ty));
	rs->drawstarty = -rs->spriteheight / 2 + HEIGHT / 2;
	if (rs->drawstarty < 0)
		rs->drawstarty = 0;
	rs->drawendy = rs->spriteheight / 2 + HEIGHT / 2;
	if (rs->drawendy >= HEIGHT)
		rs->drawendy = HEIGHT - 1;
	rs->spritewidth = abs((int)(HEIGHT / rs->ty));
	rs->drawstartx = -rs->spritewidth / 2 + rs->spritescreenx;
	if (rs->drawstartx < 0)
		rs->drawstartx = 0;
	rs->drawendx = rs->spritewidth / 2 + rs->spritescreenx;
	if (rs->drawendx >= WIDTH)
		rs->drawendx = WIDTH - 1;
	rs->stripe = rs->drawstartx;
}

void	draw_sprite(t_env *e, t_raycast *rc, t_raysprite *rs)
{
	while (rs->stripe < rs->drawendx)
	{
		rs->texx = (int)(256 * (rs->stripe - (-rs->spritewidth
			/ 2 + rs->spritescreenx)) * 64 / rs->spritewidth) / 256;
		if (rs->ty > 0 && rs->stripe > 0
				&& rs->stripe < WIDTH && rs->ty < rc->zbuffer[rs->stripe])
		{
			rs->y = rs->drawstarty;
			while (rs->y < rs->drawendy)
			{
				rs->d = (rs->y) * 256 - HEIGHT * 128 + rs->spriteheight * 128;
				rs->texy = ((rs->d * 64) / rs->spriteheight) / 256;
				draw_dot(e, rs->stripe, rs->y,
					getcolor(e->spr[e->sprite[rs->i].texture],
						rs->texx, rs->texy, 0));
				rs->y++;
			}
		}
		rs->stripe++;
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

void	raycast(t_env *e)
{
	t_raycast	rc;
	t_raysprite	rs;
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
	rs.i = 0;
	while (rs.i < NBSPRITE)
	{
		ray_sprite(e, &rs);
		draw_sprite(e, &rc, &rs);
		rs.i++;
	}
}
