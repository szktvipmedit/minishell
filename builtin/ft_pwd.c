#include "../minishell.h"

void	ft_pwd(t_shell *shell)
{
	char	buffer[PATH_MAX];

	if (getcwd(buffer, sizeof(buffer)) == NULL) //成功すると、バッファに現在の作業ディレクトリが格納される。
		ft_free_all_and_exit(shell, 1);
	printf("%s\n", buffer);
}
