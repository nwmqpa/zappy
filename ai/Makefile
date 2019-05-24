##
## Makefile zappy_ai
## michel-ange.sherfan@epitech.eu
## 2019
##

ROOT		=	.

NAME		=	zappy_ai

SOURCE		=	package.py

SHEBANG		=	/usr/bin/env python3

V		=	@

#----------------COLORS------------------#

RED		=	\e[1;91m
GREEN		=	\e[1;92m
BLUE		=	\e[1;94m
WHITE		=	\e[1;97m
DEFAULT		=	\e[0m

all: 		$(NAME)

$(NAME):
		$(V)printf "$(WHITE)Adding $(GREEN)shebang$(WHITE) to $(RED)$(SOURCE)$(DEFAULT)\n"
		$(V)echo "#!$(SHEBANG)" > $(NAME)
		$(V)cat $(SOURCE) >> $(NAME)
		$(V)chmod +x $(NAME)

clean:
		$(V)printf "$(WHITE)Cleaning $(BLUE)objects $(WHITE)files$(DEFAULT)\n"
		$(V)rm -rf __pycache__/
		$(V)find -type f -name *.pyc -delete

fclean: 	clean
		$(V)printf "$(WHITE)Cleaning $(GREEN)binary $(WHITE)files$(DEFAULT)\n"
		$(V)rm -rf $(NAME)

re: 		fclean all
