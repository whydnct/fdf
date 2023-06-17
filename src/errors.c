/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-m <aperez-m@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 13:11:41 by aperez-m          #+#    #+#             */
/*   Updated: 2023/06/17 17:46:32 by aperez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

void	error_handler(int error)
{
	if (error == EMPTY_FILE)
		ft_putstr_fd("EMPTY_FILE\n", 2);
	else if (error == WRONG_COLOR_CODE)
		ft_putstr_fd("WRONG_COLOR_CODE\n", 2);
	else if (error == OPEN_FAILED)
		ft_putstr_fd("OPEN_FAILED\n", 2);
	else if (error == MALLOC_FAILED)
		ft_putstr_fd("MALLOC_FAILED\n", 2);
	exit(error);
}
