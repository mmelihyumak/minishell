#include "minishell.h"

void	quote_handler(char *str, int *index, char q)
{
	int 	backup;
	int		i;
	char	*result;

	backup = *index + 1;
	i = *index;
	result = NULL;
	while(str[i] == q)
	{
		i++;
		while (str[i] && str[i] != q)
			i++;
		result = ft_strjoin_v3(result, ft_strdup_v2(str, backup, i));
		i++;
		backup = i + 1;
	}
	ft_lstadd_back_v2(&g_arg.list, ft_lstnew_v2(result, q));
	*index = i;
}

void	handle_others(char *str, int *index, char q)
{
	int		i;
	char	*result;

	i = *index;
	while (str[i] && str[i] != ' ' && str[i] != '>'
		&& str[i] != '<' && str[i] != '|' && str[i] != 34 && str[i] != 39)
		i++;
	result = ft_strdup_v2(str, *index, i);
	ft_lstadd_back_v2(&g_arg.list, ft_lstnew_v2(result, q));
	*index = i;
}

void	special_handler(char *str, int *index, char q)
{
	int 	backup;
	int		i;
	char	*result;

	backup = *index;
	i = 1;
	if(str[i + backup] == q && str[i + backup] != '|')
		i++;
	result = ft_strdup_v2(str, backup, i + backup);
	ft_lstadd_back_v2(&g_arg.list, ft_lstnew_v2(result, q));
	*index = i + backup;
}

int list_init(char *str)
{
	char	*result;
	int		len;
	int		i;

	len = ft_strlen(str);
	i = 0;
	//printf("--------\nstr: %s#\n", str);
	ft_lstclear_v2(&g_arg.list);
	while (i < len)
	{
		while (str[i] == ' ' && str[i] != 9)
			i++;
		if (str[i] == 34 || str[i] == 39)
			quote_handler(str, &i, str[i]);
		else if(str[i] == '>' || str[i] == '<' || str[i] == '|')
			special_handler(str, &i, str[i]);
		else if (str[i] && str[i] != ' ')
			handle_others(str, &i, 'o');
	}
	t_arg_list *ptr = g_arg.list;
	while (ptr)
	{
	//	printf("command: #%s#\nflag: %c\n\n", ptr->content, ptr->flag);
		ptr = ptr->next;
	}
	return (0);
}