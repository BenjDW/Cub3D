/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-wits <bde-wits@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 08:02:59 by bde-wits          #+#    #+#             */
/*   Updated: 2024/11/14 10:50:08 by bde-wits         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000
# endif
# include "./minilibx-linux/mlx.h"
# include <unistd.h>
# include <stdlib.h>
# include <stddef.h>
# include <fcntl.h>
# include <stdio.h>

// dois contenir les données de la map
typedef struct s_data
{
	// chemin des image texture direction
	char	*tempdir;
	char	*NORTH;
	char	*SOUTH;
	char	*EAST;
	char	*WEST;
	// code RGB 123,123,123 pas plus, possible moins
	char	*FLOOR;
	char	*CEILING;//plafond
	//
	char	**file;
	char	**map;

}				t_data;

// dois contenir tout les donnée lie a la mlx img etc
typedef struct s_xpm
{

}				t_xpm;


int		ft_chrcub(char *str);
void	freearg(char **tabarg);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
char	*ft_strncpy(char *dest, char *src, int n);
int		countword(char const *s, char c);
char	**tabc(char **tab, const char *s, char c);
char	**ft_split(char const *s, char c);
int		recup_map(t_data *data, char *file);

#endif