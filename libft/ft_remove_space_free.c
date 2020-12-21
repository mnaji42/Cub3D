/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_space_free.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnaji <mnaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 23:25:34 by najimehdi         #+#    #+#             */
/*   Updated: 2019/11/17 15:19:21 by mnaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_remove_space_free(char *s)
{
	char	*str;
	int		i;
	int		i2;
	int		len;

	i = 0;
	i2 = 0;
	len = 0;
	while (s[i] != '\0')
		if (s[i++] != ' ')
			len++;
	if (!(str = (char*)ft_memalloc(sizeof(char) * len + 1)))
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] != ' ')
			str[i2++] = s[i];
		i++;
	}
	ft_strdel(&s);
	return (str);
}
