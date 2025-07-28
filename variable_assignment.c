/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_assignment.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktiomico <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 16:00:00 by ktiomico          #+#    #+#             */
/*   Updated: 2025/07/28 16:00:00 by ktiomico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_variable_assignment(char *str)
{
	int	i;

	i = 0;
	if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (0);
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (str[i] == '=');
}

int	handle_variable_assignment(char *str, t_shell *sh)
{
	char	*key;
	char	*value;
	char	*eq_pos;
	char	*expanded_value;

	eq_pos = ft_strchr(str, '=');
	if (!eq_pos)
		return (1);
	key = ft_substr(str, 0, eq_pos - str);
	if (!key)
		return (1);
	value = eq_pos + 1;
	expanded_value = expand_word(value, sh);
	if (!expanded_value)
	{
		free(key);
		return (1);
	}
	set_env_var(sh, key, expanded_value);
	free(key);
	free(expanded_value);
	return (0);
}
