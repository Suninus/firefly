CPROG := $(wildcard *.c)
CBASE := $(basename $(CPROG))
OBJ := $(addsuffix .o,$(CBASE))


time_in.o: $(OBJ)
	$(LD) -r -o $@ $^
$(OBJ):%.o:%.c
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	-rm *.o
