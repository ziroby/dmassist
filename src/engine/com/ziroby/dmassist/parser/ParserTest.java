/**
 * Copyright 2009 Ron "Ziroby" Romero
 * All Rights Reserved
 */
package com.ziroby.dmassist.parser;

import java.util.Map;
import java.util.SortedSet;
import java.util.TreeSet;

import junit.framework.TestCase;

import org.junit.Before;
import org.junit.Test;

import com.ziroby.dmassist.model.ResultsDisplay;

/**
 * @author Ron Romero
 *
 */
public class ParserTest extends TestCase {
	
	public static class MockParserListener implements ParserListener {

		private String command;
		private Map<String, String> attributes;

		public void handleCommand(String command1, Map<String, String> attributes1,
                String fullLine) {
			this.command = command1;
			this.attributes = attributes1;
		}
		
		public String getCommandString()
		{
			StringBuilder s = new StringBuilder();
			
			s.append(command);
			s.append(' ');
			
			SortedSet<String> tags = new TreeSet<String>();
			tags.addAll(attributes.keySet());
			
			for (String tag : tags) {
				s.append(tag + "=" + attributes.get(tag)+" ");
			}
			
			return s.toString().trim();
		}

        public void printError(Exception e) {
            // TODO Auto-generated method stub
            
        }

        public void printError(String msg) {
            // TODO Auto-generated method stub
            
        }
	}

	MockParserListener listener = null;
	Parser parser = null;
	private ResultsDisplay display;
	
	/**
	 * @throws java.lang.Exception
	 */
	@Override
	@Before
	public void setUp() throws Exception {
		listener = new MockParserListener();		
		display = new ParserInterpreterTest.MockResultsDisplay();
		parser = new Parser(listener, display);		
	}

	/**
	 * Test method for {@link com.ziroby.parser.Parser#parse(java.lang.String)}.
	 */
	@Test
	public final void testParse() {
		parser.parse("next");
		assertEquals("next command=next", listener.getCommandString());
	}

	@Test
	public final void testRoll() {
		parser.parse("roll 2d6 + 2d6 + 3");
		assertEquals("roll command=roll direct object=2d6 + 2d6 + 3", listener.getCommandString());
	}
	
	@Test
	public final void testDamage()
	{
		parser.parse("roll g1 2d6 + 2d6 + 3");
		assertEquals("roll command=roll direct object=g1 indirect object=2d6 + 2d6 + 3", listener.getCommandString());
	}
	
	@Test
	public final void testSet()
	{
		parser.parse("set W5 18 hp subdual:43 init=25");
		assertEquals("set command=set direct object=W5 hp=18 init=25 subdual=43", listener.getCommandString());
	}
	@Test
	public final void testSet2()
	{
		parser.parse("set W5 2d5 hp subdual:3 d 6 init=  d  9");
		assertEquals("set command=set direct object=W5 hp=2d5 init=d  9 subdual=3 d 6", listener.getCommandString());
	}
	public final void testSet3()
	{
		parser.parse("set o hp 3d6 + 1d5 + 12");
		assertEquals("set command=set direct object=o hp=3d6 + 1d5 + 12", listener.getCommandString());
	}
	
	
}
