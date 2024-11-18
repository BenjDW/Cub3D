/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-wits <bde-wits@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 08:02:59 by bde-wits          #+#    #+#             */
/*   Updated: 2024/11/18 10:30:28 by bde-wits         ###   ########.fr       */
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

// parsing function
int		ft_chrcub(char *str);
int		recup_map(t_data *data, char *file);
int		verif_dir(t_data *data);

// split function annexe
char	**ft_split(char const *s, char c);
int		countword(char const *s, char c);
void	ft_bzero(void *s, size_t n);
char	**tabc(char **tab, const char *s, char c);
char	*ft_strncpy(char *dest, char *src, int n);
void	*ft_calloc(size_t nmemb, size_t size);
void	freearg(char **tabarg);

// get_next_line function
char	*get_next_line(int fd);
char	*readfile(int fd);
char	*ft_verif(char *s, int i, int j, int fin);
int		ft_verifn(char *src);
char	*ft_dupafter(char *src);
char	*ft_dup(char *src, int fin);
int		ftr_strlen(char *s);
char	*f_strjoin(char *s1, char *s2);
char	*ft_join(char *stock, char *buffer);

char	*ft_strdup(char *s);
int		ft_strlen(char	*c);

#endif