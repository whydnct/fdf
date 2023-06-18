/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debuggers.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-m <aperez-m@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 17:37:16 by aperez-m          #+#    #+#             */
/*   Updated: 2023/06/18 09:42:18 by aperez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

void	write_vertices_to_image(t_bundle *bundle)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (++i < bundle->v_map->rows)
	{
		while (++j < bundle->v_map->cols)
		{
			my_mlx_pixel_put(bundle->img, \
				bundle->v_map->vertices[i][j].x, \
				bundle->v_map->vertices[i][j].y, \
				bundle->v_map->vertices[i][j].color);
		}
		j = -1;
	}
}

void	print_heights_colors(t_bundle *bundle)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	printf("printing heights\n");
	while (++i < bundle->v_map->rows)
	{
		while (++j < bundle->v_map->cols)
			printf("%d\t", bundle->v_map->vertices[i][j].height);
		printf("\n");
		j = -1;
	}
	i = -1;
	printf("\npriting colors\n");
	while (++i < bundle->v_map->rows)
	{
		while (++j < bundle->v_map->cols)
			printf("%d ", bundle->v_map->vertices[i][j].color);
		printf("\n");
		j = -1;
	}
}

void	print_x_y(t_bundle *bundle)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	printf("printing x values \n");
	while (++i < bundle->v_map->rows)
	{
		while (++j < bundle->v_map->cols)
		{
			printf("%d\t", (int)bundle->v_map->vertices[i][j].x);
			if (j == bundle->v_map->cols - 1)
				printf("\n");
		}
		j = -1;
	}
	i = -1;
	printf("\nprinting y values\n");
	while (++i < bundle->v_map->rows)
	{
		while (++j < bundle->v_map->cols)
		{
			printf("%d\t", (int)bundle->v_map->vertices[i][j].y);
			if (j == bundle->v_map->cols - 1)
				printf("\n");
		}
		j = -1;
	}
}

void	print_str_map(t_bundle *bundle, char ***str_map)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	printf("priting str_map\n");
	while (++i < bundle->v_map->rows)
	{
		while (str_map[i][++j] && str_map[i][j][0] != '\0')
			printf("str_map[%d][%d]: %s\n", i, j, str_map[i][j]);
		j = -1;
	}
}

void	split_unit_test(char **string)
{
	int		i;
	int		j;

	i = -1;
	j = -1;
	printf("size of the string: %ld\n", sizeof(string));
	while (string[++i])
	{
		while (string[i][++j])
			printf("%d\n", string[i][j]);	
		printf("%d\n", string[i][j]);
		j = -1;
	}
	printf("%d\n", i);
}

/*
void	traverse_map(int row_max, int col_max, void *f, void * params)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (++i < row_max)
	{
		while (++j < col_max)
			f(params);
		j = -1;
	}
}
*/