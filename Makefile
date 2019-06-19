DOCKER_CROSS_SWITCH = devkitpro/devkita64


GRAPHIC_BASE		=	zappy_graphic_
GRAPHIC_SWITCH		=	$(GRAPHIC_BASE)switch.nro
GRAPHIC_LINUX		=	$(GRAPHIC_BASE)linux
SERVER				=	zappy_server
AI					=	zappy_ai

ROOT				=	.

GRAPHIC_DIR			=	$(ROOT)/graphic_client

SERVER_DIR			=	$(ROOT)/server

AI_DIR				=	$(ROOT)/ai

DEFAULT				=	\e[0m
WHITE				=	\e[1;97m
RED					=	\e[1;91m
GREEN				=	\e[1;92m
YELLOW				=	\e[1;93m
BLUE				=	\e[1;94m
MAGENTA				=	\e[1;95m
CYAN				=	\e[1;96m

V					=	@

all:				$(SERVER) $(AI) $(GRAPHIC_LINUX)

switch:				clean_switch $(GRAPHIC_SWITCH)
clean_switch:
					$(V)rm -f $(GRAPHIC_SWITCH)
					$(V)rm -f $(GRAPHIC_DIR)/$(GRAPHIC_SWITCH)

$(GRAPHIC_SWITCH):	$(GRAPHIC_DIR)/$(GRAPHIC_SWITCH)
					$(V)printf "$(WHITE)Copying $(GREEN)$(GRAPHIC_SWITCH) from $(BLUE)$(GRAPHIC_DIR)$(WHITE) folder $(DEFAULT)\n"
					$(V)cp $(GRAPHIC_DIR)/$(GRAPHIC_SWITCH) $(GRAPHIC_SWITCH)

$(GRAPHIC_LINUX):	$(GRAPHIC_DIR)/$(GRAPHIC_LINUX)
					$(V)printf "$(WHITE)Copying $(GREEN)$(GRAPHIC_LINUX) from $(BLUE)$(GRAPHIC_DIR)$(WHITE) folder $(DEFAULT)\n"
					$(V)cp $(GRAPHIC_DIR)/$(GRAPHIC_LINUX) $(GRAPHIC_LINUX)

$(SERVER):			$(SERVER_DIR)/$(SERVER)
					$(V)printf "$(WHITE)Copying $(GREEN)$(SERVER)$(WHITE) from $(BLUE)$(SERVER_DIR)$(WHITE) folder$(DEFAULT)\n"
					$(V)cp $(SERVER_DIR)/$(SERVER) $(SERVER)
			
$(AI):				$(AI_DIR)/$(AI)
					$(V)printf "$(WHITE)Copying $(GREEN)$(AI)$(WHITE) from $(BLUE)$(AI_DIR)$(WHITE) folder$(DEFAULT)\n"
					$(V)cp $(AI_DIR)/$(AI) $(AI)

$(GRAPHIC_DIR)/$(GRAPHIC_BASE)switch.nro:
					$(V)printf "$(WHITE)Cross-Compiling $(GREEN)$(GRAPHIC_DIR)/$(GRAPHIC_SWITCH)$(DEFAULT)\n"
					$(V)sudo docker container run --rm -v $(PWD)/$(GRAPHIC_DIR):/volume $(DOCKER_CROSS_SWITCH) bash -c "PLATFORM=switch make --no-print-directory -C volume"

$(GRAPHIC_DIR)/$(GRAPHIC_BASE)%:
					$(V)PLATFORM=$< make --no-print-directory -C graphic_client

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

fclean:				clean
					$(V)printf "$(WHITE)Cleaning $(GREEN)binaries $(WHITE)files$(DEFAULT)\n"
					$(V)rm -f $(SERVER)
					$(V)make --no-print-directory -C server fclean
					$(V)rm -f $(AI)
					$(V)make --no-print-directory -C ai fclean
					$(V)rm -f $(GRAPHIC_BASE)*
					$(V)make --no-print-directory -C graphic_client fclean

re:					fclean all

.PHONY:				all clean re echo_build_parts
