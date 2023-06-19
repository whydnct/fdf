/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-m <aperez-m@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 16:38:01 by aperez-m          #+#    #+#             */
/*   Updated: 2023/06/19 18:37:19 by aperez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

int	get_color(t_vertex *start, t_vertex *end, int *deltas)
{
	(void)deltas;
	(void)start;
	(void)end;
	return (start->color);
}
