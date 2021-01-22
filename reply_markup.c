#include "../include/telebot.h"
#include <string.h>
#include <stdio.h>

char *keyboar_to_str(telebot_reply_keyboard_markup_t *keyboard)
{
	//{\"keyboard\":[[{\"text\":\"button 1\"},{\"text\":\"button 2\"}]],\"resize_keyboard\":true}

	char final_str[] = "{\"keyboard\":[[{\"text\":\"button 1\"},{\"text\":\"button 2\"}]],\"resize_keyboard\":true}";
	char butt_str[] = "{\"text\":\"%s\"}";
	char to_ret [150];
	memset(to_ret, 0, 150);
	sprintf(to_ret, )
}