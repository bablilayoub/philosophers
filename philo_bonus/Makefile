NAME			=	philo_bonus
HEADER			=	philosophers.h
CC				=	cc
CFLAGS			=	-Wall -Wextra -Werror
SRCS			=	main.c utils.c init.c routing.c time.c checker.c
OBJ				=	$(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@echo "Compiling $(NAME)..."
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo "- Compiled -"

%.o: %.c $(HEADER)
	@echo "Making object file .."
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "Cleaning ..."
	@rm -f $(OBJ)
	@echo "Cleaning Done"

fclean : clean
	@echo "Full Cleaning ..."
	@rm -f $(OBJ) $(NAME)
	@echo "Full Cleaning Done"

re: fclean all

.PHONY: clean