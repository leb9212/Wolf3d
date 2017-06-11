/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elee <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/30 16:52:38 by elee              #+#    #+#             */
/*   Updated: 2017/06/06 13:26:20 by elee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include "libft.h"
# include "mlx.h"
# include <math.h>
# include <pthread.h>
# include <time.h>
# include <fcntl.h>

# define MAP_WIDTH 24
# define MAP_HEIGHT 24

# define TEX_WIDTH 64
# define TEX_HEIGHT 64

# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080

# define KEY_ESC 53

# define KEY_UP 126
# define KEY_DOWN 125
# define KEY_LEFT 123
# define KEY_RIGHT 124

typedef struct	s_texture
{
	void		*img;
	char		*data;
	int			width;
	int			height;
	int			bpp;
	int			sl;
	int			end;
}				t_texture;

typedef struct	s_env
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*data;
	int			map_width;
	int			map_height;
	int			**map;
	int			bpp;
	int			sl;
	int			end;
	double		pos_x;
	double		pos_y;
	double		dir;
	double		dir_x;
	double		dir_y;
	double		move_speed;
	double		rot_speed;
	double		x;
	double		ray_pos_x;
	double		ray_pos_y;
	double		ray_dir;
	double		ray_dir_x;
	double		ray_dir_y;
	double		side_dist_x;
	double		side_dist_y;
	double		delta_dist_x;
	double		delta_dist_y;
	double		perp_wall_dist;
	double		wall_x;
	int			d;
	int			map_x;
	int			map_y;
	int			step_x;
	int			step_y;
	int			hit;
	int			side;
	int			line_height;
	int			draw_start;
	int			draw_end;
	int			color;
	double		old_dir_x;
	double		old_plane_x;
	double		floor_x;
	double		floor_y;
	double		dist_wall;
	double		dist_player;
	double		current_dist;
	double		weight;
	double		current_floor_x;
	double		current_floor_y;
	int			floor_tex_x;
	int			floor_tex_y;
	int			tex_num;
	int			tex_x;
	int			tex_y;
	clock_t		time;
	clock_t		old_time;
	double		frame_time;
	t_texture	texture[9];
}				t_env;

/*
** main.c
*/

void			error_msg(t_env *env, char *msg);

/*
** init.c
*/

int				get_texture_color(t_texture texture, int tex_x, int tex_y);
void			draw_point(t_env *env, int x, int y, int color);
void			cam_setup(t_env *env);
t_env			*env_init(void);

/*
** hooks.c
*/

int				expose_hook(t_env *env);
int				exit_hook(t_env *env);
int				key_hook(int key, t_env *env);

/*
** draw.c
*/

void			draw_wolf3d(t_env *env);

/*
** read.c
*/

char			**read_map(int fd);
void			check_valid_map(t_env *env, char **map);
void			convert_map(t_env *env, char **map);

#endif
