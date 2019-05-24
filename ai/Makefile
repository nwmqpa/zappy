##
## Makefile zappy_ai
## michel-ange.sherfan@epitech.eu
## 2019
##

ROOT		=	.

NAME		=	zappy_ai

V		=	@

#----------------COLORS------------------#

RED		=	\e[31;1m

BLUE		=	\e[32;1m

GREEN		=	\e[33;1m

WHITE		=	\e[0m

all: 		$(NAME)

$(NAME):
		$(V)printf "$(GREEN)[Building project]\n$(WHITE)"
		$(V)echo "#!/usr/bin/env python3" > $(NAME)
		$(V)cat main.py >> $(NAME)
		$(V)chmod +x $(NAME)
		$(V)printf "$(BLUE)[Project build]\n$(WHITE)"

clean:
		$(V)printf "$(RED)[Cleaning binary]\n$(WHITE)"
		$(V)rm -rf $(NAME)
		$(V)rm -rf __pycache__/

fclean: 	clean
		$(V)printf "$(RED)[Cleaning repository]\n$(WHITE)"
		$(V)rm -rf $(NAME)

re: 		fclean all
