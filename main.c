/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-wits <bde-wits@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 07:12:05 by bde-wits          #+#    #+#             */
/*   Updated: 2024/11/08 10:52:33 by bde-wits         ###   ########.fr       */
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

int	recup_map(t_data *data, char *file)
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
	data->map = ft_split(buffer, '\n');
	free(buffer);
	if (verifmap(data) == 1)
		return (freearg(data->map), 1);
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

int	verif_arg(t_data *data, char *file)
{
	// int	fd;

	// if (ft_chrcub(argv[1]) == 1)
		// return (printf("need file in .cub\n"), 1);
	// fd = open(argv, O_WRONLY, 777);
	// if (fd = -1)
		// return (printf("file not fund\n"), 1);
	if (recup_map(data, file) == 1)
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
