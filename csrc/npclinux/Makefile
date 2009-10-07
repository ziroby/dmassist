OPTS=-I../qDecoder-7.0.1/src -I../dnd/npc -I../dnd/include -I../utils -I../templates -I. -I../dnd/npc/history -DUSE_COUNTER -DCTRLOCATION="\"/home/minam/npc2.cnt\""
#OPTS=-I../qDecoder-7.0.1/src -I../dnd/npc -I../dnd/include -I../utils -I. -I../dnd/npc/history
LIBS=../qDecoder-7.0.1/src/libqDecoder.a ../templates/libtemplates.a -ldl

all: npc2.cgi

WEBOBJS=\
	../dnd/npc/npccgi.c \
	../dnd/npc/pcgen_interface.c \
	../dnd/npc/npcEngine.c \
	../dnd/npc/npcTownEngine.c \
	../dnd/src/dndutil.c \
	../utils/gameutil.c \
	../utils/grammar.c \
	../dnd/npc/history/npcHistory.c \
	../qDecoder-7.0.1/src/qDecoder.c

npc2.cgi: Makefile $(WEBOBJS)
	gcc -g $(OPTS) -o ../dnd/npc/npc2.cgi $(WEBOBJS) $(LIBS)

CONSOLEOBJS=\
	../dnd/npc/npc_console.c \
	../dnd/npc/pcgen_interface.c \
	../dnd/npc/npcEngine.c \
	../dnd/npc/npcTownEngine.c \
	../dnd/src/dndutil.c \
	../utils/gameutil.c \
	../utils/grammar.c \
	../dnd/npc/history/npcHistory.c

console: Makefile $(CONSOLEOBJS)
	gcc -g $(OPTS) -o ../dnd/npc/npc $(CONSOLEOBJS)

