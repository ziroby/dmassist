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
package com.ziroby.parser;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.HashMap;
import java.util.Map;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

import javax.swing.JTextField;

import com.ziroby.dmassist.ui.ResultsDisplay;

/**
 * @author Ziroby
 *
 */
public class Parser implements ActionListener{

    private static final String REGEX_COMMAND = "\\s*(\\p{Alpha}+)\\s*(.*)";
	private static final String REGEX_ATTRIB = "\\s*(\\p{Alpha}+)\\s*[:=]?\\s*(.*)";
	private static final String REGEX_ABBREV = "\\s*(\\p{Alpha}\\p{Digit}+)\\s+(.*)";
    private static final String REGEX_WORD = "\\s*(\\p{Alpha}[\\p{Alpha}\\p{Digit}]*)\\s*(.*)";

	// This one's complicated, so we split it up
	private static final String SUBREGEX_DIE = "[\\-\\+]?\\s*\\p{Digit}*\\s*[Dd]\\s*\\p{Digit}+";
	private static final String SUBREGEX_DIE_OR_CONST = "(?:" + SUBREGEX_DIE + "|\\p{Digit}+"+ ")";
	private static final String REGEX_DICE 
		= "\\s*("  // capturing group 
			+ SUBREGEX_DIE_OR_CONST + "\\s*"    // 2d8 
			+ "(?:" // non-capturing group
				+ "\\s*[\\-\\+\\s]+\\s*" + SUBREGEX_DIE_OR_CONST + "\\s*"  // + 3d4 or + 3
			+ ")*" 
		+ ")" // end capturing group
		+ "\\s*(.*)"; // ...and the rest
		
	
	public static final String TAG_INDIRECT_OBJECT = "indirect object";
	public static final String TAG_DIRECT_OBJECT = "direct object";
	public static final String TAG_COMMAND = "command";

	private ParserListener listener;
	private ResultsDisplay resultsBox;

	private Pattern commandPattern  = Pattern.compile(REGEX_COMMAND);
	private Pattern diePattern = Pattern.compile(REGEX_DICE);
    private Pattern abbrevPattern = Pattern.compile(REGEX_ABBREV);
    private Pattern wordPattern = Pattern.compile(REGEX_WORD);
	private Pattern attribPattern = Pattern.compile(REGEX_ATTRIB);

	public Parser(ParserListener listener, ResultsDisplay resultsBox) {
		this.listener = listener;
		this.resultsBox = resultsBox;
		// TODO Auto-generated constructor stub
	}

	public void parse(String text) {
		resultsBox.addLine("> " + text);
		// TODO Auto-generated method stub
	
		Map<String, String> phrases = new HashMap<String, String>();
		regexParse(text, phrases);
		
		this.listener.handleCommand(phrases.get(TAG_COMMAND), phrases);
	}


	private void regexParse(String text1, Map<String, String> phrases) {
		String text = text1;	// Just so the param is final & Eclipse stops complaining
		Matcher commandMatcher = commandPattern.matcher(text);
		if (!commandMatcher.matches())
		{
			phrases.put(Parser.TAG_COMMAND, "");
		} 
		else
		{
			phrases.put(Parser.TAG_COMMAND, commandMatcher.group(1));
			text = commandMatcher.group(2);
		}

		Matcher dieMatcher = diePattern.matcher(text);
		if (dieMatcher.matches())
		{
			phrases.put(TAG_DIRECT_OBJECT, dieMatcher.group(1));
			text = dieMatcher.group(2);
		}
		else // Because you can't have a die as a direct object, then an indirect object
		{
			Matcher abbrevMatcher = abbrevPattern.matcher(text);
            Matcher wordMatcher = wordPattern.matcher(text);
			if (abbrevMatcher.matches())
			{
                phrases.put(TAG_DIRECT_OBJECT, abbrevMatcher.group(1));
                text = abbrevMatcher.group(2);              
			}
            else if (wordMatcher.matches())
            {
                phrases.put(TAG_DIRECT_OBJECT, wordMatcher.group(1));
                text = wordMatcher.group(2);                              
            }
			dieMatcher = diePattern.matcher(text);
			if (dieMatcher.matches())
			{
				phrases.put(TAG_INDIRECT_OBJECT, dieMatcher.group(1));
				text = dieMatcher.group(2);
			}

		}

		if (!text.trim().isEmpty())
		{
			// Now we go hunting for attribute/value pairs
			String tag = null;
			String dice = null;
			Matcher attribMatcher;
			boolean matched = true;
			if (phrases.containsKey(TAG_INDIRECT_OBJECT))
			{
				text = phrases.get(TAG_INDIRECT_OBJECT) + " " + text;
				phrases.remove(TAG_INDIRECT_OBJECT);
			}
			while(!text.trim().isEmpty() && matched)
			{
				matched = false;
				attribMatcher = attribPattern.matcher(text);
				dieMatcher = diePattern.matcher(text);
				// We have to check tag, because two tags in a row doesn't make sense.
				if (attribMatcher.matches() && tag == null)
				{
					tag = attribMatcher.group(1);
					text = attribMatcher.group(2);
					matched = true;
				}
				else if (dieMatcher.matches() && dice == null)
				{
					dice = dieMatcher.group(1);
					text = dieMatcher.group(2);
					matched = true;
				}

				if (tag != null && dice != null)
				{
					phrases.put(tag, dice.trim());
					tag = dice = null;
				}
			}
		}
		
		if (!text.trim().isEmpty())
		{
			throw new IllegalArgumentException("Too much in line: " + text);
		}
	}

	public void actionPerformed(ActionEvent e) {
		JTextField source = (JTextField) e.getSource();
		parse(source.getText());
		source.setText("");
		
	}
}
