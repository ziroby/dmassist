/* ---------------------------------------------------------------------- *
 * dndutil.c
 *
 * by Jamis Buck (jgb3@email.byu.edu)
 *
 * Utility functions for the Dungeons & Dragons(tm) API.  This file is in
 * the public domain, except for portions marked "Town gen by Ziroby"
 *
 * ---------------------------------------------------------------------- */

/* ---------------------------------------------------------------------- *
 * Dependencies
 * ---------------------------------------------------------------------- */

#include <string.h>

#include "dndconst.h"
#include "dndutil.h"

/* ---------------------------------------------------------------------- *
 * Constants
 * ---------------------------------------------------------------------- */

#if !defined(NULL)
#define NULL ( 0 )
#endif

/* ---------------------------------------------------------------------- *
 * Data types
 * ---------------------------------------------------------------------- */

typedef struct __skillsforclass__ SKILLSFORCLASS;
typedef struct __featprereq__     FEATPREREQ;
typedef struct __spellsforclass__ SPELLSFORCLASS;
typedef struct __racialbonus__    RACIALBONUS;

typedef int SPELLMATRIX[20][10];

struct __spellsforclass__ {
  int spell;
  int level;
};

struct __featprereq__ {
  int preReqType;
  int data1;
  int data2;
};

struct __skillsforclass__ {
  int skill;
  int classSkill;
};

struct __racialbonus__  {
  int type;
  int data;
  int bonus;
};

/* ---------------------------------------------------------------------- *
 * Data definitions
 * ---------------------------------------------------------------------- */

/* class and cross-class skill designations */


static SKILLSFORCLASS barbarianSkills[] = {
  { skAPPRAISE,		0 },
  { skBALANCE,		0 },
  { skBLUFF,		0 },
  { skCLIMB,		1 },
  { skCONCENTRATION,		0 },
  { skCRAFT_ALCHEMY,		1 },
  { skCRAFT_ARMORSMITHING,		1 },
  { skCRAFT_BLACKSMITHING,		1 },
  { skCRAFT_BOWMAKING,		1 },
  { skCRAFT_CARPENTRY,		1 },
  { skCRAFT_LEATHERWORKING,		1 },
  { skCRAFT_PAINTING,		1 },
  { skCRAFT_POTTERY,		1 },
  { skCRAFT_SCULPTING,		1 },
  { skCRAFT_SHIPMAKING,		1 },
  { skCRAFT_STONEMASONRY,		1 },
  { skCRAFT_TRAPMAKING,		1 },
  { skCRAFT_WEAPONSMITHING,		1 },
  { skCRAFT_WOODWORKING,		1 },
  { skDECIPHERSCRIPT,		0 },
  { skDIPLOMACY,		0 },
  { skDISABLEDEVICE,		0 },
  { skDISGUISE,		0 },
  { skESCAPEARTIST,		0 },
  { skFORGERY,		0 },
  { skGATHERINFORMATION,		0 },
  { skHANDLEANIMAL,		1 },
  { skHEAL,		0 },
  { skHIDE,		0 },
  { skINTIMIDATE,		1 },
  { skJUMP,		1 },
  { skKNOWLEDGE_ARCANA,		0 },
  { skKNOWLEDGE_ARCHITECTUREANDENGINEERING,		0 },
  { skKNOWLEDGE_DUNGEONEERING,		0 },
  { skKNOWLEDGE_GEOGRAPHY,		0 },
  { skKNOWLEDGE_HISTORY,		0 },
  { skKNOWLEDGE_LOCAL,		0 },
  { skKNOWLEDGE_NATURE,		0 },
  { skKNOWLEDGE_NOBILITYANDROYALTY,		0 },
  { skKNOWLEDGE_RELIGION,		0 },
  { skKNOWLEDGE_THEPLANES,		0 },
  { skLISTEN,		1 },
  { skMOVESILENTLY,		0 },
  { skOPENLOCK,		0 },
  { skPERFORM_ACT,		0 },
  { skPERFORM_COMEDY,		0 },
  { skPERFORM_DANCE,		0 },
  { skPERFORM_KEYBOARDINSTRUMENTS,		0 },
  { skPERFORM_ORATORY,		0 },
  { skPERFORM_PERCUSSIONINSTRUMENTS,		0 },
  { skPERFORM_SING,		0 },
  { skPERFORM_STRINGINSTRUMENTS,		0 },
  { skPERFORM_WINDINSTRUMENTS,		0 },
  { skPROFESSION_HUNTER,		0 },
  { skPROFESSION_MINER,		0 },
  { skRIDE,		1 },
  { skSEARCH,		0 },
  { skSENSEMOTIVE,		0 },
  { skSLEIGHTOFHAND,		0 },
  { skSPEAKLANGUAGE,		0 },
  { skSPELLCRAFT,		0 },
  { skSPOT,		0 },
  { skSURVIVAL,		1 },
  { skSWIM,		1 },
  { skTUMBLE,		0 },
  { skUSEMAGICDEVICE,		0 },
  { skUSEROPE,		0 },
  { 0,		0 }
};

static SKILLSFORCLASS bardSkills[] = {
  { skAPPRAISE,		1 },
  { skBALANCE,		1 },
  { skBLUFF,		1 },
  { skCLIMB,		1 },
  { skCONCENTRATION,		1 },
  { skCRAFT_ALCHEMY,		1 },
  { skCRAFT_ARMORSMITHING,		1 },
  { skCRAFT_BLACKSMITHING,		1 },
  { skCRAFT_BOWMAKING,		1 },
  { skCRAFT_CARPENTRY,		1 },
  { skCRAFT_LEATHERWORKING,		1 },
  { skCRAFT_PAINTING,		1 },
  { skCRAFT_POTTERY,		1 },
  { skCRAFT_SCULPTING,		1 },
  { skCRAFT_SHIPMAKING,		1 },
  { skCRAFT_STONEMASONRY,		1 },
  { skCRAFT_TRAPMAKING,		1 },
  { skCRAFT_WEAPONSMITHING,		1 },
  { skCRAFT_WOODWORKING,		1 },
  { skDECIPHERSCRIPT,		1 },
  { skDIPLOMACY,		1 },
  { skDISABLEDEVICE,		0 },
  { skDISGUISE,		1 },
  { skESCAPEARTIST,		1 },
  { skFORGERY,		0 },
  { skGATHERINFORMATION,		1 },
  { skHANDLEANIMAL,		0 },
  { skHEAL,		0 },
  { skHIDE,		1 },
  { skINTIMIDATE,		0 },
  { skJUMP,		1 },
  { skKNOWLEDGE_ARCANA,		1 },
  { skKNOWLEDGE_ARCHITECTUREANDENGINEERING,		1 },
  { skKNOWLEDGE_DUNGEONEERING,		1 },
  { skKNOWLEDGE_GEOGRAPHY,		1 },
  { skKNOWLEDGE_HISTORY,		1 },
  { skKNOWLEDGE_LOCAL,		1 },
  { skKNOWLEDGE_NATURE,		1 },
  { skKNOWLEDGE_NOBILITYANDROYALTY,		1 },
  { skKNOWLEDGE_RELIGION,		1 },
  { skKNOWLEDGE_THEPLANES,		1 },
  { skLISTEN,		1 },
  { skMOVESILENTLY,		1 },
  { skOPENLOCK,		0 },
  { skPERFORM_ACT,		1 },
  { skPERFORM_COMEDY,		1 },
  { skPERFORM_DANCE,		1 },
  { skPERFORM_KEYBOARDINSTRUMENTS,		1 },
  { skPERFORM_ORATORY,		1 },
  { skPERFORM_PERCUSSIONINSTRUMENTS,		1 },
  { skPERFORM_SING,		1 },
  { skPERFORM_STRINGINSTRUMENTS,		1 },
  { skPERFORM_WINDINSTRUMENTS,		1 },
  { skPROFESSION_HUNTER,		1 },
  { skPROFESSION_MINER,		1 },
  { skRIDE,		0 },
  { skSEARCH,		0 },
  { skSENSEMOTIVE,		1 },
  { skSLEIGHTOFHAND,		1 },
  { skSPEAKLANGUAGE,		1 },
  { skSPELLCRAFT,		1 },
  { skSPOT,		0 },
  { skSURVIVAL,		0 },
  { skSWIM,		1 },
  { skTUMBLE,		1 },
  { skUSEMAGICDEVICE,		1 },
  { skUSEROPE,		0 },
  { 0,		0 }
};

static SKILLSFORCLASS clericSkills[] = {
  { skAPPRAISE,		0 },
  { skBALANCE,		0 },
  { skBLUFF,		0 },
  { skCLIMB,		0 },
  { skCONCENTRATION,		1 },
  { skCRAFT_ALCHEMY,		1 },
  { skCRAFT_ARMORSMITHING,		1 },
  { skCRAFT_BLACKSMITHING,		1 },
  { skCRAFT_BOWMAKING,		1 },
  { skCRAFT_CARPENTRY,		1 },
  { skCRAFT_LEATHERWORKING,		1 },
  { skCRAFT_PAINTING,		1 },
  { skCRAFT_POTTERY,		1 },
  { skCRAFT_SCULPTING,		1 },
  { skCRAFT_SHIPMAKING,		1 },
  { skCRAFT_STONEMASONRY,		1 },
  { skCRAFT_TRAPMAKING,		1 },
  { skCRAFT_WEAPONSMITHING,		1 },
  { skCRAFT_WOODWORKING,		1 },
  { skDECIPHERSCRIPT,		0 },
  { skDIPLOMACY,		1 },
  { skDISABLEDEVICE,		0 },
  { skDISGUISE,		0 },
  { skESCAPEARTIST,		0 },
  { skFORGERY,		0 },
  { skGATHERINFORMATION,		0 },
  { skHANDLEANIMAL,		0 },
  { skHEAL,		1 },
  { skHIDE,		0 },
  { skINTIMIDATE,		0 },
  { skJUMP,		0 },
  { skKNOWLEDGE_ARCANA,		1 },
  { skKNOWLEDGE_ARCHITECTUREANDENGINEERING,		0 },
  { skKNOWLEDGE_DUNGEONEERING,		0 },
  { skKNOWLEDGE_GEOGRAPHY,		0 },
  { skKNOWLEDGE_HISTORY,		1 },
  { skKNOWLEDGE_LOCAL,		0 },
  { skKNOWLEDGE_NATURE,		0 },
  { skKNOWLEDGE_NOBILITYANDROYALTY,		0 },
  { skKNOWLEDGE_RELIGION,		1 },
  { skKNOWLEDGE_THEPLANES,		1 },
  { skLISTEN,		0 },
  { skMOVESILENTLY,		0 },
  { skOPENLOCK,		0 },
  { skPERFORM_ACT,		0 },
  { skPERFORM_COMEDY,		0 },
  { skPERFORM_DANCE,		0 },
  { skPERFORM_KEYBOARDINSTRUMENTS,		0 },
  { skPERFORM_ORATORY,		0 },
  { skPERFORM_PERCUSSIONINSTRUMENTS,		0 },
  { skPERFORM_SING,		0 },
  { skPERFORM_STRINGINSTRUMENTS,		0 },
  { skPERFORM_WINDINSTRUMENTS,		0 },
  { skPROFESSION_HUNTER,		1 },
  { skPROFESSION_MINER,		1 },
  { skRIDE,		0 },
  { skSEARCH,		0 },
  { skSENSEMOTIVE,		0 },
  { skSLEIGHTOFHAND,		0 },
  { skSPEAKLANGUAGE,		0 },
  { skSPELLCRAFT,		1 },
  { skSPOT,		0 },
  { skSURVIVAL,		0 },
  { skSWIM,		0 },
  { skTUMBLE,		0 },
  { skUSEMAGICDEVICE,		0 },
  { skUSEROPE,		0 },
  { 0,		0 }
};

static SKILLSFORCLASS druidSkills[] = {
  { skAPPRAISE,		0 },
  { skBALANCE,		0 },
  { skBLUFF,		0 },
  { skCLIMB,		0 },
  { skCONCENTRATION,		1 },
  { skCRAFT_ALCHEMY,		1 },
  { skCRAFT_ARMORSMITHING,		1 },
  { skCRAFT_BLACKSMITHING,		1 },
  { skCRAFT_BOWMAKING,		1 },
  { skCRAFT_CARPENTRY,		1 },
  { skCRAFT_LEATHERWORKING,		1 },
  { skCRAFT_PAINTING,		1 },
  { skCRAFT_POTTERY,		1 },
  { skCRAFT_SCULPTING,		1 },
  { skCRAFT_SHIPMAKING,		1 },
  { skCRAFT_STONEMASONRY,		1 },
  { skCRAFT_TRAPMAKING,		1 },
  { skCRAFT_WEAPONSMITHING,		1 },
  { skCRAFT_WOODWORKING,		1 },
  { skDECIPHERSCRIPT,		0 },
  { skDIPLOMACY,		1 },
  { skDISABLEDEVICE,		0 },
  { skDISGUISE,		0 },
  { skESCAPEARTIST,		0 },
  { skFORGERY,		0 },
  { skGATHERINFORMATION,		0 },
  { skHANDLEANIMAL,		1 },
  { skHEAL,		1 },
  { skHIDE,		0 },
  { skINTIMIDATE,		0 },
  { skJUMP,		0 },
  { skKNOWLEDGE_ARCANA,		0 },
  { skKNOWLEDGE_ARCHITECTUREANDENGINEERING,		0 },
  { skKNOWLEDGE_DUNGEONEERING,		0 },
  { skKNOWLEDGE_GEOGRAPHY,		0 },
  { skKNOWLEDGE_HISTORY,		0 },
  { skKNOWLEDGE_LOCAL,		0 },
  { skKNOWLEDGE_NATURE,		1 },
  { skKNOWLEDGE_NOBILITYANDROYALTY,		0 },
  { skKNOWLEDGE_RELIGION,		0 },
  { skKNOWLEDGE_THEPLANES,		0 },
  { skLISTEN,		1 },
  { skMOVESILENTLY,		0 },
  { skOPENLOCK,		0 },
  { skPERFORM_ACT,		0 },
  { skPERFORM_COMEDY,		0 },
  { skPERFORM_DANCE,		0 },
  { skPERFORM_KEYBOARDINSTRUMENTS,		0 },
  { skPERFORM_ORATORY,		0 },
  { skPERFORM_PERCUSSIONINSTRUMENTS,		0 },
  { skPERFORM_SING,		0 },
  { skPERFORM_STRINGINSTRUMENTS,		0 },
  { skPERFORM_WINDINSTRUMENTS,		0 },
  { skPROFESSION_HUNTER,		1 },
  { skPROFESSION_MINER,		1 },
  { skRIDE,		1 },
  { skSEARCH,		0 },
  { skSENSEMOTIVE,		0 },
  { skSLEIGHTOFHAND,		0 },
  { skSPEAKLANGUAGE,		0 },
  { skSPELLCRAFT,		1 },
  { skSPOT,		1 },
  { skSURVIVAL,		1 },
  { skSWIM,		1 },
  { skTUMBLE,		0 },
  { skUSEMAGICDEVICE,		0 },
  { skUSEROPE,		0 },
  { 0,		0 }
};

static SKILLSFORCLASS fighterSkills[] = {
  { skAPPRAISE,		0 },
  { skBALANCE,		0 },
  { skBLUFF,		0 },
  { skCLIMB,		1 },
  { skCONCENTRATION,		0 },
  { skCRAFT_ALCHEMY,		1 },
  { skCRAFT_ARMORSMITHING,		1 },
  { skCRAFT_BLACKSMITHING,		1 },
  { skCRAFT_BOWMAKING,		1 },
  { skCRAFT_CARPENTRY,		1 },
  { skCRAFT_LEATHERWORKING,		1 },
  { skCRAFT_PAINTING,		1 },
  { skCRAFT_POTTERY,		1 },
  { skCRAFT_SCULPTING,		1 },
  { skCRAFT_SHIPMAKING,		1 },
  { skCRAFT_STONEMASONRY,		1 },
  { skCRAFT_TRAPMAKING,		1 },
  { skCRAFT_WEAPONSMITHING,		1 },
  { skCRAFT_WOODWORKING,		1 },
  { skDECIPHERSCRIPT,		0 },
  { skDIPLOMACY,		0 },
  { skDISABLEDEVICE,		0 },
  { skDISGUISE,		0 },
  { skESCAPEARTIST,		0 },
  { skFORGERY,		0 },
  { skGATHERINFORMATION,		0 },
  { skHANDLEANIMAL,		1 },
  { skHEAL,		0 },
  { skHIDE,		0 },
  { skINTIMIDATE,		1 },
  { skJUMP,		1 },
  { skKNOWLEDGE_ARCANA,		0 },
  { skKNOWLEDGE_ARCHITECTUREANDENGINEERING,		0 },
  { skKNOWLEDGE_DUNGEONEERING,		0 },
  { skKNOWLEDGE_GEOGRAPHY,		0 },
  { skKNOWLEDGE_HISTORY,		0 },
  { skKNOWLEDGE_LOCAL,		0 },
  { skKNOWLEDGE_NATURE,		0 },
  { skKNOWLEDGE_NOBILITYANDROYALTY,		0 },
  { skKNOWLEDGE_RELIGION,		0 },
  { skKNOWLEDGE_THEPLANES,		0 },
  { skLISTEN,		0 },
  { skMOVESILENTLY,		0 },
  { skOPENLOCK,		0 },
  { skPERFORM_ACT,		0 },
  { skPERFORM_COMEDY,		0 },
  { skPERFORM_DANCE,		0 },
  { skPERFORM_KEYBOARDINSTRUMENTS,		0 },
  { skPERFORM_ORATORY,		0 },
  { skPERFORM_PERCUSSIONINSTRUMENTS,		0 },
  { skPERFORM_SING,		0 },
  { skPERFORM_STRINGINSTRUMENTS,		0 },
  { skPERFORM_WINDINSTRUMENTS,		0 },
  { skPROFESSION_HUNTER,		0 },
  { skPROFESSION_MINER,		0 },
  { skRIDE,		1 },
  { skSEARCH,		0 },
  { skSENSEMOTIVE,		0 },
  { skSLEIGHTOFHAND,		0 },
  { skSPEAKLANGUAGE,		0 },
  { skSPELLCRAFT,		0 },
  { skSPOT,		0 },
  { skSURVIVAL,		0 },
  { skSWIM,		1 },
  { skTUMBLE,		0 },
  { skUSEMAGICDEVICE,		0 },
  { skUSEROPE,		0 },
  { 0,		0 }
};

static SKILLSFORCLASS monkSkills[] = {
  { skAPPRAISE,		0 },
  { skBALANCE,		1 },
  { skBLUFF,		0 },
  { skCLIMB,		1 },
  { skCONCENTRATION,		1 },
  { skCRAFT_ALCHEMY,		1 },
  { skCRAFT_ARMORSMITHING,		1 },
  { skCRAFT_BLACKSMITHING,		1 },
  { skCRAFT_BOWMAKING,		1 },
  { skCRAFT_CARPENTRY,		1 },
  { skCRAFT_LEATHERWORKING,		1 },
  { skCRAFT_PAINTING,		1 },
  { skCRAFT_POTTERY,		1 },
  { skCRAFT_SCULPTING,		1 },
  { skCRAFT_SHIPMAKING,		1 },
  { skCRAFT_STONEMASONRY,		1 },
  { skCRAFT_TRAPMAKING,		1 },
  { skCRAFT_WEAPONSMITHING,		1 },
  { skCRAFT_WOODWORKING,		1 },
  { skDECIPHERSCRIPT,		0 },
  { skDIPLOMACY,		1 },
  { skDISABLEDEVICE,		0 },
  { skDISGUISE,		0 },
  { skESCAPEARTIST,		1 },
  { skFORGERY,		0 },
  { skGATHERINFORMATION,		0 },
  { skHANDLEANIMAL,		0 },
  { skHEAL,		0 },
  { skHIDE,		1 },
  { skINTIMIDATE,		0 },
  { skJUMP,		1 },
  { skKNOWLEDGE_ARCANA,		1 },
  { skKNOWLEDGE_ARCHITECTUREANDENGINEERING,		0 },
  { skKNOWLEDGE_DUNGEONEERING,		0 },
  { skKNOWLEDGE_GEOGRAPHY,		0 },
  { skKNOWLEDGE_HISTORY,		0 },
  { skKNOWLEDGE_LOCAL,		0 },
  { skKNOWLEDGE_NATURE,		0 },
  { skKNOWLEDGE_NOBILITYANDROYALTY,		0 },
  { skKNOWLEDGE_RELIGION,		1 },
  { skKNOWLEDGE_THEPLANES,		0 },
  { skLISTEN,		1 },
  { skMOVESILENTLY,		1 },
  { skOPENLOCK,		0 },
  { skPERFORM_ACT,		1 },
  { skPERFORM_COMEDY,		1 },
  { skPERFORM_DANCE,		1 },
  { skPERFORM_KEYBOARDINSTRUMENTS,		1 },
  { skPERFORM_ORATORY,		1 },
  { skPERFORM_PERCUSSIONINSTRUMENTS,		1 },
  { skPERFORM_SING,		1 },
  { skPERFORM_STRINGINSTRUMENTS,		1 },
  { skPERFORM_WINDINSTRUMENTS,		1 },
  { skPROFESSION_HUNTER,		1 },
  { skPROFESSION_MINER,		1 },
  { skRIDE,		0 },
  { skSEARCH,		0 },
  { skSENSEMOTIVE,		1 },
  { skSLEIGHTOFHAND,		0 },
  { skSPEAKLANGUAGE,		0 },
  { skSPELLCRAFT,		0 },
  { skSPOT,		1 },
  { skSURVIVAL,		0 },
  { skSWIM,		1 },
  { skTUMBLE,		1 },
  { skUSEMAGICDEVICE,		0 },
  { skUSEROPE,		0 },
  { 0,		0 }
};

static SKILLSFORCLASS paladinSkills[] = {
  { skAPPRAISE,		0 },
  { skBALANCE,		0 },
  { skBLUFF,		0 },
  { skCLIMB,		0 },
  { skCONCENTRATION,		1 },
  { skCRAFT_ALCHEMY,		1 },
  { skCRAFT_ARMORSMITHING,		1 },
  { skCRAFT_BLACKSMITHING,		1 },
  { skCRAFT_BOWMAKING,		1 },
  { skCRAFT_CARPENTRY,		1 },
  { skCRAFT_LEATHERWORKING,		1 },
  { skCRAFT_PAINTING,		1 },
  { skCRAFT_POTTERY,		1 },
  { skCRAFT_SCULPTING,		1 },
  { skCRAFT_SHIPMAKING,		1 },
  { skCRAFT_STONEMASONRY,		1 },
  { skCRAFT_TRAPMAKING,		1 },
  { skCRAFT_WEAPONSMITHING,		1 },
  { skCRAFT_WOODWORKING,		1 },
  { skDECIPHERSCRIPT,		0 },
  { skDIPLOMACY,		1 },
  { skDISABLEDEVICE,		0 },
  { skDISGUISE,		0 },
  { skESCAPEARTIST,		0 },
  { skFORGERY,		0 },
  { skGATHERINFORMATION,		0 },
  { skHANDLEANIMAL,		1 },
  { skHEAL,		1 },
  { skHIDE,		0 },
  { skINTIMIDATE,		0 },
  { skJUMP,		0 },
  { skKNOWLEDGE_ARCANA,		0 },
  { skKNOWLEDGE_ARCHITECTUREANDENGINEERING,		0 },
  { skKNOWLEDGE_DUNGEONEERING,		0 },
  { skKNOWLEDGE_GEOGRAPHY,		0 },
  { skKNOWLEDGE_HISTORY,		0 },
  { skKNOWLEDGE_LOCAL,		0 },
  { skKNOWLEDGE_NATURE,		0 },
  { skKNOWLEDGE_NOBILITYANDROYALTY,		1 },
  { skKNOWLEDGE_RELIGION,		1 },
  { skKNOWLEDGE_THEPLANES,		0 },
  { skLISTEN,		0 },
  { skMOVESILENTLY,		0 },
  { skOPENLOCK,		0 },
  { skPERFORM_ACT,		0 },
  { skPERFORM_COMEDY,		0 },
  { skPERFORM_DANCE,		0 },
  { skPERFORM_KEYBOARDINSTRUMENTS,		0 },
  { skPERFORM_ORATORY,		0 },
  { skPERFORM_PERCUSSIONINSTRUMENTS,		0 },
  { skPERFORM_SING,		0 },
  { skPERFORM_STRINGINSTRUMENTS,		0 },
  { skPERFORM_WINDINSTRUMENTS,		0 },
  { skPROFESSION_HUNTER,		1 },
  { skPROFESSION_MINER,		1 },
  { skRIDE,		1 },
  { skSEARCH,		0 },
  { skSENSEMOTIVE,		1 },
  { skSLEIGHTOFHAND,		0 },
  { skSPEAKLANGUAGE,		0 },
  { skSPELLCRAFT,		0 },
  { skSPOT,		0 },
  { skSURVIVAL,		0 },
  { skSWIM,		0 },
  { skTUMBLE,		0 },
  { skUSEMAGICDEVICE,		0 },
  { skUSEROPE,		0 },
  { 0,		0 }
};

static SKILLSFORCLASS rangerSkills[] = {
  { skAPPRAISE,		0 },
  { skBALANCE,		0 },
  { skBLUFF,		0 },
  { skCLIMB,		1 },
  { skCONCENTRATION,		1 },
  { skCRAFT_ALCHEMY,		1 },
  { skCRAFT_ARMORSMITHING,		1 },
  { skCRAFT_BLACKSMITHING,		1 },
  { skCRAFT_BOWMAKING,		1 },
  { skCRAFT_CARPENTRY,		1 },
  { skCRAFT_LEATHERWORKING,		1 },
  { skCRAFT_PAINTING,		1 },
  { skCRAFT_POTTERY,		1 },
  { skCRAFT_SCULPTING,		1 },
  { skCRAFT_SHIPMAKING,		1 },
  { skCRAFT_STONEMASONRY,		1 },
  { skCRAFT_TRAPMAKING,		1 },
  { skCRAFT_WEAPONSMITHING,		1 },
  { skCRAFT_WOODWORKING,		1 },
  { skDECIPHERSCRIPT,		0 },
  { skDIPLOMACY,		0 },
  { skDISABLEDEVICE,		0 },
  { skDISGUISE,		0 },
  { skESCAPEARTIST,		0 },
  { skFORGERY,		0 },
  { skGATHERINFORMATION,		0 },
  { skHANDLEANIMAL,		1 },
  { skHEAL,		1 },
  { skHIDE,		1 },
  { skINTIMIDATE,		0 },
  { skJUMP,		1 },
  { skKNOWLEDGE_ARCANA,		0 },
  { skKNOWLEDGE_ARCHITECTUREANDENGINEERING,		0 },
  { skKNOWLEDGE_DUNGEONEERING,		1 },
  { skKNOWLEDGE_GEOGRAPHY,		1 },
  { skKNOWLEDGE_HISTORY,		0 },
  { skKNOWLEDGE_LOCAL,		0 },
  { skKNOWLEDGE_NATURE,		1 },
  { skKNOWLEDGE_NOBILITYANDROYALTY,		0 },
  { skKNOWLEDGE_RELIGION,		0 },
  { skKNOWLEDGE_THEPLANES,		0 },
  { skLISTEN,		1 },
  { skMOVESILENTLY,		1 },
  { skOPENLOCK,		0 },
  { skPERFORM_ACT,		0 },
  { skPERFORM_COMEDY,		0 },
  { skPERFORM_DANCE,		0 },
  { skPERFORM_KEYBOARDINSTRUMENTS,		0 },
  { skPERFORM_ORATORY,		0 },
  { skPERFORM_PERCUSSIONINSTRUMENTS,		0 },
  { skPERFORM_SING,		0 },
  { skPERFORM_STRINGINSTRUMENTS,		0 },
  { skPERFORM_WINDINSTRUMENTS,		0 },
  { skPROFESSION_HUNTER,		1 },
  { skPROFESSION_MINER,		1 },
  { skRIDE,		1 },
  { skSEARCH,		1 },
  { skSENSEMOTIVE,		0 },
  { skSLEIGHTOFHAND,		0 },
  { skSPEAKLANGUAGE,		0 },
  { skSPELLCRAFT,		0 },
  { skSPOT,		1 },
  { skSURVIVAL,		1 },
  { skSWIM,		1 },
  { skTUMBLE,		0 },
  { skUSEMAGICDEVICE,		0 },
  { skUSEROPE,		1 },
  { 0,		0 }
};

static SKILLSFORCLASS rogueSkills[] = {
  { skAPPRAISE,		1 },
  { skBALANCE,		1 },
  { skBLUFF,		1 },
  { skCLIMB,		1 },
  { skCONCENTRATION,		0 },
  { skCRAFT_ALCHEMY,		1 },
  { skCRAFT_ARMORSMITHING,		1 },
  { skCRAFT_BLACKSMITHING,		1 },
  { skCRAFT_BOWMAKING,		1 },
  { skCRAFT_CARPENTRY,		1 },
  { skCRAFT_LEATHERWORKING,		1 },
  { skCRAFT_PAINTING,		1 },
  { skCRAFT_POTTERY,		1 },
  { skCRAFT_SCULPTING,		1 },
  { skCRAFT_SHIPMAKING,		1 },
  { skCRAFT_STONEMASONRY,		1 },
  { skCRAFT_TRAPMAKING,		1 },
  { skCRAFT_WEAPONSMITHING,		1 },
  { skCRAFT_WOODWORKING,		1 },
  { skDECIPHERSCRIPT,		1 },
  { skDIPLOMACY,		1 },
  { skDISABLEDEVICE,		1 },
  { skDISGUISE,		1 },
  { skESCAPEARTIST,		1 },
  { skFORGERY,		1 },
  { skGATHERINFORMATION,		1 },
  { skHANDLEANIMAL,		0 },
  { skHEAL,		0 },
  { skHIDE,		1 },
  { skINTIMIDATE,		1 },
  { skJUMP,		1 },
  { skKNOWLEDGE_ARCANA,		0 },
  { skKNOWLEDGE_ARCHITECTUREANDENGINEERING,		0 },
  { skKNOWLEDGE_DUNGEONEERING,		0 },
  { skKNOWLEDGE_GEOGRAPHY,		0 },
  { skKNOWLEDGE_HISTORY,		0 },
  { skKNOWLEDGE_LOCAL,		1 },
  { skKNOWLEDGE_NATURE,		0 },
  { skKNOWLEDGE_NOBILITYANDROYALTY,		0 },
  { skKNOWLEDGE_RELIGION,		0 },
  { skKNOWLEDGE_THEPLANES,		0 },
  { skLISTEN,		1 },
  { skMOVESILENTLY,		1 },
  { skOPENLOCK,		1 },
  { skPERFORM_ACT,		1 },
  { skPERFORM_COMEDY,		1 },
  { skPERFORM_DANCE,		1 },
  { skPERFORM_KEYBOARDINSTRUMENTS,		1 },
  { skPERFORM_ORATORY,		1 },
  { skPERFORM_PERCUSSIONINSTRUMENTS,		1 },
  { skPERFORM_SING,		1 },
  { skPERFORM_STRINGINSTRUMENTS,		1 },
  { skPERFORM_WINDINSTRUMENTS,		1 },
  { skPROFESSION_HUNTER,		1 },
  { skPROFESSION_MINER,		1 },
  { skRIDE,		0 },
  { skSEARCH,		1 },
  { skSENSEMOTIVE,		1 },
  { skSLEIGHTOFHAND,		1 },
  { skSPEAKLANGUAGE,		0 },
  { skSPELLCRAFT,		0 },
  { skSPOT,		1 },
  { skSURVIVAL,		0 },
  { skSWIM,		1 },
  { skTUMBLE,		1 },
  { skUSEMAGICDEVICE,		1 },
  { skUSEROPE,		1 },
  { 0,		0 }
};

static SKILLSFORCLASS sorcererSkills[] = {
  { skAPPRAISE,		0 },
  { skBALANCE,		0 },
  { skBLUFF,		1 },
  { skCLIMB,		0 },
  { skCONCENTRATION,		1 },
  { skCRAFT_ALCHEMY,		1 },
  { skCRAFT_ARMORSMITHING,		1 },
  { skCRAFT_BLACKSMITHING,		1 },
  { skCRAFT_BOWMAKING,		1 },
  { skCRAFT_CARPENTRY,		1 },
  { skCRAFT_LEATHERWORKING,		1 },
  { skCRAFT_PAINTING,		1 },
  { skCRAFT_POTTERY,		1 },
  { skCRAFT_SCULPTING,		1 },
  { skCRAFT_SHIPMAKING,		1 },
  { skCRAFT_STONEMASONRY,		1 },
  { skCRAFT_TRAPMAKING,		1 },
  { skCRAFT_WEAPONSMITHING,		1 },
  { skCRAFT_WOODWORKING,		1 },
  { skDECIPHERSCRIPT,		0 },
  { skDIPLOMACY,		0 },
  { skDISABLEDEVICE,		0 },
  { skDISGUISE,		0 },
  { skESCAPEARTIST,		0 },
  { skFORGERY,		0 },
  { skGATHERINFORMATION,		0 },
  { skHANDLEANIMAL,		0 },
  { skHEAL,		0 },
  { skHIDE,		0 },
  { skINTIMIDATE,		0 },
  { skJUMP,		0 },
  { skKNOWLEDGE_ARCANA,		1 },
  { skKNOWLEDGE_ARCHITECTUREANDENGINEERING,		0 },
  { skKNOWLEDGE_DUNGEONEERING,		0 },
  { skKNOWLEDGE_GEOGRAPHY,		0 },
  { skKNOWLEDGE_HISTORY,		0 },
  { skKNOWLEDGE_LOCAL,		0 },
  { skKNOWLEDGE_NATURE,		0 },
  { skKNOWLEDGE_NOBILITYANDROYALTY,		0 },
  { skKNOWLEDGE_RELIGION,		0 },
  { skKNOWLEDGE_THEPLANES,		0 },
  { skLISTEN,		0 },
  { skMOVESILENTLY,		0 },
  { skOPENLOCK,		0 },
  { skPERFORM_ACT,		0 },
  { skPERFORM_COMEDY,		0 },
  { skPERFORM_DANCE,		0 },
  { skPERFORM_KEYBOARDINSTRUMENTS,		0 },
  { skPERFORM_ORATORY,		0 },
  { skPERFORM_PERCUSSIONINSTRUMENTS,		0 },
  { skPERFORM_SING,		0 },
  { skPERFORM_STRINGINSTRUMENTS,		0 },
  { skPERFORM_WINDINSTRUMENTS,		0 },
  { skPROFESSION_HUNTER,		1 },
  { skPROFESSION_MINER,		1 },
  { skRIDE,		0 },
  { skSEARCH,		0 },
  { skSENSEMOTIVE,		0 },
  { skSLEIGHTOFHAND,		0 },
  { skSPEAKLANGUAGE,		0 },
  { skSPELLCRAFT,		1 },
  { skSPOT,		0 },
  { skSURVIVAL,		0 },
  { skSWIM,		0 },
  { skTUMBLE,		0 },
  { skUSEMAGICDEVICE,		0 },
  { skUSEROPE,		0 },
  { 0,		0 }
};

static SKILLSFORCLASS wizardSkills[] = {
  { skAPPRAISE,		0 },
  { skBALANCE,		0 },
  { skBLUFF,		0 },
  { skCLIMB,		0 },
  { skCONCENTRATION,		1 },
  { skCRAFT_ALCHEMY,		1 },
  { skCRAFT_ARMORSMITHING,		1 },
  { skCRAFT_BLACKSMITHING,		1 },
  { skCRAFT_BOWMAKING,		1 },
  { skCRAFT_CARPENTRY,		1 },
  { skCRAFT_LEATHERWORKING,		1 },
  { skCRAFT_PAINTING,		1 },
  { skCRAFT_POTTERY,		1 },
  { skCRAFT_SCULPTING,		1 },
  { skCRAFT_SHIPMAKING,		1 },
  { skCRAFT_STONEMASONRY,		1 },
  { skCRAFT_TRAPMAKING,		1 },
  { skCRAFT_WEAPONSMITHING,		1 },
  { skCRAFT_WOODWORKING,		1 },
  { skDECIPHERSCRIPT,		1 },
  { skDIPLOMACY,		0 },
  { skDISABLEDEVICE,		0 },
  { skDISGUISE,		0 },
  { skESCAPEARTIST,		0 },
  { skFORGERY,		0 },
  { skGATHERINFORMATION,		0 },
  { skHANDLEANIMAL,		0 },
  { skHEAL,		0 },
  { skHIDE,		0 },
  { skINTIMIDATE,		0 },
  { skJUMP,		0 },
  { skKNOWLEDGE_ARCANA,		1 },
  { skKNOWLEDGE_ARCHITECTUREANDENGINEERING,		1 },
  { skKNOWLEDGE_DUNGEONEERING,		1 },
  { skKNOWLEDGE_GEOGRAPHY,		1 },
  { skKNOWLEDGE_HISTORY,		1 },
  { skKNOWLEDGE_LOCAL,		1 },
  { skKNOWLEDGE_NATURE,		1 },
  { skKNOWLEDGE_NOBILITYANDROYALTY,		1 },
  { skKNOWLEDGE_RELIGION,		1 },
  { skKNOWLEDGE_THEPLANES,		1 },
  { skLISTEN,		0 },
  { skMOVESILENTLY,		0 },
  { skOPENLOCK,		0 },
  { skPERFORM_ACT,		0 },
  { skPERFORM_COMEDY,		0 },
  { skPERFORM_DANCE,		0 },
  { skPERFORM_KEYBOARDINSTRUMENTS,		0 },
  { skPERFORM_ORATORY,		0 },
  { skPERFORM_PERCUSSIONINSTRUMENTS,		0 },
  { skPERFORM_SING,		0 },
  { skPERFORM_STRINGINSTRUMENTS,		0 },
  { skPERFORM_WINDINSTRUMENTS,		0 },
  { skPROFESSION_HUNTER,		1 },
  { skPROFESSION_MINER,		1 },
  { skRIDE,		0 },
  { skSEARCH,		0 },
  { skSENSEMOTIVE,		0 },
  { skSLEIGHTOFHAND,		0 },
  { skSPEAKLANGUAGE,		0 },
  { skSPELLCRAFT,		1 },
  { skSPOT,		0 },
  { skSURVIVAL,		0 },
  { skSWIM,		0 },
  { skTUMBLE,		0 },
  { skUSEMAGICDEVICE,		0 },
  { skUSEROPE,		0 },
  { 0,		0 }
};




static SKILLSFORCLASS arcaneArcherSkills[] = {
  { skAPPRAISE,		0 },
  { skBALANCE,		0 },
  { skBLUFF,		0 },
  { skCLIMB,		0 },
  { skCONCENTRATION,		0 },
  { skCRAFT_ALCHEMY,		1 },
  { skCRAFT_ARMORSMITHING,		1 },
  { skCRAFT_BLACKSMITHING,		1 },
  { skCRAFT_BOWMAKING,		1 },
  { skCRAFT_CARPENTRY,		1 },
  { skCRAFT_LEATHERWORKING,		1 },
  { skCRAFT_PAINTING,		1 },
  { skCRAFT_POTTERY,		1 },
  { skCRAFT_SCULPTING,		1 },
  { skCRAFT_SHIPMAKING,		1 },
  { skCRAFT_STONEMASONRY,		1 },
  { skCRAFT_TRAPMAKING,		1 },
  { skCRAFT_WEAPONSMITHING,		1 },
  { skCRAFT_WOODWORKING,		1 },
  { skDECIPHERSCRIPT,		0 },
  { skDIPLOMACY,		0 },
  { skDISABLEDEVICE,		0 },
  { skDISGUISE,		0 },
  { skESCAPEARTIST,		0 },
  { skFORGERY,		0 },
  { skGATHERINFORMATION,		0 },
  { skHANDLEANIMAL,		0 },
  { skHEAL,		0 },
  { skHIDE,		1 },
  { skINTIMIDATE,		0 },
  { skJUMP,		0 },
  { skKNOWLEDGE_ARCANA,		0 },
  { skKNOWLEDGE_ARCHITECTUREANDENGINEERING,		0 },
  { skKNOWLEDGE_DUNGEONEERING,		0 },
  { skKNOWLEDGE_GEOGRAPHY,		0 },
  { skKNOWLEDGE_HISTORY,		0 },
  { skKNOWLEDGE_LOCAL,		0 },
  { skKNOWLEDGE_NATURE,		0 },
  { skKNOWLEDGE_NOBILITYANDROYALTY,		0 },
  { skKNOWLEDGE_RELIGION,		0 },
  { skKNOWLEDGE_THEPLANES,		0 },
  { skLISTEN,		1 },
  { skMOVESILENTLY,		1 },
  { skOPENLOCK,		0 },
  { skPERFORM_ACT,		0 },
  { skPERFORM_COMEDY,		0 },
  { skPERFORM_DANCE,		0 },
  { skPERFORM_KEYBOARDINSTRUMENTS,		0 },
  { skPERFORM_ORATORY,		0 },
  { skPERFORM_PERCUSSIONINSTRUMENTS,		0 },
  { skPERFORM_SING,		0 },
  { skPERFORM_STRINGINSTRUMENTS,		0 },
  { skPERFORM_WINDINSTRUMENTS,		0 },
  { skPROFESSION_HUNTER,		0 },
  { skPROFESSION_MINER,		0 },
  { skRIDE,		1 },
  { skSEARCH,		0 },
  { skSENSEMOTIVE,		0 },
  { skSLEIGHTOFHAND,		0 },
  { skSPEAKLANGUAGE,		0 },
  { skSPELLCRAFT,		0 },
  { skSPOT,		1 },
  { skSURVIVAL,		1 },
  { skSWIM,		0 },
  { skTUMBLE,		0 },
  { skUSEMAGICDEVICE,		0 },
  { skUSEROPE,		0 },
  { 0,		0 }
};

static SKILLSFORCLASS arcaneTricksterSkills[] = {
  { skAPPRAISE,		1 },
  { skBALANCE,		1 },
  { skBLUFF,		1 },
  { skCLIMB,		1 },
  { skCONCENTRATION,		1 },
  { skCRAFT_ALCHEMY,		1 },
  { skCRAFT_ARMORSMITHING,		1 },
  { skCRAFT_BLACKSMITHING,		1 },
  { skCRAFT_BOWMAKING,		1 },
  { skCRAFT_CARPENTRY,		1 },
  { skCRAFT_LEATHERWORKING,		1 },
  { skCRAFT_PAINTING,		1 },
  { skCRAFT_POTTERY,		1 },
  { skCRAFT_SCULPTING,		1 },
  { skCRAFT_SHIPMAKING,		1 },
  { skCRAFT_STONEMASONRY,		1 },
  { skCRAFT_TRAPMAKING,		1 },
  { skCRAFT_WEAPONSMITHING,		1 },
  { skCRAFT_WOODWORKING,		1 },
  { skDECIPHERSCRIPT,		1 },
  { skDIPLOMACY,		1 },
  { skDISABLEDEVICE,		1 },
  { skDISGUISE,		1 },
  { skESCAPEARTIST,		1 },
  { skFORGERY,		0 },
  { skGATHERINFORMATION,		1 },
  { skHANDLEANIMAL,		0 },
  { skHEAL,		0 },
  { skHIDE,		1 },
  { skINTIMIDATE,		0 },
  { skJUMP,		1 },
  { skKNOWLEDGE_ARCANA,		1 },
  { skKNOWLEDGE_ARCHITECTUREANDENGINEERING,		1 },
  { skKNOWLEDGE_DUNGEONEERING,		1 },
  { skKNOWLEDGE_GEOGRAPHY,		1 },
  { skKNOWLEDGE_HISTORY,		1 },
  { skKNOWLEDGE_LOCAL,		1 },
  { skKNOWLEDGE_NATURE,		1 },
  { skKNOWLEDGE_NOBILITYANDROYALTY,		1 },
  { skKNOWLEDGE_RELIGION,		1 },
  { skKNOWLEDGE_THEPLANES,		1 },
  { skLISTEN,		1 },
  { skMOVESILENTLY,		1 },
  { skOPENLOCK,		1 },
  { skPERFORM_ACT,		0 },
  { skPERFORM_COMEDY,		0 },
  { skPERFORM_DANCE,		0 },
  { skPERFORM_KEYBOARDINSTRUMENTS,		0 },
  { skPERFORM_ORATORY,		0 },
  { skPERFORM_PERCUSSIONINSTRUMENTS,		0 },
  { skPERFORM_SING,		0 },
  { skPERFORM_STRINGINSTRUMENTS,		0 },
  { skPERFORM_WINDINSTRUMENTS,		0 },
  { skPROFESSION_HUNTER,		1 },
  { skPROFESSION_MINER,		1 },
  { skRIDE,		0 },
  { skSEARCH,		1 },
  { skSENSEMOTIVE,		1 },
  { skSLEIGHTOFHAND,		1 },
  { skSPEAKLANGUAGE,		1 },
  { skSPELLCRAFT,		1 },
  { skSPOT,		1 },
  { skSURVIVAL,		0 },
  { skSWIM,		1 },
  { skTUMBLE,		1 },
  { skUSEMAGICDEVICE,		0 },
  { skUSEROPE,		0 },
  { 0,		0 }
};

static SKILLSFORCLASS archmageSkills[] = {
  { skAPPRAISE,		0 },
  { skBALANCE,		0 },
  { skBLUFF,		0 },
  { skCLIMB,		0 },
  { skCONCENTRATION,		1 },
  { skCRAFT_ALCHEMY,		1 },
  { skCRAFT_ARMORSMITHING,		0 },
  { skCRAFT_BLACKSMITHING,		0 },
  { skCRAFT_BOWMAKING,		0 },
  { skCRAFT_CARPENTRY,		0 },
  { skCRAFT_LEATHERWORKING,		0 },
  { skCRAFT_PAINTING,		0 },
  { skCRAFT_POTTERY,		0 },
  { skCRAFT_SCULPTING,		0 },
  { skCRAFT_SHIPMAKING,		0 },
  { skCRAFT_STONEMASONRY,		0 },
  { skCRAFT_TRAPMAKING,		0 },
  { skCRAFT_WEAPONSMITHING,		0 },
  { skCRAFT_WOODWORKING,		0 },
  { skDECIPHERSCRIPT,		0 },
  { skDIPLOMACY,		0 },
  { skDISABLEDEVICE,		0 },
  { skDISGUISE,		0 },
  { skESCAPEARTIST,		0 },
  { skFORGERY,		0 },
  { skGATHERINFORMATION,		0 },
  { skHANDLEANIMAL,		0 },
  { skHEAL,		0 },
  { skHIDE,		0 },
  { skINTIMIDATE,		0 },
  { skJUMP,		0 },
  { skKNOWLEDGE_ARCANA,		1 },
  { skKNOWLEDGE_ARCHITECTUREANDENGINEERING,		1 },
  { skKNOWLEDGE_DUNGEONEERING,		1 },
  { skKNOWLEDGE_GEOGRAPHY,		1 },
  { skKNOWLEDGE_HISTORY,		1 },
  { skKNOWLEDGE_LOCAL,		1 },
  { skKNOWLEDGE_NATURE,		1 },
  { skKNOWLEDGE_NOBILITYANDROYALTY,		1 },
  { skKNOWLEDGE_RELIGION,		1 },
  { skKNOWLEDGE_THEPLANES,		1 },
  { skLISTEN,		0 },
  { skMOVESILENTLY,		0 },
  { skOPENLOCK,		0 },
  { skPERFORM_ACT,		0 },
  { skPERFORM_COMEDY,		0 },
  { skPERFORM_DANCE,		0 },
  { skPERFORM_KEYBOARDINSTRUMENTS,		0 },
  { skPERFORM_ORATORY,		0 },
  { skPERFORM_PERCUSSIONINSTRUMENTS,		0 },
  { skPERFORM_SING,		0 },
  { skPERFORM_STRINGINSTRUMENTS,		0 },
  { skPERFORM_WINDINSTRUMENTS,		0 },
  { skPROFESSION_HUNTER,		1 },
  { skPROFESSION_MINER,		1 },
  { skRIDE,		0 },
  { skSEARCH,		1 },
  { skSENSEMOTIVE,		0 },
  { skSLEIGHTOFHAND,		0 },
  { skSPEAKLANGUAGE,		0 },
  { skSPELLCRAFT,		0 },
  { skSPOT,		0 },
  { skSURVIVAL,		0 },
  { skSWIM,		0 },
  { skTUMBLE,		0 },
  { skUSEMAGICDEVICE,		0 },
  { skUSEROPE,		0 },
  { 0,		0 }
};

static SKILLSFORCLASS assassinSkills[] = {
  { skAPPRAISE,		0 },
  { skBALANCE,		1 },
  { skBLUFF,		1 },
  { skCLIMB,		1 },
  { skCONCENTRATION,		0 },
  { skCRAFT_ALCHEMY,		1 },
  { skCRAFT_ARMORSMITHING,		1 },
  { skCRAFT_BLACKSMITHING,		1 },
  { skCRAFT_BOWMAKING,		1 },
  { skCRAFT_CARPENTRY,		1 },
  { skCRAFT_LEATHERWORKING,		1 },
  { skCRAFT_PAINTING,		1 },
  { skCRAFT_POTTERY,		1 },
  { skCRAFT_SCULPTING,		1 },
  { skCRAFT_SHIPMAKING,		1 },
  { skCRAFT_STONEMASONRY,		1 },
  { skCRAFT_TRAPMAKING,		1 },
  { skCRAFT_WEAPONSMITHING,		1 },
  { skCRAFT_WOODWORKING,		1 },
  { skDECIPHERSCRIPT,		1 },
  { skDIPLOMACY,		1 },
  { skDISABLEDEVICE,		1 },
  { skDISGUISE,		1 },
  { skESCAPEARTIST,		1 },
  { skFORGERY,		1 },
  { skGATHERINFORMATION,		1 },
  { skHANDLEANIMAL,		0 },
  { skHEAL,		0 },
  { skHIDE,		1 },
  { skINTIMIDATE,		1 },
  { skJUMP,		1 },
  { skKNOWLEDGE_ARCANA,		0 },
  { skKNOWLEDGE_ARCHITECTUREANDENGINEERING,		0 },
  { skKNOWLEDGE_DUNGEONEERING,		0 },
  { skKNOWLEDGE_GEOGRAPHY,		0 },
  { skKNOWLEDGE_HISTORY,		0 },
  { skKNOWLEDGE_LOCAL,		0 },
  { skKNOWLEDGE_NATURE,		0 },
  { skKNOWLEDGE_NOBILITYANDROYALTY,		0 },
  { skKNOWLEDGE_RELIGION,		0 },
  { skKNOWLEDGE_THEPLANES,		0 },
  { skLISTEN,		1 },
  { skMOVESILENTLY,		1 },
  { skOPENLOCK,		1 },
  { skPERFORM_ACT,		0 },
  { skPERFORM_COMEDY,		0 },
  { skPERFORM_DANCE,		0 },
  { skPERFORM_KEYBOARDINSTRUMENTS,		0 },
  { skPERFORM_ORATORY,		0 },
  { skPERFORM_PERCUSSIONINSTRUMENTS,		0 },
  { skPERFORM_SING,		0 },
  { skPERFORM_STRINGINSTRUMENTS,		0 },
  { skPERFORM_WINDINSTRUMENTS,		0 },
  { skPROFESSION_HUNTER,		0 },
  { skPROFESSION_MINER,		0 },
  { skRIDE,		0 },
  { skSEARCH,		1 },
  { skSENSEMOTIVE,		1 },
  { skSLEIGHTOFHAND,		1 },
  { skSPEAKLANGUAGE,		0 },
  { skSPELLCRAFT,		0 },
  { skSPOT,		1 },
  { skSURVIVAL,		0 },
  { skSWIM,		1 },
  { skTUMBLE,		1 },
  { skUSEMAGICDEVICE,		1 },
  { skUSEROPE,		0 },
  { 0,		0 }
};

static SKILLSFORCLASS blackguardSkills[] = {
  { skAPPRAISE,		0 },
  { skBALANCE,		0 },
  { skBLUFF,		0 },
  { skCLIMB,		0 },
  { skCONCENTRATION,		1 },
  { skCRAFT_ALCHEMY,		1 },
  { skCRAFT_ARMORSMITHING,		1 },
  { skCRAFT_BLACKSMITHING,		1 },
  { skCRAFT_BOWMAKING,		1 },
  { skCRAFT_CARPENTRY,		1 },
  { skCRAFT_LEATHERWORKING,		1 },
  { skCRAFT_PAINTING,		1 },
  { skCRAFT_POTTERY,		1 },
  { skCRAFT_SCULPTING,		1 },
  { skCRAFT_SHIPMAKING,		1 },
  { skCRAFT_STONEMASONRY,		1 },
  { skCRAFT_TRAPMAKING,		1 },
  { skCRAFT_WEAPONSMITHING,		1 },
  { skCRAFT_WOODWORKING,		1 },
  { skDECIPHERSCRIPT,		0 },
  { skDIPLOMACY,		1 },
  { skDISABLEDEVICE,		0 },
  { skDISGUISE,		0 },
  { skESCAPEARTIST,		0 },
  { skFORGERY,		0 },
  { skGATHERINFORMATION,		0 },
  { skHANDLEANIMAL,		1 },
  { skHEAL,		1 },
  { skHIDE,		1 },
  { skINTIMIDATE,		1 },
  { skJUMP,		0 },
  { skKNOWLEDGE_ARCANA,		0 },
  { skKNOWLEDGE_ARCHITECTUREANDENGINEERING,		0 },
  { skKNOWLEDGE_DUNGEONEERING,		0 },
  { skKNOWLEDGE_GEOGRAPHY,		0 },
  { skKNOWLEDGE_HISTORY,		0 },
  { skKNOWLEDGE_LOCAL,		0 },
  { skKNOWLEDGE_NATURE,		0 },
  { skKNOWLEDGE_NOBILITYANDROYALTY,		0 },
  { skKNOWLEDGE_RELIGION,		1 },
  { skKNOWLEDGE_THEPLANES,		0 },
  { skLISTEN,		0 },
  { skMOVESILENTLY,		0 },
  { skOPENLOCK,		0 },
  { skPERFORM_ACT,		0 },
  { skPERFORM_COMEDY,		0 },
  { skPERFORM_DANCE,		0 },
  { skPERFORM_KEYBOARDINSTRUMENTS,		0 },
  { skPERFORM_ORATORY,		0 },
  { skPERFORM_PERCUSSIONINSTRUMENTS,		0 },
  { skPERFORM_SING,		0 },
  { skPERFORM_STRINGINSTRUMENTS,		0 },
  { skPERFORM_WINDINSTRUMENTS,		0 },
  { skPROFESSION_HUNTER,		1 },
  { skPROFESSION_MINER,		1 },
  { skRIDE,		0 },
  { skSEARCH,		0 },
  { skSENSEMOTIVE,		0 },
  { skSLEIGHTOFHAND,		0 },
  { skSPEAKLANGUAGE,		0 },
  { skSPELLCRAFT,		0 },
  { skSPOT,		0 },
  { skSURVIVAL,		0 },
  { skSWIM,		0 },
  { skTUMBLE,		0 },
  { skUSEMAGICDEVICE,		0 },
  { skUSEROPE,		0 },
  { 0,		0 }
};

static SKILLSFORCLASS dragonDiscipleSkills[] = {
  { skAPPRAISE,		0 },
  { skBALANCE,		0 },
  { skBLUFF,		0 },
  { skCLIMB,		0 },
  { skCONCENTRATION,		1 },
  { skCRAFT_ALCHEMY,		1 },
  { skCRAFT_ARMORSMITHING,		1 },
  { skCRAFT_BLACKSMITHING,		1 },
  { skCRAFT_BOWMAKING,		1 },
  { skCRAFT_CARPENTRY,		1 },
  { skCRAFT_LEATHERWORKING,		1 },
  { skCRAFT_PAINTING,		1 },
  { skCRAFT_POTTERY,		1 },
  { skCRAFT_SCULPTING,		1 },
  { skCRAFT_SHIPMAKING,		1 },
  { skCRAFT_STONEMASONRY,		1 },
  { skCRAFT_TRAPMAKING,		1 },
  { skCRAFT_WEAPONSMITHING,		1 },
  { skCRAFT_WOODWORKING,		1 },
  { skDECIPHERSCRIPT,		0 },
  { skDIPLOMACY,		1 },
  { skDISABLEDEVICE,		0 },
  { skDISGUISE,		0 },
  { skESCAPEARTIST,		1 },
  { skFORGERY,		0 },
  { skGATHERINFORMATION,		1 },
  { skHANDLEANIMAL,		0 },
  { skHEAL,		0 },
  { skHIDE,		0 },
  { skINTIMIDATE,		0 },
  { skJUMP,		0 },
  { skKNOWLEDGE_ARCANA,		1 },
  { skKNOWLEDGE_ARCHITECTUREANDENGINEERING,		1 },
  { skKNOWLEDGE_DUNGEONEERING,		1 },
  { skKNOWLEDGE_GEOGRAPHY,		1 },
  { skKNOWLEDGE_HISTORY,		1 },
  { skKNOWLEDGE_LOCAL,		1 },
  { skKNOWLEDGE_NATURE,		1 },
  { skKNOWLEDGE_NOBILITYANDROYALTY,		1 },
  { skKNOWLEDGE_RELIGION,		1 },
  { skKNOWLEDGE_THEPLANES,		1 },
  { skLISTEN,		1 },
  { skMOVESILENTLY,		0 },
  { skOPENLOCK,		0 },
  { skPERFORM_ACT,		0 },
  { skPERFORM_COMEDY,		0 },
  { skPERFORM_DANCE,		0 },
  { skPERFORM_KEYBOARDINSTRUMENTS,		0 },
  { skPERFORM_ORATORY,		0 },
  { skPERFORM_PERCUSSIONINSTRUMENTS,		0 },
  { skPERFORM_SING,		0 },
  { skPERFORM_STRINGINSTRUMENTS,		0 },
  { skPERFORM_WINDINSTRUMENTS,		0 },
  { skPROFESSION_HUNTER,		1 },
  { skPROFESSION_MINER,		1 },
  { skRIDE,		0 },
  { skSEARCH,		1 },
  { skSENSEMOTIVE,		0 },
  { skSLEIGHTOFHAND,		0 },
  { skSPEAKLANGUAGE,		1 },
  { skSPELLCRAFT,		1 },
  { skSPOT,		0 },
  { skSURVIVAL,		0 },
  { skSWIM,		0 },
  { skTUMBLE,		0 },
  { skUSEMAGICDEVICE,		0 },
  { skUSEROPE,		0 },
  { 0,		0 }
};

static SKILLSFORCLASS duelistSkills[] = {
  { skAPPRAISE,		0 },
  { skBALANCE,		1 },
  { skBLUFF,		1 },
  { skCLIMB,		0 },
  { skCONCENTRATION,		0 },
  { skCRAFT_ALCHEMY,		0 },
  { skCRAFT_ARMORSMITHING,		0 },
  { skCRAFT_BLACKSMITHING,		0 },
  { skCRAFT_BOWMAKING,		0 },
  { skCRAFT_CARPENTRY,		0 },
  { skCRAFT_LEATHERWORKING,		0 },
  { skCRAFT_PAINTING,		0 },
  { skCRAFT_POTTERY,		0 },
  { skCRAFT_SCULPTING,		0 },
  { skCRAFT_SHIPMAKING,		0 },
  { skCRAFT_STONEMASONRY,		0 },
  { skCRAFT_TRAPMAKING,		0 },
  { skCRAFT_WEAPONSMITHING,		0 },
  { skCRAFT_WOODWORKING,		0 },
  { skDECIPHERSCRIPT,		0 },
  { skDIPLOMACY,		0 },
  { skDISABLEDEVICE,		0 },
  { skDISGUISE,		0 },
  { skESCAPEARTIST,		1 },
  { skFORGERY,		0 },
  { skGATHERINFORMATION,		0 },
  { skHANDLEANIMAL,		0 },
  { skHEAL,		0 },
  { skHIDE,		0 },
  { skINTIMIDATE,		0 },
  { skJUMP,		1 },
  { skKNOWLEDGE_ARCANA,		0 },
  { skKNOWLEDGE_ARCHITECTUREANDENGINEERING,		0 },
  { skKNOWLEDGE_DUNGEONEERING,		0 },
  { skKNOWLEDGE_GEOGRAPHY,		0 },
  { skKNOWLEDGE_HISTORY,		0 },
  { skKNOWLEDGE_LOCAL,		0 },
  { skKNOWLEDGE_NATURE,		0 },
  { skKNOWLEDGE_NOBILITYANDROYALTY,		0 },
  { skKNOWLEDGE_RELIGION,		0 },
  { skKNOWLEDGE_THEPLANES,		0 },
  { skLISTEN,		1 },
  { skMOVESILENTLY,		0 },
  { skOPENLOCK,		0 },
  { skPERFORM_ACT,		1 },
  { skPERFORM_COMEDY,		1 },
  { skPERFORM_DANCE,		1 },
  { skPERFORM_KEYBOARDINSTRUMENTS,		1 },
  { skPERFORM_ORATORY,		1 },
  { skPERFORM_PERCUSSIONINSTRUMENTS,		1 },
  { skPERFORM_SING,		1 },
  { skPERFORM_STRINGINSTRUMENTS,		1 },
  { skPERFORM_WINDINSTRUMENTS,		1 },
  { skPROFESSION_HUNTER,		0 },
  { skPROFESSION_MINER,		0 },
  { skRIDE,		0 },
  { skSEARCH,		0 },
  { skSENSEMOTIVE,		1 },
  { skSLEIGHTOFHAND,		0 },
  { skSPEAKLANGUAGE,		0 },
  { skSPELLCRAFT,		0 },
  { skSPOT,		1 },
  { skSURVIVAL,		0 },
  { skSWIM,		0 },
  { skTUMBLE,		0 },
  { skUSEMAGICDEVICE,		0 },
  { skUSEROPE,		0 },
  { 0,		0 }
};

static SKILLSFORCLASS dwarvenDefenderSkills[] = {
  { skAPPRAISE,		0 },
  { skBALANCE,		0 },
  { skBLUFF,		0 },
  { skCLIMB,		0 },
  { skCONCENTRATION,		0 },
  { skCRAFT_ALCHEMY,		1 },
  { skCRAFT_ARMORSMITHING,		1 },
  { skCRAFT_BLACKSMITHING,		1 },
  { skCRAFT_BOWMAKING,		1 },
  { skCRAFT_CARPENTRY,		1 },
  { skCRAFT_LEATHERWORKING,		1 },
  { skCRAFT_PAINTING,		1 },
  { skCRAFT_POTTERY,		1 },
  { skCRAFT_SCULPTING,		1 },
  { skCRAFT_SHIPMAKING,		1 },
  { skCRAFT_STONEMASONRY,		1 },
  { skCRAFT_TRAPMAKING,		1 },
  { skCRAFT_WEAPONSMITHING,		1 },
  { skCRAFT_WOODWORKING,		1 },
  { skDECIPHERSCRIPT,		0 },
  { skDIPLOMACY,		0 },
  { skDISABLEDEVICE,		0 },
  { skDISGUISE,		0 },
  { skESCAPEARTIST,		0 },
  { skFORGERY,		0 },
  { skGATHERINFORMATION,		0 },
  { skHANDLEANIMAL,		0 },
  { skHEAL,		0 },
  { skHIDE,		0 },
  { skINTIMIDATE,		0 },
  { skJUMP,		0 },
  { skKNOWLEDGE_ARCANA,		0 },
  { skKNOWLEDGE_ARCHITECTUREANDENGINEERING,		0 },
  { skKNOWLEDGE_DUNGEONEERING,		0 },
  { skKNOWLEDGE_GEOGRAPHY,		0 },
  { skKNOWLEDGE_HISTORY,		0 },
  { skKNOWLEDGE_LOCAL,		0 },
  { skKNOWLEDGE_NATURE,		0 },
  { skKNOWLEDGE_NOBILITYANDROYALTY,		0 },
  { skKNOWLEDGE_RELIGION,		0 },
  { skKNOWLEDGE_THEPLANES,		0 },
  { skLISTEN,		1 },
  { skMOVESILENTLY,		0 },
  { skOPENLOCK,		0 },
  { skPERFORM_ACT,		0 },
  { skPERFORM_COMEDY,		0 },
  { skPERFORM_DANCE,		0 },
  { skPERFORM_KEYBOARDINSTRUMENTS,		0 },
  { skPERFORM_ORATORY,		0 },
  { skPERFORM_PERCUSSIONINSTRUMENTS,		0 },
  { skPERFORM_SING,		0 },
  { skPERFORM_STRINGINSTRUMENTS,		0 },
  { skPERFORM_WINDINSTRUMENTS,		0 },
  { skPROFESSION_HUNTER,		0 },
  { skPROFESSION_MINER,		0 },
  { skRIDE,		0 },
  { skSEARCH,		0 },
  { skSENSEMOTIVE,		1 },
  { skSLEIGHTOFHAND,		0 },
  { skSPEAKLANGUAGE,		0 },
  { skSPELLCRAFT,		0 },
  { skSPOT,		0 },
  { skSURVIVAL,		0 },
  { skSWIM,		0 },
  { skTUMBLE,		0 },
  { skUSEMAGICDEVICE,		0 },
  { skUSEROPE,		0 },
  { 0,		0 }
};

static SKILLSFORCLASS eldritchKnightSkills[] = {
  { skAPPRAISE,		0 },
  { skBALANCE,		0 },
  { skBLUFF,		0 },
  { skCLIMB,		0 },
  { skCONCENTRATION,		1 },
  { skCRAFT_ALCHEMY,		1 },
  { skCRAFT_ARMORSMITHING,		1 },
  { skCRAFT_BLACKSMITHING,		1 },
  { skCRAFT_BOWMAKING,		1 },
  { skCRAFT_CARPENTRY,		1 },
  { skCRAFT_LEATHERWORKING,		1 },
  { skCRAFT_PAINTING,		1 },
  { skCRAFT_POTTERY,		1 },
  { skCRAFT_SCULPTING,		1 },
  { skCRAFT_SHIPMAKING,		1 },
  { skCRAFT_STONEMASONRY,		1 },
  { skCRAFT_TRAPMAKING,		1 },
  { skCRAFT_WEAPONSMITHING,		1 },
  { skCRAFT_WOODWORKING,		1 },
  { skDECIPHERSCRIPT,		1 },
  { skDIPLOMACY,		0 },
  { skDISABLEDEVICE,		0 },
  { skDISGUISE,		0 },
  { skESCAPEARTIST,		0 },
  { skFORGERY,		0 },
  { skGATHERINFORMATION,		0 },
  { skHANDLEANIMAL,		0 },
  { skHEAL,		0 },
  { skHIDE,		0 },
  { skINTIMIDATE,		0 },
  { skJUMP,		1 },
  { skKNOWLEDGE_ARCANA,		1 },
  { skKNOWLEDGE_ARCHITECTUREANDENGINEERING,		0 },
  { skKNOWLEDGE_DUNGEONEERING,		0 },
  { skKNOWLEDGE_GEOGRAPHY,		0 },
  { skKNOWLEDGE_HISTORY,		0 },
  { skKNOWLEDGE_LOCAL,		0 },
  { skKNOWLEDGE_NATURE,		0 },
  { skKNOWLEDGE_NOBILITYANDROYALTY,		1 },
  { skKNOWLEDGE_RELIGION,		0 },
  { skKNOWLEDGE_THEPLANES,		0 },
  { skLISTEN,		0 },
  { skMOVESILENTLY,		0 },
  { skOPENLOCK,		0 },
  { skPERFORM_ACT,		0 },
  { skPERFORM_COMEDY,		0 },
  { skPERFORM_DANCE,		0 },
  { skPERFORM_KEYBOARDINSTRUMENTS,		0 },
  { skPERFORM_ORATORY,		0 },
  { skPERFORM_PERCUSSIONINSTRUMENTS,		0 },
  { skPERFORM_SING,		0 },
  { skPERFORM_STRINGINSTRUMENTS,		0 },
  { skPERFORM_WINDINSTRUMENTS,		0 },
  { skPROFESSION_HUNTER,		0 },
  { skPROFESSION_MINER,		0 },
  { skRIDE,		1 },
  { skSEARCH,		0 },
  { skSENSEMOTIVE,		1 },
  { skSLEIGHTOFHAND,		0 },
  { skSPEAKLANGUAGE,		0 },
  { skSPELLCRAFT,		1 },
  { skSPOT,		0 },
  { skSURVIVAL,		0 },
  { skSWIM,		0 },
  { skTUMBLE,		0 },
  { skUSEMAGICDEVICE,		0 },
  { skUSEROPE,		0 },
  { 0,		0 }
};

static SKILLSFORCLASS hierophantSkills[] = {
  { skAPPRAISE,		0 },
  { skBALANCE,		0 },
  { skBLUFF,		0 },
  { skCLIMB,		0 },
  { skCONCENTRATION,		1 },
  { skCRAFT_ALCHEMY,		1 },
  { skCRAFT_ARMORSMITHING,		1 },
  { skCRAFT_BLACKSMITHING,		1 },
  { skCRAFT_BOWMAKING,		1 },
  { skCRAFT_CARPENTRY,		1 },
  { skCRAFT_LEATHERWORKING,		1 },
  { skCRAFT_PAINTING,		1 },
  { skCRAFT_POTTERY,		1 },
  { skCRAFT_SCULPTING,		1 },
  { skCRAFT_SHIPMAKING,		1 },
  { skCRAFT_STONEMASONRY,		1 },
  { skCRAFT_TRAPMAKING,		1 },
  { skCRAFT_WEAPONSMITHING,		1 },
  { skCRAFT_WOODWORKING,		1 },
  { skDECIPHERSCRIPT,		0 },
  { skDIPLOMACY,		1 },
  { skDISABLEDEVICE,		0 },
  { skDISGUISE,		0 },
  { skESCAPEARTIST,		0 },
  { skFORGERY,		0 },
  { skGATHERINFORMATION,		0 },
  { skHANDLEANIMAL,		0 },
  { skHEAL,		1 },
  { skHIDE,		0 },
  { skINTIMIDATE,		0 },
  { skJUMP,		0 },
  { skKNOWLEDGE_ARCANA,		1 },
  { skKNOWLEDGE_ARCHITECTUREANDENGINEERING,		0 },
  { skKNOWLEDGE_DUNGEONEERING,		0 },
  { skKNOWLEDGE_GEOGRAPHY,		0 },
  { skKNOWLEDGE_HISTORY,		0 },
  { skKNOWLEDGE_LOCAL,		0 },
  { skKNOWLEDGE_NATURE,		0 },
  { skKNOWLEDGE_NOBILITYANDROYALTY,		0 },
  { skKNOWLEDGE_RELIGION,		1 },
  { skKNOWLEDGE_THEPLANES,		0 },
  { skLISTEN,		0 },
  { skMOVESILENTLY,		0 },
  { skOPENLOCK,		0 },
  { skPERFORM_ACT,		0 },
  { skPERFORM_COMEDY,		0 },
  { skPERFORM_DANCE,		0 },
  { skPERFORM_KEYBOARDINSTRUMENTS,		0 },
  { skPERFORM_ORATORY,		0 },
  { skPERFORM_PERCUSSIONINSTRUMENTS,		0 },
  { skPERFORM_SING,		0 },
  { skPERFORM_STRINGINSTRUMENTS,		0 },
  { skPERFORM_WINDINSTRUMENTS,		0 },
  { skPROFESSION_HUNTER,		1 },
  { skPROFESSION_MINER,		1 },
  { skRIDE,		0 },
  { skSEARCH,		0 },
  { skSENSEMOTIVE,		0 },
  { skSLEIGHTOFHAND,		0 },
  { skSPEAKLANGUAGE,		0 },
  { skSPELLCRAFT,		0 },
  { skSPOT,		0 },
  { skSURVIVAL,		0 },
  { skSWIM,		0 },
  { skTUMBLE,		0 },
  { skUSEMAGICDEVICE,		0 },
  { skUSEROPE,		0 },
  { 0,		0 }
};

static SKILLSFORCLASS horizonWalkerSkills[] = {
  { skAPPRAISE,		0 },
  { skBALANCE,		1 },
  { skBLUFF,		0 },
  { skCLIMB,		1 },
  { skCONCENTRATION,		0 },
  { skCRAFT_ALCHEMY,		0 },
  { skCRAFT_ARMORSMITHING,		0 },
  { skCRAFT_BLACKSMITHING,		0 },
  { skCRAFT_BOWMAKING,		0 },
  { skCRAFT_CARPENTRY,		0 },
  { skCRAFT_LEATHERWORKING,		0 },
  { skCRAFT_PAINTING,		0 },
  { skCRAFT_POTTERY,		0 },
  { skCRAFT_SCULPTING,		0 },
  { skCRAFT_SHIPMAKING,		0 },
  { skCRAFT_STONEMASONRY,		0 },
  { skCRAFT_TRAPMAKING,		0 },
  { skCRAFT_WEAPONSMITHING,		0 },
  { skCRAFT_WOODWORKING,		0 },
  { skDECIPHERSCRIPT,		0 },
  { skDIPLOMACY,		1 },
  { skDISABLEDEVICE,		0 },
  { skDISGUISE,		0 },
  { skESCAPEARTIST,		0 },
  { skFORGERY,		0 },
  { skGATHERINFORMATION,		0 },
  { skHANDLEANIMAL,		1 },
  { skHEAL,		0 },
  { skHIDE,		1 },
  { skINTIMIDATE,		0 },
  { skJUMP,		0 },
  { skKNOWLEDGE_ARCANA,		0 },
  { skKNOWLEDGE_ARCHITECTUREANDENGINEERING,		0 },
  { skKNOWLEDGE_DUNGEONEERING,		0 },
  { skKNOWLEDGE_GEOGRAPHY,		1 },
  { skKNOWLEDGE_HISTORY,		0 },
  { skKNOWLEDGE_LOCAL,		0 },
  { skKNOWLEDGE_NATURE,		0 },
  { skKNOWLEDGE_NOBILITYANDROYALTY,		0 },
  { skKNOWLEDGE_RELIGION,		0 },
  { skKNOWLEDGE_THEPLANES,		0 },
  { skLISTEN,		1 },
  { skMOVESILENTLY,		1 },
  { skOPENLOCK,		0 },
  { skPERFORM_ACT,		0 },
  { skPERFORM_COMEDY,		0 },
  { skPERFORM_DANCE,		0 },
  { skPERFORM_KEYBOARDINSTRUMENTS,		0 },
  { skPERFORM_ORATORY,		0 },
  { skPERFORM_PERCUSSIONINSTRUMENTS,		0 },
  { skPERFORM_SING,		0 },
  { skPERFORM_STRINGINSTRUMENTS,		0 },
  { skPERFORM_WINDINSTRUMENTS,		0 },
  { skPROFESSION_HUNTER,		1 },
  { skPROFESSION_MINER,		1 },
  { skRIDE,		1 },
  { skSEARCH,		0 },
  { skSENSEMOTIVE,		0 },
  { skSLEIGHTOFHAND,		0 },
  { skSPEAKLANGUAGE,		1 },
  { skSPELLCRAFT,		0 },
  { skSPOT,		1 },
  { skSURVIVAL,		0 },
  { skSWIM,		0 },
  { skTUMBLE,		0 },
  { skUSEMAGICDEVICE,		0 },
  { skUSEROPE,		0 },
  { 0,		0 }
};

static SKILLSFORCLASS loremasterSkills[] = {
  { skAPPRAISE,		1 },
  { skBALANCE,		0 },
  { skBLUFF,		0 },
  { skCLIMB,		0 },
  { skCONCENTRATION,		1 },
  { skCRAFT_ALCHEMY,		1 },
  { skCRAFT_ARMORSMITHING,		0 },
  { skCRAFT_BLACKSMITHING,		0 },
  { skCRAFT_BOWMAKING,		0 },
  { skCRAFT_CARPENTRY,		0 },
  { skCRAFT_LEATHERWORKING,		0 },
  { skCRAFT_PAINTING,		0 },
  { skCRAFT_POTTERY,		0 },
  { skCRAFT_SCULPTING,		0 },
  { skCRAFT_SHIPMAKING,		0 },
  { skCRAFT_STONEMASONRY,		0 },
  { skCRAFT_TRAPMAKING,		0 },
  { skCRAFT_WEAPONSMITHING,		0 },
  { skCRAFT_WOODWORKING,		0 },
  { skDECIPHERSCRIPT,		1 },
  { skDIPLOMACY,		0 },
  { skDISABLEDEVICE,		0 },
  { skDISGUISE,		0 },
  { skESCAPEARTIST,		0 },
  { skFORGERY,		0 },
  { skGATHERINFORMATION,		1 },
  { skHANDLEANIMAL,		1 },
  { skHEAL,		1 },
  { skHIDE,		0 },
  { skINTIMIDATE,		0 },
  { skJUMP,		0 },
  { skKNOWLEDGE_ARCANA,		1 },
  { skKNOWLEDGE_ARCHITECTUREANDENGINEERING,		1 },
  { skKNOWLEDGE_DUNGEONEERING,		1 },
  { skKNOWLEDGE_GEOGRAPHY,		1 },
  { skKNOWLEDGE_HISTORY,		1 },
  { skKNOWLEDGE_LOCAL,		1 },
  { skKNOWLEDGE_NATURE,		1 },
  { skKNOWLEDGE_NOBILITYANDROYALTY,		1 },
  { skKNOWLEDGE_RELIGION,		1 },
  { skKNOWLEDGE_THEPLANES,		1 },
  { skLISTEN,		0 },
  { skMOVESILENTLY,		0 },
  { skOPENLOCK,		0 },
  { skPERFORM_ACT,		1 },
  { skPERFORM_COMEDY,		1 },
  { skPERFORM_DANCE,		1 },
  { skPERFORM_KEYBOARDINSTRUMENTS,		1 },
  { skPERFORM_ORATORY,		1 },
  { skPERFORM_PERCUSSIONINSTRUMENTS,		1 },
  { skPERFORM_SING,		1 },
  { skPERFORM_STRINGINSTRUMENTS,		1 },
  { skPERFORM_WINDINSTRUMENTS,		1 },
  { skPROFESSION_HUNTER,		1 },
  { skPROFESSION_MINER,		1 },
  { skRIDE,		0 },
  { skSEARCH,		0 },
  { skSENSEMOTIVE,		0 },
  { skSLEIGHTOFHAND,		0 },
  { skSPEAKLANGUAGE,		1 },
  { skSPELLCRAFT,		1 },
  { skSPOT,		0 },
  { skSURVIVAL,		0 },
  { skSWIM,		0 },
  { skTUMBLE,		0 },
  { skUSEMAGICDEVICE,		0 },
  { skUSEROPE,		0 },
  { 0,		0 }
};

static SKILLSFORCLASS mysticTheurgeSkills[] = {
  { skAPPRAISE,		0 },
  { skBALANCE,		0 },
  { skBLUFF,		0 },
  { skCLIMB,		0 },
  { skCONCENTRATION,		1 },
  { skCRAFT_ALCHEMY,		1 },
  { skCRAFT_ARMORSMITHING,		1 },
  { skCRAFT_BLACKSMITHING,		1 },
  { skCRAFT_BOWMAKING,		1 },
  { skCRAFT_CARPENTRY,		1 },
  { skCRAFT_LEATHERWORKING,		1 },
  { skCRAFT_PAINTING,		1 },
  { skCRAFT_POTTERY,		1 },
  { skCRAFT_SCULPTING,		1 },
  { skCRAFT_SHIPMAKING,		1 },
  { skCRAFT_STONEMASONRY,		1 },
  { skCRAFT_TRAPMAKING,		1 },
  { skCRAFT_WEAPONSMITHING,		1 },
  { skCRAFT_WOODWORKING,		1 },
  { skDECIPHERSCRIPT,		1 },
  { skDIPLOMACY,		0 },
  { skDISABLEDEVICE,		0 },
  { skDISGUISE,		0 },
  { skESCAPEARTIST,		0 },
  { skFORGERY,		0 },
  { skGATHERINFORMATION,		0 },
  { skHANDLEANIMAL,		0 },
  { skHEAL,		0 },
  { skHIDE,		0 },
  { skINTIMIDATE,		0 },
  { skJUMP,		0 },
  { skKNOWLEDGE_ARCANA,		1 },
  { skKNOWLEDGE_ARCHITECTUREANDENGINEERING,		0 },
  { skKNOWLEDGE_DUNGEONEERING,		0 },
  { skKNOWLEDGE_GEOGRAPHY,		0 },
  { skKNOWLEDGE_HISTORY,		0 },
  { skKNOWLEDGE_LOCAL,		0 },
  { skKNOWLEDGE_NATURE,		0 },
  { skKNOWLEDGE_NOBILITYANDROYALTY,		0 },
  { skKNOWLEDGE_RELIGION,		1 },
  { skKNOWLEDGE_THEPLANES,		0 },
  { skLISTEN,		0 },
  { skMOVESILENTLY,		0 },
  { skOPENLOCK,		0 },
  { skPERFORM_ACT,		0 },
  { skPERFORM_COMEDY,		0 },
  { skPERFORM_DANCE,		0 },
  { skPERFORM_KEYBOARDINSTRUMENTS,		0 },
  { skPERFORM_ORATORY,		0 },
  { skPERFORM_PERCUSSIONINSTRUMENTS,		0 },
  { skPERFORM_SING,		0 },
  { skPERFORM_STRINGINSTRUMENTS,		0 },
  { skPERFORM_WINDINSTRUMENTS,		0 },
  { skPROFESSION_HUNTER,		1 },
  { skPROFESSION_MINER,		1 },
  { skRIDE,		0 },
  { skSEARCH,		0 },
  { skSENSEMOTIVE,		1 },
  { skSLEIGHTOFHAND,		0 },
  { skSPEAKLANGUAGE,		0 },
  { skSPELLCRAFT,		0 },
  { skSPOT,		0 },
  { skSURVIVAL,		0 },
  { skSWIM,		0 },
  { skTUMBLE,		0 },
  { skUSEMAGICDEVICE,		0 },
  { skUSEROPE,		0 },
  { 0,		0 }
};

static SKILLSFORCLASS shadowdancerSkills[] = {
  { skAPPRAISE,		0 },
  { skBALANCE,		1 },
  { skBLUFF,		1 },
  { skCLIMB,		0 },
  { skCONCENTRATION,		0 },
  { skCRAFT_ALCHEMY,		0 },
  { skCRAFT_ARMORSMITHING,		0 },
  { skCRAFT_BLACKSMITHING,		0 },
  { skCRAFT_BOWMAKING,		0 },
  { skCRAFT_CARPENTRY,		0 },
  { skCRAFT_LEATHERWORKING,		0 },
  { skCRAFT_PAINTING,		0 },
  { skCRAFT_POTTERY,		0 },
  { skCRAFT_SCULPTING,		0 },
  { skCRAFT_SHIPMAKING,		0 },
  { skCRAFT_STONEMASONRY,		0 },
  { skCRAFT_TRAPMAKING,		0 },
  { skCRAFT_WEAPONSMITHING,		0 },
  { skCRAFT_WOODWORKING,		0 },
  { skDECIPHERSCRIPT,		1 },
  { skDIPLOMACY,		1 },
  { skDISABLEDEVICE,		0 },
  { skDISGUISE,		1 },
  { skESCAPEARTIST,		1 },
  { skFORGERY,		0 },
  { skGATHERINFORMATION,		0 },
  { skHANDLEANIMAL,		0 },
  { skHEAL,		0 },
  { skHIDE,		1 },
  { skINTIMIDATE,		0 },
  { skJUMP,		1 },
  { skKNOWLEDGE_ARCANA,		0 },
  { skKNOWLEDGE_ARCHITECTUREANDENGINEERING,		0 },
  { skKNOWLEDGE_DUNGEONEERING,		0 },
  { skKNOWLEDGE_GEOGRAPHY,		0 },
  { skKNOWLEDGE_HISTORY,		0 },
  { skKNOWLEDGE_LOCAL,		0 },
  { skKNOWLEDGE_NATURE,		0 },
  { skKNOWLEDGE_NOBILITYANDROYALTY,		0 },
  { skKNOWLEDGE_RELIGION,		0 },
  { skKNOWLEDGE_THEPLANES,		0 },
  { skLISTEN,		1 },
  { skMOVESILENTLY,		1 },
  { skOPENLOCK,		0 },
  { skPERFORM_ACT,		1 },
  { skPERFORM_COMEDY,		1 },
  { skPERFORM_DANCE,		1 },
  { skPERFORM_KEYBOARDINSTRUMENTS,		1 },
  { skPERFORM_ORATORY,		1 },
  { skPERFORM_PERCUSSIONINSTRUMENTS,		1 },
  { skPERFORM_SING,		1 },
  { skPERFORM_STRINGINSTRUMENTS,		1 },
  { skPERFORM_WINDINSTRUMENTS,		1 },
  { skPROFESSION_HUNTER,		1 },
  { skPROFESSION_MINER,		1 },
  { skRIDE,		0 },
  { skSEARCH,		1 },
  { skSENSEMOTIVE,		0 },
  { skSLEIGHTOFHAND,		1 },
  { skSPEAKLANGUAGE,		0 },
  { skSPELLCRAFT,		0 },
  { skSPOT,		1 },
  { skSURVIVAL,		0 },
  { skSWIM,		0 },
  { skTUMBLE,		1 },
  { skUSEMAGICDEVICE,		0 },
  { skUSEROPE,		0 },
  { 0,		0 }
};

static SKILLSFORCLASS thaumaturgistSkills[] = {
  { skAPPRAISE,		0 },
  { skBALANCE,		0 },
  { skBLUFF,		0 },
  { skCLIMB,		0 },
  { skCONCENTRATION,		1 },
  { skCRAFT_ALCHEMY,		1 },
  { skCRAFT_ARMORSMITHING,		1 },
  { skCRAFT_BLACKSMITHING,		1 },
  { skCRAFT_BOWMAKING,		1 },
  { skCRAFT_CARPENTRY,		1 },
  { skCRAFT_LEATHERWORKING,		1 },
  { skCRAFT_PAINTING,		1 },
  { skCRAFT_POTTERY,		1 },
  { skCRAFT_SCULPTING,		1 },
  { skCRAFT_SHIPMAKING,		1 },
  { skCRAFT_STONEMASONRY,		1 },
  { skCRAFT_TRAPMAKING,		1 },
  { skCRAFT_WEAPONSMITHING,		1 },
  { skCRAFT_WOODWORKING,		1 },
  { skDECIPHERSCRIPT,		0 },
  { skDIPLOMACY,		1 },
  { skDISABLEDEVICE,		0 },
  { skDISGUISE,		0 },
  { skESCAPEARTIST,		0 },
  { skFORGERY,		0 },
  { skGATHERINFORMATION,		0 },
  { skHANDLEANIMAL,		0 },
  { skHEAL,		0 },
  { skHIDE,		0 },
  { skINTIMIDATE,		0 },
  { skJUMP,		0 },
  { skKNOWLEDGE_ARCANA,		0 },
  { skKNOWLEDGE_ARCHITECTUREANDENGINEERING,		0 },
  { skKNOWLEDGE_DUNGEONEERING,		0 },
  { skKNOWLEDGE_GEOGRAPHY,		0 },
  { skKNOWLEDGE_HISTORY,		0 },
  { skKNOWLEDGE_LOCAL,		0 },
  { skKNOWLEDGE_NATURE,		0 },
  { skKNOWLEDGE_NOBILITYANDROYALTY,		0 },
  { skKNOWLEDGE_RELIGION,		1 },
  { skKNOWLEDGE_THEPLANES,		1 },
  { skLISTEN,		0 },
  { skMOVESILENTLY,		0 },
  { skOPENLOCK,		0 },
  { skPERFORM_ACT,		0 },
  { skPERFORM_COMEDY,		0 },
  { skPERFORM_DANCE,		0 },
  { skPERFORM_KEYBOARDINSTRUMENTS,		0 },
  { skPERFORM_ORATORY,		0 },
  { skPERFORM_PERCUSSIONINSTRUMENTS,		0 },
  { skPERFORM_SING,		0 },
  { skPERFORM_STRINGINSTRUMENTS,		0 },
  { skPERFORM_WINDINSTRUMENTS,		0 },
  { skPROFESSION_HUNTER,		1 },
  { skPROFESSION_MINER,		1 },
  { skRIDE,		0 },
  { skSEARCH,		0 },
  { skSENSEMOTIVE,		1 },
  { skSLEIGHTOFHAND,		0 },
  { skSPEAKLANGUAGE,		1 },
  { skSPELLCRAFT,		0 },
  { skSPOT,		0 },
  { skSURVIVAL,		0 },
  { skSWIM,		0 },
  { skTUMBLE,		0 },
  { skUSEMAGICDEVICE,		0 },
  { skUSEROPE,		0 },
  { 0,		0 }
};





static SKILLSFORCLASS adeptSkills[] = {
  { skAPPRAISE,		0 },
  { skBALANCE,		0 },
  { skBLUFF,		0 },
  { skCLIMB,		0 },
  { skCONCENTRATION,		1 },
  { skCRAFT_ALCHEMY,		1 },
  { skCRAFT_ARMORSMITHING,		1 },
  { skCRAFT_BLACKSMITHING,		1 },
  { skCRAFT_BOWMAKING,		1 },
  { skCRAFT_CARPENTRY,		1 },
  { skCRAFT_LEATHERWORKING,		1 },
  { skCRAFT_PAINTING,		1 },
  { skCRAFT_POTTERY,		1 },
  { skCRAFT_SCULPTING,		1 },
  { skCRAFT_SHIPMAKING,		1 },
  { skCRAFT_STONEMASONRY,		1 },
  { skCRAFT_TRAPMAKING,		1 },
  { skCRAFT_WEAPONSMITHING,		1 },
  { skCRAFT_WOODWORKING,		1 },
  { skDECIPHERSCRIPT,		0 },
  { skDIPLOMACY,		0 },
  { skDISABLEDEVICE,		0 },
  { skDISGUISE,		0 },
  { skESCAPEARTIST,		0 },
  { skFORGERY,		0 },
  { skGATHERINFORMATION,		0 },
  { skHANDLEANIMAL,		1 },
  { skHEAL,		1 },
  { skHIDE,		0 },
  { skINTIMIDATE,		0 },
  { skJUMP,		0 },
  { skKNOWLEDGE_ARCANA,		1 },
  { skKNOWLEDGE_ARCHITECTUREANDENGINEERING,		1 },
  { skKNOWLEDGE_DUNGEONEERING,		1 },
  { skKNOWLEDGE_GEOGRAPHY,		1 },
  { skKNOWLEDGE_HISTORY,		1 },
  { skKNOWLEDGE_LOCAL,		1 },
  { skKNOWLEDGE_NATURE,		1 },
  { skKNOWLEDGE_NOBILITYANDROYALTY,		1 },
  { skKNOWLEDGE_RELIGION,		1 },
  { skKNOWLEDGE_THEPLANES,		1 },
  { skLISTEN,		0 },
  { skMOVESILENTLY,		0 },
  { skOPENLOCK,		0 },
  { skPERFORM_ACT,		0 },
  { skPERFORM_COMEDY,		0 },
  { skPERFORM_DANCE,		0 },
  { skPERFORM_KEYBOARDINSTRUMENTS,		0 },
  { skPERFORM_ORATORY,		0 },
  { skPERFORM_PERCUSSIONINSTRUMENTS,		0 },
  { skPERFORM_SING,		0 },
  { skPERFORM_STRINGINSTRUMENTS,		0 },
  { skPERFORM_WINDINSTRUMENTS,		0 },
  { skPROFESSION_HUNTER,		1 },
  { skPROFESSION_MINER,		1 },
  { skRIDE,		0 },
  { skSEARCH,		0 },
  { skSENSEMOTIVE,		0 },
  { skSLEIGHTOFHAND,		0 },
  { skSPEAKLANGUAGE,		0 },
  { skSPELLCRAFT,		1 },
  { skSPOT,		0 },
  { skSURVIVAL,		0 },
  { skSWIM,		0 },
  { skTUMBLE,		0 },
  { skUSEMAGICDEVICE,		0 },
  { skUSEROPE,		0 },
  { 0,		0 }
};

static SKILLSFORCLASS aristocratSkills[] = {
  { skAPPRAISE,		1 },
  { skBALANCE,		0 },
  { skBLUFF,		1 },
  { skCLIMB,		0 },
  { skCONCENTRATION,		0 },
  { skCRAFT_ALCHEMY,		0 },
  { skCRAFT_ARMORSMITHING,		0 },
  { skCRAFT_BLACKSMITHING,		0 },
  { skCRAFT_BOWMAKING,		0 },
  { skCRAFT_CARPENTRY,		0 },
  { skCRAFT_LEATHERWORKING,		0 },
  { skCRAFT_PAINTING,		0 },
  { skCRAFT_POTTERY,		0 },
  { skCRAFT_SCULPTING,		0 },
  { skCRAFT_SHIPMAKING,		0 },
  { skCRAFT_STONEMASONRY,		0 },
  { skCRAFT_TRAPMAKING,		0 },
  { skCRAFT_WEAPONSMITHING,		0 },
  { skCRAFT_WOODWORKING,		0 },
  { skDECIPHERSCRIPT,		0 },
  { skDIPLOMACY,		1 },
  { skDISABLEDEVICE,		0 },
  { skDISGUISE,		1 },
  { skESCAPEARTIST,		0 },
  { skFORGERY,		1 },
  { skGATHERINFORMATION,		1 },
  { skHANDLEANIMAL,		1 },
  { skHEAL,		0 },
  { skHIDE,		0 },
  { skINTIMIDATE,		1 },
  { skJUMP,		0 },
  { skKNOWLEDGE_ARCANA,		1 },
  { skKNOWLEDGE_ARCHITECTUREANDENGINEERING,		1 },
  { skKNOWLEDGE_DUNGEONEERING,		1 },
  { skKNOWLEDGE_GEOGRAPHY,		1 },
  { skKNOWLEDGE_HISTORY,		1 },
  { skKNOWLEDGE_LOCAL,		1 },
  { skKNOWLEDGE_NATURE,		1 },
  { skKNOWLEDGE_NOBILITYANDROYALTY,		1 },
  { skKNOWLEDGE_RELIGION,		1 },
  { skKNOWLEDGE_THEPLANES,		1 },
  { skLISTEN,		1 },
  { skMOVESILENTLY,		0 },
  { skOPENLOCK,		0 },
  { skPERFORM_ACT,		1 },
  { skPERFORM_COMEDY,		1 },
  { skPERFORM_DANCE,		1 },
  { skPERFORM_KEYBOARDINSTRUMENTS,		1 },
  { skPERFORM_ORATORY,		1 },
  { skPERFORM_PERCUSSIONINSTRUMENTS,		1 },
  { skPERFORM_SING,		1 },
  { skPERFORM_STRINGINSTRUMENTS,		1 },
  { skPERFORM_WINDINSTRUMENTS,		1 },
  { skPROFESSION_HUNTER,		0 },
  { skPROFESSION_MINER,		0 },
  { skRIDE,		1 },
  { skSEARCH,		0 },
  { skSENSEMOTIVE,		1 },
  { skSLEIGHTOFHAND,		0 },
  { skSPEAKLANGUAGE,		1 },
  { skSPELLCRAFT,		0 },
  { skSPOT,		1 },
  { skSURVIVAL,		0 },
  { skSWIM,		1 },
  { skTUMBLE,		0 },
  { skUSEMAGICDEVICE,		0 },
  { skUSEROPE,		0 },
  { 0,		0 }
};

static SKILLSFORCLASS commonerSkills[] = {
  { skAPPRAISE,		0 },
  { skBALANCE,		0 },
  { skBLUFF,		0 },
  { skCLIMB,		1 },
  { skCONCENTRATION,		0 },
  { skCRAFT_ALCHEMY,		1 },
  { skCRAFT_ARMORSMITHING,		1 },
  { skCRAFT_BLACKSMITHING,		1 },
  { skCRAFT_BOWMAKING,		1 },
  { skCRAFT_CARPENTRY,		1 },
  { skCRAFT_LEATHERWORKING,		1 },
  { skCRAFT_PAINTING,		1 },
  { skCRAFT_POTTERY,		1 },
  { skCRAFT_SCULPTING,		1 },
  { skCRAFT_SHIPMAKING,		1 },
  { skCRAFT_STONEMASONRY,		1 },
  { skCRAFT_TRAPMAKING,		1 },
  { skCRAFT_WEAPONSMITHING,		1 },
  { skCRAFT_WOODWORKING,		1 },
  { skDECIPHERSCRIPT,		0 },
  { skDIPLOMACY,		0 },
  { skDISABLEDEVICE,		0 },
  { skDISGUISE,		0 },
  { skESCAPEARTIST,		0 },
  { skFORGERY,		0 },
  { skGATHERINFORMATION,		0 },
  { skHANDLEANIMAL,		1 },
  { skHEAL,		0 },
  { skHIDE,		0 },
  { skINTIMIDATE,		0 },
  { skJUMP,		1 },
  { skKNOWLEDGE_ARCANA,		0 },
  { skKNOWLEDGE_ARCHITECTUREANDENGINEERING,		0 },
  { skKNOWLEDGE_DUNGEONEERING,		0 },
  { skKNOWLEDGE_GEOGRAPHY,		0 },
  { skKNOWLEDGE_HISTORY,		0 },
  { skKNOWLEDGE_LOCAL,		0 },
  { skKNOWLEDGE_NATURE,		0 },
  { skKNOWLEDGE_NOBILITYANDROYALTY,		0 },
  { skKNOWLEDGE_RELIGION,		0 },
  { skKNOWLEDGE_THEPLANES,		0 },
  { skLISTEN,		1 },
  { skMOVESILENTLY,		0 },
  { skOPENLOCK,		0 },
  { skPERFORM_ACT,		0 },
  { skPERFORM_COMEDY,		0 },
  { skPERFORM_DANCE,		0 },
  { skPERFORM_KEYBOARDINSTRUMENTS,		0 },
  { skPERFORM_ORATORY,		0 },
  { skPERFORM_PERCUSSIONINSTRUMENTS,		0 },
  { skPERFORM_SING,		0 },
  { skPERFORM_STRINGINSTRUMENTS,		0 },
  { skPERFORM_WINDINSTRUMENTS,		0 },
  { skPROFESSION_HUNTER,		1 },
  { skPROFESSION_MINER,		1 },
  { skRIDE,		1 },
  { skSEARCH,		0 },
  { skSENSEMOTIVE,		0 },
  { skSLEIGHTOFHAND,		0 },
  { skSPEAKLANGUAGE,		0 },
  { skSPELLCRAFT,		0 },
  { skSPOT,		1 },
  { skSURVIVAL,		0 },
  { skSWIM,		1 },
  { skTUMBLE,		0 },
  { skUSEMAGICDEVICE,		0 },
  { skUSEROPE,		0 },
  { 0,		0 }
};

static SKILLSFORCLASS expertSkills[] = {
  { skAPPRAISE,		0 },
  { skBALANCE,		0 },
  { skBLUFF,		0 },
  { skCLIMB,		0 },
  { skCONCENTRATION,		0 },
  { skCRAFT_ALCHEMY,		0 },
  { skCRAFT_ARMORSMITHING,		0 },
  { skCRAFT_BLACKSMITHING,		0 },
  { skCRAFT_BOWMAKING,		0 },
  { skCRAFT_CARPENTRY,		0 },
  { skCRAFT_LEATHERWORKING,		0 },
  { skCRAFT_PAINTING,		0 },
  { skCRAFT_POTTERY,		0 },
  { skCRAFT_SCULPTING,		0 },
  { skCRAFT_SHIPMAKING,		0 },
  { skCRAFT_STONEMASONRY,		0 },
  { skCRAFT_TRAPMAKING,		0 },
  { skCRAFT_WEAPONSMITHING,		0 },
  { skCRAFT_WOODWORKING,		0 },
  { skDECIPHERSCRIPT,		0 },
  { skDIPLOMACY,		0 },
  { skDISABLEDEVICE,		0 },
  { skDISGUISE,		0 },
  { skESCAPEARTIST,		0 },
  { skFORGERY,		0 },
  { skGATHERINFORMATION,		0 },
  { skHANDLEANIMAL,		0 },
  { skHEAL,		0 },
  { skHIDE,		0 },
  { skINTIMIDATE,		0 },
  { skJUMP,		0 },
  { skKNOWLEDGE_ARCANA,		0 },
  { skKNOWLEDGE_ARCHITECTUREANDENGINEERING,		0 },
  { skKNOWLEDGE_DUNGEONEERING,		0 },
  { skKNOWLEDGE_GEOGRAPHY,		0 },
  { skKNOWLEDGE_HISTORY,		0 },
  { skKNOWLEDGE_LOCAL,		0 },
  { skKNOWLEDGE_NATURE,		0 },
  { skKNOWLEDGE_NOBILITYANDROYALTY,		0 },
  { skKNOWLEDGE_RELIGION,		0 },
  { skKNOWLEDGE_THEPLANES,		0 },
  { skLISTEN,		0 },
  { skMOVESILENTLY,		0 },
  { skOPENLOCK,		0 },
  { skPERFORM_ACT,		0 },
  { skPERFORM_COMEDY,		0 },
  { skPERFORM_DANCE,		0 },
  { skPERFORM_KEYBOARDINSTRUMENTS,		0 },
  { skPERFORM_ORATORY,		0 },
  { skPERFORM_PERCUSSIONINSTRUMENTS,		0 },
  { skPERFORM_SING,		0 },
  { skPERFORM_STRINGINSTRUMENTS,		0 },
  { skPERFORM_WINDINSTRUMENTS,		0 },
  { skPROFESSION_HUNTER,		0 },
  { skPROFESSION_MINER,		0 },
  { skRIDE,		0 },
  { skSEARCH,		0 },
  { skSENSEMOTIVE,		0 },
  { skSLEIGHTOFHAND,		0 },
  { skSPEAKLANGUAGE,		0 },
  { skSPELLCRAFT,		0 },
  { skSPOT,		0 },
  { skSURVIVAL,		0 },
  { skSWIM,		0 },
  { skTUMBLE,		0 },
  { skUSEMAGICDEVICE,		0 },
  { skUSEROPE,		0 },
  { 0,		0 }
};

static SKILLSFORCLASS warriorSkills[] = {
  { skAPPRAISE,		0 },
  { skBALANCE,		0 },
  { skBLUFF,		0 },
  { skCLIMB,		1 },
  { skCONCENTRATION,		0 },
  { skCRAFT_ALCHEMY,		0 },
  { skCRAFT_ARMORSMITHING,		0 },
  { skCRAFT_BLACKSMITHING,		0 },
  { skCRAFT_BOWMAKING,		0 },
  { skCRAFT_CARPENTRY,		0 },
  { skCRAFT_LEATHERWORKING,		0 },
  { skCRAFT_PAINTING,		0 },
  { skCRAFT_POTTERY,		0 },
  { skCRAFT_SCULPTING,		0 },
  { skCRAFT_SHIPMAKING,		0 },
  { skCRAFT_STONEMASONRY,		0 },
  { skCRAFT_TRAPMAKING,		0 },
  { skCRAFT_WEAPONSMITHING,		0 },
  { skCRAFT_WOODWORKING,		0 },
  { skDECIPHERSCRIPT,		0 },
  { skDIPLOMACY,		0 },
  { skDISABLEDEVICE,		0 },
  { skDISGUISE,		0 },
  { skESCAPEARTIST,		0 },
  { skFORGERY,		0 },
  { skGATHERINFORMATION,		0 },
  { skHANDLEANIMAL,		1 },
  { skHEAL,		0 },
  { skHIDE,		0 },
  { skINTIMIDATE,		1 },
  { skJUMP,		1 },
  { skKNOWLEDGE_ARCANA,		0 },
  { skKNOWLEDGE_ARCHITECTUREANDENGINEERING,		0 },
  { skKNOWLEDGE_DUNGEONEERING,		0 },
  { skKNOWLEDGE_GEOGRAPHY,		0 },
  { skKNOWLEDGE_HISTORY,		0 },
  { skKNOWLEDGE_LOCAL,		0 },
  { skKNOWLEDGE_NATURE,		0 },
  { skKNOWLEDGE_NOBILITYANDROYALTY,		0 },
  { skKNOWLEDGE_RELIGION,		0 },
  { skKNOWLEDGE_THEPLANES,		0 },
  { skLISTEN,		0 },
  { skMOVESILENTLY,		0 },
  { skOPENLOCK,		0 },
  { skPERFORM_ACT,		0 },
  { skPERFORM_COMEDY,		0 },
  { skPERFORM_DANCE,		0 },
  { skPERFORM_KEYBOARDINSTRUMENTS,		0 },
  { skPERFORM_ORATORY,		0 },
  { skPERFORM_PERCUSSIONINSTRUMENTS,		0 },
  { skPERFORM_SING,		0 },
  { skPERFORM_STRINGINSTRUMENTS,		0 },
  { skPERFORM_WINDINSTRUMENTS,		0 },
  { skPROFESSION_HUNTER,		0 },
  { skPROFESSION_MINER,		0 },
  { skRIDE,		1 },
  { skSEARCH,		0 },
  { skSENSEMOTIVE,		0 },
  { skSLEIGHTOFHAND,		0 },
  { skSPEAKLANGUAGE,		0 },
  { skSPELLCRAFT,		0 },
  { skSPOT,		0 },
  { skSURVIVAL,		0 },
  { skSWIM,		0 },
  { skTUMBLE,		0 },
  { skUSEMAGICDEVICE,		0 },
  { skUSEROPE,		0 },
  { 0,		0 }
};



static SPELLSFORCLASS s_Adept[] = {
  { spAID,		2 },
  { spANIMALTRANCE,		2 },
  { spANIMATEDEAD,		3 },
  { spBALEFULPOLYMORPH,		5 },
  { spBEARSENDURANCE,		2 },
  { spBESTOWCURSE,		3 },
  { spBLESS,		1 },
  { spBREAKENCHANTMENT,		5 },
  { spBULLSSTRENGTH,		2 },
  { spBURNINGHANDS,		1 },
  { spCATSGRACE,		2 },
  { spCAUSEFEAR,		1 },
  { spCOMMAND,		1 },
  { spCOMMUNE,		5 },
  { spCOMPREHENDLANGUAGES,		1 },
  { spCONTAGION,		3 },
  { spCONTINUALFLAME,		3 },
  { spCREATEWATER,		0 },
  { spCURECRITICALWOUNDS,		4 },
  { spCURELIGHTWOUNDS,		1 },
  { spCUREMINORWOUNDS,		0 },
  { spCUREMODERATEWOUNDS,		2 },
  { spCURESERIOUSWOUNDS,		3 },
  { spDARKNESS,		2 },
  { spDAYLIGHT,		3 },
  { spDEEPERDARKNESS,		3 },
  { spDELAYPOISON,		2 },
  { spDETECTCHAOS,		1 },
  { spDETECTEVIL,		1 },
  { spDETECTGOOD,		1 },
  { spDETECTLAW,		1 },
  { spDETECTMAGIC,		0 },
  { spENDUREELEMENTS,		1 },
  { spGHOSTSOUND,		0 },
  { spGUIDANCE,		0 },
  { spHEAL,		5 },
  { spINVISIBILITY,		2 },
  { spLIGHT,		0 },
  { spLIGHTNINGBOLT,		3 },
  { spMAJORCREATION,		5 },
  { spMENDING,		0 },
  { spMINORCREATION,		4 },
  { spMIRRORIMAGE,		2 },
  { spNEUTRALIZEPOISON,		3 },
  { spOBSCURINGMIST,		1 },
  { spPOLYMORPH,		4 },
  { spPROTECTIONFROMCHAOS,		1 },
  { spPROTECTIONFROMEVIL,		1 },
  { spPROTECTIONFROMGOOD,		1 },
  { spPROTECTIONFROMLAW,		1 },
  { spPURIFYFOODANDDRINK,		0 },
  { spRAISEDEAD,		5 },
  { spREADMAGIC,		0 },
  { spREMOVECURSE,		3 },
  { spREMOVEDISEASE,		3 },
  { spRESISTENERGY,		2 },
  { spRESTORATION,		4 },
  { spSCORCHINGRAY,		2 },
  { spSEEINVISIBILITY,		2 },
  { spSLEEP,		1 },
  { spSTONESKIN,		4 },
  { spTONGUES,		3 },
  { spTOUCHOFFATIGUE,		0 },
  { spTRUESEEING,		5 },
  { spWALLOFFIRE,		4 },
  { spWALLOFSTONE,		5 },
  { spWEB,		2 },
  { 0, 0 }
};

static SPELLSFORCLASS s_Air[] = {
  { spAIRWALK,		4 },
  { spCHAINLIGHTNING,		6 },
  { spCONTROLWEATHER,		7 },
  { spCONTROLWINDS,		5 },
  { spELEMENTALSWARM,		9 },
  { spGASEOUSFORM,		3 },
  { spOBSCURINGMIST,		1 },
  { spWHIRLWIND,		8 },
  { spWINDWALL,		2 },
  { 0, 0 }
};

static SPELLSFORCLASS s_Animal[] = {
  { spANIMALSHAPES,		7 },
  { spANTILIFESHELL,		6 },
  { spCALMANIMALS,		1 },
  { spCOMMUNEWITHNATURE,		5 },
  { spDOMINATEANIMAL,		3 },
  { spHOLDANIMAL,		2 },
  { spSHAPECHANGE,		9 },
  { spSUMMONNATURESALLYIV,		4 },
  { spSUMMONNATURESALLYVIII,		8 },
  { 0, 0 }
};

static SPELLSFORCLASS s_Assassin[] = {
  { spALTERSELF,		2 },
  { spCATSGRACE,		2 },
  { spCLAIRAUDIENCECLAIRVOYANCE,		4 },
  { spDARKNESS,		2 },
  { spDEEPERDARKNESS,		3 },
  { spDEEPSLUMBER,		3 },
  { spDETECTPOISON,		1 },
  { spDIMENSIONDOOR,		4 },
  { spDISGUISESELF,		1 },
  { spFALSELIFE,		3 },
  { spFEATHERFALL,		1 },
  { spFOXSCUNNING,		2 },
  { spFREEDOMOFMOVEMENT,		4 },
  { spGHOSTSOUND,		1 },
  { spGLIBNESS,		4 },
  { spILLUSORYSCRIPT,		2 },
  { spINVISIBILITY,		2 },
  { spINVISIBILITYGREATER,		4 },
  { spJUMP,		1 },
  { spLOCATECREATURE,		4 },
  { spMAGICCIRCLEAGAINSTGOOD,		3 },
  { spMISDIRECTION,		3 },
  { spMODIFYMEMORY,		4 },
  { spNONDETECTION,		3 },
  { spOBSCURINGMIST,		1 },
  { spPASSWITHOUTTRACE,		2 },
  { spPOISON,		4 },
  { spSLEEP,		1 },
  { spSPIDERCLIMB,		2 },
  { spTRUESTRIKE,		1 },
  { spUNDETECTABLEALIGNMENT,		2 },
  { 0, 0 }
};

static SPELLSFORCLASS s_Blackguard[] = {
  { spBULLSSTRENGTH,		2 },
  { spCAUSEFEAR,		1 },
  { spCONTAGION,		3 },
  { spCURECRITICALWOUNDS,		4 },
  { spCURELIGHTWOUNDS,		1 },
  { spCUREMODERATEWOUNDS,		2 },
  { spCURESERIOUSWOUNDS,		3 },
  { spDARKNESS,		2 },
  { spDEATHKNELL,		2 },
  { spDEEPERDARKNESS,		3 },
  { spDOOM,		1 },
  { spEAGLESSPLENDOR,		2 },
  { spFREEDOMOFMOVEMENT,		4 },
  { spINFLICTCRITICALWOUNDS,		4 },
  { spINFLICTLIGHTWOUNDS,		1 },
  { spINFLICTMODERATEWOUNDS,		2 },
  { spINFLICTSERIOUSWOUNDS,		3 },
  { spMAGICWEAPON,		1 },
  { spPOISON,		4 },
  { spPROTECTIONFROMENERGY,		3 },
  { spSHATTER,		2 },
  { spSUMMONMONSTERI,		1 },
  { spSUMMONMONSTERII,		2 },
  { spSUMMONMONSTERIII,		3 },
  { spSUMMONMONSTERIV,		4 },
  { 0, 0 }
};

static SPELLSFORCLASS s_Bard[] = {
  { spALARM,		1 },
  { spALTERSELF,		2 },
  { spANALYZEDWEOMER,		6 },
  { spANIMALMESSENGER,		2 },
  { spANIMALTRANCE,		2 },
  { spANIMATEOBJECTS,		6 },
  { spANIMATEROPE,		1 },
  { spBLINDNESSDEAFNESS,		2 },
  { spBLINK,		3 },
  { spBLUR,		2 },
  { spBREAKENCHANTMENT,		4 },
  { spCALMEMOTIONS,		2 },
  { spCATSGRACE,		2 },
  { spCATSGRACEMASS,		6 },
  { spCAUSEFEAR,		1 },
  { spCHARMMONSTER,		3 },
  { spCHARMMONSTERMASS,		6 },
  { spCHARMPERSON,		1 },
  { spCLAIRAUDIENCECLAIRVOYANCE,		3 },
  { spCOMPREHENDLANGUAGES,		1 },
  { spCONFUSION,		3 },
  { spCONFUSIONLESSER,		1 },
  { spCRUSHINGDESPAIR,		3 },
  { spCURECRITICALWOUNDS,		4 },
  { spCURELIGHTWOUNDS,		1 },
  { spCURELIGHTWOUNDSMASS,		5 },
  { spCUREMODERATEWOUNDS,		2 },
  { spCUREMODERATEWOUNDSMASS,		6 },
  { spCURESERIOUSWOUNDS,		3 },
  { spDANCINGLIGHTS,		0 },
  { spDARKNESS,		2 },
  { spDAYLIGHT,		3 },
  { spDAZE,		0 },
  { spDAZEMONSTER,		2 },
  { spDEEPSLUMBER,		3 },
  { spDELAYPOISON,		2 },
  { spDETECTMAGIC,		0 },
  { spDETECTSCRYING,		4 },
  { spDETECTSECRETDOORS,		1 },
  { spDETECTTHOUGHTS,		2 },
  { spDIMENSIONDOOR,		4 },
  { spDISGUISESELF,		1 },
  { spDISPELMAGIC,		3 },
  { spDISPELMAGICGREATER,		5 },
  { spDISPLACEMENT,		3 },
  { spDOMINATEPERSON,		4 },
  { spDREAM,		5 },
  { spEAGLESSPLENDOR,		2 },
  { spEAGLESSPLENDORMASS,		6 },
  { spENTHRALL,		2 },
  { spERASE,		1 },
  { spEXPEDITIOUSRETREAT,		1 },
  { spEYEBITE,		6 },
  { spFALSEVISION,		5 },
  { spFEAR,		3 },
  { spFEATHERFALL,		1 },
  { spFINDTHEPATH,		6 },
  { spFLARE,		0 },
  { spFOXSCUNNING,		2 },
  { spFOXSCUNNINGMASS,		6 },
  { spFREEDOMOFMOVEMENT,		4 },
  { spGASEOUSFORM,		3 },
  { spGEASLESSER,		3 },
  { spGEASQUEST,		6 },
  { spGHOSTSOUND,		0 },
  { spGLIBNESS,		3 },
  { spGLITTERDUST,		2 },
  { spGOODHOPE,		3 },
  { spGREASE,		1 },
  { spHALLUCINATORYTERRAIN,		4 },
  { spHASTE,		3 },
  { spHEROESFEAST,		6 },
  { spHEROISM,		2 },
  { spHEROISMGREATER,		5 },
  { spHIDEOUSLAUGHTER,		1 },
  { spHOLDMONSTER,		4 },
  { spHOLDPERSON,		2 },
  { spHYPNOTICPATTERN,		2 },
  { spHYPNOTISM,		1 },
  { spIDENTIFY,		1 },
  { spILLUSORYSCRIPT,		3 },
  { spINVISIBILITY,		2 },
  { spINVISIBILITYGREATER,		4 },
  { spINVISIBILITYSPHERE,		3 },
  { spIRRESISTIBLEDANCE,		6 },
  { spKNOWDIRECTION,		0 },
  { spLEGENDLORE,		4 },
  { spLIGHT,		0 },
  { spLOCATECREATURE,		4 },
  { spLOCATEOBJECT,		2 },
  { spLULLABY,		0 },
  { spMAGEHAND,		0 },
  { spMAGICAURA,		1 },
  { spMAGICMOUTH,		1 },
  { spMAJORIMAGE,		3 },
  { spMENDING,		0 },
  { spMESSAGE,		0 },
  { spMINDFOG,		5 },
  { spMINORIMAGE,		2 },
  { spMIRAGEARCANA,		5 },
  { spMIRRORIMAGE,		2 },
  { spMISDIRECTION,		2 },
  { spMISLEAD,		5 },
  { spMODIFYMEMORY,		4 },
  { spNEUTRALIZEPOISON,		4 },
  { spNIGHTMARE,		5 },
  { spOBSCUREOBJECT,		1 },
  { spOPENCLOSE,		0 },
  { spPERMANENTIMAGE,		6 },
  { spPERSISTENTIMAGE,		5 },
  { spPHANTOMSTEED,		3 },
  { spPRESTIDIGITATION,		0 },
  { spPROGRAMMEDIMAGE,		6 },
  { spPROJECTIMAGE,		6 },
  { spPYROTECHNICS,		2 },
  { spRAGE,		2 },
  { spRAINBOWPATTERN,		4 },
  { spREADMAGIC,		0 },
  { spREMOVECURSE,		3 },
  { spREMOVEFEAR,		1 },
  { spREPELVERMIN,		4 },
  { spRESISTANCE,		0 },
  { spSCARE,		2 },
  { spSCRYING,		3 },
  { spSCRYINGGREATER,		6 },
  { spSCULPTSOUND,		3 },
  { spSECRETPAGE,		3 },
  { spSECURESHELTER,		4 },
  { spSEEINVISIBILITY,		3 },
  { spSEEMING,		5 },
  { spSEPIASNAKESIGIL,		3 },
  { spSHADOWCONJURATION,		4 },
  { spSHADOWEVOCATION,		5 },
  { spSHADOWWALK,		5 },
  { spSHATTER,		2 },
  { spSHOUT,		4 },
  { spSHOUTGREATER,		6 },
  { spSILENCE,		2 },
  { spSILENTIMAGE,		1 },
  { spSLEEP,		1 },
  { spSLOW,		3 },
  { spSONGOFDISCORD,		5 },
  { spSOUNDBURST,		2 },
  { spSPEAKWITHANIMALS,		3 },
  { spSPEAKWITHPLANTS,		4 },
  { spSUGGESTION,		2 },
  { spSUGGESTIONMASS,		5 },
  { spSUMMONINSTRUMENT,		0 },
  { spSUMMONMONSTERI,		1 },
  { spSUMMONMONSTERII,		2 },
  { spSUMMONMONSTERIII,		3 },
  { spSUMMONMONSTERIV,		4 },
  { spSUMMONMONSTERV,		5 },
  { spSUMMONMONSTERVI,		6 },
  { spSUMMONSWARM,		2 },
  { spSYMPATHETICVIBRATION,		6 },
  { spTINYHUT,		3 },
  { spTONGUES,		2 },
  { spUNDETECTABLEALIGNMENT,		1 },
  { spUNSEENSERVANT,		1 },
  { spVEIL,		6 },
  { spVENTRILOQUISM,		1 },
  { spWHISPERINGWIND,		2 },
  { spZONEOFSILENCE,		4 },
  { 0, 0 }
};

static SPELLSFORCLASS s_Chaos[] = {
  { spANIMATEOBJECTS,		6 },
  { spCHAOSHAMMER,		4 },
  { spCLOAKOFCHAOS,		8 },
  { spDISPELLAW,		5 },
  { spMAGICCIRCLEAGAINSTLAW,		3 },
  { spPROTECTIONFROMLAW,		1 },
  { spSHATTER,		2 },
  { spSUMMONMONSTERIX,		9 },
  { spWORDOFCHAOS,		7 },
  { 0, 0 }
};

static SPELLSFORCLASS s_Cleric[] = {
  { spAID,		2 },
  { spAIRWALK,		4 },
  { spALIGNWEAPON,		2 },
  { spANIMATEDEAD,		3 },
  { spANIMATEOBJECTS,		6 },
  { spANTILIFESHELL,		6 },
  { spANTIMAGICFIELD,		8 },
  { spASTRALPROJECTION,		9 },
  { spATONEMENT,		5 },
  { spAUGURY,		2 },
  { spBANE,		1 },
  { spBANISHMENT,		6 },
  { spBEARSENDURANCE,		2 },
  { spBEARSENDURANCEMASS,		6 },
  { spBESTOWCURSE,		3 },
  { spBLADEBARRIER,		6 },
  { spBLASPHEMY,		7 },
  { spBLESS,		1 },
  { spBLESSWATER,		1 },
  { spBLINDNESSDEAFNESS,		3 },
  { spBREAKENCHANTMENT,		5 },
  { spBULLSSTRENGTH,		2 },
  { spBULLSSTRENGTHMASS,		6 },
  { spCALMEMOTIONS,		2 },
  { spCAUSEFEAR,		1 },
  { spCLOAKOFCHAOS,		8 },
  { spCOMMAND,		1 },
  { spCOMMANDGREATER,		5 },
  { spCOMMUNE,		5 },
  { spCOMPREHENDLANGUAGES,		1 },
  { spCONSECRATE,		2 },
  { spCONTAGION,		3 },
  { spCONTINUALFLAME,		3 },
  { spCONTROLWATER,		4 },
  { spCONTROLWEATHER,		7 },
  { spCREATEFOODANDWATER,		3 },
  { spCREATEGREATERUNDEAD,		8 },
  { spCREATEUNDEAD,		6 },
  { spCREATEWATER,		0 },
  { spCURECRITICALWOUNDS,		4 },
  { spCURECRITICALWOUNDSMASS,		8 },
  { spCURELIGHTWOUNDS,		1 },
  { spCURELIGHTWOUNDSMASS,		5 },
  { spCUREMINORWOUNDS,		0 },
  { spCUREMODERATEWOUNDS,		2 },
  { spCUREMODERATEWOUNDSMASS,		6 },
  { spCURESERIOUSWOUNDS,		3 },
  { spCURESERIOUSWOUNDSMASS,		7 },
  { spCURSEWATER,		1 },
  { spDARKNESS,		2 },
  { spDAYLIGHT,		3 },
  { spDEATHKNELL,		2 },
  { spDEATHWARD,		4 },
  { spDEATHWATCH,		1 },
  { spDEEPERDARKNESS,		3 },
  { spDELAYPOISON,		2 },
  { spDESECRATE,		2 },
  { spDESTRUCTION,		7 },
  { spDETECTCHAOS,		1 },
  { spDETECTEVIL,		1 },
  { spDETECTGOOD,		1 },
  { spDETECTLAW,		1 },
  { spDETECTMAGIC,		0 },
  { spDETECTPOISON,		0 },
  { spDETECTUNDEAD,		1 },
  { spDICTUM,		7 },
  { spDIMENSIONALANCHOR,		4 },
  { spDIMENSIONALLOCK,		8 },
  { spDISCERNLIES,		4 },
  { spDISCERNLOCATION,		8 },
  { spDISMISSAL,		4 },
  { spDISPELCHAOS,		5 },
  { spDISPELEVIL,		5 },
  { spDISPELGOOD,		5 },
  { spDISPELLAW,		5 },
  { spDISPELMAGIC,		3 },
  { spDISPELMAGICGREATER,		6 },
  { spDISRUPTINGWEAPON,		5 },
  { spDIVINATION,		4 },
  { spDIVINEFAVOR,		1 },
  { spDIVINEPOWER,		4 },
  { spDOOM,		1 },
  { spEAGLESSPLENDOR,		2 },
  { spEAGLESSPLENDORMASS,		6 },
  { spEARTHQUAKE,		8 },
  { spENDUREELEMENTS,		1 },
  { spENERGYDRAIN,		9 },
  { spENTHRALL,		2 },
  { spENTROPICSHIELD,		1 },
  { spETHEREALJAUNT,		7 },
  { spETHEREALNESS,		9 },
  { spFINDTHEPATH,		6 },
  { spFINDTRAPS,		2 },
  { spFIRESTORM,		8 },
  { spFLAMESTRIKE,		5 },
  { spFORBIDDANCE,		6 },
  { spFREEDOMOFMOVEMENT,		4 },
  { spGATE,		9 },
  { spGEASQUEST,		6 },
  { spGENTLEREPOSE,		2 },
  { spGIANTVERMIN,		4 },
  { spGLYPHOFWARDING,		3 },
  { spGLYPHOFWARDINGGREATER,		6 },
  { spGUIDANCE,		0 },
  { spHALLOW,		5 },
  { spHARM,		6 },
  { spHEAL,		6 },
  { spHEALMASS,		9 },
  { spHELPINGHAND,		3 },
  { spHEROESFEAST,		6 },
  { spHIDEFROMUNDEAD,		1 },
  { spHOLDPERSON,		2 },
  { spHOLYAURA,		8 },
  { spHOLYWORD,		7 },
  { spIMBUEWITHSPELLABILITY,		4 },
  { spIMPLOSION,		9 },
  { spINFLICTCRITICALWOUNDS,		4 },
  { spINFLICTCRITICALWOUNDSMASS,		8 },
  { spINFLICTLIGHTWOUNDS,		1 },
  { spINFLICTLIGHTWOUNDSMASS,		5 },
  { spINFLICTMINORWOUNDS,		0 },
  { spINFLICTMODERATEWOUNDS,		2 },
  { spINFLICTMODERATEWOUNDSMASS,		6 },
  { spINFLICTSERIOUSWOUNDS,		3 },
  { spINFLICTSERIOUSWOUNDSMASS,		7 },
  { spINSECTPLAGUE,		5 },
  { spINVISIBILITYPURGE,		3 },
  { spLIGHT,		0 },
  { spLOCATEOBJECT,		3 },
  { spMAGICCIRCLEAGAINSTCHAOS,		3 },
  { spMAGICCIRCLEAGAINSTEVIL,		3 },
  { spMAGICCIRCLEAGAINSTGOOD,		3 },
  { spMAGICCIRCLEAGAINSTLAW,		3 },
  { spMAGICSTONE,		1 },
  { spMAGICVESTMENT,		3 },
  { spMAGICWEAPON,		1 },
  { spMAGICWEAPONGREATER,		4 },
  { spMAKEWHOLE,		2 },
  { spMARKOFJUSTICE,		5 },
  { spMELDINTOSTONE,		3 },
  { spMENDING,		0 },
  { spMIRACLE,		9 },
  { spNEUTRALIZEPOISON,		4 },
  { spOBSCUREOBJECT,		3 },
  { spOBSCURINGMIST,		1 },
  { spOWLSWISDOM,		2 },
  { spOWLSWISDOMMASS,		6 },
  { spPLANARALLY,		6 },
  { spPLANARALLYGREATER,		8 },
  { spPLANARALLYLESSER,		4 },
  { spPLANESHIFT,		5 },
  { spPOISON,		4 },
  { spPRAYER,		3 },
  { spPROTECTIONFROMCHAOS,		1 },
  { spPROTECTIONFROMENERGY,		3 },
  { spPROTECTIONFROMEVIL,		1 },
  { spPROTECTIONFROMGOOD,		1 },
  { spPROTECTIONFROMLAW,		1 },
  { spPURIFYFOODANDDRINK,		0 },
  { spRAISEDEAD,		5 },
  { spREADMAGIC,		0 },
  { spREFUGE,		7 },
  { spREGENERATE,		7 },
  { spREMOVEBLINDNESSDEAFNESS,		3 },
  { spREMOVECURSE,		3 },
  { spREMOVEDISEASE,		3 },
  { spREMOVEFEAR,		1 },
  { spREMOVEPARALYSIS,		2 },
  { spREPELVERMIN,		4 },
  { spREPULSION,		7 },
  { spRESISTANCE,		0 },
  { spRESISTENERGY,		2 },
  { spRESTORATION,		4 },
  { spRESTORATIONGREATER,		7 },
  { spRESTORATIONLESSER,		2 },
  { spRESURRECTION,		7 },
  { spRIGHTEOUSMIGHT,		5 },
  { spSANCTUARY,		1 },
  { spSCRYING,		5 },
  { spSCRYINGGREATER,		7 },
  { spSEARINGLIGHT,		3 },
  { spSENDING,		4 },
  { spSHATTER,		2 },
  { spSHIELDOFFAITH,		1 },
  { spSHIELDOFLAW,		8 },
  { spSHIELDOTHER,		2 },
  { spSILENCE,		2 },
  { spSLAYLIVING,		5 },
  { spSOULBIND,		9 },
  { spSOUNDBURST,		2 },
  { spSPEAKWITHDEAD,		3 },
  { spSPELLIMMUNITY,		4 },
  { spSPELLIMMUNITYGREATER,		8 },
  { spSPELLRESISTANCE,		5 },
  { spSPIRITUALWEAPON,		2 },
  { spSTATUS,		2 },
  { spSTONESHAPE,		3 },
  { spSTORMOFVENGEANCE,		9 },
  { spSUMMONMONSTERI,		1 },
  { spSUMMONMONSTERII,		2 },
  { spSUMMONMONSTERIII,		3 },
  { spSUMMONMONSTERIV,		4 },
  { spSUMMONMONSTERIX,		9 },
  { spSUMMONMONSTERV,		5 },
  { spSUMMONMONSTERVI,		6 },
  { spSUMMONMONSTERVII,		7 },
  { spSUMMONMONSTERVIII,		8 },
  { spSYMBOLOFDEATH,		8 },
  { spSYMBOLOFFEAR,		6 },
  { spSYMBOLOFINSANITY,		8 },
  { spSYMBOLOFPAIN,		5 },
  { spSYMBOLOFPERSUASION,		6 },
  { spSYMBOLOFSLEEP,		5 },
  { spSYMBOLOFSTUNNING,		7 },
  { spSYMBOLOFWEAKNESS,		7 },
  { spTONGUES,		4 },
  { spTRUERESURRECTION,		9 },
  { spTRUESEEING,		5 },
  { spUNDEATHTODEATH,		6 },
  { spUNDETECTABLEALIGNMENT,		2 },
  { spUNHALLOW,		5 },
  { spUNHOLYAURA,		8 },
  { spVIRTUE,		0 },
  { spWALLOFSTONE,		5 },
  { spWATERBREATHING,		3 },
  { spWATERWALK,		3 },
  { spWINDWALK,		6 },
  { spWINDWALL,		3 },
  { spWORDOFCHAOS,		7 },
  { spWORDOFRECALL,		6 },
  { spZONEOFTRUTH,		2 },
  { 0, 0 }
};

static SPELLSFORCLASS s_Death[] = {
  { spANIMATEDEAD,		3 },
  { spCAUSEFEAR,		1 },
  { spCREATEGREATERUNDEAD,		8 },
  { spCREATEUNDEAD,		6 },
  { spDEATHKNELL,		2 },
  { spDEATHWARD,		4 },
  { spDESTRUCTION,		7 },
  { spSLAYLIVING,		5 },
  { spWAILOFTHEBANSHEE,		9 },
  { 0, 0 }
};

static SPELLSFORCLASS s_Destruction[] = {
  { spCONTAGION,		3 },
  { spDISINTEGRATE,		7 },
  { spEARTHQUAKE,		8 },
  { spHARM,		6 },
  { spIMPLOSION,		9 },
  { spINFLICTCRITICALWOUNDS,		4 },
  { spINFLICTLIGHTWOUNDS,		1 },
  { spINFLICTLIGHTWOUNDSMASS,		5 },
  { spSHATTER,		2 },
  { 0, 0 }
};

static SPELLSFORCLASS s_Druid[] = {
  { spAIRWALK,		4 },
  { spANIMALGROWTH,		5 },
  { spANIMALMESSENGER,		2 },
  { spANIMALSHAPES,		8 },
  { spANIMALTRANCE,		2 },
  { spANIMATEPLANTS,		7 },
  { spANTILIFESHELL,		6 },
  { spANTIPATHY,		9 },
  { spANTIPLANTSHELL,		4 },
  { spATONEMENT,		5 },
  { spAWAKEN,		5 },
  { spBALEFULPOLYMORPH,		5 },
  { spBARKSKIN,		2 },
  { spBEARSENDURANCE,		2 },
  { spBEARSENDURANCEMASS,		6 },
  { spBLIGHT,		4 },
  { spBULLSSTRENGTH,		2 },
  { spBULLSSTRENGTHMASS,		6 },
  { spCALLLIGHTNING,		3 },
  { spCALLLIGHTNINGSTORM,		5 },
  { spCALMANIMALS,		1 },
  { spCATSGRACE,		2 },
  { spCATSGRACEMASS,		6 },
  { spCHANGESTAFF,		7 },
  { spCHARMANIMAL,		1 },
  { spCHILLMETAL,		2 },
  { spCOMMANDPLANTS,		4 },
  { spCOMMUNEWITHNATURE,		5 },
  { spCONTAGION,		3 },
  { spCONTROLPLANTS,		8 },
  { spCONTROLWATER,		4 },
  { spCONTROLWEATHER,		7 },
  { spCONTROLWINDS,		5 },
  { spCREATEWATER,		0 },
  { spCREEPINGDOOM,		7 },
  { spCURECRITICALWOUNDS,		5 },
  { spCURECRITICALWOUNDSMASS,		9 },
  { spCURELIGHTWOUNDS,		1 },
  { spCURELIGHTWOUNDSMASS,		6 },
  { spCUREMINORWOUNDS,		0 },
  { spCUREMODERATEWOUNDS,		3 },
  { spCUREMODERATEWOUNDSMASS,		7 },
  { spCURESERIOUSWOUNDS,		4 },
  { spCURESERIOUSWOUNDSMASS,		8 },
  { spDAYLIGHT,		3 },
  { spDEATHWARD,		5 },
  { spDELAYPOISON,		2 },
  { spDETECTANIMALSORPLANTS,		1 },
  { spDETECTMAGIC,		0 },
  { spDETECTPOISON,		0 },
  { spDETECTSNARESANDPITS,		1 },
  { spDIMINISHPLANTS,		3 },
  { spDISPELMAGIC,		4 },
  { spDISPELMAGICGREATER,		6 },
  { spDOMINATEANIMAL,		3 },
  { spEARTHQUAKE,		8 },
  { spELEMENTALSWARM,		9 },
  { spENDUREELEMENTS,		1 },
  { spENTANGLE,		1 },
  { spFAERIEFIRE,		1 },
  { spFINDTHEPATH,		6 },
  { spFINGEROFDEATH,		8 },
  { spFIRESEEDS,		6 },
  { spFIRESTORM,		7 },
  { spFIRETRAP,		2 },
  { spFLAMEBLADE,		2 },
  { spFLAMESTRIKE,		4 },
  { spFLAMINGSPHERE,		2 },
  { spFLARE,		0 },
  { spFOGCLOUD,		2 },
  { spFORESIGHT,		9 },
  { spFREEDOMOFMOVEMENT,		4 },
  { spGIANTVERMIN,		4 },
  { spGOODBERRY,		1 },
  { spGUIDANCE,		0 },
  { spGUSTOFWIND,		2 },
  { spHALLOW,		5 },
  { spHEAL,		7 },
  { spHEATMETAL,		2 },
  { spHIDEFROMANIMALS,		1 },
  { spHOLDANIMAL,		2 },
  { spICESTORM,		4 },
  { spINSECTPLAGUE,		5 },
  { spIRONWOOD,		6 },
  { spJUMP,		1 },
  { spKNOWDIRECTION,		0 },
  { spLIGHT,		0 },
  { spLIVEOAK,		6 },
  { spLONGSTRIDER,		1 },
  { spMAGICFANG,		1 },
  { spMAGICFANGGREATER,		3 },
  { spMAGICSTONE,		1 },
  { spMELDINTOSTONE,		3 },
  { spMENDING,		0 },
  { spMOVEEARTH,		6 },
  { spNEUTRALIZEPOISON,		3 },
  { spOBSCURINGMIST,		1 },
  { spOWLSWISDOM,		2 },
  { spOWLSWISDOMMASS,		6 },
  { spPASSWITHOUTTRACE,		1 },
  { spPLANTGROWTH,		3 },
  { spPOISON,		3 },
  { spPRODUCEFLAME,		1 },
  { spPROTECTIONFROMENERGY,		3 },
  { spPURIFYFOODANDDRINK,		0 },
  { spQUENCH,		3 },
  { spREADMAGIC,		0 },
  { spREDUCEANIMAL,		2 },
  { spREGENERATE,		9 },
  { spREINCARNATE,		4 },
  { spREMOVEDISEASE,		3 },
  { spREPELMETALORSTONE,		8 },
  { spREPELVERMIN,		4 },
  { spREPELWOOD,		6 },
  { spRESISTANCE,		0 },
  { spRESISTENERGY,		2 },
  { spRESTORATIONLESSER,		2 },
  { spREVERSEGRAVITY,		8 },
  { spRUSTINGGRASP,		4 },
  { spSCRYING,		4 },
  { spSCRYINGGREATER,		7 },
  { spSHAMBLER,		9 },
  { spSHAPECHANGE,		9 },
  { spSHILLELAGH,		1 },
  { spSLEETSTORM,		3 },
  { spSNARE,		3 },
  { spSOFTENEARTHANDSTONE,		2 },
  { spSPEAKWITHANIMALS,		1 },
  { spSPEAKWITHPLANTS,		3 },
  { spSPELLSTAFF,		6 },
  { spSPIDERCLIMB,		2 },
  { spSPIKEGROWTH,		3 },
  { spSPIKESTONES,		4 },
  { spSTONESHAPE,		3 },
  { spSTONESKIN,		5 },
  { spSTONETELL,		6 },
  { spSTORMOFVENGEANCE,		9 },
  { spSUMMONNATURESALLYI,		1 },
  { spSUMMONNATURESALLYII,		2 },
  { spSUMMONNATURESALLYIII,		3 },
  { spSUMMONNATURESALLYIV,		4 },
  { spSUMMONNATURESALLYIX,		9 },
  { spSUMMONNATURESALLYV,		5 },
  { spSUMMONNATURESALLYVI,		6 },
  { spSUMMONNATURESALLYVII,		7 },
  { spSUMMONNATURESALLYVIII,		8 },
  { spSUMMONSWARM,		2 },
  { spSUNBEAM,		7 },
  { spSUNBURST,		8 },
  { spSYMPATHY,		9 },
  { spTRANSMUTEMETALTOWOOD,		7 },
  { spTRANSMUTEMUDTOROCK,		5 },
  { spTRANSMUTEROCKTOMUD,		5 },
  { spTRANSPORTVIAPLANTS,		6 },
  { spTREESHAPE,		2 },
  { spTREESTRIDE,		5 },
  { spTRUESEEING,		7 },
  { spUNHALLOW,		5 },
  { spVIRTUE,		0 },
  { spWALLOFFIRE,		5 },
  { spWALLOFSTONE,		6 },
  { spWALLOFTHORNS,		5 },
  { spWARPWOOD,		2 },
  { spWATERBREATHING,		3 },
  { spWHIRLWIND,		8 },
  { spWINDWALK,		7 },
  { spWINDWALL,		3 },
  { spWOODSHAPE,		2 },
  { spWORDOFRECALL,		8 },
  { 0, 0 }
};

static SPELLSFORCLASS s_Earth[] = {
  { spEARTHQUAKE,		7 },
  { spELEMENTALSWARM,		9 },
  { spIRONBODY,		8 },
  { spMAGICSTONE,		1 },
  { spSOFTENEARTHANDSTONE,		2 },
  { spSPIKESTONES,		4 },
  { spSTONESHAPE,		3 },
  { spSTONESKIN,		6 },
  { spWALLOFSTONE,		5 },
  { 0, 0 }
};

static SPELLSFORCLASS s_Evil[] = {
  { spBLASPHEMY,		7 },
  { spCREATEUNDEAD,		6 },
  { spDESECRATE,		2 },
  { spDISPELGOOD,		5 },
  { spMAGICCIRCLEAGAINSTGOOD,		3 },
  { spPROTECTIONFROMGOOD,		1 },
  { spSUMMONMONSTERIX,		9 },
  { spUNHOLYAURA,		8 },
  { spUNHOLYBLIGHT,		4 },
  { 0, 0 }
};

static SPELLSFORCLASS s_Fire[] = {
  { spBURNINGHANDS,		1 },
  { spELEMENTALSWARM,		9 },
  { spFIRESEEDS,		6 },
  { spFIRESHIELD,		5 },
  { spFIRESTORM,		7 },
  { spINCENDIARYCLOUD,		8 },
  { spPRODUCEFLAME,		2 },
  { spRESISTENERGY,		3 },
  { spWALLOFFIRE,		4 },
  { 0, 0 }
};

static SPELLSFORCLASS s_Good[] = {
  { spAID,		2 },
  { spBLADEBARRIER,		6 },
  { spDISPELEVIL,		5 },
  { spHOLYAURA,		8 },
  { spHOLYSMITE,		4 },
  { spHOLYWORD,		7 },
  { spMAGICCIRCLEAGAINSTEVIL,		3 },
  { spPROTECTIONFROMEVIL,		1 },
  { spSUMMONMONSTERIX,		9 },
  { 0, 0 }
};

static SPELLSFORCLASS s_Healing[] = {
  { spCURECRITICALWOUNDS,		4 },
  { spCURECRITICALWOUNDSMASS,		8 },
  { spCURELIGHTWOUNDS,		1 },
  { spCURELIGHTWOUNDSMASS,		5 },
  { spCUREMODERATEWOUNDS,		2 },
  { spCURESERIOUSWOUNDS,		3 },
  { spHEAL,		6 },
  { spHEALMASS,		9 },
  { spREGENERATE,		7 },
  { 0, 0 }
};

static SPELLSFORCLASS s_Knowledge[] = {
  { spCLAIRAUDIENCECLAIRVOYANCE,		3 },
  { spDETECTSECRETDOORS,		1 },
  { spDETECTTHOUGHTS,		2 },
  { spDISCERNLOCATION,		8 },
  { spDIVINATION,		4 },
  { spFINDTHEPATH,		6 },
  { spFORESIGHT,		9 },
  { spLEGENDLORE,		7 },
  { spTRUESEEING,		5 },
  { 0, 0 }
};

static SPELLSFORCLASS s_Law[] = {
  { spCALMEMOTIONS,		2 },
  { spDICTUM,		7 },
  { spDISPELCHAOS,		5 },
  { spHOLDMONSTER,		6 },
  { spMAGICCIRCLEAGAINSTCHAOS,		3 },
  { spORDERSWRATH,		4 },
  { spPROTECTIONFROMCHAOS,		1 },
  { spSHIELDOFLAW,		8 },
  { spSUMMONMONSTERIX,		9 },
  { 0, 0 }
};

static SPELLSFORCLASS s_Luck[] = {
  { spAID,		2 },
  { spBREAKENCHANTMENT,		5 },
  { spENTROPICSHIELD,		1 },
  { spFREEDOMOFMOVEMENT,		4 },
  { spMIRACLE,		9 },
  { spMISLEAD,		6 },
  { spMOMENTOFPRESCIENCE,		8 },
  { spPROTECTIONFROMENERGY,		3 },
  { spSPELLTURNING,		7 },
  { 0, 0 }
};

static SPELLSFORCLASS s_Magic[] = {
  { spANTIMAGICFIELD,		6 },
  { spDISPELMAGIC,		3 },
  { spIDENTIFY,		2 },
  { spIMBUEWITHSPELLABILITY,		4 },
  { spMAGESDISJUNCTION,		9 },
  { spMAGICAURA,		1 },
  { spPROTECTIONFROMSPELLS,		8 },
  { spSPELLRESISTANCE,		5 },
  { spSPELLTURNING,		7 },
  { 0, 0 }
};

static SPELLSFORCLASS s_Paladin[] = {
  { spBLESS,		1 },
  { spBLESSWATER,		1 },
  { spBLESSWEAPON,		1 },
  { spBREAKENCHANTMENT,		4 },
  { spBULLSSTRENGTH,		2 },
  { spCREATEWATER,		1 },
  { spCURELIGHTWOUNDS,		1 },
  { spCUREMODERATEWOUNDS,		3 },
  { spCURESERIOUSWOUNDS,		4 },
  { spDAYLIGHT,		3 },
  { spDEATHWARD,		4 },
  { spDELAYPOISON,		2 },
  { spDETECTPOISON,		1 },
  { spDETECTUNDEAD,		1 },
  { spDISCERNLIES,		3 },
  { spDISPELCHAOS,		4 },
  { spDISPELEVIL,		4 },
  { spDISPELMAGIC,		3 },
  { spDIVINEFAVOR,		1 },
  { spEAGLESSPLENDOR,		2 },
  { spENDUREELEMENTS,		1 },
  { spHEALMOUNT,		3 },
  { spHOLYSWORD,		4 },
  { spMAGICCIRCLEAGAINSTCHAOS,		3 },
  { spMAGICCIRCLEAGAINSTEVIL,		3 },
  { spMAGICWEAPON,		1 },
  { spMAGICWEAPONGREATER,		3 },
  { spMARKOFJUSTICE,		4 },
  { spNEUTRALIZEPOISON,		4 },
  { spOWLSWISDOM,		2 },
  { spPRAYER,		3 },
  { spPROTECTIONFROMCHAOS,		1 },
  { spPROTECTIONFROMEVIL,		1 },
  { spREADMAGIC,		1 },
  { spREMOVEBLINDNESSDEAFNESS,		3 },
  { spREMOVECURSE,		3 },
  { spREMOVEPARALYSIS,		2 },
  { spRESISTANCE,		1 },
  { spRESISTENERGY,		2 },
  { spRESTORATION,		4 },
  { spRESTORATIONLESSER,		1 },
  { spSHIELDOTHER,		2 },
  { spUNDETECTABLEALIGNMENT,		2 },
  { spVIRTUE,		1 },
  { spZONEOFTRUTH,		2 },
  { 0, 0 }
};

static SPELLSFORCLASS s_Plant[] = {
  { spANIMATEPLANTS,		7 },
  { spBARKSKIN,		2 },
  { spCOMMANDPLANTS,		4 },
  { spCONTROLPLANTS,		8 },
  { spENTANGLE,		1 },
  { spPLANTGROWTH,		3 },
  { spREPELWOOD,		6 },
  { spSHAMBLER,		9 },
  { spWALLOFTHORNS,		5 },
  { 0, 0 }
};

static SPELLSFORCLASS s_Protection[] = {
  { spANTIMAGICFIELD,		6 },
  { spMINDBLANK,		8 },
  { spPRISMATICSPHERE,		9 },
  { spPROTECTIONFROMENERGY,		3 },
  { spREPULSION,		7 },
  { spSANCTUARY,		1 },
  { spSHIELDOTHER,		2 },
  { spSPELLIMMUNITY,		4 },
  { spSPELLRESISTANCE,		5 },
  { 0, 0 }
};

static SPELLSFORCLASS s_Ranger[] = {
  { spALARM,		1 },
  { spANIMALGROWTH,		4 },
  { spANIMALMESSENGER,		1 },
  { spBARKSKIN,		2 },
  { spBEARSENDURANCE,		2 },
  { spCALMANIMALS,		1 },
  { spCATSGRACE,		2 },
  { spCHARMANIMAL,		1 },
  { spCOMMANDPLANTS,		3 },
  { spCOMMUNEWITHNATURE,		4 },
  { spCURELIGHTWOUNDS,		2 },
  { spCUREMODERATEWOUNDS,		3 },
  { spCURESERIOUSWOUNDS,		4 },
  { spDARKVISION,		3 },
  { spDELAYPOISON,		1 },
  { spDETECTANIMALSORPLANTS,		1 },
  { spDETECTPOISON,		1 },
  { spDETECTSNARESANDPITS,		1 },
  { spDIMINISHPLANTS,		3 },
  { spENDUREELEMENTS,		1 },
  { spENTANGLE,		1 },
  { spFREEDOMOFMOVEMENT,		4 },
  { spHIDEFROMANIMALS,		1 },
  { spHOLDANIMAL,		2 },
  { spJUMP,		1 },
  { spLONGSTRIDER,		1 },
  { spMAGICFANG,		1 },
  { spMAGICFANGGREATER,		3 },
  { spNEUTRALIZEPOISON,		3 },
  { spNONDETECTION,		4 },
  { spOWLSWISDOM,		2 },
  { spPASSWITHOUTTRACE,		1 },
  { spPLANTGROWTH,		3 },
  { spPROTECTIONFROMENERGY,		2 },
  { spREADMAGIC,		1 },
  { spREDUCEANIMAL,		3 },
  { spREMOVEDISEASE,		3 },
  { spREPELVERMIN,		3 },
  { spRESISTENERGY,		1 },
  { spSNARE,		2 },
  { spSPEAKWITHANIMALS,		1 },
  { spSPEAKWITHPLANTS,		2 },
  { spSPIKEGROWTH,		2 },
  { spSUMMONNATURESALLYI,		1 },
  { spSUMMONNATURESALLYII,		2 },
  { spSUMMONNATURESALLYIII,		3 },
  { spSUMMONNATURESALLYIV,		4 },
  { spTREESHAPE,		3 },
  { spTREESTRIDE,		4 },
  { spWATERWALK,		3 },
  { spWINDWALL,		2 },
  { 0, 0 }
};

static SPELLSFORCLASS s_Sorcerer[] = {
  { spACIDARROW,		2 },
  { spACIDFOG,		6 },
  { spACIDSPLASH,		0 },
  { spALARM,		1 },
  { spALTERSELF,		2 },
  { spANALYZEDWEOMER,		6 },
  { spANIMALGROWTH,		5 },
  { spANIMATEDEAD,		4 },
  { spANIMATEROPE,		1 },
  { spANTIMAGICFIELD,		6 },
  { spANTIPATHY,		8 },
  { spARCANEEYE,		4 },
  { spARCANELOCK,		2 },
  { spARCANEMARK,		0 },
  { spARCANESIGHT,		3 },
  { spARCANESIGHTGREATER,		7 },
  { spASTRALPROJECTION,		9 },
  { spBALEFULPOLYMORPH,		5 },
  { spBANISHMENT,		7 },
  { spBEARSENDURANCE,		2 },
  { spBEARSENDURANCEMASS,		6 },
  { spBESTOWCURSE,		4 },
  { spBINDING,		8 },
  { spBLACKTENTACLES,		4 },
  { spBLIGHT,		5 },
  { spBLINDNESSDEAFNESS,		2 },
  { spBLINK,		3 },
  { spBLUR,		2 },
  { spBREAKENCHANTMENT,		5 },
  { spBULLSSTRENGTH,		2 },
  { spBULLSSTRENGTHMASS,		6 },
  { spBURNINGHANDS,		1 },
  { spCATSGRACE,		2 },
  { spCATSGRACEMASS,		6 },
  { spCAUSEFEAR,		1 },
  { spCHAINLIGHTNING,		6 },
  { spCHARMMONSTER,		4 },
  { spCHARMMONSTERMASS,		8 },
  { spCHARMPERSON,		1 },
  { spCHILLTOUCH,		1 },
  { spCIRCLEOFDEATH,		6 },
  { spCLAIRAUDIENCECLAIRVOYANCE,		3 },
  { spCLENCHEDFIST,		8 },
  { spCLONE,		8 },
  { spCLOUDKILL,		5 },
  { spCOLORSPRAY,		1 },
  { spCOMMANDUNDEAD,		2 },
  { spCOMPREHENDLANGUAGES,		1 },
  { spCONEOFCOLD,		5 },
  { spCONFUSION,		4 },
  { spCONTACTOTHERPLANE,		5 },
  { spCONTAGION,		4 },
  { spCONTINGENCY,		6 },
  { spCONTINUALFLAME,		2 },
  { spCONTROLUNDEAD,		7 },
  { spCONTROLWATER,		6 },
  { spCONTROLWEATHER,		7 },
  { spCREATEGREATERUNDEAD,		8 },
  { spCREATEUNDEAD,		6 },
  { spCRUSHINGDESPAIR,		4 },
  { spCRUSHINGHAND,		9 },
  { spDANCINGLIGHTS,		0 },
  { spDARKNESS,		2 },
  { spDARKVISION,		2 },
  { spDAYLIGHT,		3 },
  { spDAZE,		0 },
  { spDAZEMONSTER,		2 },
  { spDEEPSLUMBER,		3 },
  { spDELAYEDBLASTFIREBALL,		7 },
  { spDEMAND,		8 },
  { spDETECTMAGIC,		0 },
  { spDETECTPOISON,		0 },
  { spDETECTSCRYING,		4 },
  { spDETECTSECRETDOORS,		1 },
  { spDETECTTHOUGHTS,		2 },
  { spDETECTUNDEAD,		1 },
  { spDIMENSIONALANCHOR,		4 },
  { spDIMENSIONALLOCK,		8 },
  { spDIMENSIONDOOR,		4 },
  { spDISCERNLOCATION,		8 },
  { spDISGUISESELF,		1 },
  { spDISINTEGRATE,		6 },
  { spDISMISSAL,		5 },
  { spDISPELMAGIC,		3 },
  { spDISPELMAGICGREATER,		6 },
  { spDISPLACEMENT,		3 },
  { spDISRUPTUNDEAD,		0 },
  { spDOMINATEMONSTER,		9 },
  { spDOMINATEPERSON,		5 },
  { spDREAM,		5 },
  { spEAGLESSPLENDOR,		2 },
  { spEAGLESSPLENDORMASS,		6 },
  { spENDUREELEMENTS,		1 },
  { spENERGYDRAIN,		9 },
  { spENERVATION,		4 },
  { spENLARGEPERSON,		1 },
  { spENLARGEPERSONMASS,		4 },
  { spERASE,		1 },
  { spETHEREALJAUNT,		7 },
  { spETHEREALNESS,		9 },
  { spEXPEDITIOUSRETREAT,		1 },
  { spEXPLOSIVERUNES,		3 },
  { spEYEBITE,		6 },
  { spFABRICATE,		5 },
  { spFALSELIFE,		2 },
  { spFALSEVISION,		5 },
  { spFEAR,		4 },
  { spFEATHERFALL,		1 },
  { spFEEBLEMIND,		5 },
  { spFINGEROFDEATH,		7 },
  { spFIREBALL,		3 },
  { spFIRESHIELD,		4 },
  { spFIRETRAP,		4 },
  { spFLAMEARROW,		3 },
  { spFLAMINGSPHERE,		2 },
  { spFLARE,		0 },
  { spFLESHTOSTONE,		6 },
  { spFLOATINGDISK,		1 },
  { spFLY,		3 },
  { spFOGCLOUD,		2 },
  { spFORCECAGE,		7 },
  { spFORCEFULHAND,		6 },
  { spFORESIGHT,		9 },
  { spFOXSCUNNING,		2 },
  { spFOXSCUNNINGMASS,		6 },
  { spFREEDOM,		9 },
  { spFREEZINGSPHERE,		6 },
  { spGASEOUSFORM,		3 },
  { spGATE,		9 },
  { spGEASLESSER,		4 },
  { spGEASQUEST,		6 },
  { spGENTLEREPOSE,		3 },
  { spGHOSTSOUND,		0 },
  { spGHOULTOUCH,		2 },
  { spGLITTERDUST,		2 },
  { spGLOBEOFINVULNERABILITY,		6 },
  { spGLOBEOFINVULNERABILITYLESSER,		4 },
  { spGRASPINGHAND,		7 },
  { spGREASE,		1 },
  { spGUARDSANDWARDS,		6 },
  { spGUSTOFWIND,		2 },
  { spHALLUCINATORYTERRAIN,		4 },
  { spHALTUNDEAD,		3 },
  { spHASTE,		3 },
  { spHEROISM,		3 },
  { spHEROISMGREATER,		6 },
  { spHIDEOUSLAUGHTER,		2 },
  { spHOLDMONSTER,		5 },
  { spHOLDMONSTERMASS,		9 },
  { spHOLDPERSON,		3 },
  { spHOLDPERSONMASS,		7 },
  { spHOLDPORTAL,		1 },
  { spHORRIDWILTING,		8 },
  { spHYPNOTICPATTERN,		2 },
  { spHYPNOTISM,		1 },
  { spICESTORM,		4 },
  { spIDENTIFY,		1 },
  { spILLUSORYSCRIPT,		3 },
  { spILLUSORYWALL,		4 },
  { spIMPRISONMENT,		9 },
  { spINCENDIARYCLOUD,		8 },
  { spINSANITY,		7 },
  { spINSTANTSUMMONS,		7 },
  { spINTERPOSINGHAND,		5 },
  { spINVISIBILITY,		2 },
  { spINVISIBILITYGREATER,		4 },
  { spINVISIBILITYMASS,		7 },
  { spINVISIBILITYSPHERE,		3 },
  { spIRONBODY,		8 },
  { spIRRESISTIBLEDANCE,		8 },
  { spJUMP,		1 },
  { spKEENEDGE,		3 },
  { spKNOCK,		2 },
  { spLEGENDLORE,		6 },
  { spLEVITATE,		2 },
  { spLIGHT,		0 },
  { spLIGHTNINGBOLT,		3 },
  { spLIMITEDWISH,		7 },
  { spLOCATECREATURE,		4 },
  { spLOCATEOBJECT,		2 },
  { spMAGEARMOR,		1 },
  { spMAGEHAND,		0 },
  { spMAGESDISJUNCTION,		9 },
  { spMAGESFAITHFULHOUND,		5 },
  { spMAGESMAGNIFICENTMANSION,		7 },
  { spMAGESPRIVATESANCTUM,		5 },
  { spMAGESSWORD,		7 },
  { spMAGICAURA,		1 },
  { spMAGICCIRCLEAGAINSTCHAOS,		3 },
  { spMAGICCIRCLEAGAINSTEVIL,		3 },
  { spMAGICCIRCLEAGAINSTGOOD,		3 },
  { spMAGICCIRCLEAGAINSTLAW,		3 },
  { spMAGICJAR,		5 },
  { spMAGICMISSILE,		1 },
  { spMAGICMOUTH,		2 },
  { spMAGICWEAPON,		1 },
  { spMAGICWEAPONGREATER,		3 },
  { spMAJORCREATION,		5 },
  { spMAJORIMAGE,		3 },
  { spMAZE,		8 },
  { spMENDING,		0 },
  { spMESSAGE,		0 },
  { spMETEORSWARM,		9 },
  { spMINDBLANK,		8 },
  { spMINDFOG,		5 },
  { spMINORCREATION,		4 },
  { spMINORIMAGE,		2 },
  { spMIRAGEARCANA,		5 },
  { spMIRRORIMAGE,		2 },
  { spMISDIRECTION,		2 },
  { spMISLEAD,		6 },
  { spMOMENTOFPRESCIENCE,		8 },
  { spMOUNT,		1 },
  { spMOVEEARTH,		6 },
  { spNIGHTMARE,		5 },
  { spNONDETECTION,		3 },
  { spOBSCUREOBJECT,		2 },
  { spOBSCURINGMIST,		1 },
  { spOPENCLOSE,		0 },
  { spOVERLANDFLIGHT,		5 },
  { spOWLSWISDOM,		2 },
  { spOWLSWISDOMMASS,		6 },
  { spPASSWALL,		5 },
  { spPERMANENCY,		5 },
  { spPERMANENTIMAGE,		6 },
  { spPERSISTENTIMAGE,		5 },
  { spPHANTASMALKILLER,		4 },
  { spPHANTOMSTEED,		3 },
  { spPHANTOMTRAP,		2 },
  { spPHASEDOOR,		7 },
  { spPLANARBINDING,		6 },
  { spPLANARBINDINGGREATER,		8 },
  { spPLANARBINDINGLESSER,		5 },
  { spPLANESHIFT,		7 },
  { spPOLARRAY,		8 },
  { spPOLYMORPH,		4 },
  { spPOLYMORPHANYOBJECT,		8 },
  { spPOWERWORDBLIND,		7 },
  { spPOWERWORDKILL,		9 },
  { spPOWERWORDSTUN,		8 },
  { spPRESTIDIGITATION,		0 },
  { spPRISMATICSPHERE,		9 },
  { spPRISMATICSPRAY,		7 },
  { spPRISMATICWALL,		8 },
  { spPROGRAMMEDIMAGE,		6 },
  { spPROJECTIMAGE,		7 },
  { spPROTECTIONFROMARROWS,		2 },
  { spPROTECTIONFROMCHAOS,		1 },
  { spPROTECTIONFROMENERGY,		3 },
  { spPROTECTIONFROMEVIL,		1 },
  { spPROTECTIONFROMGOOD,		1 },
  { spPROTECTIONFROMLAW,		1 },
  { spPROTECTIONFROMSPELLS,		8 },
  { spPRYINGEYES,		5 },
  { spPRYINGEYESGREATER,		8 },
  { spPYROTECHNICS,		2 },
  { spRAGE,		3 },
  { spRAINBOWPATTERN,		4 },
  { spRAYOFENFEEBLEMENT,		1 },
  { spRAYOFEXHAUSTION,		3 },
  { spRAYOFFROST,		0 },
  { spREADMAGIC,		0 },
  { spREDUCEPERSON,		1 },
  { spREDUCEPERSONMASS,		4 },
  { spREFUGE,		9 },
  { spREMOVECURSE,		4 },
  { spREPULSION,		6 },
  { spRESILIENTSPHERE,		4 },
  { spRESISTANCE,		0 },
  { spRESISTENERGY,		2 },
  { spREVERSEGRAVITY,		7 },
  { spROPETRICK,		2 },
  { spSCARE,		2 },
  { spSCINTILLATINGPATTERN,		8 },
  { spSCORCHINGRAY,		2 },
  { spSCREEN,		8 },
  { spSCRYING,		4 },
  { spSCRYINGGREATER,		7 },
  { spSECRETCHEST,		5 },
  { spSECRETPAGE,		3 },
  { spSECURESHELTER,		4 },
  { spSEEINVISIBILITY,		2 },
  { spSEEMING,		5 },
  { spSENDING,		5 },
  { spSEPIASNAKESIGIL,		3 },
  { spSEQUESTER,		7 },
  { spSHADES,		9 },
  { spSHADOWCONJURATION,		4 },
  { spSHADOWCONJURATIONGREATER,		7 },
  { spSHADOWEVOCATION,		5 },
  { spSHADOWEVOCATIONGREATER,		8 },
  { spSHADOWWALK,		6 },
  { spSHAPECHANGE,		9 },
  { spSHATTER,		2 },
  { spSHIELD,		1 },
  { spSHOCKINGGRASP,		1 },
  { spSHOUT,		4 },
  { spSHOUTGREATER,		8 },
  { spSHRINKITEM,		3 },
  { spSILENTIMAGE,		1 },
  { spSIMULACRUM,		7 },
  { spSLEEP,		1 },
  { spSLEETSTORM,		3 },
  { spSLOW,		3 },
  { spSOLIDFOG,		4 },
  { spSOULBIND,		9 },
  { spSPECTRALHAND,		2 },
  { spSPELLTURNING,		7 },
  { spSPIDERCLIMB,		2 },
  { spSTATUE,		7 },
  { spSTINKINGCLOUD,		3 },
  { spSTONESHAPE,		5 },
  { spSTONESKIN,		4 },
  { spSTONETOFLESH,		6 },
  { spSUGGESTION,		3 },
  { spSUGGESTIONMASS,		6 },
  { spSUMMONMONSTERI,		1 },
  { spSUMMONMONSTERII,		2 },
  { spSUMMONMONSTERIII,		3 },
  { spSUMMONMONSTERIV,		4 },
  { spSUMMONMONSTERIX,		9 },
  { spSUMMONMONSTERV,		5 },
  { spSUMMONMONSTERVI,		6 },
  { spSUMMONMONSTERVII,		7 },
  { spSUMMONMONSTERVIII,		8 },
  { spSUMMONSWARM,		2 },
  { spSUNBURST,		8 },
  { spSYMBOLOFDEATH,		8 },
  { spSYMBOLOFFEAR,		6 },
  { spSYMBOLOFINSANITY,		8 },
  { spSYMBOLOFPAIN,		5 },
  { spSYMBOLOFPERSUASION,		6 },
  { spSYMBOLOFSLEEP,		5 },
  { spSYMBOLOFSTUNNING,		7 },
  { spSYMBOLOFWEAKNESS,		7 },
  { spSYMPATHY,		8 },
  { spTELEKINESIS,		5 },
  { spTELEKINETICSPHERE,		8 },
  { spTELEPATHICBOND,		5 },
  { spTELEPORT,		5 },
  { spTELEPORTATIONCIRCLE,		9 },
  { spTELEPORTGREATER,		7 },
  { spTELEPORTOBJECT,		7 },
  { spTEMPORALSTASIS,		8 },
  { spTIMESTOP,		9 },
  { spTINYHUT,		3 },
  { spTONGUES,		3 },
  { spTOUCHOFFATIGUE,		0 },
  { spTOUCHOFIDIOCY,		2 },
  { spTRANSFORMATION,		6 },
  { spTRANSMUTEMUDTOROCK,		5 },
  { spTRANSMUTEROCKTOMUD,		5 },
  { spTRAPTHESOUL,		8 },
  { spTRUESEEING,		6 },
  { spTRUESTRIKE,		1 },
  { spUNDEATHTODEATH,		6 },
  { spUNSEENSERVANT,		1 },
  { spVAMPIRICTOUCH,		3 },
  { spVEIL,		6 },
  { spVENTRILOQUISM,		1 },
  { spVISION,		7 },
  { spWAILOFTHEBANSHEE,		9 },
  { spWALLOFFIRE,		4 },
  { spWALLOFFORCE,		5 },
  { spWALLOFICE,		4 },
  { spWALLOFIRON,		6 },
  { spWALLOFSTONE,		5 },
  { spWATERBREATHING,		3 },
  { spWAVESOFEXHAUSTION,		7 },
  { spWAVESOFFATIGUE,		5 },
  { spWEB,		2 },
  { spWEIRD,		9 },
  { spWHISPERINGWIND,		2 },
  { spWINDWALL,		3 },
  { spWISH,		9 },
  { 0, 0 }
};

static SPELLSFORCLASS s_Strength[] = {
  { spBULLSSTRENGTH,		2 },
  { spCLENCHEDFIST,		8 },
  { spCRUSHINGHAND,		9 },
  { spENLARGEPERSON,		1 },
  { spGRASPINGHAND,		7 },
  { spMAGICVESTMENT,		3 },
  { spRIGHTEOUSMIGHT,		5 },
  { spSPELLIMMUNITY,		4 },
  { spSTONESKIN,		6 },
  { 0, 0 }
};

static SPELLSFORCLASS s_Sun[] = {
  { spENDUREELEMENTS,		1 },
  { spFIRESEEDS,		6 },
  { spFIRESHIELD,		4 },
  { spFLAMESTRIKE,		5 },
  { spHEATMETAL,		2 },
  { spPRISMATICSPHERE,		9 },
  { spSEARINGLIGHT,		3 },
  { spSUNBEAM,		7 },
  { spSUNBURST,		8 },
  { 0, 0 }
};

static SPELLSFORCLASS s_Travel[] = {
  { spASTRALPROJECTION,		9 },
  { spDIMENSIONDOOR,		4 },
  { spFINDTHEPATH,		6 },
  { spFLY,		3 },
  { spLOCATEOBJECT,		2 },
  { spLONGSTRIDER,		1 },
  { spPHASEDOOR,		8 },
  { spTELEPORT,		5 },
  { spTELEPORTGREATER,		7 },
  { 0, 0 }
};

static SPELLSFORCLASS s_Trickery[] = {
  { spCONFUSION,		4 },
  { spDISGUISESELF,		1 },
  { spFALSEVISION,		5 },
  { spINVISIBILITY,		2 },
  { spMISLEAD,		6 },
  { spNONDETECTION,		3 },
  { spPOLYMORPHANYOBJECT,		8 },
  { spSCREEN,		7 },
  { spTIMESTOP,		9 },
  { 0, 0 }
};

static SPELLSFORCLASS s_War[] = {
  { spBLADEBARRIER,		6 },
  { spDIVINEPOWER,		4 },
  { spFLAMESTRIKE,		5 },
  { spMAGICVESTMENT,		3 },
  { spMAGICWEAPON,		1 },
  { spPOWERWORDBLIND,		7 },
  { spPOWERWORDKILL,		9 },
  { spPOWERWORDSTUN,		8 },
  { spSPIRITUALWEAPON,		2 },
  { 0, 0 }
};

static SPELLSFORCLASS s_Water[] = {
  { spACIDFOG,		7 },
  { spCONEOFCOLD,		6 },
  { spCONTROLWATER,		4 },
  { spELEMENTALSWARM,		9 },
  { spFOGCLOUD,		2 },
  { spHORRIDWILTING,		8 },
  { spICESTORM,		5 },
  { spOBSCURINGMIST,		1 },
  { spWATERBREATHING,		3 },
  { 0, 0 }
};

static SPELLSFORCLASS s_Wizard[] = {
  { spACIDARROW,		2 },
  { spACIDFOG,		6 },
  { spACIDSPLASH,		0 },
  { spALARM,		1 },
  { spALTERSELF,		2 },
  { spANALYZEDWEOMER,		6 },
  { spANIMALGROWTH,		5 },
  { spANIMATEDEAD,		4 },
  { spANIMATEROPE,		1 },
  { spANTIMAGICFIELD,		6 },
  { spANTIPATHY,		8 },
  { spARCANEEYE,		4 },
  { spARCANELOCK,		2 },
  { spARCANEMARK,		0 },
  { spARCANESIGHT,		3 },
  { spARCANESIGHTGREATER,		7 },
  { spASTRALPROJECTION,		9 },
  { spBALEFULPOLYMORPH,		5 },
  { spBANISHMENT,		7 },
  { spBEARSENDURANCE,		2 },
  { spBEARSENDURANCEMASS,		6 },
  { spBESTOWCURSE,		4 },
  { spBINDING,		8 },
  { spBLACKTENTACLES,		4 },
  { spBLIGHT,		5 },
  { spBLINDNESSDEAFNESS,		2 },
  { spBLINK,		3 },
  { spBLUR,		2 },
  { spBREAKENCHANTMENT,		5 },
  { spBULLSSTRENGTH,		2 },
  { spBULLSSTRENGTHMASS,		6 },
  { spBURNINGHANDS,		1 },
  { spCATSGRACE,		2 },
  { spCATSGRACEMASS,		6 },
  { spCAUSEFEAR,		1 },
  { spCHAINLIGHTNING,		6 },
  { spCHARMMONSTER,		4 },
  { spCHARMMONSTERMASS,		8 },
  { spCHARMPERSON,		1 },
  { spCHILLTOUCH,		1 },
  { spCIRCLEOFDEATH,		6 },
  { spCLAIRAUDIENCECLAIRVOYANCE,		3 },
  { spCLENCHEDFIST,		8 },
  { spCLONE,		8 },
  { spCLOUDKILL,		5 },
  { spCOLORSPRAY,		1 },
  { spCOMMANDUNDEAD,		2 },
  { spCOMPREHENDLANGUAGES,		1 },
  { spCONEOFCOLD,		5 },
  { spCONFUSION,		4 },
  { spCONTACTOTHERPLANE,		5 },
  { spCONTAGION,		4 },
  { spCONTINGENCY,		6 },
  { spCONTINUALFLAME,		2 },
  { spCONTROLUNDEAD,		7 },
  { spCONTROLWATER,		6 },
  { spCONTROLWEATHER,		7 },
  { spCREATEGREATERUNDEAD,		8 },
  { spCREATEUNDEAD,		6 },
  { spCRUSHINGDESPAIR,		4 },
  { spCRUSHINGHAND,		9 },
  { spDANCINGLIGHTS,		0 },
  { spDARKNESS,		2 },
  { spDARKVISION,		2 },
  { spDAYLIGHT,		3 },
  { spDAZE,		0 },
  { spDAZEMONSTER,		2 },
  { spDEEPSLUMBER,		3 },
  { spDELAYEDBLASTFIREBALL,		7 },
  { spDEMAND,		8 },
  { spDETECTMAGIC,		0 },
  { spDETECTPOISON,		0 },
  { spDETECTSCRYING,		4 },
  { spDETECTSECRETDOORS,		1 },
  { spDETECTTHOUGHTS,		2 },
  { spDETECTUNDEAD,		1 },
  { spDIMENSIONALANCHOR,		4 },
  { spDIMENSIONALLOCK,		8 },
  { spDIMENSIONDOOR,		4 },
  { spDISCERNLOCATION,		8 },
  { spDISGUISESELF,		1 },
  { spDISINTEGRATE,		6 },
  { spDISMISSAL,		5 },
  { spDISPELMAGIC,		3 },
  { spDISPELMAGICGREATER,		6 },
  { spDISPLACEMENT,		3 },
  { spDISRUPTUNDEAD,		0 },
  { spDOMINATEMONSTER,		9 },
  { spDOMINATEPERSON,		5 },
  { spDREAM,		5 },
  { spEAGLESSPLENDOR,		2 },
  { spEAGLESSPLENDORMASS,		6 },
  { spENDUREELEMENTS,		1 },
  { spENERGYDRAIN,		9 },
  { spENERVATION,		4 },
  { spENLARGEPERSON,		1 },
  { spENLARGEPERSONMASS,		4 },
  { spERASE,		1 },
  { spETHEREALJAUNT,		7 },
  { spETHEREALNESS,		9 },
  { spEXPEDITIOUSRETREAT,		1 },
  { spEXPLOSIVERUNES,		3 },
  { spEYEBITE,		6 },
  { spFABRICATE,		5 },
  { spFALSELIFE,		2 },
  { spFALSEVISION,		5 },
  { spFEAR,		4 },
  { spFEATHERFALL,		1 },
  { spFEEBLEMIND,		5 },
  { spFINGEROFDEATH,		7 },
  { spFIREBALL,		3 },
  { spFIRESHIELD,		4 },
  { spFIRETRAP,		4 },
  { spFLAMEARROW,		3 },
  { spFLAMINGSPHERE,		2 },
  { spFLARE,		0 },
  { spFLESHTOSTONE,		6 },
  { spFLOATINGDISK,		1 },
  { spFLY,		3 },
  { spFOGCLOUD,		2 },
  { spFORCECAGE,		7 },
  { spFORCEFULHAND,		6 },
  { spFORESIGHT,		9 },
  { spFOXSCUNNING,		2 },
  { spFOXSCUNNINGMASS,		6 },
  { spFREEDOM,		9 },
  { spFREEZINGSPHERE,		6 },
  { spGASEOUSFORM,		3 },
  { spGATE,		9 },
  { spGEASLESSER,		4 },
  { spGEASQUEST,		6 },
  { spGENTLEREPOSE,		3 },
  { spGHOSTSOUND,		0 },
  { spGHOULTOUCH,		2 },
  { spGLITTERDUST,		2 },
  { spGLOBEOFINVULNERABILITY,		6 },
  { spGLOBEOFINVULNERABILITYLESSER,		4 },
  { spGRASPINGHAND,		7 },
  { spGREASE,		1 },
  { spGUARDSANDWARDS,		6 },
  { spGUSTOFWIND,		2 },
  { spHALLUCINATORYTERRAIN,		4 },
  { spHALTUNDEAD,		3 },
  { spHASTE,		3 },
  { spHEROISM,		3 },
  { spHEROISMGREATER,		6 },
  { spHIDEOUSLAUGHTER,		2 },
  { spHOLDMONSTER,		5 },
  { spHOLDMONSTERMASS,		9 },
  { spHOLDPERSON,		3 },
  { spHOLDPERSONMASS,		7 },
  { spHOLDPORTAL,		1 },
  { spHORRIDWILTING,		8 },
  { spHYPNOTICPATTERN,		2 },
  { spHYPNOTISM,		1 },
  { spICESTORM,		4 },
  { spIDENTIFY,		1 },
  { spILLUSORYSCRIPT,		3 },
  { spILLUSORYWALL,		4 },
  { spIMPRISONMENT,		9 },
  { spINCENDIARYCLOUD,		8 },
  { spINSANITY,		7 },
  { spINSTANTSUMMONS,		7 },
  { spINTERPOSINGHAND,		5 },
  { spINVISIBILITY,		2 },
  { spINVISIBILITYGREATER,		4 },
  { spINVISIBILITYMASS,		7 },
  { spINVISIBILITYSPHERE,		3 },
  { spIRONBODY,		8 },
  { spIRRESISTIBLEDANCE,		8 },
  { spJUMP,		1 },
  { spKEENEDGE,		3 },
  { spKNOCK,		2 },
  { spLEGENDLORE,		6 },
  { spLEVITATE,		2 },
  { spLIGHT,		0 },
  { spLIGHTNINGBOLT,		3 },
  { spLIMITEDWISH,		7 },
  { spLOCATECREATURE,		4 },
  { spLOCATEOBJECT,		2 },
  { spMAGEARMOR,		1 },
  { spMAGEHAND,		0 },
  { spMAGESDISJUNCTION,		9 },
  { spMAGESFAITHFULHOUND,		5 },
  { spMAGESLUCUBRATION,		6 },
  { spMAGESMAGNIFICENTMANSION,		7 },
  { spMAGESPRIVATESANCTUM,		5 },
  { spMAGESSWORD,		7 },
  { spMAGICAURA,		1 },
  { spMAGICCIRCLEAGAINSTCHAOS,		3 },
  { spMAGICCIRCLEAGAINSTEVIL,		3 },
  { spMAGICCIRCLEAGAINSTGOOD,		3 },
  { spMAGICCIRCLEAGAINSTLAW,		3 },
  { spMAGICJAR,		5 },
  { spMAGICMISSILE,		1 },
  { spMAGICMOUTH,		2 },
  { spMAGICWEAPON,		1 },
  { spMAGICWEAPONGREATER,		3 },
  { spMAJORCREATION,		5 },
  { spMAJORIMAGE,		3 },
  { spMAZE,		8 },
  { spMENDING,		0 },
  { spMESSAGE,		0 },
  { spMETEORSWARM,		9 },
  { spMINDBLANK,		8 },
  { spMINDFOG,		5 },
  { spMINORCREATION,		4 },
  { spMINORIMAGE,		2 },
  { spMIRAGEARCANA,		5 },
  { spMIRRORIMAGE,		2 },
  { spMISDIRECTION,		2 },
  { spMISLEAD,		6 },
  { spMNEMONICENHANCER,		4 },
  { spMOMENTOFPRESCIENCE,		8 },
  { spMOUNT,		1 },
  { spMOVEEARTH,		6 },
  { spNIGHTMARE,		5 },
  { spNONDETECTION,		3 },
  { spOBSCUREOBJECT,		2 },
  { spOBSCURINGMIST,		1 },
  { spOPENCLOSE,		0 },
  { spOVERLANDFLIGHT,		5 },
  { spOWLSWISDOM,		2 },
  { spOWLSWISDOMMASS,		6 },
  { spPASSWALL,		5 },
  { spPERMANENCY,		5 },
  { spPERMANENTIMAGE,		6 },
  { spPERSISTENTIMAGE,		5 },
  { spPHANTASMALKILLER,		4 },
  { spPHANTOMSTEED,		3 },
  { spPHANTOMTRAP,		2 },
  { spPHASEDOOR,		7 },
  { spPLANARBINDING,		6 },
  { spPLANARBINDINGGREATER,		8 },
  { spPLANARBINDINGLESSER,		5 },
  { spPLANESHIFT,		7 },
  { spPOLARRAY,		8 },
  { spPOLYMORPH,		4 },
  { spPOLYMORPHANYOBJECT,		8 },
  { spPOWERWORDBLIND,		7 },
  { spPOWERWORDKILL,		9 },
  { spPOWERWORDSTUN,		8 },
  { spPRESTIDIGITATION,		0 },
  { spPRISMATICSPHERE,		9 },
  { spPRISMATICSPRAY,		7 },
  { spPRISMATICWALL,		8 },
  { spPROGRAMMEDIMAGE,		6 },
  { spPROJECTIMAGE,		7 },
  { spPROTECTIONFROMARROWS,		2 },
  { spPROTECTIONFROMCHAOS,		1 },
  { spPROTECTIONFROMENERGY,		3 },
  { spPROTECTIONFROMEVIL,		1 },
  { spPROTECTIONFROMGOOD,		1 },
  { spPROTECTIONFROMLAW,		1 },
  { spPROTECTIONFROMSPELLS,		8 },
  { spPRYINGEYES,		5 },
  { spPRYINGEYESGREATER,		8 },
  { spPYROTECHNICS,		2 },
  { spRAGE,		3 },
  { spRAINBOWPATTERN,		4 },
  { spRAYOFENFEEBLEMENT,		1 },
  { spRAYOFEXHAUSTION,		3 },
  { spRAYOFFROST,		0 },
  { spREADMAGIC,		0 },
  { spREDUCEPERSON,		1 },
  { spREDUCEPERSONMASS,		4 },
  { spREFUGE,		9 },
  { spREMOVECURSE,		4 },
  { spREPULSION,		6 },
  { spRESILIENTSPHERE,		4 },
  { spRESISTANCE,		0 },
  { spRESISTENERGY,		2 },
  { spREVERSEGRAVITY,		7 },
  { spROPETRICK,		2 },
  { spSCARE,		2 },
  { spSCINTILLATINGPATTERN,		8 },
  { spSCORCHINGRAY,		2 },
  { spSCREEN,		8 },
  { spSCRYING,		4 },
  { spSCRYINGGREATER,		7 },
  { spSECRETCHEST,		5 },
  { spSECRETPAGE,		3 },
  { spSECURESHELTER,		4 },
  { spSEEINVISIBILITY,		2 },
  { spSEEMING,		5 },
  { spSENDING,		5 },
  { spSEPIASNAKESIGIL,		3 },
  { spSEQUESTER,		7 },
  { spSHADES,		9 },
  { spSHADOWCONJURATION,		4 },
  { spSHADOWCONJURATIONGREATER,		7 },
  { spSHADOWEVOCATION,		5 },
  { spSHADOWEVOCATIONGREATER,		8 },
  { spSHADOWWALK,		6 },
  { spSHAPECHANGE,		9 },
  { spSHATTER,		2 },
  { spSHIELD,		1 },
  { spSHOCKINGGRASP,		1 },
  { spSHOUT,		4 },
  { spSHOUTGREATER,		8 },
  { spSHRINKITEM,		3 },
  { spSILENTIMAGE,		1 },
  { spSIMULACRUM,		7 },
  { spSLEEP,		1 },
  { spSLEETSTORM,		3 },
  { spSLOW,		3 },
  { spSOLIDFOG,		4 },
  { spSOULBIND,		9 },
  { spSPECTRALHAND,		2 },
  { spSPELLTURNING,		7 },
  { spSPIDERCLIMB,		2 },
  { spSTATUE,		7 },
  { spSTINKINGCLOUD,		3 },
  { spSTONESHAPE,		5 },
  { spSTONESKIN,		4 },
  { spSTONETOFLESH,		6 },
  { spSUGGESTION,		3 },
  { spSUGGESTIONMASS,		6 },
  { spSUMMONMONSTERI,		1 },
  { spSUMMONMONSTERII,		2 },
  { spSUMMONMONSTERIII,		3 },
  { spSUMMONMONSTERIV,		4 },
  { spSUMMONMONSTERIX,		9 },
  { spSUMMONMONSTERV,		5 },
  { spSUMMONMONSTERVI,		6 },
  { spSUMMONMONSTERVII,		7 },
  { spSUMMONMONSTERVIII,		8 },
  { spSUMMONSWARM,		2 },
  { spSUNBURST,		8 },
  { spSYMBOLOFDEATH,		8 },
  { spSYMBOLOFFEAR,		6 },
  { spSYMBOLOFINSANITY,		8 },
  { spSYMBOLOFPAIN,		5 },
  { spSYMBOLOFPERSUASION,		6 },
  { spSYMBOLOFSLEEP,		5 },
  { spSYMBOLOFSTUNNING,		7 },
  { spSYMBOLOFWEAKNESS,		7 },
  { spSYMPATHY,		8 },
  { spTELEKINESIS,		5 },
  { spTELEKINETICSPHERE,		8 },
  { spTELEPATHICBOND,		5 },
  { spTELEPORT,		5 },
  { spTELEPORTATIONCIRCLE,		9 },
  { spTELEPORTGREATER,		7 },
  { spTELEPORTOBJECT,		7 },
  { spTEMPORALSTASIS,		8 },
  { spTIMESTOP,		9 },
  { spTINYHUT,		3 },
  { spTONGUES,		3 },
  { spTOUCHOFFATIGUE,		0 },
  { spTOUCHOFIDIOCY,		2 },
  { spTRANSFORMATION,		6 },
  { spTRANSMUTEMUDTOROCK,		5 },
  { spTRANSMUTEROCKTOMUD,		5 },
  { spTRAPTHESOUL,		8 },
  { spTRUESEEING,		6 },
  { spTRUESTRIKE,		1 },
  { spUNDEATHTODEATH,		6 },
  { spUNSEENSERVANT,		1 },
  { spVAMPIRICTOUCH,		3 },
  { spVEIL,		6 },
  { spVENTRILOQUISM,		1 },
  { spVISION,		7 },
  { spWAILOFTHEBANSHEE,		9 },
  { spWALLOFFIRE,		4 },
  { spWALLOFFORCE,		5 },
  { spWALLOFICE,		4 },
  { spWALLOFIRON,		6 },
  { spWALLOFSTONE,		5 },
  { spWATERBREATHING,		3 },
  { spWAVESOFEXHAUSTION,		7 },
  { spWAVESOFFATIGUE,		5 },
  { spWEB,		2 },
  { spWEIRD,		9 },
  { spWHISPERINGWIND,		2 },
  { spWINDWALL,		3 },
  { spWISH,		9 },
  { 0, 0 }
};




static int goodAttackProgression[]   = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 };
static int mediumAttackProgression[] = { 0, 1, 2, 3, 3, 4, 5, 6, 6,  7,  8,  9,  9, 10, 11, 12, 12, 13, 14, 15 };
static int poorAttackProgression[]   = { 0, 1, 1, 2, 2, 3, 3, 4, 4,  5,  5,  6,  6,  7,  7,  8,  8,  9,  9, 10 };

static int goodSaveProgression[] = { 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9, 10, 10, 11, 11, 12 };
static int poorSaveProgression[] = { 0, 0, 1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4, 5,  5,  5,  6,  6,  6 };

static SPELLMATRIX adeptSpellsPerDay = {
  {  3,  1, -1, -1, -1, -1, -1, -1, -1, -1 },
  {  3,  1, -1, -1, -1, -1, -1, -1, -1, -1 },
  {  3,  2, -1, -1, -1, -1, -1, -1, -1, -1 },
  {  3,  2,  0, -1, -1, -1, -1, -1, -1, -1 },
  {  3,  2,  1, -1, -1, -1, -1, -1, -1, -1 },
  {  3,  2,  1, -1, -1, -1, -1, -1, -1, -1 },
  {  3,  3,  2, -1, -1, -1, -1, -1, -1, -1 },
  {  3,  3,  2,  0, -1, -1, -1, -1, -1, -1 },
  {  3,  3,  2,  1, -1, -1, -1, -1, -1, -1 },
  {  3,  3,  2,  1, -1, -1, -1, -1, -1, -1 },
  {  3,  3,  3,  2, -1, -1, -1, -1, -1, -1 },
  {  3,  3,  3,  2,  0, -1, -1, -1, -1, -1 },
  {  3,  3,  3,  2,  1, -1, -1, -1, -1, -1 },
  {  3,  3,  3,  2,  1, -1, -1, -1, -1, -1 },
  {  3,  3,  3,  3,  2, -1, -1, -1, -1, -1 },
  {  3,  3,  3,  3,  2,  0, -1, -1, -1, -1 },
  {  3,  3,  3,  3,  2,  1, -1, -1, -1, -1 },
  {  3,  3,  3,  3,  2,  1, -1, -1, -1, -1 },
  {  3,  3,  3,  3,  3,  2, -1, -1, -1, -1 },
  {  3,  3,  3,  3,  3,  2, -1, -1, -1, -1 }
};


static SPELLMATRIX bardSpellsPerDay = {
  {  2, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
  {  3,  0, -1, -1, -1, -1, -1, -1, -1, -1 },
  {  3,  1, -1, -1, -1, -1, -1, -1, -1, -1 },
  {  3,  2,  0, -1, -1, -1, -1, -1, -1, -1 },
  {  3,  3,  1, -1, -1, -1, -1, -1, -1, -1 },
  {  3,  3,  2, -1, -1, -1, -1, -1, -1, -1 },
  {  3,  3,  2,  0, -1, -1, -1, -1, -1, -1 },
  {  3,  3,  3,  1, -1, -1, -1, -1, -1, -1 },
  {  3,  3,  3,  2, -1, -1, -1, -1, -1, -1 },
  {  3,  3,  3,  2,  0, -1, -1, -1, -1, -1 },
  {  3,  3,  3,  3,  1, -1, -1, -1, -1, -1 },
  {  3,  3,  3,  3,  2, -1, -1, -1, -1, -1 },
  {  3,  3,  3,  3,  2,  0, -1, -1, -1, -1 },
  {  4,  3,  3,  3,  3,  1, -1, -1, -1, -1 },
  {  4,  4,  3,  3,  3,  2, -1, -1, -1, -1 },
  {  4,  4,  4,  3,  3,  2,  0, -1, -1, -1 },
  {  4,  4,  4,  4,  3,  3,  1, -1, -1, -1 },
  {  4,  4,  4,  4,  4,  3,  2, -1, -1, -1 },
  {  4,  4,  4,  4,  4,  4,  3, -1, -1, -1 },
  {  4,  4,  4,  4,  4,  4,  4, -1, -1, -1 }
};


static SPELLMATRIX bardSpellsKnown = {
  {  4, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
  {  5,  2, -1, -1, -1, -1, -1, -1, -1, -1 },
  {  6,  3, -1, -1, -1, -1, -1, -1, -1, -1 },
  {  6,  3,  2, -1, -1, -1, -1, -1, -1, -1 },
  {  6,  4,  3, -1, -1, -1, -1, -1, -1, -1 },
  {  6,  4,  3, -1, -1, -1, -1, -1, -1, -1 },
  {  6,  4,  4,  2, -1, -1, -1, -1, -1, -1 },
  {  6,  4,  4,  3, -1, -1, -1, -1, -1, -1 },
  {  6,  4,  4,  3, -1, -1, -1, -1, -1, -1 },
  {  6,  4,  4,  4,  2, -1, -1, -1, -1, -1 },
  {  6,  4,  4,  4,  3, -1, -1, -1, -1, -1 },
  {  6,  4,  4,  4,  3, -1, -1, -1, -1, -1 },
  {  6,  4,  4,  4,  4,  2, -1, -1, -1, -1 },
  {  6,  4,  4,  4,  4,  3, -1, -1, -1, -1 },
  {  6,  4,  4,  4,  4,  3, -1, -1, -1, -1 },
  {  6,  5,  4,  4,  4,  4,  2, -1, -1, -1 },
  {  6,  5,  5,  4,  4,  4,  3, -1, -1, -1 },
  {  6,  5,  5,  5,  4,  4,  3, -1, -1, -1 },
  {  6,  5,  5,  5,  5,  4,  4, -1, -1, -1 },
  {  6,  5,  5,  5,  5,  5,  4, -1, -1, -1 }
};


static SPELLMATRIX clericSpellsPerDay = {
  {  3,  1, -1, -1, -1, -1, -1, -1, -1, -1 },
  {  4,  2, -1, -1, -1, -1, -1, -1, -1, -1 },
  {  4,  2,  1, -1, -1, -1, -1, -1, -1, -1 },
  {  5,  3,  2, -1, -1, -1, -1, -1, -1, -1 },
  {  5,  3,  2,  1, -1, -1, -1, -1, -1, -1 },
  {  5,  3,  3,  2, -1, -1, -1, -1, -1, -1 },
  {  6,  4,  3,  2,  1, -1, -1, -1, -1, -1 },
  {  6,  4,  3,  3,  2, -1, -1, -1, -1, -1 },
  {  6,  4,  4,  3,  2,  1, -1, -1, -1, -1 },
  {  6,  4,  4,  3,  3,  2, -1, -1, -1, -1 },
  {  6,  5,  4,  4,  3,  2,  1, -1, -1, -1 },
  {  6,  5,  4,  4,  3,  3,  2, -1, -1, -1 },
  {  6,  5,  5,  4,  4,  3,  2,  1, -1, -1 },
  {  6,  5,  5,  4,  4,  3,  3,  2, -1, -1 },
  {  6,  5,  5,  5,  4,  4,  3,  2,  1, -1 },
  {  6,  5,  5,  5,  4,  4,  3,  3,  2, -1 },
  {  6,  5,  5,  5,  5,  4,  4,  3,  2,  1 },
  {  6,  5,  5,  5,  5,  4,  4,  3,  3,  2 },
  {  6,  5,  5,  5,  5,  5,  4,  4,  3,  3 },
  {  6,  5,  5,  5,  5,  5,  4,  4,  4,  4 }
};


static SPELLMATRIX druidSpellsPerDay = {
  {  3,  1, -1, -1, -1, -1, -1, -1, -1, -1 },
  {  4,  2, -1, -1, -1, -1, -1, -1, -1, -1 },
  {  4,  2,  1, -1, -1, -1, -1, -1, -1, -1 },
  {  5,  3,  2, -1, -1, -1, -1, -1, -1, -1 },
  {  5,  3,  2,  1, -1, -1, -1, -1, -1, -1 },
  {  5,  3,  3,  2, -1, -1, -1, -1, -1, -1 },
  {  6,  4,  3,  2,  1, -1, -1, -1, -1, -1 },
  {  6,  4,  3,  3,  2, -1, -1, -1, -1, -1 },
  {  6,  4,  4,  3,  2,  1, -1, -1, -1, -1 },
  {  6,  4,  4,  3,  3,  2, -1, -1, -1, -1 },
  {  6,  5,  4,  4,  3,  2,  1, -1, -1, -1 },
  {  6,  5,  4,  4,  3,  3,  2, -1, -1, -1 },
  {  6,  5,  5,  4,  4,  3,  2,  1, -1, -1 },
  {  6,  5,  5,  4,  4,  3,  3,  2, -1, -1 },
  {  6,  5,  5,  5,  4,  4,  3,  2,  1, -1 },
  {  6,  5,  5,  5,  4,  4,  3,  3,  2, -1 },
  {  6,  5,  5,  5,  5,  4,  4,  3,  2,  1 },
  {  6,  5,  5,  5,  5,  4,  4,  3,  3,  2 },
  {  6,  5,  5,  5,  5,  5,  4,  4,  3,  3 },
  {  6,  5,  5,  5,  5,  5,  4,  4,  4,  4 }
};


static SPELLMATRIX paladinSpellsPerDay = {
  { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
  { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
  { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
  { -1,  0, -1, -1, -1, -1, -1, -1, -1, -1 },
  { -1,  0, -1, -1, -1, -1, -1, -1, -1, -1 },
  { -1,  1, -1, -1, -1, -1, -1, -1, -1, -1 },
  { -1,  1, -1, -1, -1, -1, -1, -1, -1, -1 },
  { -1,  1,  0, -1, -1, -1, -1, -1, -1, -1 },
  { -1,  1,  0, -1, -1, -1, -1, -1, -1, -1 },
  { -1,  1,  1, -1, -1, -1, -1, -1, -1, -1 },
  { -1,  1,  1,  0, -1, -1, -1, -1, -1, -1 },
  { -1,  1,  1,  1, -1, -1, -1, -1, -1, -1 },
  { -1,  1,  1,  1, -1, -1, -1, -1, -1, -1 },
  { -1,  2,  1,  1,  0, -1, -1, -1, -1, -1 },
  { -1,  2,  1,  1,  1, -1, -1, -1, -1, -1 },
  { -1,  2,  2,  1,  1, -1, -1, -1, -1, -1 },
  { -1,  2,  2,  2,  1, -1, -1, -1, -1, -1 },
  { -1,  3,  2,  2,  1, -1, -1, -1, -1, -1 },
  { -1,  3,  3,  3,  2, -1, -1, -1, -1, -1 },
  { -1,  3,  3,  3,  3, -1, -1, -1, -1, -1 }
};


static SPELLMATRIX rangerSpellsPerDay = {
  { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
  { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
  { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
  { -1,  0, -1, -1, -1, -1, -1, -1, -1, -1 },
  { -1,  0, -1, -1, -1, -1, -1, -1, -1, -1 },
  { -1,  1, -1, -1, -1, -1, -1, -1, -1, -1 },
  { -1,  1, -1, -1, -1, -1, -1, -1, -1, -1 },
  { -1,  1,  0, -1, -1, -1, -1, -1, -1, -1 },
  { -1,  1,  0, -1, -1, -1, -1, -1, -1, -1 },
  { -1,  1,  1, -1, -1, -1, -1, -1, -1, -1 },
  { -1,  1,  1,  0, -1, -1, -1, -1, -1, -1 },
  { -1,  1,  1,  1, -1, -1, -1, -1, -1, -1 },
  { -1,  1,  1,  1, -1, -1, -1, -1, -1, -1 },
  { -1,  2,  1,  1,  0, -1, -1, -1, -1, -1 },
  { -1,  2,  1,  1,  1, -1, -1, -1, -1, -1 },
  { -1,  2,  2,  1,  1, -1, -1, -1, -1, -1 },
  { -1,  2,  2,  2,  1, -1, -1, -1, -1, -1 },
  { -1,  3,  2,  2,  1, -1, -1, -1, -1, -1 },
  { -1,  3,  3,  3,  2, -1, -1, -1, -1, -1 },
  { -1,  3,  3,  3,  3, -1, -1, -1, -1, -1 }
};


static SPELLMATRIX sorcererSpellsPerDay = {
  {  5,  3, -1, -1, -1, -1, -1, -1, -1, -1 },
  {  6,  4, -1, -1, -1, -1, -1, -1, -1, -1 },
  {  6,  5, -1, -1, -1, -1, -1, -1, -1, -1 },
  {  6,  6,  3, -1, -1, -1, -1, -1, -1, -1 },
  {  6,  6,  4, -1, -1, -1, -1, -1, -1, -1 },
  {  6,  6,  5,  3, -1, -1, -1, -1, -1, -1 },
  {  6,  6,  6,  4, -1, -1, -1, -1, -1, -1 },
  {  6,  6,  6,  5,  3, -1, -1, -1, -1, -1 },
  {  6,  6,  6,  6,  4, -1, -1, -1, -1, -1 },
  {  6,  6,  6,  6,  5,  3, -1, -1, -1, -1 },
  {  6,  6,  6,  6,  6,  4, -1, -1, -1, -1 },
  {  6,  6,  6,  6,  6,  5,  3, -1, -1, -1 },
  {  6,  6,  6,  6,  6,  6,  4, -1, -1, -1 },
  {  6,  6,  6,  6,  6,  6,  5,  3, -1, -1 },
  {  6,  6,  6,  6,  6,  6,  6,  4, -1, -1 },
  {  6,  6,  6,  6,  6,  6,  6,  5,  3, -1 },
  {  6,  6,  6,  6,  6,  6,  6,  6,  4, -1 },
  {  6,  6,  6,  6,  6,  6,  6,  6,  5,  3 },
  {  6,  6,  6,  6,  6,  6,  6,  6,  6,  4 },
  {  6,  6,  6,  6,  6,  6,  6,  6,  6,  6 }
};


static SPELLMATRIX sorcererSpellsKnown = {
  {  4,  2, -1, -1, -1, -1, -1, -1, -1, -1 },
  {  5,  2, -1, -1, -1, -1, -1, -1, -1, -1 },
  {  5,  3, -1, -1, -1, -1, -1, -1, -1, -1 },
  {  6,  3,  1, -1, -1, -1, -1, -1, -1, -1 },
  {  6,  4,  2, -1, -1, -1, -1, -1, -1, -1 },
  {  7,  4,  2,  1, -1, -1, -1, -1, -1, -1 },
  {  7,  5,  3,  2, -1, -1, -1, -1, -1, -1 },
  {  8,  5,  3,  2,  1, -1, -1, -1, -1, -1 },
  {  8,  5,  4,  3,  2, -1, -1, -1, -1, -1 },
  {  9,  5,  4,  3,  2,  1, -1, -1, -1, -1 },
  {  9,  5,  5,  4,  3,  2, -1, -1, -1, -1 },
  {  9,  5,  5,  4,  3,  2,  1, -1, -1, -1 },
  {  9,  5,  5,  4,  4,  3,  2, -1, -1, -1 },
  {  9,  5,  5,  4,  4,  3,  2,  1, -1, -1 },
  {  9,  5,  5,  4,  4,  4,  3,  2, -1, -1 },
  {  9,  5,  5,  4,  4,  4,  3,  2,  1, -1 },
  {  9,  5,  5,  4,  4,  4,  3,  3,  2, -1 },
  {  9,  5,  5,  4,  4,  4,  3,  3,  2,  1 },
  {  9,  5,  5,  4,  4,  4,  3,  3,  3,  2 },
  {  9,  5,  5,  4,  4,  4,  3,  3,  3,  3 }
};


static SPELLMATRIX wizardSpellsPerDay = {
  {  3,  1, -1, -1, -1, -1, -1, -1, -1, -1 },
  {  4,  2, -1, -1, -1, -1, -1, -1, -1, -1 },
  {  4,  2,  1, -1, -1, -1, -1, -1, -1, -1 },
  {  4,  3,  2, -1, -1, -1, -1, -1, -1, -1 },
  {  4,  3,  2,  1, -1, -1, -1, -1, -1, -1 },
  {  4,  3,  3,  2, -1, -1, -1, -1, -1, -1 },
  {  4,  4,  3,  2,  1, -1, -1, -1, -1, -1 },
  {  4,  4,  3,  3,  2, -1, -1, -1, -1, -1 },
  {  4,  4,  4,  3,  2,  1, -1, -1, -1, -1 },
  {  4,  4,  4,  3,  3,  2, -1, -1, -1, -1 },
  {  4,  4,  4,  4,  3,  2,  1, -1, -1, -1 },
  {  4,  4,  4,  4,  3,  3,  2, -1, -1, -1 },
  {  4,  4,  4,  4,  4,  3,  2,  1, -1, -1 },
  {  4,  4,  4,  4,  4,  3,  3,  2, -1, -1 },
  {  4,  4,  4,  4,  4,  4,  3,  2,  1, -1 },
  {  4,  4,  4,  4,  4,  4,  3,  3,  2, -1 },
  {  4,  4,  4,  4,  4,  4,  4,  3,  2,  1 },
  {  4,  4,  4,  4,  4,  4,  4,  3,  3,  2 },
  {  4,  4,  4,  4,  4,  4,  4,  4,  3,  3 },
  {  4,  4,  4,  4,  4,  4,  4,  4,  4,  4 }
};


static const struct {
  int             id;
  int             type;
  int             skillCount;
  int             hitDie;
  int             bonusFeatAtFirst;
  int             bonusFeatEveryX;
  int*            attack;
  int*            fortSave;
  int*            refSave;
  int*            willSave;
  SKILLSFORCLASS* skills;
  SPELLSFORCLASS* spells;
  void*           spellsPerDay;
  void*           spellsKnown;
  char*           abbr;
  char*           name;
} s_classInfo[] = { /*              skills feat1   attack          */
    /* class            type             HD   feat2                         fortitude            reflex               will                 skills                 spells        spells per day         spells known          abbr    name         */
  { pcBARBARIAN,        cctPLAYER,    4, 12, 0, 0, goodAttackProgression,   goodSaveProgression, poorSaveProgression, poorSaveProgression, barbarianSkills,       0,            0,                     0,                    "bbn", "barbarian" },
  { pcBARD,             cctPLAYER,    6,  6, 0, 0, mediumAttackProgression, poorSaveProgression, goodSaveProgression, goodSaveProgression, bardSkills,            s_Bard,       &bardSpellsPerDay,     &bardSpellsKnown,     "brd", "bard" },
  { pcCLERIC,           cctPLAYER,    2,  8, 0, 0, mediumAttackProgression, goodSaveProgression, poorSaveProgression, goodSaveProgression, clericSkills,          s_Cleric,     &clericSpellsPerDay,   0,                    "clr", "cleric" },
  { pcDRUID,            cctPLAYER,    4,  8, 0, 0, mediumAttackProgression, goodSaveProgression, poorSaveProgression, goodSaveProgression, druidSkills,           s_Druid,      &druidSpellsPerDay,    0,                    "drd", "druid" },
  { pcFIGHTER,          cctPLAYER,    2, 10, 1, 2, goodAttackProgression,   goodSaveProgression, poorSaveProgression, poorSaveProgression, fighterSkills,         0,            0,                     0,                    "ftr", "fighter" },
  { pcMONK,             cctPLAYER,    4,  8, 0, 0, mediumAttackProgression, goodSaveProgression, goodSaveProgression, goodSaveProgression, monkSkills,            0,            0,                     0,                    "mnk", "monk" },
  { pcPALADIN,          cctPLAYER,    2, 10, 0, 0, goodAttackProgression,   goodSaveProgression, poorSaveProgression, poorSaveProgression, paladinSkills,         s_Paladin,    &paladinSpellsPerDay,  0,                    "pal", "paladin" },
  { pcRANGER,           cctPLAYER,    6,  8, 0, 0, goodAttackProgression,   goodSaveProgression, poorSaveProgression, poorSaveProgression, rangerSkills,          s_Ranger,     &rangerSpellsPerDay,   0,                    "rgr", "ranger" },
  { pcROGUE,            cctPLAYER,    8,  6, 0, 0, mediumAttackProgression, poorSaveProgression, goodSaveProgression, poorSaveProgression, rogueSkills,           0,            0,                     0,                    "rog", "rogue" },
  { pcSORCERER,         cctPLAYER,    2,  4, 0, 0, poorAttackProgression,   poorSaveProgression, poorSaveProgression, goodSaveProgression, sorcererSkills,        s_Sorcerer,   &sorcererSpellsPerDay, &sorcererSpellsKnown, "sor", "sorcerer" },
  { pcWIZARD,           cctPLAYER,    2,  4, 0, 5, poorAttackProgression,   poorSaveProgression, poorSaveProgression, goodSaveProgression, wizardSkills,          s_Wizard,     &wizardSpellsPerDay,   0,                    "wiz", "wizard" },
  { prcARCANEARCHER,    cctPRESTIGE,  4,  8, 0, 0, goodAttackProgression,   goodSaveProgression, goodSaveProgression, poorSaveProgression, arcaneArcherSkills,    0,            0,                     0,                    "arc", "arcane archer" },
  { prcASSASSIN,        cctPRESTIGE,  4,  6, 0, 0, mediumAttackProgression, poorSaveProgression, poorSaveProgression, goodSaveProgression, assassinSkills,        s_Assassin,   0,                     0,                    "asn", "assassin" },
  { prcBLACKGUARD,      cctPRESTIGE,  2, 10, 0, 0, goodAttackProgression,   goodSaveProgression, poorSaveProgression, poorSaveProgression, blackguardSkills,      s_Blackguard, 0,                     0,                    "bgd", "blackguard" },
  { prcDWARVENDEFENDER, cctPRESTIGE,  2, 12, 0, 0, goodAttackProgression,   goodSaveProgression, poorSaveProgression, goodSaveProgression, dwarvenDefenderSkills, 0,            0,                     0,                    "ddr", "dwarven defender" },
  { prcLOREMASTER,      cctPRESTIGE,  4,  4, 0, 0, poorAttackProgression,   poorSaveProgression, poorSaveProgression, goodSaveProgression, loremasterSkills,      0,            0,                     0,                    "lmr", "loremaster" },
  { prcSHADOWDANCER,    cctPRESTIGE,  6,  8, 0, 0, mediumAttackProgression, poorSaveProgression, goodSaveProgression, poorSaveProgression, shadowdancerSkills,    0,            0,                     0,                    "sdr", "shadowdancer" },
  { npcADEPT,           cctNONPLAYER, 2,  6, 0, 0, poorAttackProgression,   poorSaveProgression, poorSaveProgression, goodSaveProgression, adeptSkills,           s_Adept,      &adeptSpellsPerDay,    0,                    "adp", "adept" },
  { npcARISTOCRAT,      cctNONPLAYER, 4,  8, 0, 0, mediumAttackProgression, poorSaveProgression, poorSaveProgression, goodSaveProgression, aristocratSkills,      0,            0,                     0,                    "nob", "aristocrat" },
  { npcCOMMONER,        cctNONPLAYER, 2,  4, 0, 0, poorAttackProgression,   poorSaveProgression, poorSaveProgression, poorSaveProgression, commonerSkills,        0,            0,                     0,                    "com", "commoner" },
  { npcEXPERT,          cctNONPLAYER, 6,  6, 0, 0, mediumAttackProgression, poorSaveProgression, poorSaveProgression, goodSaveProgression, expertSkills,          0,            0,                     0,                    "exp", "expert" },
  { npcWARRIOR,         cctNONPLAYER, 2,  8, 0, 0, goodAttackProgression,   goodSaveProgression, poorSaveProgression, poorSaveProgression, warriorSkills,         0,            0,                     0,                    "war", "warrior" },
  { 0,                  0,            0,  0, 0, 0, 0,                       0,                   0,                   0,                   0,                     0,            0,                     0,                    0,     0 }
};

static const struct {
  int id;
  char *name;
} s_specialistTypeInfo[] = {
	{ ssUNIVERSAL,            "Universalist" },
	{ ssABJURATION,           "Abjurer" },
	{ ssCONJURATION,          "Conjurer" },
	{ ssDIVINATION,           "Diviner" },
	{ ssENCHANTMENT,          "Enchanter" },
	{ ssEVOCATION,            "Evoker" },
	{ ssILLUSION,             "Illusionist" },
	{ ssNECROMANCY,           "Necromancer" },
	{ ssTRANSMUTATION,        "Transmuter" },
	{ 0,                      0 }
};


static const struct {
  int   id;
  char* name;
} s_classTypeInfo[] = {
  { cctPLAYER,    "player" },
  { cctPRESTIGE,  "prestige" },
  { cctNONPLAYER, "non-player" },
  { 0,            0 }
};


static const struct {
  int   alignment;
  char* abbr;
  char* text;
} s_alignmentText[] = {
  { alLAWFUL | alGOOD,         "LG", "lawful good" },
  { alLAWFUL | alGENEUTRAL,    "LN", "lawful neutral" },
  { alLAWFUL | alEVIL,         "LE", "lawful evil" },
  { alLCNEUTRAL | alGOOD,      "NG", "neutral good" },
  { alLCNEUTRAL | alGENEUTRAL, "N",  "true neutral" },
  { alLCNEUTRAL | alEVIL,      "NE", "neutral evil" },
  { alCHAOTIC | alGOOD,        "CG", "chaotic good" },
  { alCHAOTIC | alGENEUTRAL,   "CN", "chaotic neutral" },
  { alCHAOTIC | alEVIL,        "CE", "chaotic evil" },
  { 0,                         0,    0 }
};


static const struct {
  int   type;
  int   ability;
  int   untrained;
  int   acCheck;
  char* name;
} s_skills[] = {
	{ skAPPRAISE,		abINTELLIGENCE, 1, 0, "Appraise" },
	{ skBALANCE,		abDEXTERITY, 1, 1, "Balance" },
	{ skBLUFF,		abCHARISMA, 1, 0, "Bluff" },
	{ skCLIMB,		abSTRENGTH, 1, 1, "Climb" },
	{ skCONCENTRATION,		abCONSTITUTION, 1, 0, "Concentration" },
	{ skCRAFT_ALCHEMY,		abINTELLIGENCE, 0, 0, "Craft (Alchemy)" },
	{ skCRAFT_ARMORSMITHING,		abINTELLIGENCE, 0, 0, "Craft (Armorsmithing)" },
	{ skCRAFT_BOWMAKING,		abINTELLIGENCE, 0, 0, "Craft (Bowmaking)" },
	{ skCRAFT_BLACKSMITHING,		abINTELLIGENCE, 0, 0, "Craft (Blacksmithing)" },
	{ skCRAFT_CARPENTRY,		abINTELLIGENCE, 0, 0, "Craft (Carpentry)" },
	{ skCRAFT_LEATHERWORKING,		abINTELLIGENCE, 0, 0, "Craft (Leatherworking)" },
	{ skCRAFT_PAINTING,		abINTELLIGENCE, 0, 0, "Craft (Painting)" },
	{ skCRAFT_POTTERY,		abINTELLIGENCE, 0, 0, "Craft (Pottery)" },
	{ skCRAFT_SCULPTING,		abINTELLIGENCE, 0, 0, "Craft (Sculpting)" },
	{ skCRAFT_SHIPMAKING,		abINTELLIGENCE, 0, 0, "Craft (Shipmaking)" },
	{ skCRAFT_STONEMASONRY,		abINTELLIGENCE, 0, 0, "Craft (Stonemasonry)" },
	{ skCRAFT_TRAPMAKING,		abINTELLIGENCE, 0, 0, "Craft (Trapmaking)" },
	{ skCRAFT_WEAPONSMITHING,		abINTELLIGENCE, 0, 0, "Craft (Weaponsmithing)" },
	{ skCRAFT_WOODWORKING,		abINTELLIGENCE, 0, 0, "Craft (Woodworking)" },
	{ skDECIPHERSCRIPT,		abINTELLIGENCE, 0, 0, "Decipher Script" },
	{ skDIPLOMACY,		abCHARISMA, 1, 0, "Diplomacy" },
	{ skDISABLEDEVICE,		abINTELLIGENCE, 0, 0, "Disable Device" },
	{ skDISGUISE,		abCHARISMA, 1, 0, "Disguise" },
	{ skESCAPEARTIST,		abDEXTERITY, 1, 1, "Escape Artist" },
	{ skFORGERY,		abINTELLIGENCE, 1, 0, "Forgery" },
	{ skGATHERINFORMATION,		abCHARISMA, 1, 0, "Gather Information" },
	{ skHANDLEANIMAL,		abCHARISMA, 0, 0, "Handle Animal" },
	{ skHEAL,		abWISDOM, 1, 0, "Heal" },
	{ skHIDE,		abDEXTERITY, 1, 1, "Hide" },
	{ skINTIMIDATE,		abCHARISMA, 1, 0, "Intimidate" },
	{ skJUMP,		abSTRENGTH, 1, 1, "Jump" },
	{ skKNOWLEDGE_ARCANA,		abINTELLIGENCE, 0, 0, "Knowledge (Arcana)" },
	{ skKNOWLEDGE_ARCHITECTUREANDENGINEERING,		abINTELLIGENCE, 0, 0, "Knowledge (Architecture and Engineering)" },
	{ skKNOWLEDGE_DUNGEONEERING,		abINTELLIGENCE, 0, 0, "Knowledge (Dungeoneering)" },
	{ skKNOWLEDGE_GEOGRAPHY,		abINTELLIGENCE, 0, 0, "Knowledge (Geography)" },
	{ skKNOWLEDGE_HISTORY,		abINTELLIGENCE, 0, 0, "Knowledge (History)" },
	{ skKNOWLEDGE_LOCAL,		abINTELLIGENCE, 0, 0, "Knowledge (Local)" },
	{ skKNOWLEDGE_NATURE,		abINTELLIGENCE, 0, 0, "Knowledge (Nature)" },
	{ skKNOWLEDGE_NOBILITYANDROYALTY,		abINTELLIGENCE, 0, 0, "Knowledge (Nobility and Royalty)" },
	{ skKNOWLEDGE_RELIGION,		abINTELLIGENCE, 0, 0, "Knowledge (Religion)" },
	{ skKNOWLEDGE_THEPLANES,		abINTELLIGENCE, 0, 0, "Knowledge (The Planes)" },
	{ skLISTEN,		abWISDOM, 1, 0, "Listen" },
	{ skMOVESILENTLY,		abDEXTERITY, 1, 1, "Move Silently" },
	{ skOPENLOCK,		abDEXTERITY, 0, 0, "Open Lock" },
	{ skPERFORM_ACT,		abCHARISMA, 0, 0, "Perform (Act)" },
	{ skPERFORM_COMEDY,		abCHARISMA, 0, 0, "Perform (Comedy)" },
	{ skPERFORM_DANCE,		abCHARISMA, 0, 0, "Perform (Dance)" },
	{ skPERFORM_KEYBOARDINSTRUMENTS,		abCHARISMA, 0, 0, "Perform (Keyboard Instruments)" },
	{ skPERFORM_ORATORY,		abCHARISMA, 0, 0, "Perform (Oratory)" },
	{ skPERFORM_PERCUSSIONINSTRUMENTS,		abCHARISMA, 0, 0, "Perform (Percussion Instruments)" },
	{ skPERFORM_STRINGINSTRUMENTS,		abCHARISMA, 0, 0, "Perform (String Instruments)" },
	{ skPERFORM_WINDINSTRUMENTS,		abCHARISMA, 0, 0, "Perform (Wind Instruments)" },
	{ skPERFORM_SING,		abCHARISMA, 0, 0, "Perform (Sing)" },
	{ skPROFESSION_HUNTER,		abWISDOM, 0, 0, "Profession (Hunter)" },
	{ skPROFESSION_MINER,		abWISDOM, 0, 0, "Profession (Miner)" },
	{ skRIDE,		abDEXTERITY, 1, 0, "Ride" },
	{ skSEARCH,		abINTELLIGENCE, 1, 0, "Search" },
	{ skSENSEMOTIVE,		abWISDOM, 1, 0, "Sense Motive" },
	{ skSLEIGHTOFHAND,		abDEXTERITY, 0, 1, "Sleight of Hand" },
	{ skSPEAKLANGUAGE,		abNONE, 0, 0, "Speak Language" },
	{ skSPELLCRAFT,		abINTELLIGENCE, 0, 0, "Spellcraft" },
	{ skSPOT,		abWISDOM, 1, 0, "Spot" },
	{ skSURVIVAL,		abWISDOM, 1, 0, "Survival" },
	{ skSWIM,		abSTRENGTH, 1, 0, "Swim" },
	{ skTUMBLE,		abDEXTERITY, 0, 1, "Tumble" },
	{ skUSEMAGICDEVICE,		abCHARISMA, 0, 0, "Use Magic Device" },
	{ skUSEROPE,		abDEXTERITY, 1, 0, "Use Rope" },
	{ 0,										0,              0, 0, 0 }
};


static const struct {
  int   ability;
  char* name;
} s_abilities[] = {
  { abNONE,         "none" },
  { abSTRENGTH,     "strength" },
  { abDEXTERITY,    "dexterity" },
  { abCONSTITUTION, "constitution" },
  { abINTELLIGENCE, "intelligence" },
  { abWISDOM,       "wisdom" },
  { abCHARISMA,     "charisma" },
  { 0,              0 }
};


static const struct {
  int   id;
  char* name;
} s_featTypes[] = {
  { fttGENERAL,      "general" },
  { fttITEMCREATION, "item creation" },
  { fttMETAMAGIC,    "metamagic" },
  { fttSPECIAL,      "special" },
  { 0,               0 }
};



/* feat pre-requisite definitions */

static FEATPREREQ acrobaticPR[] = {	{ 0, 0, 0 } };

static FEATPREREQ agilePR[] = {	{ 0, 0, 0 } };

static FEATPREREQ alertnessPR[] = {	{ 0, 0, 0 } };

static FEATPREREQ animalAffinityPR[] = {	{ 0, 0, 0 } };

static FEATPREREQ armorProfHeavyPR[] = {
	{ fprFEAT, ftARMORPROFICIENCY_MEDIUM, 0 },
	{ 0, 0, 0 } };

static FEATPREREQ armorProfLightPR[] = {	{ 0, 0, 0 } };

static FEATPREREQ armorProfMedPR[] = {
	{ fprFEAT, ftARMORPROFICIENCY_LIGHT, 0 },
	{ 0, 0, 0 } };

static FEATPREREQ athleticPR[] = {	{ 0, 0, 0 } };

static FEATPREREQ augmentSummoningPR[] = {
	{ fprFEAT, ftSPELLFOCUS, ssCONJURATION },
	{ 0, 0, 0 } };

static FEATPREREQ blindfightPR[] = {	{ 0, 0, 0 } };

static FEATPREREQ brewPotionPR[] = {
	{ fprMINIMUMSPELLCASTERLEVEL, 3, 0 },
	{ 0, 0, 0 } };

static FEATPREREQ cleavePR[] = {
	{ fprMINIMUMABILITYSCORE, abSTRENGTH, 13 },
	{ fprFEAT, ftPOWERATTACK, 0 },
	{ 0, 0, 0 } };

static FEATPREREQ combatCastingPR[] = {	{ 0, 0, 0 } };

static FEATPREREQ combatExpertisePR[] = {
	{ fprMINIMUMABILITYSCORE, abINTELLIGENCE, 13 },
	{ 0, 0, 0 } };

static FEATPREREQ combatReflexesPR[] = {	{ 0, 0, 0 } };

static FEATPREREQ craftMagicArmsAndArmorPR[] = {
	{ fprMINIMUMSPELLCASTERLEVEL, 5, 0 },
	{ 0, 0, 0 } };

static FEATPREREQ craftRodPR[] = {
	{ fprMINIMUMSPELLCASTERLEVEL, 9, 0 },
	{ 0, 0, 0 } };

static FEATPREREQ craftStaffPR[] = {
	{ fprMINIMUMSPELLCASTERLEVEL, 12, 0 },
	{ 0, 0, 0 } };

static FEATPREREQ craftWandPR[] = {
	{ fprMINIMUMSPELLCASTERLEVEL, 5, 0 },
	{ 0, 0, 0 } };

static FEATPREREQ craftWondrousItemPR[] = {
	{ fprMINIMUMSPELLCASTERLEVEL, 3, 0 },
	{ 0, 0, 0 } };

static FEATPREREQ deceitfulPR[] = {	{ 0, 0, 0 } };

static FEATPREREQ deflectArrowsPR[] = {
	{ fprMINIMUMABILITYSCORE, abDEXTERITY, 13 },
	{ fprFEAT, ftIMPROVEDUNARMEDSTRIKE, 0 },
	{ 0, 0, 0 } };

static FEATPREREQ deftHandsPR[] = {	{ 0, 0, 0 } };

static FEATPREREQ diehardPR[] = {
	{ fprFEAT, ftENDURANCE, 0 },
	{ 0, 0, 0 } };

static FEATPREREQ diligentPR[] = {	{ 0, 0, 0 } };

static FEATPREREQ dodgePR[] = {
	{ fprMINIMUMABILITYSCORE, abDEXTERITY, 13 },
	{ 0, 0, 0 } };

static FEATPREREQ empowerSpellPR[] = {	{ 0, 0, 0 } };

static FEATPREREQ endurancePR[] = {	{ 0, 0, 0 } };

static FEATPREREQ enlargeSpellPR[] = {	{ 0, 0, 0 } };

static FEATPREREQ eschewMaterialsPR[] = {	{ 0, 0, 0 } };

static FEATPREREQ exoticWeaponProfPR[] = {
	{ fprMINIMUMBASEATTACKBONUS, 1, 0 },
	{ 0, 0, 0 } };

static FEATPREREQ extendSpellPR[] = {	{ 0, 0, 0 } };

static FEATPREREQ extraTurningPR[] = {
	{ fprCLERICORPALADIN, 0, 0 },
	{ 0, 0, 0 } };

static FEATPREREQ farShotPR[] = {
	{ fprFEAT, ftPOINTBLANKSHOT, 0 },
	{ 0, 0, 0 } };

static FEATPREREQ forgeRingPR[] = {
	{ fprMINIMUMSPELLCASTERLEVEL, 12, 0 },
	{ 0, 0, 0 } };

static FEATPREREQ greatCleavePR[] = {
	{ fprMINIMUMABILITYSCORE, abSTRENGTH, 13 },
	{ fprFEAT, ftPOWERATTACK, 0 },
	{ fprFEAT, ftCLEAVE, 0 },
	{ fprMINIMUMBASEATTACKBONUS, 4, 0 },
	{ 0, 0, 0 } };

static FEATPREREQ greatFortitudePR[] = {	{ 0, 0, 0 } };

static FEATPREREQ greaterSpellFocusPR[] = {
	{ fprFEAT, ftSPELLFOCUS, 0 },
	{ 0, 0, 0 } };

static FEATPREREQ greaterSpellPenetrationPR[] = {
	{ fprFEAT, ftSPELLPENETRATION, 0 },
	{ 0, 0, 0 } };

static FEATPREREQ greaterTwoWeaponFightingPR[] = {
	{ fprMINIMUMABILITYSCORE, abDEXTERITY, 19 },
	{ fprFEAT, ftTWOWEAPONFIGHTING, 0 },
	{ fprFEAT, ftIMPROVEDTWOWEAPONFIGHTING, 0 },
	{ fprMINIMUMBASEATTACKBONUS, 11, 0 },
	{ 0, 0, 0 } };

static FEATPREREQ greaterWeaponFocusPR[] = {
	{ fprFEAT, ftWEAPONFOCUS, 0 },
	{ fprMINIMUMFIGHTERLEVEL, 8, 0 },
	{ 0, 0, 0 } };

static FEATPREREQ greaterWeaponSpecializationPR[] = {
	{ fprFEAT, ftWEAPONFOCUS, 0 },
	{ fprFEAT, ftGREATERWEAPONFOCUS, 0 },
	{ fprFEAT, ftWEAPONSPECIALIZATION, 0 },
	{ fprMINIMUMFIGHTERLEVEL, 8, 0 },
	{ 0, 0, 0 } };

static FEATPREREQ heightenSpellPR[] = {	{ 0, 0, 0 } };

static FEATPREREQ improvedBullRushPR[] = {
	{ fprMINIMUMABILITYSCORE, abSTRENGTH, 13 },
	{ fprFEAT, ftPOWERATTACK, 0 },
	{ 0, 0, 0 } };

static FEATPREREQ improvedCounterspellPR[] = {	{ 0, 0, 0 } };

static FEATPREREQ improvedCriticalPR[] = {
	{ fprMINIMUMBASEATTACKBONUS, 8, 0 },
	{ fprPROFICIENTWITHWEAPON, 0, 0 },
	{ 0, 0, 0 } };

static FEATPREREQ improvedDisarmPR[] = {
	{ fprMINIMUMABILITYSCORE, abINTELLIGENCE, 13 },
	{ fprFEAT, ftCOMBATEXPERTISE, 0 },
	{ 0, 0, 0 } };

static FEATPREREQ improvedFamiliarPR[] = {	{ 0, 0, 0 } };

static FEATPREREQ improvedFeintPR[] = {
	{ fprMINIMUMABILITYSCORE, abINTELLIGENCE, 13 },
	{ fprFEAT, ftCOMBATEXPERTISE, 0 },
	{ 0, 0, 0 } };

static FEATPREREQ improvedGrapplePR[] = {
	{ fprMINIMUMABILITYSCORE, abDEXTERITY, 13 },
	{ fprFEAT, ftIMPROVEDUNARMEDSTRIKE, 0 },
	{ 0, 0, 0 } };

static FEATPREREQ improvedInitiativePR[] = {	{ 0, 0, 0 } };

static FEATPREREQ improvedOverrunPR[] = {
	{ fprMINIMUMABILITYSCORE, abSTRENGTH, 13 },
	{ fprFEAT, ftPOWERATTACK, 0 },
	{ 0, 0, 0 } };

static FEATPREREQ improvedPreciseShotPR[] = {
	{ fprMINIMUMABILITYSCORE, abDEXTERITY, 19 },
	{ fprFEAT, ftPOINTBLANKSHOT, 0 },
	{ fprFEAT, ftPRECISESHOT, 0 },
	{ fprMINIMUMBASEATTACKBONUS, 11, 0 },
	{ 0, 0, 0 } };

static FEATPREREQ improvedShieldBashPR[] = {
	{ fprFEAT, ftSHIELDPROFICIENCY, 0 },
	{ 0, 0, 0 } };

static FEATPREREQ improvedSunderPR[] = {
	{ fprMINIMUMABILITYSCORE, abSTRENGTH, 13 },
	{ fprFEAT, ftPOWERATTACK, 0 },
	{ 0, 0, 0 } };

static FEATPREREQ improvedTripPR[] = {
	{ fprMINIMUMABILITYSCORE, abINTELLIGENCE, 13 },
	{ fprFEAT, ftCOMBATEXPERTISE, 0 },
	{ 0, 0, 0 } };

static FEATPREREQ improvedTurningPR[] = {
	{ fprCLERICORPALADIN, 0, 0 },
	{ 0, 0, 0 } };

static FEATPREREQ improvedTwoWeaponFightingPR[] = {
	{ fprMINIMUMABILITYSCORE, abDEXTERITY, 17 },
	{ fprFEAT, ftTWOWEAPONFIGHTING, 0 },
	{ fprMINIMUMBASEATTACKBONUS, 6, 0 },
	{ 0, 0, 0 } };

static FEATPREREQ improvedUnarmedStrikePR[] = {	{ 0, 0, 0 } };

static FEATPREREQ investigatorPR[] = {	{ 0, 0, 0 } };

static FEATPREREQ ironWillPR[] = {	{ 0, 0, 0 } };

static FEATPREREQ leadershipPR[] = {
	{ fprMINIMUMCHARACTERLEVEL, 6, 0 },
	{ 0, 0, 0 } };

static FEATPREREQ lightningReflexesPR[] = {	{ 0, 0, 0 } };

static FEATPREREQ magicalAptitudePR[] = {	{ 0, 0, 0 } };

static FEATPREREQ manyshotPR[] = {
	{ fprMINIMUMABILITYSCORE, abDEXTERITY, 17 },
	{ fprFEAT, ftPOINTBLANKSHOT, 0 },
	{ fprFEAT, ftRAPIDSHOT, 0 },
	{ fprMINIMUMBASEATTACKBONUS, 6, 0 },
	{ 0, 0, 0 } };

static FEATPREREQ martialWeaponProfPR[] = {	{ 0, 0, 0 } };

static FEATPREREQ maximizeSpellPR[] = {	{ 0, 0, 0 } };

static FEATPREREQ mobilityPR[] = {
	{ fprMINIMUMABILITYSCORE, abDEXTERITY, 13 },
	{ fprFEAT, ftDODGE, 0 },
	{ 0, 0, 0 } };

static FEATPREREQ mountedArcheryPR[] = {
	{ fprFEAT, ftMOUNTEDCOMBAT, 0 },
	{ fprSKILL, skRIDE, 0 },
	{ 0, 0, 0 } };

static FEATPREREQ mountedCombatPR[] = {
	{ fprSKILL, skRIDE, 0 },
	{ 0, 0, 0 } };

static FEATPREREQ naturalSpellPR[] = {
	{ fprMINIMUMABILITYSCORE, abWISDOM, 13 },
	{ fprMINIMUMDRUIDLEVEL, 5, 0 },
	{ 0, 0, 0 } };

static FEATPREREQ negotiatorPR[] = {	{ 0, 0, 0 } };

static FEATPREREQ nimbleFingersPR[] = {	{ 0, 0, 0 } };

static FEATPREREQ persuasivePR[] = {	{ 0, 0, 0 } };

static FEATPREREQ pointBlankShotPR[] = {	{ 0, 0, 0 } };

static FEATPREREQ powerAttackPR[] = {
	{ fprMINIMUMABILITYSCORE, abSTRENGTH, 13 },
	{ 0, 0, 0 } };

static FEATPREREQ preciseShotPR[] = {
	{ fprFEAT, ftPOINTBLANKSHOT, 0 },
	{ 0, 0, 0 } };

static FEATPREREQ quickDrawPR[] = {
	{ fprMINIMUMBASEATTACKBONUS, 1, 0 },
	{ 0, 0, 0 } };

static FEATPREREQ quickenSpellPR[] = {	{ 0, 0, 0 } };

static FEATPREREQ rapidReloadPR[] = {	{ 0, 0, 0 } };

static FEATPREREQ rapidShotPR[] = {
	{ fprMINIMUMABILITYSCORE, abDEXTERITY, 13 },
	{ fprFEAT, ftPOINTBLANKSHOT, 0 },
	{ 0, 0, 0 } };

static FEATPREREQ rideByAttackPR[] = {
	{ fprFEAT, ftMOUNTEDCOMBAT, 0 },
	{ fprSKILL, skRIDE, 0 },
	{ 0, 0, 0 } };

static FEATPREREQ runPR[] = {	{ 0, 0, 0 } };

static FEATPREREQ scribeScrollPR[] = {
	{ fprMINIMUMSPELLCASTERLEVEL, 1, 0 },
	{ 0, 0, 0 } };

static FEATPREREQ selfSufficientPR[] = {	{ 0, 0, 0 } };

static FEATPREREQ shieldProfPR[] = {	{ 0, 0, 0 } };

static FEATPREREQ shotontheRunPR[] = {
	{ fprMINIMUMABILITYSCORE, abDEXTERITY, 13 },
	{ fprFEAT, ftPOINTBLANKSHOT, 0 },
	{ fprFEAT, ftDODGE, 0 },
	{ fprFEAT, ftMOBILITY, 0 },
	{ fprMINIMUMBASEATTACKBONUS, 4, 0 },
	{ 0, 0, 0 } };

static FEATPREREQ silentSpellPR[] = {	{ 0, 0, 0 } };

static FEATPREREQ simpleWeaponProfPR[] = {	{ 0, 0, 0 } };

static FEATPREREQ skillFocusPR[] = {	{ 0, 0, 0 } };

static FEATPREREQ snatchArrowsPR[] = {
	{ fprMINIMUMABILITYSCORE, abDEXTERITY, 15 },
	{ fprFEAT, ftIMPROVEDUNARMEDSTRIKE, 0 },
	{ fprFEAT, ftDEFLECTARROWS, 0 },
	{ 0, 0, 0 } };

static FEATPREREQ spellFocusPR[] = {	{ 0, 0, 0 } };

static FEATPREREQ spellMasteryPR[] = {
	{ fprWIZARD, 0, 0 },
	{ 0, 0, 0 } };

static FEATPREREQ spellPenetrationPR[] = {	{ 0, 0, 0 } };

static FEATPREREQ spiritedChargePR[] = {
	{ fprFEAT, ftMOUNTEDCOMBAT, 0 },
	{ fprFEAT, ftRIDEBYATTACK, 0 },
	{ fprSKILL, skRIDE, 0 },
	{ 0, 0, 0 } };

static FEATPREREQ springAttackPR[] = {
	{ fprMINIMUMABILITYSCORE, abDEXTERITY, 13 },
	{ fprFEAT, ftDODGE, 0 },
	{ fprFEAT, ftMOBILITY, 0 },
	{ fprMINIMUMBASEATTACKBONUS, 4, 0 },
	{ 0, 0, 0 } };

static FEATPREREQ stealthyPR[] = {	{ 0, 0, 0 } };

static FEATPREREQ stillSpellPR[] = {	{ 0, 0, 0 } };

static FEATPREREQ stunningFistPR[] = {
	{ fprMINIMUMABILITYSCORE, abDEXTERITY, 13 },
	{ fprMINIMUMABILITYSCORE, abWISDOM, 13 },
	{ fprFEAT, ftIMPROVEDUNARMEDSTRIKE, 0 },
	{ fprMINIMUMBASEATTACKBONUS, 8, 0 },
	{ 0, 0, 0 } };

static FEATPREREQ toughnessPR[] = {	{ 0, 0, 0 } };

static FEATPREREQ towerShieldProfPR[] = {
	{ fprFEAT, ftSHIELDPROFICIENCY, 0 },
	{ fprMINIMUMFIGHTERLEVEL, 1, 0 },
	{ 0, 0, 0 } };

static FEATPREREQ trackPR[] = {	{ 0, 0, 0 } };

static FEATPREREQ tramplePR[] = {
	{ fprFEAT, ftMOUNTEDCOMBAT, 0 },
	{ fprSKILL, skRIDE, 0 },
	{ 0, 0, 0 } };

static FEATPREREQ twoWeaponFightingPR[] = {
	{ fprMINIMUMABILITYSCORE, abDEXTERITY, 15 },
	{ fprFEAT, ftRANGERTWOWEAPONFIGHTING, 0 },
	{ 0, 0, 0 } };

static FEATPREREQ twoWeaponDefensePR[] = {
	{ fprMINIMUMABILITYSCORE, abDEXTERITY, 15 },
	{ fprFEAT, ftTWOWEAPONFIGHTING, 0 },
	{ 0, 0, 0 } };

static FEATPREREQ weaponFinessePR[] = {
	{ fprMINIMUMBASEATTACKBONUS, 1, 0 },
	{ 0, 0, 0 } };

static FEATPREREQ weaponFocusPR[] = {
	{ fprMINIMUMBASEATTACKBONUS, 1, 0 },
	{ fprPROFICIENTWITHWEAPON, 0, 0 },
	{ 0, 0, 0 } };

static FEATPREREQ weaponSpecializationPR[] = {
	{ fprFEAT, ftWEAPONFOCUS, 0 },
	{ fprMINIMUMFIGHTERLEVEL, 4, 0 },
	{ 0, 0, 0 } };

static FEATPREREQ whirlwindAttackPR[] = {
	{ fprMINIMUMABILITYSCORE, abDEXTERITY, 13 },
	{ fprMINIMUMABILITYSCORE, abINTELLIGENCE, 13 },
	{ fprFEAT, ftDODGE, 0 },
	{ fprFEAT, ftMOBILITY, 0 },
	{ fprFEAT, ftSPRINGATTACK, 0 },
	{ fprFEAT, ftCOMBATEXPERTISE, 0 },
	{ fprMINIMUMBASEATTACKBONUS, 4, 0 },
	{ 0, 0, 0 } };

static FEATPREREQ widenSpellPR[] = {	{ 0, 0, 0 } };

static FEATPREREQ abilityFocusPR[] = {	{ 0, 0, 0 } };

static FEATPREREQ awesomeBlowPR[] = {
	{ fprMINIMUMABILITYSCORE, abSTRENGTH, 25 },
	{ fprFEAT, ftPOWERATTACK, 0 },
	{ fprFEAT, ftIMPROVEDBULLRUSH, 0 },
	{ 0, 0, 0 } };

static FEATPREREQ craftConstructPR[] = {
	{ fprFEAT, ftCRAFTMAGICARMSANDARMOR, 0 },
	{ fprFEAT, ftCRAFTWONDROUSITEM, 0 },
	{ 0, 0, 0 } };

static FEATPREREQ empowerSpellLikeAbilityPR[] = {	{ 0, 0, 0 } };

static FEATPREREQ flybyAttackPR[] = {	{ 0, 0, 0 } };

static FEATPREREQ hoverPR[] = {	{ 0, 0, 0 } };

static FEATPREREQ improvedNaturalArmorPR[] = {
	{ fprMINIMUMABILITYSCORE, abCONSTITUTION, 13 },
	{ 0, 0, 0 } };

static FEATPREREQ improvedNaturalAttackPR[] = {
	{ fprMINIMUMBASEATTACKBONUS, 4, 0 },
	{ 0, 0, 0 } };

static FEATPREREQ multiweaponFightingPR[] = {
	{ fprMINIMUMABILITYSCORE, abDEXTERITY, 13 },
	{ 0, 0, 0 } };

static FEATPREREQ multiattackPR[] = {	{ 0, 0, 0 } };

static FEATPREREQ quickenSpellLikeAbilityPR[] = {	{ 0, 0, 0 } };

static FEATPREREQ snatchPR[] = {	{ 0, 0, 0 } };

static FEATPREREQ wingoverPR[] = {	{ 0, 0, 0 } };

static FEATPREREQ rangerArcheryPR[] = {
	{ fprEXACTRANGERLEVEL, 2, 0 },
	{ 0, 0, 0 } };

static FEATPREREQ rangerTwoWeaponFightingPR[] = {
	{ fprEXACTRANGERLEVEL, 2, 0 },
	{ 0, 0, 0 } };

static FEATPREREQ rangerImprovedArcheryPR[] = {
	{ fprFEAT, ftRANGERARCHERY, 0 },
	{ fprEXACTRANGERLEVEL, 6, 0 },
	{ 0, 0, 0 } };

static FEATPREREQ rangerImprovedTwoWeaponFightingPR[] = {
	{ fprFEAT, ftRANGERTWOWEAPONFIGHTING, 0 },
	{ fprEXACTRANGERLEVEL, 6, 0 },
	{ 0, 0, 0 } };

static FEATPREREQ rangerGreaterArcheryPR[] = {
	{ fprFEAT, ftRANGERIMPROVEDARCHERY, 0 },
	{ fprEXACTRANGERLEVEL, 11, 0 },
	{ 0, 0, 0 } };

static FEATPREREQ rangerGreaterTwoWeaponFightingPR[] = {
	{ fprFEAT, ftRANGERIMPROVEDTWOWEAPONFIGHTING, 0 },
	{ fprEXACTRANGERLEVEL, 11, 0 },
	{ 0, 0, 0 } };

static FEATPREREQ evasionPR[] = {	{ 0, 0, 0 } };

/* feat definitions */

static const struct {
  int         id;
  int         type;
  int         multi;
  FEATPREREQ* prereqs;
  char*       name;
} s_feats[] = {
  { ftABILITYFOCUS,                  fttGENERAL,      0, abilityFocusPR,                 "Ability Focus" },
  { ftACROBATIC,                  fttGENERAL,      0, acrobaticPR,                 "Acrobatic" },
  { ftAGILE,                  fttGENERAL,      0, agilePR,                 "Agile" },
  { ftALERTNESS,                  fttGENERAL,      0, alertnessPR,                 "Alertness" },
  { ftANIMALAFFINITY,                  fttGENERAL,      0, animalAffinityPR,                 "Animal Affinity" },
  { ftARMORPROFICIENCY_HEAVY,                  fttGENERAL,      0, armorProfHeavyPR,                 "Armor Proficiency (Heavy)" },
  { ftARMORPROFICIENCY_LIGHT,                  fttGENERAL,      0, armorProfLightPR,                 "Armor Proficiency (Light)" },
  { ftARMORPROFICIENCY_MEDIUM,                  fttGENERAL,      0, armorProfMedPR,                 "Armor Proficiency (Medium)" },
  { ftATHLETIC,                  fttGENERAL,      0, athleticPR,                 "Athletic" },
  { ftAUGMENTSUMMONING,                  fttGENERAL,      0, augmentSummoningPR,                 "Augment Summoning" },
  { ftAWESOMEBLOW,                  fttGENERAL,      0, awesomeBlowPR,                 "Awesome Blow" },
  { ftBLINDFIGHT,                  fttGENERAL,      0, blindfightPR,                 "Blind-Fight" },
  { ftBREWPOTION,                  fttITEMCREATION,      0, brewPotionPR,                 "Brew Potion" },
  { ftCLEAVE,                  fttGENERAL,      0, cleavePR,                 "Cleave" },
  { ftCOMBATCASTING,                  fttGENERAL,      0, combatCastingPR,                 "Combat Casting" },
  { ftCOMBATEXPERTISE,                  fttGENERAL,      0, combatExpertisePR,                 "Combat Expertise" },
  { ftCOMBATREFLEXES,                  fttGENERAL,      0, combatReflexesPR,                 "Combat Reflexes" },
  { ftCRAFTCONSTRUCT,                  fttITEMCREATION,      0, craftConstructPR,                 "Craft Construct" },
  { ftCRAFTMAGICARMSANDARMOR,                  fttITEMCREATION,      0, craftMagicArmsAndArmorPR,                 "Craft Magic Arms and Armor" },
  { ftCRAFTROD,                  fttITEMCREATION,      0, craftRodPR,                 "Craft Rod" },
  { ftCRAFTSTAFF,                  fttITEMCREATION,      0, craftStaffPR,                 "Craft Staff" },
  { ftCRAFTWAND,                  fttITEMCREATION,      0, craftWandPR,                 "Craft Wand" },
  { ftCRAFTWONDROUSITEM,                  fttITEMCREATION,      0, craftWondrousItemPR,                 "Craft Wondrous Item" },
  { ftDECEITFUL,                  fttGENERAL,      0, deceitfulPR,                 "Deceitful" },
  { ftDEFLECTARROWS,                  fttGENERAL,      0, deflectArrowsPR,                 "Deflect Arrows" },
  { ftDEFTHANDS,                  fttGENERAL,      0, deftHandsPR,                 "Deft Hands" },
  { ftDIEHARD,                  fttGENERAL,      0, diehardPR,                 "Diehard" },
  { ftDILIGENT,                  fttGENERAL,      0, diligentPR,                 "Diligent" },
  { ftDODGE,                  fttGENERAL,      0, dodgePR,                 "Dodge" },
  { ftEMPOWERSPELL,                  fttMETAMAGIC,      0, empowerSpellPR,                 "Empower Spell" },
  { ftEMPOWERSPELLLIKEABILITY,                  fttGENERAL,      0, empowerSpellLikeAbilityPR,                 "Empower Spell-Like Ability" },
  { ftENDURANCE,                  fttGENERAL,      0, endurancePR,                 "Endurance" },
  { ftENLARGESPELL,                  fttMETAMAGIC,      0, enlargeSpellPR,                 "Enlarge Spell" },
  { ftESCHEWMATERIALS,                  fttGENERAL,      0, eschewMaterialsPR,                 "Eschew Materials" },
  { ftEXOTICWEAPONPROFICIENCY,                  fttGENERAL,      1, exoticWeaponProfPR,                 "Exotic Weapon Proficiency" },
  { ftEXTENDSPELL,                  fttMETAMAGIC,      0, extendSpellPR,                 "Extend Spell" },
  { ftEXTRATURNING,                  fttGENERAL,      1, extraTurningPR,                 "Extra Turning" },
  { ftFARSHOT,                  fttGENERAL,      0, farShotPR,                 "Far Shot" },
  { ftFLYBYATTACK,                  fttGENERAL,      0, flybyAttackPR,                 "Flyby Attack" },
  { ftFORGERING,                  fttITEMCREATION,      0, forgeRingPR,                 "Forge Ring" },
  { ftGREATCLEAVE,                  fttGENERAL,      0, greatCleavePR,                 "Great Cleave" },
  { ftGREATERSPELLFOCUS,                  fttGENERAL,      1, greaterSpellFocusPR,                 "Greater Spell Focus" },
  { ftGREATERSPELLPENETRATION,                  fttGENERAL,      0, greaterSpellPenetrationPR,                 "Greater Spell Penetration" },
  { ftGREATERTWOWEAPONFIGHTING,                  fttGENERAL,      0, greaterTwoWeaponFightingPR,                 "Greater Two Weapon Fighting" },
  { ftGREATERWEAPONFOCUS,                  fttGENERAL,      1, greaterWeaponFocusPR,                 "Greater Weapon Focus" },
  { ftGREATERWEAPONSPECIALIZATION,                  fttGENERAL,      1, greaterWeaponSpecializationPR,                 "Greater Weapon Specialization" },
  { ftGREATFORTITUDE,                  fttGENERAL,      0, greatFortitudePR,                 "Great Fortitude" },
  { ftHEIGHTENSPELL,                  fttMETAMAGIC,      0, heightenSpellPR,                 "Heighten Spell" },
  { ftHOVER,                  fttGENERAL,      0, hoverPR,                 "Hover" },
  { ftIMPROVEDBULLRUSH,                  fttGENERAL,      0, improvedBullRushPR,                 "Improved Bull Rush" },
  { ftIMPROVEDCOUNTERSPELL,                  fttGENERAL,      0, improvedCounterspellPR,                 "Improved Counterspell" },
  { ftIMPROVEDCRITICAL,                  fttGENERAL,      1, improvedCriticalPR,                 "Improved Critical" },
  { ftIMPROVEDDISARM,                  fttGENERAL,      0, improvedDisarmPR,                 "Improved Disarm" },
  { ftIMPROVEDFAMILIAR,                  fttGENERAL,      0, improvedFamiliarPR,                 "Improved Familiar" },
  { ftIMPROVEDFEINT,                  fttGENERAL,      0, improvedFeintPR,                 "Improved Feint" },
  { ftIMPROVEDGRAPPLE,                  fttGENERAL,      0, improvedGrapplePR,                 "Improved Grapple" },
  { ftIMPROVEDINITIATIVE,                  fttGENERAL,      0, improvedInitiativePR,                 "Improved Initiative" },
  { ftIMPROVEDNATURALARMOR,                  fttGENERAL,      0, improvedNaturalArmorPR,                 "Improved Natural Armor" },
  { ftIMPROVEDNATURALATTACK,                  fttGENERAL,      0, improvedNaturalAttackPR,                 "Improved Natural Attack" },
  { ftIMPROVEDOVERRUN,                  fttGENERAL,      0, improvedOverrunPR,                 "Improved Overrun" },
  { ftIMPROVEDPRECISESHOT,                  fttGENERAL,      0, improvedPreciseShotPR,                 "Improved Precise Shot" },
  { ftIMPROVEDSHIELDBASH,                  fttGENERAL,      0, improvedShieldBashPR,                 "Improved Shield Bash" },
  { ftIMPROVEDSUNDER,                  fttGENERAL,      0, improvedSunderPR,                 "Improved Sunder" },
  { ftIMPROVEDTRIP,                  fttGENERAL,      0, improvedTripPR,                 "Improved Trip" },
  { ftIMPROVEDTURNING,                  fttGENERAL,      0, improvedTurningPR,                 "Improved Turning" },
  { ftIMPROVEDTWOWEAPONFIGHTING,                  fttGENERAL,      0, improvedTwoWeaponFightingPR,                 "Improved Two Weapon Fighting" },
  { ftIMPROVEDUNARMEDSTRIKE,                  fttGENERAL,      0, improvedUnarmedStrikePR,                 "Improved Unarmed Strike" },
  { ftINVESTIGATOR,                  fttGENERAL,      0, investigatorPR,                 "Investigator" },
  { ftIRONWILL,                  fttGENERAL,      0, ironWillPR,                 "Iron Will" },
  { ftLEADERSHIP,                  fttGENERAL,      0, leadershipPR,                 "Leadership" },
  { ftLIGHTNINGREFLEXES,                  fttGENERAL,      0, lightningReflexesPR,                 "Lightning Reflexes" },
  { ftMAGICALAPTITUDE,                  fttGENERAL,      0, magicalAptitudePR,                 "Magical Aptitude" },
  { ftMANYSHOT,                  fttGENERAL,      0, manyshotPR,                 "Manyshot" },
  { ftMARTIALWEAPONPROFICIENCY,                  fttGENERAL,      1, martialWeaponProfPR,                 "Martial Weapon Proficiency" },
  { ftMAXIMIZESPELL,                  fttMETAMAGIC,      0, maximizeSpellPR,                 "Maximize Spell" },
  { ftMOBILITY,                  fttGENERAL,      0, mobilityPR,                 "Mobility" },
  { ftMOUNTEDARCHERY,                  fttGENERAL,      0, mountedArcheryPR,                 "Mounted Archery" },
  { ftMOUNTEDCOMBAT,                  fttGENERAL,      0, mountedCombatPR,                 "Mounted Combat" },
  { ftMULTIATTACK,                  fttGENERAL,      0, multiattackPR,                 "Multiattack" },
  { ftMULTIWEAPONFIGHTING,                  fttGENERAL,      0, multiweaponFightingPR,                 "Multiweapon Fighting" },
  { ftNATURALSPELL,                  fttGENERAL,      0, naturalSpellPR,                 "Natural Spell" },
  { ftNEGOTIATOR,                  fttGENERAL,      0, negotiatorPR,                 "Negotiator" },
  { ftNIMBLEFINGERS,                  fttGENERAL,      0, nimbleFingersPR,                 "Nimble Fingers" },
  { ftPERSUASIVE,                  fttGENERAL,      0, persuasivePR,                 "Persuasive" },
  { ftPOINTBLANKSHOT,                  fttGENERAL,      0, pointBlankShotPR,                 "Point Blank Shot" },
  { ftPOWERATTACK,                  fttGENERAL,      0, powerAttackPR,                 "Power Attack" },
  { ftPRECISESHOT,                  fttGENERAL,      0, preciseShotPR,                 "Precise Shot" },
  { ftQUICKDRAW,                  fttGENERAL,      0, quickDrawPR,                 "Quick Draw" },
  { ftQUICKENSPELL,                  fttMETAMAGIC,      0, quickenSpellPR,                 "Quicken Spell" },
  { ftQUICKENSPELLLIKEABILITY,                  fttGENERAL,      0, quickenSpellLikeAbilityPR,                 "Quicken Spell-Like Ability" },
  { ftRANGERARCHERY,                  fttSPECIAL,      0, rangerArcheryPR,                 "Ranger Archery" },
  { ftRANGERGREATERARCHERY,                  fttSPECIAL,      0, rangerGreaterArcheryPR,                 "Ranger Greater Archery" },
  { ftRANGERGREATERTWOWEAPONFIGHTING,                  fttSPECIAL,      0, rangerGreaterTwoWeaponFightingPR,                 "Ranger Greater Two Weapon Fighting" },
  { ftRANGERIMPROVEDARCHERY,                  fttSPECIAL,      0, rangerImprovedArcheryPR,                 "Ranger Improved Archery" },
  { ftRANGERIMPROVEDTWOWEAPONFIGHTING,                  fttSPECIAL,      0, rangerImprovedTwoWeaponFightingPR,                 "Ranger Improved Two Weapon Fighting" },
  { ftRANGERTWOWEAPONFIGHTING,                  fttSPECIAL,      0, rangerTwoWeaponFightingPR,                 "Ranger Two Weapon Fighting" },
  { ftRAPIDRELOAD,                  fttGENERAL,      1, rapidReloadPR,                 "Rapid Reload" },
  { ftRAPIDSHOT,                  fttGENERAL,      0, rapidShotPR,                 "Rapid Shot" },
  { ftRIDEBYATTACK,                  fttGENERAL,      0, rideByAttackPR,                 "Ride By Attack" },
  { ftRUN,                  fttGENERAL,      0, runPR,                 "Run" },
  { ftSCRIBESCROLL,                  fttITEMCREATION,      0, scribeScrollPR,                 "Scribe Scroll" },
  { ftSELFSUFFICIENT,                  fttGENERAL,      0, selfSufficientPR,                 "Self Sufficient" },
  { ftSHIELDPROFICIENCY,                  fttGENERAL,      0, shieldProfPR,                 "Shield Proficiency" },
  { ftSHOTONTHERUN,                  fttGENERAL,      0, shotontheRunPR,                 "Shot on the Run" },
  { ftSILENTSPELL,                  fttMETAMAGIC,      0, silentSpellPR,                 "Silent Spell" },
  { ftSIMPLEWEAPONPROFICIENCY,                  fttGENERAL,      1, simpleWeaponProfPR,                 "Simple Weapon Proficiency" },
  { ftSKILLFOCUS,                  fttGENERAL,      1, skillFocusPR,                 "Skill Focus" },
  { ftSNATCH,                  fttGENERAL,      0, snatchPR,                 "Snatch" },
  { ftSNATCHARROWS,                  fttGENERAL,      0, snatchArrowsPR,                 "Snatch Arrows" },
  { ftSPELLFOCUS,                  fttGENERAL,      1, spellFocusPR,                 "Spell Focus" },
  { ftSPELLMASTERY,                  fttSPECIAL,      1, spellMasteryPR,                 "Spell Mastery" },
  { ftSPELLPENETRATION,                  fttGENERAL,      0, spellPenetrationPR,                 "Spell Penetration" },
  { ftSPIRITEDCHARGE,                  fttGENERAL,      0, spiritedChargePR,                 "Spirited Charge" },
  { ftSPRINGATTACK,                  fttGENERAL,      0, springAttackPR,                 "Spring Attack" },
  { ftSTEALTHY,                  fttGENERAL,      0, stealthyPR,                 "Stealthy" },
  { ftSTILLSPELL,                  fttMETAMAGIC,      0, stillSpellPR,                 "Still Spell" },
  { ftSTUNNINGFIST,                  fttGENERAL,      0, stunningFistPR,                 "Stunning Fist" },
  { ftTOUGHNESS,                  fttGENERAL,      1, toughnessPR,                 "Toughness" },
  { ftTOWERSHIELDPROFICIENCY,                  fttGENERAL,      0, towerShieldProfPR,                 "Tower Shield Proficiency" },
  { ftTRACK,                  fttGENERAL,      0, trackPR,                 "Track" },
  { ftTRAMPLE,                  fttGENERAL,      0, tramplePR,                 "Trample" },
  { ftTWOWEAPONDEFENSE,                  fttGENERAL,      0, twoWeaponDefensePR,                 "Two Weapon Defense" },
  { ftTWOWEAPONFIGHTING,                  fttGENERAL,      0, twoWeaponFightingPR,                 "Two Weapon Fighting" },
  { ftWEAPONFINESSE,                  fttGENERAL,      0, weaponFinessePR,                 "Weapon Finesse" },
  { ftWEAPONFOCUS,                  fttGENERAL,      1, weaponFocusPR,                 "Weapon Focus" },
  { ftWEAPONSPECIALIZATION,                  fttSPECIAL,      1, weaponSpecializationPR,                 "Weapon Specialization" },
  { ftWHIRLWINDATTACK,                  fttGENERAL,      0, whirlwindAttackPR,                 "Whirlwind Attack" },
  { ftWIDENSPELL,                  fttMETAMAGIC,      0, widenSpellPR,                 "Widen Spell" },
  { ftWINGOVER,                  fttGENERAL,      0, wingoverPR,                 "Wingover" },
  { ftEVASION,					fttSPECIAL, 0, evasionPR,	"Evasion" },
  { ftIMPROVEDEVASION,					fttSPECIAL, 0, evasionPR,	"Improved Evasion" },
  { 0,                            0,               0,                              0 }
};


static RACIALBONUS dwarvenHBonuses[] = {
  { rbtABILITYSCORE, abCONSTITUTION,  2 },
  { rbtABILITYSCORE, abCHARISMA,     -2 },
  { rbtSKILL,        skCRAFT_ARMORSMITHING,         2 },
  { rbtSKILL,        skCRAFT_BLACKSMITHING,         2 },
  { rbtSKILL,        skCRAFT_STONEMASONRY,         2 },
  { rbtSKILL,        skCRAFT_TRAPMAKING,         2 },
  { rbtSKILL,        skCRAFT_WEAPONSMITHING,         2 },
  { 0,               0,               0 }
};

static RACIALBONUS elvenHBonuses[] = {
  { rbtABILITYSCORE, abDEXTERITY,     2 },
  { rbtABILITYSCORE, abCONSTITUTION, -2 },
  { rbtSKILL,        skLISTEN,        2 },
  { rbtSKILL,        skSEARCH,        2 },
  { rbtSKILL,        skSPOT,          2 },
  { 0,               0,               0 }
};

static RACIALBONUS aqElfBonuses[] = {
  { rbtABILITYSCORE, abDEXTERITY,     2 },
  { rbtABILITYSCORE, abINTELLIGENCE, -2 },
  { rbtSKILL,        skLISTEN,        2 },
  { rbtSKILL,        skSEARCH,        2 },
  { rbtSKILL,        skSPOT,          2 },
  { 0,               0,               0 }
};

static RACIALBONUS gnomeRBonuses[] = {
  { rbtABILITYSCORE, abCONSTITUTION,  2 },
  { rbtABILITYSCORE, abSTRENGTH,     -2 },
  { rbtSKILL,        skLISTEN,        2 },
  { rbtSKILL,        skCRAFT_ALCHEMY,       2 },
  { 0,               0,               0 }
};

static RACIALBONUS halfElvenBonuses[] = {
  { rbtSKILL,        skLISTEN,        1 },
  { rbtSKILL,        skSEARCH,        1 },
  { rbtSKILL,        skSPOT,          1 },
  { rbtSKILL,        skGATHERINFORMATION,   2 },
  { rbtSKILL,        skDIPLOMACY,          2 },
  { 0,               0,               0 }
};

static RACIALBONUS halflingLFBonuses[] = {
  { rbtABILITYSCORE, abDEXTERITY,     2 },
  { rbtABILITYSCORE, abSTRENGTH,     -2 },
  { rbtSKILL,        skCLIMB,         2 },
  { rbtSKILL,        skJUMP,          2 },
  { rbtSKILL,        skMOVESILENTLY,  2 },
  { rbtSKILL,        skLISTEN,        2 },
  { rbtSAVINGTHROW,  svFORTITUDE,     1 },
  { rbtSAVINGTHROW,  svREFLEX,        1 },
  { rbtSAVINGTHROW,  svWILL,          1 },
  { 0,               0,               0 }
};

static RACIALBONUS halforcBonuses[] = {
  { rbtABILITYSCORE, abSTRENGTH,      2 },
  { rbtABILITYSCORE, abINTELLIGENCE, -2 },
  { rbtABILITYSCORE, abCHARISMA,     -2 },
  { 0,               0,               0 }
};

static RACIALBONUS aasimarBonuses[] = {
  { rbtABILITYSCORE, abWISDOM,        2 },
  { rbtABILITYSCORE, abCHARISMA,      2 },
  { rbtSKILL,        skLISTEN,        2 },
  { rbtSKILL,        skSPOT,          2 },
  { 0,               0,               0 }
};

static RACIALBONUS deepDwarfBonuses[] = {
  { rbtABILITYSCORE, abCONSTITUTION,  2 },
  { rbtABILITYSCORE, abCHARISMA,     -4 },
  { 0,               0,               0 }
};

static RACIALBONUS mtnDwarfBonuses[] = {
  { rbtABILITYSCORE, abCONSTITUTION,  2 },
  { rbtABILITYSCORE, abCHARISMA,     -2 },
  { rbtSKILL,        skAPPRAISE,      2 },
  { rbtSKILL,        skCRAFT_ALCHEMY,         2 },
  { rbtSKILL,        skCRAFT_ARMORSMITHING,         2 },
  { rbtSKILL,        skCRAFT_BOWMAKING,         2 },
  { rbtSKILL,        skCRAFT_BLACKSMITHING,         2 },
  { rbtSKILL,        skCRAFT_CARPENTRY,         2 },
  { rbtSKILL,        skCRAFT_LEATHERWORKING,         2 },
  { rbtSKILL,        skCRAFT_PAINTING,         2 },
  { rbtSKILL,        skCRAFT_POTTERY,         2 },
  { rbtSKILL,        skCRAFT_SCULPTING,         2 },
  { rbtSKILL,        skCRAFT_SHIPMAKING,         2 },
  { rbtSKILL,        skCRAFT_STONEMASONRY,         2 },
  { rbtSKILL,        skCRAFT_TRAPMAKING,         2 },
  { rbtSKILL,        skCRAFT_WEAPONSMITHING,         2 },
  { rbtSKILL,        skCRAFT_WOODWORKING,         2 },
  { 0,               0,               0 }
};

static RACIALBONUS grayElfBonuses[] = {
  { rbtABILITYSCORE, abDEXTERITY,     2 },
  { rbtABILITYSCORE, abCONSTITUTION, -2 },
  { rbtABILITYSCORE, abSTRENGTH,     -2 },
  { rbtABILITYSCORE, abINTELLIGENCE,  2 },
  { rbtSKILL,        skLISTEN,        2 },
  { rbtSKILL,        skSEARCH,        2 },
  { rbtSKILL,        skSPOT,          2 },
  { 0,               0,               0 }
};

static RACIALBONUS wildElfBonuses[] = {
  { rbtABILITYSCORE, abDEXTERITY,     2 },
  { rbtABILITYSCORE, abINTELLIGENCE, -2 },
  { rbtSKILL,        skLISTEN,        2 },
  { rbtSKILL,        skSEARCH,        2 },
  { rbtSKILL,        skSPOT,          2 },
  { 0,               0,               0 }
};

static RACIALBONUS woodElfBonuses[] = {
  { rbtABILITYSCORE, abSTRENGTH,      2 },
  { rbtABILITYSCORE, abDEXTERITY,     2 },
  { rbtABILITYSCORE, abCONSTITUTION, -2 },
  { rbtABILITYSCORE, abINTELLIGENCE, -2 },
  { rbtABILITYSCORE, abCHARISMA,     -2 },
  { rbtSKILL,        skLISTEN,        2 },
  { rbtSKILL,        skSEARCH,        2 },
  { rbtSKILL,        skSPOT,          2 },
  { 0,               0,               0 }
};

static RACIALBONUS forestGnomeBonuses[] = {
  { rbtABILITYSCORE, abCONSTITUTION,  2 },
  { rbtABILITYSCORE, abSTRENGTH,     -2 },
  { rbtSKILL,        skHIDE,          4 },
  { 0,               0,               0 }
};

static RACIALBONUS tallfellowBonuses[] = {
  { rbtABILITYSCORE, abDEXTERITY,     2 },
  { rbtABILITYSCORE, abSTRENGTH,     -2 },
  { rbtSKILL,        skLISTEN,        2 },
  { rbtSKILL,        skSPOT,          2 },
  { rbtSKILL,        skSEARCH,        2 },
  { rbtSAVINGTHROW,  svFORTITUDE,     1 },
  { rbtSAVINGTHROW,  svREFLEX,        1 },
  { rbtSAVINGTHROW,  svWILL,          1 },
  { 0,               0,               0 }
};

static RACIALBONUS halflingDeepBonuses[] = {
  { rbtABILITYSCORE, abDEXTERITY,     2 },
  { rbtABILITYSCORE, abSTRENGTH,     -2 },
  { rbtSKILL,        skLISTEN,        2 },
  { rbtSKILL,        skAPPRAISE,      2 },
  { rbtSKILL,        skCRAFT_ALCHEMY,         2 },
  { rbtSKILL,        skCRAFT_ARMORSMITHING,         2 },
  { rbtSKILL,        skCRAFT_BOWMAKING,         2 },
  { rbtSKILL,        skCRAFT_BLACKSMITHING,         2 },
  { rbtSKILL,        skCRAFT_CARPENTRY,         2 },
  { rbtSKILL,        skCRAFT_LEATHERWORKING,         2 },
  { rbtSKILL,        skCRAFT_PAINTING,         2 },
  { rbtSKILL,        skCRAFT_POTTERY,         2 },
  { rbtSKILL,        skCRAFT_SCULPTING,         2 },
  { rbtSKILL,        skCRAFT_SHIPMAKING,         2 },
  { rbtSKILL,        skCRAFT_STONEMASONRY,         2 },
  { rbtSKILL,        skCRAFT_TRAPMAKING,         2 },
  { rbtSKILL,        skCRAFT_WEAPONSMITHING,         2 },
  { rbtSKILL,        skCRAFT_WOODWORKING,         2 },
  { rbtSAVINGTHROW,  svFORTITUDE,     1 },
  { rbtSAVINGTHROW,  svREFLEX,        1 },
  { rbtSAVINGTHROW,  svWILL,          1 },
  { 0,               0,               0 }
};

static RACIALBONUS svirfneblinBonuses[] = {
  { rbtABILITYSCORE, abDEXTERITY,     2 },
  { rbtABILITYSCORE, abWISDOM,        2 },
  { rbtABILITYSCORE, abCHARISMA,     -4 },
  { rbtSKILL,        skHIDE,          2 },
  { rbtSAVINGTHROW,  svFORTITUDE,     2 },
  { rbtSAVINGTHROW,  svREFLEX,        2 },
  { rbtSAVINGTHROW,  svWILL,          2 },
  { rbtARMORCLASS,   0,               4 },
  { 0,               0,               0 }
};

static RACIALBONUS lizardFolkBonuses[] = {
  { rbtABILITYSCORE, abSTRENGTH,      2 },
  { rbtABILITYSCORE, abCONSTITUTION,  2 },
  { rbtABILITYSCORE, abINTELLIGENCE, -2 },
  { rbtATTACK,       0,               1 },
  { rbtSAVINGTHROW,  svREFLEX,        3 },
  { rbtARMORCLASS,   0,               5 },
  { rbtSKILL,        skJUMP,          6 },
  { rbtSKILL,        skSWIM,          8 },
  { rbtSKILL,        skBALANCE,       4 },
  { 0,               0,               0 }
};

static RACIALBONUS dopplegangerBonuses[] = {
  { rbtABILITYSCORE, abSTRENGTH,      2 },
  { rbtABILITYSCORE, abDEXTERITY,     2 },
  { rbtABILITYSCORE, abCONSTITUTION,  2 },
  { rbtABILITYSCORE, abINTELLIGENCE,  2 },
  { rbtABILITYSCORE, abWISDOM,        4 },
  { rbtABILITYSCORE, abCHARISMA,      2 },
  { rbtATTACK,       0,               3 },
  { rbtSAVINGTHROW,  svFORTITUDE,     4 },
  { rbtSAVINGTHROW,  svREFLEX,        4 },
  { rbtSAVINGTHROW,  svWILL,          4 },
  { rbtARMORCLASS,   0,               4 },
  { rbtSKILL,        skBLUFF,        11 },
  { rbtSKILL,        skDISGUISE,     11 },
  { rbtSKILL,        skLISTEN,        7 },
  { rbtSKILL,        skSENSEMOTIVE,   4 },
  { rbtSKILL,        skSPOT,          4 },
  { rbtFEAT,         ftALERTNESS,     0 },
  { rbtFEAT,         ftDODGE,         0 },
  { 0,               0,               0 }
};

static RACIALBONUS goblinBonuses[] = {
  { rbtABILITYSCORE, abSTRENGTH,     -2 },
  { rbtABILITYSCORE, abDEXTERITY,     2 },
  { rbtABILITYSCORE, abCHARISMA,     -2 },
  { rbtSKILL,        skMOVESILENTLY,  4 },
  { 0,               0,               0 }
};

static RACIALBONUS hobgoblinBonuses[] = {
  { rbtABILITYSCORE, abDEXTERITY,     2 },
  { rbtABILITYSCORE, abCONSTITUTION,  2 },
  { rbtSKILL,        skMOVESILENTLY,  4 },
  { 0,               0,               0 }
};

static RACIALBONUS koboldBonuses[] = {
  { rbtABILITYSCORE, abSTRENGTH,     -4 },
  { rbtABILITYSCORE, abDEXTERITY,     2 },
  { rbtARMORCLASS,   0,               1 },
  { rbtSKILL,        skCRAFT_ALCHEMY,         2 },
  { rbtSKILL,        skCRAFT_ARMORSMITHING,         2 },
  { rbtSKILL,        skCRAFT_BOWMAKING,         2 },
  { rbtSKILL,        skCRAFT_BLACKSMITHING,         2 },
  { rbtSKILL,        skCRAFT_CARPENTRY,         2 },
  { rbtSKILL,        skCRAFT_LEATHERWORKING,         2 },
  { rbtSKILL,        skCRAFT_PAINTING,         2 },
  { rbtSKILL,        skCRAFT_POTTERY,         2 },
  { rbtSKILL,        skCRAFT_SCULPTING,         2 },
  { rbtSKILL,        skCRAFT_SHIPMAKING,         2 },
  { rbtSKILL,        skCRAFT_STONEMASONRY,         2 },
  { rbtSKILL,        skCRAFT_TRAPMAKING,         2 },
  { rbtSKILL,        skCRAFT_WEAPONSMITHING,         2 },
  { rbtSKILL,        skCRAFT_WOODWORKING,         2 },
  { rbtSKILL,        skPROFESSION_HUNTER,         2 },
  { rbtSKILL,        skPROFESSION_MINER,         2 },
  { rbtSKILL,        skSEARCH,        2 },
  { 0,               0,               0 }
};

static RACIALBONUS orcBonuses[] = {
  { rbtABILITYSCORE, abSTRENGTH,      4 },
  { rbtABILITYSCORE, abINTELLIGENCE, -2 },
  { rbtABILITYSCORE, abWISDOM,       -2 },
  { rbtABILITYSCORE, abCHARISMA,     -2 },
  { 0,               0,               0 }
};

static RACIALBONUS tieflingBonuses[] = {
  { rbtABILITYSCORE, abDEXTERITY,     2 },
  { rbtABILITYSCORE, abINTELLIGENCE,  2 },
  { rbtABILITYSCORE, abCHARISMA,     -2 },
  { rbtSKILL,        skBLUFF,         2 },
  { rbtSKILL,        skHIDE,          2 },
  { 0,               0,               0 }
};

static RACIALBONUS drowMaleBonuses[] = {
  { rbtABILITYSCORE, abDEXTERITY,     2 },
  { rbtABILITYSCORE, abCONSTITUTION, -2 },
  { rbtABILITYSCORE, abINTELLIGENCE,  2 },
  { rbtABILITYSCORE, abCHARISMA,     -2 },
  { rbtSKILL,        skLISTEN,        2 },
  { rbtSKILL,        skSEARCH,        2 },
  { rbtSKILL,        skSPOT,          2 },
  { 0,               0,               0 }
};

static RACIALBONUS drowFemaleBonuses[] = {
  { rbtABILITYSCORE, abDEXTERITY,     2 },
  { rbtABILITYSCORE, abCONSTITUTION, -2 },
  { rbtABILITYSCORE, abINTELLIGENCE,  2 },
  { rbtABILITYSCORE, abCHARISMA,      2 },
  { rbtSKILL,        skLISTEN,        2 },
  { rbtSKILL,        skSEARCH,        2 },
  { rbtSKILL,        skSPOT,          2 },
  { 0,               0,               0 }
};

static RACIALBONUS duergarBonuses[] = {
  { rbtABILITYSCORE, abCONSTITUTION,  2 },
  { rbtABILITYSCORE, abCHARISMA,     -4 },
  { rbtSKILL,        skLISTEN,        1 },
  { rbtSKILL,        skMOVESILENTLY,  4 },
  { rbtSKILL,        skSPOT,          1 },
  { rbtFEAT,         ftALERTNESS,     0 },
  { 0,               0,               0 }
};

static RACIALBONUS derroBonuses[] = {
  { rbtABILITYSCORE, abSTRENGTH,     -2 },
  { rbtABILITYSCORE, abDEXTERITY,     4 },
  { rbtABILITYSCORE, abCONSTITUTION,  2 },
  { rbtABILITYSCORE, abCHARISMA,     -4 },
  { rbtFEAT,         ftBLINDFIGHT,    0 },
  { 0,               0,               0 }
};

static RACIALBONUS gnollBonuses[] = {
  { rbtABILITYSCORE, abSTRENGTH,      4 },
  { rbtABILITYSCORE, abCONSTITUTION,  2 },
  { rbtABILITYSCORE, abINTELLIGENCE, -2 },
  { rbtABILITYSCORE, abCHARISMA,     -2 },
  { rbtATTACK,       0,               1 },
  { rbtSAVINGTHROW,  svFORTITUDE,     3 },
  { rbtARMORCLASS,   0,               1 },
  { rbtSKILL,        skLISTEN,        3 },
  { rbtSKILL,        skSPOT,          3 },
  { rbtFEAT,         ftPOWERATTACK,   0 },
  { 0,               0,               0 }
};

static RACIALBONUS troglodyteBonuses[] = {
  { rbtABILITYSCORE, abDEXTERITY,    -2 },
  { rbtABILITYSCORE, abCONSTITUTION,  4 },
  { rbtABILITYSCORE, abINTELLIGENCE, -2 },
  { rbtSAVINGTHROW,  svFORTITUDE,     3 },
  { rbtATTACK,       0,               1 },
  { rbtARMORCLASS,   0,               6 },
  { rbtSKILL,        skHIDE,          7 },
  { rbtSKILL,        skLISTEN,        3 },
  { rbtFEAT,         ftMULTIATTACK,   0 },
  { 0,               0,               0 }
};

static RACIALBONUS bugbearBonuses[] = {
  { rbtABILITYSCORE, abSTRENGTH,      4 },
  { rbtABILITYSCORE, abDEXTERITY,     2 },
  { rbtABILITYSCORE, abCONSTITUTION,  2 },
  { rbtABILITYSCORE, abCHARISMA,     -2 },
  { rbtSAVINGTHROW,  svFORTITUDE,     1 },
  { rbtSAVINGTHROW,  svREFLEX,        3 },
  { rbtSAVINGTHROW,  svWILL,          1 },
  { rbtATTACK,       0,               2 },
  { rbtARMORCLASS,   0,               3 },
  { rbtSKILL,        skCLIMB,         2 },
  { rbtSKILL,        skHIDE,          2 },
  { rbtSKILL,        skLISTEN,        1 },
  { rbtSKILL,        skMOVESILENTLY,  2 },
  { rbtSKILL,        skSPOT,          1 },
  { rbtFEAT,         ftALERTNESS,     0 },
  { 0,               0,               0 }
};

static RACIALBONUS ogreBonuses[] = {
  { rbtABILITYSCORE, abSTRENGTH,     10 },
  { rbtABILITYSCORE, abDEXTERITY,    -2 },
  { rbtABILITYSCORE, abCONSTITUTION,  4 },
  { rbtABILITYSCORE, abINTELLIGENCE, -4 },
  { rbtABILITYSCORE, abCHARISMA,     -4 },
  { rbtSAVINGTHROW,  svFORTITUDE,     4 },
  { rbtSAVINGTHROW,  svREFLEX,        1 },
  { rbtSAVINGTHROW,  svWILL,          1 },
  { rbtATTACK,       0,               3 },
  { rbtARMORCLASS,   0,               5 },
  { rbtSKILL,        skCLIMB,         3 },
  { rbtSKILL,        skLISTEN,        3 },
  { rbtSKILL,        skSPOT,          3 },
  { 0,               0,               0 }
};

static RACIALBONUS ogreMageBonuses[] = {
  { rbtABILITYSCORE, abSTRENGTH,     10 },
  { rbtABILITYSCORE, abCONSTITUTION,  6 },
  { rbtABILITYSCORE, abINTELLIGENCE,  4 },
  { rbtABILITYSCORE, abWISDOM,        4 },
  { rbtABILITYSCORE, abCHARISMA,      6 },
  { rbtSAVINGTHROW,  svFORTITUDE,     4 },
  { rbtSAVINGTHROW,  svREFLEX,        1 },
  { rbtSAVINGTHROW,  svWILL,          1 },
  { rbtATTACK,       0,               3 },
  { rbtARMORCLASS,   0,               5 },
  { rbtSKILL,        skCONCENTRATION, 3 },
  { rbtSKILL,        skSPELLCRAFT,    2 },
  { rbtSKILL,        skLISTEN,        3 },
  { rbtSKILL,        skSPOT,          3 },
  { rbtFEAT,         ftIMPROVEDINITIATIVE, 0 },
  { 0,               0,               0 }
};

static RACIALBONUS minotaurBonuses[] = {
  { rbtABILITYSCORE, abSTRENGTH,      8 },
  { rbtABILITYSCORE, abCONSTITUTION,  4 },
  { rbtABILITYSCORE, abINTELLIGENCE, -4 },
  { rbtABILITYSCORE, abCHARISMA,     -2 },
  { rbtSAVINGTHROW,  svFORTITUDE,     2 },
  { rbtSAVINGTHROW,  svREFLEX,        5 },
  { rbtSAVINGTHROW,  svWILL,          5 },
  { rbtATTACK,       0,               6 },
  { rbtARMORCLASS,   0,               5 },
  { rbtSKILL,        skINTIMIDATE,    6 },
  { rbtSKILL,        skJUMP,          4 },
  { rbtSKILL,        skLISTEN,        8 },
  { rbtSKILL,        skSEARCH,        8 },
  { rbtSKILL,        skSPOT,          8 },
  { rbtFEAT,         ftPOWERATTACK,   0 },
  { 0,               0,               0 }
};

static RACIALBONUS mindflayerBonuses[] = {
  { rbtABILITYSCORE, abSTRENGTH,      2 },
  { rbtABILITYSCORE, abDEXTERITY,     4 },
  { rbtABILITYSCORE, abCONSTITUTION,  2 },
  { rbtABILITYSCORE, abINTELLIGENCE,  8 },
  { rbtABILITYSCORE, abWISDOM,        6 },
  { rbtABILITYSCORE, abCHARISMA,      6 },
  { rbtSAVINGTHROW,  svFORTITUDE,     2 },
  { rbtSAVINGTHROW,  svREFLEX,        2 },
  { rbtSAVINGTHROW,  svWILL,          6 },
  { rbtATTACK,       0,               6 },
  { rbtARMORCLASS,   0,               3 },
  { rbtSKILL,        skBLUFF,         6 },
  { rbtSKILL,        skCONCENTRATION, 11 },
  { rbtSKILL,        skHIDE,         11 },
  { rbtSKILL,        skINTIMIDATE,   11 },
  { rbtSKILL,        skKNOWLEDGE_ARCANA,         4 },
  { rbtSKILL,        skKNOWLEDGE_ARCHITECTUREANDENGINEERING,         4 },
  { rbtSKILL,        skKNOWLEDGE_DUNGEONEERING,         4 },
  { rbtSKILL,        skKNOWLEDGE_GEOGRAPHY,         4 },
  { rbtSKILL,        skKNOWLEDGE_HISTORY,         4 },
  { rbtSKILL,        skKNOWLEDGE_LOCAL,         4 },
  { rbtSKILL,        skKNOWLEDGE_NATURE,         4 },
  { rbtSKILL,        skKNOWLEDGE_NOBILITYANDROYALTY,         4 },
  { rbtSKILL,        skKNOWLEDGE_RELIGION,         4 },
  { rbtSKILL,        skKNOWLEDGE_THEPLANES,         4 },
  { rbtSKILL,        skLISTEN,       11 },
  { rbtSKILL,        skMOVESILENTLY, 11 },
  { rbtSKILL,        skSPOT,         11 },
  { rbtFEAT,         ftALERTNESS,     0 },
  { rbtFEAT,         ftCOMBATCASTING, 0 },
  { rbtFEAT,         ftDODGE,         0 },
  { rbtFEAT,         ftIMPROVEDINITIATIVE, 0 },
  { 0,               0,               0 }
};

static RACIALBONUS araneaBonuses[] = {
  { rbtABILITYSCORE, abDEXTERITY,     4 },
  { rbtABILITYSCORE, abCONSTITUTION,  4 },
  { rbtABILITYSCORE, abINTELLIGENCE,  4 },
  { rbtABILITYSCORE, abWISDOM,        2 },
  { rbtABILITYSCORE, abCHARISMA,      2 },
  { rbtSAVINGTHROW,  svFORTITUDE,     2 },
  { rbtSAVINGTHROW,  svREFLEX,        2 },
  { rbtSAVINGTHROW,  svWILL,          2 },
  { rbtATTACK,       0,               1 },
  { rbtARMORCLASS,   0,               1 },
  { rbtSKILL,        skCLIMB,        14 },
  { rbtSKILL,        skCONCENTRATION, 6 },
  { rbtSKILL,        skCRAFT_ALCHEMY,         6 },
  { rbtSKILL,        skCRAFT_ARMORSMITHING,         6 },
  { rbtSKILL,        skCRAFT_BOWMAKING,         6 },
  { rbtSKILL,        skCRAFT_BLACKSMITHING,         6 },
  { rbtSKILL,        skCRAFT_CARPENTRY,         6 },
  { rbtSKILL,        skCRAFT_LEATHERWORKING,         6 },
  { rbtSKILL,        skCRAFT_PAINTING,         6 },
  { rbtSKILL,        skCRAFT_POTTERY,         6 },
  { rbtSKILL,        skCRAFT_SCULPTING,         6 },
  { rbtSKILL,        skCRAFT_SHIPMAKING,         6 },
  { rbtSKILL,        skCRAFT_STONEMASONRY,         6 },
  { rbtSKILL,        skCRAFT_TRAPMAKING,         6 },
  { rbtSKILL,        skCRAFT_WEAPONSMITHING,         6 },
  { rbtSKILL,        skCRAFT_WOODWORKING,         6 },
  { rbtSKILL,        skESCAPEARTIST,  6 },
  { rbtSKILL,        skJUMP,          6 },
  { rbtFEAT,         ftALERTNESS,     0 },
  { rbtFEAT,         ftIMPROVEDINITIATIVE, 0 },
  { 0,               0,               0 }
};

static RACIALBONUS azerBonuses[] = {
  { rbtABILITYSCORE, abSTRENGTH,      2 },
  { rbtABILITYSCORE, abDEXTERITY,     2 },
  { rbtABILITYSCORE, abCONSTITUTION,  2 },
  { rbtABILITYSCORE, abINTELLIGENCE,  2 },
  { rbtABILITYSCORE, abWISDOM,        2 },
  { rbtABILITYSCORE, abCHARISMA,     -2 },
  { rbtSAVINGTHROW,  svFORTITUDE,     3 },
  { rbtSAVINGTHROW,  svREFLEX,        3 },
  { rbtSAVINGTHROW,  svWILL,          3 },
  { rbtARMORCLASS,   0,               6 },
  { rbtSKILL,        skCLIMB,         1 },
  { rbtSKILL,        skCRAFT_ALCHEMY,         5 },
  { rbtSKILL,        skCRAFT_ARMORSMITHING,         5 },
  { rbtSKILL,        skCRAFT_BOWMAKING,         5 },
  { rbtSKILL,        skCRAFT_BLACKSMITHING,         5 },
  { rbtSKILL,        skCRAFT_CARPENTRY,         5 },
  { rbtSKILL,        skCRAFT_LEATHERWORKING,         5 },
  { rbtSKILL,        skCRAFT_PAINTING,         5 },
  { rbtSKILL,        skCRAFT_POTTERY,         5 },
  { rbtSKILL,        skCRAFT_SCULPTING,         5 },
  { rbtSKILL,        skCRAFT_SHIPMAKING,         5 },
  { rbtSKILL,        skCRAFT_STONEMASONRY,         5 },
  { rbtSKILL,        skCRAFT_TRAPMAKING,         5 },
  { rbtSKILL,        skCRAFT_WEAPONSMITHING,         5 },
  { rbtSKILL,        skCRAFT_WOODWORKING,         5 },
  { rbtSKILL,        skHIDE,         -2 },
  { rbtSKILL,        skLISTEN,        3 },
  { rbtSKILL,        skSEARCH,        3 },
  { rbtSKILL,        skSPOT,          3 },
  { rbtFEAT,         ftPOWERATTACK,   0 },
  { 0,               0,               0 }
};

static RACIALBONUS centaurBonuses[] = {
  { rbtABILITYSCORE, abSTRENGTH,      8 },
  { rbtABILITYSCORE, abDEXTERITY,     4 },
  { rbtABILITYSCORE, abCONSTITUTION,  4 },
  { rbtABILITYSCORE, abINTELLIGENCE, -2 },
  { rbtABILITYSCORE, abWISDOM,        2 },
  { rbtSKILL,        skLISTEN,        3 },
  { rbtSKILL,        skMOVESILENTLY,  2 },
  { rbtSKILL,        skSPOT,          3 },
  { rbtSKILL,        skSURVIVAL, 4 },
  { rbtARMORCLASS,   0,               2 },
  { rbtATTACK,       0,               3 },
  { rbtSAVINGTHROW,  svFORTITUDE,     1 },
  { rbtSAVINGTHROW,  svREFLEX,        4 },
  { rbtSAVINGTHROW,  svWILL,          4 },
  { 0,               0,               0 }
};

static RACIALBONUS driderBonuses[] = {
  { rbtABILITYSCORE, abSTRENGTH,      4 },
  { rbtABILITYSCORE, abDEXTERITY,     4 },
  { rbtABILITYSCORE, abCONSTITUTION,  6 },
  { rbtABILITYSCORE, abINTELLIGENCE,  4 },
  { rbtABILITYSCORE, abWISDOM,        6 },
  { rbtABILITYSCORE, abCHARISMA,      4 },
  { rbtARMORCLASS,   0,               6 },
  { rbtATTACK,       0,               1 },
  { rbtSAVINGTHROW,  svFORTITUDE,     2 },
  { rbtSAVINGTHROW,  svREFLEX,        2 },
  { rbtSAVINGTHROW,  svWILL,          5 },
  { rbtSKILL,        skCLIMB,        12 },
  { rbtSKILL,        skCONCENTRATION, 7 },
  { rbtSKILL,        skHIDE,          6 },
  { rbtSKILL,        skLISTEN,        6 },
  { rbtSKILL,        skMOVESILENTLY,  5 },
  { rbtSKILL,        skSPELLCRAFT,    8 },
  { rbtSKILL,        skSPOT,          6 },
  { rbtFEAT,         ftCOMBATCASTING, 0 },
  { rbtFEAT,         ftTWOWEAPONFIGHTING, 0 },
  { 0,               0,               0 }
};

static RACIALBONUS ettinBonuses[] = {
  { rbtABILITYSCORE, abSTRENGTH,     12 },
  { rbtABILITYSCORE, abDEXTERITY,    -2 },
  { rbtABILITYSCORE, abCONSTITUTION,  4 },
  { rbtABILITYSCORE, abINTELLIGENCE, -4 },
  { rbtARMORCLASS,   0,               7 },
  { rbtATTACK,       0,               6 },
  { rbtSAVINGTHROW,  svFORTITUDE,     7 },
  { rbtSAVINGTHROW,  svREFLEX,        3 },
  { rbtSAVINGTHROW,  svWILL,          3 },
  { rbtSKILL,        skLISTEN,        8 },
  { rbtSKILL,        skSEARCH,        2 },
  { rbtSKILL,        skSPOT,          8 },
  { rbtFEAT,         ftALERTNESS,     0 },
  { rbtFEAT,         ftIMPROVEDINITIATIVE, 0 },
  { rbtFEAT,         ftPOWERATTACK,   0 },
  { 0,               0,               0 }
};

static RACIALBONUS hillGiantBonuses[] = {
  { rbtABILITYSCORE, abSTRENGTH,     14 },
  { rbtABILITYSCORE, abDEXTERITY,    -2 },
  { rbtABILITYSCORE, abCONSTITUTION,  8 },
  { rbtABILITYSCORE, abINTELLIGENCE, -4 },
  { rbtABILITYSCORE, abCHARISMA,      6 },
  { rbtARMORCLASS,   0,               9 },
  { rbtATTACK,       0,               7 },
  { rbtSAVINGTHROW,  svFORTITUDE,     8 },
  { rbtSAVINGTHROW,  svREFLEX,        4 },
  { rbtSAVINGTHROW,  svWILL,          4 },
  { rbtSKILL,        skCLIMB,         1 },
  { rbtSKILL,        skJUMP,          1 },
  { rbtSKILL,        skSPOT,          4 },
  { rbtFEAT,         ftCLEAVE,        0 },
  { rbtFEAT,         ftPOWERATTACK,   0 },
  { 0,               0,               0 }
};

static RACIALBONUS stoneGiantBonuses[] = {
  { rbtABILITYSCORE, abSTRENGTH,     16 },
  { rbtABILITYSCORE, abDEXTERITY,     4 },
  { rbtABILITYSCORE, abCONSTITUTION,  8 },
  { rbtARMORCLASS,   0,              11 },
  { rbtATTACK,       0,               9 },
  { rbtSAVINGTHROW,  svFORTITUDE,     9 },
  { rbtSAVINGTHROW,  svREFLEX,        4 },
  { rbtSAVINGTHROW,  svWILL,          4 },
  { rbtSKILL,        skCLIMB,         2 },
  { rbtSKILL,        skHIDE,          8 },
  { rbtSKILL,        skJUMP,          2 },
  { rbtSKILL,        skSPOT,          3 },
  { rbtFEAT,         ftCOMBATREFLEXES,0 },
  { rbtFEAT,         ftPOINTBLANKSHOT,0 },
  { rbtFEAT,         ftPOWERATTACK,   0 },
  { rbtFEAT,         ftPRECISESHOT,   0 },
  { 0,               0,               0 }
};

static RACIALBONUS frostGiantBonuses[] = {
  { rbtABILITYSCORE, abSTRENGTH,     18 },
  { rbtABILITYSCORE, abDEXTERITY,    -2 },
  { rbtABILITYSCORE, abCONSTITUTION, 10 },
  { rbtARMORCLASS,   0,               9 },
  { rbtATTACK,       0,               9 },
  { rbtSAVINGTHROW,  svFORTITUDE,     9 },
  { rbtSAVINGTHROW,  svREFLEX,        4 },
  { rbtSAVINGTHROW,  svWILL,          4 },
  { rbtSKILL,        skCLIMB,         4 },
  { rbtSKILL,        skJUMP,          4 },
  { rbtSKILL,        skSPOT,          6 },
  { rbtFEAT,         ftCLEAVE,        0 },
  { rbtFEAT,         ftGREATCLEAVE,   0 },
  { rbtFEAT,         ftPOWERATTACK,   0 },
  { rbtFEAT,         ftIMPROVEDSUNDER,        0 },
  { 0,               0,               0 }
};

static RACIALBONUS fireGiantBonuses[] = {
  { rbtABILITYSCORE, abSTRENGTH,     20 },
  { rbtABILITYSCORE, abDEXTERITY,    -2 },
  { rbtABILITYSCORE, abCONSTITUTION, 10 },
  { rbtARMORCLASS,   0,               8 },
  { rbtATTACK,       0,              10 },
  { rbtSAVINGTHROW,  svFORTITUDE,     9 },
  { rbtSAVINGTHROW,  svREFLEX,        4 },
  { rbtSAVINGTHROW,  svWILL,          4 },
  { rbtSKILL,        skCLIMB,         1 },
  { rbtSKILL,        skJUMP,          1 },
  { rbtSKILL,        skSPOT,          7 },
  { rbtFEAT,         ftCLEAVE,        0 },
  { rbtFEAT,         ftGREATCLEAVE,   0 },
  { rbtFEAT,         ftPOWERATTACK,   0 },
  { rbtFEAT,         ftIMPROVEDSUNDER,        0 },
  { 0,               0,               0 }
};

static RACIALBONUS cloudGiantBonuses[] = {
  { rbtABILITYSCORE, abSTRENGTH,     24 },
  { rbtABILITYSCORE, abDEXTERITY,     2 },
  { rbtABILITYSCORE, abCONSTITUTION, 12 },
  { rbtABILITYSCORE, abINTELLIGENCE,  2 },
  { rbtABILITYSCORE, abWISDOM,        2 },
  { rbtABILITYSCORE, abCHARISMA,      2 },
  { rbtARMORCLASS,   0,              12 },
  { rbtATTACK,       0,              10 },
  { rbtSAVINGTHROW,  svFORTITUDE,    10 },
  { rbtSAVINGTHROW,  svREFLEX,        5 },
  { rbtSAVINGTHROW,  svWILL,          5 },
  { rbtSKILL,        skCLIMB,         4 },
  { rbtSKILL,        skJUMP,          4 },
  { rbtSKILL,        skSPOT,          7 },
  { rbtSKILL,        skLISTEN,        7 },
  { rbtFEAT,         ftALERTNESS,     0 },
  { rbtFEAT,         ftCLEAVE,        0 },
  { rbtFEAT,         ftGREATCLEAVE,   0 },
  { rbtFEAT,         ftPOWERATTACK,   0 },
  { 0,               0,               0 }
};

static RACIALBONUS stormGiantBonuses[] = {
  { rbtABILITYSCORE, abSTRENGTH,     28 },
  { rbtABILITYSCORE, abDEXTERITY,     4 },
  { rbtABILITYSCORE, abCONSTITUTION, 12 },
  { rbtABILITYSCORE, abINTELLIGENCE,  6 },
  { rbtABILITYSCORE, abWISDOM,        6 },
  { rbtABILITYSCORE, abCHARISMA,      4 },
  { rbtARMORCLASS,   0,              12 },
  { rbtATTACK,       0,              12 },
  { rbtSAVINGTHROW,  svFORTITUDE,    11 },
  { rbtSAVINGTHROW,  svREFLEX,        6 },
  { rbtSAVINGTHROW,  svWILL,          6 },
  { rbtSKILL,        skCLIMB,         4 },
  { rbtSKILL,        skJUMP,         -2 },
  { rbtSKILL,        skSPOT,          5 },
  { rbtSKILL,        skPERFORM_ACT,         5 },
  { rbtSKILL,        skPERFORM_COMEDY,         5 },
  { rbtSKILL,        skPERFORM_DANCE,         5 },
  { rbtSKILL,        skPERFORM_KEYBOARDINSTRUMENTS,         5 },
  { rbtSKILL,        skPERFORM_ORATORY,         5 },
  { rbtSKILL,        skPERFORM_PERCUSSIONINSTRUMENTS,         5 },
  { rbtSKILL,        skPERFORM_STRINGINSTRUMENTS,         5 },
  { rbtSKILL,        skPERFORM_WINDINSTRUMENTS,         5 },
  { rbtSKILL,        skPERFORM_SING,         5 },
  { rbtFEAT,         ftCLEAVE,        0 },
  { rbtFEAT,         ftCOMBATREFLEXES,0 },
  { rbtFEAT,         ftGREATCLEAVE,   0 },
  { rbtFEAT,         ftPOWERATTACK,   0 },
  { rbtFEAT,         ftIMPROVEDSUNDER,        0 },
  { 0,               0,               0 }
};

static RACIALBONUS grimlockBonuses[] = {
  { rbtABILITYSCORE, abSTRENGTH,      4 },
  { rbtABILITYSCORE, abDEXTERITY,     2 },
  { rbtABILITYSCORE, abCONSTITUTION,  2 },
  { rbtABILITYSCORE, abWISDOM,       -2 },
  { rbtABILITYSCORE, abCHARISMA,     -4 },
  { rbtARMORCLASS,   0,               4 },
  { rbtATTACK,       0,               2 },
  { rbtSAVINGTHROW,  svREFLEX,        3 },
  { rbtSAVINGTHROW,  svWILL,          3 },
  { rbtSKILL,        skCLIMB,         5 },
  { rbtSKILL,        skHIDE,          5 },
  { rbtSKILL,        skLISTEN,        5 },
  { rbtSKILL,        skSEARCH,        5 },
  { rbtSKILL,        skSPOT,          2 },
  { rbtFEAT,         ftALERTNESS,     0 },
  { 0,               0,               0 }
};

static RACIALBONUS seaHagBonuses[] = {
  { rbtABILITYSCORE, abSTRENGTH,      8 },
  { rbtABILITYSCORE, abDEXTERITY,     2 },
  { rbtABILITYSCORE, abCONSTITUTION,  2 },
  { rbtABILITYSCORE, abWISDOM,        2 },
  { rbtARMORCLASS,   0,               3 },
  { rbtATTACK,       0,               2 },
  { rbtSAVINGTHROW,  svFORTITUDE,     1 },
  { rbtSAVINGTHROW,  svREFLEX,        3 },
  { rbtSAVINGTHROW,  svWILL,          3 },
  { rbtSKILL,        skKNOWLEDGE_ARCANA,         4 },
  { rbtSKILL,        skKNOWLEDGE_ARCHITECTUREANDENGINEERING,         4 },
  { rbtSKILL,        skKNOWLEDGE_DUNGEONEERING,         4 },
  { rbtSKILL,        skKNOWLEDGE_GEOGRAPHY,         4 },
  { rbtSKILL,        skKNOWLEDGE_HISTORY,         4 },
  { rbtSKILL,        skKNOWLEDGE_LOCAL,         4 },
  { rbtSKILL,        skKNOWLEDGE_NATURE,         4 },
  { rbtSKILL,        skKNOWLEDGE_NOBILITYANDROYALTY,         4 },
  { rbtSKILL,        skKNOWLEDGE_RELIGION,         4 },
  { rbtSKILL,        skKNOWLEDGE_THEPLANES,         4 },
  { rbtSKILL,        skHIDE,          2 },
  { rbtSKILL,        skLISTEN,        6 },
  { rbtSKILL,        skSPOT,          6 },
  { rbtFEAT,         ftALERTNESS,     0 },
  { 0,               0,               0 }
};

static RACIALBONUS annisBonuses[] = {
  { rbtABILITYSCORE, abSTRENGTH,     14 },
  { rbtABILITYSCORE, abDEXTERITY,     2 },
  { rbtABILITYSCORE, abCONSTITUTION,  4 },
  { rbtABILITYSCORE, abINTELLIGENCE,  2 },
  { rbtABILITYSCORE, abWISDOM,        2 },
  { rbtARMORCLASS,   0,              10 },
  { rbtSAVINGTHROW,  svFORTITUDE,     2 },
  { rbtSAVINGTHROW,  svREFLEX,        5 },
  { rbtSAVINGTHROW,  svWILL,          5 },
  { rbtSKILL,        skCONCENTRATION,10 },
  { rbtSKILL,        skHIDE,          6 },
  { rbtSKILL,        skLISTEN,        8 },
  { rbtSKILL,        skSPOT,          8 },
  { rbtFEAT,         ftALERTNESS,     0 },
  { rbtFEAT,         ftBLINDFIGHT,    0 },
  { rbtFEAT,         ftCOMBATCASTING, 0 },
  { 0,               0,               0 }
};

static RACIALBONUS greenHagBonuses[] = {
  { rbtABILITYSCORE, abSTRENGTH,      8 },
  { rbtABILITYSCORE, abDEXTERITY,     2 },
  { rbtABILITYSCORE, abCONSTITUTION,  2 },
  { rbtABILITYSCORE, abINTELLIGENCE,  2 },
  { rbtABILITYSCORE, abWISDOM,        2 },
  { rbtARMORCLASS,   0,              11 },
  { rbtSAVINGTHROW,  svFORTITUDE,     3 },
  { rbtSAVINGTHROW,  svREFLEX,        6 },
  { rbtSAVINGTHROW,  svWILL,          6 },
  { rbtSKILL,        skCONCENTRATION,12 },
  { rbtSKILL,        skKNOWLEDGE_ARCANA,         4 },
  { rbtSKILL,        skKNOWLEDGE_ARCHITECTUREANDENGINEERING,         4 },
  { rbtSKILL,        skKNOWLEDGE_DUNGEONEERING,         4 },
  { rbtSKILL,        skKNOWLEDGE_GEOGRAPHY,         4 },
  { rbtSKILL,        skKNOWLEDGE_HISTORY,         4 },
  { rbtSKILL,        skKNOWLEDGE_LOCAL,         4 },
  { rbtSKILL,        skKNOWLEDGE_NATURE,         4 },
  { rbtSKILL,        skKNOWLEDGE_NOBILITYANDROYALTY,         4 },
  { rbtSKILL,        skKNOWLEDGE_RELIGION,         4 },
  { rbtSKILL,        skKNOWLEDGE_THEPLANES,         4 },
  { rbtSKILL,        skHIDE,         10 },
  { rbtSKILL,        skLISTEN,        8 },
  { rbtSKILL,        skSPOT,          8 },
  { rbtFEAT,         ftALERTNESS,     0 },
  { rbtFEAT,         ftBLINDFIGHT,    0 },
  { rbtFEAT,         ftCOMBATCASTING, 0 },
  { rbtFEAT,         ftGREATFORTITUDE,0 },
  { 0,               0,               0 }
};

static RACIALBONUS harpyBonuses[] = {
  { rbtABILITYSCORE, abDEXTERITY,     4 },
  { rbtABILITYSCORE, abINTELLIGENCE, -4 },
  { rbtABILITYSCORE, abCHARISMA,      4 },
  { rbtARMORCLASS,   0,               1 },
  { rbtATTACK,       0,               7 },
  { rbtSAVINGTHROW,  svFORTITUDE,     2 },
  { rbtSAVINGTHROW,  svREFLEX,        5 },
  { rbtSAVINGTHROW,  svWILL,          5 },
  { rbtSKILL,        skBLUFF,         6 },
  { rbtSKILL,        skLISTEN,        7 },
  { rbtSKILL,        skPERFORM_ACT,         7 },
  { rbtSKILL,        skPERFORM_COMEDY,         7 },
  { rbtSKILL,        skPERFORM_DANCE,         7 },
  { rbtSKILL,        skPERFORM_KEYBOARDINSTRUMENTS,         7 },
  { rbtSKILL,        skPERFORM_ORATORY,         7 },
  { rbtSKILL,        skPERFORM_PERCUSSIONINSTRUMENTS,         7 },
  { rbtSKILL,        skPERFORM_STRINGINSTRUMENTS,         7 },
  { rbtSKILL,        skPERFORM_WINDINSTRUMENTS,         7 },
  { rbtSKILL,        skPERFORM_SING,         7 },
  { rbtSKILL,        skSPOT,          6 },
  { rbtFEAT,         ftDODGE,         0 },
  { rbtFEAT,         ftFLYBYATTACK,   0 },
  { 0,               0,               0 }
};

static RACIALBONUS kuotoaBonuses[] = {
  { rbtABILITYSCORE, abSTRENGTH,      2 },
  { rbtABILITYSCORE, abCONSTITUTION,  2 },
  { rbtABILITYSCORE, abINTELLIGENCE,  2 },
  { rbtABILITYSCORE, abWISDOM,        4 },
  { rbtABILITYSCORE, abCHARISMA,     -2 },
  { rbtARMORCLASS,   0,               6 },
  { rbtATTACK,       0,               2 },
  { rbtSAVINGTHROW,  svREFLEX,        3 },
  { rbtSAVINGTHROW,  svWILL,          3 },
  { rbtSKILL,        skESCAPEARTIST, 18 },
  { rbtSKILL,        skKNOWLEDGE_ARCANA,         5 },
  { rbtSKILL,        skKNOWLEDGE_ARCHITECTUREANDENGINEERING,         5 },
  { rbtSKILL,        skKNOWLEDGE_DUNGEONEERING,         5 },
  { rbtSKILL,        skKNOWLEDGE_GEOGRAPHY,         5 },
  { rbtSKILL,        skKNOWLEDGE_HISTORY,         5 },
  { rbtSKILL,        skKNOWLEDGE_LOCAL,         5 },
  { rbtSKILL,        skKNOWLEDGE_NATURE,         5 },
  { rbtSKILL,        skKNOWLEDGE_NOBILITYANDROYALTY,         5 },
  { rbtSKILL,        skKNOWLEDGE_RELIGION,         5 },
  { rbtSKILL,        skKNOWLEDGE_THEPLANES,         5 },
  { rbtSKILL,        skLISTEN,        5 },
  { rbtSKILL,        skMOVESILENTLY,  3 },
  { rbtSKILL,        skSEARCH,        9 },
  { rbtSKILL,        skSPOT,          7 },
  { rbtFEAT,         ftALERTNESS,     0 },
  { rbtFEAT,         ftGREATFORTITUDE,0 },
  { 0,               0,               0 }
};

static RACIALBONUS locathahBonuses[] = {
  { rbtABILITYSCORE, abDEXTERITY,     2 },
  { rbtABILITYSCORE, abINTELLIGENCE,  2 },
  { rbtABILITYSCORE, abWISDOM,        2 },
  { rbtARMORCLASS,   0,               3 },
  { rbtATTACK,       0,               1 },
  { rbtSAVINGTHROW,  svFORTITUDE,     3 },
  { rbtSKILL,        skCRAFT_ALCHEMY,         2 },
  { rbtSKILL,        skCRAFT_ARMORSMITHING,         2 },
  { rbtSKILL,        skCRAFT_BOWMAKING,         2 },
  { rbtSKILL,        skCRAFT_BLACKSMITHING,         2 },
  { rbtSKILL,        skCRAFT_CARPENTRY,         2 },
  { rbtSKILL,        skCRAFT_LEATHERWORKING,         2 },
  { rbtSKILL,        skCRAFT_PAINTING,         2 },
  { rbtSKILL,        skCRAFT_POTTERY,         2 },
  { rbtSKILL,        skCRAFT_SCULPTING,         2 },
  { rbtSKILL,        skCRAFT_SHIPMAKING,         2 },
  { rbtSKILL,        skCRAFT_STONEMASONRY,         2 },
  { rbtSKILL,        skCRAFT_TRAPMAKING,         2 },
  { rbtSKILL,        skCRAFT_WEAPONSMITHING,         2 },
  { rbtSKILL,        skCRAFT_WOODWORKING,         2 },
  { rbtSKILL,        skLISTEN,        3 },
  { rbtSKILL,        skSPOT,          3 },
  { rbtFEAT,         ftBLINDFIGHT,    0 },
  { 0,               0,               0 }
};

static RACIALBONUS medusaBonuses[] = {
  { rbtABILITYSCORE, abDEXTERITY,     4 },
  { rbtABILITYSCORE, abCONSTITUTION,  2 },
  { rbtABILITYSCORE, abINTELLIGENCE,  2 },
  { rbtABILITYSCORE, abWISDOM,        2 },
  { rbtABILITYSCORE, abCHARISMA,      4 },
  { rbtARMORCLASS,   0,               3 },
  { rbtATTACK,       0,               6 },
  { rbtSAVINGTHROW,  svFORTITUDE,     2 },
  { rbtSAVINGTHROW,  svREFLEX,        5 },
  { rbtSAVINGTHROW,  svWILL,          5 },
  { rbtSKILL,        skBLUFF,         9 },
  { rbtSKILL,        skDISGUISE,      9 },
  { rbtSKILL,        skMOVESILENTLY,  7 },
  { rbtSKILL,        skSPOT,          9 },
  { rbtFEAT,         ftPOINTBLANKSHOT,0 },
  { rbtFEAT,         ftPRECISESHOT,   0 },
  { 0,               0,               0 }
};

static RACIALBONUS merfolkBonuses[] = {
  { rbtABILITYSCORE, abDEXTERITY,     2 },
  { rbtABILITYSCORE, abCONSTITUTION,  2 },
  { rbtABILITYSCORE, abCHARISMA,      2 },
  { rbtSAVINGTHROW,  svFORTITUDE,     2 },
  { 0,               0,               0 }
};

static RACIALBONUS sahuaginBonuses[] = {
  { rbtABILITYSCORE, abSTRENGTH,      4 },
  { rbtABILITYSCORE, abDEXTERITY,     2 },
  { rbtABILITYSCORE, abCONSTITUTION,  2 },
  { rbtABILITYSCORE, abINTELLIGENCE,  4 },
  { rbtABILITYSCORE, abWISDOM,        2 },
  { rbtABILITYSCORE, abCHARISMA,     -2 },
  { rbtARMORCLASS,   0,               5 },
  { rbtATTACK,       0,               1 },
  { rbtSAVINGTHROW,  svFORTITUDE,     3 },
  { rbtSKILL,        skHANDLEANIMAL, 3 },
  { rbtSKILL,        skHIDE,          5 },
  { rbtSKILL,        skLISTEN,        6 },
  { rbtSKILL,        skPROFESSION_HUNTER,         1 },
  { rbtSKILL,        skPROFESSION_MINER,         1 },
  { rbtSKILL,        skSPOT,          6 },
  { rbtSKILL,        skSURVIVAL,-1 },
  { rbtFEAT,         ftMULTIATTACK,   0 },
  { 0,               0,               0 }
};

static RACIALBONUS trollBonuses[] = {
  { rbtABILITYSCORE, abSTRENGTH,     12},
  { rbtABILITYSCORE, abDEXTERITY,     4 },
  { rbtABILITYSCORE, abCONSTITUTION, 12 },
  { rbtABILITYSCORE, abINTELLIGENCE, -4 },
  { rbtABILITYSCORE, abWISDOM,       -2 },
  { rbtABILITYSCORE, abCHARISMA,     -4 },
  { rbtARMORCLASS,   0,               7 },
  { rbtATTACK,       0,               6 },
  { rbtSAVINGTHROW,  svFORTITUDE,     5 },
  { rbtSAVINGTHROW,  svREFLEX,        2 },
  { rbtSAVINGTHROW,  svWILL,          2 },
  { rbtSKILL,        skLISTEN,        4 },
  { rbtSKILL,        skSPOT,          4 },
  { rbtFEAT,         ftALERTNESS,     0 },
  { rbtFEAT,         ftIRONWILL,      0 },
  { 0,               0,               0 }
};

static RACIALBONUS yuanti1Bonuses[] = {
  { rbtABILITYSCORE, abDEXTERITY,     2 },
  { rbtABILITYSCORE, abINTELLIGENCE,  8 },
  { rbtABILITYSCORE, abWISDOM,        8 },
  { rbtABILITYSCORE, abCHARISMA,      6 },  
  { rbtARMORCLASS,   0,               1 },
  { rbtATTACK,       0,               6 },
  { rbtSAVINGTHROW,  svFORTITUDE,     2 },
  { rbtSAVINGTHROW,  svREFLEX,        5 },
  { rbtSAVINGTHROW,  svWILL,          5 },
  { rbtSKILL,        skCONCENTRATION, 9 },
  { rbtSKILL,        skCRAFT_ALCHEMY,         5 },
  { rbtSKILL,        skCRAFT_ARMORSMITHING,         5 },
  { rbtSKILL,        skCRAFT_BOWMAKING,         5 },
  { rbtSKILL,        skCRAFT_BLACKSMITHING,         5 },
  { rbtSKILL,        skCRAFT_CARPENTRY,         5 },
  { rbtSKILL,        skCRAFT_LEATHERWORKING,         5 },
  { rbtSKILL,        skCRAFT_PAINTING,         5 },
  { rbtSKILL,        skCRAFT_POTTERY,         5 },
  { rbtSKILL,        skCRAFT_SCULPTING,         5 },
  { rbtSKILL,        skCRAFT_SHIPMAKING,         5 },
  { rbtSKILL,        skCRAFT_STONEMASONRY,         5 },
  { rbtSKILL,        skCRAFT_TRAPMAKING,         5 },
  { rbtSKILL,        skCRAFT_WEAPONSMITHING,         5 },
  { rbtSKILL,        skCRAFT_WOODWORKING,         5 },
  { rbtSKILL,        skKNOWLEDGE_ARCANA,         5 },
  { rbtSKILL,        skKNOWLEDGE_ARCHITECTUREANDENGINEERING,         5 },
  { rbtSKILL,        skKNOWLEDGE_DUNGEONEERING,         5 },
  { rbtSKILL,        skKNOWLEDGE_GEOGRAPHY,         5 },
  { rbtSKILL,        skKNOWLEDGE_HISTORY,         5 },
  { rbtSKILL,        skKNOWLEDGE_LOCAL,         5 },
  { rbtSKILL,        skKNOWLEDGE_NATURE,         5 },
  { rbtSKILL,        skKNOWLEDGE_NOBILITYANDROYALTY,         5 },
  { rbtSKILL,        skKNOWLEDGE_RELIGION,         5 },
  { rbtSKILL,        skKNOWLEDGE_THEPLANES,         5 },
  { rbtSKILL,        skDISGUISE,      0 },
  { rbtSKILL,        skHIDE,          6 },
  { rbtSKILL,        skLISTEN,        9 },
  { rbtSKILL,        skSPOT,          9 },
  { rbtFEAT,         ftALERTNESS,     0 },
  { rbtFEAT,         ftBLINDFIGHT,    0 },
  { rbtFEAT,         ftDODGE,         0 },
  { rbtFEAT,         ftCOMBATEXPERTISE,     0 },
  { rbtFEAT,         ftIMPROVEDINITIATIVE, 0 },
  { 0,               0,               0 }
};

static RACIALBONUS yuanti2Bonuses[] = {
  { rbtABILITYSCORE, abSTRENGTH,      4 },
  { rbtABILITYSCORE, abDEXTERITY,     2 },
  { rbtABILITYSCORE, abCONSTITUTION,  2 },
  { rbtABILITYSCORE, abINTELLIGENCE,  8 },
  { rbtABILITYSCORE, abWISDOM,        8 },
  { rbtABILITYSCORE, abCHARISMA,      6 },  
  { rbtARMORCLASS,   0,               1 },
  { rbtATTACK,       0,               7 },
  { rbtSAVINGTHROW,  svFORTITUDE,     2 },
  { rbtSAVINGTHROW,  svREFLEX,        5 },
  { rbtSAVINGTHROW,  svWILL,          5 },
  { rbtSKILL,        skCONCENTRATION,10 },
  { rbtSKILL,        skCRAFT_ALCHEMY,         5 },
  { rbtSKILL,        skCRAFT_ARMORSMITHING,         5 },
  { rbtSKILL,        skCRAFT_BOWMAKING,         5 },
  { rbtSKILL,        skCRAFT_BLACKSMITHING,         5 },
  { rbtSKILL,        skCRAFT_CARPENTRY,         5 },
  { rbtSKILL,        skCRAFT_LEATHERWORKING,         5 },
  { rbtSKILL,        skCRAFT_PAINTING,         5 },
  { rbtSKILL,        skCRAFT_POTTERY,         5 },
  { rbtSKILL,        skCRAFT_SCULPTING,         5 },
  { rbtSKILL,        skCRAFT_SHIPMAKING,         5 },
  { rbtSKILL,        skCRAFT_STONEMASONRY,         5 },
  { rbtSKILL,        skCRAFT_TRAPMAKING,         5 },
  { rbtSKILL,        skCRAFT_WEAPONSMITHING,         5 },
  { rbtSKILL,        skCRAFT_WOODWORKING,         5 },
  { rbtSKILL,        skKNOWLEDGE_ARCANA,         5 },
  { rbtSKILL,        skKNOWLEDGE_ARCHITECTUREANDENGINEERING,         5 },
  { rbtSKILL,        skKNOWLEDGE_DUNGEONEERING,         5 },
  { rbtSKILL,        skKNOWLEDGE_GEOGRAPHY,         5 },
  { rbtSKILL,        skKNOWLEDGE_HISTORY,         5 },
  { rbtSKILL,        skKNOWLEDGE_LOCAL,         5 },
  { rbtSKILL,        skKNOWLEDGE_NATURE,         5 },
  { rbtSKILL,        skKNOWLEDGE_NOBILITYANDROYALTY,         5 },
  { rbtSKILL,        skKNOWLEDGE_RELIGION,         5 },
  { rbtSKILL,        skKNOWLEDGE_THEPLANES,         5 },
  { rbtSKILL,        skHIDE,          7 },
  { rbtSKILL,        skLISTEN,        9 },
  { rbtSKILL,        skSPOT,          9 },
  { rbtFEAT,         ftALERTNESS,     0 },
  { rbtFEAT,         ftBLINDFIGHT,    0 },
  { rbtFEAT,         ftDODGE,         0 },
  { rbtFEAT,         ftCOMBATEXPERTISE,     0 },
  { rbtFEAT,         ftIMPROVEDINITIATIVE, 0 },
  { 0,               0,               0 }
};

static RACIALBONUS yuanti3Bonuses[] = {
  { rbtABILITYSCORE, abSTRENGTH,      8 },
  { rbtABILITYSCORE, abDEXTERITY,     2 },
  { rbtABILITYSCORE, abCONSTITUTION,  6 },
  { rbtABILITYSCORE, abINTELLIGENCE,  8 },
  { rbtABILITYSCORE, abWISDOM,        8 },
  { rbtABILITYSCORE, abCHARISMA,      6 },  
  { rbtARMORCLASS,   0,              10 },
  { rbtATTACK,       0,               8 },
  { rbtSAVINGTHROW,  svFORTITUDE,     3 },
  { rbtSAVINGTHROW,  svREFLEX,        6 },
  { rbtSAVINGTHROW,  svWILL,          6 },
  { rbtSKILL,        skCONCENTRATION, 8 },
  { rbtSKILL,        skCRAFT_ALCHEMY,         5 },
  { rbtSKILL,        skCRAFT_ARMORSMITHING,         5 },
  { rbtSKILL,        skCRAFT_BOWMAKING,         5 },
  { rbtSKILL,        skCRAFT_BLACKSMITHING,         5 },
  { rbtSKILL,        skCRAFT_CARPENTRY,         5 },
  { rbtSKILL,        skCRAFT_LEATHERWORKING,         5 },
  { rbtSKILL,        skCRAFT_PAINTING,         5 },
  { rbtSKILL,        skCRAFT_POTTERY,         5 },
  { rbtSKILL,        skCRAFT_SCULPTING,         5 },
  { rbtSKILL,        skCRAFT_SHIPMAKING,         5 },
  { rbtSKILL,        skCRAFT_STONEMASONRY,         5 },
  { rbtSKILL,        skCRAFT_TRAPMAKING,         5 },
  { rbtSKILL,        skCRAFT_WEAPONSMITHING,         5 },
  { rbtSKILL,        skCRAFT_WOODWORKING,         5 },
  { rbtSKILL,        skKNOWLEDGE_ARCANA,         5 },
  { rbtSKILL,        skKNOWLEDGE_ARCHITECTUREANDENGINEERING,         5 },
  { rbtSKILL,        skKNOWLEDGE_DUNGEONEERING,         5 },
  { rbtSKILL,        skKNOWLEDGE_GEOGRAPHY,         5 },
  { rbtSKILL,        skKNOWLEDGE_HISTORY,         5 },
  { rbtSKILL,        skKNOWLEDGE_LOCAL,         5 },
  { rbtSKILL,        skKNOWLEDGE_NATURE,         5 },
  { rbtSKILL,        skKNOWLEDGE_NOBILITYANDROYALTY,         5 },
  { rbtSKILL,        skKNOWLEDGE_RELIGION,         5 },
  { rbtSKILL,        skKNOWLEDGE_THEPLANES,         5 },
  { rbtSKILL,        skHIDE,          8 },
  { rbtSKILL,        skLISTEN,        9 },
  { rbtSKILL,        skSPOT,          9 },
  { rbtFEAT,         ftALERTNESS,     0 },
  { rbtFEAT,         ftBLINDFIGHT,    0 },
  { rbtFEAT,         ftDODGE,         0 },
  { rbtFEAT,         ftCOMBATEXPERTISE,     0 },
  { rbtFEAT,         ftIMPROVEDINITIATIVE, 0 },
  { 0,               0,               0 }
};

static RACIALBONUS cc_abandonedBonuses[] = {
  { rbtABILITYSCORE, abSTRENGTH,      8 },
  { rbtABILITYSCORE, abCONSTITUTION,  4 },
  { rbtABILITYSCORE, abINTELLIGENCE, -4 },
  { rbtABILITYSCORE, abCHARISMA,     -4 },
  { rbtARMORCLASS,   0,               5 },
  { rbtATTACK,       0,               1 },
  { rbtSAVINGTHROW,  svFORTITUDE,     3 },
  { rbtSKILL,        skCLIMB,         2 },
  { rbtSKILL,        skHIDE,          6 },
  { rbtSKILL,        skLISTEN,        3 },
  { rbtSKILL,        skJUMP,          0 },
  { rbtSKILL,        skSPOT,          3 },
  { rbtSKILL,        skSURVIVAL,4 },
  { rbtFEAT,         ftPOWERATTACK,   0 },
  { rbtFEAT,         ftRUN,           0 },
  { rbtFEAT,         ftTRACK,         0 },
  { 0,               0,               0 }
};

static RACIALBONUS cc_asaathBonuses[] = {
  { rbtABILITYSCORE, abSTRENGTH,      2 },
  { rbtABILITYSCORE, abDEXTERITY,     6 },
  { rbtABILITYSCORE, abCONSTITUTION,  2 },
  { rbtABILITYSCORE, abINTELLIGENCE,  4 },
  { rbtABILITYSCORE, abWISDOM,        4 },
  { rbtABILITYSCORE, abCHARISMA,      2 },
  { rbtARMORCLASS,   0,               5 },
  { rbtATTACK,       0,               3 },
  { rbtSAVINGTHROW,  svFORTITUDE,     1 },
  { rbtSAVINGTHROW,  svREFLEX,        1 },
  { rbtSAVINGTHROW,  svWILL,          4 },
  { rbtSKILL,        skCRAFT_ALCHEMY,       3 },
  { rbtSKILL,        skESCAPEARTIST,  0 },
  { rbtSKILL,        skHIDE,          0 },
  { rbtSKILL,        skJUMP,          5 },
  { rbtSKILL,        skLISTEN,        3 },
  { rbtSKILL,        skMOVESILENTLY,  7 },
  { rbtSKILL,        skSEARCH,        2 },
  { rbtSKILL,        skSPELLCRAFT,    7 },
  { rbtSKILL,        skSPOT,          0 },
  { rbtSKILL,        skUSEMAGICDEVICE,0 },
  { rbtFEAT,         ftBLINDFIGHT,    0 },
  { rbtFEAT,         ftCOMBATREFLEXES,0 },
  { rbtFEAT,         ftCOMBATEXPERTISE,     0 },
  { rbtFEAT,         ftRUN,           0 },
  { 0,               0,               0 }
};

static RACIALBONUS cc_batDevilBonuses[] = {
  { rbtABILITYSCORE, abSTRENGTH,      2 },
  { rbtABILITYSCORE, abDEXTERITY,     8 },
  { rbtABILITYSCORE, abCONSTITUTION,  2 },
  { rbtABILITYSCORE, abWISDOM,        4 },
  { rbtABILITYSCORE, abCHARISMA,      4 },
  { rbtARMORCLASS,   0,               3 },
  { rbtATTACK,       0,               2 },
  { rbtSAVINGTHROW,  svREFLEX,        3 },
  { rbtSKILL,        skCLIMB,         4 },
  { rbtSKILL,        skHIDE,          0 },
  { rbtSKILL,        skLISTEN,       18 },
  { rbtSKILL,        skSPOT,          6 },
  { rbtFEAT,         ftBLINDFIGHT,    0 },
  { rbtFEAT,         ftFLYBYATTACK,   0 },
  { rbtFEAT,         ftLIGHTNINGREFLEXES, 0 },
  { 0,               0,               0 }
};

static RACIALBONUS cc_plagueWretchBonuses[] = {
  { rbtABILITYSCORE, abSTRENGTH,      4 },
  { rbtABILITYSCORE, abCONSTITUTION,  8 },
  { rbtABILITYSCORE, abCHARISMA,     -4 },
  { rbtARMORCLASS,   0,               5 },
  { rbtATTACK,       0,               3 },
  { rbtSAVINGTHROW,  svFORTITUDE,     3 },
  { rbtSAVINGTHROW,  svREFLEX,        1 },
  { rbtSAVINGTHROW,  svWILL,          1 },
  { rbtSKILL,        skBALANCE,       1 },
  { rbtSKILL,        skBLUFF,         5 },
  { rbtSKILL,        skCLIMB,         0 },
  { rbtSKILL,        skDIPLOMACY,     3 },
  { rbtSKILL,        skINTIMIDATE,    6 },
  { rbtSKILL,        skJUMP,          0 },
  { rbtSKILL,        skLISTEN,        3 },
  { rbtSKILL,        skPERFORM_ACT,         6 },
  { rbtSKILL,        skPERFORM_COMEDY,         6 },
  { rbtSKILL,        skPERFORM_DANCE,         6 },
  { rbtSKILL,        skPERFORM_KEYBOARDINSTRUMENTS,         6 },
  { rbtSKILL,        skPERFORM_ORATORY,         6 },
  { rbtSKILL,        skPERFORM_PERCUSSIONINSTRUMENTS,         6 },
  { rbtSKILL,        skPERFORM_STRINGINSTRUMENTS,         6 },
  { rbtSKILL,        skPERFORM_WINDINSTRUMENTS,         6 },
  { rbtSKILL,        skPERFORM_SING,         6 },
  { rbtSKILL,        skSPOT,          2 },
  { rbtSKILL,        skTUMBLE,        2 },
  { rbtFEAT,         ftENDURANCE,     0 },
  { 0,               0,               0 }
};

static RACIALBONUS cc_charduniBonuses[] = {
  { rbtABILITYSCORE, abSTRENGTH,      4 },
  { rbtABILITYSCORE, abCONSTITUTION,  4 },
  { rbtABILITYSCORE, abWISDOM,        2 },
  { rbtABILITYSCORE, abCHARISMA,     -2 },
  { rbtARMORCLASS,   0,               1 },
  { rbtSAVINGTHROW,  svFORTITUDE,     3 },
  { rbtSKILL,        skAPPRAISE,      1 },
  { rbtSKILL,        skCLIMB,        -1 },
  { rbtSKILL,        skCRAFT_ALCHEMY,         2 },
  { rbtSKILL,        skCRAFT_ARMORSMITHING,         2 },
  { rbtSKILL,        skCRAFT_BOWMAKING,         2 },
  { rbtSKILL,        skCRAFT_BLACKSMITHING,         2 },
  { rbtSKILL,        skCRAFT_CARPENTRY,         2 },
  { rbtSKILL,        skCRAFT_LEATHERWORKING,         2 },
  { rbtSKILL,        skCRAFT_PAINTING,         2 },
  { rbtSKILL,        skCRAFT_POTTERY,         2 },
  { rbtSKILL,        skCRAFT_SCULPTING,         2 },
  { rbtSKILL,        skCRAFT_SHIPMAKING,         2 },
  { rbtSKILL,        skCRAFT_STONEMASONRY,         2 },
  { rbtSKILL,        skCRAFT_TRAPMAKING,         2 },
  { rbtSKILL,        skCRAFT_WEAPONSMITHING,         2 },
  { rbtSKILL,        skCRAFT_WOODWORKING,         2 },
  { rbtSKILL,        skINTIMIDATE,    3 },
  { rbtSKILL,        skSURVIVAL, 3 },
  { rbtSKILL,        skLISTEN,        1 },
  { rbtSKILL,        skSPOT,          0 },
  { 0,               0,               0 }
};

static RACIALBONUS cc_coalGoblinBonuses[] = {
  { rbtABILITYSCORE, abDEXTERITY,     4 },
  { rbtABILITYSCORE, abCONSTITUTION,  2 },
  { rbtABILITYSCORE, abINTELLIGENCE,  2 },
  { rbtABILITYSCORE, abWISDOM,        2 },
  { rbtATTACK,       0,               3 },
  { rbtSAVINGTHROW,  svFORTITUDE,     0 },
  { rbtSAVINGTHROW,  svREFLEX,        3 },
  { rbtSAVINGTHROW,  svWILL,          0 },
  { rbtSKILL,        skHIDE,          6 },
  { rbtSKILL,        skLISTEN,        2 },
  { rbtSKILL,        skMOVESILENTLY,  6 },
  { rbtSKILL,        skOPENLOCK,      1 },
  { rbtSKILL,        skSPOT,          2 },
  { rbtFEAT,         ftDODGE,         0 },
  { 0,               0,               0 }
};

static RACIALBONUS cc_fdwarfBonuses[] = {
  { rbtABILITYSCORE, abCONSTITUTION,  2 },
  { rbtABILITYSCORE, abCHARISMA,     -2 },
  { rbtSAVINGTHROW,  svFORTITUDE,     3 },
  { rbtSKILL,        skCRAFT_ALCHEMY,         4 },
  { rbtSKILL,        skCRAFT_ARMORSMITHING,         4 },
  { rbtSKILL,        skCRAFT_BOWMAKING,         4 },
  { rbtSKILL,        skCRAFT_BLACKSMITHING,         4 },
  { rbtSKILL,        skCRAFT_CARPENTRY,         4 },
  { rbtSKILL,        skCRAFT_LEATHERWORKING,         4 },
  { rbtSKILL,        skCRAFT_PAINTING,         4 },
  { rbtSKILL,        skCRAFT_POTTERY,         4 },
  { rbtSKILL,        skCRAFT_SCULPTING,         4 },
  { rbtSKILL,        skCRAFT_SHIPMAKING,         4 },
  { rbtSKILL,        skCRAFT_STONEMASONRY,         4 },
  { rbtSKILL,        skCRAFT_TRAPMAKING,         4 },
  { rbtSKILL,        skCRAFT_WEAPONSMITHING,         4 },
  { rbtSKILL,        skCRAFT_WOODWORKING,         4 },
  { rbtSKILL,        skLISTEN,        1 },
  { rbtSKILL,        skSPOT,          1 },
  { 0,               0,               0 }
};

static RACIALBONUS cc_felfBonuses[] = {
  { rbtABILITYSCORE, abSTRENGTH,     -2 },
  { rbtABILITYSCORE, abDEXTERITY,     2 },
  { rbtABILITYSCORE, abCONSTITUTION, -2 },
  { rbtABILITYSCORE, abCHARISMA,      2 },
  { rbtSAVINGTHROW,  svFORTITUDE,     2 },
  { rbtATTACK,       0,               1 },
  { rbtSKILL,        skHIDE,          2 },
  { rbtSKILL,        skLISTEN,        4 },
  { rbtSKILL,        skMOVESILENTLY,  2 },
  { rbtSKILL,        skSEARCH,        4 },
  { rbtSKILL,        skSPOT,          4 },
  { rbtFEAT,         ftDODGE,         0 },
  { rbtFEAT,         ftPOINTBLANKSHOT,0 },
  { 0,               0,               0 }
};

static RACIALBONUS cc_iceGhoulBonuses[] = {
  { rbtABILITYSCORE, abSTRENGTH,      8 },
  { rbtABILITYSCORE, abDEXTERITY,     4 },
  { rbtABILITYSCORE, abCONSTITUTION,  8 },
  { rbtABILITYSCORE, abINTELLIGENCE, -4 },
  { rbtABILITYSCORE, abWISDOM,       -2 },
  { rbtABILITYSCORE, abCHARISMA,      4 },
  { rbtSAVINGTHROW,  svFORTITUDE,     3 },
  { rbtATTACK,       0,               2 },
  { rbtSKILL,        skESCAPEARTIST,  0 },
  { rbtSKILL,        skHIDE,          3 },
  { rbtSKILL,        skLISTEN,        3 },
  { rbtSKILL,        skMOVESILENTLY,  3 },
  { rbtSKILL,        skSPOT,          3 },
  { rbtSKILL,        skSWIM,          3 },
  { rbtSKILL,        skSURVIVAL,7 },
  { rbtFEAT,         ftALERTNESS,     0 },
  { rbtFEAT,         ftPOWERATTACK,   0 },
  { 0,               0,               0 }
};

static RACIALBONUS cc_manticoraBonuses[] = {
  { rbtABILITYSCORE, abSTRENGTH,      2 },
  { rbtABILITYSCORE, abDEXTERITY,     4 },
  { rbtABILITYSCORE, abCONSTITUTION,  4 },
  { rbtSAVINGTHROW,  svFORTITUDE,     2 },
  { rbtARMORCLASS,   0,               2 },
  { rbtATTACK,       0,               3 },
  { rbtSKILL,        skCLIMB,         5 },
  { rbtSKILL,        skHIDE,          3 },
  { rbtSKILL,        skINTIMIDATE,    4 },
  { rbtSKILL,        skJUMP,          3 },
  { rbtSKILL,        skLISTEN,        4 },
  { rbtSKILL,        skMOVESILENTLY,  5 },
  { rbtSKILL,        skSURVIVAL,3 },
  { rbtFEAT,         ftIMPROVEDINITIATIVE, 0 },
  { rbtFEAT,         ftTRACK,         0 },
  { 0,               0,               0 }
};

static RACIALBONUS cc_morgauntBonuses[] = {
  { rbtABILITYSCORE, abSTRENGTH,      4 },
  { rbtABILITYSCORE, abDEXTERITY,     4 },
  { rbtABILITYSCORE, abCONSTITUTION,  8 },
  { rbtABILITYSCORE, abINTELLIGENCE, -2 },
  { rbtABILITYSCORE, abWISDOM,       -2 },
  { rbtABILITYSCORE, abCHARISMA,     -4 },
  { rbtSAVINGTHROW,  svFORTITUDE,     3 },
  { rbtATTACK,       0,               3 },
  { rbtSKILL,        skBLUFF,         8 },
  { rbtSKILL,        skHIDE,          1 },
  { rbtSKILL,        skLISTEN,        1 },
  { rbtSKILL,        skSPOT,          2 },
  { rbtFEAT,         ftALERTNESS,     0 },
  { rbtFEAT,         ftBLINDFIGHT,    0 },
  { 0,               0,               0 }
};

static RACIALBONUS cc_proudBonuses[] = {
  { rbtABILITYSCORE, abSTRENGTH,      4 },
  { rbtABILITYSCORE, abDEXTERITY,     4 },
  { rbtABILITYSCORE, abCONSTITUTION,  6 },
  { rbtABILITYSCORE, abWISDOM,        2 },
  { rbtSAVINGTHROW,  svFORTITUDE,     4 },
  { rbtSAVINGTHROW,  svREFLEX,        1 },
  { rbtSAVINGTHROW,  svWILL,          1 },
  { rbtATTACK,       0,               2 },
  { rbtARMORCLASS,   0,               6 },
  { rbtSKILL,        skHIDE,          7 },
  { rbtSKILL,        skJUMP,          1 },
  { rbtSKILL,        skLISTEN,        5 },
  { rbtSKILL,        skMOVESILENTLY,  1 },
  { rbtSKILL,        skSPOT,          8 },
  { rbtSKILL,        skSURVIVAL,2 },
  { rbtFEAT,         ftCLEAVE,        0 },
  { rbtFEAT,         ftIMPROVEDINITIATIVE, 0 },
  { rbtFEAT,         ftRUN,           0 },
  { rbtFEAT,         ftTRACK,         0 },
  { 0,               0,               0 }
};

static RACIALBONUS cc_ratmanBonuses[] = {
  { rbtABILITYSCORE, abDEXTERITY,     4 },
  { rbtABILITYSCORE, abCONSTITUTION,  6 },
  { rbtABILITYSCORE, abCHARISMA,     -2 },
  { rbtSAVINGTHROW,  svFORTITUDE,     2 },
  { rbtATTACK,       0,               1 },
  { rbtARMORCLASS,   0,               1 },
  { rbtSKILL,        skESCAPEARTIST,  1 },
  { rbtSKILL,        skHIDE,          0 },
  { rbtSKILL,        skJUMP,          1 },
  { rbtFEAT,         ftDODGE,         0 },
  { 0,               0,               0 }
};

static RACIALBONUS cc_bgratmanBonuses[] = {
  { rbtABILITYSCORE, abDEXTERITY,     4 },
  { rbtABILITYSCORE, abCONSTITUTION,  6 },
  { rbtABILITYSCORE, abCHARISMA,     -2 },
  { rbtSAVINGTHROW,  svFORTITUDE,     2 },
  { rbtATTACK,       0,               1 },
  { rbtARMORCLASS,   0,               1 },
  { rbtSKILL,        skESCAPEARTIST,  1 },
  { rbtSKILL,        skHIDE,          0 },
  { rbtSKILL,        skJUMP,          1 },
  { rbtSKILL,        skSEARCH,        2 },
  { rbtFEAT,         ftDODGE,         0 },
  { 0,               0,               0 }
};

static RACIALBONUS cc_dratmanBonuses[] = {
  { rbtABILITYSCORE, abDEXTERITY,     2 },
  { rbtABILITYSCORE, abCONSTITUTION,  6 },
  { rbtABILITYSCORE, abINTELLIGENCE,  2 },
  { rbtABILITYSCORE, abWISDOM,        2 },
  { rbtABILITYSCORE, abCHARISMA,      2 },
  { rbtSAVINGTHROW,  svFORTITUDE,     2 },
  { rbtATTACK,       0,               1 },
  { rbtARMORCLASS,   0,               1 },
  { rbtSKILL,        skDIPLOMACY,     0 },
  { rbtSKILL,        skESCAPEARTIST,  2 },
  { rbtSKILL,        skHIDE,          1 },
  { rbtFEAT,         ftDODGE,         0 },
  { 0,               0,               0 }
};

static RACIALBONUS cc_fratmanBonuses[] = {
  { rbtABILITYSCORE, abSTRENGTH,      4 },
  { rbtABILITYSCORE, abDEXTERITY,     4 },
  { rbtABILITYSCORE, abCONSTITUTION,  6 },
  { rbtABILITYSCORE, abINTELLIGENCE, -2 },
  { rbtABILITYSCORE, abWISDOM,       -2 },
  { rbtABILITYSCORE, abCHARISMA,     -2 },
  { rbtSAVINGTHROW,  svFORTITUDE,     3 },
  { rbtSAVINGTHROW,  svREFLEX,        3 },
  { rbtATTACK,       0,               2 },
  { rbtARMORCLASS,   0,               1 },
  { rbtSKILL,        skESCAPEARTIST,  1 },
  { rbtSKILL,        skJUMP,         -1 },
  { rbtSKILL,        skSWIM,          3 },
  { rbtFEAT,         ftPOWERATTACK,   0 },
  { 0,               0,               0 }
};

static RACIALBONUS cc_rwratmanBonuses[] = {
  { rbtABILITYSCORE, abDEXTERITY,     4 },
  { rbtABILITYSCORE, abCONSTITUTION,  6 },
  { rbtABILITYSCORE, abINTELLIGENCE,  4 },
  { rbtABILITYSCORE, abWISDOM,        2 },
  { rbtABILITYSCORE, abCHARISMA,     -2 },
  { rbtSAVINGTHROW,  svWILL,          2 },
  { rbtATTACK,       0,               1 },
  { rbtARMORCLASS,   0,               1 },
  { rbtSKILL,        skCONCENTRATION,-1 },
  { rbtSKILL,        skESCAPEARTIST,  1 },
  { rbtSKILL,        skHIDE,          0 },
  { rbtSKILL,        skJUMP,          1 },
  { rbtSKILL,        skDECIPHERSCRIPT,          0 },
  { rbtSKILL,        skSPELLCRAFT,    3 },
  { 0,               0,               0 }
};

static RACIALBONUS cc_skinDevilBonuses[] = {
  { rbtABILITYSCORE, abSTRENGTH,      4 },
  { rbtABILITYSCORE, abDEXTERITY,     6 },
  { rbtABILITYSCORE, abCONSTITUTION,  8 },
  { rbtABILITYSCORE, abINTELLIGENCE,  2 },
  { rbtABILITYSCORE, abWISDOM,       -2 },
  { rbtABILITYSCORE, abCHARISMA,      4 },
  { rbtSAVINGTHROW,  svFORTITUDE,     4 },
  { rbtSAVINGTHROW,  svREFLEX,        1 },
  { rbtSAVINGTHROW,  svWILL,          1 },
  { rbtATTACK,       0,               5 },
  { rbtARMORCLASS,   0,               3 },
  { rbtSKILL,        skBLUFF,         8 },
  { rbtSKILL,        skHIDE,          5 },
  { rbtSKILL,        skLISTEN,        4 },
  { rbtSKILL,        skSPOT,          4 },
  { rbtFEAT,         ftALERTNESS,     0 },
  { 0,               0,               0 }
};

static RACIALBONUS cc_segoblinBonuses[] = {
  { rbtABILITYSCORE, abDEXTERITY,     4 },
  { rbtABILITYSCORE, abINTELLIGENCE, -2 },
  { rbtABILITYSCORE, abCHARISMA,     -8 },
  { rbtSAVINGTHROW,  svFORTITUDE,     2 },
  { rbtATTACK,       0,               2 },
  { rbtARMORCLASS,   0,               2 },
  { rbtSKILL,        skBALANCE,       0 },
  { rbtSKILL,        skHIDE,          5 },
  { rbtSKILL,        skJUMP,          5 },
  { rbtSKILL,        skLISTEN,        4 },
  { rbtSKILL,        skMOVESILENTLY,  2 },
  { rbtSKILL,        skSPOT,          6 },
  { 0,               0,               0 }
};

static RACIALBONUS cc_strollBonuses[] = {
  { rbtABILITYSCORE, abSTRENGTH,      4 },
  { rbtABILITYSCORE, abDEXTERITY,    -2 },
  { rbtABILITYSCORE, abCONSTITUTION,  8 },
  { rbtABILITYSCORE, abINTELLIGENCE, -2 },
  { rbtABILITYSCORE, abWISDOM,       -2 },
  { rbtABILITYSCORE, abCHARISMA,     -2 },
  { rbtSAVINGTHROW,  svFORTITUDE,     6 },
  { rbtSAVINGTHROW,  svREFLEX,        2 },
  { rbtSAVINGTHROW,  svWILL,          2 },
  { rbtATTACK,       0,               7 },
  { rbtARMORCLASS,   0,               9 },
  { rbtSKILL,        skHANDLEANIMAL,16 },
  { rbtSKILL,        skCRAFT_ALCHEMY,         9 },
  { rbtSKILL,        skCRAFT_ARMORSMITHING,         9 },
  { rbtSKILL,        skCRAFT_BOWMAKING,         9 },
  { rbtSKILL,        skCRAFT_BLACKSMITHING,         9 },
  { rbtSKILL,        skCRAFT_CARPENTRY,         9 },
  { rbtSKILL,        skCRAFT_LEATHERWORKING,         9 },
  { rbtSKILL,        skCRAFT_PAINTING,         9 },
  { rbtSKILL,        skCRAFT_POTTERY,         9 },
  { rbtSKILL,        skCRAFT_SCULPTING,         9 },
  { rbtSKILL,        skCRAFT_SHIPMAKING,         9 },
  { rbtSKILL,        skCRAFT_STONEMASONRY,         9 },
  { rbtSKILL,        skCRAFT_TRAPMAKING,         9 },
  { rbtSKILL,        skCRAFT_WEAPONSMITHING,         9 },
  { rbtSKILL,        skCRAFT_WOODWORKING,         9 },
  { rbtSKILL,        skLISTEN,       11 },
  { rbtSKILL,        skRIDE,         16 },
  { rbtSKILL,        skSPOT,         16 },
  { rbtSKILL,        skSURVIVAL,11 },
  { rbtFEAT,         ftRIDEBYATTACK,  0 },
  { rbtFEAT,         ftSPIRITEDCHARGE,0 },
  { rbtFEAT,         ftTOUGHNESS,     0 },
  { rbtFEAT,         ftTOUGHNESS,     0 },
  { rbtFEAT,         ftTRACK,         0 },
  { 0,               0,               0 }
};

static RACIALBONUS cc_selementBonuses[] = {
  { rbtABILITYSCORE, abDEXTERITY,     2 },
  { rbtABILITYSCORE, abCONSTITUTION,  2 },
  { rbtSAVINGTHROW,  svFORTITUDE,     4 },
  { rbtSAVINGTHROW,  svREFLEX,        1 },
  { rbtSAVINGTHROW,  svWILL,          1 },
  { rbtATTACK,       0,               4 },
  { rbtARMORCLASS,   0,               3 },
  { 0,               0,               0 }
};

static RACIALBONUS cc_tokalBonuses[] = {
  { rbtABILITYSCORE, abSTRENGTH,      6 },
  { rbtABILITYSCORE, abDEXTERITY,     6 },
  { rbtABILITYSCORE, abCONSTITUTION,  4 },
  { rbtABILITYSCORE, abINTELLIGENCE, -2 },
  { rbtABILITYSCORE, abWISDOM,       -2 },
  { rbtABILITYSCORE, abCHARISMA,     -4 },
  { rbtSAVINGTHROW,  svFORTITUDE,     3 },
  { rbtSAVINGTHROW,  svREFLEX,        3 },
  { rbtATTACK,       0,               2 },
  { rbtSKILL,        skLISTEN,        1 },
  { rbtSKILL,        skSPOT,          1 },
  { rbtFEAT,         ftALERTNESS,     0 },
  { 0,               0,               0 }
};

static RACIALBONUS cc_ubantuBonuses[] = {
  { rbtABILITYSCORE, abDEXTERITY,     2 },
  { rbtABILITYSCORE, abCHARISMA,     -2 },
  { rbtSAVINGTHROW,  svREFLEX,        2 },
  { rbtATTACK,       0,               2 },
  { rbtSKILL,        skCRAFT_ALCHEMY,         2 },
  { rbtSKILL,        skCRAFT_ARMORSMITHING,         2 },
  { rbtSKILL,        skCRAFT_BOWMAKING,         2 },
  { rbtSKILL,        skCRAFT_BLACKSMITHING,         2 },
  { rbtSKILL,        skCRAFT_CARPENTRY,         2 },
  { rbtSKILL,        skCRAFT_LEATHERWORKING,         2 },
  { rbtSKILL,        skCRAFT_PAINTING,         2 },
  { rbtSKILL,        skCRAFT_POTTERY,         2 },
  { rbtSKILL,        skCRAFT_SCULPTING,         2 },
  { rbtSKILL,        skCRAFT_SHIPMAKING,         2 },
  { rbtSKILL,        skCRAFT_STONEMASONRY,         2 },
  { rbtSKILL,        skCRAFT_TRAPMAKING,         2 },
  { rbtSKILL,        skCRAFT_WEAPONSMITHING,         2 },
  { rbtSKILL,        skCRAFT_WOODWORKING,         2 },
  { rbtSKILL,        skHANDLEANIMAL,  1 },
  { rbtSKILL,        skLISTEN,        2 },
  { rbtSKILL,        skRIDE,          1 },
  { rbtSKILL,        skSEARCH,        3 },
  { rbtSKILL,        skSPOT,          3 },
  { rbtSKILL,        skSURVIVAL,3 },
  { rbtFEAT,         ftENDURANCE,     0 },
  { rbtFEAT,         ftMOUNTEDCOMBAT, 0 },
  { rbtFEAT,         ftPOINTBLANKSHOT,0 },
  { rbtFEAT,         ftPRECISESHOT,   0 },
  { rbtFEAT,         ftRIDEBYATTACK,  0 },
  { rbtFEAT,         ftRUN,           0 },
  { rbtFEAT,         ftTRACK,         0 },
  { 0,               0,               0 }
};

static int humanLanguages[] = { lnCOMMON, 0 };
static int elfLanguages[] = { lnELVEN, lnCOMMON, 0 };
static int dwarfLanguages[] = { lnDWARVEN, lnCOMMON, 0 };
static int gnomeLanguages[] = { lnGNOME, lnCOMMON, 0 };
static int halflingLanguages[] = { lnHALFLING, lnCOMMON, 0 };
static int halforcLanguages[] = { lnCOMMON, lnORC, 0 };
static int sylvanLanguages[] = { lnCOMMON, lnSYLVAN, 0 };
static int ignanLanguages[] = { lnCOMMON, lnIGNAN, 0 };
static int bugbearLanguages[] = { lnCOMMON, lnGOBLIN, 0 };
static int centaurLanguages[] = { lnSYLVAN, lnELVEN, 0 };
static int undercommonLanguages[] = { lnCOMMON, lnUNDERCOMMON, 0 };
static int drowLanguages[] = { lnELVEN, lnCOMMON, lnUNDERCOMMON, 0 };
static int giantLanguages[] = { lnGIANT, lnCOMMON, 0 };
static int gnollLanguages[] = { lnGNOLL, 0 };
static int forestGnomeLanguages[] = { lnGNOME, lnELVEN, lnSYLVAN, 0 };
static int svirfneblinLanguages[] = { lnGNOME, lnCOMMON, lnTERRAN, lnUNDERCOMMON, 0 };
static int goblinLanguages[] = { lnGOBLIN, 0 };
static int tallfellowLanguages[] = { lnCOMMON, lnHALFLING, lnELVEN, 0 };
static int deepHalfLanguages[] = { lnCOMMON, lnHALFLING, lnDWARVEN, 0 };
static int draconicLanguages[] = { lnDRACONIC, 0 };
static int kuotoaLanguages[] = { lnUNDERCOMMON, lnAQUAN, 0 };
static int merfolkLanguages[] = { lnCOMMON, lnAQUAN, 0 };
static int orcLanguages[] = { lnORC, 0 };
static int yuantiLanguages[] = { lnCOMMON, lnDRACONIC, lnABYSSAL, 0 };
static int majorLanguages[] = { lnCOMMON, lnDWARVEN, lnELVEN, lnGNOME, lnHALFLING, 0 };

static int asaathLanguages[] = { lnCOMMON, lnDRACONIC, 0 };

static int dwarvenBonusLang[] = { lnGIANT, lnGNOME, lnGOBLIN, lnORC, lnTERRAN, lnUNDERCOMMON, 0 };
static int elvenBonusLang[] = { lnDRACONIC, lnGNOLL, lnGNOME, lnGOBLIN, lnORC, lnSYLVAN, 0 };
static int halforcBonusLang[] = { lnDRACONIC, lnGIANT, lnGNOLL, lnGOBLIN, lnINFERNAL, 0 };
static int halflingBonusLang[] = { lnDWARVEN, lnELVEN, lnGNOME, lnGOBLIN, lnORC, 0 };
static int araneaBonusLang[] = { lnELVEN, lnUNDERCOMMON, 0 };
static int evilBonusLang[] = { lnORC, lnGOBLIN, lnGNOLL, lnABYSSAL, lnGIANT, lnINFERNAL, lnUNDERCOMMON, 0 };
static int goodBonusLang[] = { lnCELESTIAL, lnAURAN, lnELVEN, lnSYLVAN, 0 };

static const struct {
  int                   id;
  int                   speed;
  int                   challengeRating;
  int                   size;
  int                   extraHitDieCount;
  int                   extraHitDie;
  int                   preferredClass;
  int                   usualAlignment;
  RACIALBONUS*          maleBonuses;
  RACIALBONUS*          femaleBonuses;
  DNDRACIALHEIGHTWEIGHT male;
  DNDRACIALHEIGHTWEIGHT female;
  int*                  automaticLanguages;
  int*                  bonusLanguages;
  char*                 name;
} s_races[] = {
  { rcAASIMAR,              30,  0, szMEDIUM,  0, 0, pcPALADIN,   alGOOD,                    aasimarBonuses,      aasimarBonuses,      {  4, 10, 2, 10,   120, 2,  4 }, { 4,   5, 2, 10,    85, 2,  4 }, humanLanguages,       0,               "aasimar" },
  { rcARANEA,               50,  4, szMEDIUM,  3, 8, pcSORCERER,  alLCNEUTRAL | alGENEUTRAL, araneaBonuses,       araneaBonuses,       {  2,  8, 2,  4,   100, 4,  4 }, { 2,   8, 2,  4,   100, 4,  4 }, sylvanLanguages,      araneaBonusLang, "aranea" },
  { rcAZER,                 30,  2, szMEDIUM,  2, 8, pcFIGHTER,   alLAWFUL | alGENEUTRAL,    azerBonuses,         azerBonuses,         {  3,  9, 2,  4,   130, 2,  6 }, { 3,   7, 2,  4,   100, 2,  6 }, ignanLanguages,       dwarvenBonusLang,"azer" },
  { rcBUGBEAR,              30,  2, szMEDIUM,  3, 8, pcROGUE,     alCHAOTIC | alEVIL,        bugbearBonuses,      bugbearBonuses,      {  6,  5, 2,  6,   170, 1,  8 }, { 6,   4, 2,  6,   160, 1,  8 }, bugbearLanguages,     evilBonusLang,   "bugbear" },
  { rcCENTAUR,              50,  3, szLARGE,   4, 8, pcRANGER,    alLCNEUTRAL | alGOOD,      centaurBonuses,      centaurBonuses,      {  7,  6, 2, 10,   600, 3,  8 }, { 7,   6, 2, 10,   600, 3,  8 }, centaurLanguages,     elvenBonusLang,  "centaur" },
  { rcDOPPLEGANGER,         30,  3, szMEDIUM,  4, 8, 0,           alGENEUTRAL,               dopplegangerBonuses, dopplegangerBonuses, {  4, 10, 2, 10,   120, 2,  4 }, { 4,   5, 2, 10,    85, 2,  4 }, humanLanguages,       evilBonusLang,   "doppleganger" },
  { rcDRIDER,               30,  7, szLARGE,   6, 8, pcSORCERER,  alCHAOTIC | alEVIL,        driderBonuses,       driderBonuses,       {  7,  6, 2, 10,   600, 3,  8 }, { 7,   6, 2, 10,   600, 3,  8 }, undercommonLanguages, evilBonusLang,   "drider" },
  { rcDWARF_DEEP,           20,  0, szMEDIUM,  0, 0, pcFIGHTER,   alGENEUTRAL,               deepDwarfBonuses,    deepDwarfBonuses,    {  3,  9, 2,  4,   130, 2,  6 }, { 3,   7, 2,  4,   100, 2,  6 }, dwarfLanguages,       dwarvenBonusLang,"dwarf (deep)" },
  { rcDWARF_DERRO,          20,  1, szMEDIUM,  0, 0, pcSORCERER,  alCHAOTIC | alEVIL,        derroBonuses,        derroBonuses,        {  3,  9, 2,  4,   130, 2,  6 }, { 3,   7, 2,  4,   100, 2,  6 }, dwarfLanguages,       dwarvenBonusLang,"dwarf (derro)" },
  { rcDWARF_DUERGAR,        20,  1, szMEDIUM,  0, 0, pcFIGHTER,   alLAWFUL | alEVIL,         duergarBonuses,      duergarBonuses,      {  3,  9, 2,  4,   130, 2,  6 }, { 3,   7, 2,  4,   100, 2,  6 }, dwarfLanguages,       dwarvenBonusLang,"dwarf (duergar)" },
  { rcDWARF_HILL,           20,  0, szMEDIUM,  0, 0, pcFIGHTER,   alLAWFUL,                  dwarvenHBonuses,     dwarvenHBonuses,     {  3,  9, 2,  4,   130, 2,  6 }, { 3,   7, 2,  4,   100, 2,  6 }, dwarfLanguages,       dwarvenBonusLang,"dwarf" },
  { rcDWARF_MOUNTAIN,       20,  0, szMEDIUM,  0, 0, pcFIGHTER,   alLAWFUL | alGOOD,         mtnDwarfBonuses,     mtnDwarfBonuses,     {  3,  9, 2,  4,   130, 2,  6 }, { 3,   7, 2,  4,   100, 2,  6 }, dwarfLanguages,       dwarvenBonusLang,"dwarf (mountain)" },
  { rcELF_AQUATIC,          30,  0, szMEDIUM,  0, 0, pcFIGHTER,   alCHAOTIC,                 aqElfBonuses,        aqElfBonuses,        {  4,  5, 2,  6,    85, 1,  6 }, { 4,   5, 2,  6,    80, 1,  6 }, elfLanguages,         elvenBonusLang,  "elf (aquatic)" },
  { rcELF_DROW,             30,  1, szMEDIUM,  0, 0, pcWIZARD,    alLCNEUTRAL | alEVIL,      drowMaleBonuses,     drowFemaleBonuses,   {  4,  5, 2,  6,    85, 1,  6 }, { 4,   5, 2,  6,    80, 1,  6 }, drowLanguages,        elvenBonusLang,  "elf (drow)" },
  { rcELF_GRAY,             30,  0, szMEDIUM,  0, 0, pcWIZARD,    alCHAOTIC | alGOOD,        grayElfBonuses,      grayElfBonuses,      {  4,  5, 2,  6,    85, 1,  6 }, { 4,   5, 2,  6,    80, 1,  6 }, elfLanguages,         elvenBonusLang,  "elf (gray)" },
  { rcELF_HIGH,             30,  0, szMEDIUM,  0, 0, pcWIZARD,    alCHAOTIC,                 elvenHBonuses,       elvenHBonuses,       {  4,  5, 2,  6,    85, 1,  6 }, { 4,   5, 2,  6,    80, 1,  6 }, elfLanguages,         elvenBonusLang,  "elf" },
  { rcELF_WILD,             30,  0, szMEDIUM,  0, 0, pcSORCERER,  alCHAOTIC | alGOOD,        wildElfBonuses,      wildElfBonuses,      {  4,  5, 2,  6,    85, 1,  6 }, { 4,   5, 2,  6,    80, 1,  6 }, elfLanguages,         elvenBonusLang,  "elf (wild)" },
  { rcELF_WOOD,             30,  0, szMEDIUM,  0, 0, pcRANGER,    alLCNEUTRAL,               woodElfBonuses,      woodElfBonuses,      {  4,  5, 2,  6,    85, 1,  6 }, { 4,   5, 2,  6,    80, 1,  6 }, elfLanguages,         elvenBonusLang,  "elf (wood)" },
  { rcETTIN,                40,  5, szLARGE,  10, 8, pcBARBARIAN, alCHAOTIC | alEVIL,        ettinBonuses,        ettinBonuses,        { 12,  0, 2, 12,  4500, 9, 12 }, { 12,  0, 2, 12,  4500, 9, 12 }, 0,                    evilBonusLang,   "ettin" },
  { rcGIANT_CLOUD,          50, 11, szHUGE,   17, 8, pcSORCERER,  alLCNEUTRAL,               cloudGiantBonuses,   cloudGiantBonuses,   { 17,  0, 2, 12,  4800, 3, 20 }, { 16,  6, 2, 12,  4600, 3, 20 }, giantLanguages,       goodBonusLang,   "giant, cloud" },
  { rcGIANT_FIRE,           40, 10, szLARGE,  15, 8, pcCLERIC,    alLAWFUL | alEVIL,         fireGiantBonuses,    fireGiantBonuses,    { 11,  6, 1, 12,  6850, 2, 20 }, { 11,  0, 1, 12,  6650, 2, 20 }, giantLanguages,       evilBonusLang,   "giant, fire" },
  { rcGIANT_FROST,          40,  9 ,szLARGE,  14, 8, pcCLERIC,    alCHAOTIC | alEVIL,        frostGiantBonuses,   frostGiantBonuses,   { 14,  0, 2, 12,  2600, 2, 20 }, { 13,  8, 2, 12,  2500, 2, 20 }, giantLanguages,       evilBonusLang,   "giant, frost" },
  { rcGIANT_HILL,           40,  7, szLARGE,  12, 8, pcBARBARIAN, alCHAOTIC | alEVIL,        hillGiantBonuses,    hillGiantBonuses,    {  9,  8, 2, 10,  1000, 1, 10 }, {  9,  8, 2, 10,  1000, 1, 10 }, giantLanguages,       evilBonusLang,   "giant, hill" },
  { rcGIANT_STONE,          40,  8, szLARGE,  14, 8, pcBARBARIAN, alLCNEUTRAL | alGENEUTRAL, stoneGiantBonuses,   stoneGiantBonuses,   { 11,  4, 2,  8,  1400, 2, 10 }, { 11,  4, 2,  8,  1400, 2, 10 }, giantLanguages,       evilBonusLang,   "giant, stone" },
  { rcGIANT_STORM,          50, 13, szHUGE,   19, 8, pcSORCERER,  alCHAOTIC | alGOOD,        stormGiantBonuses,   stormGiantBonuses,   { 20,  0, 2, 12, 11500, 4, 20 }, { 20,  0, 2, 12, 11500, 4, 20 }, giantLanguages,       goodBonusLang,   "giant, storm" },
  { rcGNOLL,                30,  1, szMEDIUM,  2, 8, pcRANGER,    alCHAOTIC | alEVIL,        gnollBonuses,        gnollBonuses,        {  6,  8, 2, 10,   180, 2,  6 }, { 6,   4, 2, 10,   180, 2,  6 }, gnollLanguages,       evilBonusLang,   "gnoll" },
  { rcGNOME_FOREST,         20,  0, szSMALL,   0, 0, pcWIZARD,    alLCNEUTRAL | alGOOD,      forestGnomeBonuses,  forestGnomeBonuses,  {  1, 11, 2,  4,    25, 1,  1 }, { 2,   0, 2,  4,    25, 1,  1 }, forestGnomeLanguages, halflingBonusLang, "gnome (forest)" },
  { rcGNOME_ROCK,           20,  0, szSMALL,   0, 0, pcBARD,      alGOOD,                    gnomeRBonuses,       gnomeRBonuses,       {  3,  0, 2,  4,    40, 1,  1 }, { 2,  10, 2,  4,    35, 1,  1 }, gnomeLanguages,       halflingBonusLang, "gnome" },
  { rcGNOME_SVIRFNEBLIN,    20,  1, szSMALL,   0, 0, pcWIZARD,    alLCNEUTRAL,               svirfneblinBonuses,  svirfneblinBonuses,  {  3,  0, 2,  4,    40, 1,  1 }, { 2,  10, 2,  4,    35, 1,  1 }, svirfneblinLanguages, halflingBonusLang, "gnome (svirfneblin)" },
  { rcGOBLIN,               30,  0, szSMALL,   0, 0, pcROGUE,     alLCNEUTRAL | alEVIL,      goblinBonuses,       goblinBonuses,       {  3,  0, 2,  4,    40, 1,  1 }, { 2,  10, 2,  4,    35, 1,  1 }, goblinLanguages,      evilBonusLang,   "goblin" },
  { rcGRIMLOCK,             30,  1, szMEDIUM,  2, 8, pcBARBARIAN, alLCNEUTRAL | alEVIL,      grimlockBonuses,     grimlockBonuses,     {  4,  5, 2,  6,   100, 2,  6 }, { 4,   5, 2,  6,   100, 2,  6 }, goblinLanguages,      evilBonusLang,   "grimlock" },
  { rcHAG_ANNIS,            40,  6, szLARGE,   7, 8, pcSORCERER,  alCHAOTIC | alEVIL,        annisBonuses,        annisBonuses,        {  7,  6, 1, 12,   380, 2,  6 }, {  7,  6, 1, 12,   380, 2,  6 }, giantLanguages,       evilBonusLang,   "hag, annis" },
  { rcHAG_GREEN,            30,  5, szLARGE,   9, 8, pcSORCERER,  alCHAOTIC | alEVIL,        greenHagBonuses,     greenHagBonuses,     {  6,  5, 2,  6,   170, 1,  8 }, { 6,   4, 2,  6,   160, 1,  8 }, giantLanguages,       evilBonusLang,   "hag, green" },
  { rcHAG_SEA,              30,  4, szLARGE,   3, 8, pcSORCERER,  alCHAOTIC | alEVIL,        seaHagBonuses,       seaHagBonuses,       {  7,  6, 1, 12,   380, 2,  6 }, {  7,  6, 1, 12,   380, 2,  6 }, giantLanguages,       evilBonusLang,   "hag, sea" },
  { rcHALFELF,              30,  0, szMEDIUM,  0, 0, 0,           0,                         halfElvenBonuses,    halfElvenBonuses,    {  4,  7, 2,  8,   100, 2,  4 }, { 4,   5, 2,  8,    80, 2,  4 }, elfLanguages,         0,               "half-elf" },
  { rcHALFLING_DEEP,        20,  0, szSMALL,   0, 0, pcROGUE,     alLCNEUTRAL,               halflingDeepBonuses, halflingDeepBonuses, {  2,  8, 2,  4,    30, 1,  1 }, { 2,   6, 2,  4,    25, 1,  1 }, deepHalfLanguages,    halflingBonusLang, "halfling (deep)" },
  { rcHALFLING_LIGHTFOOT,   20,  0, szSMALL,   0, 0, pcROGUE,     alLCNEUTRAL,               halflingLFBonuses,   halflingLFBonuses,   {  2,  8, 2,  4,    30, 1,  1 }, { 2,   6, 2,  4,    25, 1,  1 }, halflingLanguages,    halflingBonusLang, "halfling" },
  { rcHALFLING_TALLFELLOW,  20,  0, szSMALL,   0, 0, pcROGUE,     alLCNEUTRAL,               tallfellowBonuses,   tallfellowBonuses,   {  3,  9, 2,  4,   130, 2,  6 }, { 3,   7, 2,  4,   100, 2,  6 }, tallfellowLanguages,  halflingBonusLang, "halfling (tallfellow)" },
  { rcHALFORC,              30,  0, szMEDIUM,  0, 0, pcBARBARIAN, alCHAOTIC,                 halforcBonuses,      halforcBonuses,      {  4, 10, 2, 10,   130, 2,  4 }, { 4,   4, 2, 10,    90, 2,  4 }, halforcLanguages,     evilBonusLang,   "half-orc" },
  { rcHARPY,                20,  4, szMEDIUM,  7, 8, pcBARD,      alCHAOTIC | alEVIL,        harpyBonuses,        harpyBonuses,        {  4,  5, 2,  6,    85, 1,  6 }, { 4,   5, 2,  6,    80, 1,  6 }, humanLanguages,       evilBonusLang,   "harpy" },
  { rcHOBGOBLIN,            30,  0, szMEDIUM,  0, 0, pcFIGHTER,   alLAWFUL | alEVIL,         hobgoblinBonuses,    hobgoblinBonuses,    {  5,  6, 2, 10,   180, 2,  6 }, { 5,   4, 2, 10,   170, 2,  6 }, bugbearLanguages,     evilBonusLang,   "hobgoblin" },
  { rcHUMAN,                30,  0, szMEDIUM,  0, 0, 0,           0,                         0,                   0,                   {  4, 10, 2, 10,   120, 2,  4 }, { 4,   5, 2, 10,    85, 2,  4 }, humanLanguages,       0,               "human" },
  { rcKOBOLD,               30,  0, szSMALL,   0, 0, pcSORCERER,  alLAWFUL | alEVIL,         koboldBonuses,       koboldBonuses,       {  3,  0, 2,  4,    40, 1,  1 }, { 2,  10, 2,  4,    35, 1,  1 }, draconicLanguages,    evilBonusLang,   "kobold" },
  { rcKUOTOA,               20,  2, szMEDIUM,  2, 8, pcROGUE,     alLCNEUTRAL | alEVIL,      kuotoaBonuses,       kuotoaBonuses,       {  4,  6, 2,  6,    85, 1,  6 }, { 4,   6, 2,  6,    80, 1,  6 }, kuotoaLanguages,      evilBonusLang,   "kuo-toa" },
  { rcLIZARDFOLK,           30,  1, szMEDIUM,  2, 8, pcDRUID,     alLCNEUTRAL,               lizardFolkBonuses,   lizardFolkBonuses,   {  5,  8, 2, 10,   180, 2,  6 }, { 5,   8, 2, 10,   180, 2,  6 }, draconicLanguages,    evilBonusLang,   "lizardfolk" },
  { rcLOCATHAH,             10,  0, szMEDIUM,  2, 8, pcBARBARIAN, alLCNEUTRAL | alGENEUTRAL, locathahBonuses,     locathahBonuses,     {  4,  6, 2,  6,   150, 1,  6 }, { 4,   6, 2,  6,   150, 1,  6 }, merfolkLanguages,     evilBonusLang,   "locathah" },
  { rcMEDUSA,               30,  7, szMEDIUM,  6, 8, pcROGUE,     alLAWFUL | alEVIL,         medusaBonuses,       medusaBonuses,       {  4, 10, 2, 10,   120, 2,  4 }, { 4,   8, 2, 10,   105, 2,  4 }, undercommonLanguages, evilBonusLang,   "medusa" },
  { rcMERFOLK,               5,  0, szMEDIUM,  0, 0, pcBARD,      alLCNEUTRAL | alGENEUTRAL, merfolkBonuses,      merfolkBonuses,      {  4, 10, 2, 10,   120, 2,  4 }, { 4,   8, 2, 10,   105, 2,  4 }, merfolkLanguages,     evilBonusLang,   "merfolk" },
  { rcMINDFLAYER,           30,  8, szMEDIUM,  8, 8, pcSORCERER,  alLAWFUL | alEVIL,         mindflayerBonuses,   mindflayerBonuses,   {  5,  0, 2, 10,   130, 2,  4 }, { 4,   9, 2, 10,   100, 2,  4 }, undercommonLanguages, evilBonusLang,   "mind flayer" },
  { rcMINOTAUR,             30,  4, szLARGE,   6, 8, pcBARBARIAN, alCHAOTIC | alEVIL,        minotaurBonuses,     minotaurBonuses,     {  6,  8, 2,  6,   250, 2,  8 }, { 6,   8, 4,  6,   250, 2,  8 }, giantLanguages,       evilBonusLang,   "minotaur" },
  { rcOGRE,                 30,  2, szLARGE,   4, 8, pcBARBARIAN, alCHAOTIC | alEVIL,        ogreBonuses,         ogreBonuses,         {  8,  6, 4,  6,   250, 2,  8 }, { 8,   6, 4,  6,   250, 2,  8 }, giantLanguages,       evilBonusLang,   "ogre" },
  { rcOGREMAGE,             30,  8, szLARGE,   5, 8, pcSORCERER,  alLAWFUL | alEVIL,         ogreMageBonuses,     ogreMageBonuses,     {  9,  0, 4,  6,   450, 2,  8 }, { 9,   0, 4,  6,   450, 2,  8 }, giantLanguages,       evilBonusLang,   "ogre mage" },
  { rcORC,                  30,  0, szMEDIUM,  0, 0, pcBARBARIAN, alCHAOTIC | alEVIL,        orcBonuses,          orcBonuses,          {  4, 10, 2, 10,   120, 2,  4 }, { 4,   5, 2, 10,    85, 2,  4 }, orcLanguages,         evilBonusLang,   "orc" },
  { rcSAHUAGIN,             30,  2, szMEDIUM,  2, 8, pcRANGER,    alLAWFUL | alEVIL,         sahuaginBonuses,     sahuaginBonuses,     {  5,  1, 2, 10,   150, 2,  4 }, { 5,   0, 2, 10,   150, 2,  4 }, kuotoaLanguages,      evilBonusLang,   "sahuagin" },
  { rcTIEFLING,             30,  0, szMEDIUM,  0, 0, pcROGUE,     alEVIL,                    tieflingBonuses,     tieflingBonuses,     {  4, 10, 2, 10,   120, 2,  4 }, { 4,   5, 2, 10,    85, 2,  4 }, humanLanguages,       0,               "tiefling" },
  { rcTROGLODYTE,           30,  1, szMEDIUM,  2, 8, pcCLERIC,    alCHAOTIC | alEVIL,        troglodyteBonuses,   troglodyteBonuses,   {  4,  5, 2,  6,   130, 1,  6 }, { 4,   5, 2,  6,   120, 1,  6 }, draconicLanguages,    evilBonusLang,   "troglodyte" },
  { rcTROLL,                30,  5, szLARGE,   6, 8, pcBARBARIAN, alCHAOTIC | alEVIL,        trollBonuses,        trollBonuses,        {  8,  6, 1, 12,   400, 2, 20 }, {  8,  6, 1, 12,   400, 2, 20 }, giantLanguages,       evilBonusLang,   "troll" },
  { rcYUANTI_ABOMINATION,   30,  7, szLARGE,   9, 8, pcCLERIC,    alCHAOTIC | alEVIL,        yuanti3Bonuses,      yuanti3Bonuses,      {  7,  6, 1, 12,   380, 2,  6 }, {  7,  6, 1, 12,   380, 2,  6 }, yuantiLanguages,      evilBonusLang,   "yuan-ti, abomination" },
  { rcYUANTI_HALFBLOOD,     30,  5, szMEDIUM,  7, 8, pcRANGER,    alCHAOTIC | alEVIL,        yuanti2Bonuses,      yuanti2Bonuses,      {  4, 10, 2, 10,   120, 2,  4 }, { 4,   5, 2, 10,    85, 2,  4 }, yuantiLanguages,      evilBonusLang,   "yuan-ti, halfblood" },
  { rcYUANTI_PUREBLOOD,     30,  5, szMEDIUM,  6, 8, pcRANGER,    alCHAOTIC | alEVIL,        yuanti1Bonuses,      yuanti1Bonuses,      {  4, 10, 2, 10,   120, 2,  4 }, { 4,   5, 2, 10,    85, 2,  4 }, yuantiLanguages,      evilBonusLang,   "yuan-ti, pureblood" },
  { rcCC_ABANDONED,         30,  0, szLARGE,   2, 8, pcBARBARIAN, alLCNEUTRAL | alGENEUTRAL, cc_abandonedBonuses, cc_abandonedBonuses, {  8,  6, 4,  6,   250, 2,  8 }, { 8,   6, 4,  6,   250, 2,  8 }, 0,                    0,               "abandoned" },
  { rcCC_ASAATH,            40,  2, szMEDIUM,  3, 8, pcFIGHTER,   alCHAOTIC | alEVIL,        cc_asaathBonuses,    cc_asaathBonuses,    {  5,  6, 2, 10,   100, 2,  4 }, { 5,   4, 2, 10,    85, 2,  4 }, asaathLanguages,      evilBonusLang,   "asaath" },
  { rcCC_BATDEVIL,          30,  0, szMEDIUM,  2, 8, pcROGUE,     alLCNEUTRAL | alGENEUTRAL, cc_batDevilBonuses,  cc_batDevilBonuses,  {  4,  5, 2,  6,    85, 1,  6 }, { 4,   5, 2,  6,    80, 1,  6 }, 0,                    0,               "bat devil" },
  { rcCC_PLAGUEWRETCH,      30,  2, szMEDIUM,  3, 8, pcFIGHTER,   alLCNEUTRAL | alEVIL,      cc_plagueWretchBonuses, cc_plagueWretchBonuses, {  4, 10, 2, 10,   120, 2,  4 }, { 4,   5, 2, 10,    85, 2,  4 }, 0,              0,               "plague wretch (carnival krewe)" },
  { rcCC_CHARDUNI,          20,  0, szMEDIUM,  0, 8, pcFIGHTER,   alLAWFUL | alEVIL,         cc_charduniBonuses,  cc_charduniBonuses,  {  3, 11, 2,  4,   130, 2,  6 }, { 3,   9, 2,  4,   100, 2,  6 }, dwarfLanguages,       dwarvenBonusLang,"charduni" },
  { rcCC_COALGOBLIN,        30,  0, szSMALL,   2, 8, pcROGUE,     alLCNEUTRAL | alEVIL,      cc_coalGoblinBonuses,cc_coalGoblinBonuses,{  3,  0, 2,  4,    40, 1,  1 }, { 2,  10, 2,  4,    35, 1,  1 }, goblinLanguages,      evilBonusLang,   "coal goblin" },
  { rcCC_DWARF_FORSAKEN,    15,  0, szMEDIUM,  0, 8, pcFIGHTER,   alLAWFUL | alEVIL,         cc_fdwarfBonuses,    cc_fdwarfBonuses,    {  3,  9, 2,  4,   130, 2,  6 }, { 3,   7, 2,  4,   100, 2,  6 }, dwarfLanguages,       dwarvenBonusLang,"dwarf (forsaken)" },
  { rcCC_ELF_FORSAKEN,      30,  0, szMEDIUM,  0, 8, pcFIGHTER,   alCHAOTIC | alGENEUTRAL,   cc_felfBonuses,      cc_felfBonuses,      {  4,  5, 2,  6,    85, 1,  6 }, { 4,   5, 2,  6,    80, 1,  6 }, elfLanguages,         elvenBonusLang,  "elf (forsaken)" },
  { rcCC_ICE_GHOUL,         40,  1, szMEDIUM,  2, 8, pcBARBARIAN, alCHAOTIC | alEVIL,        cc_iceGhoulBonuses,  cc_iceGhoulBonuses,  {  4, 10, 2, 10,   120, 2,  4 }, { 4,   5, 2, 10,    85, 2,  4 }, 0,                    0,               "ice ghoul" },
  { rcCC_MANTICORA,         30,  2, szMEDIUM,  2, 8, pcBARBARIAN, alCHAOTIC | alEVIL,        cc_manticoraBonuses, cc_manticoraBonuses, {  5,  2, 2, 10,   100, 2,  4 }, { 5,   2, 2, 10,    85, 2,  4 }, humanLanguages,       evilBonusLang,   "manticora" },
  { rcCC_MORGAUNT,          60,  1, szMEDIUM,  3, 8, npcCOMMONER, alLCNEUTRAL | alEVIL,      cc_morgauntBonuses,  cc_morgauntBonuses,  {  4, 10, 2, 10,   120, 2,  4 }, { 4,   5, 2, 10,    85, 2,  4 }, humanLanguages,       0,               "morgaunt" }, 
  { rcCC_PROUD,             60,  1, szLARGE,   3, 8, pcBARBARIAN, alCHAOTIC | alEVIL,        cc_proudBonuses,     cc_proudBonuses,     {  6,  6, 2, 10,   400, 3,  8 }, { 6,   6, 2, 10,   400, 3,  8 }, humanLanguages,       0,               "proud" },
  { rcCC_RATMAN,            30,  0, szMEDIUM,  0, 8, pcROGUE,     alLAWFUL | alEVIL,         cc_ratmanBonuses,    cc_ratmanBonuses,    {  4, 10, 2, 10,   120, 2,  4 }, { 4,   5, 2, 10,    85, 2,  4 }, humanLanguages,       0,               "ratman" }, 
  { rcCC_RATMAN_BROWNGORGER,30,  0, szMEDIUM,  0, 8, pcFIGHTER,   alLAWFUL | alEVIL,         cc_bgratmanBonuses,  cc_bgratmanBonuses,  {  4, 10, 2, 10,   120, 2,  4 }, { 4,   5, 2, 10,    85, 2,  4 }, humanLanguages,       0,               "ratman, brown gorger" }, 
  { rcCC_RATMAN_DISEASED,   30,  0, szMEDIUM,  0, 8, pcCLERIC,    alLAWFUL | alEVIL,         cc_dratmanBonuses,   cc_dratmanBonuses,   {  4, 10, 2, 10,   120, 2,  4 }, { 4,   5, 2, 10,    85, 2,  4 }, humanLanguages,       0,               "ratman, the diseased" }, 
  { rcCC_RATMAN_FOAMER,     30,  0, szMEDIUM,  2, 8, npcWARRIOR,  alLAWFUL | alEVIL,         cc_fratmanBonuses,   cc_fratmanBonuses,   {  6,  6, 2, 10,   180, 3,  8 }, { 6,   6, 2, 10,   180, 3,  8 }, humanLanguages,       0,               "ratman, foamer" },
  { rcCC_RATMAN_REDWITCH,   30,  0, szMEDIUM,  0, 8, pcWIZARD,    alLAWFUL | alEVIL,         cc_rwratmanBonuses,  cc_rwratmanBonuses,  {  4, 10, 2, 10,   120, 2,  4 }, { 4,   5, 2, 10,    85, 2,  4 }, humanLanguages,       0,               "ratman, red witch" },
  { rcCC_SKINDEVIL,         60,  4, szMEDIUM,  5, 8, pcROGUE,     alCHAOTIC | alGENEUTRAL,   cc_skinDevilBonuses, cc_skinDevilBonuses, {  4, 10, 2, 10,   120, 2,  4 }, { 4,   5, 2, 10,    85, 2,  4 }, majorLanguages,       0,               "skin devil" },
  { rcCC_SPIDEREYEGOBLIN,   30,  0, szSMALL,   2, 8, pcROGUE,     alLCNEUTRAL | alEVIL,      cc_segoblinBonuses,  cc_segoblinBonuses,  {  3,  0, 2,  4,    40, 1,  1 }, { 2,  10, 2,  4,    35, 1,  1 }, goblinLanguages,      evilBonusLang,   "spider-eye goblin" },
  { rcCC_STEPPETROLL,       40,  5, szLARGE,   8, 8, pcBARBARIAN, alLCNEUTRAL | alGENEUTRAL, cc_strollBonuses,    cc_strollBonuses,    {  8,  6, 1, 12,   400, 2, 20 }, {  8,  6, 1, 12,   400, 2, 20 }, giantLanguages,       evilBonusLang,   "steppe troll" },
  { rcCC_STRIFEELEMENTAL,   30,  2, szMEDIUM,  4, 8, pcFIGHTER,   alCHAOTIC | alGENEUTRAL,   cc_selementBonuses,  cc_selementBonuses,  {  4, 10, 2, 10,   120, 2,  4 }, { 4,   5, 2, 10,    85, 2,  4 }, majorLanguages,       0,               "strife elemental" },
  { rcCC_TOKALTRIBESMAN,    30,  0, szMEDIUM,  2, 8, pcBARBARIAN, alLCNEUTRAL | alGENEUTRAL, cc_tokalBonuses,     cc_tokalBonuses,     {  4, 10, 2, 10,   120, 2,  4 }, { 4,   5, 2, 10,    85, 2,  4 }, 0,                    0,               "tokal tribesman" },
  { rcCC_UBANTUTRIBESMAN,   30,  0, szMEDIUM,  0, 8, pcBARBARIAN, alLAWFUL | alGENEUTRAL,    cc_ubantuBonuses,    cc_ubantuBonuses,    {  4, 10, 2, 10,   120, 2,  4 }, { 4,   5, 2, 10,    85, 2,  4 }, 0,                    0,               "ubantu tribesman" },
  { 0,                       0,  0, 0,         0, 0, 0,           0,                         0,                   0,                   {  0,  0, 0,  0,     0, 0,  0 }, {  0,  0, 0,  0,     0, 0,  0 }, 0,                    0,               0 }
};


static const struct {
  int   id;
  int   type;
  int   cost; /* copper pieces */
  int   acBonus;
  int   maxDex;
  int   checkPenalty;
  int   arcaneSpellFailure;
  char* name;
} s_armors[] = {                    
  { arPADDED,               atLIGHT,    500, 1,  8,   0,  5, "padded" },
  { arLEATHER,              atLIGHT,   1000, 2,  6,   0, 10, "leather" },
  { arSTUDDEDLEATHER,       atLIGHT,   2500, 3,  5,  -1, 15, "studded leather" },
  { arCHAINSHIRT,           atLIGHT,  10000, 4,  4,  -2, 20, "chain shirt" },
  { arHIDE,                atMEDIUM,   1500, 3,  4,  -3, 20, "hide" },
  { arSCALEMAIL,           atMEDIUM,   5000, 4,  3,  -4, 25, "scale mail" },
  { arCHAINMAIL,           atMEDIUM,  15000, 5,  2,  -5, 30, "chainmail" },
  { arBREASTPLATE,         atMEDIUM,  20000, 5,  3,  -4, 25, "breastplate" },
  { arSPLINTMAIL,           atHEAVY,  20000, 6,  0,  -7, 40, "splint mail" },
  { arBANDEDMAIL,           atHEAVY,  25000, 6,  1,  -6, 35, "banded mail" },
  { arHALFPLATE,            atHEAVY,  60000, 7,  0,  -7, 40, "half-plate" },
  { arFULLPLATE,            atHEAVY, 150000, 8,  1,  -6, 35, "full plate" },
  { arBUCKLER,             atSHIELD,   1500, 1, 99,  -1,  5, "buckler" },
  { arSHIELD_SMALL_WOODEN, atSHIELD,    300, 1, 99,  -1,  5, "shield, small, wooden" },
  { arSHIELD_SMALL_STEEL,  atSHIELD,    900, 1, 99,  -1,  5, "shield, small, steel" }, 
  { arSHIELD_LARGE_WOODEN, atSHIELD,    700, 2, 99,  -2, 15, "shield, large, wooden" },
  { arSHIELD_LARGE_STEEL,  atSHIELD,   2000, 2, 99,  -2, 15, "shield, large, steel" },
  { arSHIELD_TOWER,        atSHIELD,   3000, 0, 99, -10, 50, "shield, tower" },
  { 0,                     0,          0,    0,  0,   0,  0, 0 }
};


static const struct {
  int   id;
  int   size;
  int   cost; /* copper pieces */
  int   type;
  char* name;
  char* pcgen_name;
} s_weapons[] = {                         
  { wpGAUNTLET,             szTINY,         200, wtMELEE | wtBLUDGEONING | wtSIMPLE,                "gauntlet", "Gauntlet" },
  { wpUNARMED,              szTINY,           0, wtMELEE | wtBLUDGEONING | wtSIMPLE,                "strike, unarmed", "Unarmed Strike" },
  { wpDAGGER,               szTINY,         200, wtMELEE | wtPIERCING | wtSIMPLE,                   "dagger", "Dagger" },
  { wpDAGGER_PUNCHING,      szTINY,         200, wtMELEE | wtPIERCING | wtSIMPLE,                   "dagger, punching", "Dagger (Punching)" },
  { wpGAUNTLET_SPIKED,      szTINY,         500, wtMELEE | wtPIERCING | wtSIMPLE,                   "gauntlet, spiked", "Gauntlet (Spiked)" },
  { wpMACE_LIGHT,           szSMALL,        500, wtMELEE | wtBLUDGEONING | wtSIMPLE,                "mace, light", "Mace (Light)" },
  { wpSICKLE,               szSMALL,        600, wtMELEE | wtSLASHING | wtSIMPLE,                   "sickle", "Sickle" },
  { wpCLUB,                 szMEDIUM,         0, wtMELEE | wtBLUDGEONING | wtSIMPLE,                "club", "Club" },
  { wpHALFSPEAR,            szMEDIUM,       100, wtMELEE | wtPIERCING | wtSIMPLE,                   "spear", "Spear" },
  { wpMACE_HEAVY,           szMEDIUM,      1200, wtMELEE | wtBLUDGEONING | wtSIMPLE,                "mace, heavy", "Mace (Heavy)" },
  { wpMORNINGSTAR,          szMEDIUM,       800, wtMELEE | wtBLUDGEONING | wtPIERCING | wtSIMPLE,   "morningstar", "Morningstar" },
  { wpQUARTERSTAFF,         szLARGE,          0, wtMELEE | wtBLUDGEONING | wtSIMPLE,                "quarterstaff", "Quarterstaff" },
  { wpSHORTSPEAR,           szLARGE,        200, wtMELEE | wtPIERCING | wtSIMPLE,                   "shortspear", "Shortspear" },
  { wpCROSSBOW_LIGHT,       szSMALL,       3500, wtCROSSBOW | wtRANGED | wtPIERCING | wtSIMPLE,                  "crossbow, light", "Crossbow (Light)" },
  { wpDART,                 szSMALL,         50, wtRANGED | wtPIERCING | wtSIMPLE,                  "dart", "Dart" },
  { wpSLING,                szSMALL,          0, wtRANGED | wtBLUDGEONING | wtSIMPLE,               "sling", "Sling" },
  { wpCROSSBOW_HEAVY,       szMEDIUM,      5000, wtCROSSBOW | wtRANGED | wtPIERCING | wtSIMPLE,                  "crossbow, heavy", "Crossbow (Heavy)" },
  { wpJAVELIN,              szMEDIUM,       100, wtRANGED | wtPIERCING | wtSIMPLE,                  "javelin", "Javelin" },
  { wpAXE_THROWING,         szSMALL,        800, wtMELEE | wtSLASHING | wtMARTIAL,                  "axe, throwing", "Axe (Throwing)" },
  { wpHAMMER_LIGHT,         szSMALL,        100, wtMELEE | wtBLUDGEONING | wtMARTIAL,               "hammer, light", "Hammer (Light)" },
  { wpHANDAXE,              szSMALL,        600, wtMELEE | wtSLASHING | wtMARTIAL,                  "handaxe", "Handaxe" },
  { wpLANCE_LIGHT,          szSMALL,        600, wtMELEE | wtPIERCING | wtMARTIAL,                  "lance, light", "Lance" },
  { wpPICK_LIGHT,           szSMALL,        400, wtMELEE | wtPIERCING | wtMARTIAL,                  "pick, light", "Pick (Light)" },
  { wpSAP,                  szSMALL,        100, wtMELEE | wtBLUDGEONING | wtMARTIAL,               "sap", "Sap" },
  { wpSWORD_SHORT,          szSMALL,       1000, wtMELEE | wtPIERCING | wtMARTIAL,                  "sword, short", "Sword (Short)" },
  { wpBATTLEAXE,            szMEDIUM,      1000, wtMELEE | wtSLASHING | wtMARTIAL,                  "battleaxe", "Battleaxe" },
  { wpFLAIL_LIGHT,          szMEDIUM,       800, wtMELEE | wtBLUDGEONING | wtMARTIAL,               "flail, light", "Flail" },
  { wpLANCE_HEAVY,          szMEDIUM,      1000, wtMELEE | wtPIERCING | wtMARTIAL,                  "lance, heavy", "Lance (Heavy)" },
  { wpLONGSWORD,            szMEDIUM,      1500, wtMELEE | wtSLASHING | wtMARTIAL,                  "longsword", "Longsword" },
  { wpPICK_HEAVY,           szMEDIUM,       800, wtMELEE | wtPIERCING | wtMARTIAL,                  "pick, heavy", "Pick (Heavy)" },
  { wpRAPIER,               szMEDIUM,      2000, wtMELEE | wtPIERCING | wtMARTIAL,                  "rapier", "Rapier" },
  { wpSCIMITAR,             szMEDIUM,      1500, wtMELEE | wtSLASHING | wtMARTIAL,                  "scimitar", "Scimitar" },
  { wpTRIDENT,              szMEDIUM,      1500, wtMELEE | wtPIERCING | wtMARTIAL,                  "trident", "Trident" },
  { wpWARHAMMER,            szMEDIUM,      1200, wtMELEE | wtBLUDGEONING | wtMARTIAL,               "warhammer", "Warhammer" },
  { wpFALCHION,             szLARGE,       7500, wtMELEE | wtSLASHING | wtMARTIAL,                  "falchion", "Falchion" },
  { wpFLAIL_HEAVY,          szLARGE,       1500, wtMELEE | wtBLUDGEONING | wtMARTIAL,               "flail, heavy", "Flail (Heavy)" },
  { wpGLAIVE,               szLARGE,        800, wtMELEE | wtSLASHING | wtMARTIAL,                  "glaive", "Glaive" },
  { wpGREATAXE,             szLARGE,       2000, wtMELEE | wtSLASHING | wtMARTIAL,                  "greataxe", "Greataxe" },
  { wpGREATCLUB,            szLARGE,        500, wtMELEE | wtBLUDGEONING | wtMARTIAL,               "greatclub", "Greatclub" },
  { wpGREATSWORD,           szLARGE,       5000, wtMELEE | wtSLASHING | wtMARTIAL,                  "greatsword", "Greatsword" },
  { wpGUISARME,             szLARGE,        900, wtMELEE | wtSLASHING | wtMARTIAL,                  "guisarme", "Guisarme" },
  { wpHALBERD,              szLARGE,       1000, wtMELEE | wtPIERCING | wtSLASHING | wtMARTIAL,     "halberd", "Halberd" },
  { wpLONGSPEAR,            szLARGE,        500, wtMELEE | wtPIERCING | wtMARTIAL,                  "longspear", "Longspear" },
  { wpRANSEUR,              szLARGE,       1000, wtMELEE | wtPIERCING | wtMARTIAL,                  "ranseur", "Ranseur" },
  { wpSCYTHE,               szLARGE,       1800, wtMELEE | wtPIERCING | wtSLASHING | wtMARTIAL,     "scythe", "Scythe" },
  { wpSHORTBOW,             szMEDIUM,      3000, wtRANGED | wtPIERCING | wtMARTIAL,                 "shortbow", "Shortbow" },
  { wpSHORTBOW_COMPOSITE,   szMEDIUM,      7500, wtRANGED | wtPIERCING | wtMARTIAL,                 "shortbow, composite", "Shortbow (Composite)" },
  { wpLONGBOW,              szLARGE,       7500, wtRANGED | wtPIERCING | wtMARTIAL,                 "longbow", "Longbow" },
  { wpLONGBOW_COMPOSITE,    szLARGE,      10000, wtRANGED | wtPIERCING | wtMARTIAL,                 "longbow, composite", "Longbow (Composite)" },
  { wpKUKRI,                szTINY,         800, wtMELEE | wtSLASHING | wtEXOTIC,                   "kukri", "Kukri" },
  { wpKAMA,                 szSMALL,        200, wtMELEE | wtSLASHING | wtEXOTIC,                   "kama", "Kama" },
  { wpNUNCHAKU,             szSMALL,        200, wtMELEE | wtBLUDGEONING | wtEXOTIC,                "nunchaku", "Nunchaku" },
  { wpSIANGHAM,             szSMALL,        300, wtMELEE | wtPIERCING | wtEXOTIC,                   "siangham", "Siangham" },
  { wpSWORD_BASTARD,        szMEDIUM,      3500, wtMELEE | wtSLASHING | wtEXOTIC,                   "sword, bastard", "Sword (Bastard)" },
  { wpWARAXE_DWARVEN,       szMEDIUM,      3000, wtMELEE | wtSLASHING | wtEXOTIC,                   "waraxe, dwarven", "Waraxe (Dwarven)" },
  { wpHAMMER_GNOMEHOOKED,   szMEDIUM,      2000, wtMELEE | wtBLUDGEONING | wtPIERCING | wtEXOTIC,   "hammer, gnome hooked", "Hammer (Gnome Hooked)" },
  { wpAXE_ORCDOUBLE,        szLARGE,       6000, wtMELEE | wtSLASHING | wtEXOTIC,                   "axe, orc double", "Axe (Orc Double)" },
  { wpCHAIN_SPIKED,         szLARGE,       2500, wtMELEE | wtPIERCING | wtEXOTIC,                   "chain, spiked", "Chain (Spiked)" },
  { wpFLAIL_DIRE,           szLARGE,       9000, wtMELEE | wtBLUDGEONING | wtEXOTIC,                "flail, dire", "Flail (Dire)" },
  { wpSWORD_TWOBLADED,      szLARGE,      10000, wtMELEE | wtSLASHING | wtEXOTIC,                   "sword, two-bladed", "Sword (Two-Bladed)" },
  { wpURGOSH_DWARVEN,       szLARGE,       5000, wtMELEE | wtSLASHING | wtPIERCING | wtEXOTIC,      "urgosh, dwarven", "Urgrosh (Dwarven)" },
  { wpCROSSBOW_HAND,        szTINY,       10000, wtCROSSBOW | wtRANGED | wtPIERCING | wtEXOTIC,                  "crossbow, hand", "Crossbow (Hand)" },
  { wpSHURIKEN,             szTINY,         100, wtRANGED | wtPIERCING | wtEXOTIC,                  "shuriken", "Shuriken" },
  { wpWHIP,                 szSMALL,        100, wtRANGED | wtSLASHING | wtEXOTIC,                  "whip", "Whip" },
  { wpCROSSBOW_REPEATING,   szMEDIUM,     25000, wtRANGED | wtPIERCING | wtEXOTIC,                  "crossbow, repeating", "Crossbow (Repeating Light)" },
  { wpNET,                  szMEDIUM,      2000, wtRANGED | wtEXOTIC,                               "net", "Net" },
  { 0,                      0,                0, 0,                                                 0 }
};


static const struct {
  int   id;
  int   acMod;
  int   grappleMod;
  int   hideCheck;
  char* name;
} s_sizes[] = {
  { szFINE,        8, -16,  16, "fine" },
  { szDIMINUTIVE,  4, -12,  12, "diminutive" },
  { szTINY,        2,  -8,   8, "tiny" },
  { szSMALL,       1,  -4,   4, "small" },
  { szMEDIUM,      0,   0,   0, "medium" },
  { szLARGE,      -1,   4,  -4, "large" },
  { szHUGE,       -2,   8,  -8, "huge" },
  { szGARGANTUAN, -4,  12, -12, "gargantuan" },
  { szCOLOSSAL,   -8,  16, -16, "colossal" },
  { 0,             0,   0,   0, 0 }
};


static const struct {
  int   id;
  char* name;
} s_magicSchools[] = {
  { ssUNIVERSAL,     "universal" },
  { ssABJURATION,    "abjuration" },
  { ssCONJURATION,   "conjuration" },
  { ssDIVINATION,    "divination" },
  { ssENCHANTMENT,   "enchantment" },
  { ssEVOCATION,     "evocation" },
  { ssILLUSION,      "illusion" },
  { ssNECROMANCY,    "necromancy" },
  { ssTRANSMUTATION, "transmutation" },
  { 0,               0 }
};


static const struct {
  int   id;
  int   school;
  char* name;
  char* pcgen_name;
} s_spells[] = {
  { spACIDARROW,		ssCONJURATION,     "Acid Arrow", "Acid Arrow" },
  { spACIDFOG,		ssCONJURATION,     "Acid Fog", "Acid Fog" },
  { spACIDSPLASH,		ssCONJURATION,     "Acid Splash", "Acid Splash" },
  { spAID,		ssENCHANTMENT,     "Aid", "Aid" },
  { spAIRWALK,		ssTRANSMUTATION,     "Air Walk", "Air Walk" },
  { spALARM,		ssABJURATION,     "Alarm", "Alarm" },
  { spALIGNWEAPON,		ssTRANSMUTATION,     "Align Weapon", "Align Weapon" },
  { spALTERSELF,		ssTRANSMUTATION,     "Alter Self", "Alter Self" },
  { spANALYZEDWEOMER,		ssDIVINATION,     "Analyze Dweomer", "Analyze Dweomer" },
  { spANIMALGROWTH,		ssTRANSMUTATION,     "Animal Growth", "Animal Growth" },
  { spANIMALMESSENGER,		ssENCHANTMENT,     "Animal Messenger", "Animal Messenger" },
  { spANIMALSHAPES,		ssTRANSMUTATION,     "Animal Shapes", "Animal Shapes" },
  { spANIMALTRANCE,		ssENCHANTMENT,     "Animal Trance", "Animal Trance" },
  { spANIMATEDEAD,		ssNECROMANCY,     "Animate Dead", "Animate Dead" },
  { spANIMATEOBJECTS,		ssTRANSMUTATION,     "Animate Objects", "Animate Objects" },
  { spANIMATEPLANTS,		ssTRANSMUTATION,     "Animate Plants", "Animate Plants" },
  { spANIMATEROPE,		ssTRANSMUTATION,     "Animate Rope", "Animate Rope" },
  { spANTILIFESHELL,		ssABJURATION,     "Antilife Shell", "Antilife Shell" },
  { spANTIMAGICFIELD,		ssABJURATION,     "Antimagic Field", "Antimagic Field" },
  { spANTIPATHY,		ssENCHANTMENT,     "Antipathy", "Antipathy" },
  { spANTIPLANTSHELL,		ssABJURATION,     "Antiplant Shell", "Antiplant Shell" },
  { spARCANEEYE,		ssDIVINATION,     "Arcane Eye", "Arcane Eye" },
  { spARCANELOCK,		ssABJURATION,     "Arcane Lock", "Arcane Lock" },
  { spARCANEMARK,		ssUNIVERSAL,     "Arcane Mark", "Arcane Mark" },
  { spARCANESIGHT,		ssDIVINATION,     "Arcane Sight", "Arcane Sight" },
  { spARCANESIGHTGREATER,		ssDIVINATION,     "Greater Arcane Sight", "Arcane Sight (Greater)" },
  { spASTRALPROJECTION,		ssNECROMANCY,     "Astral Projection", "Astral Projection" },
  { spATONEMENT,		ssABJURATION,     "Atonement", "Atonement" },
  { spAUGURY,		ssDIVINATION,     "Augury", "Augury" },
  { spAWAKEN,		ssTRANSMUTATION,     "Awaken", "Awaken" },
  { spBALEFULPOLYMORPH,		ssTRANSMUTATION,     "Baleful Polymorph", "Baleful Polymorph" },
  { spBANE,		ssENCHANTMENT,     "Bane", "Bane" },
  { spBANISHMENT,		ssABJURATION,     "Banishment", "Banishment" },
  { spBARKSKIN,		ssTRANSMUTATION,     "Barkskin", "Barkskin" },
  { spBEARSENDURANCE,		ssTRANSMUTATION,     "Bear's Endurance", "Bear's Endurance" },
  { spBEARSENDURANCEMASS,		ssTRANSMUTATION,     "Mass Bear's Endurance", "Bear's Endurance (Mass)" },
  { spBESTOWCURSE,		ssNECROMANCY,     "Bestow Curse", "Bestow Curse" },
  { spBINDING,		ssENCHANTMENT,     "Binding", "Binding" },
  { spBLACKTENTACLES,		ssCONJURATION,     "Black Tentacles", "Black Tentacles" },
  { spBLADEBARRIER,		ssEVOCATION,     "Blade Barrier", "Blade Barrier" },
  { spBLASPHEMY,		ssEVOCATION,     "Blasphemy", "Blasphemy" },
  { spBLESS,		ssENCHANTMENT,     "Bless", "Bless" },
  { spBLESSWATER,		ssTRANSMUTATION,     "Bless Water", "Bless Water" },
  { spBLESSWEAPON,		ssTRANSMUTATION,     "Bless Weapon", "Bless Weapon" },
  { spBLIGHT,		ssNECROMANCY,     "Blight", "Blight" },
  { spBLINDNESSDEAFNESS,		ssNECROMANCY,     "Blindness/Deafness", "Blindness/Deafness" },
  { spBLINK,		ssTRANSMUTATION,     "Blink", "Blink" },
  { spBLUR,		ssILLUSION,     "Blur", "Blur" },
  { spBREAKENCHANTMENT,		ssABJURATION,     "Break Enchantment", "Break Enchantment" },
  { spBULLSSTRENGTH,		ssTRANSMUTATION,     "Bull's Strength", "Bull's Strength" },
  { spBULLSSTRENGTHMASS,		ssTRANSMUTATION,     "Mass Bull's Strength", "Bull's Strength (Mass)" },
  { spBURNINGHANDS,		ssEVOCATION,     "Burning Hands", "Burning Hands" },
  { spCALLLIGHTNING,		ssEVOCATION,     "Call Lightning", "Call Lightning" },
  { spCALLLIGHTNINGSTORM,		ssEVOCATION,     "Call Lightning Storm", "Call Lightning Storm" },
  { spCALMANIMALS,		ssENCHANTMENT,     "Calm Animals", "Calm Animals" },
  { spCALMEMOTIONS,		ssENCHANTMENT,     "Calm Emotions", "Calm Emotions" },
  { spCATSGRACE,		ssTRANSMUTATION,     "Cat's Grace", "Cat's Grace" },
  { spCATSGRACEMASS,		ssTRANSMUTATION,     "Mass Cat's Grace", "Cat's Grace (Mass)" },
  { spCAUSEFEAR,		ssNECROMANCY,     "Cause Fear", "Cause Fear" },
  { spCHAINLIGHTNING,		ssEVOCATION,     "Chain Lightning", "Chain Lightning" },
  { spCHANGESTAFF,		ssTRANSMUTATION,     "Changestaff", "Changestaff" },
  { spCHAOSHAMMER,		ssEVOCATION,     "Chaos Hammer", "Chaos Hammer" },
  { spCHARMANIMAL,		ssENCHANTMENT,     "Charm Animal", "Charm Animal" },
  { spCHARMMONSTER,		ssENCHANTMENT,     "Charm Monster", "Charm Monster" },
  { spCHARMMONSTERMASS,		ssENCHANTMENT,     "Mass Charm Monster", "Charm Monster (Mass)" },
  { spCHARMPERSON,		ssENCHANTMENT,     "Charm Person", "Charm Person" },
  { spCHILLMETAL,		ssTRANSMUTATION,     "Chill Metal", "Chill Metal" },
  { spCHILLTOUCH,		ssNECROMANCY,     "Chill Touch", "Chill Touch" },
  { spCIRCLEOFDEATH,		ssNECROMANCY,     "Circle of Death", "Circle of Death" },
  { spCLAIRAUDIENCECLAIRVOYANCE,		ssDIVINATION,     "Clairaudience/Clairvoyance", "Clairaudience/Clairvoyance" },
  { spCLENCHEDFIST,		ssEVOCATION,     "Clenched Fist", "Clenched Fist" },
  { spCLOAKOFCHAOS,		ssABJURATION,     "Cloak of Chaos", "Cloak of Chaos" },
  { spCLONE,		ssNECROMANCY,     "Clone", "Clone" },
  { spCLOUDKILL,		ssCONJURATION,     "Cloudkill", "Cloudkill" },
  { spCOLORSPRAY,		ssILLUSION,     "Color Spray", "Color Spray" },
  { spCOMMAND,		ssENCHANTMENT,     "Command", "Command" },
  { spCOMMANDPLANTS,		ssTRANSMUTATION,     "Command Plants", "Command Plants" },
  { spCOMMANDUNDEAD,		ssNECROMANCY,     "Command Undead", "Command Undead" },
  { spCOMMANDGREATER,		ssENCHANTMENT,     "Greater Command", "Command (Greater)" },
  { spCOMMUNE,		ssDIVINATION,     "Commune", "Commune" },
  { spCOMMUNEWITHNATURE,		ssDIVINATION,     "Commune with Nature", "Commune with Nature" },
  { spCOMPREHENDLANGUAGES,		ssDIVINATION,     "Comprehend Languages", "Comprehend Languages" },
  { spCONEOFCOLD,		ssEVOCATION,     "Cone of Cold", "Cone of Cold" },
  { spCONFUSION,		ssENCHANTMENT,     "Confusion", "Confusion" },
  { spCONFUSIONLESSER,		ssENCHANTMENT,     "Lesser Confusion", "Confusion (Lesser)" },
  { spCONSECRATE,		ssEVOCATION,     "Consecrate", "Consecrate" },
  { spCONTACTOTHERPLANE,		ssDIVINATION,     "Contact Other Plane", "Contact Other Plane" },
  { spCONTAGION,		ssNECROMANCY,     "Contagion", "Contagion" },
  { spCONTINGENCY,		ssEVOCATION,     "Contingency", "Contingency" },
  { spCONTINUALFLAME,		ssEVOCATION,     "Continual Flame", "Continual Flame" },
  { spCONTROLPLANTS,		ssTRANSMUTATION,     "Control Plants", "Control Plants" },
  { spCONTROLUNDEAD,		ssNECROMANCY,     "Control Undead", "Control Undead" },
  { spCONTROLWATER,		ssTRANSMUTATION,     "Control Water", "Control Water" },
  { spCONTROLWEATHER,		ssTRANSMUTATION,     "Control Weather", "Control Weather" },
  { spCONTROLWINDS,		ssTRANSMUTATION,     "Control Winds", "Control Winds" },
  { spCREATEFOODANDWATER,		ssCONJURATION,     "Create Food and Water", "Create Food and Water" },
  { spCREATEGREATERUNDEAD,		ssNECROMANCY,     "Create Greater Undead", "Create Greater Undead" },
  { spCREATEUNDEAD,		ssNECROMANCY,     "Create Undead", "Create Undead" },
  { spCREATEWATER,		ssCONJURATION,     "Create Water", "Create Water" },
  { spCREEPINGDOOM,		ssCONJURATION,     "Creeping Doom", "Creeping Doom" },
  { spCRUSHINGDESPAIR,		ssENCHANTMENT,     "Crushing Despair", "Crushing Despair" },
  { spCRUSHINGHAND,		ssEVOCATION,     "Crushing Hand", "Crushing Hand" },
  { spCURECRITICALWOUNDS,		ssCONJURATION,     "Cure Critical Wounds", "Cure Critical Wounds" },
  { spCURECRITICALWOUNDSMASS,		ssCONJURATION,     "Mass Cure Critical Wounds", "Cure Critical Wounds (Mass)" },
  { spCURELIGHTWOUNDS,		ssCONJURATION,     "Cure Light Wounds", "Cure Light Wounds" },
  { spCURELIGHTWOUNDSMASS,		ssCONJURATION,     "Mass Cure Light Wounds", "Cure Light Wounds (Mass)" },
  { spCUREMINORWOUNDS,		ssCONJURATION,     "Cure Minor Wounds", "Cure Minor Wounds" },
  { spCUREMODERATEWOUNDS,		ssCONJURATION,     "Cure Moderate Wounds", "Cure Moderate Wounds" },
  { spCUREMODERATEWOUNDSMASS,		ssCONJURATION,     "Mass Cure Moderate Wounds", "Cure Moderate Wounds (Mass)" },
  { spCURESERIOUSWOUNDS,		ssCONJURATION,     "Cure Serious Wounds", "Cure Serious Wounds" },
  { spCURESERIOUSWOUNDSMASS,		ssCONJURATION,     "Mass Cure Serious Wounds", "Cure Serious Wounds (Mass)" },
  { spCURSEWATER,		ssNECROMANCY,     "Curse Water", "Curse Water" },
  { spDANCINGLIGHTS,		ssEVOCATION,     "Dancing Lights", "Dancing Lights" },
  { spDARKNESS,		ssEVOCATION,     "Darkness", "Darkness" },
  { spDARKVISION,		ssTRANSMUTATION,     "Darkvision", "Darkvision" },
  { spDAYLIGHT,		ssEVOCATION,     "Daylight", "Daylight" },
  { spDAZE,		ssENCHANTMENT,     "Daze", "Daze" },
  { spDAZEMONSTER,		ssENCHANTMENT,     "Daze Monster", "Daze Monster" },
  { spDEATHKNELL,		ssNECROMANCY,     "Death Knell", "Death Knell" },
  { spDEATHWARD,		ssNECROMANCY,     "Death Ward", "Death Ward" },
  { spDEATHWATCH,		ssNECROMANCY,     "Deathwatch", "Deathwatch" },
  { spDEEPSLUMBER,		ssENCHANTMENT,     "Deep Slumber", "Deep Slumber" },
  { spDEEPERDARKNESS,		ssEVOCATION,     "Deeper Darkness", "Deeper Darkness" },
  { spDELAYPOISON,		ssCONJURATION,     "Delay Poison", "Delay Poison" },
  { spDELAYEDBLASTFIREBALL,		ssEVOCATION,     "Delayed Blast Fireball", "Delayed Blast Fireball" },
  { spDEMAND,		ssENCHANTMENT,     "Demand", "Demand" },
  { spDESECRATE,		ssEVOCATION,     "Desecrate", "Desecrate" },
  { spDESTRUCTION,		ssNECROMANCY,     "Destruction", "Destruction" },
  { spDETECTANIMALSORPLANTS,		ssDIVINATION,     "Detect Animals or Plants", "Detect Animals or Plants" },
  { spDETECTCHAOS,		ssDIVINATION,     "Detect Chaos", "Detect Chaos" },
  { spDETECTEVIL,		ssDIVINATION,     "Detect Evil", "Detect Evil" },
  { spDETECTGOOD,		ssDIVINATION,     "Detect Good", "Detect Good" },
  { spDETECTLAW,		ssDIVINATION,     "Detect Law", "Detect Law" },
  { spDETECTMAGIC,		ssDIVINATION,     "Detect Magic", "Detect Magic" },
  { spDETECTPOISON,		ssDIVINATION,     "Detect Poison", "Detect Poison" },
  { spDETECTSCRYING,		ssDIVINATION,     "Detect Scrying", "Detect Scrying" },
  { spDETECTSECRETDOORS,		ssDIVINATION,     "Detect Secret Doors", "Detect Secret Doors" },
  { spDETECTSNARESANDPITS,		ssDIVINATION,     "Detect Snares and Pits", "Detect Snares and Pits" },
  { spDETECTTHOUGHTS,		ssDIVINATION,     "Detect Thoughts", "Detect Thoughts" },
  { spDETECTUNDEAD,		ssDIVINATION,     "Detect Undead", "Detect Undead" },
  { spDICTUM,		ssEVOCATION,     "Dictum", "Dictum" },
  { spDIMENSIONDOOR,		ssCONJURATION,     "Dimension Door", "Dimension Door" },
  { spDIMENSIONALANCHOR,		ssABJURATION,     "Dimensional Anchor", "Dimensional Anchor" },
  { spDIMENSIONALLOCK,		ssABJURATION,     "Dimensional Lock", "Dimensional Lock" },
  { spDIMINISHPLANTS,		ssTRANSMUTATION,     "Diminish Plants", "Diminish Plants" },
  { spDISCERNLIES,		ssDIVINATION,     "Discern Lies", "Discern Lies" },
  { spDISCERNLOCATION,		ssDIVINATION,     "Discern Location", "Discern Location" },
  { spDISGUISESELF,		ssILLUSION,     "Disguise Self", "Disguise Self" },
  { spDISINTEGRATE,		ssTRANSMUTATION,     "Disintegrate", "Disintegrate" },
  { spDISMISSAL,		ssABJURATION,     "Dismissal", "Dismissal" },
  { spDISPELCHAOS,		ssABJURATION,     "Dispel Chaos", "Dispel Chaos" },
  { spDISPELEVIL,		ssABJURATION,     "Dispel Evil", "Dispel Evil" },
  { spDISPELGOOD,		ssABJURATION,     "Dispel Good", "Dispel Good" },
  { spDISPELLAW,		ssABJURATION,     "Dispel Law", "Dispel Law" },
  { spDISPELMAGIC,		ssABJURATION,     "Dispel Magic", "Dispel Magic" },
  { spDISPELMAGICGREATER,		ssABJURATION,     "Greater Dispel Magic", "Dispel Magic (Greater)" },
  { spDISPLACEMENT,		ssILLUSION,     "Displacement", "Displacement" },
  { spDISRUPTUNDEAD,		ssNECROMANCY,     "Disrupt Undead", "Disrupt Undead" },
  { spDISRUPTINGWEAPON,		ssTRANSMUTATION,     "Disrupting Weapon", "Disrupting Weapon" },
  { spDIVINATION,		ssDIVINATION,     "Divination", "Divination" },
  { spDIVINEFAVOR,		ssEVOCATION,     "Divine Favor", "Divine Favor" },
  { spDIVINEPOWER,		ssEVOCATION,     "Divine Power", "Divine Power" },
  { spDOMINATEANIMAL,		ssENCHANTMENT,     "Dominate Animal", "Dominate Animal" },
  { spDOMINATEMONSTER,		ssENCHANTMENT,     "Dominate Monster", "Dominate Monster" },
  { spDOMINATEPERSON,		ssENCHANTMENT,     "Dominate Person", "Dominate Person" },
  { spDOOM,		ssNECROMANCY,     "Doom", "Doom" },
  { spDREAM,		ssILLUSION,     "Dream", "Dream" },
  { spEAGLESSPLENDOR,		ssTRANSMUTATION,     "Eagle's Splendor", "Eagle's Splendor" },
  { spEAGLESSPLENDORMASS,		ssTRANSMUTATION,     "Mass Eagle's Splendor", "Eagle's Splendor (Mass)" },
  { spEARTHQUAKE,		ssEVOCATION,     "Earthquake", "Earthquake" },
  { spELEMENTALSWARM,		ssCONJURATION,     "Elemental Swarm", "Elemental Swarm" },
  { spENDUREELEMENTS,		ssABJURATION,     "Endure Elements", "Endure Elements" },
  { spENERGYDRAIN,		ssNECROMANCY,     "Energy Drain", "Energy Drain" },
  { spENERVATION,		ssNECROMANCY,     "Enervation", "Enervation" },
  { spENLARGEPERSON,		ssTRANSMUTATION,     "Enlarge Person", "Enlarge Person" },
  { spENLARGEPERSONMASS,		ssTRANSMUTATION,     "Mass Enlarge Person", "Enlarge Person (Mass)" },
  { spENTANGLE,		ssTRANSMUTATION,     "Entangle", "Entangle" },
  { spENTHRALL,		ssENCHANTMENT,     "Enthrall", "Enthrall" },
  { spENTROPICSHIELD,		ssABJURATION,     "Entropic Shield", "Entropic Shield" },
  { spERASE,		ssTRANSMUTATION,     "Erase", "Erase" },
  { spETHEREALJAUNT,		ssTRANSMUTATION,     "Ethereal Jaunt", "Ethereal Jaunt" },
  { spETHEREALNESS,		ssTRANSMUTATION,     "Etherealness", "Etherealness" },
  { spEXPEDITIOUSRETREAT,		ssTRANSMUTATION,     "Expeditious Retreat", "Expeditious Retreat" },
  { spEXPLOSIVERUNES,		ssABJURATION,     "Explosive Runes", "Explosive Runes" },
  { spEYEBITE,		ssNECROMANCY,     "Eyebite", "Eyebite" },
  { spFABRICATE,		ssTRANSMUTATION,     "Fabricate", "Fabricate" },
  { spFAERIEFIRE,		ssEVOCATION,     "Faerie Fire", "Faerie Fire" },
  { spFALSELIFE,		ssNECROMANCY,     "False Life", "False Life" },
  { spFALSEVISION,		ssILLUSION,     "False Vision", "False Vision" },
  { spFEAR,		ssNECROMANCY,     "Fear", "Fear" },
  { spFEATHERFALL,		ssTRANSMUTATION,     "Feather Fall", "Feather Fall" },
  { spFEEBLEMIND,		ssENCHANTMENT,     "Feeblemind", "Feeblemind" },
  { spFINDTHEPATH,		ssDIVINATION,     "Find the Path", "Find the Path" },
  { spFINDTRAPS,		ssDIVINATION,     "Find Traps", "Find Traps" },
  { spFINGEROFDEATH,		ssNECROMANCY,     "Finger of Death", "Finger of Death" },
  { spFIRESEEDS,		ssCONJURATION,     "Fire Seeds", "Fire Seeds" },
  { spFIRESHIELD,		ssEVOCATION,     "Fire Shield", "Fire Shield" },
  { spFIRESTORM,		ssEVOCATION,     "Fire Storm", "Fire Storm" },
  { spFIRETRAP,		ssABJURATION,     "Fire Trap", "Fire Trap" },
  { spFIREBALL,		ssEVOCATION,     "Fireball", "Fireball" },
  { spFLAMEARROW,		ssTRANSMUTATION,     "Flame Arrow", "Flame Arrow" },
  { spFLAMEBLADE,		ssEVOCATION,     "Flame Blade", "Flame Blade" },
  { spFLAMESTRIKE,		ssEVOCATION,     "Flame Strike", "Flame Strike" },
  { spFLAMINGSPHERE,		ssEVOCATION,     "Flaming Sphere", "Flaming Sphere" },
  { spFLARE,		ssEVOCATION,     "Flare", "Flare" },
  { spFLESHTOSTONE,		ssTRANSMUTATION,     "Flesh to Stone", "Flesh to Stone" },
  { spFLOATINGDISK,		ssEVOCATION,     "Floating Disk", "Floating Disk" },
  { spFLY,		ssTRANSMUTATION,     "Fly", "Fly" },
  { spFOGCLOUD,		ssCONJURATION,     "Fog Cloud", "Fog Cloud" },
  { spFORBIDDANCE,		ssABJURATION,     "Forbiddance", "Forbiddance" },
  { spFORCECAGE,		ssEVOCATION,     "Forcecage", "Forcecage" },
  { spFORCEFULHAND,		ssEVOCATION,     "Forceful Hand", "Forceful Hand" },
  { spFORESIGHT,		ssDIVINATION,     "Foresight", "Foresight" },
  { spFOXSCUNNING,		ssTRANSMUTATION,     "Fox's Cunning", "Fox's Cunning" },
  { spFOXSCUNNINGMASS,		ssTRANSMUTATION,     "Mass Fox's Cunning", "Fox's Cunning (Mass)" },
  { spFREEDOM,		ssABJURATION,     "Freedom", "Freedom" },
  { spFREEDOMOFMOVEMENT,		ssABJURATION,     "Freedom of Movement", "Freedom of Movement" },
  { spFREEZINGSPHERE,		ssEVOCATION,     "Freezing Sphere", "Freezing Sphere" },
  { spGASEOUSFORM,		ssTRANSMUTATION,     "Gaseous Form", "Gaseous Form" },
  { spGATE,		ssCONJURATION,     "Gate", "Gate" },
  { spGEASLESSER,		ssENCHANTMENT,     "Lesser Geas", "Geas (Lesser)" },
  { spGEASQUEST,		ssENCHANTMENT,     "Geas/Quest", "Geas/Quest" },
  { spGENTLEREPOSE,		ssNECROMANCY,     "Gentle Repose", "Gentle Repose" },
  { spGHOSTSOUND,		ssILLUSION,     "Ghost Sound", "Ghost Sound" },
  { spGHOULTOUCH,		ssNECROMANCY,     "Ghoul Touch", "Ghoul Touch" },
  { spGIANTVERMIN,		ssTRANSMUTATION,     "Giant Vermin", "Giant Vermin" },
  { spGLIBNESS,		ssTRANSMUTATION,     "Glibness", "Glibness" },
  { spGLITTERDUST,		ssCONJURATION,     "Glitterdust", "Glitterdust" },
  { spGLOBEOFINVULNERABILITY,		ssABJURATION,     "Globe of Invulnerability", "Globe of Invulnerability" },
  { spGLOBEOFINVULNERABILITYLESSER,		ssABJURATION,     "Lesser Globe of Invulnerability", "Globe of Invulnerability (Lesser)" },
  { spGLYPHOFWARDING,		ssABJURATION,     "Glyph of Warding", "Glyph of Warding" },
  { spGLYPHOFWARDINGGREATER,		ssABJURATION,     "Greater Glyph of Warding", "Glyph of Warding (Greater)" },
  { spGOODHOPE,		ssENCHANTMENT,     "Good Hope", "Good Hope" },
  { spGOODBERRY,		ssTRANSMUTATION,     "Goodberry", "Goodberry" },
  { spGRASPINGHAND,		ssEVOCATION,     "Grasping Hand", "Grasping Hand" },
  { spGREASE,		ssCONJURATION,     "Grease", "Grease" },
  { spGUARDSANDWARDS,		ssABJURATION,     "Guards and Wards", "Guards and Wards" },
  { spGUIDANCE,		ssDIVINATION,     "Guidance", "Guidance" },
  { spGUSTOFWIND,		ssEVOCATION,     "Gust of Wind", "Gust of Wind" },
  { spHALLOW,		ssEVOCATION,     "Hallow", "Hallow" },
  { spHALLUCINATORYTERRAIN,		ssILLUSION,     "Hallucinatory Terrain", "Hallucinatory Terrain" },
  { spHALTUNDEAD,		ssNECROMANCY,     "Halt Undead", "Halt Undead" },
  { spHARM,		ssNECROMANCY,     "Harm", "Harm" },
  { spHASTE,		ssTRANSMUTATION,     "Haste", "Haste" },
  { spHEAL,		ssCONJURATION,     "Heal", "Heal" },
  { spHEALMOUNT,		ssCONJURATION,     "Heal Mount", "Heal Mount" },
  { spHEALMASS,		ssCONJURATION,     "Mass Heal", "Heal (Mass)" },
  { spHEATMETAL,		ssTRANSMUTATION,     "Heat Metal", "Heat Metal" },
  { spHELPINGHAND,		ssEVOCATION,     "Helping Hand", "Helping Hand" },
  { spHEROESFEAST,		ssCONJURATION,     "Heroes' Feast", "Heroes' Feast" },
  { spHEROISM,		ssENCHANTMENT,     "Heroism", "Heroism" },
  { spHEROISMGREATER,		ssENCHANTMENT,     "Greater Heroism", "Heroism (Greater)" },
  { spHIDEFROMANIMALS,		ssABJURATION,     "Hide from Animals", "Hide from Animals" },
  { spHIDEFROMUNDEAD,		ssABJURATION,     "Hide from Undead", "Hide from Undead" },
  { spHIDEOUSLAUGHTER,		ssENCHANTMENT,     "Hideous Laughter", "Hideous Laughter" },
  { spHOLDANIMAL,		ssENCHANTMENT,     "Hold Animal", "Hold Animal" },
  { spHOLDMONSTER,		ssENCHANTMENT,     "Hold Monster", "Hold Monster" },
  { spHOLDMONSTERMASS,		ssENCHANTMENT,     "Mass Hold Monster", "Hold Monster (Mass)" },
  { spHOLDPERSON,		ssENCHANTMENT,     "Hold Person", "Hold Person" },
  { spHOLDPERSONMASS,		ssENCHANTMENT,     "Mass Hold Person", "Hold Person (Mass)" },
  { spHOLDPORTAL,		ssABJURATION,     "Hold Portal", "Hold Portal" },
  { spHOLYAURA,		ssABJURATION,     "Holy Aura", "Holy Aura" },
  { spHOLYSMITE,		ssEVOCATION,     "Holy Smite", "Holy Smite" },
  { spHOLYSWORD,		ssEVOCATION,     "Holy Sword", "Holy Sword" },
  { spHOLYWORD,		ssEVOCATION,     "Holy Word", "Holy Word" },
  { spHORRIDWILTING,		ssNECROMANCY,     "Horrid Wilting", "Horrid Wilting" },
  { spHYPNOTICPATTERN,		ssILLUSION,     "Hypnotic Pattern", "Hypnotic Pattern" },
  { spHYPNOTISM,		ssENCHANTMENT,     "Hypnotism", "Hypnotism" },
  { spICESTORM,		ssEVOCATION,     "Ice Storm", "Ice Storm" },
  { spIDENTIFY,		ssDIVINATION,     "Identify", "Identify" },
  { spILLUSORYSCRIPT,		ssILLUSION,     "Illusory Script", "Illusory Script" },
  { spILLUSORYWALL,		ssILLUSION,     "Illusory Wall", "Illusory Wall" },
  { spIMBUEWITHSPELLABILITY,		ssEVOCATION,     "Imbue with Spell Ability", "Imbue with Spell Ability" },
  { spIMPLOSION,		ssEVOCATION,     "Implosion", "Implosion" },
  { spIMPRISONMENT,		ssABJURATION,     "Imprisonment", "Imprisonment" },
  { spINCENDIARYCLOUD,		ssCONJURATION,     "Incendiary Cloud", "Incendiary Cloud" },
  { spINFLICTCRITICALWOUNDS,		ssNECROMANCY,     "Inflict Critical Wounds", "Inflict Critical Wounds" },
  { spINFLICTCRITICALWOUNDSMASS,		ssNECROMANCY,     "Mass Inflict Critical Wounds", "Inflict Critical Wounds (Mass)" },
  { spINFLICTLIGHTWOUNDS,		ssNECROMANCY,     "Inflict Light Wounds", "Inflict Light Wounds" },
  { spINFLICTLIGHTWOUNDSMASS,		ssNECROMANCY,     "Mass Inflict Light Wounds", "Inflict Light Wounds (Mass)" },
  { spINFLICTMINORWOUNDS,		ssNECROMANCY,     "Inflict Minor Wounds", "Inflict Minor Wounds" },
  { spINFLICTMODERATEWOUNDS,		ssNECROMANCY,     "Inflict Moderate Wounds", "Inflict Moderate Wounds" },
  { spINFLICTMODERATEWOUNDSMASS,		ssNECROMANCY,     "Mass Inflict Moderate Wounds", "Inflict Moderate Wounds (Mass)" },
  { spINFLICTSERIOUSWOUNDS,		ssNECROMANCY,     "Inflict Serious Wounds", "Inflict Serious Wounds" },
  { spINFLICTSERIOUSWOUNDSMASS,		ssNECROMANCY,     "Mass Inflict Serious Wounds", "Inflict Serious Wounds (Mass)" },
  { spINSANITY,		ssENCHANTMENT,     "Insanity", "Insanity" },
  { spINSECTPLAGUE,		ssCONJURATION,     "Insect Plague", "Insect Plague" },
  { spINSTANTSUMMONS,		ssCONJURATION,     "Instant Summons", "Instant Summons" },
  { spINTERPOSINGHAND,		ssEVOCATION,     "Interposing Hand", "Interposing Hand" },
  { spINVISIBILITY,		ssILLUSION,     "Invisibility", "Invisibility" },
  { spINVISIBILITYPURGE,		ssEVOCATION,     "Invisibility Purge", "Invisibility Purge" },
  { spINVISIBILITYSPHERE,		ssILLUSION,     "Invisibility Sphere", "Invisibility Sphere" },
  { spINVISIBILITYGREATER,		ssILLUSION,     "Greater Invisibility", "Invisibility (Greater)" },
  { spINVISIBILITYMASS,		ssILLUSION,     "Mass Invisibility", "Invisibility (Mass)" },
  { spIRONBODY,		ssTRANSMUTATION,     "Iron Body", "Iron Body" },
  { spIRONWOOD,		ssTRANSMUTATION,     "Ironwood", "Ironwood" },
  { spIRRESISTIBLEDANCE,		ssENCHANTMENT,     "Irresistible Dance", "Irresistible Dance" },
  { spJUMP,		ssTRANSMUTATION,     "Jump", "Jump" },
  { spKEENEDGE,		ssTRANSMUTATION,     "Keen Edge", "Keen Edge" },
  { spKNOCK,		ssTRANSMUTATION,     "Knock", "Knock" },
  { spKNOWDIRECTION,		ssDIVINATION,     "Know Direction", "Know Direction" },
  { spLEGENDLORE,		ssDIVINATION,     "Legend Lore", "Legend Lore" },
  { spLEVITATE,		ssTRANSMUTATION,     "Levitate", "Levitate" },
  { spLIGHT,		ssEVOCATION,     "Light", "Light" },
  { spLIGHTNINGBOLT,		ssEVOCATION,     "Lightning Bolt", "Lightning Bolt" },
  { spLIMITEDWISH,		ssUNIVERSAL,     "Limited Wish", "Limited Wish" },
  { spLIVEOAK,		ssTRANSMUTATION,     "Liveoak", "Liveoak" },
  { spLOCATECREATURE,		ssDIVINATION,     "Locate Creature", "Locate Creature" },
  { spLOCATEOBJECT,		ssDIVINATION,     "Locate Object", "Locate Object" },
  { spLONGSTRIDER,		ssTRANSMUTATION,     "Longstrider", "Longstrider" },
  { spLULLABY,		ssENCHANTMENT,     "Lullaby", "Lullaby" },
  { spMAGEARMOR,		ssCONJURATION,     "Mage Armor", "Mage Armor" },
  { spMAGEHAND,		ssTRANSMUTATION,     "Mage Hand", "Mage Hand" },
  { spMAGESDISJUNCTION,		ssABJURATION,     "Mage's Disjunction", "Mage's Disjunction" },
  { spMAGESFAITHFULHOUND,		ssCONJURATION,     "Mage's Faithful Hound", "Mage's Faithful Hound" },
  { spMAGESLUCUBRATION,		ssTRANSMUTATION,     "Mage's Lucubration", "Mage's Lucubration" },
  { spMAGESMAGNIFICENTMANSION,		ssCONJURATION,     "Mage's Magnificent Mansion", "Mage's Magnificent Mansion" },
  { spMAGESPRIVATESANCTUM,		ssABJURATION,     "Mage's Private Sanctum", "Mage's Private Sanctum" },
  { spMAGESSWORD,		ssEVOCATION,     "Mage's Sword", "Mage's Sword" },
  { spMAGICAURA,		ssILLUSION,     "Magic Aura", "Magic Aura" },
  { spMAGICCIRCLEAGAINSTCHAOS,		ssABJURATION,     "Magic Circle against Chaos", "Magic Circle against Chaos" },
  { spMAGICCIRCLEAGAINSTEVIL,		ssABJURATION,     "Magic Circle against Evil", "Magic Circle against Evil" },
  { spMAGICCIRCLEAGAINSTGOOD,		ssABJURATION,     "Magic Circle against Good", "Magic Circle against Good" },
  { spMAGICCIRCLEAGAINSTLAW,		ssABJURATION,     "Magic Circle against Law", "Magic Circle against Law" },
  { spMAGICFANG,		ssTRANSMUTATION,     "Magic Fang", "Magic Fang" },
  { spMAGICFANGGREATER,		ssTRANSMUTATION,     "Greater Magic Fang", "Magic Fang (Greater)" },
  { spMAGICJAR,		ssNECROMANCY,     "Magic Jar", "Magic Jar" },
  { spMAGICMISSILE,		ssEVOCATION,     "Magic Missile", "Magic Missile" },
  { spMAGICMOUTH,		ssILLUSION,     "Magic Mouth", "Magic Mouth" },
  { spMAGICSTONE,		ssTRANSMUTATION,     "Magic Stone", "Magic Stone" },
  { spMAGICVESTMENT,		ssTRANSMUTATION,     "Magic Vestment", "Magic Vestment" },
  { spMAGICWEAPON,		ssTRANSMUTATION,     "Magic Weapon", "Magic Weapon" },
  { spMAGICWEAPONGREATER,		ssTRANSMUTATION,     "Greater Magic Weapon", "Magic Weapon (Greater)" },
  { spMAJORCREATION,		ssCONJURATION,     "Major Creation", "Major Creation" },
  { spMAJORIMAGE,		ssILLUSION,     "Major Image", "Major Image" },
  { spMAKEWHOLE,		ssTRANSMUTATION,     "Make Whole", "Make Whole" },
  { spMARKOFJUSTICE,		ssNECROMANCY,     "Mark of Justice", "Mark of Justice" },
  { spMAZE,		ssCONJURATION,     "Maze", "Maze" },
  { spMELDINTOSTONE,		ssTRANSMUTATION,     "Meld into Stone", "Meld into Stone" },
  { spMENDING,		ssTRANSMUTATION,     "Mending", "Mending" },
  { spMESSAGE,		ssTRANSMUTATION,     "Message", "Message" },
  { spMETEORSWARM,		ssEVOCATION,     "Meteor Swarm", "Meteor Swarm" },
  { spMINDBLANK,		ssABJURATION,     "Mind Blank", "Mind Blank" },
  { spMINDFOG,		ssENCHANTMENT,     "Mind Fog", "Mind Fog" },
  { spMINORCREATION,		ssCONJURATION,     "Minor Creation", "Minor Creation" },
  { spMINORIMAGE,		ssILLUSION,     "Minor Image", "Minor Image" },
  { spMIRACLE,		ssEVOCATION,     "Miracle", "Miracle" },
  { spMIRAGEARCANA,		ssILLUSION,     "Mirage Arcana", "Mirage Arcana" },
  { spMIRRORIMAGE,		ssILLUSION,     "Mirror Image", "Mirror Image" },
  { spMISDIRECTION,		ssILLUSION,     "Misdirection", "Misdirection" },
  { spMISLEAD,		ssILLUSION,     "Mislead", "Mislead" },
  { spMNEMONICENHANCER,		ssTRANSMUTATION,     "Mnemonic Enhancer", "Mnemonic Enhancer" },
  { spMODIFYMEMORY,		ssENCHANTMENT,     "Modify Memory", "Modify Memory" },
  { spMOMENTOFPRESCIENCE,		ssDIVINATION,     "Moment of Prescience", "Moment of Prescience" },
  { spMOUNT,		ssCONJURATION,     "Mount", "Mount" },
  { spMOVEEARTH,		ssTRANSMUTATION,     "Move Earth", "Move Earth" },
  { spNEUTRALIZEPOISON,		ssCONJURATION,     "Neutralize Poison", "Neutralize Poison" },
  { spNIGHTMARE,		ssILLUSION,     "Nightmare", "Nightmare" },
  { spNONDETECTION,		ssABJURATION,     "Nondetection", "Nondetection" },
  { spOBSCUREOBJECT,		ssABJURATION,     "Obscure Object", "Obscure Object" },
  { spOBSCURINGMIST,		ssCONJURATION,     "Obscuring Mist", "Obscuring Mist" },
  { spOPENCLOSE,		ssTRANSMUTATION,     "Open/Close", "Open/Close" },
  { spORDERSWRATH,		ssEVOCATION,     "Order's Wrath", "Order's Wrath" },
  { spOVERLANDFLIGHT,		ssTRANSMUTATION,     "Overland Flight", "Overland Flight" },
  { spOWLSWISDOM,		ssTRANSMUTATION,     "Owl's Wisdom", "Owl's Wisdom" },
  { spOWLSWISDOMMASS,		ssTRANSMUTATION,     "Mass Owl's Wisdom", "Owl's Wisdom (Mass)" },
  { spPASSWITHOUTTRACE,		ssTRANSMUTATION,     "Pass without Trace", "Pass without Trace" },
  { spPASSWALL,		ssTRANSMUTATION,     "Passwall", "Passwall" },
  { spPERMANENCY,		ssUNIVERSAL,     "Permanency", "Permanency" },
  { spPERMANENTIMAGE,		ssILLUSION,     "Permanent Image", "Permanent Image" },
  { spPERSISTENTIMAGE,		ssILLUSION,     "Persistent Image", "Persistent Image" },
  { spPHANTASMALKILLER,		ssILLUSION,     "Phantasmal Killer", "Phantasmal Killer" },
  { spPHANTOMSTEED,		ssCONJURATION,     "Phantom Steed", "Phantom Steed" },
  { spPHANTOMTRAP,		ssILLUSION,     "Phantom Trap", "Phantom Trap" },
  { spPHASEDOOR,		ssCONJURATION,     "Phase Door", "Phase Door" },
  { spPLANARALLY,		ssCONJURATION,     "Planar Ally", "Planar Ally" },
  { spPLANARALLYGREATER,		ssCONJURATION,     "Greater Planar Ally", "Planar Ally (Greater)" },
  { spPLANARALLYLESSER,		ssCONJURATION,     "Lesser Planar Ally", "Planar Ally (Lesser)" },
  { spPLANARBINDING,		ssCONJURATION,     "Planar Binding", "Planar Binding" },
  { spPLANARBINDINGGREATER,		ssCONJURATION,     "Greater Planar Binding", "Planar Binding (Greater)" },
  { spPLANARBINDINGLESSER,		ssCONJURATION,     "Lesser Planar Binding", "Planar Binding (Lesser)" },
  { spPLANESHIFT,		ssCONJURATION,     "Plane Shift", "Plane Shift" },
  { spPLANTGROWTH,		ssTRANSMUTATION,     "Plant Growth", "Plant Growth" },
  { spPOISON,		ssNECROMANCY,     "Poison", "Poison" },
  { spPOLARRAY,		ssEVOCATION,     "Polar Ray", "Polar Ray" },
  { spPOLYMORPH,		ssTRANSMUTATION,     "Polymorph", "Polymorph" },
  { spPOLYMORPHANYOBJECT,		ssTRANSMUTATION,     "Polymorph Any Object", "Polymorph Any Object" },
  { spPOWERWORDBLIND,		ssENCHANTMENT,     "Power Word Blind", "Power Word Blind" },
  { spPOWERWORDKILL,		ssENCHANTMENT,     "Power Word Kill", "Power Word Kill" },
  { spPOWERWORDSTUN,		ssENCHANTMENT,     "Power Word Stun", "Power Word Stun" },
  { spPRAYER,		ssENCHANTMENT,     "Prayer", "Prayer" },
  { spPRESTIDIGITATION,		ssUNIVERSAL,     "Prestidigitation", "Prestidigitation" },
  { spPRISMATICSPHERE,		ssABJURATION,     "Prismatic Sphere", "Prismatic Sphere" },
  { spPRISMATICSPRAY,		ssEVOCATION,     "Prismatic Spray", "Prismatic Spray" },
  { spPRISMATICWALL,		ssABJURATION,     "Prismatic Wall", "Prismatic Wall" },
  { spPRODUCEFLAME,		ssEVOCATION,     "Produce Flame", "Produce Flame" },
  { spPROGRAMMEDIMAGE,		ssILLUSION,     "Programmed Image", "Programmed Image" },
  { spPROJECTIMAGE,		ssILLUSION,     "Project Image", "Project Image" },
  { spPROTECTIONFROMARROWS,		ssABJURATION,     "Protection from Arrows", "Protection from Arrows" },
  { spPROTECTIONFROMCHAOS,		ssABJURATION,     "Protection from Chaos", "Protection from Chaos" },
  { spPROTECTIONFROMENERGY,		ssABJURATION,     "Protection from Energy", "Protection from Energy" },
  { spPROTECTIONFROMEVIL,		ssABJURATION,     "Protection from Evil", "Protection from Evil" },
  { spPROTECTIONFROMGOOD,		ssABJURATION,     "Protection from Good", "Protection from Good" },
  { spPROTECTIONFROMLAW,		ssABJURATION,     "Protection from Law", "Protection from Law" },
  { spPROTECTIONFROMSPELLS,		ssABJURATION,     "Protection from Spells", "Protection from Spells" },
  { spPRYINGEYES,		ssDIVINATION,     "Prying Eyes", "Prying Eyes" },
  { spPRYINGEYESGREATER,		ssDIVINATION,     "Greater Prying Eyes", "Prying Eyes (Greater)" },
  { spPURIFYFOODANDDRINK,		ssTRANSMUTATION,     "Purify Food and Drink", "Purify Food and Drink" },
  { spPYROTECHNICS,		ssTRANSMUTATION,     "Pyrotechnics", "Pyrotechnics" },
  { spQUENCH,		ssTRANSMUTATION,     "Quench", "Quench" },
  { spRAGE,		ssENCHANTMENT,     "Rage", "Rage" },
  { spRAINBOWPATTERN,		ssILLUSION,     "Rainbow Pattern", "Rainbow Pattern" },
  { spRAISEDEAD,		ssCONJURATION,     "Raise Dead", "Raise Dead" },
  { spRAYOFENFEEBLEMENT,		ssNECROMANCY,     "Ray of Enfeeblement", "Ray of Enfeeblement" },
  { spRAYOFEXHAUSTION,		ssNECROMANCY,     "Ray of Exhaustion", "Ray of Exhaustion" },
  { spRAYOFFROST,		ssEVOCATION,     "Ray of Frost", "Ray of Frost" },
  { spREADMAGIC,		ssDIVINATION,     "Read Magic", "Read Magic" },
  { spREDUCEANIMAL,		ssTRANSMUTATION,     "Reduce Animal", "Reduce Animal" },
  { spREDUCEPERSON,		ssTRANSMUTATION,     "Reduce Person", "Reduce Person" },
  { spREDUCEPERSONMASS,		ssTRANSMUTATION,     "Mass Reduce Person", "Reduce Person (Mass)" },
  { spREFUGE,		ssCONJURATION,     "Refuge", "Refuge" },
  { spREGENERATE,		ssCONJURATION,     "Regenerate", "Regenerate" },
  { spREINCARNATE,		ssTRANSMUTATION,     "Reincarnate", "Reincarnate" },
  { spREMOVEBLINDNESSDEAFNESS,		ssCONJURATION,     "Remove Blindness/Deafness", "Remove Blindness/Deafness" },
  { spREMOVECURSE,		ssABJURATION,     "Remove Curse", "Remove Curse" },
  { spREMOVEDISEASE,		ssCONJURATION,     "Remove Disease", "Remove Disease" },
  { spREMOVEFEAR,		ssABJURATION,     "Remove Fear", "Remove Fear" },
  { spREMOVEPARALYSIS,		ssCONJURATION,     "Remove Paralysis", "Remove Paralysis" },
  { spREPELMETALORSTONE,		ssABJURATION,     "Repel Metal or Stone", "Repel Metal or Stone" },
  { spREPELVERMIN,		ssABJURATION,     "Repel Vermin", "Repel Vermin" },
  { spREPELWOOD,		ssTRANSMUTATION,     "Repel Wood", "Repel Wood" },
  { spREPULSION,		ssABJURATION,     "Repulsion", "Repulsion" },
  { spRESILIENTSPHERE,		ssEVOCATION,     "Resilient Sphere", "Resilient Sphere" },
  { spRESISTENERGY,		ssABJURATION,     "Resist Energy", "Resist Energy" },
  { spRESISTANCE,		ssABJURATION,     "Resistance", "Resistance" },
  { spRESTORATION,		ssCONJURATION,     "Restoration", "Restoration" },
  { spRESTORATIONGREATER,		ssCONJURATION,     "Greater Restoration", "Restoration (Greater)" },
  { spRESTORATIONLESSER,		ssCONJURATION,     "Lesser Restoration", "Restoration (Lesser)" },
  { spRESURRECTION,		ssCONJURATION,     "Resurrection", "Resurrection" },
  { spREVERSEGRAVITY,		ssTRANSMUTATION,     "Reverse Gravity", "Reverse Gravity" },
  { spRIGHTEOUSMIGHT,		ssTRANSMUTATION,     "Righteous Might", "Righteous Might" },
  { spROPETRICK,		ssTRANSMUTATION,     "Rope Trick", "Rope Trick" },
  { spRUSTINGGRASP,		ssTRANSMUTATION,     "Rusting Grasp", "Rusting Grasp" },
  { spSANCTUARY,		ssABJURATION,     "Sanctuary", "Sanctuary" },
  { spSCARE,		ssNECROMANCY,     "Scare", "Scare" },
  { spSCINTILLATINGPATTERN,		ssILLUSION,     "Scintillating Pattern", "Scintillating Pattern" },
  { spSCORCHINGRAY,		ssEVOCATION,     "Scorching Ray", "Scorching Ray" },
  { spSCREEN,		ssILLUSION,     "Screen", "Screen" },
  { spSCRYING,		ssDIVINATION,     "Scrying", "Scrying" },
  { spSCRYINGGREATER,		ssDIVINATION,     "Greater Scrying", "Scrying (Greater)" },
  { spSCULPTSOUND,		ssTRANSMUTATION,     "Sculpt Sound", "Sculpt Sound" },
  { spSEARINGLIGHT,		ssEVOCATION,     "Searing Light", "Searing Light" },
  { spSECRETCHEST,		ssCONJURATION,     "Secret Chest", "Secret Chest" },
  { spSECRETPAGE,		ssTRANSMUTATION,     "Secret Page", "Secret Page" },
  { spSECURESHELTER,		ssCONJURATION,     "Secure Shelter", "Secure Shelter" },
  { spSEEINVISIBILITY,		ssDIVINATION,     "See Invisibility", "See Invisibility" },
  { spSEEMING,		ssILLUSION,     "Seeming", "Seeming" },
  { spSENDING,		ssEVOCATION,     "Sending", "Sending" },
  { spSEPIASNAKESIGIL,		ssCONJURATION,     "Sepia Snake Sigil", "Sepia Snake Sigil" },
  { spSEQUESTER,		ssABJURATION,     "Sequester", "Sequester" },
  { spSHADES,		ssILLUSION,     "Shades", "Shades" },
  { spSHADOWCONJURATION,		ssILLUSION,     "Shadow Conjuration", "Shadow Conjuration" },
  { spSHADOWCONJURATIONGREATER,		ssILLUSION,     "Greater Shadow Conjuration", "Shadow Conjuration (Greater)" },
  { spSHADOWEVOCATION,		ssILLUSION,     "Shadow Evocation", "Shadow Evocation" },
  { spSHADOWEVOCATIONGREATER,		ssILLUSION,     "Greater Shadow Evocation", "Shadow Evocation (Greater)" },
  { spSHADOWWALK,		ssILLUSION,     "Shadow Walk", "Shadow Walk" },
  { spSHAMBLER,		ssCONJURATION,     "Shambler", "Shambler" },
  { spSHAPECHANGE,		ssTRANSMUTATION,     "Shapechange", "Shapechange" },
  { spSHATTER,		ssEVOCATION,     "Shatter", "Shatter" },
  { spSHIELD,		ssABJURATION,     "Shield", "Shield" },
  { spSHIELDOFFAITH,		ssABJURATION,     "Shield of Faith", "Shield of Faith" },
  { spSHIELDOFLAW,		ssABJURATION,     "Shield of Law", "Shield of Law" },
  { spSHIELDOTHER,		ssABJURATION,     "Shield Other", "Shield Other" },
  { spSHILLELAGH,		ssTRANSMUTATION,     "Shillelagh", "Shillelagh" },
  { spSHOCKINGGRASP,		ssEVOCATION,     "Shocking Grasp", "Shocking Grasp" },
  { spSHOUT,		ssEVOCATION,     "Shout", "Shout" },
  { spSHOUTGREATER,		ssEVOCATION,     "Greater Shout", "Shout (Greater)" },
  { spSHRINKITEM,		ssTRANSMUTATION,     "Shrink Item", "Shrink Item" },
  { spSILENCE,		ssILLUSION,     "Silence", "Silence" },
  { spSILENTIMAGE,		ssILLUSION,     "Silent Image", "Silent Image" },
  { spSIMULACRUM,		ssILLUSION,     "Simulacrum", "Simulacrum" },
  { spSLAYLIVING,		ssNECROMANCY,     "Slay Living", "Slay Living" },
  { spSLEEP,		ssENCHANTMENT,     "Sleep", "Sleep" },
  { spSLEETSTORM,		ssCONJURATION,     "Sleet Storm", "Sleet Storm" },
  { spSLOW,		ssTRANSMUTATION,     "Slow", "Slow" },
  { spSNARE,		ssTRANSMUTATION,     "Snare", "Snare" },
  { spSOFTENEARTHANDSTONE,		ssTRANSMUTATION,     "Soften Earth and Stone", "Soften Earth and Stone" },
  { spSOLIDFOG,		ssCONJURATION,     "Solid Fog", "Solid Fog" },
  { spSONGOFDISCORD,		ssENCHANTMENT,     "Song of Discord", "Song of Discord" },
  { spSOULBIND,		ssNECROMANCY,     "Soul Bind", "Soul Bind" },
  { spSOUNDBURST,		ssEVOCATION,     "Sound Burst", "Sound Burst" },
  { spSPEAKWITHANIMALS,		ssDIVINATION,     "Speak with Animals", "Speak with Animals" },
  { spSPEAKWITHDEAD,		ssNECROMANCY,     "Speak with Dead", "Speak with Dead" },
  { spSPEAKWITHPLANTS,		ssDIVINATION,     "Speak with Plants", "Speak with Plants" },
  { spSPECTRALHAND,		ssNECROMANCY,     "Spectral Hand", "Spectral Hand" },
  { spSPELLIMMUNITY,		ssABJURATION,     "Spell Immunity", "Spell Immunity" },
  { spSPELLIMMUNITYGREATER,		ssABJURATION,     "Greater Spell Immunity", "Spell Immunity (Greater)" },
  { spSPELLRESISTANCE,		ssABJURATION,     "Spell Resistance", "Spell Resistance" },
  { spSPELLTURNING,		ssABJURATION,     "Spell Turning", "Spell Turning" },
  { spSPELLSTAFF,		ssTRANSMUTATION,     "Spellstaff", "Spellstaff" },
  { spSPIDERCLIMB,		ssTRANSMUTATION,     "Spider Climb", "Spider Climb" },
  { spSPIKEGROWTH,		ssTRANSMUTATION,     "Spike Growth", "Spike Growth" },
  { spSPIKESTONES,		ssTRANSMUTATION,     "Spike Stones", "Spike Stones" },
  { spSPIRITUALWEAPON,		ssEVOCATION,     "Spiritual Weapon", "Spiritual Weapon" },
  { spSTATUE,		ssTRANSMUTATION,     "Statue", "Statue" },
  { spSTATUS,		ssDIVINATION,     "Status", "Status" },
  { spSTINKINGCLOUD,		ssCONJURATION,     "Stinking Cloud", "Stinking Cloud" },
  { spSTONESHAPE,		ssTRANSMUTATION,     "Stone Shape", "Stone Shape" },
  { spSTONETELL,		ssDIVINATION,     "Stone Tell", "Stone Tell" },
  { spSTONETOFLESH,		ssTRANSMUTATION,     "Stone to Flesh", "Stone to Flesh" },
  { spSTONESKIN,		ssABJURATION,     "Stoneskin", "Stoneskin" },
  { spSTORMOFVENGEANCE,		ssCONJURATION,     "Storm of Vengeance", "Storm of Vengeance" },
  { spSUGGESTION,		ssENCHANTMENT,     "Suggestion", "Suggestion" },
  { spSUGGESTIONMASS,		ssENCHANTMENT,     "Mass Suggestion", "Suggestion (Mass)" },
  { spSUMMONINSTRUMENT,		ssCONJURATION,     "Summon Instrument", "Summon Instrument" },
  { spSUMMONMONSTERI,		ssCONJURATION,     "Summon Monster I", "Summon Monster I" },
  { spSUMMONMONSTERII,		ssCONJURATION,     "Summon Monster II", "Summon Monster II" },
  { spSUMMONMONSTERIII,		ssCONJURATION,     "Summon Monster III", "Summon Monster III" },
  { spSUMMONMONSTERIV,		ssCONJURATION,     "Summon Monster IV", "Summon Monster IV" },
  { spSUMMONMONSTERIX,		ssCONJURATION,     "Summon Monster IX", "Summon Monster IX" },
  { spSUMMONMONSTERV,		ssCONJURATION,     "Summon Monster V", "Summon Monster V" },
  { spSUMMONMONSTERVI,		ssCONJURATION,     "Summon Monster VI", "Summon Monster VI" },
  { spSUMMONMONSTERVII,		ssCONJURATION,     "Summon Monster VII", "Summon Monster VII" },
  { spSUMMONMONSTERVIII,		ssCONJURATION,     "Summon Monster VIII", "Summon Monster VIII" },
  { spSUMMONNATURESALLYI,		ssCONJURATION,     "Summon Nature's Ally I", "Summon Nature's Ally I" },
  { spSUMMONNATURESALLYII,		ssCONJURATION,     "Summon Nature's Ally II", "Summon Nature's Ally II" },
  { spSUMMONNATURESALLYIII,		ssCONJURATION,     "Summon Nature's Ally III", "Summon Nature's Ally III" },
  { spSUMMONNATURESALLYIV,		ssCONJURATION,     "Summon Nature's Ally IV", "Summon Nature's Ally IV" },
  { spSUMMONNATURESALLYIX,		ssCONJURATION,     "Summon Nature's Ally IX", "Summon Nature's Ally IX" },
  { spSUMMONNATURESALLYV,		ssCONJURATION,     "Summon Nature's Ally V", "Summon Nature's Ally V" },
  { spSUMMONNATURESALLYVI,		ssCONJURATION,     "Summon Nature's Ally VI", "Summon Nature's Ally VI" },
  { spSUMMONNATURESALLYVII,		ssCONJURATION,     "Summon Nature's Ally VII", "Summon Nature's Ally VII" },
  { spSUMMONNATURESALLYVIII,		ssCONJURATION,     "Summon Nature's Ally VIII", "Summon Nature's Ally VIII" },
  { spSUMMONSWARM,		ssCONJURATION,     "Summon Swarm", "Summon Swarm" },
  { spSUNBEAM,		ssEVOCATION,     "Sunbeam", "Sunbeam" },
  { spSUNBURST,		ssEVOCATION,     "Sunburst", "Sunburst" },
  { spSYMBOLOFDEATH,		ssNECROMANCY,     "Symbol of Death", "Symbol of Death" },
  { spSYMBOLOFFEAR,		ssNECROMANCY,     "Symbol of Fear", "Symbol of Fear" },
  { spSYMBOLOFINSANITY,		ssENCHANTMENT,     "Symbol of Insanity", "Symbol of Insanity" },
  { spSYMBOLOFPAIN,		ssNECROMANCY,     "Symbol of Pain", "Symbol of Pain" },
  { spSYMBOLOFPERSUASION,		ssENCHANTMENT,     "Symbol of Persuasion", "Symbol of Persuasion" },
  { spSYMBOLOFSLEEP,		ssENCHANTMENT,     "Symbol of Sleep", "Symbol of Sleep" },
  { spSYMBOLOFSTUNNING,		ssENCHANTMENT,     "Symbol of Stunning", "Symbol of Stunning" },
  { spSYMBOLOFWEAKNESS,		ssNECROMANCY,     "Symbol of Weakness", "Symbol of Weakness" },
  { spSYMPATHETICVIBRATION,		ssEVOCATION,     "Sympathetic Vibration", "Sympathetic Vibration" },
  { spSYMPATHY,		ssENCHANTMENT,     "Sympathy", "Sympathy" },
  { spTELEKINESIS,		ssTRANSMUTATION,     "Telekinesis", "Telekinesis" },
  { spTELEKINETICSPHERE,		ssEVOCATION,     "Telekinetic Sphere", "Telekinetic Sphere" },
  { spTELEPATHICBOND,		ssDIVINATION,     "Telepathic Bond", "Telepathic Bond" },
  { spTELEPORT,		ssCONJURATION,     "Teleport", "Teleport" },
  { spTELEPORTOBJECT,		ssCONJURATION,     "Teleport Object", "Teleport Object" },
  { spTELEPORTGREATER,		ssCONJURATION,     "Greater Teleport", "Teleport (Greater)" },
  { spTELEPORTATIONCIRCLE,		ssCONJURATION,     "Teleportation Circle", "Teleportation Circle" },
  { spTEMPORALSTASIS,		ssTRANSMUTATION,     "Temporal Stasis", "Temporal Stasis" },
  { spTIMESTOP,		ssTRANSMUTATION,     "Time Stop", "Time Stop" },
  { spTINYHUT,		ssEVOCATION,     "Tiny Hut", "Tiny Hut" },
  { spTONGUES,		ssDIVINATION,     "Tongues", "Tongues" },
  { spTOUCHOFFATIGUE,		ssNECROMANCY,     "Touch of Fatigue", "Touch of Fatigue" },
  { spTOUCHOFIDIOCY,		ssENCHANTMENT,     "Touch of Idiocy", "Touch of Idiocy" },
  { spTRANSFORMATION,		ssTRANSMUTATION,     "Transformation", "Transformation" },
  { spTRANSMUTEMETALTOWOOD,		ssTRANSMUTATION,     "Transmute Metal to Wood", "Transmute Metal to Wood" },
  { spTRANSMUTEMUDTOROCK,		ssTRANSMUTATION,     "Transmute Mud to Rock", "Transmute Mud to Rock" },
  { spTRANSMUTEROCKTOMUD,		ssTRANSMUTATION,     "Transmute Rock to Mud", "Transmute Rock to Mud" },
  { spTRANSPORTVIAPLANTS,		ssTRANSMUTATION,     "Transport via Plants", "Transport via Plants" },
  { spTRAPTHESOUL,		ssCONJURATION,     "Trap the Soul", "Trap the Soul" },
  { spTREESHAPE,		ssTRANSMUTATION,     "Tree Shape", "Tree Shape" },
  { spTREESTRIDE,		ssCONJURATION,     "Tree Stride", "Tree Stride" },
  { spTRUERESURRECTION,		ssCONJURATION,     "True Resurrection", "True Resurrection" },
  { spTRUESEEING,		ssDIVINATION,     "True Seeing", "True Seeing" },
  { spTRUESTRIKE,		ssDIVINATION,     "True Strike", "True Strike" },
  { spUNDEATHTODEATH,		ssNECROMANCY,     "Undeath to Death", "Undeath to Death" },
  { spUNDETECTABLEALIGNMENT,		ssABJURATION,     "Undetectable Alignment", "Undetectable Alignment" },
  { spUNHALLOW,		ssEVOCATION,     "Unhallow", "Unhallow" },
  { spUNHOLYAURA,		ssABJURATION,     "Unholy Aura", "Unholy Aura" },
  { spUNHOLYBLIGHT,		ssEVOCATION,     "Unholy Blight", "Unholy Blight" },
  { spUNSEENSERVANT,		ssCONJURATION,     "Unseen Servant", "Unseen Servant" },
  { spVAMPIRICTOUCH,		ssNECROMANCY,     "Vampiric Touch", "Vampiric Touch" },
  { spVEIL,		ssILLUSION,     "Veil", "Veil" },
  { spVENTRILOQUISM,		ssILLUSION,     "Ventriloquism", "Ventriloquism" },
  { spVIRTUE,		ssTRANSMUTATION,     "Virtue", "Virtue" },
  { spVISION,		ssDIVINATION,     "Vision", "Vision" },
  { spWAILOFTHEBANSHEE,		ssNECROMANCY,     "Wail of the Banshee", "Wail of the Banshee" },
  { spWALLOFFIRE,		ssEVOCATION,     "Wall of Fire", "Wall of Fire" },
  { spWALLOFFORCE,		ssEVOCATION,     "Wall of Force", "Wall of Force" },
  { spWALLOFICE,		ssEVOCATION,     "Wall of Ice", "Wall of Ice" },
  { spWALLOFIRON,		ssCONJURATION,     "Wall of Iron", "Wall of Iron" },
  { spWALLOFSTONE,		ssCONJURATION,     "Wall of Stone", "Wall of Stone" },
  { spWALLOFTHORNS,		ssCONJURATION,     "Wall of Thorns", "Wall of Thorns" },
  { spWARPWOOD,		ssTRANSMUTATION,     "Warp Wood", "Warp Wood" },
  { spWATERBREATHING,		ssTRANSMUTATION,     "Water Breathing", "Water Breathing" },
  { spWATERWALK,		ssTRANSMUTATION,     "Water Walk", "Water Walk" },
  { spWAVESOFEXHAUSTION,		ssNECROMANCY,     "Waves of Exhaustion", "Waves of Exhaustion" },
  { spWAVESOFFATIGUE,		ssNECROMANCY,     "Waves of Fatigue", "Waves of Fatigue" },
  { spWEB,		ssCONJURATION,     "Web", "Web" },
  { spWEIRD,		ssILLUSION,     "Weird", "Weird" },
  { spWHIRLWIND,		ssEVOCATION,     "Whirlwind", "Whirlwind" },
  { spWHISPERINGWIND,		ssTRANSMUTATION,     "Whispering Wind", "Whispering Wind" },
  { spWINDWALK,		ssTRANSMUTATION,     "Wind Walk", "Wind Walk" },
  { spWINDWALL,		ssEVOCATION,     "Wind Wall", "Wind Wall" },
  { spWISH,		ssUNIVERSAL,     "Wish", "Wish" },
  { spWOODSHAPE,		ssTRANSMUTATION,     "Wood Shape", "Wood Shape" },
  { spWORDOFCHAOS,		ssEVOCATION,     "Word of Chaos", "Word of Chaos" },
  { spWORDOFRECALL,		ssCONJURATION,     "Word of Recall", "Word of Recall" },
  { spZONEOFSILENCE,		ssILLUSION,     "Zone of Silence", "Zone of Silence" },
  { spZONEOFTRUTH,		ssENCHANTMENT,     "Zone of Truth", "Zone of Truth" },
  { 0,                                    0,                 0, 0 }
};


static const struct {
  int   id;
  int   forbiddenAlignments;
  char* name;
  SPELLSFORCLASS* spells;
} s_domains[] = {
  { dmAIR,         0,                       "air",         s_Air },
  { dmANIMAL,      0,                       "animal",      s_Animal },
  { dmCHAOS,       alLAWFUL | alLCNEUTRAL,  "chaos",       s_Chaos },
  { dmDEATH,       alGOOD,                  "death",       s_Death },
  { dmDESTRUCTION, alGOOD,                  "destruction", s_Destruction },
  { dmEARTH,       0,                       "earth",       s_Earth },
  { dmEVIL,        alGOOD | alGENEUTRAL,    "evil",        s_Evil },       
  { dmFIRE,        0,                       "fire",        s_Fire },
  { dmGOOD,        alEVIL | alGENEUTRAL,    "good",        s_Good },
  { dmHEALING,     0,                       "healing",     s_Healing },
  { dmKNOWLEDGE,   0,                       "knowledge",   s_Knowledge },
  { dmLAW,         alCHAOTIC | alLCNEUTRAL, "law",         s_Law },
  { dmLUCK,        0,                       "luck",        s_Luck },
  { dmMAGIC,       0,                       "magic",       s_Magic },
  { dmPLANT,       0,                       "plant",       s_Plant },
  { dmPROTECTION,  0,                       "protection",  s_Protection },
  { dmSTRENGTH,    0,                       "strength",    s_Strength },
  { dmSUN,         0,                       "sun",         s_Sun },
  { dmTRAVEL,      0,                       "travel",      s_Travel },
  { dmTRICKERY,    alLAWFUL,                "trickery",    s_Trickery },
  { dmWAR,         0,                       "war",         s_War },
  { dmWATER,       0,                       "water",       s_Water },
  { 0,             0,                       0,             0 }      
};


static int s_npcGearValue[] = { 900, 2000, 2500, 3300, 4300, 5600, 7200,
        9400, 12000, 16000, 21000, 27000, 35000, 45000, 59000, 77000,
        100000, 130000, 170000, 220000 };

static struct {
  int   id;
  char* name;
} s_languages[] = {
  { lnABYSSAL,     "abyssal" },
  { lnAQUAN,       "aquan" },
  { lnAURAN,       "auran" },
  { lnCELESTIAL,   "celestial" },
  { lnCOMMON,      "common" },
  { lnDRACONIC,    "draconic" },
  { lnDRUIDIC,     "druidic" },
  { lnDWARVEN,     "dwarven" },
  { lnELVEN,       "elven" },
  { lnGNOME,       "gnome" },
  { lnGOBLIN,      "goblin" },
  { lnGIANT,       "giant" },
  { lnGNOLL,       "gnoll" },
  { lnHALFLING,    "halfling" },
  { lnIGNAN,       "ignan" },
  { lnINFERNAL,    "infernal" },
  { lnORC,         "orc" },
  { lnSYLVAN,      "sylvan" },
  { lnTERRAN,      "terran" },
  { lnUNDERCOMMON, "undercommon" },
  { 0,             0 }
};

/* ---------------------------------------------------------------------- *
 * Function definitions
 * ---------------------------------------------------------------------- */

static int roundToNearest5( int num ) {
  int mod5;
  
  mod5 = num % 5;
  if( mod5 <= 2 ) {
    return ( num - mod5 );
  }
  
  return ( num - mod5 ) + 5;  
}


char* dndGetClassName( int id ) {
  int i;

  for( i = 0; s_classInfo[ i ].id != 0; i++ ) {
    if( s_classInfo[ i ].id == id ) {
      return s_classInfo[ i ].name;
    }
  }

  return NULL;
}


int dndGetClassHitDie( int id ) {
  int i;

  for( i = 0; s_classInfo[ i ].id != 0; i++ ) {
    if( s_classInfo[ i ].id == id ) {
      return s_classInfo[ i ].hitDie;
    }
  }

  return 0;
}


int dndGetClassType( int id ) {
  int i;

  for( i = 0; s_classInfo[ i ].id != 0; i++ ) {
    if( s_classInfo[ i ].id == id ) {
      return s_classInfo[ i ].type;
    }
  }

  return 0;
}


char* dndGetClassTypeName( int id ) {
  int i;

  for( i = 0; s_classTypeInfo[ i ].id != 0; i++ ) {
    if( s_classTypeInfo[ i ].id == id ) {
      return s_classTypeInfo[ i ].name;
    }
  }

  return NULL;
}


char* dndGetAlignmentText( int alignment ) {
  int i;

  for( i = 0; s_alignmentText[ i ].alignment != 0; i++ ) {
    if( s_alignmentText[ i ].alignment == alignment ) {
      return s_alignmentText[ i ].text;
    }
  }

  return NULL;
}


char* dndGetSkillName( int skill ) {
  int i;

  for( i = 0; s_skills[ i ].name != 0; i++ ) {
    if( s_skills[ i ].type == skill ) {
      return s_skills[ i ].name;
    }
  }
  
  return NULL;
}


int dndGetSkillAbility( int skill ) {
  int i;

  for( i = 0; s_skills[ i ].name != 0; i++ ) {
    if( s_skills[ i ].type == skill ) {
      return s_skills[ i ].ability;
    }
  }
  
  return 0;
}


int dndGetSkillType( int classType, int skill ) {
  int i;
  int j;

  for( i = 0; s_classInfo[ i ].name != 0; i++ ) {
    if( s_classInfo[ i ].id == classType ) {
      for( j = 0; s_classInfo[ i ].skills[ j ].skill != 0; j++ ) {
        if( s_classInfo[ i ].skills[ j ].skill == skill ) {
          if( s_classInfo[ i ].skills[ j ].classSkill ) {
            return sktCLASS;
          } else {
            return sktCROSSCLASS;
          }
        }
      }

      break;
    }
  }

  //return sktEXCLUSIVE;
  return sktCROSSCLASS;
}

int dndIsSkillCraft( int skill ) {
	switch (skill) {
		case skCRAFT_ALCHEMY:
		case skCRAFT_ARMORSMITHING:
		case skCRAFT_BOWMAKING:
		case skCRAFT_BLACKSMITHING:
		case skCRAFT_CARPENTRY:
		case skCRAFT_LEATHERWORKING:
		case skCRAFT_PAINTING:
		case skCRAFT_POTTERY:
		case skCRAFT_SCULPTING:
		case skCRAFT_SHIPMAKING:
		case skCRAFT_STONEMASONRY:
		case skCRAFT_TRAPMAKING:
		case skCRAFT_WEAPONSMITHING:
		case skCRAFT_WOODWORKING:
			return 1;
	}

	return 0;
}

int dndIsSkillKnowledge( int skill ) {
	switch (skill) {
		case skKNOWLEDGE_ARCANA:
		case skKNOWLEDGE_ARCHITECTUREANDENGINEERING:
		case skKNOWLEDGE_DUNGEONEERING:
		case skKNOWLEDGE_GEOGRAPHY:
		case skKNOWLEDGE_HISTORY:
		case skKNOWLEDGE_LOCAL:
		case skKNOWLEDGE_NATURE:
		case skKNOWLEDGE_NOBILITYANDROYALTY:
		case skKNOWLEDGE_RELIGION:
		case skKNOWLEDGE_THEPLANES:
			return 1;
	}

	return 0;
}

int dndIsSkillPerform( int skill ) {
	switch (skill) {
		case skPERFORM_ACT:
		case skPERFORM_COMEDY:
		case skPERFORM_DANCE:
		case skPERFORM_KEYBOARDINSTRUMENTS:
		case skPERFORM_ORATORY:
		case skPERFORM_PERCUSSIONINSTRUMENTS:
		case skPERFORM_STRINGINSTRUMENTS:
		case skPERFORM_WINDINSTRUMENTS:
		case skPERFORM_SING:
			return 1;
	}

	return 0;
}


int dndIsSkillProfession( int skill ) {
	switch (skill) {
		case skPROFESSION_HUNTER:
		case skPROFESSION_MINER:
			return 1;
	}

	return 0;
}

int dndGetSkillBonusForClass( int classType ) {
  int i;

  for( i = 0; s_classInfo[ i ].name != 0; i++ ) {
    if( s_classInfo[ i ].id == classType ) {
      return s_classInfo[ i ].skillCount;
    }
  }
  
  return 0;
}


char* dndGetAbilityName( int ability ) {
  int i;

  for( i = 0; s_abilities[ i ].name != 0; i++ ) {
    if( s_abilities[ i ].ability == ability ) {
      return s_abilities[ i ].name;
    }
  }

  return NULL;
}


int dndGetAbilityBonus( int abilityScore ) {
  int abilityBonus;

  abilityBonus = abilityScore - 10;
  if( abilityBonus < 0 ) {
    abilityBonus--;
  }

  return abilityBonus >> 1;
}


int dndClassHasBonusFeatAtFirstLevel( int id ) {
  int i;

  for( i = 0; s_classInfo[ i ].id != 0; i++ ) {
    if( s_classInfo[ i ].id == id ) {
      return s_classInfo[ i ].bonusFeatAtFirst;
    }
  }

  return 0;
}


int dndClassBonusFeatEveryXLevels( int id ) {
  int i;

  for( i = 0; s_classInfo[ i ].id != 0; i++ ) {
    if( s_classInfo[ i ].id == id ) {
      return s_classInfo[ i ].bonusFeatEveryX;
    }
  }

  return 0;
}


char* dndGetFeatName( int id ) {
  int i;

  for( i = 0; s_feats[ i ].name != 0; i++ ) {
    if( s_feats[ i ].id == id ) {
      return s_feats[ i ].name;
    }
  }

  return NULL;
}

int dndGetFeatType( int id ) {
  int i;

  for( i = 0; s_feats[ i ].name != 0; i++ ) {
    if( s_feats[ i ].id == id ) {
      return s_feats[ i ].type;
    }
  }

  return 0;
}


int dndFeatIsReusable( int id ) {
  int i;

  for( i = 0; s_feats[ i ].name != 0; i++ ) {
    if( s_feats[ i ].id == id ) {
      return s_feats[ i ].multi;
    }
  }

  return 0;
}


int dndGetFeatPrerequisite( int id, int* type, int* data1, int* data2, char** next ) {
  int i;
  FEATPREREQ* fpr = NULL;

  if( id != 0 ) {
    for( i = 0; s_feats[ i ].name != 0; i++ ) {
      if( s_feats[ i ].id == id ) {
        fpr = s_feats[ i ].prereqs;
        break;
      }
    }
    if( fpr == NULL ) {
      return 0;
    }
  } else {
    if( *next == NULL ) {
      return 0;
    }
    fpr = (FEATPREREQ*)(*next);
  }

  *next = NULL;

  if( fpr->preReqType == 0 ) {
    return 0;
  }

  *type = fpr->preReqType;
  *data1 = fpr->data1;
  *data2 = fpr->data2;

  *next = (char*)( fpr + 1 );

  return 1;
}


int dndGetClassAttackBonus( int id, int level ) {
  int i;

  if( ( level < 1 ) || ( level > 20 ) ) {
    return 0;
  }

  for( i = 0; s_classInfo[ i ].id != 0; i++ ) {
    if( s_classInfo[ i ].id == id ) {
      return s_classInfo[ i ].attack[ level-1 ];
    }
  }

  return 0;
}


char* dndGetRaceName( int id ) {
  int i;

  for( i = 0; s_races[ i ].name != 0; i++ ) {
    if( s_races[ i ].id == id ) {
      return s_races[ i ].name;
    }
  }

  return NULL;
}


int dndGetRaceSize( int id ) {
  int i;

  for( i = 0; s_races[ i ].name != 0; i++ ) {
    if( s_races[ i ].id == id ) {
      return s_races[ i ].size;
    }
  }

  return 0;
}


char* dndGetWeaponName( int id ) {
  int i;

  for( i = 0; s_weapons[ i ].name != 0; i++ ) {
    if( s_weapons[ i ].id == id ) {
      return s_weapons[ i ].name;
    }
  }

  return NULL;
}

char* dndGetWeaponPCGenName( int id ) {
  int i;

  for( i = 0; s_weapons[ i ].name != 0; i++ ) {
    if( s_weapons[ i ].id == id ) {
      return s_weapons[ i ].pcgen_name;
    }
  }

  return NULL;
}

int dndGetWeaponSize( int id ) {
  int i;

  for( i = 0; s_weapons[ i ].name != 0; i++ ) {
    if( s_weapons[ i ].id == id ) {
      return s_weapons[ i ].size;
    }
  }

  return 0;
}


int dndGetWeaponType( int id ) {
  int i;

  for( i = 0; s_weapons[ i ].name != 0; i++ ) {
    if( s_weapons[ i ].id == id ) {
      return s_weapons[ i ].type;
    }
  }

  return 0;
}


int dndGetWeaponCost( int id ) {
  int i;

  for( i = 0; s_weapons[ i ].name != 0; i++ ) {
    if( s_weapons[ i ].id == id ) {
      return s_weapons[ i ].cost;
    }
  }

  return 0;
}


char* dndGetSchoolOfMagicName( int id ) {
  int i;

  for( i = 0; s_magicSchools[ i ].name != 0; i++ ) {
    if( s_magicSchools[ i ].id == id ) {
      return s_magicSchools[ i ].name;
    }
  }

  return NULL;
}

char* dndGetSpecialistName( int id ) {
  int i;

  for( i = 0; s_specialistTypeInfo[ i ].name != 0; i++ ) {
    if( s_specialistTypeInfo[ i ].id == id ) {
      return s_specialistTypeInfo[ i ].name;
    }
  }

  return NULL;
}

char* dndGetSizeName( int id ) {
  int i;

  for( i = 0; s_sizes[ i ].name != 0; i++ ) {
    if( s_sizes[ i ].id == id ) {
      return s_sizes[ i ].name;
    }
  }

  return NULL;
}


int dndGetSizeACMod( int id ) {
  int i;

  for( i = 0; s_sizes[ i ].name != 0; i++ ) {
    if( s_sizes[ i ].id == id ) {
      return s_sizes[ i ].acMod;
    }
  }

  return 0;
}


char* dndGetSpellName( int id ) {
  int i;

  for( i = 0; s_spells[ i ].name != 0; i++ ) {
    if( s_spells[ i ].id == id ) {
      return s_spells[ i ].name;
    }
  }

  return NULL;
}

char* dndGetSpellPCGenName( int id ) {
  int i;

  for( i = 0; s_spells[ i ].name != 0; i++ ) {
    if( s_spells[ i ].id == id ) {
      return s_spells[ i ].pcgen_name;
    }
  }

  return NULL;
}

int dndGetSpellLevel( int classid, int spellid ) {
  SPELLSFORCLASS* list;
  int i;

  list = 0;
  for( i = 0; s_classInfo[ i ].name != 0; i++ ) {
    if( s_classInfo[ i ].id == classid ) {
      list = s_classInfo[ i ].spells;
      break;
    }
  }

  if( list == 0 ) {
    return -1;
  }

  for( i = 0; list[ i ].spell != 0; i++ ) {
    if( list[ i ].spell == spellid ) {
      return list[ i ].level;
    }
  }

  return -1;
}


int dndGetSpellOfLevel( int classid, int level, char** next ) {
  SPELLSFORCLASS* list;
  int i;

  list = 0;

  if( classid != 0 ) {
    for( i = 0; s_classInfo[ i ].name != 0; i++ ) {
      if( s_classInfo[ i ].id == classid ) {
        list = s_classInfo[ i ].spells;
        break;
      }
    }
    if( list == 0 ) {
      for( i = 0; s_domains[ i ].name != 0; i++ ) {
        if( s_domains[ i ].id == classid ) {
          list = s_domains[ i ].spells;
        }
      }
    }
  } else {
    list = (SPELLSFORCLASS*)(*next);
  }

  if( list == 0 ) {
    *next = 0;
    return 0;
  }

  if( list->spell == 0 ) {
    *next = 0;
    return 0;
  }

  while( list->level != level ) {
    list++;
    if( list->spell == 0 ) {
      *next = 0;
      return 0;
    }
  }

  *next = (char*)( list + 1 );

  return list->spell;
}


int dndGetSpellsPerDay( int classid, int classLevel, int spellLevel ) {
  int i;
  SPELLMATRIX* s;

  s = 0;
  for( i = 0; s_classInfo[ i ].name != 0; i++ ) {
    if( s_classInfo[ i ].id == classid ) {
      if( s_classInfo[ i ].spellsPerDay == 0 ) {
        return -1;
      }
      s = (SPELLMATRIX*)s_classInfo[ i ].spellsPerDay;
      break;
    }
  }

  if( s == 0 ) {
    return -1;
  }

  return (*s)[ classLevel - 1 ][ spellLevel ];
}


int dndGetSpellsKnown( int classid, int classLevel, int spellLevel ) {
  int i;
  SPELLMATRIX* s;

  switch( classid ) {
    case pcWIZARD:
    case pcDRUID:
    case pcCLERIC:
    case pcRANGER:
    case pcPALADIN:
      return 0;
  }

  s = 0;
  for( i = 0; s_classInfo[ i ].name != 0; i++ ) {
    if( s_classInfo[ i ].id == classid ) {
      if( s_classInfo[ i ].spellsPerDay == 0 ) {
        return -1;
      }
      s = (SPELLMATRIX*)s_classInfo[ i ].spellsKnown;
      break;
    }
  }

  if( s == 0 ) {
    return -1;
  }

  return (*s)[ classLevel - 1 ][ spellLevel ];
}


int dndGetBonusSpellsPerDay( int relevantAbility, int spellLevel ) {
  int rc;

  if( spellLevel < 1 ) {
    return 0;
  }

  if( relevantAbility < 10 ) {
    return -1;
  }

  if( relevantAbility < ( 10 + spellLevel*2 ) ) {
    return 0;
  }

  /* formula is:
   *   AS -> ability score
   *   SL -> spell level
   *
   *   bonus = floor( ( AS - 10 - SL*2 ) / 8 ) + 1
   */

  rc = ( ( relevantAbility - 10 - spellLevel*2 ) >> 3 ) + 1;
  if( rc < 1 ) {
    rc = 0;
  }

  return rc;
}


char* dndGetDomainName( int id ) {
  int i;

  for( i = 0; s_domains[ i ].name != 0; i++ ) {
    if( s_domains[ i ].id == id ) {
      return s_domains[ i ].name;
    }
  }

  return NULL;
}


int dndGetForbiddenAlignmentsForDomain( int id ) {
  int i;

  for( i = 0; s_domains[ i ].name != 0; i++ ) {
    if( s_domains[ i ].id == id ) {
      return s_domains[ i ].forbiddenAlignments;
    }
  }

  return 0;
}


char* dndGetArmorName( int id ) {
  int i;

  for( i = 0; s_armors[ i ].name != 0; i++ ) {
    if( s_armors[ i ].id == id ) {
      return s_armors[ i ].name;
    }
  }

  return NULL;
}


int dndGetArmorType( int id ) {
  int i;

  for( i = 0; s_armors[ i ].name != 0; i++ ) {
    if( s_armors[ i ].id == id ) {
      return s_armors[ i ].type;
    }
  }

  return 0;
}


int dndGetArmorCost( int id ) {
  int i;

  for( i = 0; s_armors[ i ].name != 0; i++ ) {
    if( s_armors[ i ].id == id ) {
      return s_armors[ i ].cost;
    }
  }

  return 0;
}


int dndGetArmorACBonus( int id ) {
  int i;

  for( i = 0; s_armors[ i ].name != 0; i++ ) {
    if( s_armors[ i ].id == id ) {
      return s_armors[ i ].acBonus;
    }
  }

  return 0;
}


int dndGetArmorMaxDexterity( int id ) {
  int i;

  for( i = 0; s_armors[ i ].name != 0; i++ ) {
    if( s_armors[ i ].id == id ) {
      return s_armors[ i ].maxDex;
    }
  }

  return 0;
}


int dndGetArmorCheckPenalty( int id ) {
  int i;

  for( i = 0; s_armors[ i ].name != 0; i++ ) {
    if( s_armors[ i ].id == id ) {
      return s_armors[ i ].checkPenalty;
    }
  }

  return 0;
}


int dndGetArmorArcaneSpellFailure( int id ) {
  int i;

  for( i = 0; s_armors[ i ].name != 0; i++ ) {
    if( s_armors[ i ].id == id ) {
      return s_armors[ i ].arcaneSpellFailure;
    }
  }

  return 0;
}


int dndGetClassMultipleAttackBonus( int baseAttack, int which ) {
  int bonus;

  if( which < 1 ) {
    return 0;
  }
  
  bonus = baseAttack - ( which - 1 ) * 5;

  return bonus;
}


int dndGetClassAttacksPerRound( int baseAttack ) {
  int count;

  /* extra attacks are gained when the baseAttack is +6, +11, and +16 */

  count = ( baseAttack - 1 ) / 5 + 1;
  return count;
}


int dndGetMonkAttacksPerRound( int baseAttack ) {
  int count;

  /* extra attacks are gained when the baseAttack is +6, +8, +11 */

  //count = ( baseAttack - 1 ) / 3 + 1;
  if (baseAttack < 6) count = 2;
  else if (baseAttack < 8) count = 3;
  else if (baseAttack < 11) count = 4;
  else count = 5;
  return count;
}


int dndGetMonkMultipleAttackBonus( int baseAttack, int monkLevel, int which ) {
  int bonus;
  int count;
  int monkmod;

  if( which < 1 ) {
    return 0;
  }

  if (monkLevel < 11) count = 2;
  else count = 3; 

  if (monkLevel < 5) monkmod = 2;
  else if (monkLevel < 9) monkmod = 1;
  else monkmod = 0;

  if (which <= count) bonus = baseAttack - monkmod;
  else bonus = (baseAttack - 5*(which-count)) - monkmod;

  return bonus;
}


int dndGetFortitudeSave( int classType, int level ) {
  int i;

  if( ( level < 1 ) || ( level > 20 ) ) {
    return 0;
  }

  for( i = 0; s_classInfo[ i ].name != 0; i++ ) {
    if( s_classInfo[ i ].id == classType ) {
      return s_classInfo[ i ].fortSave[ level - 1 ];
    }
  }

  return 0;
}


int dndGetReflexSave( int classType, int level ) {
  int i;

  if( ( level < 1 ) || ( level > 20 ) ) {
    return 0;
  }

  for( i = 0; s_classInfo[ i ].name != 0; i++ ) {
    if( s_classInfo[ i ].id == classType ) {
      return s_classInfo[ i ].refSave[ level - 1 ];
    }
  }

  return 0;
}


int dndGetWillSave( int classType, int level ) {
  int i;

  if( ( level < 1 ) || ( level > 20 ) ) {
    return 0;
  }

  for( i = 0; s_classInfo[ i ].name != 0; i++ ) {
    if( s_classInfo[ i ].id == classType ) {
      return s_classInfo[ i ].willSave[ level - 1 ];
    }
  }

  return 0;
}


int dndGetNPCGearValue( int level ) {
  if( level < 1 ) {
    return 0;
  }
  if( level > 20 ) {
    level = 20;
  }
  
  return s_npcGearValue[ level - 1 ];  
}


int dndGetRaceBonus( int id, int gender, int type, int data ) {
  int i;
  int j;
  RACIALBONUS *bonuses;

  for( i = 0; s_races[ i ].name != 0; i++ ) {
    if( s_races[ i ].id == id ) {
      if( gender == gFEMALE ) {
        bonuses = s_races[ i ].femaleBonuses;
      } else {
        bonuses = s_races[ i ].maleBonuses;
      }

      if( bonuses == 0 ) {
        break;
      }

      for( j = 0; bonuses[ j ].type != 0; j++ ) {
        if( bonuses[ j ].type == type ) {
          if( bonuses[ j ].data == data ) {
            return bonuses[ j ].bonus;
          }
        }
      }
      break;
    }
  }

  return 0;
}


int dndGetRacialHeightWeight( int race, int gender, DNDRACIALHEIGHTWEIGHT* data ) {
  int i;

  for( i = 0; s_races[ i ].name != 0; i++ ) {
    if( s_races[ i ].id == race ) {
      if( gender == gMALE ) {
        memcpy( data, &(s_races[ i ].male), sizeof( *data ) );
      } else if( gender == gFEMALE ) {
        memcpy( data, &(s_races[ i ].female), sizeof( *data ) );
      } else {
        return 0;
      }
      return 1;
    }
  }

  return 0;
}


int dndGetRaceAlignment( int race ) {
  int i;

  for( i = 0; s_races[ i ].name != 0; i++ ) {
    if( s_races[ i ].id == race ) {
      return s_races[ i ].usualAlignment;
    }
  }

  return 0;
}


int dndGetRaceExtraHitDice( int race, int* count, int* type ) {
  int i;

  for( i = 0; s_races[ i ].name != 0; i++ ) {
    if( s_races[ i ].id == race ) {
      *count = s_races[ i ].extraHitDieCount;
      *type  = s_races[ i ].extraHitDie;

      return ( *count > 0 ? 1 : 0 );
    }
  }

  return 0;
}


int dndGetRaceBonusOfType( int race, int gender, int type, int* data, int* bonus, char** next ) {
  RACIALBONUS* b;
  int i;

  b = 0;

  if( race != 0 ) {
    for( i = 0; s_races[ i ].name != 0; i++ ) {
      if( s_races[ i ].id == race ) {
        if( gender == gFEMALE ) {
          b = s_races[ i ].femaleBonuses;
        } else {
          b = s_races[ i ].maleBonuses;
        }
        break;
      }
    }

  } else {
    b = (RACIALBONUS*)(*next);
  }

  if( b == 0 ) {
    *next = 0;
    return 0;
  }

  while( ( b->type != 0 ) && ( b->type != type ) ) {
    b++;
  }

  if( b->type == 0 ) {
    *next = 0;
    return 0;
  }

  *data  = b->data;
  *bonus = b->bonus;

  b++;
  *next = (char*)b;

  return 1;
}


int dndGetRacePreferredClass( int race ) {
  int i;

  for( i = 0; s_races[ i ].name != 0; i++ ) {
    if( s_races[ i ].id == race ) {
      return s_races[ i ].preferredClass;
    }
  }

  return 0;
}


int dndGetRaceCR( int id ) {
  int i;

  for( i = 0; s_races[ i ].name != 0; i++ ) {
    if( s_races[ i ].id == id ) {
      return s_races[ i ].challengeRating;
    }
  }

  return 0;
}


char* dndGetClassAbbr( int id ) {
  int i;

  for( i = 0; s_classInfo[ i ].name != 0; i++ ) {
    if( s_classInfo[ i ].id == id ) {
      return s_classInfo[ i ].abbr;
    }
  }

  return NULL;
}


char* dndGetAlignmentAbbr( int alignment ) {
  int i;

  for( i = 0; s_alignmentText[ i ].text != 0; i++ ) {
    if( s_alignmentText[ i ].alignment == alignment ) {
      return s_alignmentText[ i ].abbr;
    }
  }

  return NULL;
}


char* dndGetLanguageName( int id ) {
  int i;

  for( i = 0; s_languages[ i ].name != 0; i++ ) {
    if( s_languages[ i ].id == id ) {
      return s_languages[ i ].name;
    }
  }

  return NULL;
}


int dndGetGivenLanguages( int id, char** next ) {
  int *entry;
  int  i;

  entry = 0;

  if( id != 0 ) {
    for( i = 0; s_races[ i ].name != 0; i++ ) {
      if( s_races[ i ].id == id ) {
        entry = s_races[i].automaticLanguages;
        break;
      }
    }
  } else {
    entry = (int*)(*next);
  }

  if( entry == 0 ) {
    return 0;
  }

  i = *entry;
  entry++;

  *next = (char*)entry;

  return i;
}


int dndGetBonusLanguages( int id, char** next ) {
  int *entry;
  int  i;

  entry = 0;

  if( id != 0 ) {
    for( i = 0; s_races[ i ].name != 0; i++ ) {
      if( s_races[ i ].id == id ) {
        entry = s_races[i].bonusLanguages;
        break;
      }
    }
  } else {
    entry = (int*)(*next);
  }

  if( entry == 0 ) {
    return 0;
  }

  i = *entry;
  entry++;

  *next = (char*)entry;

  return i;
}


int dndGetRelativeWeaponSize( int raceid, int weapon ) {
  int raceSize;
  int weaponSize;

  raceSize = dndGetRaceSize( raceid );
  weaponSize = dndGetWeaponSize( weapon );

  if( weaponSize < raceSize ) {
    return wtLIGHT;
  } else if( weaponSize == raceSize ) {
    return wtONEHANDED;
  }

  return wtTWOHANDED;
}


int dndGetSizeHideMod( int id ) {
  int i;

  for( i = 0; s_sizes[ i ].name != 0; i++ ) {
    if( s_sizes[ i ].id == id ) {
      return s_sizes[ i ].hideCheck;
    }
  }

  return 0;
}


int dndGetSpellSchool( int id ) {
  int i;

  for( i = 0; s_spells[ i ].name != 0; i++ ) {
    if( s_spells[ i ].id == id ) {
      return s_spells[ i ].school;
    }
  }

  return 0;
}


int dndGetMonkSpeedForRace( int raceid, int level ) {
  int baseSpeed;
  
  /* formula for calculating a monk's speed is:
   * baseSpeed * ( ( 3 + floor(level/3) ) / 3 )
   */

  baseSpeed = dndGetRaceSpeed( raceid );
  //baseSpeed = (int)( baseSpeed * ( ( 3 + level/3 ) / 3.0 ) );

  if (level > 2) baseSpeed += (int) ((level / 3) * 10);

  return roundToNearest5( baseSpeed );
}


int dndGetRaceSpeed( int id ) {
  int i;

  for( i = 0; s_races[ i ].name != 0; i++ ) {
    if( s_races[ i ].id == id ) {
      return s_races[ i ].speed;
    }
  }

  return 0;
}

