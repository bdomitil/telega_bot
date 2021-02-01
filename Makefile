files.c = src/linker.c src/reply_markup.c src/active_users.c src/utils.c src/commands.c main.c 

files.o = $(files.c:.c=.o)

CC = gcc


NAME = telega_bot

all :	$(NAME)

$(NAME) :  $(files.o)
			$(CC)  -g $(files.o) include/gnl.a include/libft.a include/libtelebot.so -o $(NAME) -lcurl
			
%.o : %.c 
			@gcc  -g -c  $<  -o $@ 
			@echo "\033[36m$<\033[0m \033[35m is compiled!\033[0m"

re : 		fclean $(NAME)

clean :	
			@rm -rf $(files.o)

fclean :	
			@rm -rf $(files.o) $(NAME)