SRC_DIR = src

all: build

build: ${SRC_DIR}
	cd $< && make

install: ${SRC_DIR}
	cd $< && make clean install

clean: ${SRC_DIR}
	cd $< && make clean 

uninstall: ${SRC_DIR}
	cd $< && make uninstall 

.PHONY: build clean
