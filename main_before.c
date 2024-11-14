/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-wits <bde-wits@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 07:12:05 by bde-wits          #+#    #+#             */
/*   Updated: 2024/11/09 09:08:45 by bde-wits         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// check si la map a exclusivement des contours en "1" texture mur
int	check_wall(t_data *data)
{
	int	end;
	int	j;
	int	i;

	end = 0;
	j = -1;
	while (data->map[end] != NULL)
		end++;
	end--;
	while (data->map[0][++j] != '\0')
	{
		if (data->map[0][j] != '1')
			return (1);
	}
	j = -1;
	while (data->map[end][++j] != '\0')
	{
		if (data->map[end][j] != '1')
			return (1);
	}
	j = -1;
	while (++j <= end)
	{
		i = 0;
		if (data->map[j][0] != '1')
			return (1);
		while (data->map[j][i] != '\0')
			i++;
		if (data->map[j][i] != '1')
			return (1);
	}
	return (0);
}

// converti tout les espace en "1" mur
void	convert_space(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	printf("map convert\n");
	while (data->map[++i] != NULL)
	{
		j = -1;
		while (data->map[i][++j] != '\0')
		{
			if (data->map[i][j] == ' ')
				data->map[i][j] = '1';
		}
		printf("%s\n", data->map[i]);
	}
}

int	verifmap(t_data *data)
{
	convert_space(data);
	if (check_wall(data) == 1)
		return (printf("return 1 check wall\n"), 1);
	return (0);
}

int	file_intochar(t_data *data, char *file)
{
	int		fd;
	char	*buffer;
	int		bytesread;

	buffer = (char *)malloc(sizeof(char) * (10000 + 1));
	if (buffer == NULL)
		return (1);
	if (ft_chrcub(file) == 1)
		return (write(1, "errorfilename\n", 13), 1);
	fd = open(file, O_RDONLY, 0777);
	if (fd < 0)
		return (free(buffer), write(1, "fd introuvable", 14), 1);
	bytesread = read(fd, buffer, 10000);
	buffer[bytesread] = '\0';
	data->file = ft_split(buffer, '\n');
	free(buffer);
	// if (verifmap(data) == 1)
	// 	return (freearg(data->map), 1);
	return (0);
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
	return (1);
}

void	skip_space(t_data *data, int *i, int *j, int sign)
{
	if (sign == 1)
		(*j)++;
	if (sign == 2)
		(*j) + 2;
	while (data->file[*i][*j] == ' ' || data->file[*i][*j] == '\t')
		(*j)++;
}

int	recup_direction(t_data *data, int *i, int j)
{
	if (data->file[*i][0] == '\n' || data->file[*i][0] == '\0' || data->file[*i][0] == ' ')
		(*i)++;
	if (data->file[*i][0] == 'N' && data->file[*i][1] == 'O')
	{
		skip_space(data, i, &j, 2);
		data->NORTH = ft_strdup(data->file[*i][0] + j);
		(*i)++;
	}
	if (data->file[*i][0] == 'S' && data->file[*i][1] == 'O')
	{
		skip_space(data, i, &j, 2);
		data->SOUTH = ft_strdup(data->file[*i][0] + j);
		(*i)++;
	}
	if (data->file[*i][0] == 'W' && data->file[*i][1] == 'E')
	{
		skip_space(data, i, &j, 2);
		data->WEST = ft_strdup(data->file[*i][0] + j);
		(*i)++;
	}
	if (data->file[*i][0] == 'E' && data->file[*i][1] == 'A')
	{
		skip_space(data, i, &j, 2);
		data->EAST = ft_strdup(data->file[*i][0] + j);
		(*i)++;
	}
	if (data->file[*i][0] == 'F' && data->file[*i][1] != '\0')
	{
		skip_space(data, i, &j, 1);
		data->FLOOR = ft_strdup(data->file[*i][0] + j);
		(*i)++;
	}
	if (data->file[*i][0] == 'C' && data->file[*i][1] != '\0')
	{
		skip_space(data, i, &j, 1);
		data->CEILING = ft_strdup(data->file[*i][0] + j);
		(*i)++;
	}
}

// fonction qui va decoupe les donne de la map
int	recup_data_infile(t_data *data, int i, int j)
{
	while (data->file[i] != NULL)
		recup_direction(data, &i, 0);
	i = -1;
	// while (data->file[++i] != NULL)
	// {
	// 	if (ft_strchr())
	// }
}

int	verif_arg(t_data *data, char *file)
{
	// int	fd;

	// if (ft_chrcub(argv[1]) == 1)
		// return (printf("need file in .cub\n"), 1);
	// fd = open(argv, O_WRONLY, 777);
	// if (fd = -1)
		// return (printf("file not fund\n"), 1);
	if (file_intochar(data, file) == 1)
		return (1);
	if (recup_data_infile(data, 0, 0) == 1)
		return (1);
	return (0);
}

int	parsing(int argc, char **argv, t_data *data)
{
	if (argc != 2 || verif_arg(data, argv[1]) == 1)
		return (1);
	return (0);
}

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

void	init_data(t_data *data)
{
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
		return (1);
	printf("finish\n");
	return (0);
}
