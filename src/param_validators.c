/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_validators.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-m <aperez-m@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 10:09:39 by aperez-m          #+#    #+#             */
/*   Updated: 2023/06/17 10:09:58 by aperez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

int	get_line_cols(char *line, char c)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	while (line[i])
	{
		while (line[i] == c)
			i++;
		if (line[i] != c && line[i])
			ret++;
		while (line[i] != c && line[i])
			i++;
	}
	return (ret);
}
