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
	printf("horizontal: %f\n", v_map->span_h);
}
