/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anthrodr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 11:40:29 by anthrodr          #+#    #+#             */
/*   Updated: 2023/10/09 11:52:24 by anthrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../gc/gc.h"
#include "../../include/minishell.h"

void	handle_escape_char(t_lexer *lexer)
{
	(lexer->current)++;
	if (*(lexer->current) == '"' || *(lexer->current) == '\''
		|| *(lexer->current) == '\\')
		lexer->buffer[(lexer->bufidx)++] = *(lexer->current)++;
	else
	{
		lexer->buffer[(lexer->bufidx)++] = '\\';
		lexer->buffer[(lexer->bufidx)++] = *(lexer->current)++;
	}
}

void	handle_quoted_string(t_lexer *lexer, char quote_char)
{
	(lexer->current)++;
	while (*(lexer->current))
	{
		if (*(lexer->current) == '\\' && quote_char == '"')
		{
			(lexer->current)++;
			if (*(lexer->current) == '"' || *(lexer->current) == '\\'
				|| *(lexer->current) == '$')
				lexer->buffer[(lexer->bufidx)++] = *(lexer->current)++;
			else
			{
				lexer->buffer[(lexer->bufidx)++] = '\\';
				lexer->buffer[(lexer->bufidx)++] = *(lexer->current)++;
			}
		}
		else if (*(lexer->current) == quote_char)
			break ;
		else
			lexer->buffer[(lexer->bufidx)++] = *(lexer->current)++;
	}
	if (*(lexer->current) == quote_char)
		(lexer->current)++;
	else
		lexer->error = 1;
}

void	handle_space_char(t_lexer *lexer)
{
	t_token	t;

	if (lexer->bufidx > 0)
	{
		lexer->buffer[lexer->bufidx] = '\0';
		t.value = ft_strdup(lexer->buffer);
		if (lexer->tokencount == 0)
			t.type = TOKEN_COMMAND;
		else
			t.type = TOKEN_ARGUMENT;
		lexer->tokens[(lexer->tokencount)++] = t;
		lexer->bufidx = 0;
	}
	(lexer->current)++;
}

void	handle_pipe(t_lexer *lexer)
{
	t_token	t;

	t.value = NULL;
	t.type = TOKEN_PIPE;
	lexer->tokens[(lexer->tokencount)++] = t;
	(lexer->current)++;
}

void	handle_redirect_in(t_lexer *lexer)
{
	t_token	t;

	t.value = NULL;
	if (*(lexer->current + 1) == '<')
	{
		t.type = TOKEN_REDIRECT_IN_APPEND;
		lexer->current += 2;
	}
	else
	{
		t.type = TOKEN_REDIRECT_IN;
		(lexer->current)++;
	}
	lexer->tokens[(lexer->tokencount)++] = t;
}
