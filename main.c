#include "include/telebot.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "../gnl/get_next_line.h"
# define SIZE_OF_ARRAY(array) (sizeof(array) / sizeof(array[0]))
# define token "1452987339:AAFAIrbzKsnAVdQDhiJkCZs7irwpyMvS0Xc"

char *active();

typedef enum
{
	add_user,
	none
} mode_e;

int main()
{
telebot_handler_t handle;
mode_e mode = none;
if (telebot_create(&handle, token) != TELEBOT_ERROR_NONE)
	{
		printf("Error in creating bot\n");
		exit(-1);
	}
telebot_user_t me;
if (telebot_get_me(handle, &me) != TELEBOT_ERROR_NONE)
	{
		printf ("Error in getting bot info\n");
		telebot_destroy(handle);
		exit (-1);
	}
printf("ID: %d\n", me.id);
printf("First Name: %s\n", me.first_name);
printf("User Name: %s\n", me.username);

telebot_put_me(&me);
int index, count, offset = -1;
telebot_error_e ret;
telebot_message_t message;
telebot_update_type_e update_types[] = {TELEBOT_UPDATE_TYPE_MESSAGE};
	while (1)
	{
		telebot_update_t *updates;
        ret = telebot_get_updates(handle, offset, 20, 0, update_types, 0, &updates, &count);
        if (ret != TELEBOT_ERROR_NONE)
            continue;
		for (index = 0; index < count; index++)
        {
            message = updates[index].message;
			char str[4096];
			if (strcmp(message.from->username, "telega_gaga") != 0)
			{
				snprintf(str, SIZE_OF_ARRAY(str), "You are not authorized\n");
				ret = telebot_send_message(handle, message.chat->id, str, "HTML", false, false, updates[index].message.message_id, "");
				if (ret != TELEBOT_ERROR_NONE)
					printf("Error in sending message");
				offset = updates[index].update_id + 1;
							continue;

			}
			 else 
			{			
				if (message.text)
				{
/*exit adding*/		if (strcmp(message.text, "/exit") == 0)
					{
						mode = none;
						offset = updates[index].update_id + 1;
							continue;
					}

/*start*/			if (strcmp(message.text, "/start") == 0 && mode != add_user)
					{
						ret = telebot_send_message(handle, message.chat->id, "Hello master\n", "HTML", false, false,0, "");
					if (ret != TELEBOT_ERROR_NONE)
					printf("Error in sending message");
					}
					
/*active_user*/			if (strcmp(message.text, "/active") == 0 && mode != add_user)
						{
							char *text = active();
							if (text != NULL)
							{
							ret = telebot_send_message(handle, message.chat->id, text, "HTML", false, false, 0, "");
								if (ret != TELEBOT_ERROR_NONE)
							printf("Error in sending message");
							free(text);
							}
						}
/*add_user*/		if (strcmp( message.text, "/add_user") == 0 || mode == add_user)
					{
						if (strstr(message.text, "/") != NULL && mode == add_user)
							{
								ret = telebot_send_message(handle, message.chat->id, "В режиме добавления пользователя\n введите имя или /exit чтобы выйти", "HTML", false, false, 0, "");
								if (ret != TELEBOT_ERROR_NONE)
							printf("Error in sending message");
							offset = updates[index].update_id + 1;
						continue;
							}
						if (mode != add_user)
						{
						mode = add_user;
						ret = telebot_send_message(handle, message.chat->id, "Введите имя пользователя\n", "HTML", false, false, 0, "");
								if (ret != TELEBOT_ERROR_NONE)
							printf("Error in sending message");
						}
						else
						{
							setenv("client", message.text, 1);
							if (system("bash add_user.sh") != 0)
							{
								ret = telebot_send_message(handle, message.chat->id, "Неверное имя пользователя\n", "HTML", false, false, 0, "");
								if (ret != TELEBOT_ERROR_NONE)
							printf("Error in sending message");
							}
							else 
							{
								ret = telebot_send_message(handle, message.chat->id, "Успешно создан!\n", "HTML", false, false, 0, "");
								if (ret != TELEBOT_ERROR_NONE)
							printf("Error in sending message");
							char file_name[100];
							sprintf(file_name, "/vpn_clients/%s.ovpn", message.text);
							
								ret = telebot_send_document(handle, message.chat->id, file_name, true, NULL, "", NULL, false, 0, "");
								if (ret != TELEBOT_ERROR_NONE)
							printf("Error in sending message");
								mode = none;
							}		
						}
					}
				}
				offset = updates[index].update_id + 1;
					continue;

			}
            // if (message.text)
            // {
            //     printf("%s: %s \n", message.from->first_name, message.text);
            //     if (strstr(message.text, "/dice"))
            //     {
            //         telebot_send_dice(handle, message.chat->id, false, 0, "");
            //     }
            //     else
            //     {
                
            //         if (strstr(message.text, "/start"))
            //         {
            //             snprintf(str, SIZE_OF_ARRAY(str), "Hello %s", message.from->first_name);
            //         }
            //         else
            //         {
            //             snprintf(str, SIZE_OF_ARRAY(str), "<i>%s</i>", message.text);
            //         }
            //         ret = telebot_send_message(handle, message.chat->id, str, "HTML", false, false, updates[index].message.message_id, "");
            //     }
            //     if (ret != TELEBOT_ERROR_NONE)
            //     {
            //         printf("Failed to send message: %d \n", ret);
            //     }
            // }
            
        }
        telebot_put_updates(updates, count);

        sleep(1);




	}
}
