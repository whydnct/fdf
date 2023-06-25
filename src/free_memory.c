/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-m <aperez-m@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 13:03:30 by aperez-m          #+#    #+#             */
/*   Updated: 2023/06/25 20:20:27 by aperez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

void	free_v_map(t_v_map *v_map)
{
	int	i;

	i = -1;
	while (++i < v_map->rows)
		free(v_map->vertices[i]);
	free(v_map->vertices);
	free(v_map);
}

void	free_str_map(t_bundle *bundle)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (bundle->str_map[++i])
	{
		while (bundle->str_map[i][++j])
			free(bundle->str_map[i][j]);
		j = -1;
	}
}

void	free_all(t_bundle *bundle)
{
	free(bundle->persp);
	free(bundle->img);
	if (bundle->str_map)
		free_str_map(bundle);
	if (bundle->v_map)
		free_v_map(bundle->v_map);
	printf("memory freed\n");
	free(bundle->mlx_inst);
}
