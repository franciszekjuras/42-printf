NAME = libftprintf.a

FILES =	ft_printf ft_put_format ft_parse_format

OFILES = $(FILES:%=%.o)

CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

bonus: $(NAME)

$(NAME): $(OFILES) libft/libft.a
	cp -f libft/libft.a $@
	ar rcs $@ $(OFILES)

$(OFILES): %.o: %.c
	gcc $(CFLAGS) -c $< -o $@

libft/libft.a: FORCE
	make -C libft libft.a

FORCE: ;

clean:
	rm -f $(OFILES)
	make -C libft fclean

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re FORCE
