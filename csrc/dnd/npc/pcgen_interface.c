#include <ctype.h>
#include <string.h>

#include "npcEngine.h"
#include "dndconst.h"
#include "dndutil.h"

#include "pcgen_interface.h"


static int writeFeat( FILE* output, NPCFEAT* feats, int type );
static int writeSpells( FILE* output, NPCCLASS* cls );
static int computeMinimumXP( NPC* npc );
static int getPCGenAlignmentCode( NPC* npc );

static int mixCase( char* to, char* from );


static int mixCase( char* to, char* from ) {
  int i;
  int upit;

  strcpy( to, from );

  upit = 1;
  for( i = 0; to[i] != 0; i++ ) {
    if( upit && isalpha( to[i] ) ) {
      to[i] = toupper( to[i] );
      upit = 0;
    }
    upit = ( !isalpha( to[i] ) && to[i] != '\'' );
  }

  return 0;
}


static int writeFeat( FILE* output, NPCFEAT* feats, int type ) {
  NPCFEAT*       feat;
  NPCFEATWEAPON* nfw;
  NPCFEATSKILL*  nfs;
  NPCFEATSCHOOL* nfsch;
  NPCFEATSPELLS* nfsp;
  int            count;
  int            i;
  char           buffer[ 128 ];

  count = 0;
  for( feat = feats; feat != 0; feat = feat->next ) {
    if( feat->type == type ) {
      count++;
    }
  }

  if( count < 1 ) {
    return 0;
  }

  //mixCase( buffer, dndGetFeatName( type ) );
  //fprintf( output, "FEAT:%s|APPLIEDTO:", buffer);

  for( feat = feats; feat != 0; feat = feat->next ) {
    if( feat->type == type ) {
	  strcpy( buffer, dndGetFeatName( type ) );
      switch( feat->type ) {
        case ftSPELLMASTERY:
          nfsp = feat->data;
		  fprintf( output, "FEAT:Spell Mastery|APPLIEDTO:MULTISELECT:%d&colon;%d&colon;",nfsp->count,nfsp->count);
          for( i = 0; i < nfsp->count; i++ ) {
            strcpy( buffer, dndGetSpellPCGenName( nfsp->spells[ i ] ) );
			//fprintf( output, "FEAT:Spell Mastery|APPLIEDTO:");
            fprintf( output, "%s", buffer );
			//fprintf( output, "|TYPE:Special|DESC:See Text\n");
			if (i < (nfsp->count - 1)) fprintf( output, "&colon;");
          }
		  fprintf( output, "|TYPE:Special|DESC:See Text\n");
          break;
        case ftSPELLFOCUS:
          nfsch = feat->data;
          mixCase( buffer, dndGetSchoolOfMagicName( nfsch->school ) );
		  fprintf( output, "FEAT:Spell Focus|APPLIEDTO:");
          fprintf( output, "%s", buffer );
		  fprintf( output, "|TYPE:General|DESC:See Text\n");
          break;
        case ftGREATERSPELLFOCUS:
          nfsch = feat->data;
          mixCase( buffer, dndGetSchoolOfMagicName( nfsch->school ) );
		  fprintf( output, "FEAT:Greater Spell Focus|APPLIEDTO:");
          fprintf( output, "%s", buffer );
		  fprintf( output, "|TYPE:General|DESC:See Text\n");
          break;
        case ftSIMPLEWEAPONPROFICIENCY:
        case ftMARTIALWEAPONPROFICIENCY:
        case ftEXOTICWEAPONPROFICIENCY:
        case ftIMPROVEDCRITICAL:
        case ftRAPIDRELOAD:
        case ftWEAPONFOCUS:
        case ftGREATERWEAPONFOCUS:
        case ftWEAPONSPECIALIZATION:
        case ftGREATERWEAPONSPECIALIZATION:
          nfw = feat->data;
          strcpy( buffer, dndGetWeaponPCGenName( nfw->weapon ) );
		  fprintf( output, "FEAT:%s|APPLIEDTO:",dndGetFeatName( type ));
          fprintf( output, "%s", buffer );
		  fprintf( output, "|TYPE:General|DESC:See Text\n");
          break;
        case ftSKILLFOCUS:
          nfs = feat->data;
          strcpy( buffer, dndGetSkillName( nfs->skill ) );
		  fprintf( output, "FEAT:%s|APPLIEDTO:",dndGetFeatName( type ));
          fprintf( output, "%s", buffer );
		  fprintf( output, "|TYPE:General|DESC:See Text\n");
          break;
        case ftTOUGHNESS:
		  fprintf( output, "FEAT:Toughness|APPLIEDTO:+3 HP|TYPE:General|DESC:See Text\n");
          break;
//		case ftRANGERARCHERY:
//		case ftRANGERGREATERARCHERY:
//		case ftRANGERGREATERTWOWEAPONFIGHTING:
//		case ftRANGERIMPROVEDARCHERY:
//		case ftRANGERIMPROVEDTWOWEAPONFIGHTING:
//		case ftRANGERTWOWEAPONFIGHTING:
//			continue;

      }
    }
  }

  return 0;
}


static int writeSpells( FILE* output, NPCCLASS* cls ) {
  NPCSPELL** spells;
  NPCSPELL*  spell;
  int i;
  char buffer[ 128 ];
  char buffer2[ 128 ];

  switch( cls->type ) {
    case pcWIZARD:   spells = ((NPCWIZARDDATA*)cls->data)->spells; break;
    case pcBARD:     spells = ((NPCBARDDATA*)cls->data)->spells; break;
    case pcSORCERER: spells = ((NPCSORCERERDATA*)cls->data)->spells; break;
    default:
      spells = 0;
  }

  if( spells != 0 ) {
	 mixCase( buffer2, dndGetClassName( cls->type ) );
    for( i = 0; i < 10; i++ ) {
      for( spell = spells[i]; spell != 0; spell = spell->next ) {
        strcpy( buffer, dndGetSpellPCGenName( spell->spell ) );
		fprintf( output, "SPELLNAME:%s|TIMES:1|CLASS:%s|BOOK:Known Spells|SPELLLEVEL:%d|SOURCE:[TYPE:CLASS|NAME:%s]\n",buffer,buffer2,dndGetSpellLevel(cls->type, spell->spell),buffer2);
      }
    }
  }

  fprintf( output, "\n" );

  if( cls->type == pcCLERIC) {
    fprintf( output, "\n" ); /* for Domain spells */
  }

  return 0;
}


static int computeMinimumXP( NPC* npc ) {
  NPCCLASS* cls;
  int       i;
  int       xp;
  int		levels = 0;

  xp = 0;
  for( cls = npc->classes; cls != 0; cls = cls->next ) {
	levels += cls->level;
	/*
    for( i = 0; i < cls->level; i++ ) {
      //xp += ( cls->level - 1 ) * 1000;
	  xp += (i+levels) * 1000;
    }
	*/

  }
  for(i=0;i<levels;i++) {
	xp += i * 1000;
  }

  return xp;
}


static int getPCGenAlignmentCode( NPC* npc ) {
  int code = 0;

  if( npc->alignment & alLCNEUTRAL ) {
    code = 3;
  } else if( npc->alignment & alCHAOTIC ) {
    code = 6;
  }

  if( npc->alignment & alGENEUTRAL ) {
    code++;
  } else if( npc->alignment & alEVIL ) {
    code += 2;
  }

  return code;
}


int convertToPCGen( NPC* npc, FILE* output ) {
  NPCCLASS* cls;
  int       i,j;
  int       hp_per_lev;
  int       hp_extra;
  NPCFEAT*  feat;
  NPCSKILL* skill;
  NPCLANGUAGE* language;
  int       is_literate;
  char      buffer[ 128 ];
  char      buffer2[ 128 ];
  char      buffer3[ 128 ];
  char      buffer4[ 128 ];
  char      tmp[ 255 ];
  NPCCLERICDATA* clericData;
  int		can_turn = 0;
  NPCWIZARDDATA* wiz;

// Version Block

	fprintf( output, "PCGVERSION:2.0\n\n");

// System Block

	fprintf( output, "# System Information\n");
	fprintf( output, "CAMPAIGN:WotC - DnD Core Rulebook I - PHB(3.5)|CAMPAIGN:WotC - DnD Core Rulebook II - DMG(3.5)|CAMPAIGN:WotC - DnD Core Rulebook II - DMG(3.5), No Races|CAMPAIGN:WotC - Revised (v.3.5) System Reference Document\n" );
	fprintf( output, "VERSION:5.5.1\n");
	fprintf( output, "ROLLMETHOD:8|EXPRESSION:10\n");
	fprintf( output, "PURCHASEPOINTS:N|TYPE:\n");
	fprintf( output, "POOLPOINTS:0\n");
	fprintf( output, "GAMEMODE:35e\n");
	fprintf( output, "TABLABEL:0\n");
	fprintf( output, "AUTOSPELLS:Y\n");
	fprintf( output, "LOADCOMPANIONS:N\n");
	fprintf( output, "USETEMPMODS:N\n");
	fprintf( output, "AUTOSORTGEAR:Y\n");
	fprintf( output, "AUTOSORTSKILLS:Y\n\n");

// Bio Block
	fprintf( output, "# Character Bio\n");

	switch( npc->race ) {
		case rcELF_HIGH: strcpy( buffer, "Elf" ); break;
		case rcDWARF_HILL: strcpy( buffer, "Dwarf" ); break;
		case rcGNOME_ROCK: strcpy( buffer, "Gnome" ); break;
		case rcHALFLING_LIGHTFOOT: strcpy( buffer, "Halfling" ); break;
		case rcHALFORC: strcpy( buffer, "Half-orc" ); break;
		default:
		  mixCase( buffer, dndGetRaceName( npc->race ) );
	}


	fprintf( output, "CHARACTERNAME:%s %s %s ",npc->name,( npc->gender == gMALE ? "Male" : "Female" ),buffer);

	for( cls = npc->classes; cls != 0; cls = cls->next ) {
		mixCase( buffer, dndGetClassAbbr( cls->type ) );
		if (cls->type == pcWIZARD) {
			wiz = cls->data;
			if (wiz->favoredSchool) {
				mixCase( buffer, dndGetSpecialistName( wiz->favoredSchool ) );
			}
		}

		fprintf( output, "%s%d", buffer, cls->level );
	}
	fprintf( output, "\n" );

//	fprintf( output, "CHARACTERNAME:%s\n", npc->name);
	fprintf( output, "TABNAME:\n");
	fprintf( output, "PLAYERNAME:NPC\n");
	fprintf( output, "HEIGHT:%d\n",npc->height_ft * 12 + npc->height_in);
	fprintf( output, "WEIGHT:%d\n",npc->weight);
	fprintf( output, "AGE:%d\n",npc->age);
	fprintf( output, "GENDER:%s\n",( npc->gender == gMALE ? "Male" : "Female" ));
	fprintf( output, "HANDED:Right\n");
	fprintf( output, "SKINCOLOR:\n");
	fprintf( output, "EYECOLOR:\n");
	fprintf( output, "HAIRCOLOR:\n");
	fprintf( output, "HAIRSTYLE:\n");
	fprintf( output, "LOCATION:\n");
	fprintf( output, "CITY:\n");
	fprintf( output, "BIRTHPLACE:\n");
	fprintf( output, "PERSONALITYTRAIT1:\n");
	fprintf( output, "PERSONALITYTRAIT2:\n");
	fprintf( output, "SPEECHPATTERN:\n");
	fprintf( output, "PHOBIAS:\n");
	fprintf( output, "INTERESTS:\n");
	fprintf( output, "CATCHPHRASE:\n");
	fprintf( output, "PORTRAIT:\n\n");

// Attribute Block

	fprintf( output, "# Character Attributes\n");
	fprintf( output, "STAT:STR|SCORE:%d\n",npc->strength - dndGetRaceBonus( npc->race, npc->gender, rbtABILITYSCORE, abSTRENGTH ));
	fprintf( output, "STAT:DEX|SCORE:%d\n",npc->dexterity - dndGetRaceBonus( npc->race, npc->gender, rbtABILITYSCORE, abDEXTERITY ));
	fprintf( output, "STAT:CON|SCORE:%d\n",npc->constitution - dndGetRaceBonus( npc->race, npc->gender, rbtABILITYSCORE, abCONSTITUTION ));
	fprintf( output, "STAT:INT|SCORE:%d\n",npc->intelligence - dndGetRaceBonus( npc->race, npc->gender, rbtABILITYSCORE, abINTELLIGENCE ));
	fprintf( output, "STAT:WIS|SCORE:%d\n",npc->wisdom - dndGetRaceBonus( npc->race, npc->gender, rbtABILITYSCORE, abWISDOM ));
	fprintf( output, "STAT:CHA|SCORE:%d\n",npc->charisma - dndGetRaceBonus( npc->race, npc->gender, rbtABILITYSCORE, abCHARISMA ));

	if (npc->alignment == (alLCNEUTRAL | alGENEUTRAL)) fprintf( output, "ALIGN:TN\n");
	else fprintf( output, "ALIGN:%s\n",dndGetAlignmentAbbr( npc->alignment ));

	switch( npc->race ) {
		case rcELF_HIGH: strcpy( buffer, "Elf" ); break;
		case rcDWARF_HILL: strcpy( buffer, "Dwarf" ); break;
		case rcGNOME_ROCK: strcpy( buffer, "Gnome" ); break;
		case rcHALFLING_LIGHTFOOT: strcpy( buffer, "Halfling" ); break;
		case rcHALFORC: strcpy( buffer, "Half-orc" ); break;
		default:
		  mixCase( buffer, dndGetRaceName( npc->race ) );
	}

	fprintf( output, "RACE:%s\n\n",buffer);

// Classes Block

	fprintf( output, "# Character Class(es)\n");

	for( cls = npc->classes; cls != 0; cls = cls->next ) {
		strcpy(buffer2,"");
		strcpy(buffer3,"");
		strcpy(buffer4,"");
		mixCase( buffer, dndGetClassName( cls->type ));
		mixCase( buffer2, dndGetClassName( cls->type ));
		if (cls->type == pcWIZARD) {
			wiz = cls->data;
			if (wiz->favoredSchool) {
				mixCase( buffer2, dndGetSpecialistName(wiz->favoredSchool));
				mixCase(tmp,dndGetSchoolOfMagicName(wiz->opposedSchools[0]));
				sprintf(buffer3,"|PROHIBITED:%s",tmp);
				if (wiz->opposedSchools[1]) {
					mixCase(tmp,dndGetSchoolOfMagicName(wiz->opposedSchools[1]));
					sprintf(buffer4,",%s",tmp);
				}
			}
		}
		fprintf( output, "CLASS:%s|SUBCLASS:%s|LEVEL:%d|SKILLPOOL:0%s%s\n",buffer,buffer2,cls->level,buffer3,buffer4);
		if (cls->type == pcCLERIC) can_turn = 1;
		if (cls->type == pcPALADIN && cls->level >= 4) can_turn = 1;

	}

	for( cls = npc->classes; cls != 0; cls = cls->next ) {
		mixCase( buffer, dndGetClassName( cls->type ));
		hp_per_lev = cls->hp / cls->level;
		hp_extra = cls->hp % cls->level;
		for( i = 0; i < cls->level; i++ ) {
		//	fprintf( output, "CLASSABILITIESLEVEL:%s=%d|HITPOINTS:%d|SKILLSGAINED:%d\n",buffer,i+1,hp_per_lev + ( hp_extra > 0 ? 1 : 0 ),cls->skillpoints[i]);
			fprintf( output, "CLASSABILITIESLEVEL:%s=%d|HITPOINTS:%d|SKILLSGAINED:%d\n",buffer,i+1,cls->levelhp[i],cls->skillpoints[i]);
			hp_extra--;
		}

	}
	fprintf( output, "\n");

// Experience Block

	fprintf( output, "# Character Experience\n");
	fprintf( output, "EXPERIENCE:%d\n\n",computeMinimumXP( npc ));

// Template and Region Block

	fprintf( output, "# Character Templates\n");
	fprintf( output, "\n");
	fprintf( output, "# Character Region\n\n");

// Skill Block

	fprintf( output, "# Character Skills\n");

	j=1;
	for( skill = npc->skills; skill != 0; skill = skill->next ) {
		if (skill->rank > 0) {
			strcpy( buffer, dndGetSkillName( skill->type ) );
			fprintf( output, "SKILL:%s|OUTPUTORDER:%d|",buffer,j++);
			
			for(i=1;i<100;i++) {
				if (skill->classrank[i] > 0.4f) {
					mixCase( buffer, dndGetClassName(i) );
					fprintf( output, "CLASSBOUGHT:[CLASS:%s|RANKS:%g|COST:%d|CLASSSKILL:%c]",buffer,skill->classrank[i],( dndGetSkillType(i,skill->type) == sktCLASS ? 1 : 2), ( dndGetSkillType(i,skill->type) == sktCLASS ? 'Y' : 'N'));
				}
			}
			fprintf( output, "\n");
		}
	}
	fprintf( output, "\n");

// Language Block
	
	fprintf( output, "# Character Languages\n");
	for( language = npc->languages; language != 0; language = language->next ) {
		mixCase( buffer, dndGetLanguageName( language->language ) );
		fprintf( output, "LANGUAGE:%s", buffer );
		if (language->next) fprintf( output, "|");
		else fprintf( output, "\n");
	}

	fprintf( output, "\n");

// Feat Block

  fprintf( output, "# Character Feats\n");
  if (can_turn) {
	if (npc->alignment & alEVIL) fprintf( output, "FEAT:Rebuke Undead|TYPE:TURNUNDEAD|DESC:\n");
	else fprintf( output, "FEAT:Turn Undead|TYPE:TURNUNDEAD|DESC:\n");
  }
  for( feat = npc->feats; feat != 0; feat = feat->next ) {
    switch( feat->type ) {
		case ftSPELLMASTERY:
		case ftSPELLFOCUS:
		case ftGREATERSPELLFOCUS:
		case ftSIMPLEWEAPONPROFICIENCY:
		case ftMARTIALWEAPONPROFICIENCY:
		case ftEXOTICWEAPONPROFICIENCY:
		case ftIMPROVEDCRITICAL:
		case ftRAPIDRELOAD:
		case ftWEAPONFOCUS:
		case ftWEAPONSPECIALIZATION:
		case ftGREATERWEAPONFOCUS:
		case ftGREATERWEAPONSPECIALIZATION:
		case ftSKILLFOCUS:
		case ftTOUGHNESS:
//		case ftRANGERARCHERY:
//		case ftRANGERGREATERARCHERY:
//		case ftRANGERGREATERTWOWEAPONFIGHTING:
//		case ftRANGERIMPROVEDARCHERY:
//		case ftRANGERIMPROVEDTWOWEAPONFIGHTING:
//		case ftRANGERTWOWEAPONFIGHTING:
			continue;

		  continue;
	  case ftEXTRATURNING:
		  fprintf( output, "FEAT:Extra Turning|APPLIEDTO:TurnUndead|TYPE:GENERAL|DESC:See Text\n");
		  continue;
	  //case ftRANGER
    }
	strcpy( buffer, dndGetFeatName( feat->type ) );
	if (feat->autoAdd) fprintf( output, "VFEAT:%s|", buffer );
	else fprintf( output, "FEAT:%s|", buffer );
	switch (dndGetFeatType(feat->type)) {
		case fttGENERAL: fprintf( output, "TYPE:General|DESC:See Text\n", buffer ); break;
		case fttITEMCREATION: fprintf( output, "TYPE:ItemCreation|DESC:See Text\n", buffer ); break;
		case fttMETAMAGIC: fprintf( output, "TYPE:Metamagic|DESC:See Text\n", buffer ); break;
		default: fprintf( output, "TYPE:Special|DESC:See Text\n", buffer ); break;
	}
  }
  writeFeat( output, npc->feats, ftSPELLMASTERY );
  writeFeat( output, npc->feats, ftSPELLFOCUS );
  writeFeat( output, npc->feats, ftGREATERSPELLFOCUS );
  writeFeat( output, npc->feats, ftSIMPLEWEAPONPROFICIENCY);
  writeFeat( output, npc->feats, ftMARTIALWEAPONPROFICIENCY);
  writeFeat( output, npc->feats, ftEXOTICWEAPONPROFICIENCY);
  writeFeat( output, npc->feats, ftIMPROVEDCRITICAL );
  writeFeat( output, npc->feats, ftRAPIDRELOAD );
  writeFeat( output, npc->feats, ftWEAPONFOCUS );
  writeFeat( output, npc->feats, ftWEAPONSPECIALIZATION );
  writeFeat( output, npc->feats, ftGREATERWEAPONFOCUS );
  writeFeat( output, npc->feats, ftGREATERWEAPONSPECIALIZATION );
  writeFeat( output, npc->feats, ftSKILLFOCUS );
  writeFeat( output, npc->feats, ftTOUGHNESS );

  fprintf( output, "FEATPOOL:0.0\n\n" );

// Misc Block

	fprintf( output, "# Character Equipment\n");
	fprintf( output, "MONEY:%d\n",npcGearValue( npc ));
	fprintf( output, "EQUIPNAME:Outfit (Explorer's)|OUTPUTORDER:0|COST:0|WT:8.0|QUANTITY:1.0|CUSTOMIZATION:[BASEITEM:Outfit (Explorer's)|DATA:COSTMOD=-10]\n");
	fprintf( output, "EQUIPSET:Default Set|ID:0.1\n");
	fprintf( output, "EQUIPSET:Torso|ID:0.1.1|VALUE:Outfit (Explorer's)|QUANTITY:1.0\n");
	fprintf( output, "CALCEQUIPSET:0.1\n\n");


	fprintf( output, "# Temporary Bonuses\n\n");

	fprintf( output, "# EquipSet Temp Bonuses\n\n");

// Domain Block

	fprintf( output, "# Character Deity/Domain\n");
	  for( cls = npc->classes; cls != 0; cls = cls->next ) {
		if( cls->type == pcCLERIC ) {
		  clericData = (NPCCLERICDATA*)cls->data;
		  fprintf( output, "DEITY:None|DEITYDOMAINS:[DOMAIN:Air|DOMAIN:Animal|DOMAIN:Chaos|DOMAIN:Death|DOMAIN:Destruction|DOMAIN:Earth|DOMAIN:Evil|DOMAIN:Fire|DOMAIN:Good|DOMAIN:Healing|DOMAIN:Knowledge|DOMAIN:Law|DOMAIN:Luck|DOMAIN:Magic|DOMAIN:Plant|DOMAIN:Protection|DOMAIN:Strength|DOMAIN:Sun|DOMAIN:Travel|DOMAIN:Trickery|DOMAIN:War|DOMAIN:Water]|ALIGNALLOW:012345678|DESC:None|HOLYITEM:None|DEITYFAVWEAP:[]|DEITYALIGN:\n");
		  mixCase( buffer, dndGetDomainName( clericData->domain[0] ) );
		  fprintf( output, "DOMAIN:%s|DOMAINGRANTS:See Text|SOURCE:[TYPE:PCClass|NAME:Cleric|LEVEL:1]\n", buffer );
		  mixCase( buffer, dndGetDomainName( clericData->domain[1] ) );
		  fprintf( output, "DOMAIN:%s|DOMAINGRANTS:See Text|SOURCE:[TYPE:PCClass|NAME:Cleric|LEVEL:1]\n", buffer );
		  break;
		}
	  }
	fprintf( output, "\n" );
// Spell Block

	fprintf( output, "# Character Spells Information\n");
  is_literate = 0;
  for( cls = npc->classes; cls != 0; cls = cls->next ) {
    writeSpells( output, cls );
    is_literate = ( is_literate || ( cls->type != pcBARBARIAN ) );
  }
	fprintf( output, "\n" );
// Other Block

	fprintf( output, "# Character Description/Bio/History\n");
	fprintf( output, "CHARACTERBIO:\n");
	fprintf( output, "CHARACTERDESC:\n");
	fprintf( output, "CHARACTERCOMP:\n");
	fprintf( output, "CHARACTERASSET:\n");
	fprintf( output, "CHARACTERMAGIC:\n\n");

	fprintf( output, "# Character Master/Follower\n\n");

	fprintf( output, "# Character Notes Tab\n\n");

	fprintf( output, "# Kits\n\n");

	fprintf( output, "# Chosen Armor Profs\n\n");

	fprintf( output, "# Age Set Selections\n\n");
	fprintf( output, "AGESET:1:0:0:0:0:0:0:0:0:0\n\n");

  return 0;
}



