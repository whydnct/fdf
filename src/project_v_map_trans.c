/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project_v_map_trans.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-m <aperez-m@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 18:31:14 by aperez-m          #+#    #+#             */
/*   Updated: 2023/07/06 16:57:44 by aperez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

void	center_v_map(t_v_map *v_map)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (++i < v_map->rows)
	{
		while (++j < v_map->cols)
		{
			v_map->vtx[i][j].x += v_map->offset_h;
			v_map->vtx[i][j].y += v_map->offset_v;
		}
		j = -1;
	}
}

void	get_offset(t_bundle *bundle)
{
	double	x_max;
	double	x_min;

	x_max = bundle->v_map->\
		vtx[bundle->v_map->rows - 1][bundle->v_map->cols - 1].x;
	x_min = bundle->v_map->vtx[0][0].x;
	bundle->v_map->offset_h = 0.5 * \
		(bundle->img->width - x_max - x_min);
	bundle->v_map->offset_v = 0.5 * \
		(bundle->img->height \
		- get_y_min(bundle->v_map) \
		- get_y_max(bundle->v_map));
}
