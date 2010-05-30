/*
 *   Copyright 2010 Ron "Ziroby" Romero
 * 
 *   This file is part of dmassist-engine.
 *
 *   dmassist-engine is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   dmassist-engine is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with dmassist-engine.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

package com.ziroby.dmassist.parser;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Collection;
import java.util.List;

import com.ziroby.dmassist.model.Entity;
import com.ziroby.dmassist.model.EntityList;
import com.ziroby.util.AbstractListenable;
import com.ziroby.util.Listener;

public class MockDataModel extends AbstractListenable 
    implements EntityList {

	private Entity entity;

	public MockDataModel()
	{
		reset();
	}

	/**
	 * 
	 */
	public void reset() {
		entity = new Entity();
		entity.setAbbreviation("s1");
		entity.setName("Sample");
		entity.setHitpoints(64);
		entity.setSubdual(32);
	}
	
	public void addEntities(Collection<Entity> list) {
        // Dummy Test Method
	}

	public void addEntity(Entity entity1) {
        // Dummy Test Method
	}

	public void clear() {
        // Dummy Test Method
	}

	public Entity findByAbbrev(String abbrev) {
		return entity;
	}

	public Collection<Entity> getEntities() {
		return null;
	}

	public Entity getEntity(int row) {
		return null;
	}

	public Integer getInitCount() {
		return 0;
	}

	public void gotoNextInitCount() {
        // Dummy Test Method
	}

	public void importFile(File file) throws FileNotFoundException {
        // Dummy Test Method
	}

	public boolean isMyTurn(int row) {
		return false;
	}

	public void remove(int index) {
        // Dummy Test Method
	}

	public void save(File file) throws FileNotFoundException {
        // Dummy Test Method
	}

	public void setInitCount(Integer initCount) {
        // Dummy Test Method
	}

    public void addlistener(Listener listener) {
        // Dummy Test Method
    }

    public int getRowCount() {
        return 0;
    }

    public int getColumnCount() {
        return 0;
    }

    public String getColumnHeader(int column) {
        return null;
    }

    public boolean isCellEditable(int rowIndex, int columnIndex) {
        return false;
    }

    public void setColumn(Entity entity, int columnIndex, Object value) {
        //Dummy Test Method
    }

    public Class<?> getColumnClass(int columnIndex) {
        return null;
    }

    public List<Object> getEntireRow(Entity entity1) {
        return null;
    }

    public Object getColumn(Entity entity1, int col) {
        return null;
    }

    public Object getValueAt(int row, int col) {
        return null;
    }
}