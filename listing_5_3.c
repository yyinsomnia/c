void strcat(char *s, char *t)
{
	while (*s != '\0')
		s++;
	while (*t != '\0')
		*(s++) = *(t++);
}