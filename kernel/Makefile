CURDIR := $(shell pwd)
$(INCLUDE) += -I$(CURDIR)/include/
IRQ := ./irq/irq_in.o
TIME := ./time/time_in.o
OBJ := core.o
$(OBJ): $(IRQ) $(TIME)
	$(LD) -r -o $@ $^
$(IRQ):
	$(MAKE) -C irq
$(TIME):
	$(MAKE) -C time

clean:
	-rm core.o
	$(MAKE) clean -C irq/
	$(MAKE) clean -C time/
