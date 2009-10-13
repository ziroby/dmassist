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
package com.ziroby.util;

import com.ziroby.dmassist.model.Entity;

/**
 * Utilities for working with entity abbreviations.  An abbreviation is
 * a short, unique string labeling the Entity.  By default, it is the first
 * character of the Entity's name, followed by a number to make it unique. 
 * But it could be any string, generally a short one.  So for goblins, you
 * could have "GOB1", "GOB2", etc., instead of "G1", "G2"
 * 
 * @see Entity
 * 
 * @author Ron Romero
 *
 */
public class AbbrevUtil {

	/**
	 * Returns the beginning of the string which is alpha
	 * 
	 * @param abbreviation
	 */
	public static String getAplhaPrefix(String abbreviation) 
	{	
		StringBuilder str = new StringBuilder();
		for (int i = 0; 
			i < abbreviation.length() && Character.isLetter(abbreviation.charAt(i));
			++i)
		{
			str.append(abbreviation.charAt(i));
		}
		return str.toString();
	}

}
