/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elee <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/31 11:02:55 by elee              #+#    #+#             */
/*   Updated: 2017/06/06 13:26:41 by elee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		get_texture_color(t_texture texture, int tex_x, int tex_y)
{
	int		index;
	int		color;

	index = texture.sl * tex_y + texture.bpp / 8 * tex_x;
	color = 0;
	color += (unsigned char)texture.data[index];
	color += (unsigned char)(texture.data[index + 1]) << 8;
	color += (unsigned char)(texture.data[index + 2]) << 16;
	color += (unsigned char)(texture.data[index + 3]) << 24;
	return (color);
}

void	draw_point(t_env *env, int x, int y, int color)
{
	int		index;

	index = env->sl * y + env->bpp / 8 * x;
	env->data[index + 0] = (color & 0x0000FF);
	env->data[index + 1] = (color & 0x00FF00) >> 8;
	env->data[index + 2] = (color & 0xFF0000) >> 16;
	env->data[index + 3] = 0;
}

t_env	*env_init(void)
{
	t_env	*env;

	env = (t_env*)malloc(sizeof(t_env));
	env->mlx = mlx_init();
	env->win = mlx_new_window(env->mlx, WIN_WIDTH, WIN_HEIGHT, "Wolf3d");
	env->map = NULL;
	env->pos_x = 22.0;
	env->pos_y = 11.5;
	env->dir = M_PI;
	env->time = clock();
	env->old_time = clock();
	return (env);
}

void	cam_setup(t_env *env)
{
	env->ray_pos_x = env->pos_x;
	env->ray_pos_y = env->pos_y;
	env->map_x = (int)env->ray_pos_x;
	env->map_y = (int)env->ray_pos_y;
	env->ray_dir = env->dir - 0.33 * env->x;
	env->ray_dir_x = cos(env->ray_dir);
	env->ray_dir_y = sin(env->ray_dir);
	env->dir_x = cos(env->dir);
	env->dir_y = sin(env->dir);
	env->delta_dist_x = sqrt(1 + (env->ray_dir_y * env->ray_dir_y) /
			(env->ray_dir_x * env->ray_dir_x));
	env->delta_dist_y = sqrt(1 + (env->ray_dir_x * env->ray_dir_x) /
			(env->ray_dir_y * env->ray_dir_y));
	env->step_x = (env->ray_dir_x < 0) ? -1 : 1;
	env->side_dist_x = (env->ray_dir_x < 0) ? (env->ray_pos_x - env->map_x) *
	env->delta_dist_x : (env->map_x + 1.0 - env->ray_pos_x) * env->delta_dist_x;
	env->step_y = (env->ray_dir_y < 0) ? -1 : 1;
	env->side_dist_y = (env->ray_dir_y < 0) ? (env->ray_pos_y - env->map_y) *
	env->delta_dist_y : (env->map_y + 1.0 - env->ray_pos_y) * env->delta_dist_y;
}
