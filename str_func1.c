#include "shell.h"

/**
 * _getline - get line of string from file
 * @lnptr: variable to store string
 * @size: number of strings stored
 * @fd: file to read from
 *
 * Return: the lenghh of lnptr or -1 on failure
 */

int _getline(char **lnptr, size_t *size, int fd)
{
	char buffer[BUFFER_t + 1];
	int r = BUFFER_t, len = 0, mode = isatty(0);
	char *tmp;

	*lnptr = (char *)_malloc(4);
	**lnptr = '\0';
	while (r == BUFFER_t)
	{
		if (*lnptr && len > 0)
			if ((*lnptr)[len - 1] == '\n' && mode)
				break;
		r = read(fd, buffer, BUFFER_t);
		if (r < 0 && errno == EINTR)
		{
			**lnptr = '\n',	*(*lnptr + 1) = '\n', len = 2;
			return (len);
		}
		if (r < 0)
			exit(-1);
		if (r == 0 && mode)
			return (-1);
		tmp = _realloc(*lnptr, len + r + 4);
		*size = len + r + 4, *lnptr = tmp;
		buffer[r] = '\0', _strcat(*lnptr, buffer), len += r;
		if (!mode)
			find_n_rep(lnptr, "\n", ";");
	}
	if (!mode)
	{
		tmp = _realloc(*lnptr, _strlen(*lnptr) + 3);
		*lnptr = tmp;
		(*lnptr)[len] = '\n', (*lnptr)[len + 1] = '\0';
	}
	return (len);
}

/**
 * _strcmpd - custom strcmp
 * @fstring: fstring
 * @sub: subset
 *
 * Return: 1 on success and -1 on faliur
 */

int _strcmpd(char *fstring, const char *sub)
{
	if (!fstring || !sub)
		return (-1);
	if (!*fstring)
		return (-1);
	if (_strlen(fstring) < _strlen(sub))
		return (-1);
	while (*sub)
	{
		if (*sub == *fstring)
			return (1);
		sub++;
	}
	return (-1);
}

/**
 * _strcmps - alternate custom strcmp
 * @fstring: fstring
 * @sub: subset
 * Return: 1 on success and -1 on faliur
 */

int _strcmps(char *fstring, const char *sub)
{
	if (!fstring || !sub)
		return (-1);
	if (!*fstring)
		return (-1);
	if (_strlen(fstring) < _strlen(sub))
		return (-1);
	while (*sub && *fstring)
	{
		if (*sub != *fstring)
			return (-1);
		sub++, fstring++;
	}
	return (1);
}

/**
 * _strtok - tokenize string
 * @str: string to be tokenized
 * @delimeter: token delimiter
 * @whichf: which strcmp to use, 0 for strcmpd, and 1 for strcmps
 *
 * Return: a character pointer to the current delimited token
 */

char *_strtok(char *str, const char *delimeter, int whichf)
{
	static char *save;
	char *_new = NULL;
	int i = 0, (*func)(char *, const char *), loc;

	func = (whichf == 0) ? _strcmpd : _strcmps;
	loc = (whichf) ? _strlen(delimeter) - 1 : 0;
	if (!str || !*str)
	{
		if (!save || !*save)
			return (NULL);

		while (func(save + i, delimeter) != 1 && *(save + i) != '\0')
			i++;
		if (*(save + i) == '\0')
		{
			_new = save, save = NULL;
			return (_new);
		}
		_new = save;
		*(save + i) = '\0';
		save = save + i + loc + 1;

		return (_new);

	}
	while (func(str + i, delimeter) != 1 && *(str + i) != '\0')
		i++;

	if (*(str + i) == '\0')
	{
		save = NULL;
		return (str);
	}
	save = str + i + loc + 1;
	*(str + i) = '\0';
	return (str);
}
