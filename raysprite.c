#include "wolf3d.h"

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
