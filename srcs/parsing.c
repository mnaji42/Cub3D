/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnaji <mnaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 00:29:44 by najimehdi         #+#    #+#             */
/*   Updated: 2019/11/17 13:00:39 by mnaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	stock_player_dir(t_cub *cub, char c)
{
	if (c == 'N')
	{
		cub->pl.dir_x = -1;
		cub->ray.plane_y = 0.66;
	}
	else if (c == 'E')
	{
		cub->pl.dir_y = 1;
		cub->ray.plane_x = 0.66;
	}
	else if (c == 'S')
	{
		cub->pl.dir_x = 1;
		cub->ray.plane_y = -0.66;
	}
	else if (c == 'W')
	{
		cub->pl.dir_y = -1;
		cub->ray.plane_x = -0.66;
	}
}

static int	check_player(t_cub *cub, char *map_tmp, int map_len)
{
	int		i;

	i = 0;
	cub->pl.pos_x = 0.5;
	cub->pl.pos_y = 0.5;
	while (map_tmp[i] != '\0')
	{
		if (map_tmp[i] == 'N' || map_tmp[i] == 'S' || \
				map_tmp[i] == 'E' || map_tmp[i] == 'W')
		{
			stock_player_dir(cub, map_tmp[i]);
			map_tmp[i] = '0';
			return (1);
		}
		if (cub->pl.pos_y++ > map_len - 1)
		{
			cub->pl.pos_y = 0.5;
			cub->pl.pos_x++;
		}
		i++;
	}
	return (-1);
}

static int	check_wall(t_map *map)
{
	int		i;
	int		count;

	i = 0;
	count = 1;
	while (map->tmp[i] != '\0')
	{
		if (map->tmp[i] != '0' && map->tmp[i] != '1' && map->tmp[i] != '2')
			return (-1);
		if (i < map->len && map->tmp[i] != '1')
			return (-1);
		if ((count == 1 || count == map->len) && map->tmp[i] != '1')
			return (-1);
		if ((i > map->len * (map->height - 1)) && map->tmp[i] != '1')
			return (-1);
		count++;
		i++;
		if (count == map->len + 1)
			count = 1;
	}
	return (1);
}

static int	checkmap(int fd, char *str, t_cub *cub)
{
	str = ft_remove_space_free(str);
	cub->map.len = ft_strlen(str);
	cub->map.tmp = ft_strdup_free(str, str);
	cub->map.height++;
	while (get_next_line(fd, &str))
	{
		if (ft_strlen(str = ft_remove_space_free(str)) != (size_t)cub->map.len)
		{
			ft_strdel(&cub->map.tmp);
			ft_strdel(&str);
			return (-1);
		}
		cub->map.tmp = ft_strjoin_free2(cub->map.tmp, str);
		cub->map.height++;
	}
	if (check_player(cub, cub->map.tmp, cub->map.len) == (-1))
		return (-1);
	stock_sprites(cub, cub->map.tmp, cub->map.len);
	if (check_wall(&cub->map) == -1)
		return (-1);
	return (1);
}

int			parsing(char *file, t_cub *cub)
{
	int		fd;
	char	*str;

	if ((fd = open(file, O_RDONLY)) == -1)
		return (print_error("File not valid !\n", cub, -1));
	while (get_next_line(fd, &str))
	{
		if (ft_isdigit(str[0]) == 1)
			break ;
		stock_param(str, cub);
		free(str);
	}
	if (checkmap(fd, str, cub) == -1)
		return (print_error("Map Invalid !\n", cub, 0));
	if (stockmap(&cub->map) == -1)
		return (print_error("Alloc memory failed !\n", cub, cub->map.tmpfree));
	if (close(fd) == -1)
		return (print_error("Close failed !\n", cub, cub->map.height + 1));
	return (0);
}
