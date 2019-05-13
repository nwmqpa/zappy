
SERVER		=	zappy_server
AI		=	zappy_ai

ROOT		=	.

SERVER_DIR	=	$(ROOT)/server

AI_DIR		=	$(ROOT)/ai

DEFAULT		=	\e[0m
WHITE		=	\e[1;97m
RED		=	\e[1;91m
GREEN		=	\e[1;92m
YELLOW		=	\e[1;93m
BLUE		=	\e[1;94m
MAGENTA		=	\e[1;95m
CYAN		=	\e[1;96m

V		=	@

all:			$(SERVER) $(AI)

			
$(SERVER):		$(SERVER_DIR)/$(SERVER)
			$(V)printf "$(WHITE)Copying $(GREEN)$(SERVER)$(WHITE) from $(BLUE)$(SERVER_DIR)$(WHITE) folder$(DEFAULT)\n"
			$(V)cp $(SERVER_DIR)/$(SERVER) $(SERVER)
			
$(AI):			$(AI_DIR)/$(AI)
			$(V)printf "$(WHITE)Copying $(GREEN)$(AI)$(WHITE) from $(BLUE)$(AI_DIR)$(WHITE) folder$(DEFAULT)\n"
			$(V)cp $(AI_DIR)/$(AI) $(SERVER)

$(SERVER_DIR)/$(SERVER):
			$(V)printf "$(WHITE)Making $(GREEN)$(SERVER)$(DEFAULT)\n"
			$(V)make --no-print-directory -C $(SERVER_DIR)

$(AI_DIR)/$(AI):
			$(V)printf "$(WHITE)Making $(GREEN)$(AI)$(DEFAULT)\n"
			$(V)make --no-print-directory -C $(AI_DIR)

clean:
			$(Vprintf "$(WHITE)Cleaning $(BLUE)objects $(WHITE)files$(DEFAULT)\n"
			$(V)make --no-print-directory -C server clean
			$(V)make --no-print-directory -C ai clean

fclean:			clean
			$(V)printf "$(WHITE)Cleaning $(GREEN)binaries $(WHITE)files$(DEFAULT)\n"
			$(V)rm -f $(SERVER)
			$(V)make --no-print-directory -C server fclean
			$(V)rm -f $(AI)
			$(V)make --no-print-directory -C ai fclean

re:			fclean all

.PHONY:			all clean re echo_build_parts
