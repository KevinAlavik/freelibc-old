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
CFLAGS = -fno-stack-protector -ffreestanding -nostdlib -nostartfiles -nodefaultlibs -nostdinc -I /usr/local/include/freelibc
LDFLAGS = -L/usr/local/lib -lfreelibc
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
