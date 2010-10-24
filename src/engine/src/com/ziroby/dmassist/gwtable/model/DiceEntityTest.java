package com.ziroby.dmassist.gwtable.model;


import static org.junit.Assert.*;

import org.junit.Before;
import org.junit.Test;

public class DiceEntityTest {

	@Before
	public void setUp() throws Exception {
	}

	@Test
	public void plusTwentyInitShouldBeAboveTwenty() throws Exception {
		Integer initRollValue = rollInit("+20");
		assertNotNull(initRollValue);
		assertTrue("wrong init value: " + initRollValue, initRollValue > 20);
	}

	private Integer rollInit(String diceEquation) {
		Entity entity = new DiceEntity();

		entity.setInitRoll(diceEquation);
		entity.startCombat();

		Integer initRollValue = entity.getInitRoll();
		return initRollValue;
	}

	@Test
	public void negativeTwentyShouldBeGreaterThanNegative20() throws Exception {
		Integer initRollValue = rollInit("-20");
		assertNotNull(initRollValue);
		assertTrue("wrong init value: " + initRollValue, initRollValue > -20);
	}
	@Test
	public void negative1ShouldBeGreaterThanPositive() throws Exception {
		Integer initRollValue = rollInit("-1");
		assertNotNull(initRollValue);
		assertTrue("wrong init value: " + initRollValue, initRollValue > 0);
	}
	@Test
	public void initValueShouldBeNegativeBeforeCombatStart() throws Exception {
		Entity entity = new DiceEntity();

		entity.setInitRoll("-1");

		Integer initRollValue = entity.getInitRoll();
		assertNull(initRollValue);
	}
	@Test
	public void initValueShouldBeNullAfterCombatEnd() throws Exception {
		Entity entity = new DiceEntity();

		entity.setInitRoll("-5");

		Integer initRollValue = entity.getInitRoll();
		assertNull(initRollValue);

		entity.startCombat();
		initRollValue = entity.getInitRoll();
		assertNotNull(initRollValue);
		entity.endCombat();
		initRollValue = entity.getInitRoll();
		assertNull(initRollValue);
	}
	@Test
	public void bareIntegersDontRollDice() throws Exception {
		Integer initRollValue = rollInit("22");
		assertNotNull(initRollValue);
		assertEquals(new Integer(22), initRollValue);
	}
	@Test
	public void bareDiceDontRollDice() throws Exception {
		Integer initRollValue = rollInit("1d100+20");
		assertNotNull(initRollValue);
		assertTrue("wrong init value: " + initRollValue, initRollValue > 21);
		assertTrue("wrong init value: " + initRollValue, initRollValue < 121);
	}
	@Test
	public void ifNoDiceEquationShouldBeInitRoll() throws Exception {
		Entity entity = new DiceEntity();

		entity.setInitRoll(12);
		entity.startCombat();

		Integer initRollValue = entity.getInitRoll();
		assertNotNull(initRollValue);
		assertEquals("wrong init value: ", initRollValue, new Integer(12));
	}
}
