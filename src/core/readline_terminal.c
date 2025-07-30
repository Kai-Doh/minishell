/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_terminal.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktiomico <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 02:00:00 by ktiomico          #+#    #+#             */
/*   Updated: 2025/07/30 02:00:00 by ktiomico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/ioctl.h>
#include <termios.h>
#include <term.h>

static int	putchar_for_tputs(int c)
{
	return (write(STDOUT_FILENO, &c, 1));
}

static void	setup_terminal_no_wrap(char *term_type, char *term_buffer)
{
	struct winsize	ws;
	char			*am_cap;
	char			*rmam_cap;

	(void)term_type;
	(void)term_buffer;
	if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == 0 && ws.ws_col > 0)
	{
		am_cap = tgetstr("am", NULL);
		if (am_cap && tgetflag("am") > 0)
		{
			rmam_cap = tgetstr("rmam", NULL);
			if (rmam_cap)
				tputs(rmam_cap, 1, putchar_for_tputs);
		}
	}
}

static void	restore_terminal_wrap(char *term_type, char *term_buffer)
{
	char	*smam_cap;

	(void)term_type;
	(void)term_buffer;
	smam_cap = tgetstr("smam", NULL);
	if (smam_cap)
		tputs(smam_cap, 1, putchar_for_tputs);
}

char	*safe_readline(const char *prompt_str)
{
	char	*line;
	char	*term_type;
	char	term_buffer[2048];

	term_type = getenv("TERM");
	if (term_type && tgetent(term_buffer, term_type) > 0)
		setup_terminal_no_wrap(term_type, term_buffer);
	line = readline(prompt_str);
	if (term_type && tgetent(term_buffer, term_type) > 0)
		restore_terminal_wrap(term_type, term_buffer);
	return (line);
}
