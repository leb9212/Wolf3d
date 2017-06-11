/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elee <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/30 22:32:56 by elee              #+#    #+#             */
/*   Updated: 2017/06/06 13:20:44 by elee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int			expose_hook(t_env *env)
{
	draw_wolf3d(env);
	return (0);
}

int			exit_hook(t_env *env)
{
	if (env)
	{
		if (env->win)
			mlx_destroy_window(env->mlx, env->win);
		if (env->mlx)
			free(env->mlx);
		if (env->map)
			ft_int_twodfree(env->map, env->map_height);
		free(env);
	}
	exit(0);
	return (0);
}

static void	key_up_down(int key, t_env *env)
{
	if (key == KEY_UP)
	{
		if (env->map[(int)(env->pos_x + env->dir_x *
				env->move_speed)][(int)(env->pos_y)] == 0)
			env->pos_x += env->dir_x * env->move_speed;
		if (env->map[(int)(env->pos_x)][(int)(env->pos_y +
					env->dir_y * env->move_speed)] == 0)
			env->pos_y += env->dir_y * env->move_speed;
	}
	else if (key == KEY_DOWN)
	{
		if (env->map[(int)(env->pos_x - env->dir_x *
					env->move_speed)][(int)(env->pos_y)] == 0)
			env->pos_x -= env->dir_x * env->move_speed;
		if (env->map[(int)(env->pos_x)][(int)(env->pos_y -
					env->dir_y * env->move_speed)] == 0)
			env->pos_y -= env->dir_y * env->move_speed;
	}
	draw_wolf3d(env);
}

static void	key_left_right(int key, t_env *env)
{
	if (key == KEY_RIGHT)
		env->dir -= env->rot_speed;
	else if (key == KEY_LEFT)
		env->dir += env->rot_speed;
	draw_wolf3d(env);
}

int			key_hook(int key, t_env *env)
{
	(key == KEY_ESC) ? exit(0) : 0;
	key_up_down(key, env);
	key_left_right(key, env);
	return (0);
}
