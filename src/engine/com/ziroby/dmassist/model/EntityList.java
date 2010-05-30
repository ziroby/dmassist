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
package com.ziroby.dmassist.model;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Collection;
import java.util.List;

import com.ziroby.util.Listenable;

/**
 * An abstract list of entities.  
 *
 * @see Entity
 * 
 * @author Ron Romero
 *
 */
public interface EntityList 
    extends Listenable {

    /** The number for the turn indicator column. */
    public static final int COLUMN_NUMBER_MY_TURN = 0;
    /** The number for the abbreviation column. */
    public static final int COLUMN_NUMBER_NUM = 1; 
    /** The number for the name column. */
    public static final int COLUMN_NUMBER_NAME = 2; 
    /** The number for the initiative count column. */
    public static final int COLUMN_NUMBER_INIT = 3; 
    /** The number for the hitpoint column. */
    public static final int COLUMN_NUMBER_HP = 4; 
    /** The number for the subdual damage column. */
    public static final int COLUMN_NUMBER_SUBDUAL = 5;
    /** The number for the number of rounds left column. */
    public static final int COLUMN_NUMBER_ROUNDS = 6;
    
    /** Returns the human readable column heading for the given "column". */
    public String getColumnHeader(int column);

    /** The number of virtual columns. */
    public int getColumnCount();
   /**
	 * Tells if it's this row's turn.  That is, is this row's initiative count
	 * equal to the currently active initiative count? 
	 */
	public boolean isMyTurn(int row);

    public int getRowCount();
    
    public void addEntity(Entity entity);

	public Integer getInitCount();

	public void setInitCount(Integer initCount);

	/**
	 * Goes to the "next" initiative count.  The next highest number, or if this is
	 * the highest number, then to the minimum number.  
	 */
	public void gotoNextInitCount();

	public void remove(int index);

	public Entity getEntity(int row);

	public Entity findByAbbrev(String abbrev);

	public Collection<Entity> getEntities();

	public void addEntities(Collection<Entity> list);

	public void clear();

	/**
	 * @param file
	 * @throws FileNotFoundException
	 */
	public void save(File file) throws FileNotFoundException;

	/**
	 * @param file
	 * @throws FileNotFoundException
	 */
	public void importFile(File file) throws FileNotFoundException;

    public boolean isCellEditable(int rowIndex, int columnIndex);

    /**
     * Sets the given virtual column.  Delegates to the correct setFoo() method.
     * 
     * @param columnIndex The index to set.
     * @param value The value; must be of the appropriate type (usually
     * String or Integer).
     */
    public void setColumn(Entity entity, int columnIndex, Object value);

    public Class<?> getColumnClass(int columnIndex);
    
    /**
     * Returns all the attributed (the entire "row") as a <code>List</code>.
     */
    public List<Object> getEntireRow(Entity entity);
    
    public Object getValueAt(int row, int col);
    
    /** Returns the given virtual column. */
    public Object getColumn(Entity entity, int col);

}