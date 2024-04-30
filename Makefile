.SUFFIXES: .c .h .x .o

CFLAGS = -pedantic -Wall -std=c99
LFLAGS = -pedantic -Wall -std=c99
CO = gcc
LD = $(CO)

NAME1 = cw3a
NAME2 = cw3b
NAME3 = cw3c
NAME4 = cw3c1


OBJS1 = $(NAME1).o
OBJS2 = $(NAME2).o
OBJS3 = $(NAME3).o
OBJS4 = $(NAME4).o


EXEC1 = $(NAME1).x
EXEC2 = $(NAME2).x
EXEC3 = $(NAME3).x
EXEC4 = $(NAME4).x



.PHONY: help
help:
	@echo "make all		Kompiluje wszystkie programy"
	@echo "make run-all	Uruchamia wszystkie programy"
	@echo "make run-$(NAME1)    Uruchamia program $(NAME1)"
	@echo "make run-$(NAME2)    Uruchamia program $(NAME2)"
	@echo "make run-$(NAME3)	Uruchamia program $(NAME3)"
	@echo "make run-$(NAME4)	Uruchamia program $(NAME4)"
	@echo "make clean	Usuwa pliki *.o oraz *.x"
.PHONY: all
all: $(EXEC1) $(EXEC2) $(EXEC3) $(EXEC4) $(EXEC5)

$(EXEC1): $(OBJS1)
	$(LD) $(LFLAGS) -o $@ $^

$(EXEC2): $(OBJS2)
	$(LD) $(LFLAGS) -o $@ $^

$(EXEC3): $(OBJS3)
	$(LD) $(LFLAGS) -o $@ $^

$(EXEC4): $(OBJS4)
	$(LD) $(LFLAGS) -o $@ $^

%.o: %.c %.h
	$(CO) $(CFLAGS) -c $<

.PHONY: run-$(EXEC1) run-$(EXEC2) run-$(EXEC3) run-$(EXEC4) 

run-$(NAME1): $(EXEC1)
	./$(EXEC1) 3 2

run-$(NAME2): $(EXEC2)
	./$(EXEC2)

run-$(NAME3): $(EXEC3)
	./$(EXEC3)

run-$(NAME4): $(EXEC4)
	./$(EXEC4)



.PHONY: clean

clean:
	rm *.o *.x

.PHONY: run-all
run-all: $(EXEC1) $(EXEC2) $(EXEC3) $(EXEC4) 
	./$(EXEC1)
	./$(EXEC2)
	./$(EXEC3)
	./$(EXEC4)
	

