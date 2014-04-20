OBJDIR := build

# Rules
all: $(OBJDIR)/main

%: %.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

$(OBJDIR)/%.o: %.c
	$(CC) -c $(CFLAGS) $(LDFLAGS) -o $@ $^

$(OBJDIR):
	mkdir -p $@

# Dependencies
$(OBJDIR)/main: $(OBJDIR)/main.o $(OBJDIR)/scanner.o | $(OBJDIR)
$(OBJDIR)/main.o $(OBJDIR)/scanner.o: | $(OBJDIR)
