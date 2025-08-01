/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktiomico <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 16:00:00 by ktiomico          #+#    #+#             */
/*   Updated: 2025/07/28 16:00:00 by ktiomico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_short_pwd(void)
{
	char	*cwd;
	char	*home;
	char	*short_path;
	int		home_len;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (ft_strdup("?"));
	home = getenv("HOME");
	if (home && ft_strncmp(cwd, home, ft_strlen(home)) == 0)
	{
		home_len = ft_strlen(home);
		if (cwd[home_len] == '\0')
			short_path = ft_strdup("~");
		else
			short_path = ft_strjoin("~", cwd + home_len);
		free(cwd);
		return (short_path);
	}
	return (cwd);
}

char	*build_prompt(void)
{
	char	*username;
	char	*cwd;
	char	*result;
	size_t	total_len;

	if (!isatty(STDIN_FILENO))
		return (ft_strdup("__MINISHELL_PROMPT__ "));
	username = getenv("USER");
	if (!username)
		username = "unknown";
	cwd = get_short_pwd();
	if (!cwd)
		return (NULL);
	total_len = ft_strlen(GREEN "👾 Minishell" YELLOW "@") + ft_strlen(username)
		+ ft_strlen(BLUE ":") + ft_strlen(cwd) + ft_strlen(GREEN " ➜ " RESET) + 1;
	result = malloc(total_len);
	if (!result)
		return (free(cwd), NULL);
	ft_strlcpy(result, GREEN "👾 Minishell" YELLOW "@", total_len);
	ft_strlcat(result, username, total_len);
	ft_strlcat(result, BLUE ":", total_len);
	ft_strlcat(result, cwd, total_len);
	ft_strlcat(result, GREEN " ➜ " RESET, total_len);
	free(cwd);
	return (result);
}
