##
## Makefile zappy_ai
## michel-ange.sherfan@epitech.eu
## 2019
##

ROOT	=	.

NAME	=	zappy_ai

V		=	@

#----------------COLORS------------------#

RED		=	\e[31;1m

BLUE	=	\e[32;1m

GREEN	=	\e[33;1m

WHITE	=	\e[0m

all: $(NAME)

$(NAME):
		@printf "$(GREEN)[Building project]\n$(WHITE)"
		@echo "#!/usr/bin/env python3" > $(NAME)
		@cat main_ai >> $(NAME)
		@chmod +x $(NAME)
		@printf "$(BLUE)[Project build]\n$(WHITE)"

clean:
		@printf "$(RED)[Cleaning binary]\n$(WHITE)"
		$(V)rm -rf $(NAME)
		$(V)rm -rf __pycache__/

fclean: clean
		@printf "$(RED)[Cleaning repository]\n$(WHITE)"
		$(V)rm -rf $(NAME)

re: fclean all