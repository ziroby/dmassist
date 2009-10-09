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

import javax.swing.JButton;
import javax.swing.event.TableModelEvent;
import javax.swing.event.TableModelListener;


/**
 * @author Ron Romero
 *
 */
public class NextButton extends JButton implements TableModelListener {

	private static final long serialVersionUID = -5233118550534354723L;
	
	private final EntityDataModel dataModel;
	
	public NextButton(EntityDataModel dataModel) {
		super(Messages.getString("NextButton.0")); //$NON-NLS-1$
		this.dataModel = dataModel;
		
		dataModel.addTableModelListener(this);
		tableChanged(null); // simulate a table change to set enabled status
	}

	public void tableChanged(TableModelEvent arg0) {
		int numRows = dataModel.getRowCount();
		
		if (numRows > 1)
		{
			setEnabled(true);
		}
		else
		{
			setEnabled(false);
		}
	}

}
