/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-m <aperez-m@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 13:26:58 by aperez-m          #+#    #+#             */
/*   Updated: 2023/05/15 14:04:52 by aperez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

t_v_map *create_v_map(char *file, t_view *view, int w_width, int w_height)
{
	t_v_map	*ret;
	char	***str_map;
	
	ret = malloc(sizeof(ret));
	get_str_map_rows(file, ret);
	str_map = get_str_map(file, ret);
	get_str_map_cols(ret, &str_map);
	get_heights_colors(ret, &str_map);
	to_new_perspective(s_v_map, view);
	get_span_v(ret);
	get_span_h(ret);
	get_max_pps(v_map, w_width, w_height);
	scale_v_map(s_v_map);
	get_offset(v_map, w_width, w_height);
	center_v_map(v_map);
	
	return (ret);	
	
}

void	write_v_map_to_image(t_data *data, t_v_map *v_map)
{
	int i;
	int j;
	
	i = 0;
	j = 0;
	while (i < v_map->rows)
	{
		while(j < v_map->cols)
		{
			my_mlx_pixel_put(data, v_map->vertices[i][j]->x, /
				v_map->vertices[i][j]->y, v_map->vertices[i][j]->color);
			j++;
		}
		j = 0;
		i++;
	}
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	main(int argc, char **argv)
{
	void	*mlx;
	void	*mlx_win;
	void	*param;
	t_data	img;
	int		w_width;
	int		w_height;	
	char	*file;
	t_v_map	*v_map;

	(void)argc;
	param = &w_width;
	file = agrv[1];
	w_width = ft_atoi(argv[2]);
	w_height = ft_atoi(argv[3]);
	mlx = mlx_init(); //connects to the graphical system. Returns a mlx instance
	mlx_win = mlx_new_window(mlx, w_width, w_height, "prueba"); //creates a window, with size and title, tied to the mlx instance
	img.img = mlx_new_image(mlx, w_width, w_height); //creates an image, with size in pixels, tied to the mlx instance
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
			&img.endian); //allocates and returns address of the image. All variables but the address are set by mlx.
	v_map = create_v_map(file);
	write_v_map_to_image(&img, v_map);
	my_mlx_pixel_put(&img, 195, 195, 0x00FF0000);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0); //pushes the img (t_data) to the window
	mlx_key_hook(mlx_win, &exit_on_esc, param);
	mlx_loop(mlx); //renders the window
}
