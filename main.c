/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-wits <bde-wits@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 05:18:11 by bde-wits          #+#    #+#             */
/*   Updated: 2024/11/19 10:22:17 by bde-wits         ###   ########.fr       */
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
int	chr_dir(char *line, int i, int *code)
{
	// skip space and tab before word
	while (line[++i] != '\0')
	{
		if (line[i] == 'N' && line[i + 1] == 'O') //NORTH
			(*code) = 1;
		if (line[i] == 'S' && line[i + 1] == 'O') //SOUTH
			(*code) = 2;
		if (line[i] == 'W' && line[i + 1] == 'E') //WEST
			(*code) = 3;
		if (line[i] == 'E' && line[i + 1] == 'A') //EAST
			(*code) = 4;
		if (line[i] == 'F' && line[i] != '\0') //FLOOR
			(*code) = 5;
		if (line[i] == 'C' && line[i] != '\0') //CEILLING
			(*code) = 6;
		if (code != 0)
			return (printf("code status %d\n", (*code)), 0);
		// search for dir and maybe apply or get_dir will handle it
	}
	return (1);
}

void	skip_to_path(char *line, int *i)
{
	while (line[*i] == ' ' || line[*i] == '\t')
		(*i)++;
	if (line[*i] != '\0' && line[*i] != '\n')
	{
		while (line[*i] != ' ' && line[*i] != '\t' && line[*i] != '\0')
			(*i)++;
		(*i)++;
	}
	printf ("resultat skip i = %d\n", (*i));
}

void	get_dir(t_data *data, char *line, int i, int code)
{
	printf("start get_dir\n");
	skip_to_path(line, &i);
	if (code == 1)
		data->NORTH = ft_strdup(line + i);
	else if (code == 2)
		data->SOUTH = ft_strdup(line + i);
	else if (code == 3)
		data->WEST = ft_strdup(line + i);
	else if (code == 4)
		data->EAST = ft_strdup(line + i);
	else if (code == 5)
		data->FLOOR = ft_strdup(line + i);
	else if (code == 6)
		data->CEILING = ft_strdup(line + i);
	printf("print strdup \"%s\"\n", line);
}

int	verif_dir(t_data *data)
{
	printf("start of verif dir\n");
	if (data->NORTH == NULL || data->SOUTH == NULL || data->WEST == NULL
		|| data->EAST == NULL || data->FLOOR == NULL 
		|| data->CEILING == NULL)
		return (printf("error direction path not found\n"), 1);
	return (0);
}

// fonction qui trouve le debut de la map
int	found_map(char *line)
{
	int i;

	i = -1;
	if (line == NULL)
		return (2); // skip is a the start of the file
	while (line[++i] != '\0')
	{
		if (line[i] == '1' || line[i] == '0')
			return (1);
	}
	return (0);
}

// get dir path for xpm directional
int get_path_dir(t_data *data, char *file, int fd, char *line)
{
	int	code;

	if (openfd(&fd, file) == 1)
		return (printf("error open file\n"), 1);
	while (1)
	{
		code = 0;
		line = get_next_line(fd);
		if (line == NULL || found_map(line) == 1)
			break ;
		if (chr_dir(line, -1, &code) == 0) // direction found in line
			get_dir(data, line, 0, code); // save in the right thing
		free(line);
	}
	// printf("%s\n", data->SOUTH);
	// printf("%s\n", data->NORTH);
	// printf("%s\n", data->WEST);
	// printf("%s\n", data->EAST);
	// printf("%s\n", data->FLOOR);
	// printf("%s\n", data->CEILING);
	if (verif_dir(data) == 1) // verif all dir is not empty and maybe test in , if path is functunial
		return (close(fd), 1);
	return(close(fd), 0);
}

// solution 1 : close et reopen pour recupere le nombre de line neccessaire pour la map
// solution 2 : trouve le depart de la map et utilise un read pour lire le reste et split \n
void	get_map()
{
	
}

int	chr_map(char *line, int i)
{
	while (line[++i] != '\0')
	{
		if (line[i] == '0' || line[i] == '1')
			return (0);
	}
	return (1);
}

// search the nbr of line in the map and if the map have error at end of it
int	len_map(char *line, int *len, int i, int fd)
{
	(*len) = 0;
	while (found_map(line) != 1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			return (close(fd), 1);
	}
	while (1)
	{
		i = -1;
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		while (line[++i] == '\0')
		{
			if (line[i] != '0' || line[i] != '1' || line[i] != 'N' 
				|| line[i] != 'W' || line[i] != 'E' || line[i] != 'S' 
				|| line[i] != '2' || line[i] != '3')
				return (close(fd), 1);
		}
		(*len)++;
	}
	return (close(fd), 0);
}


int	verif_map(t_data *data, char *file, int fd, char *line)
{
	int	len;

	if (openfd(&fd, file) == 1)
	return (printf("error open file\n"), 1);
	if (len_map(line, &len, -1, fd) == 1)
		return (printf("error in map\n") ,1);
	printf("result of len in file %d\n", len);
	openfd(&fd, file);
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (found_map(line) == 1) // map found in line
		{
			get_map(); // save map in data->map
			//return (close(fd), 0);
		}
		free(line);
	}
	if (check_map(data) == 1) // verif all dir is not empty and maybe test in , if path is functunial
		return (close(fd), 1);
	return(close(fd), 0);
}

int	verif_arg(t_data *data, char *file)
{
	//verif format	verif data xpm
	if (ft_chrcub(file) == 1 || get_path_dir(data, file, 0, NULL) == 1)
		return (1);
	if (verif_map(data, file, 0, NULL) == 1)
		return (1);
	return (0);
}

int	parsing(int argc, char **argv, t_data *data)
{
	if (argc != 2 || verif_arg(data, argv[1]) == 1)
		return (1);
	return (0);
}

void	init_data(t_data *data)
{
	data->NORTH = NULL;
	data->SOUTH = NULL;
	data->EAST = NULL;
	data->WEST = NULL;
	data->FLOOR = NULL;
	data->CEILING = NULL;
	data->temp = NULL;
	data->map = NULL;
	printf("finish init\n");
	// data->
}

char	*ft_strdup(char *s)
{
	char	*dup;
	int		i;
	int		ls;

	i = 0;
	ls = ft_strlen(s);
	dup = (char *)malloc((sizeof(char)) * (ls + 1));
	if (dup == NULL)
		return (NULL);
	while (s[i] != '\0')
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

int	ft_strlen(char	*c)
{
	int	i;

	i = 0;
	while (c[i] != '\0')
		i++;
	return (i);
}

int	main(int argc, char **argv)
{
	t_data	data;

	printf("start main\n");
	init_data(&data);
	if (parsing(argc, argv, &data) == 1)
		return (1); //free parsing;
	printf("finish in OK CASE\n");
	return (0);
}