/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_to_window.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-m <aperez-m@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 19:44:56 by aperez-m          #+#    #+#             */
/*   Updated: 2023/05/21 12:21:58by aperez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

void	write_v_map_to_image(t_bundle *bundle)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < bundle->v_map->rows)
	{
		while (j < bundle->v_map->cols)
		{
/**			if (j < v_map->cols - 1)
				draw_line(img, &v_map->vertices[i][j], \
					&v_map->vertices[i][j + 1]);
			if (i < v_map->rows - 1)
				draw_line(img, &v_map->vertices[i][j], \
					&v_map->vertices[i + 1][j]);
*/
			my_mlx_pixel_put(bundle->img,\
				bundle->v_map->vertices[i][j].x, \
				bundle->v_map->vertices[i][j].y, \
				bundle->v_map->vertices[i][j].color);
			printf("%c", \
				'\n'*(j == bundle->v_map->cols - 1 ) + \
				'\t'*(j != bundle->v_map->cols));
			j++;
		}
		j = 0;
		i++;
	}
}

void	draw_line(t_img *img, t_vertex *start, t_vertex *end)
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
		my_mlx_pixel_put(img, start->x + x, y, color);
	}
}

int	interpolate(int x, int span_x, int span_value)
{
	int	ret;

	ret = (span_value / span_x) * x;
	return (ret);
}

void	my_mlx_pixel_put(t_img *img, double x, double y, int color)
{
	char	*dst;
	int		offset;

	if (xy_within_limits(img, x, y))
	{
		offset = (int)(y * img->line_length \
			+ x * (img->bits_per_pixel / 8));
		dst = img->addr + offset;
		*(unsigned int *)dst = color;
		//printf("%d,%d\t", (int)x, (int)y);
		//printf("%d " , offset);
		printf("%p ", dst);
	}
}

int	xy_within_limits(t_img *img, double x, double y)
{
	if (x < 0 || y < 0)
		return (0);
	if (x > img->width || y > img->height)
		return (0);
	return (1);
}
/*void	plot_line(t_data *data, t_vertex *start, t_vertex *end)
{
	t_vertex	*swap;
	int			deltas[2];

	if (start->y > end->y)
	{
		swap = start;
		start = end;
		end = swap;
	}
	deltas[0] = end->x - start->x;
	deltas[1] = end->y - start->y;
	if (deltas[0] > 0)
	{
		if (deltas[0] > deltas[1])
			plot_lineH(data, start, deltas, 1);
		else
			plot_lineV(data, start, deltas, 1);
	}
	else
	{
		deltas[0] = -deltas[0];
		if (deltas[0] > deltas[1])
			plot_lineH(data, start, deltas, -1);
		else
			plot_lineV(data, start, deltas, -1);
	}
}

void	plot_lineH(t_data *data, t_vertex *start, int *deltas, int dir)
{
	int	pixel[2];
	int	deltas_x2;
	int	deltas_y2;
	int	error;

	pixel[0] = start->x;
	pixel[1] = start->y;
	deltas_x2 = deltas[0] * 2;
	deltas_y2 = deltas[1] * 2;
	error = deltas_y2 - deltas[0];

	while (deltas[0]--)
	{
		if (error >= 0)
		{
			pixel[1]++;
			error -= deltas_x2;
		}
		error += deltas_y2;
		pixel[0] += dir;
		my_mlx_pixel_put(data, pixel[0], pixel[1], start->color);
	}
}

void	plot_lineV(t_data *data, t_vertex *start, int *deltas, int const dir)
{
	int	pixel[2];
	int	deltas_x2;
	int	deltas_y2;
	int	error;

	pixel[0] = start->x;
	pixel[1] = start->y;
	deltas_x2 = deltas[0] * 2;
	deltas_y2 = deltas[1] * 2;
	error = deltas_x2 - deltas[1];
	while (deltas[1]--)
	{
		if (error >= 0)
		{
			pixel[0] += dir;
			error -= deltas_y2;
		}
		error += deltas_x2;
		pixel[1]++;
		my_mlx_pixel_put(data, pixel[0], pixel[1], start->color);
	}
}
*/