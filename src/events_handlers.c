/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-m <aperez-m@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 05:50:40 by aperez-m          #+#    #+#             */
/*   Updated: 2023/05/21 19:39:21 by aperez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

int exit_on_esc(int keycode, void *data, t_v_map *v_map, void *mlx, void *mlx_win)
{
	if (keycode == 0xff1b)
	{
		free_t_vertex(v_map);
		mlx_destroy_image(mlx, data);
		mlx_destroy_window(mlx, mlx_win);
		exit(1);
	}
	return (0);
}
