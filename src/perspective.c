/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perspective.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-m <aperez-m@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 06:06:44 by aperez-m          #+#    #+#             */
/*   Updated: 2023/06/18 16:54:17 by aperez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

void	init_persp(t_bundle *bundle)
{
	bundle->persp = malloc(sizeof(t_persp));
	bundle->persp->col_x = COL_2_X;
	bundle->persp->row_x = ROW_2_X;
	bundle->persp->col_y = COL_2_Y;
	bundle->persp->row_y = ROW_2_Y;
	bundle->persp->height_y = HEIGHT_2_Y;
}

void	to_new_perspective(t_v_map *v_map, t_persp *persp)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (++i < v_map->rows)
	{
		while (++j < v_map->cols)
		{
			v_map->vertices[i][j].x = \
				j * persp->col_x + i * persp->row_x;
			v_map->vertices[i][j].y = \
				j * persp->col_y + i * persp->row_y \
				+ v_map->vertices[i][j].height * persp->height_y;
		}
		j = -1;
	}
	printf("transformed to new perspective \n");
}

void	get_span_v(t_v_map *v_map)
{
	v_map->span_v = get_y_max(v_map) - get_y_min(v_map);
	printf("vertical span: %d\n", v_map->span_v);
}

double	get_y_max(t_v_map *v_map)
{
	double	ret;
	int		i;
	int		j;

	i = -1;
	j = -1;
	ret = v_map->vertices[0][0].y;
	while (++i < v_map->rows)
	{
		while (++j < v_map->cols)
		{
			if (ret < v_map->vertices[i][j].y)
				ret = v_map->vertices[i][j].y;
		}
		j = -1;
	}
	return (ret);
}

double	get_y_min(t_v_map *v_map)
{
	double	ret;
	int		i;
	int		j;

	i = -1;
	j = -1;
	ret = v_map->vertices[0][0].y;
	while (++i < v_map->rows)
	{
		while (++j < v_map->cols)
		{
			if (ret > v_map->vertices[i][j].y)
				ret = v_map->vertices[i][j].y;
		}
		j = -1;
	}
	return (ret);
}

void	get_span_h(t_v_map *v_map)
{
	v_map->span_h = \
		v_map->vertices[0][v_map->cols - 1].x \
		- v_map->vertices[v_map->rows - 1][0].x;
	printf("horizontal: %d\n", v_map->span_h);
}

void	get_max_pps(t_v_map *v_map, t_img * img)
{
	double	slenderness_map;
	double	slenderness_img;

	slenderness_map = v_map->span_h / v_map->span_v;
	slenderness_img = img->width / img->height;
	if (slenderness_map >= slenderness_img)
		v_map->pps = img->height / v_map->span_v;
	else
		v_map->pps = img->width / v_map->span_h;
	printf("max_pps: %f\n", v_map->pps);
}

void	scale_v_map(t_v_map *v_map)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (++i < v_map->rows)
	{
		while (++j < v_map->cols)
		{
			v_map->vertices[i][j].x *= 0.9 * v_map->pps;
			v_map->vertices[i][j].y *= 0.9 * v_map->pps;
		}
		j = -1;
	}
	get_span_v(v_map);
}

void	get_offset(t_bundle *bundle)
{
	double	x_max;
	double	x_min;

	x_max = bundle->v_map->vertices[0][bundle->v_map->cols - 1].x;
	x_min = bundle->v_map->vertices[bundle->v_map->rows - 1][0].x;
	bundle->v_map->offset_h = 0.5 * \
		(bundle->img->width - x_max - x_min);
	bundle->v_map->offset_v = 0.5 * \
		(bundle->img->height \
		- get_y_min(bundle->v_map) \
		- get_y_max(bundle->v_map));
	printf("y_max: %f\ny_min: %f\n", \
		get_y_max(bundle->v_map), \
		get_y_min(bundle->v_map));
	printf("x_max: %f\nx_min: %f\n", x_max, x_min);
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
			v_map->vertices[i][j].x += v_map->offset_h;
			v_map->vertices[i][j].y += v_map->offset_v;
			j++;
		}
		j = 0;
		i++;
	}
	printf("y_max: %f\ny_min: %f\n", get_y_max(v_map), get_y_min(v_map));
	printf("x_max: %f\nx_min: %f\n", v_map->vertices[0][v_map->cols - 1].x,
		v_map->vertices[v_map->rows - 1][0].x);
}

/*
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
			v_map->vertices[i][j].x = zoom * \
				(v_map->vertices[i][j].x - img_w);
			v_map->vertices[i][j].y = zoom * \
				(v_map->vertices[i][j].y - img_h);
			j++;
		}
		j = 0;
		i++;
	}
}
*/