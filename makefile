OBJDIR = obj
SRCDIR = src
OUT = icebearino.out
CC = g++ -std=c++11
FLAGS = -Wall -O2

_OBJS = main.o icefloe.o game.o penguin.o polygon.o util.o player.o particlesystem.o  perlin.o
OBJS = $(patsubst %,$(OBJDIR)/%,$(_OBJS))

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) $(FLAGS) -MMD -c -o $@ $<

$(OUT): $(OBJS)
	$(CC) $(OBJS) -o $@ -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system

-include $(OBJDIR)/*.d
