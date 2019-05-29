
NAME		=	zappy_server

CC		=	gcc

LD		=	gcc

AR		=	ar

ROOT		=	.

TEST_DIR	=	$(ROOT)/tests

BUILD_DIR	=	$(ROOT)/build

SRC_DIR 	=	$(ROOT)/sources

INCLUDE_DIR	=	$(ROOT)/includes

MODULES		=

SOURCES		=	main.c \
				zappy.c \
				server/options.c \
				server/server.c \
				server/server_init.c \
				gen_list/basic.c \
				gen_list/compare.c \
				gen_list/filter.c \
				gen_list/insert.c \
				gen_list/utils.c \
				utils/logger.c \
				client/client.c \
				client/command.c \
				utils/dispatcher.c \
				server/graphic_handler.c \
				server/client_handler.c \
				server/teams.c
				map/map.c \
				map/tile.c

TEST_SOURCES	=	client_command.c \
					generic_list.c \
					arg_parser.c \
					map.c

PREFIXED_SRCS 	=	$(addprefix $(SRC_DIR)/, $(SOURCES))
PREFIXED_TEST 	=	$(addprefix $(TEST_DIR)/, $(TEST_SOURCES))
PATSUBST_OBJS	=	$(patsubst  $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(PREFIXED_SRCS))
PATSUBST_OBJS_TEST	=	$(patsubst  $(TEST_DIR)/%.c, $(BUILD_DIR)/%.o, $(PREFIXED_TEST))
LIBS_MODULES 	=	$(addprefix lib, $(addsuffix .a, $(MODULES)))
PREFIXED_MODULS	=	$(addprefix $(SRC_DIR)/, $(MODULES))
PATSUBST_MODULS =	$(patsubst  $(SRC_DIR)/%, $(BUILD_DIR)/lib%.a, $(PREFIXED_MODULS))
LINK_MODULES	=	$(addprefix -l, $(MODULES))


WARNINGS	=	-Wall -Wextra
CFLAGS		=	-I $(INCLUDE_DIR) $(WARNINGS) -fdiagnostics-color=always -D _GNU_SOURCE -Wno-unused-parameter
LDFLAGS		=	-L $(BUILD_DIR) $(LINK_MODULES)

DEFAULT		=	\e[0m
WHITE		=	\e[1;97m
RED		=	\e[1;91m
GREEN		=	\e[1;92m
YELLOW		=	\e[1;93m
BLUE		=	\e[1;94m
MAGENTA		=	\e[1;95m
CYAN		=	\e[1;96m

V		=	@

all:	$(ROOT)/$(NAME)

test:	CFLAGS += -g -D TEST
test:	LDFLAGS += -lcriterion
test:	$(ROOT)/test

debug: CFLAGS += -g -D LOG_LEVEL=5
debug:	re

clean:
			$(Vprintf "$(WHITE)Cleaning $(BLUE)objects $(WHITE)files$(DEFAULT)\n"
			$(V)rm -f $(PATSUBST_OBJS)
			$(V)rm -f $(PATSUBST_OBJS_TEST)
			$(V)for dir in $(PREFIXED_MODULS); do \
				make --no-print-directory -C $$dir clean; \
			done

fclean:			clean
			$(V)printf "$(WHITE)Cleaning $(GREEN)linked $(WHITE)files$(DEFAULT)\n"
			$(V)rm -f $(ROOT)/$(NAME) $(BUILD_DIR)/$(NAME)
			$(V)rm -f $(ROOT)/test $(BUILD_DIR)/test
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

$(ROOT)/test:	$(BUILD_DIR)/test
			$(V)printf "$(WHITE)Copying $(GREEN)test$(WHITE) from $(BLUE)$(BUILD_DIR)$(WHITE) folder$(DEFAULT)\n"
			$(V)cp $(BUILD_DIR)/test $(ROOT)/test
			$(V)printf "$(WHITE)Final $(GREEN)test$(WHITE) size: $(CYAN)%dKb$(DEFAULT)\n" `du -s $@ | awk -F ' ' '{print $$1}'`

$(BUILD_DIR)/$(NAME):	$(PATSUBST_OBJS) $(PATSUBST_MODULS) echo_build_parts
			$(V)printf "$(WHITE)Linking $(BLUE)objects $(WHITE)into $(GREEN)$(NAME)$(DEFAULT)\n"
			$(V)$(LD) -o $(BUILD_DIR)/$(NAME) $(PATSUBST_OBJS) $(LDFLAGS)

$(BUILD_DIR)/test:	$(PATSUBST_OBJS_TEST) $(PATSUBST_OBJS) $(PATSUBST_MODULS)
			$(V)printf "$(WHITE)Linking $(BLUE)objects $(WHITE)into $(GREEN)test$(DEFAULT)\n"
			$(V)$(LD) -o $(BUILD_DIR)/test $(PATSUBST_OBJS) $(PATSUBST_OBJS_TEST) $(LDFLAGS)

$(BUILD_DIR)/%.o:	$(SRC_DIR)/%.c
			$(V)printf "$(WHITE)Compiling $(RED)$<$(WHITE) => $(BLUE)$@$(DEFAULT)\n"
			$(V)mkdir -p $(dir $@)
			$(V)$(CC) -o $@ -c $< $(CFLAGS)

$(BUILD_DIR)/%.o:	$(TEST_DIR)/%.c
			$(V)printf "$(WHITE)Compiling $(RED)$<$(WHITE) => $(BLUE)$@$(DEFAULT)\n"
			$(V)mkdir -p $(dir $@)
			$(V)$(CC) -o $@ -c $< $(CFLAGS)

$(BUILD_DIR)/lib%.a:	$(SRC_DIR)/%
			$(V)printf "$(WHITE)Compiling module $(MAGENTA)$<$(DEFAULT)\n"
			$(V)make --no-print-directory -C $<

.PHONY:			all clean re echo_build_parts fclean test
