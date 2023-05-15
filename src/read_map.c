/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-m <aperez-m@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 13:05:23 by aperez-m          #+#    #+#             */
/*   Updated: 2023/05/15 07:27:02 by aperez-m         ###   ########.fr       */
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

int get_map_cols(int fd, t_map *map)
{
    int ret;
    int i;
    int temp;

    ret = 0;
    i = 0;
	temp = 0;
    while(i < map->rows)
    {
		temp = get_next_line(fd);
        if (ret < temp)
			ret = temp;
    }
	return (ret);
}

char	***get_str_map(char *file, t_v_map *v_map)
{
	char ***ret;
	int	fd;
	int  i;

	i = -1;
	fd = open(file, O_READONLY);
	ret = malloc((1 + *v_map->rows)*sizeof(char **));
	while (++i < *v_map->rows)
		ret[i] = ft_split(get_next_line(fd), ' ');
	close(file);
	return (ret); 
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
		ret = j * 16 * (1 - i);
		j = 0;
		i++;
	}
}

//map of chars -> map with heights and colors
//TODO: free in malloc error
t_vertex **get_map_int(char ****map_chars, t_map *map)
{
	t_vertex	**ret;
    int				i;
    int				j;
	
	i = 0;
    j = 0;
	ret = malloc(map->rows * sizeof(t_vertex));
	while (i < map->rows)
	{
		ret[i] = malloc(map->columns * sizeof(t_vertex));
		while (j < map->columns)
        {
			ret[i][j].height = ft_atoi((**map_chars)[i][j]);
			ret[i][j].R = get_color(ft_strchr((**map_chars)[i][j], ','), R_OFFSET);
			ret[i][j].G = get_color(ft_strchr((**map_chars)[i][j], ','), G_OFFSET);
			ret[i][j].B = get_color(ft_strchr((**map_chars)[i][j], ','), B_OFFSET);
			ret[i][j].A = get_color(ft_strchr((**map_chars)[i][j], ','), A_OFFSET);
			j++;
        }
        j = 0;
        i++;
	}
	return (ret);
}