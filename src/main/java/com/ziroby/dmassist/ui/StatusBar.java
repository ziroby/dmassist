/*
 *   Copyright 2009 Ron "Ziroby" Romero
 * 
 *   This file is part of dmassist.
 *
 *   dmassist is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   dmassist is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with dmassist.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
package com.ziroby.dmassist.ui;

import java.awt.Component;
import java.awt.SystemColor;

import javax.swing.BorderFactory;
import javax.swing.Box;
import javax.swing.BoxLayout;
import javax.swing.JComponent;
import javax.swing.JLabel;
import javax.swing.border.BevelBorder;
import javax.swing.border.Border;

/**
 * A small line of controls at the bottom of the window. 
 * 
 * Thanks to Colin Bell see http://www.java2s.com/Code/Java/Swing-Components/Statusbarcomponent.htm
 *
 * @author rromero
 *
 */
public class StatusBar extends Box {

    /**
     * This is the box that actually holds the components. We need this so that
     * we can add a little buffer below the components.
     */
    private Box componentBox = Box.createHorizontalBox();

    /**
     * The border applied to child components.
     */
    private static final Border componentBorder = 
        BorderFactory.createCompoundBorder(
            BorderFactory.createBevelBorder(BevelBorder.LOWERED),
            BorderFactory.createEmptyBorder(0, 3, 0, 3));
    
    /**
     * Basic constructor.
     */
    public StatusBar() {
        super(BoxLayout.Y_AXIS);
        
        super.add(componentBox);
        super.add(Box.createVerticalStrut(5));
        
        this.setBackground(SystemColor.control);
    }

    /**
     * Adds the given label to the status bar.
     * 
     */
    public void addLabel(JLabel label) {
        add(label);
    }

    @Override
    public Component add(Component comp) {
        if (comp instanceof JComponent)
        {
            ((JComponent) comp).setBorder(componentBorder);
        }
        componentBox.add(Box.createHorizontalStrut(5));
        componentBox.add(comp);

        return comp;
    }
    
    /**
     * Finished off the box by adding the glue at the end.
     */
    public void addGlue() {
        componentBox.add(Box.createHorizontalGlue());
        
    }
}
