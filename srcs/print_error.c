/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnaji <mnaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 20:27:38 by najimehdi         #+#    #+#             */
/*   Updated: 2019/11/17 13:02:23 by mnaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_error_usage(int argc)
{
	ft_putstr("Error\n");
	if (argc < 2)
		ft_putstr("Too few arguments\n");
	else
		ft_putstr("Too much arguments\n");
	ft_putstr("Usage:\nTo run Cub3D : ./Cub3D [path to the maps]\n");
	ft_putstr("To save the first img : ./Cub3D [path to the maps] -save\n");
}

int		print_error(char *error, t_cub *cub, int nb)
{
	free_all_cub(cub, nb);
	ft_putstr("Error\n");
	ft_putstr(error);
	return (-1);
}

int		print_error_path(char *path, t_cub *cub)
{
	ft_putstr("Error\n\"");
	ft_putstr(path);
	ft_putstr("\" don't works ! Please enter a valid path !\n");
	free_all_cub(cub, cub->map.height + 1);
	return (-1);
}
