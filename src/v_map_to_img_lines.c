/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_map_to_img_lines.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-m <aperez-m@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 16:12:32 by aperez-m          #+#    #+#             */
/*   Updated: 2023/06/19 18:40:31 by aperez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

void	choose_lines(t_bundle *bundle, int i, int j)
{
	if (i < bundle->v_map->rows - 1)
		draw_line(bundle, i, j, 0);
	if (j < bundle->v_map->cols - 1)
		draw_line(bundle, i, j, 1);
}

void	draw_line(t_bundle *bundle, int i, int j, int dir)
{
	t_vertex	*nodes[2];
	t_vertex	*swap;
	int			deltas[2];
	int			sense;

	nodes[0] = &bundle->v_map->vertices[i][j];
	nodes[1] = &bundle->v_map->vertices[i + (dir == 0)][j + (dir == 1)];
	if (nodes[0]->y > nodes[1]->y)
	{
		swap = nodes[0];
		nodes[0] = nodes[1];
		nodes[1] = swap;
	}
	deltas[0] = nodes[1]->x - nodes[0]->x;
	deltas[1] = nodes[1]->y - nodes[0]->y;
	sense = (deltas[0] > 0) - (deltas[0] < 0);
	deltas[0] *= sense;
	if (deltas[0] > deltas[1])
		plot_line_h(bundle, nodes, deltas, sense);
	else
		plot_line_v(bundle, nodes, deltas, sense);
}

void	plot_line_h(t_bundle *bundle, t_vertex **nodes, int *deltas, int sense)
{
	int	pixel[2];
	int	deltas_2[2];
	int	error;

	pixel[0] = nodes[0]->x;
	pixel[1] = nodes[1]->y;
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
		my_mlx_pixel_put(bundle->img, pixel[0], pixel[1], \
			get_color(nodes[0], nodes[1], deltas));
	}
}

void	plot_line_v(t_bundle *bundle, t_vertex **nodes, int *deltas, int sense)
{
	int	pixel[2];
	int	deltas_2[2];
	int	error;

	pixel[0] = nodes[0]->x;
	pixel[1] = nodes[0]->y;
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
		my_mlx_pixel_put(bundle->img, pixel[0], pixel[1], \
			get_color(nodes[0], nodes[1], deltas));
	}
}
