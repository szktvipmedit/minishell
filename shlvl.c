#include "minishell.h"

static size_t	ft_get_env_index(char **env, char *str)
{
	size_t	i;

	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], str, ft_strlen(str)) == 0)
			return (i);
		i++;
	}
	return (i);//リストにSHLVLがなければ最後のNULLを指したインデックスが返される。
}

void	ft_increment_shlvl(t_shell *shell)
{
	size_t	i;
	int			prev_lvl;
	char		*tmp;
	char		**env;

	env = shell->environ_list_head;//変数名が長くて不便なので一時的に短くする。
	i = ft_get_env_index(env, "SHLVL=");//envリストの中からSHLVL=が格納されているインデックスを探す。
	if (env[i] == NULL)
		return ;//リストにSHLVLがなかった。
	prev_lvl = ft_atoi(env[i] + 6);
	tmp = env[i];//文字列をswap->freeする流れ。
	env[i] = ft_strjoin("SHLVL=", ft_itoa(prev_lvl + 1));//shlvlの数字の部分がインクリメントされる。
	if (env[i] == NULL)
	{
		ft_free_strs(shell->environ_list_head);
		ft_msg_and_exit();
	}
	free(tmp);
}
