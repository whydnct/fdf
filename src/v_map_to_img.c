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

	i = -1;
	j = -1;
	while (++i < bundle->v_map->rows)
	{
		while (++j < bundle->v_map->cols)
			choose_lines(bundle, i, j);
		j = -1;
	}
}

void	choose_lines(t_bundle *bundle, int i, int j)
{
	if (i < bundle->v_map->rows - 1)
		draw_line(bundle, i, j, 0);
	if (j < bundle->v_map->cols - 1)
		draw_line(bundle, i, j, 1);
}

void	draw_line(t_bundle *bundle, int i, int j, int dir)
{
	t_vertex	*start;
	t_vertex	*end;
	t_vertex	*swap;
	int			deltas[2];
	int			sense;

	start = &bundle->v_map->vertices[i][j];
	end = &bundle->v_map->vertices[i + (dir == 0)][j + (dir == 1)];
	if (start->y > end->y)
	{
		swap = start;
		start = end;
		end = swap;
	}
	deltas[0] = end->x - start->x;
	deltas[1] = end->y - start->y;
	sense = (deltas[0] > 0) - (deltas[0] < 0);
	deltas[0] *= sense;
	if (deltas[0] > deltas[1])
		plot_lineH(bundle, start, deltas, sense);
	else
		plot_lineV(bundle, start, deltas, sense);
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
	}
	else
		printf("out of bounds\n");
}

int	xy_within_limits(t_img *img, double x, double y)
{
	if (x < 0 || y < 0)
		return (0);
	if (x > img->width || y > img->height)
		return (0);
	return (1);
}

void	plot_lineH(t_bundle *bundle, t_vertex *start, int *deltas, int sense)
{
	int	pixel[2];
	int	deltas_2[2];
	int	error;

	pixel[0] = start->x;
	pixel[1] = start->y;
	deltas_2[0] = deltas[0] * 2;
	deltas_2[1] = deltas[1] * 2;
	error = deltas_2[1] - deltas[0];
	while (deltas[0]--)
	{
		if (error >= 0)
		{
			pixel[1]++;
			error -= deltas_2[0];
		}
		error += deltas_2[1];
		pixel[0] += sense;
		my_mlx_pixel_put(bundle->img, pixel[0], pixel[1], start->color);
	}
}

void	plot_lineV(t_bundle *bundle, t_vertex *start, int *deltas, int sense)
{
	int	pixel[2];
	int	deltas_2[2];
	int	error;

	pixel[0] = start->x;
	pixel[1] = start->y;
	deltas_2[0] = deltas[0] * 2;
	deltas_2[1] = deltas[1] * 2;
	error = deltas_2[0] - deltas[1];
	while (deltas[1]--)
	{
		if (error >= 0)
		{
			pixel[0] += sense;
			error -= deltas_2[1];
		}
		error += deltas_2[0];
		pixel[1]++;
		my_mlx_pixel_put(bundle->img, pixel[0], pixel[1], start->color);
	}
}

int	interpolate(int x, int span_x, int span_value)
{
	int	ret;

	ret = (span_value / span_x) * x;
	return (ret);
}
