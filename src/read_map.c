/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-m <aperez-m@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 18:53:11 by aperez-m          #+#    #+#             */
/*   Updated: 2023/07/06 16:58:01 by aperez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

void	get_str_map_rows(char *file, t_bundle *bundle)
{
	int		fd;
	char	*line;

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
			line = purge_gnl(fd, &line);
	}
	close(fd);
}

void	get_str_map(char *file, t_bundle *bundle)
{
	int		fd;
	int		i;
	char	*line;

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

	i = -1;
	j = -1;
	bundle->v_map->vtx = malloc(bundle->v_map->rows * sizeof(t_vertex *));
	if (!bundle->v_map->vtx)
		quit(bundle, EXIT_FAILURE);
	bundle->allocs = VTX_ALLOCD;
	while (++i < bundle->v_map->rows)
	{
		bundle->v_map->vtx[i] = malloc(bundle->v_map->cols * sizeof(t_vertex));
		if (!bundle->v_map->vtx[i])
		{
			bundle->v_map->rows = i;
			quit(bundle, EXIT_FAILURE);
		}
		while (++j < bundle->v_map->cols)
		{
			bundle->v_map->vtx[i][j].height = ft_atoi(bundle->str_map[i][j]);
			bundle->v_map->vtx[i][j].color = \
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
		return (0xffffff);
	ret = 0;
	base = "0123456789abcdef";
	i = 0;
	j = 0;
	str = str + 3;
	while (i < 6 && str[i] && ft_strchr(base, str[i]))
	{
		while (base[j] && (base[j] != str[i]))
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
