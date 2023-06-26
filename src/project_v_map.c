/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project_v_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-m <aperez-m@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 18:31:14 by aperez-m          #+#    #+#             */
/*   Updated: 2023/06/26 19:00:22 by aperez-m         ###   ########.fr       */
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
			v_map->vtx[i][j].x = \
				j * persp->col_x + i * persp->row_x;
			v_map->vtx[i][j].y = \
				j * persp->col_y + i * persp->row_y \
				+ v_map->vtx[i][j].height * persp->height_y;
		}
		j = -1;
	}
	printf("transformed to new perspective \n");
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
			v_map->vtx[i][j].x *= 0.9 * v_map->pps;
			v_map->vtx[i][j].y *= 0.9 * v_map->pps;
		}
		j = -1;
	}
	get_span_v(v_map);
}

void	get_max_pps(t_v_map *v_map, t_img *img)
{
	double	slenderness_map;
	double	slenderness_img;

	slenderness_map = v_map->span_v / v_map->span_h;
	slenderness_img = img->height / img->width ;
	if (slenderness_map >= slenderness_img)
		v_map->pps = (double)img->height / v_map->span_v;
	else
		v_map->pps = (double)img->width / v_map->span_h;
	printf("max_pps: %f\n", v_map->pps);
}
