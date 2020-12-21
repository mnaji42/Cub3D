/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnaji <mnaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 20:56:46 by najimehdi         #+#    #+#             */
/*   Updated: 2019/11/17 12:55:52 by mnaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	move_side(t_cub *cub)
{
	if (cub->ray.move.left == 1)
	{
		if (cub->map.s[(int)(cub->pl.pos_x - cub->pl.dir_y *\
				cub->ray.move.speed)][(int)(cub->pl.pos_y)] != '1')
			cub->pl.pos_x -= cub->pl.dir_y * cub->ray.move.speed;
		if (cub->map.s[(int)cub->pl.pos_x][(int)(cub->pl.pos_y + \
				cub->pl.dir_x * cub->ray.move.speed)] != '1')
			cub->pl.pos_y += cub->pl.dir_x * cub->ray.move.speed;
	}
	if (cub->ray.move.right == 1)
	{
		if (cub->map.s[(int)(cub->pl.pos_x + cub->pl.dir_y *\
				cub->ray.move.speed)][(int)(cub->pl.pos_y)] != '1')
			cub->pl.pos_x += cub->pl.dir_y * cub->ray.move.speed;
		if (cub->map.s[(int)cub->pl.pos_x][(int)(cub->pl.pos_y - \
				cub->pl.dir_x * cub->ray.move.speed)] != '1')
			cub->pl.pos_y -= cub->pl.dir_x * cub->ray.move.speed;
	}
}

static void	move_straight(t_cub *cub)
{
	if (cub->ray.move.back == 1)
	{
		if (cub->map.s[(int)(cub->pl.pos_x - cub->pl.dir_x *\
				cub->ray.move.speed)][(int)cub->pl.pos_y] != '1')
			cub->pl.pos_x -= cub->pl.dir_x * cub->ray.move.speed;
		if (cub->map.s[(int)cub->pl.pos_x][(int)(cub->pl.pos_y - \
				cub->pl.dir_y * cub->ray.move.speed)] != '1')
			cub->pl.pos_y -= cub->pl.dir_y * cub->ray.move.speed;
	}
	if (cub->ray.move.forward == 1)
	{
		if (cub->map.s[(int)(cub->pl.pos_x + cub->pl.dir_x *\
				cub->ray.move.speed)][(int)cub->pl.pos_y] != '1')
			cub->pl.pos_x += cub->pl.dir_x * cub->ray.move.speed;
		if (cub->map.s[(int)cub->pl.pos_x][(int)(cub->pl.pos_y +\
				cub->pl.dir_y * cub->ray.move.speed)] != '1')
			cub->pl.pos_y += cub->pl.dir_y * cub->ray.move.speed;
	}
}

static void	move_cam_right(t_cub *cub)
{
	double	old_player_dir_x;
	double	old_plane_x;

	old_player_dir_x = cub->pl.dir_x;
	cub->pl.dir_x = cub->pl.dir_x * cos(-cub->ray.move.cam_speed) -\
		cub->pl.dir_y * sin(-cub->ray.move.cam_speed);
	cub->pl.dir_y = old_player_dir_x * sin(-cub->ray.move.cam_speed) +\
		cub->pl.dir_y * cos(-cub->ray.move.cam_speed);
	old_plane_x = cub->ray.plane_x;
	cub->ray.plane_x = cub->ray.plane_x * cos(-cub->ray.move.cam_speed) -\
		cub->ray.plane_y * sin(-cub->ray.move.cam_speed);
	cub->ray.plane_y = old_plane_x * sin(-cub->ray.move.cam_speed) +\
		cub->ray.plane_y * cos(-cub->ray.move.cam_speed);
}

static void	move_cam_left(t_cub *cub)
{
	double	old_player_dir_x;
	double	old_plane_x;

	old_player_dir_x = cub->pl.dir_x;
	cub->pl.dir_x = cub->pl.dir_x * cos(cub->ray.move.cam_speed) -\
		cub->pl.dir_y * sin(cub->ray.move.cam_speed);
	cub->pl.dir_y = old_player_dir_x * sin(cub->ray.move.cam_speed) +\
		cub->pl.dir_y * cos(cub->ray.move.cam_speed);
	old_plane_x = cub->ray.plane_x;
	cub->ray.plane_x = cub->ray.plane_x * cos(cub->ray.move.cam_speed) -\
			cub->ray.plane_y * sin(cub->ray.move.cam_speed);
	cub->ray.plane_y = old_plane_x * sin(cub->ray.move.cam_speed) +\
			cub->ray.plane_y * cos(cub->ray.move.cam_speed);
}

void		move(t_cub *cub)
{
	if (cub->ray.move.cam_left == 1)
		move_cam_left(cub);
	if (cub->ray.move.cam_right == 1)
		move_cam_right(cub);
	if (cub->ray.move.back == 1 || cub->ray.move.forward == 1)
		move_straight(cub);
	if (cub->ray.move.left == 1 || cub->ray.move.right == 1)
		move_side(cub);
}
