/**
 * TODO: Add License
 */

#include <jni.h>
 
#include "npc_console.h" 
 
#include "com_ziroby_jamis_Npc.h"
 
 int gen(char* buffer, int len )
 {
      NPC* npc;
      NPCGENERATOROPTS opts;
      NPC_OPTS cmd_opts;

  if( parseCommandLine( 0 /*argc*/, 0/*argv*/, &cmd_opts ) != 0 ) {
    return 0;
  }

  opts.raceType  = cmd_opts.race;
  opts.gender    = cmd_opts.gender;
  opts.alignment = cmd_opts.alignment;
  opts.level[0]  = cmd_opts.levels[0];
  opts.level[1]  = cmd_opts.levels[1];
  opts.level[2]  = cmd_opts.levels[2];
  opts.classType[0] = cmd_opts.classes[0];
  opts.classType[1] = cmd_opts.classes[1];
  opts.classType[2] = cmd_opts.classes[2];
  opts.abilityScoreStrategy = strategies[ cmd_opts.score_strategy ];

  opts.filePath = cmd_opts.data_path;

    npc = npcGenerateNPC( &opts );

  npcBuildStatBlock( npc, &opts, buffer, len);

    npcDestroyNPC( npc );
   
   return 1;     
 }
 
 /*
 * Class:     com_ziroby_jamis_Npc
 * Method:    gen
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_ziroby_jamis_Npc_gen
  (JNIEnv * env, jobject obj)
  {
    char    statBlock[4096];

    if (!gen(statBlock, sizeof(statBlock)))
    {
        return 0;
    }
    else
    {
        return (*env)->NewStringUTF(env, statBlock);
    }
  }



