/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elee <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/31 13:25:42 by elee              #+#    #+#             */
/*   Updated: 2017/06/06 13:26:27 by elee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		dda(t_env *env)
{
	env->hit = 0;
	while (env->hit == 0)
	{
		if (env->side_dist_x < env->side_dist_y && !(env->side = 0))
		{
			env->side_dist_x += env->delta_dist_x;
			env->map_x += env->step_x;
		}
		else if ((env->side = 1))
		{
			env->side_dist_y += env->delta_dist_y;
			env->map_y += env->step_y;
		}
		(env->map[env->map_x][env->map_y] > 0) ? (env->hit = 1) : 0;
	}
	env->perp_wall_dist = (env->side == 0) ?
		(env->map_x - env->ray_pos_x + (1 - env->step_x) / 2) / env->ray_dir_x :
		(env->map_y - env->ray_pos_y + (1 - env->step_y) / 2) / env->ray_dir_y;
	env->line_height = (int)(WIN_HEIGHT / env->perp_wall_dist);
	env->draw_start = -env->line_height / 2 + WIN_HEIGHT / 2;
	(env->draw_start < 0) ? (env->draw_start = 0) : 0;
	env->draw_end = env->line_height / 2 + WIN_HEIGHT / 2;
	(env->draw_end >= WIN_HEIGHT) ? (env->draw_end = WIN_HEIGHT - 1) : 0;
}

void		draw_wall(t_env *env, int x)
{
	int		y;

	env->tex_num = env->map[env->map_x][env->map_y] - 1;
	if (env->side == 0)
		env->wall_x = env->ray_pos_y + env->perp_wall_dist * env->ray_dir_y;
	else
		env->wall_x = env->ray_pos_x + env->perp_wall_dist * env->ray_dir_x;
	env->wall_x -= floor(env->wall_x);
	env->tex_x = (int)(env->wall_x * (double)TEX_WIDTH);
	if ((env->side == 0 && env->ray_dir_x > 0)
			|| (env->side == 1 && env->ray_dir_y < 0))
		env->tex_x = TEX_WIDTH - env->tex_x - 1;
	y = env->draw_start - 1;
	while (++y < env->draw_end)
	{
		env->d = y * 256 - WIN_HEIGHT * 128 + env->line_height * 128;
		env->tex_y = ((env->d * TEX_HEIGHT) / env->line_height) / 256;
		env->color = get_texture_color(env->texture[env->tex_num],
				env->tex_x, env->tex_y);
		(env->side == 1) ? (env->color = (env->color >> 1) & 8355711) : 0;
		draw_point(env, x, y, env->color);
	}
}

void		floor_setup(t_env *env)
{
	if (env->side == 0 && env->ray_dir_x > 0)
	{
		env->floor_x = env->map_x;
		env->floor_y = env->map_y + env->wall_x;
	}
	else if (env->side == 0 && env->ray_dir_x < 0)
	{
		env->floor_x = env->map_x + 1.0;
		env->floor_y = env->map_y + env->wall_x;
	}
	else if (env->side == 1 && env->ray_dir_y > 0)
	{
		env->floor_x = env->map_x + env->wall_x;
		env->floor_y = env->map_y;
	}
	else
	{
		env->floor_x = env->map_x + env->wall_x;
		env->floor_y = env->map_y + 1.0;
	}
	env->dist_wall = env->perp_wall_dist;
	env->dist_player = 0.0;
	if (env->draw_end < 0)
		env->draw_end = WIN_HEIGHT;
}

void		draw_floor(t_env *env, int x)
{
	int		y;

	y = env->draw_end;
	while (++y < WIN_HEIGHT)
	{
		env->current_dist = WIN_HEIGHT / (2.0 * y - WIN_HEIGHT);
		env->weight = (env->current_dist - env->dist_player) /
			(env->dist_wall - env->dist_player);
		env->current_floor_x = env->weight * env->floor_x +
			(1.0 - env->weight) * env->pos_x;
		env->current_floor_y = env->weight * env->floor_y +
			(1.0 - env->weight) * env->pos_y;
		env->floor_tex_x = (int)(env->current_floor_x * TEX_WIDTH)
			% TEX_WIDTH;
		env->floor_tex_y = (int)(env->current_floor_y * TEX_HEIGHT)
			% TEX_HEIGHT;
		draw_point(env, x, y, (get_texture_color(env->texture[6],
					env->floor_tex_x, env->floor_tex_y) >> 1) & 8355711);
		draw_point(env, x, WIN_HEIGHT - y, get_texture_color(env->texture[6],
					env->floor_tex_x, env->floor_tex_y));
	}
}

void		draw_wolf3d(t_env *env)
{
	int		x;

	mlx_clear_window(env->mlx, env->win);
	env->img = mlx_new_image(env->mlx, WIN_WIDTH, WIN_HEIGHT);
	env->data = mlx_get_data_addr(env->img, &env->bpp, &env->sl, &env->end);
	x = -1;
	while (++x < WIN_WIDTH)
	{
		env->x = 2 * x / (double)WIN_WIDTH - 1;
		cam_setup(env);
		dda(env);
		draw_wall(env, x);
		floor_setup(env);
		draw_floor(env, x);
	}
	env->old_time = env->time;
	env->time = clock();
	env->frame_time = (double)(env->time - env->old_time) / CLOCKS_PER_SEC;
	env->move_speed = env->frame_time * 1.5;
	env->rot_speed = env->frame_time * 1;
	mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
	mlx_destroy_image(env->mlx, env->img);
}
