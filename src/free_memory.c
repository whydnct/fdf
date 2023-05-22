/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-m <aperez-m@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 13:03:30 by aperez-m          #+#    #+#             */
/*   Updated: 2023/05/21 18:50:10 by aperez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

void	free_t_vertex(t_v_map *v_map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < v_map->rows)
	{
		while (j < v_map->cols)
			free(&(v_map->vertices[i][j]));
		free(v_map->vertices[i]);
	}
	free(v_map->vertices);
	free(v_map);
}