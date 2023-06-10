/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debuggers.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-m <aperez-m@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 17:37:16 by aperez-m          #+#    #+#             */
/*   Updated: 2023/06/10 10:07:00 by aperez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"


void	print_heights_colors(t_bundle *bundle)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < bundle->v_map->rows)
	{
		while (j < bundle->v_map->cols)
		{
			printf("%d\t", bundle->v_map->vertices[i][j].height);
			if (j == bundle->v_map->cols - 1)
				printf("\n");
			j++;
		}
		j = 0;
		i++;
	}
	i = 0;
	printf("\n");
	while (i < bundle->v_map->rows)
	{
		while (j < bundle->v_map->cols)
		{
			printf("%d ", bundle->v_map->vertices[i][j].color);
			if (j == bundle->v_map->cols - 1)
				printf("\n");
			j++;
		}
		j = 0;
		i++;
	}
}


void	write_vertices_to_image(t_bundle *bundle)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < bundle->v_map->rows)
	{
		while (j < bundle->v_map->cols)
		{
		/*	my_mlx_pixel_put(bundle->img, \
				bundle->v_map->vertices[i][j].x, \
				bundle->v_map->vertices[i][j].y, \
				//bundle->v_map->vertices[i][j].color);
				0x00FF0000);
		*/	my_mlx_pixel_put(bundle->img, \
				5, \
				5, \
				0x00FF0000);
			j++;
		}
		j = 0;
		i++;
	}
}

void	print_x_y(t_bundle *bundle)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < bundle->v_map->rows)
	{
		while (j < bundle->v_map->cols)
		{
			printf("%d\t", (int)bundle->v_map->vertices[i][j].x);
			if (j == bundle->v_map->cols - 1)
				printf("\n");
			j++;
		}
		j = 0;
		i++;
	}
	i = 0;
	printf("\n");
	while (i < bundle->v_map->rows)
	{
		while (j < bundle->v_map->cols)
		{
			printf("%d\t", (int)bundle->v_map->vertices[i][j].y);
			if (j == bundle->v_map->cols - 1)
				printf("\n");
			j++;
		}
		j = 0;
		i++;
	}
}
