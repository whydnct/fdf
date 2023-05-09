/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperez-m <aperez-m@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 13:05:23 by aperez-m          #+#    #+#             */
/*   Updated: 2023/05/09 15:25:13 by aperez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

int get_map_rows(int fd)
{
    int ret;
    
    ret = 0;
    while(get_next_line(fd))
        ret++;
    if (!ret)
        error_handler(EMPTY_FILE);
	return (ret);
}

int get_map_cols(int fd, int rows)
{
    int ret;
    int i;
    int temp;

    ret = 0;
    i = 0;
	temp = 0;
    while(i < rows)
    {
		temp = get_next_line(fd);
        if (ret < temp)
			ret = temp;
    }
	return (ret);
}

char   ***get_map_chars(int fd)
{
   char ***ret;
   int  rows;
   int  i;
   
   i = 0;
   ret = malloc((rows)*sizeof(char **));
   while (i < rows)
		ret[i] = ft_split(get_next_line(fd), ' ');
   return (ret); 
}

//this is wrong, it's not handling \0 and end of char[]
int	**get_map_int(char ****map_chars)
{
	int	**ret;
	int	i;
	int	rows;
	
	i = 0;
	ret = malloc(rows*columns*sizeof(int));
	while (i < rows)
	{
		while (****(map_chars + i))
			(ret + i) = ft_atoi(map_chars + i);
	}
	
	return (ret);
}