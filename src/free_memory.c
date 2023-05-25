/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-m <aperez-m@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 13:03:30 by aperez-m          #+#    #+#             */
/*   Updated: 2023/05/25 20:33:37 by aperez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

void	free_v_map(t_v_map *v_map)
{
	int	i;

	i = 0;
	while (i < v_map->rows)
		free(v_map->vertices[i]);
	free(v_map);
}

void	free_all(t_bundle *bundle)
{
	free(bundle->persp);
	free(bundle->v_map);
}