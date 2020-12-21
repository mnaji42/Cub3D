/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnaji <mnaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 20:07:50 by najimehdi         #+#    #+#             */
/*   Updated: 2019/11/17 15:15:41 by mnaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	exit_x(t_cub *cub)
{
	free_all_cub(cub, cub->map.height + 1);
	mlx_destroy_window(cub->mlx.ptr, cub->mlx.win);
	exit(0);
	return (0);
}

static int	release_key(int keycode, t_cub *cub)
{
	if (keycode == 53)
	{
		free_all_cub(cub, cub->map.height + 1);
		mlx_destroy_window(cub->mlx.ptr, cub->mlx.win);
		exit(0);
	}
	if (keycode == 0)
		cub->ray.move.left = 0;
	if (keycode == 2)
		cub->ray.move.right = 0;
	if (keycode == 123)
		cub->ray.move.cam_left = 0;
	if (keycode == 124)
		cub->ray.move.cam_right = 0;
	if (keycode == 125 || keycode == 1)
		cub->ray.move.back = 0;
	if (keycode == 126 || keycode == 13)
		cub->ray.move.forward = 0;
	if (keycode == 49 && cub->rx + cub->ry < 2000)
		cub->ray.move.speed = 0.05;
	else if (keycode == 49)
		cub->ray.move.speed = 0.1;
	return (0);
}

static int	press_key(int keycode, t_cub *cub)
{
	if (keycode == 53)
	{
		free_all_cub(cub, cub->map.height + 1);
		mlx_destroy_window(cub->mlx.ptr, cub->mlx.win);
		exit(0);
	}
	if (keycode == 0)
		cub->ray.move.left = 1;
	if (keycode == 2)
		cub->ray.move.right = 1;
	if (keycode == 123)
		cub->ray.move.cam_left = 1;
	if (keycode == 124)
		cub->ray.move.cam_right = 1;
	if (keycode == 125 || keycode == 1)
		cub->ray.move.back = 1;
	if (keycode == 126 || keycode == 13)
		cub->ray.move.forward = 1;
	if (keycode == 49 && cub->rx + cub->ry < 2000)
		cub->ray.move.speed = 0.1;
	else if (keycode == 49)
		cub->ray.move.speed = 0.2;
	if (keycode == 36 && cub->pl.pv <= 0)
		cub->pl.pv = 100;
	return (0);
}

static int	deal_hook(t_cub *cub)
{
	if (cub->pl.pv > 0)
	{
		ft_bzero(cub->img.data, cub->rx * cub->ry * cub->img.bpp);
		move(cub);
		create_image(cub);
		mlx_put_image_to_window(cub->mlx.ptr, cub->mlx.win, cub->img.ptr, 0, 0);
		mlx_string_put(cub->mlx.ptr, cub->mlx.win, 20, 20, 0xffffff, \
			ft_itoa((int)cub->pl.pv));
	}
	else
	{
		mlx_string_put(cub->mlx.ptr, cub->mlx.win, cub->rx / 2 - 40, \
			cub->ry / 2 - 20, 0xff0000, "GAME OVER");
		mlx_string_put(cub->mlx.ptr, cub->mlx.win, cub->rx / 2 - 110, \
			cub->ry / 2 + 20, 0x00ff00, "PRESS ENTER TO CONTINUE");
	}
	return (0);
}

void		launch_window(t_cub *cub)
{
	cub->mlx.win = mlx_new_window(cub->mlx.ptr, cub->rx, cub->ry, "Cub3D");
	mlx_hook(cub->mlx.win, 17, 1L << 17, exit_x, cub);
	mlx_hook(cub->mlx.win, 2, 3, press_key, cub);
	mlx_hook(cub->mlx.win, 3, 3, release_key, cub);
	mlx_loop_hook(cub->mlx.ptr, deal_hook, cub);
	mlx_loop(cub->mlx.ptr);
}
