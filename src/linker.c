#include <curl/curl.h>
#include <stdio.h>
#include <stdlib.h>
#include "../include/get_next_line.h"

char *changed_link = NULL;

void function_pt(void *ptr, size_t size, size_t nmemb, void *stream){
	changed_link = (char*)ptr;
	return ;
}

char *change_link(char *link)
{
	CURL *curl;
	CURLcode res;
	char *ret;
	changed_link = NULL;

	link = ft_strjoin("https://clck.ru/--?url=" ,link);
	curl = curl_easy_init();
	if (curl)
	{
		curl_easy_setopt(curl, CURLOPT_URL, link);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, function_pt);
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
		curl_easy_perform(curl);
		if (!res)
		{
			curl_easy_cleanup(curl);
			free(link);
			return NULL;
		}
		else
		{ 
		curl_easy_cleanup(curl);
		free(link);
		return changed_link;
		}
	}
}