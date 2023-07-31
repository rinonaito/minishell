#include	<stdio.h>
#include	<unistd.h>
#include	<limits.h>
#include	<string.h>

int	main(void)
{
	char s1[PATH_MAX];
	char *s2;

	/*** getcwd ***/
	memset(s1, '\0', PATH_MAX);//initialize the variable
	s2 = getcwd(s1, PATH_MAX);//get the currect working directory
	printf("s1:[%s]\n", s1);
	printf("s2:[%s]\n", s2);

	/*** chdir ***/
	int ret = chdir("/Users/taaraki/Documents");
	if (ret == -1)
		printf("Error chdir\n");
	memset(s1, '\0', PATH_MAX);//initialize the variable
	s2 = getcwd(s1, PATH_MAX);
	printf("s1:[%s]\n", s1);
	printf("s2:[%s]\n", s2);
	return (0);
}
