/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_image.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnaji <mnaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 14:57:44 by najimehdi         #+#    #+#             */
/*   Updated: 2019/11/17 14:59:53 by mnaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	dist_hit(t_cub *cub)
{
	cub->ray.hit = 1;
	if (cub->ray.side == 0)
		cub->ray.dist = (cub->ray.map_x - cub->pl.pos_x +
			(1 - cub->ray.step_x) / 2) / cub->ray.dir_x;
	else
		cub->ray.dist = (cub->ray.map_y - cub->pl.pos_y +
			(1 - cub->ray.step_y) / 2) / cub->ray.dir_y;
}

static void	calcul_dist(t_cub *cub)
{
	while (cub->ray.hit == 0)
	{
		if (cub->ray.side_dist_x < cub->ray.side_dist_y)
		{
			cub->ray.side_dist_x += cub->ray.dx;
			cub->ray.map_x += cub->ray.step_x;
			cub->ray.side = 0;
		}
		else
		{
			cub->ray.side_dist_y += cub->ray.dy;
			cub->ray.map_y += cub->ray.step_y;
			cub->ray.side = 1;
		}
		if (cub->map.s[cub->ray.map_x][cub->ray.map_y] == '2')
			sprite_here(cub);
		if (cub->map.s[cub->ray.map_x][cub->ray.map_y] == '1')
			dist_hit(cub);
	}
}

static void	step(t_cub *cub)
{
	if (cub->ray.dir_x < 0)
	{
		cub->ray.step_x = -1;
		cub->ray.side_dist_x = (cub->pl.pos_x -
			(int)cub->pl.pos_x) * cub->ray.dx;
	}
	else
	{
		cub->ray.step_x = 1;
		cub->ray.side_dist_x = ((int)cub->pl.pos_x + 1
			- cub->pl.pos_x) * cub->ray.dx;
	}
	if (cub->ray.dir_y < 0)
	{
		cub->ray.step_y = -1;
		cub->ray.side_dist_y = (cub->pl.pos_y -
			(int)cub->pl.pos_y) * cub->ray.dy;
	}
	else
	{
		cub->ray.step_y = 1;
		cub->ray.side_dist_y = ((int)cub->pl.pos_y + 1
			- cub->pl.pos_y) * cub->ray.dy;
	}
}

static void	init_ray(t_cub *cub, double x)
{
	cub->ray.cam = 2 * x / cub->rx - 1;
	cub->ray.map_x = (int)cub->pl.pos_x;
	cub->ray.map_y = (int)cub->pl.pos_y;
	cub->ray.dir_x = cub->pl.dir_x
		+ cub->ray.plane_x * cub->ray.cam;
	cub->ray.dir_y = cub->pl.dir_y
		+ cub->ray.plane_y * cub->ray.cam;
	cub->ray.dx = sqrt(1 + (cub->ray.dir_y * cub->ray.dir_y) /
			(cub->ray.dir_x * cub->ray.dir_x));
	cub->ray.dy = sqrt(1 + (cub->ray.dir_x * cub->ray.dir_x) /
			(cub->ray.dir_y * cub->ray.dir_y));
	cub->ray.hit = 0;
	cub->ray.dist = -1;
	cub->ray.side = -1;
}

void		create_image(t_cub *cub)
{
	int			x;
	t_sprite	*spr_draw;

	x = 0;
	while (x < cub->rx)
	{
		init_ray(cub, (double)x);
		step(cub);
		calcul_dist(cub);
		draw_wall(cub, x);
		draw_ground_sky(cub, x);
		x++;
	}
	while ((spr_draw = sort_sprites(cub)) != NULL)
		draw_sprite(cub, spr_draw);
}
