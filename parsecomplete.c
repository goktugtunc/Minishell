#include "minishell.h"

typedef struct s_parse
{
	char    *str;
	char    *type;
}   t_parse;

int countfrompars(t_lists *data)
{
	char	*str;
	int		i;
	int		count;
	int		tru;

	tru = 1;
	count = 0;
	str = data->arguments;
	while(str[i])
	{
		if ((str[i] == '|') || (str[i] == '>' || str[i] == '>'))
		{
			tru = 1;
			count++;
			i++;
			if ((str[i - 1] == '<' && str[i] == '<') || (str[i - 1] == '>' && str[i] == '>'))
				i++;
		}
		else if (str[i] != ' ' && tru == 1)
		{
			tru == 0;
			count++;
		}
		i++;
	}
	return (count);
}

t_parse *lastparse(t_lists *data)
{
	t_parse	*last;
	char	*str;
	int		i;
	int		j;

	j = 0;
	i = 0;
	last = (t_parse *)malloc(sizeof(t_parse) * countfrompars(data));
	while (str[i])
	{
		if (!str[i] || (str[i] == '|') || (str[i] == '>' || str[i] == '>'))
		{
			last[j].str = ft_substr(str, 0, i);
			last[j++].str = ft_strdup("part");
			i++;
			if ((str[i - 1] == '<' && str[i] == '<') || (str[i - 1] == '>' && str[i] == '>'))
			{
				i++;
				last[j].str = ft_substr(str, i - 2, i);
				last[j++].str = ft_strdup("pipe");
			}
			else
			{
				last[j].str = ft_substr(str, i - 1, i);
				last[j++].str = ft_strdup("part");
			}
		}
	}
	return (last);
}
