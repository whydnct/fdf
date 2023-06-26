/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-m <aperez-m@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 16:38:01 by aperez-m          #+#    #+#             */
/*   Updated: 2023/06/26 17:42:37 by aperez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

int	get_color(t_vertex **nodes, int *deltas, int *pixel)
{
	int		red;
	int		green;
	int		blue;
	double	percentaje;

	if (deltas[0] > deltas[1])
		percentaje = percent(nodes[0]->x, nodes[1]->x, pixel[0]);
	else
		percentaje = percent(nodes[0]->y, nodes[1]->y, pixel[1]);
	red = ((nodes[0]->color >> 16) & 0xFF) * (1 - percentaje) \
		+ ((nodes[1]->color >> 16) & 0xFF) * percentaje;
	green = ((nodes[0]->color >> 8) & 0xFF) * (1 - percentaje) \
		+ ((nodes[1]->color >> 8) & 0xFF) * percentaje;
	blue = ((nodes[0]->color >> 0) & 0xFF) * (1 - percentaje) \
		+ ((nodes[1]->color >> 0) & 0xFF) * percentaje;
	return ((red << 16) | (green << 8) | blue << 0);
}

double	percent(int start, int end, int current)
{
	double	placement;
	double	distance;

	placement = current - start;
	distance = end - start;
	if (distance == 0)
		return (1);
	else
		return (placement / distance);
}
