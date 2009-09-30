/*
 *  Die.java
 *  Copyright (C) 2002 Devon D Jones
 *  Modifications Copyright (C) 2009 Ron "Ziroby" Romero
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

import java.util.Random;

/** Abstract class describing a die of any kind
 * @author Soulcatcher
 * @since May 24, 2003
 */
public abstract class Die
{
	/** Random number seed */
	protected static Random rand = new Random();

	/** Holds the rolls of each die */
	protected int[] rolls;

	/** Die modifier */
	protected int modifier;

	/** Number of dice */
	protected int num;

	/** Number of sides */
	protected int sides;

	/**  Number of times rolled */
	protected int timesRolled;

	/** Total from last die roll */
	protected int total;

	/** Roll the die, and get back a value
	 * @return Result of the die roll
	 */
	public abstract int roll();

	/** Writes out the die name (like 2d6+1)
	 * @return Die name
	 */
	@Override
	public abstract String toString();

	/** Sets the random Die object. Allows you to put in a seeded random for better randomness.
	 * @param rand Random
	 */
	public void setRandom(Random rand)
	{
		Die.rand = rand;
	}

	/** Returns the last roll.
	 * @return The last roll
	 */
	public int value()
	{
		return total;
	}

    /**
     * Adds the given value to the modifier of the Die.
     * 
     * @param i the value to add.
     * @author Ziroby
     */
	public void addToModifier(int i)
	{
		modifier += i;
	}
}
