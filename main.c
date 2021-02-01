#include "include/telega_bot.h"
#include <stdlib.h>

int main()
{
	telebot_handler_t handle;
	mode_e mode = none;
	if (telebot_create(&handle, token) != TELEBOT_ERROR_NONE)
		{
			printf("Error in creating bot\n");
			exit (-1);		
		}
	telebot_user_t me;
	if (telebot_get_me(handle, &me) != TELEBOT_ERROR_NONE)
		{
			printf ("Error in getting bot info\n");
			telebot_destroy(handle);
			exit (-1);
		}
	telebot_put_me(&me);
	telebot_reply_keyboard_markup_t keyboard;
	telebot_keyboard_button_t button[4];
	keyboard.keyboard = button;
	button[0].text = "check_active";
	button[1].text = "add_user";
	button[2].text = "exit";
	button[3].text = "show_all";
	reply_mark  = keyboar_to_str(keyboard, 4);
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
			if (message.from->id != 753969222)
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
				commad_t command = check_command(message.text);
					if (command == exit_command)
					{
						mode = none;
						offset = updates[index].update_id + 1;
							continue;
					}
					else if (command ==  active && mode != add_user_mod )
					{
						if (active_user_send(handle, message) != TELEBOT_ERROR_NONE)
							printf("Error in sending message");
						offset = updates[index].update_id + 1;
							continue;
					}
					else if (command == add_user || mode == add_user_mod) 
					{
						if (add_user_send(handle, message, &mode) != TELEBOT_ERROR_NONE)
						printf("Error in sending message");
						offset = updates[index].update_id + 1;
							continue;
					}
					else if (command == show_all) 
					{
							if (all_users_send(handle, message) != TELEBOT_ERROR_NONE)
								printf("Error in sending message");
							offset = updates[index].update_id + 1;
							continue;
					}
					else   
					{
						ret = telebot_send_message(handle, message.chat->id, "Unknown command master!\n", "HTML", false, false, 0, "");
								if (ret != TELEBOT_ERROR_NONE)
							printf("Error in sending message");
						offset = updates[index].update_id + 1;
							continue;
					}

				}
         
			}
        }
        telebot_put_updates(updates, count);
        sleep(1);
	}
}
