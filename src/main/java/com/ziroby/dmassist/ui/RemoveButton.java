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
import javax.swing.JTable;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;

/**
 * @author Ziroby
 *
 */
public class RemoveButton extends JButton implements ListSelectionListener {

	private static final long serialVersionUID = -3732232740041909571L;

	private final JTable table;
	
	public RemoveButton(JTable table) {
		super(Messages.getString("RemoveButton.0")); //$NON-NLS-1$
	
		this.table = table;
		table.getSelectionModel().addListSelectionListener(this);
		valueChanged(null); // Set enabled by simulated selection change event
	}

	public void valueChanged(ListSelectionEvent arg0) {
		int selectedRow = table.getSelectedRow();
		
		if (selectedRow == -1)
		{
			setEnabled(false);
		}
		else
		{
			setEnabled(true);
		}
	}
	
}
