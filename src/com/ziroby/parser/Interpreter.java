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

import java.util.Map;

import com.ziroby.dmassist.model.DiceEquation;
import com.ziroby.dmassist.model.Entity;
import com.ziroby.dmassist.model.Entity.DamageType;
import com.ziroby.dmassist.model.EntityList;
import com.ziroby.dmassist.ui.ResultsDisplay;
import com.ziroby.jamis.Npc;

/**
 * @author Ziroby
 *
 */
public class Interpreter implements ParserListener{

	private static final String HELP_TEXT = "<table>" +
            "<tr><td>next</td>                                      <td>go to the next initiative count</td></tr>" +
            "<tr><td>roll &lt;dice equation&gt;</td>                <td>roll the specified dice</td></tr>" +
            "<tr><td>dmg &lt;abbrev&gt; &lt;dice equation&gt;</td>  <td>deal the specified damage</td></tr>" +
            "<tr><td>sub &lt;abbrev&gt; &lt;dice equation&gt;</td>  <td>deal the specified subdual damage</td></tr>" +
            "<tr><td>heal &lt;abbrev&gt; &lt;dice equation&gt;</td> <td>heal the specified amount of hitpoints</td></tr>" +
            "<tr><td>set &lt;abbrev&gt; &lt;attributes&gt;</td>     <td>set attributes</td></tr>" +
            "<tr><td>add &lt;abbrev&gt; &lt;attributes&gt;</td>     <td>add a new character or effect</td></tr>" +
            "<tr><td>npc &lt;options&gt;</td>                       <td>generate an NPC</td></tr>" +
            "<tr><td>help</td>                                      <td>this message</td></tr>" +
            "</table>";
	private EntityList dataModel;
	private ResultsDisplay results;

	public Interpreter(EntityList dataModel, ResultsDisplay results) {
		this.dataModel = dataModel;
		this.results = results;
	}

	public void handleCommand(String command,
			Map<String, String> attributes, String fullLine) {	
		try {
			if ("next".equalsIgnoreCase(command)
					|| "n".equalsIgnoreCase(command))
			{
				dataModel.gotoNextInitCount();
			}
			else if ("roll".equalsIgnoreCase(command)
					|| "r".equalsIgnoreCase(command))
			{
				String directObject = attributes.get("direct object");
				if (directObject == null)
				{
					printError("No direct object for \"roll\"");
				}
				else
				{
					DiceEquation eq = new DiceEquation(directObject);
					results.addLine(command + " " + directObject + " = " + eq.value());
					results.setResult("" + eq.value());
				}
			}
            else if (Entity.stringToDamageType(command) != null)
            {
                damage(command, attributes, Entity.stringToDamageType(command));
            }
            else if ("set".equalsIgnoreCase(command))
            {
                set(command, attributes);
            }
            else if ("add".equalsIgnoreCase(command))
            {
                add(command, attributes);
            }
            else if ("npc".equalsIgnoreCase(command))
            {
                if (!Npc.isLibraryLoaded())
                {
                    printError("NPC library not loaded: " + Npc.getException().getLocalizedMessage());
                }
                else
                {
                    try
                    {
                        String s = Npc.gen(fullLine);
                        results.addLine(s);
                    }
                    catch (Exception e)
                    {
                        printError("Exception while generating NPC: " + e.getLocalizedMessage());
                    }
                }
            }
            else if ("quit".equalsIgnoreCase(command) ||
                    "exit".equalsIgnoreCase(command))
            {
                System.exit(0);
            }
			else
			{
				printError("Unknown command: " + command);
			}
		} catch (RuntimeException e) {
			printError(e);
		}
	}

	private void set(String command, Map<String, String> attributes) {
		attributes.remove("command");
		String directObject = attributes.get("direct object");
		if (directObject == null)
		{
			printError("No direct object for \"" + command + "\"");
		}
		else
		{
			attributes.remove("direct object");
			Entity e = dataModel.findByAbbrev(directObject);
			if (e == null)
			{
				printError("Can't find entity \"" + directObject + "\"");
			}
			else
			{
				String s = set(e, attributes);
                if (s != null)
                {
                    results.addLine("set \"" + e.getName() + "\" " + s);
                }
			}
		}
	}
    
    
    
    private String add(String command, Map<String, String> attributes)
    {
        String s = null;
        attributes.remove("command");
        String directObject = attributes.get("direct object");
        if (directObject == null)
        {
            printError("No direct object for \"" + command + "\"");
        }
        else
        {
            attributes.remove("direct object");
            Entity e = new Entity();
            e.setName(directObject);
            s = set(e, attributes);
            if (s != null)
            {
                dataModel.addEntity(e);
                results.addLine("add \"" + e.getName() + "\" " + s);
            }
        }        
        return s;
    }

	private String set(Entity e, Map<String, String> attributes) {
		StringBuilder s = new StringBuilder();
		boolean setResult = false;
		if (attributes.size() == 1)
		{
			setResult = true;
		}
		for(Map.Entry<String, String> attr : attributes.entrySet())
		{
			if (attr.getKey().equalsIgnoreCase("hp")
					|| attr.getKey().equalsIgnoreCase("hitpoints")
					|| attr.getKey().equalsIgnoreCase("hitpoint"))
			{
				e.setHitpoints(diceAttribute(s, attr, setResult));
			}
			else if (attr.getKey().equalsIgnoreCase("init"))
			{
				e.setInitRoll(diceAttribute(s, attr, setResult));
			}
			else if (attr.getKey().equalsIgnoreCase("subdual")
					|| attr.getKey().equalsIgnoreCase("sub"))
			{
				e.setSubdual(diceAttribute(s, attr, setResult));
			}
			else if (attr.getKey().equalsIgnoreCase("rnds")
					|| attr.getKey().equalsIgnoreCase("rnd")
					|| attr.getKey().equalsIgnoreCase("rounds")
					|| attr.getKey().equalsIgnoreCase("round"))
			{
				e.setRoundsLeft(diceAttribute(s, attr, setResult));
			}

			else
			{
				printError("Unknown attribute: " + attr.getKey() + " ( = " + attr.getValue() + ")");
                return null;
			}
		}
		
		return s.toString().trim();
			
	}

	/**
	 * Handles an attribute which can be a die value (or int constant).  Also
	 * logs the attribute to the StringBuilder.
	 * @param setResult 
	 * 
	 */
	private int diceAttribute(StringBuilder s, Map.Entry<String, String> attr, boolean setResult) {
		DiceEquation eq = new DiceEquation(attr.getValue());
		s.append(eq.toLongString());
		s.append(" ");
		s.append(attr.getKey());
		s.append(' ');
		
		if (setResult)
		{
			results.setResult("" + eq.value());			
		}
		return eq.value();
	}

	/**
	 * @param command
	 * @param attributes
	 */
	private void damage(String command, Map<String, String> attributes, DamageType type) {
		String directObject = attributes.get("direct object");
		String indirectObject = attributes.get("indirect object");
		if (directObject == null)
		{
			printError("No direct object for \"" + command + "\"");
		}
		else if (indirectObject == null)
		{
			printError("No indirect object for \"" + command + "\"");
		}
		else
		{
//					results.setCommand(command + " DO: \"" + directObject + "\" IO: \"" + indirectObject + "\"");
            DiceEquation damage = null;
            try
            {
                damage = new DiceEquation (indirectObject);
            }
            catch (IllegalArgumentException e)
			{
				printError("Invalid damage amount: \"" + e.getLocalizedMessage() + "\"");
                damage = null;
			}
			
            if (damage != null)
			{
				Entity e = dataModel.findByAbbrev(directObject);
				if (e == null)
				{
					printError("Can't find entity \"" + directObject + "\"");
				}
				else
				{
					results.setResult("" + damage.value());
                    results.addLine(Entity.damageTypeToString(type) + " \""
                            + e.getName() + "\" by " + damage.toLongString());
					e.damage(type, damage.value());
				}
			}
		}
	}

    public void printError(Exception e) {
		printError(e.getLocalizedMessage());
		e.printStackTrace();
		
	}

	public void printError(String msg)
	{
		results.addLine("Error: " + msg);
		results.setResult(null);
	}
}
