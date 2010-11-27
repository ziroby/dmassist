package com.ziroby.dmassist.model;

import static org.junit.Assert.*;

import org.junit.Before;
import org.junit.Test;

import com.ziroby.dmassist.gwtable.model.Entity;


public class EnhancedEntityListTest {
	private EnhancedEntityList dataModel;

	@Before
	public void setUp() {
		dataModel = new EnhancedEntityList();
	}
	
	@Test
	public void startCombatRerollsInitiative() throws Exception {
        EnhancedEntity newCreature = new EnhancedEntity();
        newCreature.setAbbreviation("G");
        newCreature.setName("Ogre 1");
        newCreature.setInitDiceString("+30");
        newCreature.setInitRoll(12);
        newCreature.setHitpoints(25);
        dataModel.addEntity(newCreature);
        
        EnhancedEntity actualCreature = dataModel.getEnhancedEntities().iterator().next();
        
        assertEquals(new Integer(12), actualCreature.getInitRoll());
        
        dataModel.resetNumRounds();
        
        assertTrue("Initiative not rerolled", !new Integer(12).equals(actualCreature.getInitRoll()));
	}
}
