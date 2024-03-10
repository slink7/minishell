#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#include "libft.h"

int w(int c)
{
	return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_';
}

int W(int c)
{
	return !w(c);
}

int	o(int c)
{
	return c == '>' || c == '<' || c == '|';
}

int	strfchr(char *str, int(*f)(int), int inverted)
{
	int	k;

	k = -1;
	while (str[++k])
		if (f(str[k]) ^ inverted)
			return (k);
	return (k);
}

void	escape_quoted(char *str)
{
	int fk;
	int tk;
	int in;
	int	esc;

	fk = 0;
	tk = 0;
	in = 0;
	while (str[fk])
	{
		if (in == 0 && str[fk] == '\"')
		{
			in = 2;
			fk++;
			continue;
		}
		else if (in == 0 && str[fk] == '\'')
		{
			in = 1;
			fk++;
			continue;
		}
		else if (in == 1 && str[fk] == '\'')
		{
			in = 0;
			fk++;
			continue;
		}
		else if (in == 2 && str[fk] == '\"')
		{
			in = 0;
			fk++;
			continue;
		}
		else
		{
			if (str[fk] >= 0)
				str[tk++] = str[fk++] - (!!in * 128);
			else
				str[tk++] = str[fk++];
			if (fk > tk)
				str[fk - 1] = 0;
		}
	}
}

void	unescape(char *str)
{
	while (*str)
	{
		if (*str < 0)
			*str += 128;
		str++;
	}
}

int		count_(char *str, char c, int len)
{
	int	out;

	out = 0;
	while (--len >= 0)
		out += str[len] == c;
	return (out);
}

void	strend(char *str)
{
	static char	c = 0;
	char		temp;

	temp = c;
	c = *str;
	*str = temp;
}

void	strnesc(char *str, int len)
{
	if (!str || !*str)
		return ;
	if (len > 0)
		while (--len >= 0)
			*str++ -= 128;
	else
		strnesc(str, ft_strlen(str));
}

t_bst *bst;

void	expand_variables(char **str)
{
	t_strbuilder	*builder;
	int 			chr;
	int				k;
	char			*temp;
	int m = 0;

	builder = ft_strbuilder_new();
	k = 0;
	chr = ft_strchri((*str), '$');
	while (chr > -1)
	{
		if (chr > 0)
			ft_strbuilder_addstr(builder, (*str) + k, chr);
		k += chr + 1;
	
		if (count_(*str, '\'', k) % 2 == 0)
		{
			int ve = strfchr((*str) + k, w, 1);
			strend((*str) + k + ve);
			temp = ft_bst_getvar(bst, (*str) + k);
			if (temp && *temp)
			{
				temp = ft_strdup(temp);
				//printf("Fetching $%s: \"%s\"\n", (*str) + k, temp);
				strnesc(temp, 0);
				ft_strbuilder_addstr(builder, temp, 0);
				free(temp);
			}
			strend((*str) + k + ve);
			k += ve;
		}
		chr = ft_strchri((*str) + k, '$');
	}
	ft_strbuilder_addstr(builder, (*str) + k, 0);
	free(*str);
	*str = ft_strbuilder_build(builder);
	ft_strbuilder_free(&builder);
}

void	parse(char *line)
{
	char ** commands;
	printf("\nParsing : \t[%s]\n", line);
	expand_variables(&line);
	//printf("After var expansion :\n\t[%s]\n", line);
	escape_quoted(line);
	//printf("After quote eval :\n\t[%s]\n", line);
	printf("Final :\n");
	commands = ft_split(line, '|');
	while (*commands)
	{
		printf("\t");
		char **words = ft_split(*commands++, ' ');
		while  (*words)
		{
			unescape(*words);
			printf("[%s] ", *words++);
		}
		printf("\n");
	}
	printf("\n");
}

int	main(int argc, char **argv)
{
	ft_bst_setvar(&bst, "ARG", "1 2");
	ft_bst_setvar(&bst, "SPACE", " ");
	ft_bst_setvar(&bst, "EMPTY", "");
	ft_bst_setvar(&bst, "PIPE", "|");
	ft_bst_setvar(&bst, "CMD", "\"t .txt\"");

	//split avec fonction plutot que char
	parse(ft_strdup("egrep $ARGS$ARG <   \"in .txt\" | cat>$NOT $ARG"));
	parse(ft_strdup("echo \"$PIPE\"\'$PIPE\'"));
	parse(ft_strdup("echo \"$PIPE\" \'$PIPE\'"));
	parse(ft_strdup("echo \"$PIPE\"|\'$PIPE\'"));
	parse(ft_strdup("cat $CMD\"a b\""));
	parse(ft_strdup("echo $SPACE$EMPTY$SPACE$NOT$SPACE."));

	ft_bst_free(&bst);
	return 0;
}

// https://unix.stackexchange.com/questions/234755/command-line-processing-tokens-and-metacharacters
//  This is not a very good explanation. A token is a sequence of characters
//  that forms a word or punctuation sign. Characters like < and | are part of
//  tokens too. You may call them metacharacters but this is not useful
//  terminology. The basic rules are:

// Whitespace is not part of a token and separates tokens.
// A token is made up of ordinary characters, or of operator
// characters ()<>&|;, but not both. For example, foo<@a&>b consists
// of the tokens foo (ordinary), < (operator), @a (ordinary),
// &> (operator) and b.
// Then there are additional rules about quoting: special characters
// lose their meaning if they're quotes, with different rules depending
// on the type of quote. For example, foo'&&'bar\|qux is a single token
// with the character sequence foo&&bar|qux.
