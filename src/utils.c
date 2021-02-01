#include "../include/telega_bot.h"

commad_t check_command(char *str)
{
	commad_t ret = fail;
	if (strcmp(str, "check_active") == 0)
		ret = active;
	else if (strcmp(str, "add_user") == 0)
		ret = add_user;
	else if (strcmp(str, "show_all") == 0)
		ret = show_all;
	else if (strcmp(str, "exit") == 0)
		ret = exit_command;
	return (ret);
}

char *get_all_users(int *number_of_lines)
{
int fd , len = 0;
char buff = 0;
int words = 0;
char *ret = NULL;
if (system("bash get_users.sh"))
	return (ret);
if (system("sort all_users.txt  | nl -s ') ' | sed 's/   //g' > sorted.txt"))
	return (ret);
fd = open("sorted.txt", O_RDONLY);
if (fd < 0)
	return (ret);
while (read(fd, &buff, 1) == 1)
{	
	if (buff == '\n')
		words++;
	len++;
}
char mass[len];
mass[len] = '\0';
close (fd);
fd = open("sorted.txt", O_RDONLY);
if (fd < 0)
	return (NULL);
int i = 0 ;
read(fd, mass, len);
close (fd);
ret = malloc(len);
strcpy(ret, mass);
*number_of_lines = words;
return (ret);
}