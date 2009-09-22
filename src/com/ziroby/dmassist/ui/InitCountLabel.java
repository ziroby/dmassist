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

import javax.swing.JLabel;
import javax.swing.event.TableModelEvent;
import javax.swing.event.TableModelListener;

import com.ziroby.dmassist.model.EntityList;
import com.ziroby.dmassist.model.InitOrderDataModel;

/**
 * @author Ziroby
 *
 */
public class InitCountLabel extends JLabel implements TableModelListener {

	EntityList dataModel;
	
	public InitCountLabel(InitOrderDataModel dataModel) {
		this.dataModel = dataModel;
		setText(" " + dataModel.getInitCount() + " ");
		dataModel.addTableModelListener(this);
	}


	public void tableChanged(TableModelEvent e) {
		setText(" " + dataModel.getInitCount() + " ");
	}

	private static final long serialVersionUID = -8007621851847525139L;
}
