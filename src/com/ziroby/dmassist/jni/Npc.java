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

package com.ziroby.dmassist.jni;

/**
 * A connection to Jamis Buck's NPC Gen, used to generate random NPCs.
 * Outputs a stat block defining the NPC.
 * The interface is very similar to the command-line version of NPC Gen.
 * It uses flags and parameters to define what type of NPC to create and
 * what open to use.
 * 
 * If the native library is not available, this class is defined to fail
 * gracefully.
 * 
 * @author Ron Romero
 *
 */
public class Npc extends JniLibrary
{
    private static native String gen1();

    private static native String gen2(String[] params);
    
    /**
     * Generate an NPC with default parameters.
     * 
     * @return
     */
    public static String gen()
    {
        checkLibraryLoaded();
        
        return doMarkup(gen1());
    }

    /**
     * Generate an NPC with the given parameters. Use -help to get info on the
     * parameters.
     * 
     * The returned stat block has embedded formatting characters. Stuff like ~I
     * and ~i to turn on and off italics.  Use {@link #doMarkup(String)} to translate
     * into HTML.
     * 
     * @param params
     *            each word in the parameter, passed in like parameters on the
     *            command line.
     * @return A stat block defining the NPC.
     */
    public static String gen(String[] params)
    {
        checkLibraryLoaded();
        
        return doMarkup(gen2(params));
    }

    /**
     * Generates an NPC with options described in the given command line. The
     * command line should be a series of space-seperated words, much like an
     * unprocessed Unix command line.
     * 
     * @param commandLine
     *            The command line to process. Use -help to get details.
     * 
     * @return A stat block for an NPC. Use {@link #doMarkup(String)} to
     *         translate into HTML.
     * 
     */
    public static String gen(String commandLine)
    {
        checkLibraryLoaded();
        
        String[] params = commandLine.split("\\s");
        return doMarkup(gen2(params));
    }
    /**
     * Does the markup modifications for the given string, which should be
     * output from NPC Gen.
     * 
     * @param s
     * @return
     */
    private static String doMarkup(String s) {
        if (s == null) return s;
//        s = s.replaceAll("<", "&lt;");
//        s = s.replaceAll(">", "&gt;");
        
        s = s.replaceAll("\n\n", "<p>");
        s = s.replaceAll("~I", "<i>");
        s = s.replaceAll("~i", "</i>");
        s = s.replaceAll("~B", "<b>");
        s = s.replaceAll("~b", "</b>");
        return s;
    }
    
    static {
        tryLoadLibrary("DMAssist");
        // System.loadLibrary("DMAssistJNI");
    }

}
