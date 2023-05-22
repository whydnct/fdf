/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perspective.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-m <aperez-m@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 06:06:44 by aperez-m          #+#    #+#             */
/*   Updated: 2023/05/21 19:49:19 by aperez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

void	to_new_perspective(t_v_map *v_map, t_view *view)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < v_map->rows)
	{
		while (j < v_map->cols)
		{
			v_map->vertices[i][j]->x = (v_map->vertices[i][j]->col \
				* view->col_x + v_map->vertices[i][j]->row * view->row_x);
			v_map->vertices[i][j]->y = (v_map->vertices[i][j]->col \
				* view->col_y + v_map->vertices[i][j]->row * view->row_y \
				+ v_map->vertices[i][j]->height * view->height_y);
			j++;
		}
		j = 0;
		i++;
	}
}

void	get_span_v(t_v_map *v_map)
{
	int	max;
	int	min;
	int	i;
	int	j;

	i = 0;
	j = 0;
	max = v_map->vertices[0][0]->y;
	min = max;
	while (i < v_map->rows)
	{
		while (j < v_map->cols)
		{
			if (max < v_map->vertices[i][j]->y)
				max = v_map->vertices[i][j]->y;
			if (min > v_map->vertices[i][j]->y)
				min = v_map->vertices[i][j]->y;
			j++;
		}
		j = 0;
		i++;
	}
	v_map->span_v = max - min;
}

void	get_span_h(t_v_map *v_map, t_view *view)
{
	v_map->span_h = v_map->cols * view->col_x \
		- v_map->rows * view->row_x;
}

void	get_max_pps(t_v_map *v_map, int img_width, int img_height)
{
	if (v_map->span_h * img_height < img_width * v_map->span_v)
		v_map->pps = img_height / v_map->span_v;
	else
		v_map->pps = img_width / v_map->span_h;
}

void	scale_v_map(t_v_map *v_map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < v_map->rows)
	{
		while (j < v_map->cols)
		{
			v_map->vertices[i][j]->x *= v_map->pps;
			v_map->vertices[i][j]->y = v_map->pps;
			j++;
		}
		j = 0;
		i++;
	}
}

void	get_offset(t_v_map *v_map, int img_width, int img_height)
{
	v_map->offset_h = (img_width - v_map->pps * v_map->span_h) / 2;
	v_map->offset_v = (img_height - v_map->pps * v_map->span_v) / 2;
}

void	center_v_map(t_v_map *v_map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < v_map->rows)
	{
		while (j < v_map->cols)
		{
			v_map->vertices[i][j]->x += v_map->offset_h;
			v_map->vertices[i][j]->y += v_map->offset_v;
			j++;
		}
		j = 0;
		i++;
	}
}

void	re_scale_v_map(t_v_map *v_map, double zoom, int img_w, int img_h)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < v_map->rows)
	{
		while (j < v_map->cols)
		{
			v_map->vertices[i][j]->x = zoom * \
				(v_map->vertices[i][j]->x - img_w);
			v_map->vertices[i][j]->y = zoom * \
				(v_map->vertices[i][j]->y - img_h);
			j++;
		}
		j = 0;
		i++;
	}
}
