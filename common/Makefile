# Freelibc
# Copyright (C) 2024 Kevin Alavik and contributors

# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

CC ?= gcc
INCLUDE_DIR ?= ../include
CFLAGS ?= -fno-stack-protector -ffreestanding -Wall -Wextra -g -I$(INCLUDE_DIR)
BIN_DIR ?= ../bin
OBJ_DIR = $(BIN_DIR)/obj
SRC_FILES = $(shell find . -name '*.c')
OBJ_FILES = $(patsubst ./%.c,$(OBJ_DIR)/%.o,$(SRC_FILES))
AR = ar
ARFLAGS = cr

all: $(OBJ_DIR)/freelibc.a

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@echo -e "\tCC\t\t$<"
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/freelibc.a: $(OBJ_FILES)
	@echo -e "\tAR\t\t$@"
	@$(AR) $(ARFLAGS) $@ $^

clean:
	@echo -e "\tCLEAN\t\t$(OBJ_DIR)"
	@rm -rf $(OBJ_DIR)

.PHONY: all clean
