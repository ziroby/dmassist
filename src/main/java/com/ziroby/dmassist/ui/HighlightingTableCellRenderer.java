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

import java.awt.Color;
import java.awt.Component;
import java.awt.Font;

import javax.swing.JTable;
import javax.swing.table.TableCellRenderer;

import com.ziroby.dmassist.model.EntityList;

/**
 * A renderer that just adds or removes highlighting to a square, then delegates to the
 * old, passed in, renderer.  The highlighting is based on whether it is the current
 * row's "turn".  OK, this is pretty code; it works for any type of renderer you
 * pass in and adds the highlight for that component.
 * 
 * @author Ziroby
 *
 */
public class HighlightingTableCellRenderer
		implements
			TableCellRenderer {
	private final TableCellRenderer oldRenderer;
	HighlightingTableCellRenderer(TableCellRenderer oldRenderer) {
		this.oldRenderer = oldRenderer;
	}

	public Component getTableCellRendererComponent(JTable table,
			Object value, boolean isSelected, boolean hasFocus, 
			int row, int column) {
		Component rendererComputer 
			= oldRenderer.getTableCellRendererComponent(
					table, value, isSelected, hasFocus, row, column);
		int modelRow = table.convertRowIndexToModel(row);
		int modelColumn = table.convertColumnIndexToModel(column);
		final EntityList dataModel = (EntityList) table.getModel();
		if (dataModel.isMyTurn(modelRow))
		{
			rendererComputer.setBackground(Color.YELLOW);
			Font f2 = rendererComputer.getFont().deriveFont(Font.BOLD);
			rendererComputer.setFont(f2);
		}
		else
		{
			rendererComputer.setBackground(null);
		}
		
		rendererComputer.setForeground(Color.BLACK);
		if (modelColumn == EntityDataModel.COLUMN_NUMBER_SUBDUAL)
		{ 
			if (dataModel.getEntity(modelRow).isSubdued())
			{
				addBlueFont(rendererComputer);
			}
		}
		else if (modelColumn == EntityDataModel.COLUMN_NUMBER_HP)
		{
			final Integer hitpoints = dataModel.getEntity(modelRow).getHitpoints();
            if (hitpoints != null && hitpoints <= 0)
			{
				addBlueFont(rendererComputer);
			}
		}
        else if (modelColumn == EntityDataModel.COLUMN_NUMBER_ROUNDS)
        {
            if (dataModel.getEntity(modelRow).isExpired(0))
            {
                addBlueFont(rendererComputer);
            }
        }
		return rendererComputer;
	}
	/**
	 * @param rendererComputer
	 */
	private void addBlueFont(Component rendererComputer) {
		Font f2 = rendererComputer.getFont().deriveFont(Font.BOLD);			
		rendererComputer.setFont(f2);			
		rendererComputer.setForeground(Color.BLUE);
	}
}