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

import java.awt.Component;
import java.awt.Dimension;
import java.awt.Font;

import javax.swing.BorderFactory;
import javax.swing.Box;
import javax.swing.BoxLayout;
import javax.swing.JEditorPane;
import javax.swing.JLabel;
import javax.swing.JScrollPane;
import javax.swing.text.BadLocationException;
import javax.swing.text.Document;
import javax.swing.text.JTextComponent;

/**
 * @author Ziroby
 *
 */
public class ResultsBox extends Box implements ResultsDisplay {

	public ResultsBox() {
		super(BoxLayout.LINE_AXIS);
		
	    cmdDisplay = new JEditorPane();
	    cmdDisplay.setMinimumSize(new Dimension(80, 30));
	    cmdDisplay.setEditable(false);
	    JScrollPane scrollPane = new JScrollPane(cmdDisplay); 
		new JLabel();
		resultDisplay = new JLabel(" ");
		resultDisplay.setFont(new Font("Serif", Font.BOLD, 24));
	    resultDisplay.setBorder(BorderFactory.createEtchedBorder());
	    resultDisplay.setAlignmentX(Component.CENTER_ALIGNMENT);
//	    resultDisplay.setVisible(false);

	    this.add(scrollPane);
//	    this.add(Box.createHorizontalStrut(5));
//	    this.add(objDisplay);
//	    this.add(Box.createHorizontalStrut(5));
//	    this.add(resultDisplay);
	}

	/**
	 * 
	 */
	private static final long serialVersionUID = -5288264204199798064L;
	private JTextComponent cmdDisplay;
	private JLabel resultDisplay;

	public void addLine(String s) {
		Document doc = cmdDisplay.getDocument();
		try {
			doc.insertString(doc.getLength(), s + "\n", null);
		} catch (BadLocationException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

//		cmdDisplay.setText(s);		
	}


	public void setResult(String s) {		
		if (s == null || s.trim().equals(""))
		{
			resultDisplay.setVisible(false);			
		}
		else
		{
			resultDisplay.setText(" " + s + " ");
			resultDisplay.setVisible(true);
		}
	}
	/**
	 * @return the resultDisplay
	 */
	public final JLabel getResultDisplay() {
		return resultDisplay;
	}
}
