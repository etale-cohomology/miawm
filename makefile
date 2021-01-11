# -----------------------------------------------------------------------------------------------------------------------------#
CC     = gcc-8
MWATCH = makefile
CFLAGS = -std=gnu11  -Wno-unused-result -Wno-unused-variable -Wno-unused-but-set-variable -Wno-unused-function -Wno-parentheses  # NOTE! `-no-pie -fno-PIE -fno-pic -fno-PIC` breaks compilation of static & shared libraries!
CNOPIE = -no-pie -fno-PIE -fno-pic -fno-PIC  
CFAST  = -Ofast -march=native  -flto -fwhole-program  -fno-stack-protector -fstrict-aliasing -fomit-frame-pointer  -funroll-loops -finline-functions  -DNDEBUG -pipe  # NOTE! `-no-pie -fno-PIE -fno-pic -fno-PIC` breaks compilation of static & shared libraries!
BIN    = $(HOME)/bin

# -----------------------------------------------------------------------------------------------------------------------------#
all: miawm

# ----------------------------------------------------------------
miawm: miawm.c miawm_util.c miawm_config.h  $(MWATCH)
	$(CC)  $< -o $@  $(CFLAGS) $(CNOPIE) $(CFAST)  -lxcb -lxcb-res
debug: miawm.c miawm_util.c miawm_config.h  $(MWATCH)
	$(CC)  $< -o miawm  $(CFLAGS) $(CNOPIE)  -lxcb -lxcb-res

# ----------------------------------------------------------------
install:
	cp miawm $(BIN)
uninstall:
	rm $(BIN)/miawm
clean:
	rm -f miawm
test:
	Xephyr -ac -screen 960x540 -reset -terminate :1  &
	sleep 0.016
	DISPLAY=:1 ./miawm
