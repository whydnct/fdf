/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertex_to_img.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-m <aperez-m@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 06:06:44 by aperez-m          #+#    #+#             */
/*   Updated: 2023/05/15 06:52:20 by aperez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

void	to_new_perspective(t_v_map *v_map, t_view *view)
{
	int	i[2];
	
	i[0] = 0;
	i[1] = 0;
	while (i[0] < *v_map->rows)
	{
		while (i[1] < *v_map->cols)
		{
			*v_map->vertices[i[0]][i[1]]->x = (*v_map->vertices[i[0]][i[1]]->col \
				* *view->col_x + *v_map->vertices[i[0]][i[1]]->row *view->row_x);
			*v_map->vertices[i[0]][i[1]]->y = (*v_map->vertices[i[0]][i[1]]->col \
				* *view->col_y + *v_map->vertices[i[0]][i[1]]->row * *view->row_y \
				+ *v_map->vertices[i[0]][i[1]]->height * *view->height_y);
			i[1]++;
		}
		i[1] = 0;
		i[0]++;
	}
}

void	get_span_v(t_v_map *v_map)
{
	int	max;
	int min;
	int i[2];

	i[0] = 0;
	i[1] = 0;
	max = v_map->vertices[0][0];
	min = max;
	while (i[0] < *v_map->rows)
	{
		while (i[1] < *v_map->cols)
		{
			if (max < v_map->vertices[i][j])
				max = v_map->vertices[i][j];
			if (min > v_map->vertices[i][j])
				min = v_map->vertices[i][j]);
			i[1]++;
		}
		i[1] = 0;
		i[0]++;	
	}
	*vertex_map->span_v = max - min;
}

void	get_span_h(t_v_map *v_map, t_view *view)
{
	*v_map->span_h = *v_map->cols * *view->col_x \
		- *v_map->rows * *view->row_x;
}

void	get_max_pps(t_v_map *v_map, int img_width, int img_height)
{
	if (span_h * img_height < with * span_v)
		*v_map->pps = img_height / *v_map->span_v;
	else
		*v_map->pps = img_width / *v_map->span_h;
}

void	scale_v_map(t_v_map *v_map)
{
	int	i[2];

	i[0] = 0;
	i[1] = 0;
	while(i[0] < v_map->rows)
	{
		while(i[1] < v_map->cols)
		{
			*v_map->vertices[i[0]][i[1]]->x *= *s_v_map->pps;
			*v_map->vertices[i[0]][i[1]]->y = *s_v_map->pps;
			i[1]++;
		}
		i[1] = 0;
		i[0]++;
	}
}

void	get_offset(t_v_map *v_map, int img_width, int img_height)
{
	*v_map->offset_h = (img_width - *v_map->pps * *v_map->span_h) / 2;
	*v_map->offset_v = (img_height - *v_map->pps * *v_map->span_v) / 2; 
}

void	center_v_map(t_v_map *v_map)
{
	int	i[2];

	i[0] = 0;
	i[1] = 0;
	while(i[0] < v_map->rows)
	{
		while(i[1] < v_map->cols)
		{
			*v_map->vertices[i[0]][i[1]]->x += *v_map->offset_h;
			*v_map->vertices[i[0]][i[1]]->y += *v_map->offset_v;
			i[1]++;
		}
		i[1] = 0;
		i[0]++;
	}
}

void	re_scale_v_map(t_v_map *v_map, double zoom, int img_width, int img_height)
{
	int	i[2];

	i[0] = 0;
	i[1] = 0;
	while(i[0] < v_map->rows)
	{
		while(i[1] < v_map->cols)
		{
			*v_map->vertices[i[0]][i[1]]->x = zoom * \
				(*v_map->vertices[i[0]][i[1]]->x - img_width);
			*v_map->vertices[i[0]][i[1]]->y = zoom * \
				(*v_map->vertices[i[0]][i[1]]->y - img_height);
			i[1]++;
		}
		i[1] = 0;
		i[0]++;
	}
}