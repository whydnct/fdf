/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debuggers.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-m <aperez-m@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 17:37:16 by aperez-m          #+#    #+#             */
/*   Updated: 2023/06/12 22:37:00 by aperez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"


void	print_heights_colors(t_bundle *bundle)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < bundle->v_map->rows)
	{
		while (j < bundle->v_map->cols)
		{
			printf("%d\t", bundle->v_map->vertices[i][j].height);
			if (j == bundle->v_map->cols - 1)
				printf("\n");
			j++;
		}
		j = 0;
		i++;
	}
	i = 0;
	printf("\n");
	while (i < bundle->v_map->rows)
	{
		while (j < bundle->v_map->cols)
		{
			printf("%d ", bundle->v_map->vertices[i][j].color);
			if (j == bundle->v_map->cols - 1)
				printf("\n");
			j++;
		}
		j = 0;
		i++;
	}
}


void	write_vertices_to_image(t_bundle *bundle)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < bundle->v_map->rows)
	{
		while (j < bundle->v_map->cols)
		{
			my_mlx_pixel_put(bundle->img, \
				bundle->v_map->vertices[i][j].x, \
				bundle->v_map->vertices[i][j].y, \
				//bundle->v_map->vertices[i][j].color);
				0x00FF0000);
		/*	my_mlx_pixel_put(bundle->img, \
				5, \
				5, \
				0x00FF0000);
		*/	j++;
		}
		j = 0;
		i++;
	}
}

void	print_x_y(t_bundle *bundle)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < bundle->v_map->rows)
	{
		while (j < bundle->v_map->cols)
		{
			printf("%d\t", (int)bundle->v_map->vertices[i][j].x);
			if (j == bundle->v_map->cols - 1)
				printf("\n");
			j++;
		}
		j = 0;
		i++;
	}
	i = 0;
	printf("\n");
	while (i < bundle->v_map->rows)
	{
		while (j < bundle->v_map->cols)
		{
			printf("%d\t", (int)bundle->v_map->vertices[i][j].y);
			if (j == bundle->v_map->cols - 1)
				printf("\n");
			j++;
		}
		j = 0;
		i++;
	}
}

int	get_last_bit_of_img(t_img *img)
{
	return((img->width + 32) * img->height * 4);
}

void	print_img_to_file(t_bundle *bundle)
{
	int	i;
	int fid;
	int	i_limit;
	
	fid = open("./img_report", O_CREAT || O_WRONLY, 0664);
	i = -1;
	i_limit = 15000;
	while (++i < i_limit)	
	{
		ft_putnbr_fd(*((unsigned int *)bundle->img->img + i), fid);
		write(fid, "\t", 1);
		i++;
	}
	close(fid);
}	

void	print_str_map(t_bundle *bundle, char ***str_map)
{
	int	i;
	int	j;

	i = -1;
	j= 0;
	while (++i < bundle->v_map->rows)
	{
		while (str_map[i][j][0] != '\0')
		{
			printf("str_map[%d][%d]: %s\n", i, j, str_map[i][j]);
			j++;
		}
		j = 0;
	}
}

void	split_unit_test(char **string)
{
	int	i;
	int	j;
	char *null_str;
	
	null_str = "\0";	
	i = 0;
	j = 0;
	if (string[4][0] == 0)
		printf("null_str[0] != 0");
	printf("%s", null_str);
	printf("%ld\n", sizeof(string));
	while (i < 5)
	{
		while (string[i][j])
		{
			printf("%d\n", string[i][j]);	
			j++;
		}
		printf("%d\n", string[i][j]);
		j = 0;
		i++;
	}
	printf("%d\n", i);
	printf("%s\n", string[i]);	
}