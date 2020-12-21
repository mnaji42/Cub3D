/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnaji <mnaji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 18:20:27 by soel-kar          #+#    #+#             */
/*   Updated: 2019/11/17 14:51:56 by mnaji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "mlx.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <math.h>
# include "libbmp.h"

# define PATH_NO "./texture_xpm/wall/brick1.xpm"
# define PATH_SO "./texture_xpm/wall/brick2.xpm"
# define PATH_WE "./texture_xpm/wall/brick3.xpm"
# define PATH_EA "./texture_xpm/wall/brick4.xpm"
# define PATH_S "./texture_xpm/sprite/skeleton1.xpm"
# define WINX_MAX 2560
# define WINY_MAX 1395
# define WINX_MIN 520
# define WINY_MIN 280
# define TEXTURE_WIDTH 64
# define TEXTURE_HEIGHT 64
# define NB_SPRITES 20

typedef struct	s_color
{
	int			red;
	int			green;
	int			blue;
}				t_color;

typedef struct	s_img
{
	char	*path;
	void	*ptr;
	char	*data;
	int		bpp;
	int		stride;
	int		endian;
	int		x;
	int		y;
	t_color	color;
}				t_img;

typedef struct	s_texture
{
	t_img		no;
	t_img		so;
	t_img		we;
	t_img		ea;
	t_img		s;
	t_img		sky;
	t_img		ground;
}				t_texture;

typedef struct	s_map
{
	char		**s;
	char		*tmp;
	int			height;
	int			len;
	int			tmpfree;
}				t_map;

typedef struct	s_player
{
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		pv;
}				t_player;

typedef struct	s_mlx
{
	void		*ptr;
	void		*win;
}				t_mlx;

typedef struct	s_move
{
	double		speed;
	double		cam_speed;
	int			forward;
	int			back;
	int			left;
	int			right;
	int			cam_left;
	int			cam_right;
}				t_move;

typedef struct	s_draw_spr
{
	double		invdet;
	double		transf_x;
	double		transf_y;
	int			spr_screen;
	int			vmove_screen;
	int			spr_height;
	int			spr_width;
	int			draw_start_x;
	int			draw_start_y;
	int			draw_end_x;
	int			draw_end_y;
	int			stripe;
	int			txt_x;
	int			txt_y;
	int			y;
}				t_draw_spr;

typedef struct	s_sprite
{
	double		x;
	double		y;
	double		distance;
}				t_sprite;

typedef struct	s_ray
{
	double		plane_x;
	double		plane_y;
	double		cam;
	int			map_x;
	int			map_y;
	double		dir_x;
	double		dir_y;
	double		dx;
	double		dy;
	int			hit;
	int			side;
	double		dist;
	int			step_x;
	int			step_y;
	double		side_dist_x;
	double		side_dist_y;
	int			draw_start;
	int			draw_end;
	int			txt_x;
	int			txt_y;
	t_move		move;
}				t_ray;

typedef struct	s_cub
{
	int			rx;
	int			ry;
	t_texture	txt;
	t_map		map;
	t_player	pl;
	t_mlx		mlx;
	t_ray		ray;
	t_img		img;
	t_sprite	spr[NB_SPRITES];
	t_draw_spr	dspr;
}				t_cub;

int				parsing(char *file, t_cub *cub);
void			get_color(t_color *elem, int red, int green, int blue);
void			print_error_usage(int argc);
int				print_error(char *error, t_cub *cub, int i);
void			free_all_cub(t_cub *cub, int nb);
void			launch_window(t_cub *cub);
int				print_error_path(char *path, t_cub *cub);
void			create_image(t_cub *cub);
void			move(t_cub *cub);
void			draw_ground_sky(t_cub *cub, int x);
void			draw_wall(t_cub *cub, int x);
void			stock_param(char *param, t_cub *cub);
int				stockmap(t_map *map);
void			stock_sprites(t_cub *cub, char *map_tmp, int map_len);
int				save_bmp(t_cub *cub);
void			sprite_here(t_cub *cub);
void			draw_sprite(t_cub *cub, t_sprite *spr);
t_sprite		*sort_sprites(t_cub *cub);

#endif
