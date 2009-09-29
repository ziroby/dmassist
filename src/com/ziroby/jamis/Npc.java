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

package com.ziroby.jamis;

/**
 * @author rromero
 *
 */
public class Npc
{
    public static native String gen1();
    
    public static String gen()
    {
        if (isLibraryLoaded())
        {
            String s = gen1();
            
            s = s.replaceAll("~I", "<i>");
            s = s.replaceAll("~i", "</i>");
            s = s.replaceAll("~B", "<b>");
            s = s.replaceAll("~b", "</b>");
            
            return s;
        }
        else
        {
            throw exception;
        }
    }
    
    private static boolean libraryLoaded = false;
    private static UnsatisfiedLinkError exception = null;
    
    static {
        try
        {
            System.loadLibrary("DMAssistJNI");
            libraryLoaded = true;
        }
        catch (UnsatisfiedLinkError e)
        {
            exception = e;
            libraryLoaded = false;
        }
    }

    /**
     * If we failed loading the library, gives the exception thrown.
     */
    public static UnsatisfiedLinkError getException() {
        return exception;
    }

    /**
     * Did we succesfully load the link library?
     * 
     */
    public static boolean isLibraryLoaded() {
        return libraryLoaded;
    }

}
