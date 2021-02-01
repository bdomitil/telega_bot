#include "../include/telega_bot.h"

 telebot_error_e active_user_send(telebot_handler_t handle, telebot_message_t message)
{
	telebot_error_e ret = TELEBOT_ERROR_NONE;
	char *text = get_active_user();
	if (text != NULL)
	{
	ret = telebot_send_message(handle, message.chat->id, text, "HTML", false, false, 0, reply_mark);
		if (ret != TELEBOT_ERROR_NONE)
		printf("Error in sending message");
	free(text);
	}
	return ret;
}

telebot_error_e add_user_send(telebot_handler_t handle, telebot_message_t message, mode_t *mode) 
{
	telebot_error_e ret = TELEBOT_ERROR_NONE;
	if (*mode != add_user_mod)
	{
		ret = telebot_send_message(handle, message.chat->id, "Введите имя пользователя\n", "HTML", false, false, 0, "");
								if (ret != TELEBOT_ERROR_NONE)
							printf("Error in sending message");
		*mode = add_user_mod;
	}
	else 
	{
		setenv("client", message.text, 1);
		if (system("bash add_user.sh") != 0)
		{
			ret = telebot_send_message(handle, message.chat->id, "Неверное имя пользователя\n", "HTML", false, false, 0, reply_mark);
			if (ret != TELEBOT_ERROR_NONE)
				printf("Error in sending message");
		}
		else 
		{
			ret = telebot_send_message(handle, message.chat->id, "Успешно создан!\n", "HTML", false, false, 0, reply_mark);
			if (ret != TELEBOT_ERROR_NONE)
				printf("Error in sending message");
		char file_name[100];
		char path[100];
		sprintf(path, "95.163.182.122/Xsa23aw49/%s.ovpn", message.text);
		sprintf(file_name, "/vpn_clients/%s.ovpn", message.text);
		char *res = change_link(path);
			ret = telebot_send_document(handle, message.chat->id, file_name, true, NULL, res, "HTML", false, 0, reply_mark);
		setenv("client", "", 1);
			if (ret != TELEBOT_ERROR_NONE)
		printf("Error in sending message");
			*mode = none;
		}	
	}
	return ret;
}

 telebot_error_e all_users_send(telebot_handler_t handle, telebot_message_t message)
 {
	telebot_error_e ret = TELEBOT_ERROR_NONE;
	int num_lines = 0;
	int strlen = 0;
	int pos = 0;
	int i =  0;
	int new_lines = 0;
	char *text = get_all_users(&num_lines);

	char *temp = NULL;
	int number_of_messages = num_lines / 30 + 1;
	if (text != NULL)
		while (i < number_of_messages)
		{
		while (new_lines < 30 && text[strlen] != '\0')
			if (text[strlen++] == '\n')
				new_lines++;
		char **buttons = ft_split(&text[pos], '\n');
		char *custom_reply = inline_key_to_str(buttons, 2, new_lines);
		for (int j = 0; j < new_lines; j++)
			free(buttons[j]);
		free(buttons);
		temp = ft_substr(text, pos, strlen- pos);
		pos = strlen;
		new_lines = 0;
		i++;
		ret = telebot_send_message(handle, message.chat->id, "__", "HTML", false, false, 0, custom_reply);
		if (ret != TELEBOT_ERROR_NONE)
		printf("Error in sending message");
		free(temp);
		temp = NULL;
		free(custom_reply);
		custom_reply = NULL;
		}
		free(text);
	return ret;
 }