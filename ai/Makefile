##
## EPITECH PROJECT, 2018
## zappy_ai
## File description:
## zappy_ai
##

NAME	=	zappy_ai

CC		=	gcc

LD		=	gcc

AR		=	ar

ROOT		=	.

BUILD_DIR	=	$(ROOT)

SRC_DIR 	=	$(ROOT)/sources

INCLUDE_DIR	=	$(ROOT)/include

MODULES		=

SOURCES		=	source/main.c \
				source/get_args.c \
				source/get_opt.c

PREFIXED_SRCS 	=	$(addprefix $(SRC_DIR)/, $(SOURCES))
PATSUBST_OBJS	=	$(patsubst  $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(PREFIXED_SRCS))
LIBS_MODULES 	=	$(addprefix lib, $(addsuffix .a, $(MODULES)))
PREFIXED_MODULS	=	$(addprefix $(SRC_DIR)/, $(MODULES))
PATSUBST_MODULS =	$(patsubst  $(SRC_DIR)/%, $(BUILD_DIR)/lib%.a, $(PREFIXED_MODULS))
LINK_MODULES	=	$(addprefix -l, $(MODULES))


WARNINGS	=	-Wall -Wextra
CFLAGS		=	-I $(INCLUDE_DIR) $(WARNINGS) -fdiagnostics-color=always
LDFLAGS		=	-L $(BUILD_DIR) $(LINK_MODULES)

DEFAULT		=	\e[0m
WHITE		=	\e[1;97m
RED			=	\e[1;91m
GREEN		=	\e[1;92m
YELLOW		=	\e[1;93m
BLUE		=	\e[1;94m
MAGENTA		=	\e[1;95m
CYAN		=	\e[1;96m

V		=	@

all:			$(ROOT)/$(NAME)

clean:
			$(Vprintf "$(WHITE)Cleaning $(BLUE)objects $(WHITE)files$(DEFAULT)\n"
			$(V)rm -f $(PATSUBST_OBJS)
			$(V)for dir in $(PREFIXED_MODULS); do \
				make --no-print-directory -C $$dir clean; \
			done

fclean:			clean
			$(V)printf "$(WHITE)Cleaning $(GREEN)linked $(WHITE)files$(DEFAULT)\n"
			$(V)rm -f $(ROOT)/$(NAME) $(BUILD_DIR)/$(NAME)
			$(V)for dir in $(PREFIXED_MODULS); do \
				make --no-print-directory -C $$dir fclean; \
			done

re:			fclean all

echo_build_parts:
			$(V)printf "$(WHITE)Binary $(GREEN)$(NAME)$(WHITE) built from:\n"
			$(V)for obj in $(PATSUBST_OBJS); do \
				printf " $(CYAN)(%dKb)\t$(BLUE)%s$(WHITE)\n" `du -s $$obj | awk -F' ' '{ print $$1 }'` `basename $$obj`; \
			done
			$(V)for module in $(PATSUBST_MODULS); do \
				printf " $(CYAN)(%dKb)\t$(YELLOW)%s$(WHITE)\n" `du -s $$module | awk -F' ' '{ print $$1 }'` `basename $$module`; \
			done

$(ROOT)/$(NAME):	$(BUILD_DIR)/$(NAME)
			$(V)printf "$(WHITE)Copying $(GREEN)$(NAME)$(WHITE) from $(BLUE)$(BUILD_DIR)$(WHITE) folder$(DEFAULT)\n"
			$(V)cp $(BUILD_DIR)/$(NAME) $(ROOT)/$(NAME)
			$(V)printf "$(WHITE)Final $(GREEN)$(NAME)$(WHITE) size: $(CYAN)%dKb$(DEFAULT)\n" `du -s $@ | awk -F ' ' '{print $$1}'`

$(BUILD_DIR)/$(NAME):	$(PATSUBST_OBJS) $(PATSUBST_MODULS) echo_build_parts
			$(V)printf "$(WHITE)Linking $(BLUE)objects $(WHITE)into $(GREEN)$(NAME)$(DEFAULT)\n"
			$(V)$(LD) -o $(BUILD_DIR)/$(NAME) $(PATSUBST_OBJS) $(LDFLAGS)

$(BUILD_DIR)/%.o:	$(SRC_DIR)/%.c
			$(V)printf "$(WHITE)Compiling $(RED)$<$(WHITE) => $(BLUE)$@$(DEFAULT)\n"
			$(V)$(CXX) -o $@ -c $< $(CFLAGS)

$(BUILD_DIR)/lib%.a:	$(SRC_DIR)/%
			$(V)printf "$(WHITE)Compiling module $(MAGENTA)$<$(DEFAULT)\n"
			$(V)make --no-print-directory -C $<

.PHONY:			all clean re echo_build_parts
