/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-m <aperez-m@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 18:30:39 by aperez-m          #+#    #+#             */
/*   Updated: 2023/05/18 21:24:05 by aperez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * NEXT: ver si el "retorno de my_pixel_put" es correcto.
*/

#ifndef FT_FDF_H
# define FT_FDF_H

# define EMPTY_FILE 1
# define WRONG_COLOR_CODE 2
# define OPEN_FAILED 3
# define MALLOC_FAILED 4
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
# include <limits.h>

/**
 * @brief called on errors, prints diagnostic.
 * @param error Macro for the error.
 * @note 
 */
void	error_handler(int error);

//sets the color for the pixel at x, y on image coordinates	 
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);

//READ FILE INTO VERTEX MAP

//gets the number of rows in the file
void	get_str_map_rows(char *file, t_v_map *v_map);

/**
 * @brief reads the file into a char ***. Every row is a char **
 * @param file path for the file
 * @return char *** that stores all strings in the map
 * @note 
 */
char	***get_str_map(char *file, t_v_map *v_map);
//gets the maximum number of columns in the map
void	get_str_map_cols(t_v_map *v_map, char ****str_map);
//builds a t_vertex ** and gets height and color for each vertex
void	get_heights_colors(t_v_map *v_map, char ****str_map);
//transforms the hexa coded color to int
int		hex_to_color(char *str);

//GENERATE PERSPECTIVE

//gets x and y of each vertex in the to the new perspective,
//doesn't scale, doesnt center the vertices map
void	to_new_perspective(t_v_map *v_map, t_view *view);
//get the vertical span of the vertices map, unscaled
void	get_span_v(t_v_map *v_map);
//get the horizontal span of the vertices map, unscaled
void	get_span_h(t_v_map *vertex_map, t_view *view);
//gets the maximum zoom for the vertices map to be shown
// completely in the window
//pps = pixels per grid side
void	get_max_pps(t_v_map *v_map, int img_width, int img_height);
//scale v_map_around 0,0
void	scale_v_map(t_v_map *v_map);
//get vector from scaled v_map to image center
void	get_offset(t_v_map *v_map, int img_with, int img_height);
//move the v_map to the center of the window
void	center_v_map(t_v_map *v_map);
//draws lines along the axis from one vertex to the next
void	draw_line(t_data *data, t_v_map *start, t_v_map *end);

/**
 * @brief interpolates the value between two points, bringing the 
 * origin to the first point
 * @param x increment of x from start for which you want to get the value
 * @param span_x end_x - start_x
 * @param span_value end_value - start_value
 * @return increment of value at x
 * @note 
 */
int		interpolate(int x, int span_x, int span_value);

//scale v_map_around image_center
void	rescale_v_map(t_v_map *v_map, double zoom);

//image to push to window
typedef struct s_data{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

//map of chars
typedef struct s_map{
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
	t_vertex	***vertices;
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
	int				col;
	int				row;
	int				height;
	int				x;
	int				y;
	unsigned int	color;
}				t_vertex;
#endif