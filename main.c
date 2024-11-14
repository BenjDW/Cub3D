/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-wits <bde-wits@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 05:18:11 by bde-wits          #+#    #+#             */
/*   Updated: 2024/11/14 10:56:12 by bde-wits         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	freearg(char **tabarg)
{
	int	i;

	i = 0;
	while (tabarg[i] != NULL)
	{
		free(tabarg[i]);
		i++;
	}
	free(tabarg);
}

int	ft_chrcub(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	if (i > 4)
	{
		i--;
		if (str[i] == 'b')
			i--;
		if (str[i] == 'u')
			i--;
		if (str[i] == 'c')
			i--;
		if (str[i] == '.')
			return (0);
	}
	printf("error not a .cub file\n");
	return (1);
}

int	openfd(int *fd, char *file)
{
	(*fd) = open(file, O_RDONLY, 0777);
	if ((*fd) < 0)
		return (1);
	return (0);
}

// search for directional path and floor , ceilling rgb code 
int	chr_dir(char *line, int i)
{
	while (line[i] != '\0')
	{
		// search for dir and maybe apply or get_dir will handle it
	}
	return (1);
}

// get dir path for xpm directional
int get_path_dir(t_data *data, char *file, int fd, char *line)
{
	if (openfd(&fd, file) == 1)
		return (printf("error open file\n"), 1);
	// if (get_dir() == )
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (chr_dir(line, -1) == 0) // direction found in line
			get_dir(); // save in the right thing
		// free(line);
	}
	verif_dir(); // verif all dir is not empty and maybe test in , if path is functunial
	return(close(fd), 0);
}

int	verif_arg(t_data *data, char *file)
{
	//verif format	verif data xpm
	if (ft_chrcub(file) == 1 || get_path_dir(data, file, 0, NULL) == 1)
		return (1);

}

int	parsing(int argc, char **argv, t_data *data)
{
	if (argc != 2 || verif_arg(data, argv[1]) == 1)
		return (1);
	return (0);
}

void	init_data(t_data *data)
{
	data->tempdir = NULL;
	data->NORTH = NULL;
	data->SOUTH = NULL;
	data->EAST = NULL;
	data->WEST = NULL;
	data->FLOOR = NULL;
	data->CEILING = NULL;
	data->map = NULL;
	printf("finish init\n");
	// data->
}

int	main(int argc, char **argv)
{
	t_data	data;

	printf("start main\n");
	init_data(&data);
	if (parsing(argc, argv, &data) == 1)
		return (1); //free parsing;
	printf("finish\n");
	return (0);
}