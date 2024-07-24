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
