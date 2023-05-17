/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_to_window.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-m <aperez-m@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 19:44:56 by aperez-m          #+#    #+#             */
/*   Updated: 2023/05/17 21:40:30 by aperez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

void	write_v_map_to_image(t_data *data, t_v_map *v_map)
{
	int i;
	int j;
	
	i = 0;
	j = 0;
	while (i < v_map->rows)
	{
		while (j < v_map->cols)
		{
			if (j < v_map->cols - 1)
				draw_line(data, v_map->vertices[i][j], v_map->vertices[i][j + 1]);
			if (i < v_map->rows - 1)
				draw_line(data, v_map->vertices[i][j], v_map->vertices[i + 1][j]);
			my_mlx_pixel_put(data, v_map->vertices[i][j]->x, \
				v_map->vertices[i][j]->y, v_map->vertices[i][j]->color);
			j++;
		}
		j = 0;
		i++;
	}
}

void	draw_line(t_data *data, t_vertex *start, t_vertex *end)
{
	int	x;
	int	y;
	int color;

	x = start->x;

	while (++x < end->x)
	{
		y = interpolate(x, *start->x, *start->y, *end->x, *end->y);
		color = interpolate(x, *start->x, *end->x, *start->color, *end->color);
		my_mlx_pixel_put(data, x, y, color);
	}
}

int	interpolate(int x, int st_x, int st_value, int end_x, int end_value)
{
	int	ret;

	ret = (end_value - st_value) / (end_x - st_x) \ 
		* (x - st_x) + st_value;
	return (ret);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
