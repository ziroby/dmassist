/**
 * Copyright 2009 Ron "Ziroby" Romero
 * All Rights Reserved
 */
package com.ziroby.dmassist.parser;


import junit.framework.TestCase;

import org.junit.Test;

import com.ziroby.dmassist.model.EntityList;
import com.ziroby.dmassist.model.ResultsDisplay;

/**
 * Tests the parser and interpreter working together.
 * 
 * @author Ron Romero
 *
 */
public class ParserInterpreterTest extends TestCase {

    public static class MockResultsDisplay implements ResultsDisplay {

		private String result;
		private boolean error = false;
		private String errorMessage = "";

		public void addLine(String s) {
			if (s.matches("Error.*"))
			{
				errorMessage = s;
				error  = true;
			}
		}

		public void setResult(String s) {
			result = s;
		}

		public final String getResult() {
			return result;
		}

		public final boolean isError() {
			boolean temp = error;
			error = false;
			errorMessage = "";
			return temp;
		}

		public final String getErrorMessage() {
			String temp = errorMessage;
			errorMessage = "";
			return temp;
		}
	}

	private EntityList dataModel;
	private Interpreter interpreter;
	private MockResultsDisplay resultsDisplay;
	private Parser parser;

	/**
	 * @see junit.framework.TestCase#setUp()
	 */
	@Override
	protected void setUp() throws Exception {
		super.setUp();

		dataModel = new MockDataModel();

		resultsDisplay = new MockResultsDisplay();
		interpreter = new Interpreter(dataModel, resultsDisplay);
		parser = new Parser(interpreter, resultsDisplay);
	}

	/**
	 * Test method for {@link com.ziroby.parser.Interpreter#Interpreter}
	 */
	@Test
	public final void testInterpreter() {
		parser.parse("next");
	}
	
	
	@Test
	public void testCommandNext()
	{
		parser.parse("next");
		assertEquals("", resultsDisplay.getErrorMessage());
		parser.parse("n");		
		assertEquals("", resultsDisplay.getErrorMessage());
	}

	@Test
	public void testCommandRoll()
	{
		parser.parse("roll 1d6");		
		assertEquals("", resultsDisplay.getErrorMessage());
		assertTrue(haveResultes());
		parser.parse("r 2d5 + 1d8 - 3");		
		assertEquals("", resultsDisplay.getErrorMessage());
		assertTrue(haveResultes());
	}
	@Test
	public void testCommandRollError()
	{
		parser.parse("roll");		
		assertTrue(resultsDisplay.isError());
		assertFalse(haveResultes());
		parser.parse("r");		
		assertTrue(resultsDisplay.isError());
		assertFalse(haveResultes());
	}

	@Test
	public void testCommandDamage()
	{
		parser.parse("daMage p2 8");
		assertEquals("", resultsDisplay.getErrorMessage());
		assertTrue(haveResultes());
		parser.parse("dmg c2 d6 + 2d 6 + 3 d8");		
		assertEquals("", resultsDisplay.getErrorMessage());
		assertTrue(haveResultes());
	}
	@Test
	public void testCommandSubdue()
	{
		parser.parse("SUBDUE p2 8");
		assertEquals("", resultsDisplay.getErrorMessage());
		assertTrue(haveResultes());
		parser.parse("Sub c2 d6 + 2d 6 + 3 d8");		
		assertEquals("", resultsDisplay.getErrorMessage());
		assertTrue(haveResultes());
	}
	@Test
	public void testCommandHeal()
	{
		parser.parse("hEaL p2 8");
		assertEquals("", resultsDisplay.getErrorMessage());
		assertTrue(haveResultes());
		parser.parse("h c2 d6 + 2d 6 + 3 d8");		
		assertEquals("", resultsDisplay.getErrorMessage());
		assertTrue(haveResultes());
	}
	@Test
	public void testCommandRecover()
	{
		parser.parse("recover p2 8");
		assertEquals("", resultsDisplay.getErrorMessage());
		assertTrue(haveResultes());
		parser.parse("rec c2 d6 + 2d 6 + 3 d8");		
		assertEquals("", resultsDisplay.getErrorMessage());
		assertTrue(haveResultes());
	}
	@Test
	public void testCommandSet()
	{
		parser.parse("set p2 8 hp");
		assertEquals("", resultsDisplay.getErrorMessage());
		assertTrue(haveResultes());
		parser.parse("set c2 hp: d6 + 2d 6 + 3 d8");		
		assertEquals("", resultsDisplay.getErrorMessage());
		assertTrue(haveResultes());
	}
	@Test
	public void testCommandSet1()
	{
		parser.parse("set p2 hp 8");
		assertEquals("", resultsDisplay.getErrorMessage());
		assertTrue(haveResultes());
		parser.parse("set c2 hp: d6 + 2d 6 + 3 d8");		
		assertEquals("", resultsDisplay.getErrorMessage());
		assertTrue(haveResultes());
	}
	@Test
	public void testCommandSet2()
	{
		parser.parse("set W5 18 HP subDual:43 init=25");
		assertEquals("", resultsDisplay.getErrorMessage());
		assertFalse(haveResultes());
		parser.parse("set W5 18 hitpoints sub: 43 init = 25");		
		assertEquals("", resultsDisplay.getErrorMessage());
		assertFalse(haveResultes());
		parser.parse("set W5 18 hitpoint sub: 43 init = 25");		
		assertEquals("", resultsDisplay.getErrorMessage());
		assertFalse(haveResultes());
	}
	@Test
	public void testCommandSet3()
	{
		parser.parse("set W5 18 HP rnds 5 subDual:43 init=25");
		assertEquals("", resultsDisplay.getErrorMessage());
		assertFalse(haveResultes());
		parser.parse("set W5 18 hitpoints rounds 5 sub: 43 init = 25");		
		assertEquals("", resultsDisplay.getErrorMessage());
		assertFalse(haveResultes());
		parser.parse("set W5 18 hitpoint round 2 sub: 43 init = 25");		
		assertEquals("", resultsDisplay.getErrorMessage());
		assertFalse(haveResultes());
		parser.parse("set W5 18 hitpoint rnd 2 sub: 43 init = 25");		
		assertEquals("", resultsDisplay.getErrorMessage());
		assertFalse(haveResultes());
	}
	public void testCommandHelp()
	{
		parser.parse("help");
		assertEquals("", resultsDisplay.getErrorMessage());
		assertFalse(haveResultes());
//		parser.parse("?");		
//		assertEquals("", resultsDisplay.getErrorMessage());
//		assertFalse(haveResultes());
	}
	@Test
	public void testBadCommand()
	{
		parser.parse("bad");		
		assertTrue(resultsDisplay.isError());
		assertFalse(haveResultes());
		parser.parse("x");		
		assertTrue(resultsDisplay.isError());
		assertFalse(haveResultes());
	}
	
	

	@Test
	public void testRollCommand1() {
		checkRollCommand("1d4+2");
	}


	@Test
	public void testRollCommand2() {
		checkRollCommand("1d5");
	}


	@Test
	public void testRollCommand3() {
		checkRollCommand("1d5 + 0");
	}


	@Test
	public void testRollCommand4() {
		checkRollCommand("d20");
	}


	@Test
	public void testRollCommand5() {
		checkRollCommand("d20+2");
	}


	@Test
	public void testRollCommand6() {
		checkRollCommand("1d4 +2");
	}


	@Test
	public void testRollCommand7() {
		checkRollCommand("  1d4 +2");
	}


	@Test
	public void testRollCommand8() {
		checkRollCommand("1d4 + 2");
	}


	@Test
	public void testRollCommand9() {
		checkRollCommand("1 d   4 +  2");
	}


	@Test
	public void testRollCommand10() {
		checkRollCommand("1  d 4 +  2");	
	}


	@Test
	public void testRollCommand11() {
		checkRollCommand("2d6+4");
	}


	@Test
	public void testRollCommand12() {
		checkRollCommand("3d13+89");
	}


	@Test
	public void testRollCommand13() {
		checkRollCommand("1d4 -2");
	}


	@Test
	public void testRollCommand14() {
		checkRollCommand("1d4-2");
	}


	@Test
	public void testRollCommand15() {
		checkRollCommand("1d4+-2");
	}


	@Test
	public void testRollCommand16() {
		checkRollCommand("1d4--2");
	}


	@Test
	public void testRollCommand17() {
		checkRollCommand("1d4+2+3");
	}


	@Test
	public void testRollCommand18() {
		checkRollCommand("1d4++3");
	}

	@Test
	public void testRollCommand19() {
		checkRollCommand("-1d4 +3");
	}

	@Test
	public void testRollCommand20() {
		checkRollCommand("-1d4+2");
	}

	@Test
	public void testRollCommand21() {
		checkRollCommand("- 2d4+2");
	}


	/**
	 * Test method for {@link com.ziroby.dmassist.model.DiceEquation#DiceEquation(java.lang.String)}.
	 */
	@Test
	public void testDiceExtendedEquationCtor1() {
		checkRollCommand("2d8 +1d6");
	}


	/**
	 * Test method for {@link com.ziroby.dmassist.model.DiceEquation#DiceEquation(java.lang.String)}.
	 */
	@Test
	public void testDiceExtendedEquationCtor2() {
		checkRollCommand("2d8 +d6");
	}


	/**
	 * Test method for {@link com.ziroby.dmassist.model.DiceEquation#DiceEquation(java.lang.String)}.
	 */
	@Test
	public void testDiceExtendedEquationCtor3() {
		checkRollCommand("2d8 - 3d6");
	}


	/**
	 * Test method for {@link com.ziroby.dmassist.model.DiceEquation#DiceEquation(java.lang.String)}.
	 */
	@Test
	public void testDiceExtendedEquationCtor4() {
		checkRollCommand("2d8- d6");
	}



	/**
	 * @param str
	 */
	private void checkRollCommand(String str) {
		parser.parse("roll " + str);		
		assertEquals("", resultsDisplay.getErrorMessage());
		assertTrue(haveResultes());
		parser.parse("r " + str);		
		assertEquals("", resultsDisplay.getErrorMessage());
		assertTrue(haveResultes());
//		parser.parse(str); // If you just type a dice equation it assumes you wanna roll it.		
//		assertEquals("", resultsDisplay.getErrorMessage());
//		assertTrue(haveResultes());
	}

	
	
	
	/**
	 * Tells if there are any results in the result display box.
	 * 
	 * @return false if the result is null, empty, or just spaces.  True otherwise
	 */
	private boolean haveResultes() {
		return resultsDisplay.getResult() != null &&
				   !resultsDisplay.getResult().isEmpty();
	}

	
	
}
