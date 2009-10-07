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

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;

import javax.swing.JTextField;

/**
 * @author Ziroby
 *
 */
public class CommandLine extends JTextField implements KeyListener, ActionListener {

	public CommandLine() {
		this.addKeyListener(this);
		this.setDocument(new LineHistoryDocument());
		document = (LineHistoryDocument) getDocument();
		this.addActionListener(this);
	}
	
	/**
	 * 
	 */
	private static final long serialVersionUID = 3823010430004001526L;
	private final LineHistoryDocument document;

	public void keyPressed(KeyEvent key) {
	}

	public void keyReleased(KeyEvent key) {
		if (key.getKeyCode() == KeyEvent.VK_UP)
		{
			document.gotoPreviousLine();
		}
		if (key.getKeyCode() == KeyEvent.VK_DOWN)
		{
			document.gotoNextLine();
		}
		// TODO Auto-generated method stub
		
	}

	public void keyTyped(KeyEvent key) {
		// TODO Auto-generated method stub
		
	}

	public void actionPerformed(ActionEvent e) {
		// TODO Auto-generated method stub
		document.addLine(e.getActionCommand());
	}
	
}
