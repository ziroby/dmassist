/*
 *  Dice.java
 *  Copyright (C) 2002 Devon D Jones
 *  modifications Copyright (C) 2009 Ron "Ziroby" Romero
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 *  The author of this program grants you the ability to use this code
 *  in conjunction with code that is covered under the Open Gaming License
 *
 */
package com.ziroby.dmassist.model;

/** A normal die
 * @author Soulcatcher
 * @since May 24, 2003
 */
public class Dice extends Die
{
	/** Die modifier */
//	private int aModifier;

	private int sign = 1;

	/** Constructor for the Dice object
	 * @param num Number of dice
	 * @param sides Number of sides
	 * @param modifier Modifier to the die roll
	 */
	public Dice(int num, int sides, int modifier)
	{
		this.num = num;
		this.sides = sides;
		this.modifier = modifier;
		rolls = new int[num];
		roll();
	}

	/** Constructor for the Dice object
	 * @param num Number of dice
	 * @param sides Number of sides per die
	 */
	public Dice(int num, int sides)
	{
		this(num, sides, 0);
	}

	/**
     * Create from a string as given by toString.
     * 
     * @param s
     *            A string in nds+m format.
     * 
     * @throws IllegalArgumentException
     *             if the string is not a valid dice value (nds+m), or if number
     *             or sides is zero.
     */
	public Dice(String s) {
		try
		{
			String[] parts = s.trim().split("\\s*d\\s*", 2);
			if (parts.length != 2)
			{
				badFormat(s);
			}

			if (parts[0].trim().equals("") || parts[0].trim().equals("+"))
			{
				this.num = 1;
			}
			else if (parts[0].trim().equals("-"))
			{
				this.num = -1;
			}
			else
			{
				this.num = Integer.parseInt(parts[0]);
			}

			int modifierSign = 1;
			if (parts[1].matches(".*\\+.*"))
			{
				parts = parts[1].split("\\s*\\+\\s*", 2);
				if (parts.length != 2)
				{
					badFormat(s);
				}
			}
			else if(parts[1].matches(".*\\-.*"))
			{
				parts = parts[1].split("\\s*-\\s*", 2);
				if (parts.length != 2)
				{
					badFormat(s);
				}
				modifierSign = -1;
			}
			else
			{
				parts[0] = parts[1];
				parts[1] = "0";
			}

			this.sides = Integer.parseInt(parts[0]);
			this.modifier = Integer.parseInt(parts[1]) * modifierSign;

			if (this.num < 0)
			{
				this.num = -this.num;
				this.sign  = -1;
			}
			
			if (this.sides <= 0 || this.num <= 0)
			{
				throw new IllegalArgumentException("Sides and numbers must be positive: \"" + s + "\"");
			}
		}
		catch (NumberFormatException e)
		{
			throw new IllegalArgumentException("Illegal die format: \"" + s + "\"", e);
		}

		rolls = new int[num];
		roll();		
	}

	private void badFormat(String s) {
		throw new IllegalArgumentException("Illegal die format: \"" + s + "\" should be \"nds+m\" format");
	}

	/**
     * Rolls the die, and returns the result. I made it final as it's called
     * from the constructor.
     * 
     * @return Result of the die roll
     */
    @Override
	public final int roll()
	{
		int value = 0;
		int i;
		total = 0;

		for (i = 0; i < num; i++)
		{
			rolls[i] = rand.nextInt(sides) + 1;
			value = rolls[i] + value;
		}

		total = value + modifier;
		timesRolled++;

		return total;
	}

	/**
     * Name of the die in the nds+m format, with a minus sign (-) for negative
     * dice.
     * 
     * @return Name of the die
     */
	@Override
	public String toString()
	{
		StringBuilder s = new StringBuilder();
		
		if (sign < 0)
		{
			s.append("-");
		}
		
		return getStringNoSign(s);
	}

	/**
     * The string representation without the sign.
	 */
	private String getStringNoSign(StringBuilder s) {
		if (num != 0)
		{
			s.append(num + "d" + sides);
		}
		
		if (modifier == 0)
		{
			;
		}
		else if (modifier > 0)
		{
			if (num != 0)
				s.append('+');
			s.append(modifier);
		}
		else
		{
			s.append("-" + -modifier);			
		}
		
		return s.toString();
	}

	/**
     * Gets the plus or minus value of the die.
     * 
	 * @return 1 for positive, -1 for negative.
	 */
	public final int getSign() {
		return sign;
	}

    /**
     * The string representation of the dice, with a plus (+) or minus (-) for
     * the sign.
     * 
     * @return
     */
	public Object toStringWithSign() {
		StringBuilder s = new StringBuilder();
		
		if (sign < 0)
		{
			s.append(" - ");
		}
		else
		{
			s.append(" + ");
		}
			
		
		return getStringNoSign(s);
	}

    /**
     * Tells if this is really a constant, i.e., not a dice at all, but just
     * holding a constant value.  Constants are represented internally as
     * num = 0.
     * 
     * @return
     */
	public boolean isConstant() {
		return num == 0;
	}
}
