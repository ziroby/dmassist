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

/**
 * Various utilities for working with Strings. This class is a candidate for
 * reuse.
 * 
 * @author Ron Romero
 * 
 */
public class StringUtil {

    /**
     * Attempt to parse the given string as an Integer, but don't throw an
     * exception if it's not a valid integer. Instead, returns null if it can't
     * be parsed.
     * 
     * @param text
     *            The string to attempt to parse
     * @return The value of text, or null if it can't be parsed.
     */
    public static Integer tryParseInt(String text) {
        if (text == null)
            return null;

        int n;
        try {
            String t = text.trim();
            int sign = 1;
            if (t.matches("^\\+.*")) {
                t = t.substring(1).trim();
            } else if (t.matches("^-")) {
                sign = -1;
                t = t.substring(1).trim();
            }
            n = Integer.parseInt(t) * sign;
        } catch (NumberFormatException e) {
            // oops, guess we didn't get integers.
            return null;
        }
        return n;
    }
}
