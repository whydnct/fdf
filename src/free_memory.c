/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-m <aperez-m@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 13:03:30 by aperez-m          #+#    #+#             */
/*   Updated: 2023/07/06 16:57:07 by aperez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

void	free_v_map(t_bundle *bundle)
{
	int	i;

	i = -1;
	if (bundle->allocs >= VTX_ALLOCD)
	{
		while (++i < bundle->v_map->rows)
			free(bundle->v_map->vtx[i]);
		free(bundle->v_map->vtx);
	}
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
	if (bundle->allocs >= VTX_ALLOCD)
		free_v_map(bundle);
	if (bundle->allocs >= PERSP_ALLOCD)
		free(bundle->persp);
	if (bundle->allocs >= STR_MAP_ALLOCD)
		free_str_map(bundle);
	if (bundle->allocs >= V_MAP_ALLOCD)
		free(bundle->v_map);
	if (bundle->allocs >= IMG_ALLOCD)
		free(bundle->img);
	free(bundle->mlx_inst);
}
