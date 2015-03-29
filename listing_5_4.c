void strend(char *s, char *t)
{
	int flag = 0;
	while (*s && *s != *t)
		s++;
	if (*s == '\0')
		return 0;
	while (*s++ == *t++ && *s && *t)
		;
	if (*s == '\0' && *t == '\0')
		return 1;
	else
		return 0;
}