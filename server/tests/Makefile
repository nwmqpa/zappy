
CC		=	gcc

LD		=	gcc

AR		=	ar

ROOT		=	..

TEST	:=	test

BUILD_DIR	=	$(ROOT)/build

SRC_DIR 	=	$(ROOT)/sources

TEST_DIR	=	$(ROOT)/tests

INCLUDE_DIR	=	$(ROOT)/includes

MODULES		=

SOURCES		=	main.c \
				zappy.c \
				server/options.c \
				server/server.c \
				server/server_init.c \
				gen_list/generic_list.c \
				utils/logger.c \
				client/client.c	 \
				client/command.c

TEST_SOURCES	=	client_command.c \
					generic_list.c

PREFIXED_SRCS 	=	$(addprefix $(SRC_DIR)/, $(SOURCES))
PREFIXED_TEST 	=	$(addprefix $(TEST_DIR)/, $(TEST_SOURCES))
PATSUBST_OBJS_SRCS	=	$(patsubst  $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(PREFIXED_SRCS))
PATSUBST_OBJS_TEST	=	$(patsubst  $(TEST_DIR)/%.c, $(BUILD_DIR)/%.o, $(PREFIXED_TEST))
LIBS_MODULES 	=	$(addprefix lib, $(addsuffix .a, $(MODULES)))
PREFIXED_MODULS	=	$(addprefix $(SRC_DIR)/, $(MODULES))
PATSUBST_MODULS =	$(patsubst  $(SRC_DIR)/%, $(BUILD_DIR)/lib%.a, $(PREFIXED_MODULS))
LINK_MODULES	=	$(addprefix -l, $(MODULES))


WARNINGS	=	-Wall -Wextra
CFLAGS		=	-I $(INCLUDE_DIR) $(WARNINGS) -fdiagnostics-color=always -D _GNU_SOURCE -D TEST -g
LDFLAGS		=	-L $(BUILD_DIR) $(LINK_MODULES) -lcriterion

DEFAULT		=	\e[0m
WHITE		=	\e[1;97m
RED		=	\e[1;91m
GREEN		=	\e[1;92m
YELLOW		=	\e[1;93m
BLUE		=	\e[1;94m
MAGENTA		=	\e[1;95m
CYAN		=	\e[1;96m

V		=	@

all:			$(ROOT)/$(TEST)

clean:
			$(Vprintf "$(WHITE)Cleaning $(BLUE)objects $(WHITE)files$(DEFAULT)\n"
			$(V)rm -f $(PATSUBST_OBJS)
			$(V)for dir in $(PREFIXED_MODULS); do \
				make --no-print-directory -C $$dir clean; \
			done

fclean:			clean
			$(V)printf "$(WHITE)Cleaning $(GREEN)linked $(WHITE)files$(DEFAULT)\n"
			$(V)rm -f $(ROOT)/$(TEST) $(BUILD_DIR)/$(TEST)
			$(V)for dir in $(PREFIXED_MODULS); do \
				make --no-print-directory -C $$dir fclean; \
			done

re:			fclean all

echo_build_parts:
			$(V)printf "$(WHITE)Binary $(GREEN)$(TEST)$(WHITE) built from:\n"
			$(V)for obj in $(PATSUBST_OBJS_SRCS) $(PATSUBST_OBJS_TEST); do \
				printf " $(CYAN)(%dKb)\t$(BLUE)%s$(WHITE)\n" `du -s $$obj | awk -F' ' '{ print $$1 }'` `basename $$obj`; \
			done
			$(V)for module in $(PATSUBST_MODULS); do \
				printf " $(CYAN)(%dKb)\t$(YELLOW)%s$(WHITE)\n" `du -s $$module | awk -F' ' '{ print $$1 }'` `basename $$module`; \
			done

$(ROOT)/$(TEST):	$(BUILD_DIR)/$(TEST)
			$(V)printf "$(WHITE)Copying $(GREEN)$(TEST)$(WHITE) from $(BLUE)$(BUILD_DIR)$(WHITE) folder$(DEFAULT)\n"
			$(V)cp $(BUILD_DIR)/$(TEST) $(ROOT)/$(TEST)
			$(V)printf "$(WHITE)Final $(GREEN)$(TEST)$(WHITE) size: $(CYAN)%dKb$(DEFAULT)\n" `du -s $@ | awk -F ' ' '{print $$1}'`

$(BUILD_DIR)/$(TEST):	$(PATSUBST_OBJS_SRCS) $(PATSUBST_OBJS_TEST) $(PATSUBST_MODULS) echo_build_parts
			$(V)printf "$(WHITE)Linking $(BLUE)objects $(WHITE)into $(GREEN)$(TEST)$(DEFAULT)\n"
			$(V)$(LD) -o $(BUILD_DIR)/$(TEST) $(PATSUBST_OBJS_TEST) $(PATSUBST_OBJS_SRCS) $(LDFLAGS)

$(BUILD_DIR)/%.o:	$(TEST_DIR)/%.c
			$(V)printf "$(WHITE)Compiling $(RED)$<$(WHITE) => $(BLUE)$@$(DEFAULT)\n"
			$(V)mkdir -p $(dir $@)
			$(V)$(CC) -o $@ -c $< $(CFLAGS)

$(BUILD_DIR)/%.o:	$(SRC_DIR)/%.c
			$(V)printf "$(WHITE)Compiling $(RED)$<$(WHITE) => $(BLUE)$@$(DEFAULT)\n"
			$(V)mkdir -p $(dir $@)
			$(V)$(CC) -o $@ -c $< $(CFLAGS)

$(BUILD_DIR)/lib%.a:	$(SRC_DIR)/%
			$(V)printf "$(WHITE)Compiling module $(MAGENTA)$<$(DEFAULT)\n"
			$(V)make --no-print-directory -C $<

.PHONY:			all clean re echo_build_parts fclean
