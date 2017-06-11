/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elee <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/02 03:03:32 by elee              #+#    #+#             */
/*   Updated: 2017/06/06 13:22:42 by elee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

char		**read_map(int fd)
{
	char	*line;
	char	**map;

	map = ft_ptrnew(0);
	while (get_next_line(fd, &line) > 0)
	{
		ft_twod_realloc(&map, line);
		free(line);
	}
	return (map);
}

void		check_valid_map(t_env *env, char **map)
{
	int		i;
	int		len;
	char	**parts;

	if (ft_ptrlen(map) == 0)
		error_msg(env, "Error: Invalid map");
	parts = ft_strsplit(map[0], ' ');
	len = ft_ptrlen(parts);
	ft_free_two(parts);
	i = 0;
	while (map[++i])
	{
		parts = ft_strsplit(map[i], ' ');
		if ((int)ft_ptrlen(parts) != len && ft_free_two(parts)
				&& ft_free_two(map))
			error_msg(env, "Error: Invalid map");
		ft_free_two(parts);
	}
	env->map_width = len;
	env->map_height = i + 1;
}

static int	check_int(char **parts)
{
	int		i;

	i = -1;
	while (parts[++i])
	{
		if (ft_strlen(parts[i]) != 1 && !ft_isdigit(parts[i][0]) &&
				(ft_atoi(parts[i]) < 0 || ft_atoi(parts[i]) > 7))
			return (0);
	}
	return (1);
}

void		convert_map(t_env *env, char **map)
{
	int		i;
	int		j;
	int		**i_map;
	char	**parts;

	i_map = ft_int_twodnew(env->map_height, env->map_width);
	i = -1;
	while (map[++i])
	{
		j = -1;
		parts = ft_strsplit(map[i], ' ');
		if (!check_int(parts) && ft_int_twodfree(i_map, env->map_height)
				&& ft_free_two(parts))
			error_msg(env, "Error: Invalid map");
		while (parts[++j])
			i_map[i][j] = ft_atoi(parts[j]);
		ft_free_two(parts);
	}
	env->map = i_map;
}
