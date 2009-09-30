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

import java.util.List;
import java.util.Vector;

import com.ziroby.util.StringUtil;

/**
 * A series of {@link com.ziroby.dmassist.die Die}, connected into a
 * mathmatical formula. Right now, we only do the summation of dice. Something
 * like "3+ 2d6+2 + 1d4+1".
 * 
 * @author Ziroby
 * 
 */
public class DiceEquation extends Die {

	public static final String REGEX = null;

    List<Dice> dice = new Vector<Dice>();
	
    /**
     * Constucts the dice from the given <code>String</code>.
     * 
     * @param str
     *            The string representation of the <code>Dice Equation</code>.
     * 
     * @throws IllegalArgumentException
     *             If the string is not a correctly formatted
     *             <code>DiceEquation</code>.
     */
	public DiceEquation(final String str) {
		
		String s;
		s = str.replaceAll("\\s*-\\s*-\\s*", "+");
		s = s.replaceAll("\\s*-\\s*", "+-");
		s = s.replaceAll("\\s*-\\s*-\\s*", "+");
		s = s.replaceAll("\\s*\\+\\s*\\+\\s*", "+");
		
		Dice lastDice = null;
		for (String element : s.split("\\s*\\+\\s*")) {
			
			if (element.matches("^\\s*[-+]?\\s*[0-9]+\\s*$"))
			{
				if (lastDice != null)
				{
					lastDice.addToModifier(StringUtil.tryParseInt(element));
					lastDice.roll();
				}
				else
				{
					// Make a "constant" die.
					lastDice = new Dice(0, 1, StringUtil.tryParseInt(element));
					dice.add(lastDice);
				}
			}
			else if (element.length() == 0)
			{
				// do nothing				
			}
			else
			{
				lastDice = new Dice(element);
				dice.add(lastDice);
			}
		}
	}

	/**
     * Generates a new random value for the equation.
     * 
	 * @see com.ziroby.dmassist.model.Die#roll()
	 */
	@Override
	public int roll() {
		int accumulator=0;
		for (Dice die : dice) {
			accumulator += die.roll();
		}
		return accumulator;
	}

	/**
     * The canonical format of the string representation.  
     * 
	 * @see com.ziroby.dmassist.model.Die#toString()
	 */
	@Override
	public String toString() {
		StringBuilder s = new StringBuilder();
		for (Dice die : dice) {
			if (s.length() > 0)
			{
				s.append(die.toStringWithSign());
			}
			else
			{
				s.append(die.toString());
			}
		}
		return s.toString();
	}

	/**
     * The number "rolled up". This value will not change until/unless
     * #roll is called.
     * 
     * @see com.ziroby.dmassist.model.Die#value()
     */
	@Override
	public int value() {
		int accumulator=0;
		for (Dice die : dice) {
			accumulator += die.value();
		}
		return accumulator;
	}

    /**
     * Attempts to parse the given string as a <code>DiceEquation</code> and,
     * if that works, returns the {@link value}.
     * 
     * @param text
     *            The string representation to try to parse.
     * @return The value of the equation (randomly generated), or null if it
     *         couldn't be parsed.
     */
	public static Integer tryParseInt(String text) {
	
		if (text.length() == 0)
		{
			return null;
		}
		else if (text.trim().matches("^[+-]?\\s*\\d+\\s*$"))
		{
			return StringUtil.tryParseInt(text);
		}

        DiceEquation eq = null;
        try
        {
            eq = new DiceEquation(text);
        }
        catch (IllegalArgumentException e)
        {
            // Guess that didn't work.
            return null;
        }
		
		return eq.value();
	}

    /**
     * A string representation, with the formula, and the value of each die in
     * parenthesis. Something like "2 + 2d6+1 - 1d4-1(5)".
     * 
     * @return the string representation with values.
     */
	public Object toLongString() {
		StringBuilder s = new StringBuilder();
		
		s.append(this.toString());
		if (!isConstant())
		{
			s.append("(" + value() + ")");
		}
		return s.toString();
	}

    /**
     * Whether there is a random component to this equation.  That is, is
     * there any random component.
     * 
     */
	private boolean isConstant() {
		return (dice.size() == 1 && dice.get(0).isConstant());
	}
}
