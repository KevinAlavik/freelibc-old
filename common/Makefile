CC ?= gcc
CFLAGS ?= -ffreestanding -Wall -Wextra -g
BIN_DIR ?= ../bin
OBJ_DIR = $(BIN_DIR)/obj
SRC_FILES = $(shell find . -name '*.c')
OBJ_FILES = $(SRC_FILES:.c=$(OBJ_DIR)/%.o)
AR = ar
ARFLAGS = cr

GREEN = \033[0;32m
BLUE = \033[0;34m
NC = \033[0m

all: $(OBJ_DIR)/freelibc.a

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@echo -e "$(BLUE)====> Compiling $<...$(NC)"
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/freelibc.a: $(OBJ_FILES)
	@echo -e "$(GREEN)====> Archiving objects into $@...$(NC)"
	@$(AR) $(ARFLAGS) $@ $^

clean:
	@echo -e "$(BLUE)====> Cleaning up...$(NC)"
	@rm -rf $(OBJ_DIR)

.PHONY: all clean
