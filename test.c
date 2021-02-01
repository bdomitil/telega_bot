#include "include/telega_bot.h"

char *get_text()
{
	int fd;
	char q = 0;
	int size = 0;
	fd = open("all_users.txt", O_RDONLY);
	while (read(fd, &q, 1) == 1)
			size++;
	char mass[size];
	mass[size] = '\0';
	close (fd);
	char *ret = malloc(size);
	fd = open("all_users.txt", O_RDONLY);
	read(fd, mass, size);
	close(fd);
	strcpy(ret, mass);
	return ret;
}

int main()
{
	int num_lines = 79;
	int strlen = 0;
	int pos = 0;
	int i =  0;
	int new_lines = 0;
	char *text = get_text();
	char *temp = NULL;
	int number_of_messages = num_lines / 30 + 1;
		while (i < number_of_messages)
		{
		while (new_lines < 30 && text[strlen] != '\0')
			if (text[strlen++] == '\n')
				new_lines++;
		temp = ft_substr(text, pos, strlen- pos);
		printf("temp = %s\n " , temp);
		pos = strlen;
		new_lines = 0;
		free(temp);
		temp = NULL;
		i++;
		}
	float a = 28 / 30;
	int b = a;
	printf("res = %d\n", b);
	free(text);
}