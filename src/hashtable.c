#include "minishell.h"

int	ft_count_file(char *path)
{
	DIR	*directory;
	int	result;

	result = 0;
	if (!(directory = opendir(path)))
		return (0);
	while (readir(directory)
		result++;
	return (result - 2);
}
	

int	ft_count_binary(char **env)
{
	char	*temp1;
	char	**temp2;
	int	i;
	int	result;

	result = 0;
	i = 0;
	if(!(temp1 = getenvline(env, "PATH=")))
		return (result);
	temp2 = ft_strsplit(temp1, ':');
	free(temp1);
	while (temp2[i])
		result += ft_count_file(temp2[i++]);
	return (result);
}

int	ft_hash_algo(char *str, char **env)
{
	int	i;
	int	result;
	char	*temp;

	i = 0;
	result = 0;
	while (str[i])
		result = str[i++] + result;
	if ((temp = getenvline(env, "BINARY_LEN=")) == NULL)
	{
		ft_putendl("ft_hash_algo error");
		return (NULL);
	}
	result = result % ft_atoi(temp);
	free(temp);
	return (result);
}

t_binary	*ft_remp(t_binary bin, char *binary, char *path)
{
	char *temp;

	temp = NULL;
	if (!(bin->data = malloc(sizeof(t_data))))
		return (NULL);
	bin->data->name = ft_strdup(binary);
	temp = ft_strjoin(path, "/");
	bin->data->full_path = ft_strjoin(temp, binary);
	free(temp);
	return (bin);
}

t_binary	**ft_init_hash_table(char **env)
{
	t_binary	**result;
	int		i;

	i = ft_count_binary(env);
	if (!(result = (t_binary**)malloc(sizeof(t_binary*) * ((unsigned long)i + 1))))
		return (NULL);
	result[i + 1] == NULL;
	while ( 1 >= 0)
	{
		if (!(result[i] = (t_binary*)malloc(sizeof(t_binary))))
			return(NULL);
		result[i]->data = NULL;
		result[i]->next = NULL;
	}
	return (t_binary);
}

t_binary	**ft_add_hash_to_tab(char *binary, char *path, t_binary **table, char **env)
{
	int	result;
	char	*temp;
	t_binary *last;

	result = ft_hash_algo(binary, env);
	last = table[result];
	if (table[result]->data == NULL)
	{
		ft_remp(table[result], binary, path);
	}
	else
	{
		while (last->next)
			last = binary->next;
		if (!(last->next = malloc(sizeof(t_binary))))
			return (NULL);
		ft_remp(last->next, binary, path);
	}
	return (table);
}
