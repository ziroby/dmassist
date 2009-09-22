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

import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.Toolkit;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;

import javax.swing.BorderFactory;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JWindow;

/**
 * @author Ziroby
 *
 */
public class AboutBox extends JWindow {

	private static final String TEXT = 
		"<html><H1><center>DM Assist " +
		"<small>v" + Main.VERSION + "</small>" + 
		"</center></H1>" +
//		"<p>" +
//		"<center>INTERNAL USE -- NOT A RELEASE<br>" +
//		"Not to be distributed<br>" +
//		"All rights reserved</center>" +
		"<p>" +
		"<center>Copyright &copy; 2009 Ron Romero</center></br>" +
		"<p><center><small>This program comes with ABSOLUTELY NO WARRANTY.</small><p><p>" +
        "<small>This is free software, and you are welcome to redistribute it<br>" +
		"under certain conditions; see \"Help -> License...\" for details.</small></center>" +
		"<p><p><small>DM Assist contains:<p>" +
		"<ul>" +
		"<li>portions from GMGen/PCGen, copyright &copy; 2002 Devon D. Jones</li>" +
		"<li><left>jYaml, copyright &copy; 2005, Yu Cheung Ho</left></li>" +
		"</ul></small>" +		
		"<p>&nbsp;</html>";

	AboutBox()
	{
		JPanel panel = new JPanel();
		panel.setBorder(BorderFactory.createEtchedBorder());
		getContentPane().add(panel, BorderLayout.CENTER);
		
		// from http://www.javaworld.com/javaworld/javatips/jw-javatip104.html
		JLabel label = new JLabel(TEXT);
		panel.add(label, BorderLayout.CENTER);
		pack();
        Dimension screenSize =
        	Toolkit.getDefaultToolkit().getScreenSize();
        Dimension labelSize = label.getPreferredSize();
        setLocation(screenSize.width/2 - (labelSize.width/2),
        		screenSize.height/2 - (labelSize.height/2));        
          
        addMouseListener(new MouseAdapter()
        {
            @Override
			public void mousePressed(MouseEvent e)
            {
                setVisible(false);
                dispose();
            }
        });		
	}
	
	/**
	 * 
	 */
	private static final long serialVersionUID = 2359174457304044436L;

}
