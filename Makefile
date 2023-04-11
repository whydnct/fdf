NAME = fdf_al

CC = gcc
CFLAGS = -Wall -Werror -Wextra

AR = AR
ARFLAGS = rsc

# Directorios
SRC_DIR    = src
OBJ_DIR    = obj
INC_DIR    = includes
LIBFT_DIR  = libft
MINLBX_DIR = minilibx

# Archivos fuentes y objetos
SRC_FILES  = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES  = $(SRC_FILES:.c=.o)

# Direcciones
SRC        = $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ        = $(addprefix $(OBJ_DIR), $(OBJ_FILES))
LIBFT      = $(addprefix $(LIBFT_DIR), libft.a)
MINLBX     = $(addprefix $(MINLBX_DIR), libmlx.a)

#INCLUDE = -lmlx -lXext -lX11

all: $(NAME)

# Crea la carpeta donde estara los objetos.
obj:
	@mkdir -p $(OBJ_DIR)

$(OBJ_FILE): $(SRC_FILES)
	@$(CC) $(CFLAGS) -I/usr/include -Imlx_linux -03 -o $@ -c $<

$(NAME): $(OBJ_FILES)
	@$(CC) $(OBJ_FILES) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)