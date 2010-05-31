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
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collection;
import java.util.List;
import java.util.Map;
import java.util.Vector;

import org.ho.yaml.Yaml;

import com.ziroby.util.AbstractListenable;
import com.ziroby.util.Listener;
import com.ziroby.util.ObjectEvent;

/**
 * The data model for our main initiative order table.
 * 
 * @author Ron Romero
 *
 * @todo Inherits from a Swing class.  We should break that link.
 */
public class EntityListImpl extends AbstractListenable
		implements
			Listener,
			EntityList 
{
    private final static String[] ColumnName = {" ", "##", "Name", "Init", "HP", "Sub", "Rnds"};

    private static final int SECONDS_PER_ROUND = 6;

	private List<Entity> entities = new Vector<Entity>();	
	private Integer initCount = null;
	/**
	 * How deep in the call stack are we? This is used to make sure we only send
	 * one table changed event per public call.
	 */
	private int depth = 0;
	private boolean dirty = false;

    private int numRounds;
	
	/**
	 * 
	 */
	private static final long serialVersionUID = 5503046605866805606L;

	public int getRowCount() {
		return entities.size();
	}

	/**
	 * @see com.ziroby.dmassist.model.EntityList#isMyTurn(int)
	 */
	public boolean isMyTurn(int row) {
		final Integer initRoll = entities.get(row).getInitRoll();
		return initRoll != null && initRoll == this.initCount;
	}

	/**
	 * @see com.ziroby.dmassist.model.EntityList#addEntity(com.ziroby.dmassist.model.Entity)
	 */
	public void addEntity(Entity entity)
	{
		if (entity == null)
		{
			// Silently do nothing.
			return;
		}
		
		enterPublicMethod();
		
		sanitizeValue(entity);
		
		//int newRowNum = entities.size();
		entities.add(entity);
		dirty = true;
		//fireTableRowsInserted(newRowNum - 1, newRowNum);
		entity.addListener(this);
		leavePublicMethod();
	}

	/**
	 * Fixes the data in the entity, so it fits into the table well.
	 * @param entity
	 */
	private void sanitizeValue(Entity entity) {
		
		if (entity.getName() == null || entity.getName().trim().length() == 0)
		{
			throw new NullPointerException("Blank names are not allowed");
		}

		entity.sanitizeAbbrev(entities);
	}


	/**
	 * @see com.ziroby.dmassist.model.EntityList#getInitCount()
	 */
	public final Integer getInitCount() {
		return initCount;
	}

	public final void setInitCount(Integer initCount) {
		if (this.initCount == initCount)
		{
			// Nothing to do.
			return;
		}

		enterPublicMethod();
		this.initCount = initCount;
		this.dirty = true;
		leavePublicMethod();
	}

	/**
	 * @see com.ziroby.dmassist.model.EntityList#gotoNextInitCount()
	 */
	public void gotoNextInitCount() {	    
		enterPublicMethod();
		
		// We count backwards, so we look for the highest total init count, and the highest one
		// that's less than current.
		Integer oldInitCount = getInitCount();
		Integer maximumNext = null;
		Integer maximum = null;
		
		for (Entity row : entities)
		{
			Integer initRoll = row.getInitRoll();
			
			if (initRoll == null)
				continue;
			if (maximum == null || initRoll > maximum)
				maximum = initRoll;
			if ((oldInitCount == null || initRoll < oldInitCount)
                    && (maximumNext == null || initRoll > maximumNext))
				maximumNext = initRoll;
            
            if (initRoll == oldInitCount)
            {
                row.decrementRound();
            }
		}
		
		if (maximumNext != null)
			setInitCount(maximumNext);
		else if (maximum != null) {
		    numRounds++;
			setInitCount(maximum);
        }
		else
			setInitCount(null);
        
        for (int i=entities.size()-1; i >= 0; --i)
        {
            if (entities.get(i).isExpired(1))
            {
                entities.remove(i);
                dirty = true;
            }
        }

        leavePublicMethod();
	}

	/**
	 * Call this any time you enter a publicly-callable.  It takes care of counting call 
	 * depth and setting things up to fire table change events appropriately.  
	 */
	private void enterPublicMethod() {
		depth++;
	}

	/**
	 * Call this at the end of a method that called enterPublicMethod().  It decrements the depth and
	 * fires table changes if necessary. 
	 */
	private void leavePublicMethod() {
		if (--depth == 0 && dirty)
		{
			// We only fire if we're at top level and something has changed.
			alertListeners();			
			dirty = false;
		}
		if (depth < 0)
		{
			throw new IllegalStateException("Shouldn't have a negative depth in ");
		}
	}

    /**
	 * @see com.ziroby.dmassist.model.EntityList#remove(int)
	 */
	public void remove(int index) {
		enterPublicMethod();
		entities.remove(index);
		dirty = true;
		leavePublicMethod();
	}
	
	/**
	 * @see com.ziroby.dmassist.model.EntityList#getEntity(int)
	 */
	public Entity getEntity(int row)
	{
		return entities.get(row);
	}

	/**
	 * @see com.ziroby.dmassist.model.EntityList#findByAbbrev(java.lang.String)
	 */
	public Entity findByAbbrev(String abbrev) {
		// Linear search for now cuz I'm lazy & how long will it really be?
		for (Entity e : entities)
		{
			if (e.getAbbreviation().equalsIgnoreCase(abbrev))
			{
				return e;
			}
		}
		// Hmmm... Maybe they entered an entire name
		for (Entity e : entities)
		{
			if (e.getName().trim().equalsIgnoreCase(abbrev.trim()))
			{
				return e;
			}
		}
		
		// Couldn't find it.
		return null;
	}

	public void objectChanged(ObjectEvent event) {
		enterPublicMethod();
		dirty = true;
		leavePublicMethod();		
	}

	/**
	 * @see com.ziroby.dmassist.model.EntityList#getEntities()
	 */
	public Collection<Entity> getEntities() {
		return entities;
	}

	/**
	 * @see com.ziroby.dmassist.model.EntityList#addEntities(java.util.Collection)
	 */
	public void addEntities(Collection<Entity> list) {
		enterPublicMethod();
		for (Entity entity : list)
		{
			addEntity(entity);
		}		
		leavePublicMethod();
	}

	/**
	 * @see com.ziroby.dmassist.model.EntityList#clear()
	 */
	public void clear() {
		enterPublicMethod();
		if (entities.size() > 0) {
		    entities.clear();
		    dirty = true;
		}
		leavePublicMethod();
	}

	/**
	 * @see com.ziroby.dmassist.model.EntityList#save(java.io.File)
	 */
	public void save(File file) throws FileNotFoundException {
		Yaml.dump(getEntities(), file, true);
	}

	/**
	 * @see com.ziroby.dmassist.model.EntityList#importFile(java.io.File)
	 */
	@SuppressWarnings("unchecked")
	public void importFile(File file) throws FileNotFoundException {
		enterPublicMethod();
		Collection<Entity> list = (Collection<Entity>) Yaml.load(file);
		addEntities(list);
        leavePublicMethod();
	}

    /** Returns the human readable column heading for the given "column". */
    public String getColumnHeader(int column) {
        return ColumnName[column];
    }

    /** The number of virtual columns. */
    public int getColumnCount() {
        return ColumnName.length;
    }

    public boolean isCellEditable(int rowIndex, int columnIndex) {
        if (columnIndex == COLUMN_NUMBER_MY_TURN)
            return false;
    
        return true;
    }
    /**
     * Sets the given virtual column.  Delegates to the correct setFoo() method.
     * 
     * @param columnIndex The index to set.
     * @param value The value; must be of the appropriate type (usually
     * String or Integer).
     */
    public void setColumn(Entity entity, int columnIndex, Object value) {
        switch (columnIndex) {
            case COLUMN_NUMBER_NAME:
                entity.setName((String) value);
                break;
            case COLUMN_NUMBER_NUM:
                entity.setAbbreviation((String) value);
                break;
            case COLUMN_NUMBER_HP:
                entity.setHitpoints((Integer) value);
                break;
            case COLUMN_NUMBER_INIT:
                entity.setInitRoll((Integer) value);
                break;
            case COLUMN_NUMBER_MY_TURN:
                throw new IllegalArgumentException("Can not edit 'my turn' value");
            case COLUMN_NUMBER_SUBDUAL:
                entity.setSubdual((Integer) value);
                break;
            case COLUMN_NUMBER_ROUNDS:
                entity.setRoundsLeft((Integer) value);
                break;

            default :
                throw new IllegalArgumentException("Invalid column number: " + columnIndex);
        }
    }

    public Class<?> getColumnClass(int columnIndex) {
        switch (columnIndex) {
            case COLUMN_NUMBER_NAME:
            case COLUMN_NUMBER_NUM:
                return String.class;
            case COLUMN_NUMBER_HP:
            case COLUMN_NUMBER_SUBDUAL:
            case COLUMN_NUMBER_INIT:
            case COLUMN_NUMBER_ROUNDS:
                return Integer.class;
            case COLUMN_NUMBER_MY_TURN:
                return Boolean.class;               
                
            default:
                return null;
        }
    }
    /**
     * Returns all the attributed (the entire "row") as a <code>List</code>.
     */
    public List<Object> getEntireRow(Entity entity)
    {
        Object a[] = { false /* my turn */, entity.getAbbreviation(),
                entity.getName(), entity.getInitRoll(), entity.getHitpoints(),
                entity.getSubdual(), entity.getRoundsLeft() };
        
        return Arrays.asList(a);
    }

    public Object getValueAt(int row, int col) {
        Entity entity = getEntity(row);  
        
        if (col == COLUMN_NUMBER_MY_TURN)
        {
            return isMyTurn(row);
        }
        
        return getColumn(entity, col);
    }

    /** Returns the given virtual column. */
    public Object getColumn(Entity entity, int col) {
        // TODO Cache the row, so we're not regenerating it every time.
        return getEntireRow(entity).get(col);
    }

    public void setValueAt(Object value, int rowIndex, int columnIndex) {
        Entity entity = getEntity(rowIndex);  
        
        setColumn(entity, columnIndex, value);
    }

    public List<Map<String, String>> getListOfMaps() {
        List<Map<String,String>> list = new ArrayList<Map<String,String>>();
        
        getListOfMaps(list);
        
        return list;
    }

    @Override
    public List<Map<String,String>> getListOfMaps(List<Map<String, String>> data) {
        data.clear();
        
        for (Entity entity: getEntities())
        {
            data.add(entity.getAsMap());
        }
        
        return data;
    }

    public int getNumRounds() {
        return numRounds;
    }

    public void resetNumRounds() {
        enterPublicMethod();
        if (numRounds != 0) {
            numRounds = 0;
            setInitCount(null);
            this.dirty = true;
        }
        leavePublicMethod();
    }

    public String formatRoundsAsTime() {
        int seconds = (numRounds * SECONDS_PER_ROUND) % 60;
        int minutes = ((numRounds * SECONDS_PER_ROUND) / 60) % 60;
        int hours = (numRounds * SECONDS_PER_ROUND) / (60 * 60);

        String s;
        if (hours == 0)
        {
            s = String.format("%02d:%02d", minutes, seconds); //$NON-NLS-1$
        }
        else
        {
            s = String.format("%02d:%02d:%02d", hours, minutes, seconds); //$NON-NLS-1$
        }
        return s;
    }
    
}
