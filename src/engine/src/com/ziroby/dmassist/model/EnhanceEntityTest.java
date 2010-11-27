package com.ziroby.dmassist.model;

import static org.junit.Assert.*;
import static org.junit.Assert.assertEquals;

import org.junit.Before;
import org.junit.Test;


public class EnhanceEntityTest {

	private EnhancedEntity entity;
	@Before
	public void setUp() {
		entity = new EnhancedEntity();		
	}
	
	@Test
	public void setInitToIntegerShouldWork() throws Exception {
		entity.setInitRoll(22);
		assertEquals(new Integer(22), entity.getInitRoll());
	}
	
	@Test
	public void setToDiceEquationShouldSetToNumberInRange() throws Exception {
		entity.setInitRoll("1d20+40");
		
		Integer initRoll = entity.getInitRoll();
		assertNotNull(initRoll);
		int actual = initRoll;
		
		assertTrue("number " + actual + " too low", actual > 40);
		assertTrue("number " + actual + " too high", actual <= 40 + 20);
	}
	@Test
	public void setToDiceEquationShouldSetToNumberInRange2() throws Exception {
		entity.setInitRoll("1d20+10");
		
		Integer initRoll = entity.getInitRoll();
		assertNotNull(initRoll);
		int actual = initRoll;
		
		assertTrue("number " + actual + " too low", actual > 10);
		assertTrue("number " + actual + " too high", actual <= 10 + 20);
	}
	@Test
	public void setInitRollShouldSetInitDiceString() throws Exception {
		String diceEquation = "1d10+2";
		entity.setInitRoll(diceEquation);
		
		String actual = entity.getInitDiceString();
		
		assertEquals(diceEquation, actual);
	}
	@Test
	public void setInitRollShouldSetInitDiceString2() throws Exception {
		String diceEquation = "2d20-5";
		entity.setInitRoll(diceEquation);
		
		String actual = entity.getInitDiceString();
		
		assertEquals(diceEquation, actual);
	}
	@Test
	public void settingToIntegerShouldNotSetInitDiceString() throws Exception {
		entity.setInitRoll("12");
		
		String actual = entity.getInitDiceString();
		
		assertEquals(null, actual);
		
	}
	@Test
	public void initModifierShouldSetTo1d20PlusModifier() throws Exception {
		entity.setInitRoll("+40");
		
		Integer initRoll = entity.getInitRoll();
		assertNotNull(initRoll);
		int actual = initRoll;
		
		assertTrue("number " + actual + " too low", actual > 40);
		assertTrue("number " + actual + " too high", actual <= 40 + 20);
		
		assertEquals("+40", entity.getInitDiceString());
	}
	@Test
	public void initModifierShouldSetTo1d20MinusModifier() throws Exception {
		entity.setInitRoll("-40");
		
		Integer initRoll = entity.getInitRoll();
		assertNotNull(initRoll);
		int actual = initRoll;
		
		assertTrue("number " + actual + " too low", actual > -40);
		assertTrue("number " + actual + " too high", actual <= -40 + 20);
		
		assertEquals("-40", entity.getInitDiceString());
	}
}
