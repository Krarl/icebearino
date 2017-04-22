OBJDIR = obj
SRCDIR = src
OUT = icebearino.out
CC = g++ -std=c++11
FLAGS = -Wall

_OBJS = main.o icefloe.o game.o penguin.o polygon.o
OBJS = $(patsubst %,$(OBJDIR)/%,$(_OBJS))

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) $(FLAGS) -MMD -c -o $@ $<

$(OUT): $(OBJS)
	$(CC) $(OBJS) -o $@ -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system

-include $(OBJDIR)/*.d
