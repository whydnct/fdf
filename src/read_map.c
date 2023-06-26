/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-m <aperez-m@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 13:05:23 by aperez-m          #+#    #+#             */
/*   Updated: 2023/06/23 17:15:29by aperez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

void	get_str_map_rows(char *file, t_bundle *bundle)
{
	int		fd;
	char	*line;

	printf("get_str_map_rows()\n");
	fd = open(file, O_RDONLY);
	if (fd < 0)
		quit(bundle, EXIT_FAILURE);
	line = sanitize_line(get_next_line(fd));
	if (!line)
		quit(bundle, EXIT_SUCCESS);
	bundle->v_map->rows = 0;
	while (line)
	{
		bundle->v_map->rows++;
		bundle->v_map->cols = get_line_cols(line, ' ');
		free(line);
		line = sanitize_line(get_next_line(fd));
		if (line && (bundle->v_map->cols != get_line_cols(line, ' ')))
		{
			ft_putstr_fd("VARIABLE_ROW_LENGTH\n", 2);
			break ;
		}
	}
	free(line);
	close(fd);
}

void	get_str_map(char *file, t_bundle *bundle)
{
	int		fd;
	int		i;
	char	*line;

	printf("get_str_map()\n");
	bundle->str_map = NULL;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		quit(bundle, EXIT_FAILURE);
	bundle->str_map = malloc((bundle->v_map->rows + 1) * sizeof(char **));
	if (!bundle->str_map)
		quit(bundle, EXIT_FAILURE);
	bundle->allocs = STR_MAP_ALLOCD;
	i = -1;
	while (++i < bundle->v_map->rows)
	{
		line = sanitize_line(get_next_line(fd));
		bundle->str_map[i] = ft_split(line, ' ');
		free(line);
	}
	close(fd);
	bundle->str_map[bundle->v_map->rows] = NULL;
}

void	get_heights_colors(t_bundle *bundle)
{
	int		i;
	int		j;

	printf("get_height_colors\n");
	i = -1;
	j = -1;
	bundle->v_map->vertices = malloc(bundle->v_map->rows * sizeof(t_vertex *));
	if (!bundle->v_map->vertices)
		quit(bundle, EXIT_FAILURE);
	bundle->allocs = VERTICES_ALLOCD;
	while (++i < bundle->v_map->rows)
	{
		bundle->v_map->vertices[i] = \
			malloc(bundle->v_map->cols * sizeof(t_vertex));
		if (!bundle->v_map->vertices[i])
		{
			bundle->v_map->rows = i;
			quit(bundle, EXIT_FAILURE);
		}
		while (++j < bundle->v_map->cols)
		{
			bundle->v_map->vertices[i][j].height = \
				ft_atoi(bundle->str_map[i][j]);
			bundle->v_map->vertices[i][j].color = \
				hex_to_color(ft_strchr(bundle->str_map[i][j], ','));
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

	if (!str)
		return (16777215);
	ret = 0;
	base = "123456789abcdef";
	i = 0;
	j = 0;
	str = str + 3;
	while (i < 6 && ft_strchr(base, str[i]))
	{
		while (base[j] != str[i])
			j++;
		ret = ret * 16 + j;
		j = 0;
		i++;
	}
	return (ret);
}

char	*sanitize_line(char *line)
{
	int		i;
	char	*valid_chars;

	if (!line)
		return (NULL);
	valid_chars = "abcdefx ,-";
	i = -1;
	while (line[++i])
	{
		line[i] = ft_tolower(line[i]);
		if (!ft_isdigit(line[i]) && !ft_strchr(valid_chars, line[i]))
			line[i] = ' ';
	}
	return (line);
}
