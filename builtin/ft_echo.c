#include "../minishell.h"

static void	output_strings(int i, bool option_flag, char **split_cmd_args)
{
	while (split_cmd_args[i])
	{
		printf("%s", split_cmd_args[i]);
		if (split_cmd_args[i + 1])
			printf(" ");
		i++;
	}
	if (!option_flag)
		printf("\n");
}

static void	prossesing_option_group(int *i, bool *option_flag,
		char **split_cmd_args)
{
	while (split_cmd_args[*i])
	{
		if (ft_strncmp(split_cmd_args[*i], "-n", 3))
			break ;
		*option_flag = true;
		*i = *i + 1;
	}
}

static void	output(char **split_cmd_args)
{
	int		i;
	bool	option_flag;

	option_flag = false;
	i = 1;
	prossesing_option_group(&i, &option_flag, split_cmd_args);
	output_strings(i, option_flag, split_cmd_args);
}

int	ft_echo(char *cmd_args)
{
	int		argc;
	char	**split_cmd_args;

	split_cmd_args = ft_split(cmd_args, ' ');
	argc = get_cmd_args_cnt(split_cmd_args);
	if (argc == 1)
		printf("\n");
	else
		output(split_cmd_args);
	ft_split_all_free(split_cmd_args);
	return (0);
}
