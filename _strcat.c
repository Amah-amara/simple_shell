#include "shell.h"

/**
 * _strcat - concatinate 2 strings
 * @dest: string destination
 * @src: source string
 *
 * Return: concatinated string
 */

char *_strcat(char *dest, char *src)
{
	char *ptr = dest + _strlen(dest);

	while (*src)
		*ptr++ = *src++;
	*ptr = '\0';
	return (dest);
}
