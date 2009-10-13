#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <pwd.h>
#include <stdio.h>

#include "gameutil.h"
#include "npcEngine.h"
#include "dndconst.h"
#include "dndutil.h"
#include "grammar.h"
#include "npcHistory.h"
#include "pcgen_interface.h"
#include "npc_console.h"

#ifdef unix
#define rand  random
#define srand srandom
#endif

#define APPNAME     "npc"

#define MODE_STATBLOCK  ( 0 )
#define MODE_PCGEN      ( 1 )


typedef struct tag_lookup  LOOKUP_TBL;


struct tag_lookup {
  char* name;
  int   id;
};


#define HELP_RACES      1
#define HELP_CLASSES    2
#define HELP_ALIGNMENTS 3
#define HELP_GENDERS    4
#define HELP_STRATEGIES 5

static LOOKUP_TBL help_lists[] = {
  { "alignments", HELP_ALIGNMENTS },
  { "classes",    HELP_CLASSES },
  { "genders",    HELP_GENDERS },
  { "races",      HELP_RACES },
  { "strategies", HELP_STRATEGIES },
  { 0,            0 }
};


static LOOKUP_TBL strategies_lookup[] = {
  { "18s",      5 },
  { "3d6",      2 },
  { "4d6",      1 },
  { "average",  4 },
  { "heroic",   3 },
  { 0,          0 }
};


static LOOKUP_TBL levels[] = {
  { "any",  levelANY },
  { "high", levelHI },
  { "low",  levelLOW },
  { "mid",  levelMID },
  { 0,      0 }
};


static LOOKUP_TBL genders[] = {
  { "any",       gANY },
  { "female",    gFEMALE },
  { "male",      gMALE },
  { 0,           0 }
};


static LOOKUP_TBL alignments[] = {
  { "any",       alANY },
  { "ce",        alCHAOTIC | alEVIL },
  { "cg",        alCHAOTIC | alGOOD },
  { "chaotic",   alANY_CHAOTIC },
  { "cn",        alCHAOTIC | alGENEUTRAL },
  { "evil",      alANY_EVIL },
  { "geneutral", alANY_GENEUTRAL },
  { "good",      alANY_GOOD },
  { "lawful",    alANY_LAWFUL },
  { "lcneutral", alANY_LCNEUTRAL },
  { "le",        alLAWFUL | alEVIL },
  { "lg",        alLAWFUL | alGOOD },
  { "ln",        alLAWFUL | alGENEUTRAL },
  { "ne",        alLCNEUTRAL | alEVIL },
  { "ng",        alLCNEUTRAL | alGOOD },
  { "nn",        alLCNEUTRAL | alGENEUTRAL },
  { 0,           0 }
};


static LOOKUP_TBL classtypes[] = {
  { "adept",      npcADEPT },
  { "any",        classANY },
  { "anynpc",     classANY_NPC },
  { "anypc",      classANY_PC },
  { "aristocrat", npcARISTOCRAT },
  { "barbarian",  pcBARBARIAN },
  { "bard",       pcBARD },
  { "cleric",     pcCLERIC },
  { "commoner",   npcCOMMONER },
  { "druid",      pcDRUID },
  { "expert",     npcEXPERT },
  { "fighter",    pcFIGHTER },
  { "monk",       pcMONK },
  { "paladin",    pcPALADIN },
  { "ranger",     pcRANGER },
  { "rogue",      pcROGUE },
  { "sorcerer",   pcSORCERER },
  { "warrior",    npcWARRIOR },
  { "wizard",     pcWIZARD },
  { 0,            0 }
};

static LOOKUP_TBL racetypes[] = {
  { "any",        raceANY },
  { "dwarf",      rcDWARF_HILL },
  { "elf",        rcELF_HIGH },
  { "gnome",      rcGNOME_ROCK },
  { "halfelf",    rcHALFELF },
  { "halfling",   rcHALFLING_LIGHTFOOT },
  { "halforc",    rcHALFORC },
  { "human",      rcHUMAN },
  { 0,            0 }
};


NPCABSCOREGENFUNC strategies[] = {
  0, 
  npcAbScoreStrategy_BestOf4d6, 
  npcAbScoreStrategy_Straight3d6,
  heroicAbilities,
  averageAbilities,
  straight18s
};

static int icomp( const void* x, const void* y ) {
  int ix = *(int*)x;
  int iy = *(int*)y;

  if( ix < iy ) return 1;
  if( ix > iy ) return -1;
  return 0;
}


void heroicAbilities( int* scores, void* data ) {
  int i;

  npcAbScoreStrategy_BestOf4d6( scores, data );
  scores[0] = 18;
  scores[1] = 18;

  for( i = 2; i < 6; i++ ) {
    if( scores[i] < 12 ) {
      scores[ i ] = 12;
    }
  }
}


void straight18s( int* scores, void* data ) {
  int i;

  for( i = 0; i < 6; i++ ) {
    scores[ i ] = 18;
  }
}


void averageAbilities( int* scores, void* data ) {
  int i;

  for( i = 0; i < 6; i++ ) {
    scores[i] = 10 + ( rand() % 2 );
  }
}


static void strrepl( char* buf, char* srch, char* repl ) {
  char* p;
  int   slen;
  int   rlen;

  slen = strlen( srch );
  rlen = strlen( repl );

  p = strstr( buf, srch );
  while( p != NULL ) {
    memmove( p+rlen, p+slen, strlen( p + slen ) + 1 );
    strncpy( p, repl, rlen );
    p = strstr( p+rlen, srch );
  }
}


static int lookup( char* string, LOOKUP_TBL* tbl, int* found ) {
  int rc;
  int idx;
  int len;

  len = strlen( string );
  *found = 1;
  for( idx = 0; tbl[ idx ].name != 0; idx++ ) {
    rc = strncasecmp( string, tbl[ idx ].name, len );
    if( rc == 0 ) {
      return tbl[ idx ].id;
    } else if( rc < 0 ) {
      break;
    }
  }

  *found = 0;
  return -1;
}


#define USAGE APPNAME ", by Jamis Buck (jgb3@email.byu.edu)\n\
<p>\
  Options:<br>\
  <table border=0>\
    <tr><td>-r &lt;race&gt;</td>        <td>-S &lt;seed&gt;</td>      <td>-c &lt;class&gt;</td>     <td>-g &lt;gender&gt;<td></tr>\
    <tr><td>-l &lt;level&gt;</td>       <td colspan=2>-h (race|class|strategy|alignment|gender)</td></tr>\
    <tr><td>-s &lt;strategy&gt;</td>    <td>-n &lt;count&gt;</td>     <td>-a &lt;alignment&gt;</td> <td>-b</td></tr>\
    <tr><td colspan=2>-o (a|c|i|b|s|k|l|f|p|S)</td>                   <td></td>                     <td></td></tr>\
    <tr><td colspan=2>-W &lt;wrap-length&gt;</td> <td>-d &lt;data-path&gt;</td></tr>\
  </table>\
<p>\
  For &lt;race&gt;, &lt;level&gt;, &lt;strategy&gt;, &lt;class&gt;, and &lt;alignment&gt;, you only\
  need to type part of the full name.  To see what possible options exist\
  for those values, use the -h option, followed by race, level, strategy,\
  class, alignment, or gender. (No space, ie: -hrace, or -hgender).\
<p>\
  If -b is given, background information is generated.  The -W option will\
  cause the lines to wrap at the given line length, at the first white space\
  found.  The -d option species the path to the NPC data files (for names and\
  background files) -- it defaults to '~/.npc/'.\
<p>\
  The -o options are for the stat-block output.  They mean:<br>\
  <table>\
    <tr><td>a: ability bonuses</td>         <td>k: skill breakdown</td></tr>\
    <tr><td>c: AC breakdown</td>            <td>l: languages</td></tr>\
    <tr><td>i: initiative breakdown</td>\   <td>f: skills and feats</td></tr>\
    <tr><td>b: attack breakdown</td>\       <td>p: posessions</td></tr>\
    <tr><td>s: saving throw breakdown</td>\ <td>S: spells</td></tr>\
  </table>\
"
//  The -w option is for determining the output format.  It means:\n\
//    p: output in PCGen format.\n\
//    s: output in stat-block format.\n\
//\n\
//  &lt;path&gt;, when doing stat-block output (-ws), is the name of a file, in\n\
//  which case the output is all redirected to that file.  When doing\n\
//  PCGen output (-wp), &lt;path&gt; is the name of a directory, in which case\n\
//  each NPC is created in a separate file in the given directory.\n\


static int usage(char* buffer, int len) {
    printf("usage(%d, %d);\n", buffer, len);
    strncpy(buffer, USAGE, len);
    buffer[len - 1] = '\0';
    return 1;
}

static int usage2(char* buffer, int len) {
    printf("usage(%d, %d);\n", buffer, len);
    strncpy(buffer, "For help, type \"npc -h\".", len);
    buffer[len - 1] = '\0';
    return 1;
}

static int getLookup( char* parmName, char* arg, LOOKUP_TBL* list, 
                      char * buffer, int len ) {
  int i;
  int found;

  i = lookup( arg, list, &found );
  if( !found ) {
    sprintf( buffer, "Invalid %s: '%s'\n", parmName, arg );
    usage2(buffer + strlen(buffer), len - strlen(buffer));
    return -1;
  }

  return i;
}


static void getHomeDirectory( char* home ) {
  uid_t uid;
  struct passwd *pwd;

  uid = geteuid();
  pwd = getpwuid( uid );

  strcpy( home, pwd->pw_dir );
  if( home[ strlen( home ) - 1 ] != '/' ) {
    strcat( home, "/" );
  }
}


int parseCommandLine( int argc, char* argv[], NPC_OPTS* opts, char* buffer, int len ) {
  int c;
  int i;
  int found;
  int class_count;
  int level_count;
  LOOKUP_TBL* list;

  memset( opts, 0, sizeof( *opts ) );
  opts->race = raceANY_CORE;
  opts->classes[0] = classANY;
  opts->classes[1] = classNONE;
  opts->classes[2] = classNONE;
  opts->levels[0] = levelANY;
  opts->levels[1] = levelANY;
  opts->levels[2] = levelANY;
  opts->score_strategy = 1;
  opts->count = 1;
  opts->gender = gANY;
  opts->wrap = 0;

  getHomeDirectory( opts->data_path );
  strcat( opts->data_path, ".npc/" );

  class_count = 0;
  level_count = 0;

  srand( time( NULL ) );

  optarg = "";
  optind = 0; // Tell getopt that this is the first call.
  while( ( c = getopt( argc, argv, "r:c:l:s:a:S:g:n:h::bo:p:w:W:d:t:" ) ) != -1 ) {
    switch( c ) {
      case 'r':
        opts->race = getLookup( "race", optarg, racetypes, buffer, len );
        break;
      case 'c':
        opts->classes[ class_count++ ] = getLookup( "class", optarg, classtypes, buffer, len );
        break;
      case 'l':
        opts->levels[ level_count ] = lookup( optarg, levels, &found );
        if( !found ) {
          opts->levels[ level_count ] = atoi( optarg );
          if( opts->levels[ level_count ] < 1 ) {
            sprintf( buffer, "Invalid level specification: %s\n", optarg );
            usage2(buffer + strlen(buffer), len - strlen(buffer));
            return 1;
          }
        }
        level_count++;
        break;
      case 's':
        opts->score_strategy = getLookup( "strategy", optarg, strategies_lookup, buffer, len );
        break;
      case 'a':
        opts->alignment = getLookup( "alignment", optarg, alignments, buffer, len );
        break;
      case 'S':
        opts->seed = atoi( optarg );
        srand( opts->seed );
        break;
      case 'g':
        opts->gender = getLookup( "gender", optarg, genders, buffer, len );
        break;
      case 'h':
        if( optarg == 0 ) {
          usage(buffer, len);
          return 1;
        } else {
          i = lookup( optarg, help_lists, &found );
          switch( i ) {
            case HELP_RACES:      list = racetypes; break;
            case HELP_CLASSES:    list = classtypes; break;
            case HELP_ALIGNMENTS: list = alignments; break;
            case HELP_GENDERS:    list = genders; break;
            case HELP_STRATEGIES: list = strategies_lookup; break;
            default:
              sprintf( buffer, "Invalid help specification: %s\n", optarg );
              usage2(buffer + strlen(buffer), len - strlen(buffer));
              return 1;
          }
          for( i = 0; list[ i ].name != 0; i++ ) {
            printf( "  %s\n", list[ i ].name );
          }
          printf( "\n" );
          return 0;
        }
        return 0;
      case 'n':
        opts->count = atoi( optarg );
        break;
      case 'b':
        opts->background = !opts->background;
        break;
      case 'o':
        for( i = 0; optarg[i]; i++ ) {
          switch( optarg[i] ) {
            case 'a': opts->opts.abilityBonuses = !opts->opts.abilityBonuses; break;
            case 'c': opts->opts.acBreakdown = !opts->opts.acBreakdown; break;
            case 'i': opts->opts.initBreakdown = !opts->opts.initBreakdown; break;
            case 'b': opts->opts.attackBreakdown = !opts->opts.attackBreakdown; break;
            case 's': opts->opts.saveBreakdown = !opts->opts.saveBreakdown; break;
            case 'k': opts->opts.skillBreakdown = !opts->opts.skillBreakdown; break;
            case 'l': opts->opts.languages = !opts->opts.languages; break;
            case 'f': opts->opts.skillsAndFeats = !opts->opts.skillsAndFeats; break;
            case 'p': opts->opts.possessions = !opts->opts.possessions; break;
            case 'S': opts->opts.spells = !opts->opts.spells; break;
            default:
              sprintf( buffer, "Invalid stat-block format specifier: %c\n", optarg[i] );
              usage2(buffer + strlen(buffer), len - strlen(buffer));
          }
        }
        break;
      case 'w':
        for( i = 0; optarg[i]; i++ ) {
          switch( optarg[i] ) {
            case 's': opts->mode = MODE_STATBLOCK; break;
            case 'p': opts->mode = MODE_PCGEN; break;
            default:
              sprintf(buffer, "Invalid output mode specifier: %c\n", optarg[i] );
              usage2(buffer + strlen(buffer), len - strlen(buffer));
          }
        }
        break;
      case 'p':
        strcpy( opts->path, optarg );
        break;
      case 'W':
        opts->wrap = atoi( optarg );
        break;
      case 'd':
        strcpy( opts->data_path, optarg );
        if( opts->data_path[ strlen( opts->data_path )-1 ] != '/' ) {
          strcat( opts->data_path, "/" );
        }
        break;

      default:
        usage(buffer, len);
        return 1;
    }
  }

  return 0;
}


static void wrapLines( char* string, int width ) {
  int     c;
  int     count;
  int     i;
  int     last;

  if( width > 0 ) {
    count = width+1;
    last = 0;
    while( count < strlen( string ) ) {
      for( i = last; i < count; i++ ) {
        if( string[i] == '\n' )
          break;
      }

      if( string[i] != '\n' ) {
        for( i = count; i > 0; i-- ) {
          c = string[i];
          if( isspace( c ) ) {
            string[i] = '\n';
            break;
          }
        }
      }

      last = i+1;
      count = i + width+1;
    }
  }
}


int displayNPC_StatBlock( NPC_OPTS* opts, FILE *output, NPC* npc ) {
  char    statBlock[4096];
  int     count;
  int     i;
  int     doBg;
  char    motivation1[ 1024 ];
  char    motivation2[ 1024 ];
  grGRAMMAR* grammar;

  if( opts->background ) {
    grammar = openNPCMotivationGrammar( opts->data_path );
  }

  npcBuildStatBlock( npc, &opts->opts, statBlock, sizeof( statBlock ) );

  strrepl( statBlock, "~B", "" );
  strrepl( statBlock, "~b", "" );
  strrepl( statBlock, "~I", "" );
  strrepl( statBlock, "~i", "" );

  wrapLines( statBlock, opts->wrap );
  fputs( statBlock, output );

  if( opts->background) {
  	if (grammar) {
	    grammar->startSymbol = "[motivation]";
	    getNPCMotivation( grammar, npc, motivation1, sizeof( motivation1 ) );
	    do {      
	      getNPCMotivation( grammar, npc, motivation2, sizeof( motivation1 ) );
	    } while( strcmp( motivation1, motivation2 ) == 0 );
	
	    strcpy( statBlock, "Primary motivation: " );
	    strcat( statBlock, motivation1 );
	    wrapLines( statBlock, opts->wrap );
	    fprintf( output, "\n\n%s\n", statBlock );
	
	    strcpy( statBlock, "Secondary motivation: " );
	    strcat( statBlock, motivation2 );
	    wrapLines( statBlock, opts->wrap );
	    fprintf( output, "\n%s\n", statBlock );
	
	    getNPCRecentPast( grammar, npc, motivation1, sizeof( motivation1 ) );
	
	    strcpy( statBlock, "Recent Past: " );
	    strcat( statBlock, motivation1 );
	    wrapLines( statBlock, opts->wrap );
	    fprintf( output, "\n%s\n", statBlock );
	} else fprintf( output, "\n\nNo background history files found. Have you specified the correct directory?\n");
  }

  if( opts->background && grammar) {
    grDestroyGrammar( grammar );
  }

  fprintf( output, "\n" );

  return 0;
}


/*
  int main( int argc, char* argv[] ) {
  char buffer[512];
  int i;
  FILE *output;
       
  NPC* npc;
  NPCGENERATOROPTS opts;
  NPCGENERATOROPTS tempOpts;
  NPC_OPTS cmd_opts;

  if( parseCommandLine( argc, argv, &cmd_opts ) != 0 ) {
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

  if( cmd_opts.mode == MODE_STATBLOCK && cmd_opts.path[0] != 0 ) {
    output = fopen( cmd_opts.path, "w" );
  } else {
    output = stdout;
  }

  for( i = 0; i < cmd_opts.count; i++ ) {
    memcpy( &tempOpts, &opts, sizeof( tempOpts ) );
    npc = npcGenerateNPC( &tempOpts );
    if( cmd_opts.mode == MODE_STATBLOCK ) {
      displayNPC_StatBlock( &cmd_opts, output, npc );
      if( i+1 < cmd_opts.count ) {
        fprintf( output, "---------------------------\n" );
      }
    } else if( cmd_opts.mode == MODE_PCGEN ) {
      if( cmd_opts.path[0] != 0 ) {
        fclose( output );
        strcpy( buffer, cmd_opts.path );
        strcat( buffer, "/" );
        strcat( buffer, npc->name );
        strcat( buffer, ".pcg" );
        output = fopen( buffer, "w" );
      }
      convertToPCGen( npc, output );
      fprintf( output, "\n" );
    }
    npcDestroyNPC( npc );
  }

  if( output != stdout )
  {
    fclose( output );
  }

  return 0;
}

*/

