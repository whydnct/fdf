/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-m <aperez-m@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 13:05:23 by aperez-m          #+#    #+#             */
/*   Updated: 2023/06/20 22:48:59 by aperez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

void	get_str_map_rows(char *file, t_v_map *v_map)
{
	int		fd;
	int		temp;
	char	*line;
	int		line_cols;

	printf("get_str_map_rows()\n");
	fd = open(file, O_RDONLY);
	if (fd < 0)
		error_handler(OPEN_FAILED);
	line = get_next_line(fd);
	printf("%s\n", line);
	if (!line)
		error_handler(EMPTY_FILE);
	temp = 0;
	while (line)
	{
		line_cols = get_line_cols(line, ' ');
		free(line);
		temp++;
		line = get_next_line(fd);
		if (line && line_cols != get_line_cols(line, ' '))
			break ;
	}
	close(fd);
	v_map->rows = temp;
	v_map->cols = line_cols;
	printf("rows:%d - cols:%d\n", v_map->rows, v_map->cols);
}

char	***get_str_map(char *file, t_v_map *v_map)
{
	char	***ret;
	int		fd;
	int		i;
	char	*line;

	printf("get_str_map()\n");
	i = -1;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		error_handler(OPEN_FAILED);
	ret = malloc(v_map->rows * sizeof(char **));
	if (!ret)
		error_handler(MALLOC_FAILED);
	while (++i < v_map->rows)
	{
		line = get_next_line(fd);
		ret[i] = ft_split(line, ' ');
		free(line);
	}
	close(fd);
	return (ret);
}

void	get_heights_colors(t_v_map *v_map, char ***str_map)
{
	int		i;
	int		j;

	printf("get_height_colors\n");
	i = -1;
	j = -1;
	v_map->vertices = malloc(v_map->rows * sizeof(t_vertex *));
	while (++i < v_map->rows)
	{
		v_map->vertices[i] = malloc(v_map->cols * sizeof(t_vertex));
		while (++j < v_map->cols)
		{
			v_map->vertices[i][j].height = ft_atoi(str_map[i][j]);
			v_map->vertices[i][j].color = \
				hex_to_color(ft_strchr(str_map[i][j], ','));
		}
		j = -1;
	}
}

int	hex_to_color(char *str)
{
	unsigned int	ret;
	char			*base;
	int				i;
	int				j;

	printf("hex_to_color()\n");
	if (!str)
		return (16777215);
	ret = 0;
	base = "123456789abcdef";
	i = 0;
	j = 0;
	str = str + 3;
	while (i < 6 && ft_strchr(base, ft_tolower(*(str + i))))
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
