#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include "../include/get_next_line.h"

char *get_active_user()
{
	int fd = open("/etc/openvpn/server/openvpn-status.log",O_RDONLY);
		char *to_ret = NULL;
	if (fd < 1)
	{
		to_ret = ("Error in opening log file\n");
		exit(0);
	}
	else 
	{
		int number = 0;
		int result;
		char *str;
		char word[] = "ROUTING_TABLE";
		char *tmp = NULL;
		char *tmp2 = NULL;
		int comma = 0;
		while ((result = get_next_line(fd, &str)) == 1)
		{
			if((tmp = strstr(str, word)) && !strstr(str, "Virtual"))
			{
				while (comma != 2)
				{
					if (*tmp == ',')
						comma++;
				tmp++;
				}
				char *temp = tmp;
				while (*temp != ',')
					temp++;
				*temp = '\0';
				tmp2 = to_ret;
				to_ret = ft_strjoin(to_ret, tmp);
				if (tmp2)
					free(tmp2);
				tmp2 = to_ret;
				to_ret = ft_strjoin(to_ret, "\n");
				free(tmp2);
				comma = 0;
				number++;
			}
		free(str);
		str = NULL;
		tmp = NULL;	
		}
		char buff[strlen("%d users are currently active\n") + 2];
		sprintf (buff,"%d users are currently active\n",number);
		tmp2 = to_ret;
		to_ret = ft_strjoin(to_ret, buff);
		if (tmp2)
			free(tmp2);
	}
	close(fd);
	return (to_ret);
}
