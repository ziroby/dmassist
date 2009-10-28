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

import javax.swing.JFrame;

/**
 * @author Ron Romero
 *
 */
public class Main {

	public static final String VERSION = "1.2";


	static void createAndShowGUI() {
	//Create and set up the window.
	//JFrame frame = new JFrame("HelloWorldSwing");
	JFrame frame = new InitOrderFrame();
    frame.setVisible(true);
	}


	/**
	 * @param args
	 */
	public static void main(String[] args) {
	       javax.swing.SwingUtilities.invokeLater(new Runnable() {
	            public void run() {
	                createAndShowGUI();
	            }
	       });
	}

}
