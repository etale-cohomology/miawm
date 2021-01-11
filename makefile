# -----------------------------------------------------------------------------------------------------------------------------#
CC     = gcc-8
MWATCH = makefile ${mathisart}/mathisart.h ${mathisart}/mathisart.c

# -----------------------------------------------------------------------------------------------------------------------------#
all: miawm

# ----------------------------------------------------------------
miawm: miawm.c miawm_util.c miawm_config.h  $(MWATCH)
	t $(CC)  $< -o $@  ${cflags} ${cnopie}  -lxcb -lxcb-res
release: miawm.c miawm_util.c miawm_config.h  $(MWATCH)
	t gcc-8  miawm.c -o miawm  ${cflags} ${cfast} ${cnopie}  -lxcb -lxcb-res

# ----------------------------------------------------------------
install:
	cp miawm ${bin}
uninstall:
	rm ${bin}/miawm
clean:
	rm -f miawm
run:
	Xephyr -ac -screen 960x540 -reset -terminate :1  &
	sleep 0.016
	DISPLAY=:1 ./miawm
