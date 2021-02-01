#include "../include/telega_bot.h" 

char *keyboar_to_str(telebot_reply_keyboard_markup_t inline_keyboard, int num_of_buttons)
{
	//char *final_str_sh = "{\"keyboard\":[[{\"text\":\"button 1\"},{\"text\":\"button 2\"}]],\"resize_keyboard\":true}";
	char *final_str = NULL;
	char *start = "{\"keyboard\":[";
	char *end = "],\"resize_keyboard\":true}";
	// char *end = "]}";
	char *remove_keyboard = "{\"keyboard\":[],\"remove_keyboard\":true}";
	char *temp;

	if (num_of_buttons > 0)
	{
		int i = 0;
		final_str = ft_strjoin(start, "[");
		while (i < num_of_buttons)
		{
			char buff[100];
			memset(buff, 0, 100);
			sprintf(buff, "{\"text\":\"%s\"}", inline_keyboard.keyboard[i].text);
			temp = final_str;
			final_str = ft_strjoin(final_str, buff);
			free(temp);
			i++;
			if (i < num_of_buttons)
			{	
				temp = final_str;
				final_str = ft_strjoin(final_str, ",");
				free(temp);
			}
			else 
			{
				temp = final_str;
				final_str = ft_strjoin(final_str, "]");
				free(temp);
			}
		}
		temp = final_str;
		if (!final_str)
			final_str = ft_strjoin(start, end);
		else 
		{
			temp = final_str;
			final_str = ft_strjoin(final_str, end);
		}
	}
	else if (num_of_buttons == -1)
		final_str = ft_strjoin(final_str, remove_keyboard);
	if (final_str == NULL)
		final_str = ft_strjoin(final_str, "");
	return(final_str);
}

char *inline_key_to_str(char **mass, int columns ,int num_of_buttons)
{
	//char *final_str_sh = "{\"keyboard\":[[{\"text\":\"button 1\"},{\"text\":\"button 2\"}]],\"resize_keyboard\":true}";
	char *final_str = NULL;
	char *start = "{\"inline_keyboard\":[";
	char *end = "]}";
	// char *end = "]}";
	char *remove_keyboard = "{\"keyboard\":[],\"remove_keyboard\":true}";
	char *temp;

	if (num_of_buttons > 0)
	{
		int i = 0;
			final_str = ft_strjoin(start, "[");
		while (i < num_of_buttons)
		{
			char buff[100];
			memset(buff, 0, 100);
			if (i == 0)
				sprintf(buff, "{\"text\":\"%s\",\"callback_data\": \"%i\"}", mass[i], i);
			else if ((i +1) % columns == 0)
				sprintf(buff, "{\"text\":\"%s\",\"callback_data\": \"%i\"}]", mass[i], i);
			else if ((i + 1) % columns  > 0)
				sprintf(buff, "[{\"text\":\"%s\",\"callback_data\": \"%i\"}", mass[i], i);
			temp = final_str;
			final_str = ft_strjoin(final_str, buff);
			free(temp);
			i++;
			if (i < num_of_buttons)
			{	
				temp = final_str;
				final_str = ft_strjoin(final_str, ",");
				free(temp);
			}
			
			if (!(mass + i))
				break;
		}
		if (num_of_buttons % 2 > 0)
			{
				temp = final_str;
				final_str = ft_strjoin(final_str, "]");
				free(temp);
			}
		temp = final_str;
		if (!final_str)
			final_str = ft_strjoin(start, end);
		else 
		{
			temp = final_str;
			final_str = ft_strjoin(final_str, end);
		}
	}
	else if (num_of_buttons == -1)
		final_str = ft_strjoin(final_str, remove_keyboard);
	if (final_str == NULL)
		final_str = ft_strjoin(final_str, "");
	return(final_str);
}