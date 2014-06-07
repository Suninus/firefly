DEP := mini2440.S lowlevel_init.S nand_read.c print.S
CPROG := $(wildcard *.c)
ASMPROG := $(wildcard *.S)
ASMPROG += $(wildcard *.s)

CBASE := $(basename $(CPROG))
ASMBASE := $(basename $(ASMPROG))
COBJ := $(addsuffix .o,$(CBASE))
ASMOBJ := $(addsuffix .o,$(ASMBASE))
OBJ := $(COBJ) $(ASMOBJ)

head.o: $(OBJ)
	$(LD) -Thead.lds -r -o $@ $^
$(COBJ):%.o:%.c
	$(CC) $(CFLAGS) -c $^ -o $@
$(ASMOBJ):%.o:%.S
	$(CC) $(CFLAGS) -c $^ -o $@
clean:
	-rm *.o
