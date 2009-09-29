/**
 * TODO: Add License
 */

#include <jni.h>
#include <malloc.h>
 
#include "npc_console.h" 
 
#include "com_ziroby_jamis_Npc.h"
 
 int gen(char* buffer, int len, int argc, char* argv[] )
 {
      NPC* npc;
      NPCGENERATOROPTS opts;
      NPC_OPTS cmd_opts;

  buffer[0] = '\0';
  if( parseCommandLine( argc, argv, &cmd_opts, buffer, len ) != 0 ) {
    return 0;
  }
  if (buffer[0])
  {
    puts(buffer);
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

  npcBuildStatBlock( npc, &(cmd_opts.opts), buffer, len);

    npcDestroyNPC( npc );
   
   return 1;     
 }
 
 /*
 * Class:     com_ziroby_jamis_Npc
 * Method:    gen
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_ziroby_jamis_Npc_gen1
  (JNIEnv * env, jobject obj)
  {
    char    statBlock[4096];

    if (!gen(statBlock, sizeof(statBlock), 0, 0))
    {
        return 0;
    }
    else
    {
        return (*env)->NewStringUTF(env, statBlock);
    }
  }

/*
 * Class:     com_ziroby_jamis_Npc
 * Method:    gen2
 * Signature: ([Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_ziroby_jamis_Npc_gen2
  (JNIEnv * env, jclass c, jobjectArray array)
  {
    int argc = (*env)->GetArrayLength(env, array);
    char** argv;
    argv = malloc(sizeof(char *) * argc);
    if (!argv)
    {
        return 0;
    }
    
    jsize i;
    for(i = 0; i < argc; ++i)
    {
        jstring s = (jstring) (*env)->GetObjectArrayElement(env, array, i);
        jboolean isCopy;
        argv[i] = (char*)(*env)->GetStringUTFChars(env, s, &isCopy);
    }   
    
    char    statBlock[4096] = "";

    if (!gen(statBlock, sizeof(statBlock), argc, argv))
    {
        puts("gen() returned non-zero.");
    }
    else
    {
    }

    for (i = 0; i < argc; ++i)
    {
        jstring s = (jstring) (*env)->GetObjectArrayElement(env, array, i);
        (*env)->ReleaseStringUTFChars(env, s, argv[i]);
    }
    
    if (argv)
    {
        free (argv);
    }

    return (*env)->NewStringUTF(env, statBlock);

  }





