#include "minishell.h"

int	words_of_parts(char **argu)
{
	int i;
	int count;

	count = 0;
	i = 0;
	while(argu[i])
	{
		if (argu[i][0] == '|' || argu[i][0] == '<' || argu[i][0] == '>')
			return (count);
		i++;
		count++;
	}
	return (count);
}

char **towDcopy(char **src)
{
	char	**dest;
	int		i;
	int		words;

	i = 0;
	if (src[0][0] && src[0][0] != '<' && src[0][0] != '>' && src[0][0] != '|')
		words = words_of_parts(src);
	else
		words = 1;
	dest = (char **)malloc(sizeof(char **) * words + 1);
	while(i < words)
	{
		dest[i] = ft_strdup(src[i]); 
		i++;
	}
	dest[i] = NULL;
	return (dest);
}

int countfrompars(t_lists *data)
{
	char	**str;
	int		i;
	int		count;
	int		tru;

	tru = 1;
	count = 0;
	i = 0;
	str = data->arguments;
	while(str[i])
	{
		if ((str[i][0] == '|') || (str[i][0] == '>' || str[i][0] == '<'))
		{
			tru = 1;
			count++;
		}
		else if (tru == 1)
		{
			tru = 0;
			count++;
		}

		i++;
	}	
	return (count);
}

t_parse *lastparse(t_lists *data)
{
	t_parse	*last = NULL;
	char	**str;
	int		i;
	int		j;
	int		tru;

	tru = 1;
	j = 0;
	i = 0;
	str = data->arguments;
	last = (t_parse *)malloc(sizeof(t_parse) * countfrompars(data));
	while (str[i])
	{

		if ((str[i][0] == '|') || (str[i][0] == '>' || str[i][0] == '<'))
		{
			tru = 1;
			last[j].str = towDcopy(&str[i]);
			last[j++].type = ft_strdup("pipe");
		}
		else if (tru)
		{
			tru = 0;
			last[j].str = towDcopy(&str[i]);
			last[j++].type = ft_strdup("part");
		}

		i++;
	}
	return (last);
}
