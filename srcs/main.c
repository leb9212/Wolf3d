/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elee <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/30 16:52:55 by elee              #+#    #+#             */
/*   Updated: 2017/06/06 13:22:02 by elee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		error_msg(t_env *env, char *msg)
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
	if (msg)
		ft_putendl_fd(msg, 2);
	exit(0);
}

static void	import_textures(t_env *env)
{
	int		i;

	env->texture[0].img = mlx_xpm_file_to_image(env->mlx, "xpms/bluestone.xpm",
			&env->texture[0].width, &env->texture[0].height);
	env->texture[1].img = mlx_xpm_file_to_image(env->mlx, "xpms/eagle.xpm",
			&env->texture[1].width, &env->texture[1].height);
	env->texture[2].img = mlx_xpm_file_to_image(env->mlx, "xpms/greystone.xpm",
			&env->texture[2].width, &env->texture[2].height);
	env->texture[3].img = mlx_xpm_file_to_image(env->mlx, "xpms/pillar.xpm",
			&env->texture[3].width, &env->texture[3].height);
	env->texture[4].img = mlx_xpm_file_to_image(env->mlx, "xpms/redbrick.xpm",
			&env->texture[4].width, &env->texture[4].height);
	env->texture[5].img = mlx_xpm_file_to_image(env->mlx, "xpms/colorstone.xpm",
			&env->texture[5].width, &env->texture[5].height);
	env->texture[6].img = mlx_xpm_file_to_image(env->mlx, "xpms/mossy.xpm",
			&env->texture[6].width, &env->texture[6].height);
	env->texture[7].img = mlx_xpm_file_to_image(env->mlx, "xpms/purples.xpm",
			&env->texture[7].width, &env->texture[7].height);
	env->texture[8].img = mlx_xpm_file_to_image(env->mlx, "xpms/wood.xpm",
			&env->texture[8].width, &env->texture[8].height);
	i = -1;
	while (++i < 9)
		env->texture[i].data = mlx_get_data_addr(env->texture[i].img,
		&env->texture[i].bpp, &env->texture[i].sl, &env->texture[i].end);
}

int			main(int argc, char **argv)
{
	t_env		*env;
	int			fd;
	char		**map;

	env = NULL;
	if (argc != 2)
		error_msg(env, "Usage: ./wolf3d [map_file]");
	if ((fd = open(argv[1], O_RDONLY)) == -1)
		error_msg(env, "Error: Could not open the map file");
	env = env_init();
	map = read_map(fd);
	close(fd);
	check_valid_map(env, map);
	convert_map(env, map);
	import_textures(env);
	mlx_expose_hook(env->win, &expose_hook, env);
	mlx_hook(env->win, 2, 0, &key_hook, env);
	mlx_hook(env->win, 17, 0, &exit_hook, env);
	mlx_loop(env->mlx);
	return (0);
}
