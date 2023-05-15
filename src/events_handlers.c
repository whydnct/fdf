/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-m <aperez-m@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 05:50:40 by aperez-m          #+#    #+#             */
/*   Updated: 2023/05/13 05:51:20 by aperez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "ft_fdf.h"

int	exit_on_esc(int keycode, void *param)
{
	(void)param;
	if (keycode == 0xff1b)
		exit(1);
	return (0);
}