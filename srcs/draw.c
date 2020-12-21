/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnaji <mnaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 21:14:11 by najimehdi         #+#    #+#             */
/*   Updated: 2019/11/17 12:45:12 by mnaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		draw_ground_sky(t_cub *cub, int x)
{
	int		y;

	y = cub->ray.draw_end + 1;
	while (y < cub->ry)
	{
		cub->img.data[4 * (cub->rx * y + x)] = cub->txt.ground.color.blue;
		cub->img.data[4 * (cub->rx * y + x) + 1] = cub->txt.ground.color.green;
		cub->img.data[4 * (cub->rx * y + x) + 2] = cub->txt.ground.color.red;
		cub->img.data[4 * (cub->rx * (cub->ry - y) + x)] = \
			cub->txt.sky.color.blue;
		cub->img.data[4 * (cub->rx * (cub->ry - y) + x) + 1] = \
			cub->txt.sky.color.green;
		cub->img.data[4 * (cub->rx * (cub->ry - y) + x) + 2] = \
			cub->txt.sky.color.red;
		y++;
	}
}

static void	put_texture_wall(t_cub *cub, int x, int y)
{
	t_img	*tmp;

	if (cub->ray.side == 0 && cub->ray.dir_x >= 0)
		tmp = &cub->txt.no;
	else if (cub->ray.side == 0 && cub->ray.dir_x < 0)
		tmp = &cub->txt.so;
	else if (cub->ray.side == 1 && cub->ray.dir_y >= 0)
		tmp = &cub->txt.we;
	else
		tmp = &cub->txt.ea;
	cub->img.data[4 * (cub->rx * y + x)] = tmp->data
		[4 * (TEXTURE_WIDTH * cub->ray.txt_y + cub->ray.txt_x)];
	cub->img.data[4 * (cub->rx * y + x) + 1] = tmp->data
		[4 * (TEXTURE_WIDTH * cub->ray.txt_y + cub->ray.txt_x) + 1];
	cub->img.data[4 * (cub->rx * y + x) + 2] = tmp->data
		[4 * (TEXTURE_WIDTH * cub->ray.txt_y + cub->ray.txt_x) + 2];
}

void		draw_wall(t_cub *cub, int x)
{
	int		line_height;
	double	wall_x;

	line_height = (int)(cub->ry / cub->ray.dist);
	cub->ray.draw_start = (cub->ry - line_height) / 2;
	if (cub->ray.draw_start < 0)
		cub->ray.draw_start = 0;
	cub->ray.draw_end = (cub->ry + line_height) / 2;
	if (cub->ray.draw_end >= cub->ry)
		cub->ray.draw_end = cub->ry - 1;
	if (cub->ray.side == 0)
		wall_x = cub->pl.pos_y + cub->ray.dist * cub->ray.dir_y;
	else
		wall_x = cub->pl.pos_x + cub->ray.dist * cub->ray.dir_x;
	wall_x -= floor(wall_x);
	cub->ray.txt_x = (int)(wall_x * TEXTURE_WIDTH);
	while (cub->ray.draw_start < cub->ray.draw_end)
	{
		cub->ray.txt_y = ((cub->ray.draw_start - cub->ry * 0.5f +
			line_height * 0.5f) * TEXTURE_WIDTH) / line_height;
		put_texture_wall(cub, x, cub->ray.draw_start);
		cub->ray.draw_start++;
	}
}
