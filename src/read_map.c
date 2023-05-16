/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-m <aperez-m@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 13:05:23 by aperez-m          #+#    #+#             */
/*   Updated: 2023/05/15 13:38:45 by aperez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

void get_str_map_rows(char *file, t_v_map *v_map)
{
	int	fd;
	int	temp;
    
	fd = open(file, O_READONLY);
    while(get_next_line(fd))
        temp++;
    if (!ret)
        error_handler(EMPTY_FILE);
	close(fd);
	*v_map->rows = temp;
}

char	***get_str_map(char *file, t_v_map *v_map)
{
	char ***ret;
	int	fd;
	int  i;

	i = -1;
	fd = open(file, O_READONLY);
	ret = malloc(*v_map->rows*sizeof(char **));
	while (++i < *v_map->rows)
		ret[i] = ft_split(get_next_line(fd), ' ');
	close(file);
	return (ret); 
}

void get_str_map_cols(t_v_map *v_map, char ****str_map)
{
	int	cols;
    int i;
	int	j;
    int temp;

    cols = 0;
    i = 0;
	j = 0;
	temp = 0;
    while(i < *v_map->rows)
    {
		while(*str_map[i][j][0])
			j++;
		temp = j;
        if (cols < temp)
			cols = temp;
		j = 0;
		i++;
    }
	*v_map->cols = cols;
}
unsigned int	get_color(char *str, int offset)
{
	unsigned int	ret;
	char			*base;
	int				i;
	int				j;
	
	ret = 0;
	base = "123456789abcdef";
	i = 0;
	j = 0;
	while(i < 2)
	{
		while(base[j] != ft_tolower(*(str + offset + i)))
		{
			j++;
			if (j == 16)
				error_handler(WRONG_COLOR_CODE);
		}
		ret = j * 16 * (2 - i);
		j = 0;
		i++;
	}
}

void	get_heights_colors(t_v_map *v_map, char ****str_map)
{
    int	i;
	int	j;
	
	i = 0;
	j = 0;
	v_map->vertices = malloc(map->rows * sizeof(t_vertex*));
	while (i < map->rows)
	{
		v_map->vertices[i] = malloc(*v_map->cols * sizeof(t_vertex));
		while (j < map->columns)
		{
			*v_map->vertices[i][j]->height = ft_atoi((*str_map)[i][j]);
			*v_map->vertices[i][j]->R = get_color(ft_strchr((*str_map)[i][j], ','), R_OFFSET);
			*v_map->vertices[i][j]->G = get_color(ft_strchr((*str_map)[i][j], ','), G_OFFSET);
			*v_map->vertices[i][j]->B = get_color(ft_strchr((*str_map)[i][j], ','), B_OFFSET);
			*v_map->vertices[i][j]->A = get_color(ft_strchr((*str_map)[i][j], ','), A_OFFSET);
			j++;
		}
		j = 0;
		i++;
	}
}