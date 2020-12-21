/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: najimehdi <najimehdi@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 00:16:57 by najimehdi         #+#    #+#             */
/*   Updated: 2019/10/22 00:19:21 by najimehdi        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_free2(char *s1, char *s2)
{
	char	*str;
	int		len_join;
	int		i;
	int		i2;

	if (s1 == 0 || s2 == 0)
		return (NULL);
	len_join = ft_strlen(s1) + ft_strlen(s2);
	i = 0;
	i2 = 0;
	if (!(str = (char*)malloc(sizeof(char) * (len_join + 1))))
		return (NULL);
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[i2] != '\0')
		str[i++] = s2[i2++];
	str[i] = '\0';
	ft_strdel(&s1);
	ft_strdel(&s2);
	return (str);
}
