/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project_v_map_spans.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-m <aperez-m@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 18:52:42 by aperez-m          #+#    #+#             */
/*   Updated: 2023/06/26 17:26:07 by aperez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

void	get_span_v(t_v_map *v_map)
{
	v_map->span_v = get_y_max(v_map) - get_y_min(v_map);
	printf("vertical span: %f\n", v_map->span_v);
}

double	get_y_max(t_v_map *v_map)
{
	double	ret;
	int		i;
	int		j;

	i = -1;
	j = -1;
	ret = v_map->vtx[0][0].y;
	while (++i < v_map->rows)
	{
		while (++j < v_map->cols)
		{
			if (ret < v_map->vtx[i][j].y)
				ret = v_map->vtx[i][j].y;
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
	ret = v_map->vtx[0][0].y;
	while (++i < v_map->rows)
	{
		while (++j < v_map->cols)
		{
			if (ret > v_map->vtx[i][j].y)
				ret = v_map->vtx[i][j].y;
		}
		j = -1;
	}
	return (ret);
}

void	get_span_h(t_v_map *v_map)
{
	v_map->span_h = \
		v_map->vtx[0][v_map->cols - 1].x \
		- v_map->vtx[v_map->rows - 1][0].x;
	printf("horizontal: %f\n", v_map->span_h);
}
