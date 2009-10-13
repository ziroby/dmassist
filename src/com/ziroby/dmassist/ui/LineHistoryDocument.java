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
package com.ziroby.dmassist.ui;

import java.util.List;
import java.util.Vector;

import javax.swing.text.BadLocationException;
import javax.swing.text.Document;
import javax.swing.text.PlainDocument;

/**
 * @author Ron Romero
 *
 */
public class LineHistoryDocument extends PlainDocument implements Document {

	List<String> history = new Vector<String>();
	int position = 0;
	
	LineHistoryDocument()
	{
	}
	
	/**
	 * 
	 */
	private static final long serialVersionUID = 935165581555747390L;

	/**
	 * Moves to the previous line in history, after saving the value of the
	 * current line in its correct position in history.
	 */
	public void gotoPreviousLine() {
		if (position > 0)
		{
			try {
				if (position == history.size() && !currentLine().equals(""))
				{					
					history.add("XXX");
					history.set(position, currentLine());
				}
				--position;
				this.remove(0, this.getLength());
				this.insertString(0, history.get(position), null);
			} catch (BadLocationException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
	}

	/**
	 * Moves to the previous line in history, after saving the value of the
	 * current line in its correct position in history.
	 */
	public void gotoNextLine() {
		if (position < history.size())
		{
			try {
				history.set(position, currentLine());
				++position;
				this.remove(0, this.getLength());
				this.insertString(0, history.get(position), null);
			} catch (BadLocationException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
	}

	/**
	 * Action listener to set current line to history and move to end of history
	 * list.  When the text is entered into the JTextField, we get an ActionEvent.
	 * At that time, we want to save the value of the current line.  Iff the current
	 * line is identical to the last line in history, we do not add it.  This removes
	 * adjacent duplicates, but if you select an earlier line, it adds it to the 
	 * end of the history.
	 */
	public void addLine(String line) {
		if (line.trim().equals(""))
		{
			// Don't add blank lines
			return;
		}
		// Add to the end of the history, but only if it's not the same as the 
		// last element in the history.  
		if (history.size() == 0 
                || !line.equals(history.get(history.size()-1)))
		{
			history.add(line);
			position = history.size();		
		}
		else
		{
			position = history.size();
		}
	}

	/**
	 * Returns the entire line.
	 * @throws BadLocationException
	 */
	public String currentLine() {
		try {
			return this.getText(0, this.getLength()).trim();
		} catch (BadLocationException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			return null;
		}
	}

}
