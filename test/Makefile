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

CC = gcc
AS = as
CFLAGS = -ffreestanding -nostdlib -nostartfiles -I../include -nodefaultlibs
LDFLAGS = -L../bin/obj -lfreelibc -lgcc
BINDIR = bin

SRC = $(wildcard *.c)
BIN = $(patsubst %.c, $(BINDIR)/%, $(SRC))
STARTUP_OBJ = startup.o

all: $(STARTUP_OBJ) $(BIN)

$(STARTUP_OBJ): startup.S
	$(AS) $< -o $@

$(BINDIR)/%: %.c $(STARTUP_OBJ)
	@mkdir -p $(BINDIR)
	$(CC) $^ -o $@ $(CFLAGS) $(LDFLAGS)

clean:
	rm -rf $(BINDIR) $(STARTUP_OBJ)

.PHONY: all clean
