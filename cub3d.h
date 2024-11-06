/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-wits <bde-wits@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 08:02:59 by bde-wits          #+#    #+#             */
/*   Updated: 2024/11/06 07:13:48 by bde-wits         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "./minilibx-linux/mlx.h"
# include <unistd.h>
# include <stdlib.h>
# include <stddef.h>
# include <fcntl.h>

// dois contenir les données de la map
typedef struct s_data
{
	// chemin des image texture direction
	char	*NORTH;
	char	*SOUTH;
	char	*EAST;
	char	*WEST;
	// code RGB 123,123,123 pas plus, possible moins
	char	*FLOOR;
	char	*CEILING;//plafond
	// 

}				data;

// dois contenir tout les donnée lie a la mlx img etc
typedef struct s_xpm
{

}				t_xpm;

#endif