/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libbmp.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnaji <mnaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 11:30:48 by mnaji             #+#    #+#             */
/*   Updated: 2019/11/17 11:31:01 by mnaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBBMP_H
# define LIBBMP_H
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include "bmp.h"
# include <stdio.h>

int				get_imagedata(t_bmp *bmp);
void			decode_bitmap_info_header(t_bmp *bmp);
void			decode_bmp_file_header(t_bmp *bmp);
unsigned char	*import_bmp(char *path, size_t *width, size_t *height);

void			fill_headers(t_bmp *bmp, int width, int height);
int				fill_imagedata(t_bmp *bmp, char *img, int width, int height);
int				write_rgb(t_bmp *bmp);
void			write_headers(t_bmp *bmp);
int				export_as_bmp(char *path, char *img, int width, int height);

t_bmp			*init_bmp(int height);
t_bitmap_data	*new_bitmapdata_node(t_uchar b, t_uchar g,
				t_uchar r);
int				check_header(t_bmp *bmp);
t_uint			bytes_to_number(t_uchar *str, t_uint len);
void			number_to_bytes(t_uint nb, unsigned char *buffer, t_uint len);
void			destroy_bmp(t_bmp *bmp);
void			free2d(unsigned char ***str);

#endif
