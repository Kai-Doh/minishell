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

static char	*build_prompt_part1(char *username)
{
	char	*temp;
	char	*result;

	temp = ft_strjoin(GREEN "👾 Minishell" YELLOW "@", username);
	if (!temp)
		return (NULL);
	result = ft_strjoin(temp, BLUE ":");
	free(temp);
	return (result);
}

static char	*build_prompt_part2(char *part1, char *cwd)
{
	char	*temp;
	char	*result;

	temp = ft_strjoin(part1, cwd);
	if (!temp)
		return (NULL);
	result = ft_strjoin(temp, GREEN " ➜ " RESET);
	free(temp);
	return (result);
}

char	*build_prompt(void)
{
	char	*username;
	char	*cwd;
	char	*part1;
	char	*result;

	username = getenv("USER");
	if (!username)
		username = "unknown";
	cwd = get_short_pwd();
	if (!cwd)
		return (NULL);
	part1 = build_prompt_part1(username);
	if (!part1)
		return (free(cwd), NULL);
	result = build_prompt_part2(part1, cwd);
	free(part1);
	free(cwd);
	return (result);
}
