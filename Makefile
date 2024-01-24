NAME			=	philo
HEADER			=	./philo/philosophers.h
CC				=	cc
CFLAGS			=	-Wall -Wextra -Werror
SRCS			=	./philo/main.c ./philo/utils.c ./philo/ft_atoi.c
OBJ				=	$(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@echo "Compiling $(NAME)..."
	@$(CC) $(CFLAGS) $(OBJ) -o ./philo/$(NAME)
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
	@rm -f $(OBJ) ./philo/$(NAME)
	@echo "Full Cleaning Done"

re: fclean all

.PHONY: comp_start clean