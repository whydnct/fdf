/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_to_window.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-m <aperez-m@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 19:44:56 by aperez-m          #+#    #+#             */
/*   Updated: 2023/05/18 21:05:31 by aperez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

void	write_v_map_to_image(t_data *data, t_v_map *v_map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < v_map->rows)
	{
		while (j < v_map->cols)
		{
			if (j < v_map->cols - 1)
				draw_line(data, v_map->vertices[i][j], \
					v_map->vertices[i][j + 1]);
			if (i < v_map->rows - 1)
				draw_line(data, v_map->vertices[i][j], \
					v_map->vertices[i + 1][j]);
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
	int	color;

	x = 0;
	while (++x < end->x - start->x)
	{
		y = start->y + interpolate(x, end->x - start->x, end->y - start->y);
		color = start->color \
			+ interpolate(x, end->x - start->x, end->color - start->color);
		my_mlx_pixel_put(data, start->x + x, y, color);
	}
}

int	interpolate(int x, int span_x, int span_value)
{
	int	ret;

	ret = (span_value / span_x) * x;
	return (ret);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
