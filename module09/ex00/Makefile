NAME	= btc
CC		= c++
CFLAGS	= -Wall -Werror -Wextra -std=c++98
MFILES	= $(wildcard ./*.cpp)

all	: $(NAME)

$(NAME): $(MFILES)
	$(CC) -o $(NAME) $(CFLAGS) $(MFILES)

clean	:
	@rm -rf $(NAME)

fclean : clean
re : fclean all

.PHONY: all run clean fclean re
