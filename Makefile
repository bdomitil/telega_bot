files.c = src/active_users.c src/linker.c main.c

files.o = $(files.c:.c=.o)

CC = gcc


NAME = telega_bot

all :	$(NAME)

$(NAME) :  $(files.o)
			$(CC)  $(files.o) gnl.a libtelebot.so -o $(NAME) -lcurl
			
%.o : %.c 
			@gcc  -c  $<  -o $@ 
			@echo "\033[36m$<\033[0m \033[35m is compiled!\033[0m"

re : 		fclean $(NAME)

clean :	
			@rm -rf $(files.o)

fclean :	
			@rm -rf $(files.o) $(NAME)