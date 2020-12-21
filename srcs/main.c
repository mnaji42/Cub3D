/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnaji <mnaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 16:31:07 by soel-kar          #+#    #+#             */
/*   Updated: 2019/11/17 14:52:44 by mnaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	init_param(t_cub *cub)
{
	cub->rx = 1280;
	cub->ry = 720;
	if (!(cub->txt.no.path = ft_strdup(PATH_NO)))
		return (-1);
	if (!(cub->txt.so.path = ft_strdup(PATH_SO)))
		return (-1);
	if (!(cub->txt.we.path = ft_strdup(PATH_WE)))
		return (-1);
	if (!(cub->txt.ea.path = ft_strdup(PATH_EA)))
		return (-1);
	if (!(cub->txt.s.path = ft_strdup(PATH_S)))
		return (-1);
	get_color(&cub->txt.sky.color, 40, 40, 40);
	get_color(&cub->txt.ground.color, 150, 150, 150);
	if (cub->rx + cub->ry < 2000)
	{
		cub->ray.move.speed = 0.05;
		cub->ray.move.cam_speed = 0.05;
	}
	else
	{
		cub->ray.move.speed = 0.1;
		cub->ray.move.cam_speed = 0.08;
	}
	return (1);
}

static void	background_color(t_img *img, int height)
{
	int		i;

	i = 0;
	while (i < height * 4)
	{
		img->data[i] = img->color.blue;
		img->data[i + 1] = img->color.green;
		img->data[i + 2] = img->color.red;
		img->data[i + 3] = 1;
		i = i + 4;
	}
}

static void	get_data_add_help(t_cub *cub)
{
	cub->txt.no.data = mlx_get_data_addr(cub->txt.no.ptr, &cub->txt.no.bpp, \
			&cub->txt.no.stride, &cub->txt.no.endian);
	cub->txt.so.data = mlx_get_data_addr(cub->txt.so.ptr, &cub->txt.so.bpp, \
			&cub->txt.so.stride, &cub->txt.so.endian);
	cub->txt.we.data = mlx_get_data_addr(cub->txt.we.ptr, &cub->txt.we.bpp, \
			&cub->txt.we.stride, &cub->txt.we.endian);
	cub->txt.ea.data = mlx_get_data_addr(cub->txt.ea.ptr, &cub->txt.ea.bpp, \
			&cub->txt.ea.stride, &cub->txt.ea.endian);
	cub->txt.s.data = mlx_get_data_addr(cub->txt.s.ptr, &cub->txt.s.bpp, \
			&cub->txt.s.stride, &cub->txt.s.endian);
	cub->txt.sky.ptr = mlx_new_image(cub->mlx.ptr, cub->rx, cub->ry);
	cub->txt.sky.data = mlx_get_data_addr(cub->txt.sky.ptr, &cub->txt.sky.bpp, \
			&cub->txt.sky.stride, &cub->txt.sky.endian);
	cub->txt.ground.ptr = mlx_new_image(cub->mlx.ptr, cub->rx, cub->ry);
	cub->txt.ground.data = mlx_get_data_addr(cub->txt.ground.ptr, \
			&cub->txt.ground.bpp, &cub->txt.ground.stride, \
			&cub->txt.ground.endian);
}

static int	init_img(t_cub *cub)
{
	cub->mlx.ptr = mlx_init();
	cub->img.ptr = mlx_new_image(cub->mlx.ptr, cub->rx, cub->ry);
	cub->img.data = mlx_get_data_addr(cub->img.ptr, &cub->img.bpp, \
			&cub->img.stride, &cub->img.endian);
	cub->img.bpp = cub->img.bpp / 8;
	ft_bzero(cub->img.data, cub->rx * cub->ry * cub->img.bpp);
	if (!(cub->txt.no.ptr = mlx_xpm_file_to_image(cub->mlx.ptr, \
			cub->txt.no.path, &cub->txt.no.x, &cub->txt.no.y)))
		return (print_error_path(cub->txt.no.path, cub));
	if (!(cub->txt.so.ptr = mlx_xpm_file_to_image(cub->mlx.ptr, \
			cub->txt.so.path, &cub->txt.so.x, &cub->txt.so.y)))
		return (print_error_path(cub->txt.so.path, cub));
	if (!(cub->txt.we.ptr = mlx_xpm_file_to_image(cub->mlx.ptr, \
			cub->txt.we.path, &cub->txt.we.x, &cub->txt.we.y)))
		return (print_error_path(cub->txt.we.path, cub));
	if (!(cub->txt.ea.ptr = mlx_xpm_file_to_image(cub->mlx.ptr, \
			cub->txt.ea.path, &cub->txt.ea.x, &cub->txt.ea.y)))
		return (print_error_path(cub->txt.ea.path, cub));
	if (!(cub->txt.s.ptr = mlx_xpm_file_to_image(cub->mlx.ptr, \
			cub->txt.s.path, &cub->txt.s.x, &cub->txt.s.y)))
		return (print_error_path(cub->txt.s.path, cub));
	get_data_add_help(cub);
	background_color(&cub->txt.sky, cub->rx * cub->ry);
	background_color(&cub->txt.ground, cub->rx * cub->ry);
	return (0);
}

int			main(int argc, char **argv)
{
	t_cub	cub;

	ft_bzero(&cub, sizeof(t_cub));
	if (ft_strcmp(&argv[1][ft_strlen(argv[1]) - 4], ".cub") != 0)
		ft_putstr("Error\nParam 1 must be a .cub file\n");
	else if ((argc == 3 && ft_strcmp(argv[2], "-save") == 0) || argc == 2)
	{
		if (init_param(&cub) == -1)
			ft_putstr("Initialisation parameter Cub3D don't work !\n");
		if (parsing(argv[1], &cub) == -1)
			return (0);
		if (init_img(&cub) == -1)
			return (0);
		cub.pl.pv = 100;
		create_image(&cub);
		if (argc == 3)
			export_as_bmp("screenshot.bmp", cub.img.data, cub.rx, cub.ry);
		else
			launch_window(&cub);
	}
	else
		print_error_usage(argc);
	free_all_cub(&cub, cub.map.height + 1);
	return (0);
}
