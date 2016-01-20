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

void	draw_line(t_raycast *rc, int x, t_env *e)
{
	int	lineheight;
	int	drawstart;
	int	drawend;
	int	color;
	int	s;

	color = e->map->wall[(int)rc->mapy][(int)rc->mapx];
	//printf("[%d:%d]%d\n", (int)rc->mapy, (int)rc->mapx, color);
	s = 0;
	lineheight = abs((int)(HEIGHT / rc->perpwalldist));
	drawstart = -lineheight / 2 + HEIGHT / 2;
	if (drawstart < 0)
		drawstart = 0;
	drawend = lineheight / 2 + HEIGHT / 2;
	if (drawend >= HEIGHT)
		drawend = HEIGHT - 1;

	double	wallx;
	if (rc->side == 1)
		wallx = rc->rayposx + ((rc->mapy - rc->rayposy + (1 - rc->stepy) / 2) / rc->raydiry) * rc->raydirx;
	else
		wallx = rc->rayposy + ((rc->mapx - rc->rayposx + (1 - rc->stepx) / 2) / rc->raydirx) * rc->raydiry;
	wallx -= floor(wallx);

	//if (x == WIDTH / 2)
	//	printf("wallx:%f\n", wallx);
	int	texx;
	int	texy;
	int	d;
	int	c;

	texx = (int)(wallx * (double)64);
	if (rc->side == 0 && rc->raydirx > 0)
		texx = 64 - texx - 1;
	if (rc->side == 1 && rc->raydiry < 0)
		texx = 64 - texx -1;

	//printf("texx:%d\n", texx);
	while (s < HEIGHT)
	{
		if (s < drawstart)
			draw_dot(e, x, s, 150 + 150 * 256 + 150 * 256 * 256);
		else if (s >= drawstart && s <= drawend)
		{
			d = s * 256 - HEIGHT * 128 + lineheight * 128;
			texy = ((d * 64) / lineheight) / 256;

			c = (texy * 64 + texx) * 4;
			draw_dot(e, x, s, e->wall->buffer[c] + 256 * e->wall->buffer[c + 1] + 256 * 256 * e->wall->buffer[c + 2]);
			/*
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
			draw_dot(e, x, s, 50 + 50 * 256 + 50 * 256 * 256); 
		s++;
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

void	raydda(t_raycast *rc, t_env *e, int x)
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
		if (x == 512 && rc->hit == 1 )
		{
			//printf("raydir:[%f:%f]  hit[%d:%d]\n", rc->raydirx, rc->raydiry, (int)rc->mapx, (int)rc->mapy);
			//printf("raypos:[%f:%f]\n", rc->rayposx, rc->rayposy);

		}
	}
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
		raydda(&rc, e, x);
		if (rc.side == 0)
			rc.perpwalldist = fabs((rc.mapx - rc.rayposx + (1 - rc.stepx) / 2) / rc.raydirx);
		else
			rc.perpwalldist = fabs((rc.mapy - rc.rayposy + (1 - rc.stepy) / 2) / rc.raydiry);
		draw_line(&rc, x, e);
		x++;
	}
}
