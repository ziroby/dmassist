/*
 *   Copyright 2009 Ron "Ziroby" Romero
 * 
 *   This file is part of DM Assist.
 *
 *   DM Assist is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   DM Assist is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with DM Assist.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
package com.ziroby.dmassist.model;

import junit.framework.TestCase;

import org.junit.After;
import org.junit.Before;
import org.junit.Test;


/**
 * @author Ron Romero
 *
 */
public class DiceEquationTest extends TestCase {

	/**
	 * @throws java.lang.Exception
	 */
	@Override
	@Before
	public void setUp() throws Exception {
	    // Nothing to do
	}

	/**
	 * @throws java.lang.Exception
	 */
	@Override
	@After
	public void tearDown() throws Exception {
	    // Noting to see; move along.
	}

	/**
	 * Test method for {@link com.ziroby.dmassist.model.DiceEquation#DiceEquation(java.lang.String)}.
	 */
	@Test
	public void testDiceEquation() {
		DiceEquation eq = new DiceEquation("1d4+2");
		assertEquals("1d4+2", eq.toString());
	}

//	/**
//	 * Test method for {@link com.ziroby.dmassist.model.DiceEquation#DiceEquation(java.lang.String)}.
//	 */
//	@Test
//	public void testDiceEquationFromArray() {
//		String[][] testString = {
//				{"1d4+2", "1d4+2"},
//				{"1d5", "1d5"},
//				{"1d5 + 0", "1d5"},
//				{"d20", "1d20"},
//				{"d20+2", "1d20+2"},
//				{"1d4 +2", "1d4+2"},
//				{"  1d4 +2", "1d4+2"},
//				{"1d4 + 2", "1d4+2"},
//				{"1 d   4 +  2", "1d4+2"},
//				{"1  d 4 +  2", "1d4+2"},	
//				{"2d6+4", "2d6+4"},
//				{"3d13+89", "3d13+89"},
//				{"1d4 -2", "1d4-2"},
//				{"1d4-2", "1d4-2"},
//				{"1d4+-2", "1d4-2"},
//				{"1d4--2", "1d4+2"},
//		};
//		
//		for (String[] string : testString) {
//			checkDiceEquationCtor(string[0], string[1]);
//		}
//	}

	/**
	 * Test method for {@link com.ziroby.dmassist.model.DiceEquation#DiceEquation(java.lang.String)}.
	 */
	@Test
	public void testDiceEquationCtor1() {
		checkDiceEquationCtor("1d4+2", "1d4+2");
	}


	/**
	 * Test method for {@link com.ziroby.dmassist.model.DiceEquation#DiceEquation(java.lang.String)}.
	 */
	@Test
	public void testDiceEquationCtor2() {
		checkDiceEquationCtor("1d5", "1d5");
	}


	/**
	 * Test method for {@link com.ziroby.dmassist.model.DiceEquation#DiceEquation(java.lang.String)}.
	 */
	@Test
	public void testDiceEquationCtor3() {
		checkDiceEquationCtor("1d5 + 0", "1d5");
	}


	/**
	 * Test method for {@link com.ziroby.dmassist.model.DiceEquation#DiceEquation(java.lang.String)}.
	 */
	@Test
	public void testDiceEquationCtor4() {
		checkDiceEquationCtor("d20", "1d20");
	}


	/**
	 * Test method for {@link com.ziroby.dmassist.model.DiceEquation#DiceEquation(java.lang.String)}.
	 */
	@Test
	public void testDiceEquationCtor5() {
		checkDiceEquationCtor("d20+2", "1d20+2");
	}


	/**
	 * Test method for {@link com.ziroby.dmassist.model.DiceEquation#DiceEquation(java.lang.String)}.
	 */
	@Test
	public void testDiceEquationCtor6() {
		checkDiceEquationCtor("1d4 +2", "1d4+2");
	}


	/**
	 * Test method for {@link com.ziroby.dmassist.model.DiceEquation#DiceEquation(java.lang.String)}.
	 */
	@Test
	public void testDiceEquationCtor7() {
		checkDiceEquationCtor("  1d4 +2", "1d4+2");
	}


	/**
	 * Test method for {@link com.ziroby.dmassist.model.DiceEquation#DiceEquation(java.lang.String)}.
	 */
	@Test
	public void testDiceEquationCtor8() {
		checkDiceEquationCtor("1d4 + 2", "1d4+2");
	}


	/**
	 * Test method for {@link com.ziroby.dmassist.model.DiceEquation#DiceEquation(java.lang.String)}.
	 */
	@Test
	public void testDiceEquationCtor9() {
		checkDiceEquationCtor("1 d   4 +  2", "1d4+2");
	}


	/**
	 * Test method for {@link com.ziroby.dmassist.model.DiceEquation#DiceEquation(java.lang.String)}.
	 */
	@Test
	public void testDiceEquationCtor10() {
		checkDiceEquationCtor("1  d 4 +  2", "1d4+2");	
	}


	/**
	 * Test method for {@link com.ziroby.dmassist.model.DiceEquation#DiceEquation(java.lang.String)}.
	 */
	@Test
	public void testDiceEquationCtor11() {
		checkDiceEquationCtor("2d6+4", "2d6+4");
	}


	/**
	 * Test method for {@link com.ziroby.dmassist.model.DiceEquation#DiceEquation(java.lang.String)}.
	 */
	@Test
	public void testDiceEquationCtor12() {
		checkDiceEquationCtor("3d13+89", "3d13+89");
	}


	/**
	 * Test method for {@link com.ziroby.dmassist.model.DiceEquation#DiceEquation(java.lang.String)}.
	 */
	@Test
	public void testDiceEquationCtor13() {
		checkDiceEquationCtor("1d4 -2", "1d4-2");
	}


	/**
	 * Test method for {@link com.ziroby.dmassist.model.DiceEquation#DiceEquation(java.lang.String)}.
	 */
	@Test
	public void testDiceEquationCtor14() {
		checkDiceEquationCtor("1d4-2", "1d4-2");
	}


	/**
	 * Test method for {@link com.ziroby.dmassist.model.DiceEquation#DiceEquation(java.lang.String)}.
	 */
	@Test
	public void testDiceEquationCtor15() {
		checkDiceEquationCtor("1d4+-2", "1d4-2");
	}


	/**
	 * Test method for {@link com.ziroby.dmassist.model.DiceEquation#DiceEquation(java.lang.String)}.
	 */
	@Test
	public void testDiceEquationCtor16() {
		checkDiceEquationCtor("1d4--2", "1d4+2");
	}


	/**
	 * Test method for {@link com.ziroby.dmassist.model.DiceEquation#DiceEquation(java.lang.String)}.
	 */
	@Test
	public void testDiceEquationCtor17() {
		checkDiceEquationCtor("1d4+2+3", "1d4+5");
	}


	/**
	 * Test method for {@link com.ziroby.dmassist.model.DiceEquation#DiceEquation(java.lang.String)}.
	 */
	@Test
	public void testDiceEquationCtor18() {
		checkDiceEquationCtor("1d4++3", "1d4+3");
	}


	/**
	 * Test method for {@link com.ziroby.dmassist.model.DiceEquation#DiceEquation(java.lang.String)}.
	 */
	@Test
	public void testDiceEquationCtor19() {
		checkDiceEquationCtor("-1d4 +3", "-1d4+3");
	}


	/**
	 * Test method for {@link com.ziroby.dmassist.model.DiceEquation#DiceEquation(java.lang.String)}.
	 */
	@Test
	public void testDiceEquationCtor20() {
		checkDiceEquationCtor("-1d4+2", "-1d4+2");
	}

	
	/**
	 * Test method for {@link com.ziroby.dmassist.model.DiceEquation#DiceEquation(java.lang.String)}.
	 */
	@Test
	public void testDiceEquationCtor21() {
		checkDiceEquationCtor("- 2d4+2", "-2d4+2");
	}

	@Test
	public void testDiceEquationCtor22() {
		checkDiceEquationCtor("1", "1");
	}

	@Test
	public void testDiceEquationCtor23() {
		checkDiceEquationCtor("-8", "-8");
	}

	@Test
	public void testDiceEquationCtor24() {
		checkDiceEquationCtor("- 8", "-8");
	}


	/**
	 * @param str
	 * @param expected
	 */
	private void checkDiceEquationCtor(String str, String expected) {
		DiceEquation eq;
		eq = new DiceEquation(str);
		assertEquals(expected, eq.toString());
	}

	/**
	 * Test method for {@link com.ziroby.dmassist.model.DiceEquation#DiceEquation(java.lang.String)}.
	 */
	@Test
	public void testDiceEquationErrors() {
		String[] testString = {
				"1d4+2x",
				"1 1",
				"1d",
				"1dd4+2",
				"2d6 2",
				"3.2d4",
				"1d4d2",
				"1d-4+2",
				"0d4+2",
				"1d0+2",
		};
		DiceEquation eq;
		for (String s : testString) {
			try {
				eq = new DiceEquation(s);
				fail("Should've caused an error: \"" + s + "\", but returned \"" + eq.toString() + "\"");				
			} catch (IllegalArgumentException e) {
				// good; this is a bad string
			}
		}
	}


	/**
	 * Test method for {@link com.ziroby.dmassist.model.DiceEquation#DiceEquation(java.lang.String)}.
	 */
	@Test
	public void testDiceExtendedEquationCtor1() {
		checkDiceEquationCtor("2d8 +1d6", "2d8 + 1d6");
	}


	/**
	 * Test method for {@link com.ziroby.dmassist.model.DiceEquation#DiceEquation(java.lang.String)}.
	 */
	@Test
	public void testDiceExtendedEquationCtor2() {
		checkDiceEquationCtor("2d8 +d6", "2d8 + 1d6");
	}


	/**
	 * Test method for {@link com.ziroby.dmassist.model.DiceEquation#DiceEquation(java.lang.String)}.
	 */
	@Test
	public void testDiceExtendedEquationCtor3() {
		checkDiceEquationCtor("2d8 - 3d6", "2d8 - 3d6");
	}


	/**
	 * Test method for {@link com.ziroby.dmassist.model.DiceEquation#DiceEquation(java.lang.String)}.
	 */
	@Test
	public void testDiceExtendedEquationCtor4() {
		checkDiceEquationCtor("2d8- d6", "2d8 - 1d6");
	}


//	/**
//	 * Test method for {@link com.ziroby.dmassist.model.DiceEquation#DiceEquation(java.lang.String)}.
//	 */
//	@Test
//	public void testDiceExtendedEquationCtor5() {
//		checkDiceEquationCtor("1d5 * 2", "1d5 *2");
//	}
//
//
//	/**
//	 * Test method for {@link com.ziroby.dmassist.model.DiceEquation#DiceEquation(java.lang.String)}.
//	 */
//	@Test
//	public void testDiceExtendedEquationCtor6() {
//		checkDiceEquationCtor("6d6 / 2", "6d6 / 2");
//	}
//
//
//	/**
//	 * Test method for {@link com.ziroby.dmassist.model.DiceEquation#DiceEquation(java.lang.String)}.
//	 */
//	@Test
//	public void testDiceExtendedEquationCtor7() {
//		checkDiceEquationCtor("6d6 /2 + 1d 4", "6d6 / 2 + 1d4");
//	}
//
//
//	/**
//	 * Test method for {@link com.ziroby.dmassist.model.DiceEquation#DiceEquation(java.lang.String)}.
//	 */
//	@Test
//	public void testDiceExtendedEquationCtor8() {
//		checkDiceEquationCtor("3d8 +2 *2 * 3", "3d8+2 *2 *3");
//	}
//
//
//	/**
//	 * Test method for {@link com.ziroby.dmassist.model.DiceEquation#DiceEquation(java.lang.String)}.
//	 */
//	@Test
//	public void testDiceExtendedEquationCtor9() {
//		checkDiceEquationCtor("1d5 * 3 * 4", "1d5 *6");
//	}
//
//
	/**
	 * Test method for {@link com.ziroby.dmassist.model.DiceEquation#DiceEquation(java.lang.String)}.
	 */
	@Test
	public void testDiceEquationRange() {
		DiceEquation eq;
		for (int i=0; i < 50; ++i)
		{
			eq = new DiceEquation("2d4+3");
			assertEquals("2d4+3", eq.toString());
			assertTrue("Value too low: " + eq.value(), eq.value() >= 5);
			assertTrue("Value too high: " + eq.value(), eq.value() <= 11);
			eq.roll();
			assertTrue("Value too low: " + eq.value(), eq.value() >= 5);
			assertTrue("Value too high: " + eq.value(), eq.value() <= 11);
		}
	}
	
	@Test
	public void testTryParseInt()
	{
		assertEquals(new Integer(3), DiceEquation.tryParseInt(" 3 "));
	}


	@Test
	public void testTryParseInt2()
	{
		assertEquals(new Integer(3), DiceEquation.tryParseInt(" +3 "));
	}


	@Test
	public void testTryParseInt3()
	{
		assertEquals(new Integer(-3), DiceEquation.tryParseInt(" -3 "));
	}


	@Test
	public void testTryParseIntError()
	{
	    assertNull(DiceEquation.tryParseInt(" 3f "));
	}
	
	
	@Test
	public void testTryParseIntDie()
	{		
		assertEquals(new Integer(3), DiceEquation.tryParseInt(" 2d1+ 1 "));
	}

}
