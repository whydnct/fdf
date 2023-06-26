# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aperez-m <aperez-m@student.42urduliz.com>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/02 13:31:05 by aperez-m          #+#    #+#              #
#    Updated: 2023/06/26 19:10:27 by aperez-m         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

OS := $(shell uname -s)

NAME := fdf_al

#------------------------------------------------#
#   INGREDIENTS                                  #
#------------------------------------------------#
# LIBS        libraries to be used
# LIBS_TARGET libraries to be built
#
# INCS        header file locations
#
# SRC_DIR     source directory
# SRCS        source files
#
# BUILD_DIR   build directory
# OBJS        object files
# DEPS        dependency files
#
# CC          compiler
# CFLAGS      compiler flags
# CPPFLAGS    preprocessor flags
# LDFLAGS     linker flags
# LDLIBS      libraries name

LIBS_TARGET := lib/libft/libft.a 

INCS        := include \
			lib/libft/include
ifeq ($(OS), Linux)
LIBS		:= ft mlx_Linux X11 Xext m z
INCS		:= $(INCS) lib/mlx_linux /usr/include
LIBS_TARGET := $(LIBS_TARGET) lib/mlx_linux/mlx_Linux.a
MFLAGS		:=
else ifeq ($(OS), Darwin)
LIBS		:= ft mlx
INCS		:= $(INCS) lib/mlx
LIBS_TARGET := $(LIBS_TARGET) lib/mlx/mlx.a
MFLAGS		:= -framework OpenGL -framework AppKit
endif

SRC_DIR     	:= src
SRCS			:= \
				main.c \
				events_handlers.c \
				free_memory.c \
				v_map_to_img.c \
				v_map_to_img_lines.c \
				project_v_map.c \
				project_v_map_trans.c \
				project_v_map_spans.c \
				read_map.c \
				param_validators.c \
				colors.c
SRCS			:= $(SRCS:%=$(SRC_DIR)/%)

BUILD_DIR   := .build
OBJS		:= $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
DEPS		:= $(OBJS:.o=.d)

CC          := gcc
CFLAGS      := -Wall -Wextra -Werror -g -O0
CPPFLAGS    := $(addprefix -I,$(INCS)) -MMD -MP
LDFLAGS     := $(addprefix -L,$(dir $(LIBS_TARGET)))
LDLIBS      := $(addprefix -l,$(LIBS))

#------------------------------------------------#
#   UTENSILS                                     #
#------------------------------------------------#
# RM        force remove
# MAKEFLAGS make flags
# DIR_DUP   duplicate directory tree

RM          := rm -f
MAKEFLAGS   += --silent --no-print-directory
DIR_DUP     = mkdir -p $(@D)

#------------------------------------------------#
#   RECIPES                                      #
#------------------------------------------------#
# all       default goal
# $(NAME)   link .o -> archive
# $(LIBS)   build libraries
# %.o       compilation .c -> .o
# clean     remove .o
# fclean    remove .o + binary
# re        remake default goal
# run       run the program
# info      print the default goal recipe

all: $(NAME)

$(NAME): $(OBJS) $(LIBS_TARGET)
	$(CC) $(LDFLAGS) $(OBJS) $(LDLIBS) $(MFLAGS) -o $(NAME).out
	$(info CREATED $(NAME))

$(LIBS_TARGET):
	$(MAKE) -C $(@D)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(DIR_DUP)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<
	$(info CREATED $@)

-include $(DEPS)

clean:
	for f in $(dir $(LIBS_TARGET)); do $(MAKE) -C $$f clean; done
	$(RM) $(OBJS) $(DEPS)

fclean: clean
	$(MAKE) fclean -C lib/libft
	$(RM) $(NAME)

re:
	$(MAKE) fclean
	$(MAKE) all

info-%:
	$(MAKE) --dry-run --always-make $* | grep -v "info"

#------------------------------------------------#
#   SPEC                                         #
#------------------------------------------------#

.PHONY: clean fclean re
.SILENT:
