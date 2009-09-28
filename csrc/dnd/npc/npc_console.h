#ifndef NPC_CONSOLE_H_
#define NPC_CONSOLE_H_

 #include "npcEngine.h"

typedef struct tag_npcopts NPC_OPTS;
struct tag_npcopts {
  long seed;
  int  background;
  int  alignment;
  int  race;
  int  classes[ 3 ];
  int  levels[ 3 ];
  int  score_strategy;
  int  count;
  int  gender;

  int  mode;
  int  wrap;

  char path[ 512 ];
  char data_path[ 512 ];

  NPCSTATBLOCKOPTS opts;
};

void heroicAbilities( int* scores, void* data );
void straight18s( int* scores, void* data );
void averageAbilities( int* scores, void* data );

extern NPCABSCOREGENFUNC strategies[];

int parseCommandLine( int argc, char* argv[], NPC_OPTS* opts );
int displayNPC_StatBlock( NPC_OPTS* opts, FILE *output, NPC* npc );

#endif /*NPC_CONSOLE_H_*/
 
