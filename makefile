OUT=minivm

OPT=-Ofast

CFILES=vm/vm.c vm/state.c vm/gc.c main/main.c
OBJS=$(CFILES:%.c=%.o)

default: $(OUT)

$(OUT): $(OBJS)
	: mkdir -p bin
	$(CC) $(OBJS) -o $(OUT) -lm $(LFLAGS)

$(OBJS): $(@:%.o=%.c) $(basename $@)
	$(CC) -c $(OPT) -o $@ $(@:%.o=%.c) $(CFLAGS)

.dummy:

clean: .dummy
	rm -f $(OBJS) $(OUT)
