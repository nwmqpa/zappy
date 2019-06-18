NAME		=	zappy_graphic_linux

CC		=	g++

LD		=	g++

AR		=	ar

ROOT		=	.

TEST_DIR	=	$(ROOT)/tests

BUILD_DIR	=	$(ROOT)/build

SRC_DIR 	=	$(ROOT)/sources

INCLUDE_DIR	=	$(ROOT)/includes

COMPILER_COMMAND = compile_commands.json

MODULES		=

SOURCES		=		Case.cpp	\
					WindowCreator.cpp	\
					Protocol.cpp \
					main.cpp

TEST_SOURCES	=	dummy.c


PREFIXED_SRCS 	=	$(addprefix $(SRC_DIR)/, $(SOURCES))
PREFIXED_TEST 	=	$(addprefix $(TEST_DIR)/, $(TEST_SOURCES))
PATSUBST_OBJS	=	$(patsubst  $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(PREFIXED_SRCS))
PATSUBST_OBJS_TEST	=	$(patsubst  $(TEST_DIR)/%.c, $(BUILD_DIR)/%.o, $(PREFIXED_TEST))
PATSUBST_JSON	=	$(patsubst  $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o.json, $(PREFIXED_SRCS))
LIBS_MODULES 	=	$(addprefix lib, $(addsuffix .a, $(MODULES)))
PREFIXED_MODULS	=	$(addprefix $(SRC_DIR)/, $(MODULES))
PATSUBST_MODULS =	$(patsubst  $(SRC_DIR)/%, $(BUILD_DIR)/lib%.a, $(PREFIXED_MODULS))
LINK_MODULES	=	$(addprefix -l, $(MODULES))


WARNINGS	=	-Wall -Wextra -lSDL2 -lSDL2_image -g
CXXFLAGS		=	-I $(INCLUDE_DIR) $(WARNINGS) -fdiagnostics-color=always -D _GNU_SOURCE
LDFLAGS		=	-L $(BUILD_DIR) $(LINK_MODULES) -lSDL2 -lSDL2_image

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

test:			CXXFLAGS += -g -D TEST
test:			LDFLAGS += -lcriterion
test:			$(ROOT)/test

debug: 			CXXFLAGS += -g -D LOG_LEVEL=5
debug:			re

cmd_gen: $(ROOT)/$(COMPILER_COMMAND)

$(ROOT)/$(COMPILER_COMMAND): $(PATSUBST_JSON)
	$(V)printf "$(WHITE)Creating $(BLUE)$(COMPILER_COMMAND)$(WHITE).\n"
	$(V)sed -e '1s/^/[$\n/' -e '$$s/,$$/$\n]/' $(PATSUBST_JSON) > $(ROOT)/$(COMPILER_COMMAND)
	$(V)printf "$(WHITE)Cleaning $(BLUE)objects $(WHITE)files$(DEFAULT)\n"
	$(V)rm *.o


clean:
			$(V)printf "$(WHITE)Cleaning $(BLUE)objects $(WHITE)files$(DEFAULT)\n"
			$(V)rm -f $(PATSUBST_OBJS)
			$(V)rm -f $(PATSUBST_OBJS_TEST)
			$(V)rm -f $(PATSUBST_JSON)
			$(V)for dir in $(PREFIXED_MODULS); do \
				make --no-print-directory -C $$dir clean; \
			done

fclean:			clean
			$(V)printf "$(WHITE)Cleaning $(GREEN)linked $(WHITE)files$(DEFAULT)\n"
			$(V)rm -f $(ROOT)/$(NAME) $(BUILD_DIR)/$(NAME)
			$(V)rm -f $(ROOT)/$(COMPILER_COMMAND)
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

$(ROOT)/test:		$(BUILD_DIR)/test
			$(V)printf "$(WHITE)Copying $(GREEN)test$(WHITE) from $(BLUE)$(BUILD_DIR)$(WHITE) folder$(DEFAULT)\n"
			$(V)cp $(BUILD_DIR)/test $(ROOT)/test
			$(V)printf "$(WHITE)Final $(GREEN)test$(WHITE) size: $(CYAN)%dKb$(DEFAULT)\n" `du -s $@ | awk -F ' ' '{print $$1}'`

$(BUILD_DIR)/$(NAME):	$(PATSUBST_OBJS) $(PATSUBST_MODULS) echo_build_parts
			$(V)printf "$(WHITE)Linking $(BLUE)objects $(WHITE)into $(GREEN)$(NAME)$(DEFAULT)\n"
			$(V)$(LD) -o $(BUILD_DIR)/$(NAME) $(PATSUBST_OBJS) $(LDFLAGS)

$(BUILD_DIR)/%.o.json:	$(SRC_DIR)/%.cpp
			$(V)printf "$(WHITE)Compiling command $(RED)$<$(WHITE) => $(BLUE)$@$(DEFAULT)\n"
			$(V)mkdir -p $(dir $@)
		    $(V)clang++ -MJ $@ -c $< $(CXXFLAGS)

$(BUILD_DIR)/test:	$(PATSUBST_OBJS_TEST) $(PATSUBST_OBJS) $(PATSUBST_MODULS)
			$(V)printf "$(WHITE)Linking $(BLUE)objects $(WHITE)into $(GREEN)test$(DEFAULT)\n"
			$(V)$(LD) -o $(BUILD_DIR)/test $(PATSUBST_OBJS) $(PATSUBST_OBJS_TEST) $(LDFLAGS)

$(BUILD_DIR)/%.o:	$(SRC_DIR)/%.cpp
			$(V)printf "$(WHITE)Compiling $(RED)$<$(WHITE) => $(BLUE)$@$(DEFAULT)\n"
			$(V)mkdir -p $(dir $@)
			$(V)$(CC) -o $@ -c $< $(CXXFLAGS)

$(BUILD_DIR)/%.o:	$(TEST_DIR)/%.c
			$(V)printf "$(WHITE)Compiling $(RED)$<$(WHITE) => $(BLUE)$@$(DEFAULT)\n"
			$(V)mkdir -p $(dir $@)
			$(V)$(CC) -o $@ -c $< $(CXXFLAGS)

$(BUILD_DIR)/lib%.a:	$(SRC_DIR)/%
			$(V)printf "$(WHITE)Compiling module $(MAGENTA)$<$(DEFAULT)\n"
			$(V)make --no-print-directory -C $<

.PHONY:			all clean re echo_build_parts fclean test
