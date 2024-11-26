/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-wits <bde-wits@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 05:18:11 by bde-wits          #+#    #+#             */
/*   Updated: 2024/11/26 07:52:45 by bde-wits         ###   ########.fr       */
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
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	while (line[i] != '\0')
	{
		if (line[i] == 'N' && line[i + 1] == 'O') //NORTH
			(*code) = 1;
		else if (line[i] == 'S' && line[i + 1] == 'O') //SOUTH
			(*code) = 2;
		else if (line[i] == 'W' && line[i + 1] == 'E') //WEST
			(*code) = 3;
		else if (line[i] == 'E' && line[i + 1] == 'A') //EAST
			(*code) = 4;
		else if (line[i] == 'F' && line[i] != '\0') //FLOOR
			(*code) = 5;
		else if (line[i] == 'C' && line[i] != '\0') //CEILLING
			(*code) = 6;
		else if (code != 0)
			return (/*printf("code status %d\n", (*code)), */0);
		i++;
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
	// printf ("resultat skip i = %d\n", (*i));
}

void	get_dir(t_data *data, char *line, int i, int code)
{
	// printf("start get_dir\n");
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
	// printf("print strdup \"%s\"\n", line);
}

int	verif_rgb(t_data *data, char **split, int sign)
{
	int i;

	i = -1;
	if (sign == 0)
		split = ft_split(data->CEILING, ',');
	else
		split = ft_split(data->FLOOR, ',');
	while (split[++i] != NULL)
	{
		if (i >= 3 || ft_atoi(split[i]) > 255 || ft_atoi(split[i]) < 0)
			return (printf("error in rgb code\n"), freearg(split), 1);
	}
	i = -1;
	while (split[++i] != NULL)
	{
		if (sign == 0)
			data->C_rgb[i] = ft_atoi(split[i]);
		else
			data->F_rgb[i] = ft_atoi(split[i]);
	}
	i = -1;
	freearg(split);
	return (0);
}

int	verif_dir(t_data *data)
{
	printf("start of verif dir\n");
	if (data->NORTH == NULL || data->SOUTH == NULL || data->WEST == NULL
		|| data->EAST == NULL || data->FLOOR == NULL 
		|| data->CEILING == NULL)
		return (printf("error direction path not found\n"), 1);
	if (verif_rgb(data, NULL, 1) == 1 || verif_rgb(data, NULL, 0) == 1)
		return (printf("RGB CEILING test error\n"), 1);
	// if (verif_rgb(data, NULL, 1) == 1)
	// 	return (printf("RGB FLOOR test error\n"), 1);
	return (0);
}

// fonction qui trouve le debut de la map
int	found_map(char *line)
{
	int i;

	i = -1;
	if (line == NULL)
		return (2); // skip is a the start of the file
	if (is_instr(line, 'F', -1) == 0 || is_instr(line, 'C', -1) == 0)
		return (0);
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
		if (line == NULL/* || found_map(line) == 1*/)
			break ;
		if (chr_dir(line, 0, &code) == 0) // direction found in line
			get_dir(data, line, 0, code); // save in the right thing
		// gere le cas du F 125,250,120 car F contient possiblement des 1 et 0
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


int	chr_map(char *line, int i)
{
	// if (is_instr(line, 'F', -1) == 1 || is_instr(line, 'C', -1) == 1)
	// 	return (1);
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
	(*len) = 1;
	while (found_map(line) != 1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			return (close(fd), printf("line = NULL\n"), 1);
	}
	// printf("len_map map found\n%s", line);
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
				|| line[i] != '2' || line[i] != '3' || line[i] != ' ' || line[i] != '\n')
				return (close(fd), 1);
		}
		(*len)++;
	}
	// if ((*len) < 3)
		// return (close(fd), 1);
	return (close(fd), 0);
}

void	init_map(t_data *data, int len)
{
	// printf("LEN %d\n", len);
	data->map = (char **)malloc(sizeof(char *) * (len + 1));
	data->map[len] = NULL;
}

// solution 1 : close et reopen pour recupere le nombre de line neccessaire pour la map
// solution 2 : trouve le depart de la map et utilise un read pour lire le reste et split \n
void	get_map(t_data *data, int fd, char *line, int len)
{
	int	i;

	i = 0;
	init_map(data, len); // init the map to right length
	while (1)
	{
		if (line == NULL)
			break ;
		// printf("line = %s\n", line);
		data->map[i] = ft_strdup(line);
		free(line);
		// printf("data %d = %s\n", i, data->map[i]);
		i++;
		line = get_next_line(fd);
	}
	// printf("\n\nlen %d = %s\n", len, data->map[len]);
	// printf("len %d = %s\n\n", (len + 1), data->map[len + 1]);
	close(fd);
}

// possible de recupere la position de depart aussi
int	check_start(t_data *data, int i, int j)
{
	int	start;

	start = 0;
	while (data->map[++i] != NULL)
	{
		j = -1;
		while (data->map[i][++j] != '\0')
		{
			if (data->map[i][j] == 'N' || data->map[i][j] == 'S' 
				|| data->map[i][j] == 'W' || data->map[i][j] == 'E')
				start++;
		}
	}
	if (start != 1)
		return (printf("too much player start\n"), 1);
	return (0);
}

// check all centralize the test on the map
int	check_map(t_data *data, int i)
{
	while (data->map[i] != NULL)
		i++;
	if (i < 3)
		return (printf("error too small map\n"), 1);
	if (check_start(data, -1, -1) == 1)
		return (1);
	if (test_map(data, 0, 0) == 1)
		return (printf("TEST NOT ok\n"), 1);
	return (printf("finish check_map\n"), 0);
}

int check_around(t_data *data, int x, int y)
{
    if (x <= 0 || y <= 0 || data->map[x + 1] == NULL || data->map[x][y + 1] == '\0')
        return (1);
    // Vérifie les cases adjacentes pour voir si elles sont valides
    if (data->map[x - 1][y] == ' ' || data->map[x + 1][y] == ' ' ||
        data->map[x][y - 1] == ' ' || data->map[x][y + 1] == ' ')
        return (1); // '0' adjacent à un espace ou un vide
    return (0);
}

int is_instr(char *str, char c, int i)
{
	while(str[++i] != '\0')
	{
		if (str[i] == c)
			return (0);
	}
	return (1);
}

int	test_map(t_data *data, int x, int y)
{
	if (is_instr(data->map[0], '0', -1) == 0)
		return (1);
	printf("test map apres premier ligne\n");
	while (data->map[++x] != NULL && data->map[x + 1] != NULL)
	{
		y = -1;
		while (data->map[x][++y] != '\0')
		{
			if (data->map[x][y] == '0')
			{
				if (check_around(data, x, y) == 1)
					return (printf("map invalid check_around\n"), 1);
			}
		}
	}
	int	i = -1;
	while (data->map[++i] != NULL)
		printf("%s\n", data->map[i]);
	printf("test map derniere ligne %d\n%s\n", x, data->map[x]);
	if (is_instr(data->map[x], '0', -1) == 0)
		return (1);
	return (0);
}

int	len_max(char **map)
{
	int	i;
	int	temp;

	i = -1;
	temp = 0;
	while(map[++i] != NULL)
	{
		if (ft_strlen(map[i]) > temp)
			temp = ft_strlen(map[i]);
	}
	// printf("\nlen_max %d\n", temp);
	return (temp);
}

void resize_map(t_data *data, int i, int l, int max)
{
    int len;

    while (data->map[++i] != NULL)
    {
        len = ft_strlen(data->map[i]);
        l = -1;
        char *temp = (char *)malloc(sizeof(char) * (max + 1));
        if (!temp)
            return;
        while (++l < len)
        {
            if (data->map[i][l] == '\n')
                temp[l] = ' ';
            else
                temp[l] = data->map[i][l];
        }
        while (l < max)
            temp[l++] = ' ';
        
        temp[l] = '\0';
        free(data->map[i]);
        data->map[i] = temp;
    }
}

int	verif_map(t_data *data, char *file, int fd, char *line)
{
	int	len;

	if (openfd(&fd, file) == 1)
		return (printf("error open file\n"), 1);
	if (len_map(line, &len, -1, fd) == 1)
		return (printf("error in LEN_map\n") ,1);
	// printf("result of len in file %d\n", len);
	openfd(&fd, file);
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (found_map(line) == 1) // map found in line
		{
			printf("ok verifmap foundmap = 1\n");
			get_map(data, fd, line, len);
			//return (/*close(fd), */0);
		}
		// free(line);
	}
	len = -1;
	resize_map(data, -1, -1, len_max(data->map));
	if (check_map(data, 0) == 1) // test the map if is a correct form
		return (/*close(fd), */1);
	return(/*close(fd), */0);
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

int	ft_atoi(char *ptr)
{
	int			i;
	long long	result;
	int			sign;

	i = 0;
	result = 0;
	sign = 1;
	while ((ptr[i] >= 9 && ptr[i] <= 13) || ptr[i] == 32)
		i++;
	if (ptr[i] == '+' || ptr[i] == '-')
	{
		if (ptr[i] == '-')
			sign = sign * -1;
		i++;
	}
	while (ptr[i] != '\0' && (ptr[i] >= 48 && ptr[i] <= 57))
	{
		result = result * 10 + (ptr[i] - '0');
		i++;
	}
	return (result * sign);
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