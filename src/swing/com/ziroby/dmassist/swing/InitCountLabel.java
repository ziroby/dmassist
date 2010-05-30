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
package com.ziroby.dmassist.swing;

import java.awt.Component;
import java.awt.Font;

import javax.swing.BorderFactory;
import javax.swing.JLabel;

import com.ziroby.dmassist.model.EntityList;
import com.ziroby.util.Listener;
import com.ziroby.util.ObjectEvent;

/**
 * @author Ron Romero
 *
 */
public class InitCountLabel extends JLabel implements Listener {

	EntityList dataModel;
	
	public InitCountLabel(EntityList dataModel) {
		this.dataModel = dataModel;
		setFont(new Font("Serif", Font.BOLD, 24));
        setBorder(BorderFactory.createEtchedBorder());
        setAlignmentX(Component.CENTER_ALIGNMENT);
		setText(" " + dataModel.getInitCount() + " ");
		dataModel.addListener(this);
	}

    @Override
    public void objectChanged(ObjectEvent event) {
        
		final Integer initCount = dataModel.getInitCount();
        if (initCount == null)
        {
            setText("  ");            
        }
        else
        {
            setText(" " + initCount + " ");
        }
    }

	private static final long serialVersionUID = -8007621851847525139L;
}
