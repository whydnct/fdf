/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-m <aperez-m@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 13:05:23 by aperez-m          #+#    #+#             */
/*   Updated: 2023/05/27 08:01:52 by aperez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

void	get_str_map_rows(char *file, t_v_map *v_map)
{
	int	fd;
	int	temp;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		error_handler(OPEN_FAILED);
	temp = 0;
	while (get_next_line(fd))
		temp++;
	if (!temp)
		error_handler(EMPTY_FILE);
	close(fd);
	v_map->rows = temp;
}

char	***get_str_map(char *file, t_v_map *v_map)
{
	char	***ret;
	int		fd;
	int		i;

	i = -1;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		error_handler(OPEN_FAILED);
	ret = malloc(v_map->rows * sizeof(char **));
	if (!ret)
		error_handler(MALLOC_FAILED);
	while (++i < v_map->rows)
		ret[i] = ft_split(get_next_line(fd), ' ');
	close(fd);
	return (ret);
}

void	get_str_map_cols(t_v_map *v_map, char ***str_map)
{
	int	cols;
	int	i;
	int	j;
	int	temp;

	cols = 0;
	i = 0;
	j = 0;
	temp = 0;
	while (i < v_map->rows)
	{
		while (str_map[i][j][0] != '\n')
			j++;
		temp = j;
		if (cols < temp)
			cols = temp;
		j = 0;
		i++;
	}
	v_map->cols = cols;
}

void	get_heights_colors(t_v_map *v_map, char ***str_map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	v_map->vertices = malloc(v_map->rows * sizeof(t_vertex *));
	while (i < v_map->rows)
	{
		v_map->vertices[i] = malloc(v_map->cols * sizeof(t_vertex));
		while (j < v_map->cols)
		{
			v_map->vertices[i][j].height = ft_atoi(str_map[i][j]);
			v_map->vertices[i][j].color = \
				hex_to_color(ft_strchr(str_map[i][j], ','));
			j++;
		}
		j = 0;
		i++;
	}
}

int	hex_to_color(char *str)
{
	unsigned int	ret;
	char			*base;
	int				i;
	int				j;

	ret = 0;
	base = "123456789abcdef";
	i = 0;
	j = 0;
	if (!str)
		return (16777215);
	str++;
	while (i < 6 && *(str + i))
	{
		while (base[j] != ft_tolower(*(str + i)))
		{
			j++;
			if (j == 16)
				error_handler(WRONG_COLOR_CODE);
		}
		ret = ret * 16 + j;
		j = 0;
		i++;
	}
	return (ret);
}
