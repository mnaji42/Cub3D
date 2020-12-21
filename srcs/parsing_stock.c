/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_stock.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnaji <mnaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 21:48:57 by najimehdi         #+#    #+#             */
/*   Updated: 2019/11/17 14:18:55 by mnaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	stock_color(char *param, t_color *txt)
{
	int		i;

	i = 0;
	txt->red = ft_atoi(&param[i]);
	while (ft_isdigit(param[i]))
		i++;
	i++;
	txt->green = ft_atoi(&param[i]);
	while (ft_isdigit(param[i]))
		i++;
	i++;
	txt->blue = ft_atoi(&param[i]);
}

static int	ifparam_isvalid(char *param)
{
	if (param[0] == 'R')
		return (1);
	else if (param[0] == 'N' && param[1] == 'O')
		return (2);
	else if (param[0] == 'S' && param[1] == 'O')
		return (2);
	else if (param[0] == 'W' && param[1] == 'E')
		return (2);
	else if (param[0] == 'E' && param[1] == 'A')
		return (2);
	else if (param[0] == 'S')
		return (1);
	else if (param[0] == 'F')
		return (1);
	else if (param[0] == 'C')
		return (1);
	return (-1);
}

static void	stock_resolutiom(char *param, t_cub *cub, int i)
{
	if (ft_atoi(&param[i]) > WINX_MAX)
		cub->rx = WINX_MAX;
	else
		cub->rx = ft_atoi(&param[i]);
	while (ft_isdigit(param[i]))
		i++;
	if (ft_atoi(&param[i]) > WINY_MAX)
		cub->ry = WINY_MAX;
	else
		cub->ry = ft_atoi(&param[i]);
	if (cub->rx > WINX_MAX)
		cub->rx = WINX_MAX;
	if (cub->ry > WINY_MAX)
		cub->ry = WINY_MAX;
	if (cub->rx < WINX_MIN)
		cub->rx = WINX_MIN;
	if (cub->ry < WINY_MIN)
		cub->ry = WINY_MIN;
}

void		stock_param(char *param, t_cub *cub)
{
	int		i;

	if ((i = ifparam_isvalid(param)) > 0)
		while (param[i] == ' ')
			i++;
	if (param[0] == 'R')
		stock_resolutiom(param, cub, i);
	else if (param[0] == 'N' && param[1] == 'O')
		cub->txt.no.path = ft_strdup_free(cub->txt.no.path, &param[i]);
	else if (param[0] == 'S' && param[1] == 'O')
		cub->txt.so.path = ft_strdup_free(cub->txt.so.path, &param[i]);
	else if (param[0] == 'W' && param[1] == 'E')
		cub->txt.we.path = ft_strdup_free(cub->txt.we.path, &param[i]);
	else if (param[0] == 'E' && param[1] == 'A')
		cub->txt.ea.path = ft_strdup_free(cub->txt.ea.path, &param[i]);
	else if (param[0] == 'S')
		cub->txt.s.path = ft_strdup_free(cub->txt.s.path, &param[i]);
	else if (param[0] == 'F')
		stock_color(&param[i], &cub->txt.ground.color);
	else if (param[0] == 'C')
		stock_color(&param[i], &cub->txt.sky.color);
}

int			stockmap(t_map *map)
{
	int		i;
	int		i2;

	i = 0;
	i2 = 0;
	if (!(map->s = (char**)ft_memalloc(sizeof(char*) * map->height)))
		return (-1);
	map->tmpfree++;
	while (i < map->height)
	{
		if (!(map->s[i] = ft_strndup(&map->tmp[i2], map->len)))
			return (-1);
		map->tmpfree++;
		i++;
		i2 = i2 + map->len;
	}
	return (0);
}
