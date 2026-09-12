.PHONY: all clean fclean re val cl fcl r

NAME=test
CC=cc
CFLAGS=-Wall -Wextra -Werror -g -fsanitize=address #-lm
RM=rm -rf
OBJS_DIR=build
LINK=-lm

INCLUDES:=-I. -I../../includes -I./../../../includes -I./../../src/Libft
# SRCS:=	../../src/vec/vec_ops.c \
# 		../../src/vec/vec_comp_ops.c \
# 		../../src/vec/vec_utils.c \
# 		../../src/ray/intersect.c \
# 		../../src/ray/hit_cylinder.c \
# 		../../src/error_handler/error_handler.c \
# 		../../src/general/utils.c\
# 		./intersect_objects/test_hit_cyl.c \
# 		./intersect_objects/test_hit_pl.c \
# 		./intersect_objects/test_hit_sph.c \
# 		./test_exec.c

SRC:=	../../src/vec/vec_ops.c \
		../../src/vec/vec_comp_ops.c \
		../../src/vec/vec_utils.c \
		../../src/ray/intersect.c \
		../../src/ray/hit_cylinder.c \
		../../src/error_handler/error_handler.c \
		../../src/general/utils.c

TEST_SRC:=	./intersect_objects/test_hit_cyl.c \
			./intersect_objects/test_hit_pl.c \
			./intersect_objects/test_hit_sph.c \
			./test_exec.c

OBJS := $(SRC:../../src/%.c=$(OBJS_DIR)/src/%.o)
OBJS += $(TEST_SRC:./%.c=$(OBJS_DIR)/%.o)

# OBJS:=$(patsubst %.c,$(OBJS_DIR)/%.o, $(SRCS))
VALGRIND = valgrind \
			--leak-check=full \
			--track-fds=yes \
			--show-leak-kinds=all \
			--track-origins=yes \
			--suppressions=readline.supp

LIBFT_DIR=./../../src/Libft
LIBFT_MAKE=make -C $(LIBFT_DIR)
LIBFT_LIB=$(LIBFT_DIR)/libft.a


all: $(NAME)

$(NAME): $(LIBFT_LIB) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_LIB) $(LINK) -o $(NAME)

$(LIBFT_LIB):
	$(LIBFT_MAKE) all

# $(OBJS_DIR)/%.o: %.c
# 	@mkdir -p $(dir $@)
# 	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJS_DIR)/src/%.o: ../../src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJS_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

val: $(NAME)
	$(VALGRIND) ./$(NAME)

clean:
	$(RM) $(OBJS_DIR)
	$(LIBFT_MAKE) clean

fclean: clean
	$(RM) $(NAME)
	$(LIBFT_MAKE) fclean

re: fclean all
