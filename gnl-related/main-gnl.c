/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main-gnl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-m <aperez-m@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 19:35:45 by aperez-m          #+#    #+#             */
/*   Updated: 2023/05/23 19:35:45 by aperez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include "lib/libft/include/ft.h"

int	main(int argc, char **argv)
{
	int	fd;
	int	lines;
	int	i;

	if (argc != 3)
	{
		printf("usage: executable file lines to read\n");
		exit(-1);
	}
	lines = atoi(argv[2]);
	i = 0;
	if ((fd = open(argv[1], O_RDONLY)) == -1)
	{
		printf("error abriendo");
		exit(-1);
	}
	while (i < lines)
	{
		ft_putstr_fd(get_next_line(fd), 1);
		i++;
	}
	close(fd);
}
