/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnaji <mnaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 20:12:57 by najimehdi         #+#    #+#             */
/*   Updated: 2019/11/17 14:58:59 by mnaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		get_color(t_color *elem, int red, int green, int blue)
{
	elem->red = red;
	elem->green = green;
	elem->blue = blue;
}

void		free_all_cub(t_cub *cub, int nb)
{
	ft_strdel(&cub->txt.no.path);
	ft_strdel(&cub->txt.so.path);
	ft_strdel(&cub->txt.we.path);
	ft_strdel(&cub->txt.ea.path);
	ft_strdel(&cub->txt.s.path);
	if (nb > 0)
		ft_strdel(&cub->map.tmp);
	while (nb > 1)
	{
		nb--;
		ft_strdel(&cub->map.s[nb - 1]);
	}
	if (nb == 1)
	{
		free(cub->map.s);
		cub->map.s = NULL;
	}
}

t_sprite	*sort_sprites(t_cub *cub)
{
	int			i;
	t_sprite	*spr_draw;
	double		dist;

	i = 0;
	dist = 0.1;
	while (i < NB_SPRITES)
	{
		if (cub->spr[i].distance > dist)
		{
			spr_draw = &cub->spr[i];
			dist = cub->spr[i].distance;
		}
		i++;
	}
	if (dist == 0.1)
		return (NULL);
	spr_draw->distance = 0;
	return (spr_draw);
}
