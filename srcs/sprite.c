/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnaji <mnaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 16:19:58 by najimehdi         #+#    #+#             */
/*   Updated: 2019/11/17 15:01:55 by mnaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		sprite_here(t_cub *cub)
{
	int		i;

	i = 0;
	while (i < NB_SPRITES)
	{
		if (cub->spr[i].x == cub->ray.map_x + 0.5 && cub->spr[i].y == \
				cub->ray.map_y + 0.5)
		{
			cub->spr[i].distance = fabs(((cub->pl.pos_x - cub->spr[i].x) * \
					(cub->pl.pos_x - cub->spr[i].x) + (cub->pl.pos_y - \
					cub->spr[i].y) * (cub->pl.pos_y - cub->spr[i].y)));
			if (cub->spr[i].distance < 0.5)
				cub->pl.pv -= 0.001;
			return ;
		}
		i++;
	}
}

void		stock_sprites(t_cub *cub, char *map_tmp, int map_len)
{
	int		i;
	int		i2;
	int		x;
	int		y;

	i = 0;
	i2 = 0;
	x = 0;
	y = 0;
	while (map_tmp[i] != '\0' && i2 < NB_SPRITES)
	{
		if (map_tmp[i] == '2')
		{
			cub->spr[i2].x = x + 0.5;
			cub->spr[i2].y = y + 0.5;
			i2++;
		}
		if (y > map_len - 1)
		{
			y = 0;
			x++;
		}
		y++;
		i++;
	}
}

static void	put_txt_sprite(t_cub *cub, t_draw_spr *dsp)
{
	int		d;

	d = (dsp->y - dsp->vmove_screen) * 256 - cub->ry * 128 + \
		dsp->spr_height * 128;
	dsp->txt_y = ((d * TEXTURE_HEIGHT) / dsp->spr_height) / 256;
	if (cub->txt.s.data[4 * (int)(TEXTURE_WIDTH * dsp->txt_y + \
		dsp->txt_x)] != -120)
	{
		cub->img.data[4 * (int)(cub->rx * dsp->y + dsp->stripe)] = \
			cub->txt.s.data[4 * (TEXTURE_WIDTH * dsp->txt_y + dsp->txt_x)];
		cub->img.data[4 * (int)(cub->rx * dsp->y + dsp->stripe) + 1] = \
			cub->txt.s.data[4 * (TEXTURE_WIDTH * dsp->txt_y + dsp->txt_x) + 1];
		cub->img.data[4 * (int)(cub->rx * dsp->y + dsp->stripe) + 2] = \
			cub->txt.s.data[4 * (TEXTURE_WIDTH * dsp->txt_y + dsp->txt_x) + 2];
	}
}

static void	init_draw_spr(t_cub *cub, t_sprite *spr, t_draw_spr *dsp)
{
	dsp->invdet = 1.0 / (cub->ray.plane_x * cub->pl.dir_y - \
		cub->pl.dir_x * cub->ray.plane_y);
	dsp->transf_x = dsp->invdet * (cub->pl.dir_y * (spr->x - \
		cub->pl.pos_x) - cub->pl.dir_x * (spr->y - cub->pl.pos_y));
	dsp->transf_y = dsp->invdet * (-cub->ray.plane_y * (spr->x - \
		cub->pl.pos_x) + cub->ray.plane_x * (spr->y - cub->pl.pos_y));
	dsp->spr_screen = (int)((cub->rx / 2) * \
		(1 + dsp->transf_x / dsp->transf_y));
	dsp->vmove_screen = (int)(0.0 / dsp->transf_y);
	dsp->spr_height = abs((int)(cub->ry / (dsp->transf_y))) / 1;
	dsp->draw_start_y = -dsp->spr_height / 2 + cub->ry / 2 + dsp->vmove_screen;
	if (dsp->draw_start_y < 0)
		dsp->draw_start_y = 0;
	dsp->draw_end_y = dsp->spr_height / 2 + cub->ry / 2 + dsp->vmove_screen;
	if (dsp->draw_end_y >= cub->ry)
		dsp->draw_end_y = cub->ry - 1;
	dsp->spr_width = abs((int)(cub->ry / (dsp->transf_y))) / 1;
	dsp->draw_start_x = -dsp->spr_width / 2 + dsp->spr_screen;
	if (dsp->draw_start_x < 0)
		dsp->draw_start_x = 0;
	dsp->draw_end_x = dsp->spr_width / 2 + dsp->spr_screen;
	if (dsp->draw_end_x >= cub->rx)
		dsp->draw_end_x = cub->rx - 1;
	dsp->stripe = dsp->draw_start_x;
}

void		draw_sprite(t_cub *cub, t_sprite *spr)
{
	t_draw_spr	dsp;

	init_draw_spr(cub, spr, &dsp);
	while (dsp.stripe < dsp.draw_end_x)
	{
		dsp.txt_x = (int)(256 * (dsp.stripe - (-dsp.spr_width / 2 + \
		dsp.spr_screen)) * TEXTURE_WIDTH / dsp.spr_width) / 256;
		if (dsp.transf_y > 0 && dsp.stripe > 0 && dsp.stripe < cub->rx)
			dsp.y = dsp.draw_start_y;
		while (dsp.y < dsp.draw_end_y)
		{
			put_txt_sprite(cub, &dsp);
			dsp.y++;
		}
		dsp.stripe++;
	}
}
