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
package com.ziroby.dmassist.parser;

import java.util.Map;

/**
 * Something that can respond to the events from a Parser.  The Parser doesn't
 * actually know the class of the Interpreter.  Rather, it is initialized
 * with a ParserListener, and gives its results to the ParserListener.
 * 
 * @author Ron Romero
 *
 */
public interface ParserListener {
	public void handleCommand(String command, 
			Map<String, String> attributes, String fullLine);
    
    public void printError(Exception e);
    
    public void printError(String msg);
}
