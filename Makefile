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

BIN_DIR := $(abspath bin)
COMMON_DIR := $(abspath common)
INCLUDE_DIR := $(abspath include)
LIB_DIR := /usr/local/lib
INCLUDE_INSTALL_DIR := /usr/local/include

all: $(BIN_DIR)/freelibc.a

$(BIN_DIR)/freelibc.a:
	$(MAKE) -C $(COMMON_DIR) BIN_DIR=$(BIN_DIR)

install: $(BIN_DIR)/freelibc.a
	@echo "====> Installing freelibc.a to $(LIB_DIR)"
	install -d $(LIB_DIR)
	install $(BIN_DIR)/freelibc.a $(LIB_DIR)/libfreelibc.a
	@echo "====> Installing headers to $(INCLUDE_INSTALL_DIR)"
	install -d $(INCLUDE_INSTALL_DIR)
	install -t $(INCLUDE_INSTALL_DIR) $(INCLUDE_DIR)/*
	@echo "====> Configuring GCC"
	echo $(LIB_DIR) | sudo tee /etc/ld.so.conf.d/freelibc.conf
	sudo ldconfig

clean:
	$(MAKE) -C $(COMMON_DIR) clean
	rm -rf $(BIN_DIR)

.PHONY: all install clean
