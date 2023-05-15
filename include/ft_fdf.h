/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-m <aperez-m@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 18:30:39 by aperez-m          #+#    #+#             */
/*   Updated: 2023/05/15 07:16:21 by aperez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FDF_H
# define FT_FDF_H

# define EMPTY_FILE 1
# define WRONG_COLOR_CODE 2
# define R_OFFSET 2
# define G_OFFSET 4
# define B_OFFSET 6
# define A_OFFSET 8
# define COL_2_X //cos2(30)
# define ROW_2_X //-sen(30)cos(30)
# define COL_2_Y //Sen(30)cos(30)
# define ROW_2_Y //Sen2(30)
# define HEIGHT_2_Y //-cos(30)

# include "mlx.h"
# include "ft.h"
# include <stdio.h>
# include <math.h>
# include <fcntl.h>

void	error_handler(int error);

//sets the color for the pixel at x, y on image coordinates	 
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);

//read file into vertex map
//gets the number of rows in the file
int get_str_map_rows(char *file)
//reads a file into a char ***.
//It has to be to be char *** because each row has as
//many char * as vertices, so each row is a char **.
char	***get_str_map(char *file)


//vertex map transformations
//gets x and y of each vertex in the to the new perspective,
//doesn't scale, doesnt center the vertices map
void	to_new_perspective(t_v_map *v_map, t_view *view);
//get the vertical span of the vertices map, unscaled
void	get_span_v(t_v_map *v_map);
//get the horizontal span of the vertices map, unscaled
void	get_span_h(t_v_map *vertex_map, t_view *view)
//gets the maximum zoom for the vertices map to be shown completely in the window
//pps = pixels per grid side
int	get_max_pps(t_v_map *v_map, int img_width, int img_height);
//scale v_map_around 0,0
void	scale_v_map(t_v_map *v_map)
//get vector from scaled v_map to image center
void	get_offset(t_v_map *v_map, int img_with, int img_height)
//move the v_map to the center of the window
void	center_v_map(t_v_map *v_map)
//scale v_map_around image_center
void	rescale_v_map(t_v_map *v_map, double zoom)


//image to push to window
typedef struct s_data{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

//map of chars
typedef	struct s_map{
	int	rows;
	int	columns;
}				t_map;

typedef struct s_view{
	double	col_x;
	double	row_x;
	double	col_y;
	double	row_y;
	double	height_y;
}				t_view;

//vertex map
typedef struct s_v_map{
	t_vertex	**vertices;
	int			rows;
	int			cols;
	int			span_h;
	int			span_v;
	int			offset_h;
	int			offset_v;
	int			pps;
}				t_v_map;

//vertex of the wireframe
typedef struct s_vertex{
	int	column;
	int	row;
	int	height;
	int	x;
	int	y;
	char	R;
	char	G;
	char	B;
	char	A;
}				t_vertex;



#endif


