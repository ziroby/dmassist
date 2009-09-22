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
 * @author Ziroby
 *
 */
public class DiceEquation extends Die {

	public static final String REGEX = null;
	List<Dice> dice = new Vector<Dice>();
	
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

	public Object toLongString() {
		StringBuilder s = new StringBuilder();
		
		s.append(this.toString());
		if (!isConstant())
		{
			s.append("(" + value() + ")");
		}
		return s.toString();
	}

	private boolean isConstant() {
		return (dice.size() == 1 && dice.get(0).isConstant());
	}
}
