/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debuggers.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-m <aperez-m@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 18:31:59 by aperez-m          #+#    #+#             */
/*   Updated: 2023/06/26 18:32:00 by aperez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

void	debug(t_bundle *bundle)
{
	print_x_y_file(bundle);
	print_height_file(bundle);
	print_color_file(bundle);
	write_vtx_to_image(bundle);
}

void	write_vtx_to_image(t_bundle *bundle)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	printf("write_vtx_to_image\n");
	while (++i < bundle->v_map->rows)
	{
		while (++j < bundle->v_map->cols)
		{
			my_mlx_pixel_put(bundle->img, \
				(int)bundle->v_map->vtx[i][j].x, \
				(int)bundle->v_map->vtx[i][j].y, \
				bundle->v_map->vtx[i][j].color);
		}
		j = -1;
	}
}

void	print_heights_colors(t_bundle *bundle)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	printf("printing heights\n");
	while (++i < bundle->v_map->rows)
	{
		while (++j < bundle->v_map->cols)
			printf("%d\t", bundle->v_map->vtx[i][j].height);
		printf("\n");
		j = -1;
	}
	i = -1;
	printf("\npriting colors\n");
	while (++i < bundle->v_map->rows)
	{
		while (++j < bundle->v_map->cols)
			printf("%d ", bundle->v_map->vtx[i][j].color);
		printf("\n");
		j = -1;
	}
}

void	print_x_y_file(t_bundle *bundle)
{
	int	i;
	int	j;
	int	fd;

	i = -1;
	j = -1;
	printf("print_x_y_file()\n");
	fd = open("logs/x_y", O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (fd < 0)
		perror("fallo de apertura");
	while (++i < bundle->v_map->rows)
	{
		while (++j < bundle->v_map->cols)
		{
			ft_putnbr_fd((int)bundle->v_map->vtx[i][j].x, fd);
			write(fd, ";", 1);
			ft_putnbr_fd((int)bundle->v_map->vtx[i][j].y, fd);
			if (j < bundle->v_map->cols - 1)
				write(fd, "\t", 1);
		}
		write(fd, "\n", 1);
		j = -1;
	}
	close(fd);
}

void	print_height_file(t_bundle *bundle)
{
	int	i;
	int	j;
	int	fd;

	i = -1;
	j = -1;
	printf("print_height_file()\n");
	fd = open("logs/heights", O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (fd < 0)
		perror("fallo de apertura");
	while (++i < bundle->v_map->rows)
	{
		while (++j < bundle->v_map->cols)
		{
			ft_putnbr_fd((int)bundle->v_map->vtx[i][j].height, fd);
			if (j < bundle->v_map->cols - 1)
				write(fd, " ", 1);
		}
		write(fd, "\n", 1);
		j = -1;
	}
	close(fd);
}

void	print_color_file(t_bundle *bundle)
{
	int	i;
	int	j;
	int	fd;

	i = -1;
	j = -1;
	printf("print_color_file()\n");
	fd = open("logs/colors", O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (fd < 0)
		perror("fallo de apertura");
	while (++i < bundle->v_map->rows)
	{
		while (++j < bundle->v_map->cols)
		{
			ft_putnbr_fd((int)bundle->v_map->vtx[i][j].color, fd);
			if (j < bundle->v_map->cols - 1)
				write(fd, " ", 1);
		}
		write(fd, "\n", 1);
		j = -1;
	}
	close(fd);
}
void	print_x_y(t_bundle *bundle)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	printf("print_x_y()\n");
	printf("printing x values");
	while (++i < bundle->v_map->rows)
	{
		while (++j < bundle->v_map->cols)
			printf("%f\t", bundle->v_map->vtx[i][j].x);
		printf("\n");
		j = -1;
	}
	i = -1;
	printf("\nprinting y values\n");
	while (++i < bundle->v_map->rows)
	{
		while (++j < bundle->v_map->cols)
			printf("%d\t", (int)bundle->v_map->vtx[i][j].y);
		printf("\n");
		j = -1;
	}
}
void	print_str_map(t_bundle *bundle, char ***str_map)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	printf("print_str_map\n");
	while (++i < bundle->v_map->rows)
	{
		while (str_map[i][++j] && str_map[i][j][0] != '\0')
			printf("str_map[%d][%d]: %s\n", i, j, str_map[i][j]);
		j = -1;
	}
}

/*
void	traverse_map(int row_max, int col_max, void *f, void * params)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (++i < row_max)
	{
		while (++j < col_max)
			f(params);
		j = -1;
	}
}
*/