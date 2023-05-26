/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-m <aperez-m@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 05:50:40 by aperez-m          #+#    #+#             */
/*   Updated: 2023/05/27 00:19:58 by aperez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

int	exit_on_esc(int keycode, t_bundle *bundle)
{
	if (keycode == XK_ESCAPE_L || keycode == Q_KEY_L \
		|| keycode == Q_KEY_M || keycode == ESC_KEY_M)
		quit(bundle);
	return (0);
}

int	quit(t_bundle *bundle)
{
	mlx_destroy_window(bundle->mlx_inst, bundle->mlx_win);
	free_all(bundle);
	exit(0);
}

