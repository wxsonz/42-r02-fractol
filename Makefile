# ============================================================================== #
#                                 Project Variables                              #
# ============================================================================== #

# Executable Name
NAME		:= fractol

# Compiler and Flags
CC			:= cc
CFLAGS		:= -Wall -Wextra -Werror -O3 -g

# ============================================================================== #
#                                 Directory Setup                                #
# ============================================================================== #

# Source and Object Directories
SRCS_DIR	:= srcs
OBJS_DIR	:= objs

# Library Directories
LIB_DIR		:= lib
MLX_DIR		:= $(LIB_DIR)/MLX42
MLX_BUILD	:= $(MLX_DIR)/build
MLX_LIB		:= $(MLX_BUILD)/libmlx42.a

# Include Paths
INCLUDE		:= -I include -I $(MLX_DIR)/include

# ============================================================================== #
#                                  Source Files                                  #
# ============================================================================== #

# Explicitly list all your.c files here.
SRCS_FILES	:= main.c \
			   parser.c \
			   utils.c \
			   init.c \
			   render.c \
			   math_fractol.c \
			   math_zoom.c \
			   color.c \
			   events_mouse.c \
			   events_keyboard.c

# Prepend the source directory path to each file.
SRCS		:= $(addprefix $(SRCS_DIR)/, $(SRCS_FILES))

# Generate object file names, placing them in OBJS_DIR
OBJS		:= $(patsubst $(SRCS_DIR)/%.c, $(OBJS_DIR)/%.o, $(SRCS))

# Generate dependency files for header tracking
DEPS		:= $(OBJS:.o=.d)

# ============================================================================== #
#                                  Linker Flags                                  #
# ============================================================================== #

# Platform-specific linker flags for MLX42 and its dependencies
# Default to Linux flags
LDFLAGS		:= -L$(MLX_BUILD) -lmlx42 -ldl -lglfw -pthread -lm

# Check for macOS
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S), Darwin)
	LDFLAGS := -L$(MLX_BUILD) -lmlx42 -lglfw -framework Cocoa -framework OpenGL -framework IOKit
endif

# ============================================================================== #
#                                     Rules                                      #
# ============================================================================== #

# Default rule
all: $(NAME)

# Rule to build the MLX42 library
$(MLX_LIB):
	@echo "Building MLX42 library..."
	@cmake $(MLX_DIR) -B $(MLX_BUILD)
	@make -C $(MLX_BUILD) -j4

# Rule to link the final executable
$(NAME): $(MLX_LIB) $(OBJS)
	@echo "Linking executable: $(NAME)"
	@$(CC) $(OBJS) $(LDFLAGS) -o $(NAME)
	@echo "Done."

# Rule to compile object files and generate dependencies
$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(@D)
	@echo "Compiling: $<"
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@ -MMD -MP

# Include dependency files
-include $(DEPS)

# Clean rules
clean:
	@echo "Cleaning object files..."
	@rm -rf $(OBJS_DIR)

fclean: clean
	@echo "Full clean: removing executable and library build..."
	@rm -f $(NAME)
	@rm -rf $(MLX_BUILD)

# Rebuild rule
re: fclean all

# Phony targets to prevent conflicts with files of the same name
.PHONY: all clean fclean re
