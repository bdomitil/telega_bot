#ifndef TELEGA_BOT_H
#define TELEGA_BOT_H
#include "telebot.h"
#include "get_next_line.h"
#include "libft.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
# define SIZE_OF_ARRAY(array) (sizeof(array) / sizeof(array[0]))
# define token "1452987339:AAFAIrbzKsnAVdQDhiJkCZs7irwpyMvS0Xc"

typedef enum 
{
	active,
	add_user,
	show_all,
	exit_command, 
	fail
}		commad_t;



typedef enum
{
	add_user_mod,
	none
} mode_e;

char *get_active_user();
char *change_link(char *link);
char *inline_key_to_str(char **text_of_buttoms, int columns, int num_of_buttons);
char *keyboar_to_str(telebot_reply_keyboard_markup_t keyboard, int num_of_buttons);
commad_t check_command(char *str);
char *get_all_users(int *number_of_lines);
telebot_error_e active_user_send(telebot_handler_t handle, telebot_message_t message);
telebot_error_e add_user_send(telebot_handler_t handle, telebot_message_t message, mode_t *mode);
telebot_error_e all_users_send(telebot_handler_t handle, telebot_message_t message);
char *reply_mark;



#endif