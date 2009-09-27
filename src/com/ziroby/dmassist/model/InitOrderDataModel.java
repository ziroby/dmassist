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
import java.util.Vector;

import javax.swing.table.AbstractTableModel;

import org.ho.yaml.Yaml;

import com.ziroby.dmassist.model.test.ObjectEvent;

/**
 * The data model for our main initiative order table.
 * 
 * @author Ziroby
 *
 */
public class InitOrderDataModel extends AbstractTableModel
		implements
			Listener,
			EntityList 
{
	private List<Entity> entities = new Vector<Entity>(getColumnCount());	
	private Integer initCount = null;
	/**
	 * How deep in the call stack are we? This is used to make sure we only send
	 * one table changed event per public call.
	 */
	private int depth = 0;
	private boolean dirty = false;
	
	/**
	 * 
	 */
	private static final long serialVersionUID = 5503046605866805606L;

	/**
	 * @see javax.swing.table.TableModel#getColumnCount()
	 */
	public int getColumnCount() {
		// TODO Auto-generated method stub
		return Entity.getColumnCount();
	}

	/**
	 * @see javax.swing.table.TableModel#getRowCount()
	 */
	public int getRowCount() {
		// TODO Auto-generated method stub
		return entities.size();
	}

	/**
	 * @see javax.swing.table.TableModel#getValueAt(int, int)
	 */
	public Object getValueAt(int row, int col) {
		if (col == Entity.ROW_NUMBER_MY_TURN)
		{
			return isMyTurn(row);
		}
		

		return entities.get(row).getColumn(col);
	}

	/**
	 * @see com.ziroby.dmassist.model.EntityList#isMyTurn(int)
	 */
	public boolean isMyTurn(int row) {
		final Integer initRoll = entities.get(row).getInitRoll();
		return initRoll != null && initRoll == this.initCount;
	}

	@Override
	public String getColumnName(int column) {
		return Entity.getColumnHeader(column);
	}

	@Override
	public boolean isCellEditable(int rowIndex, int columnIndex) {
		// TODO Auto-generated method stub
		if (columnIndex == Entity.ROW_NUMBER_MY_TURN)
			return false;

		return true;
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
	 * @see javax.swing.table.AbstractTableModel#getColumnClass(int)
	 */
	@Override
	public Class<?> getColumnClass(int columnIndex) {
		switch (columnIndex) {
			case Entity.ROW_NUMBER_NAME:
			case Entity.ROW_NUMBER_NUM:
				return String.class;
			case Entity.ROW_NUMBER_HP:
			case Entity.ROW_NUMBER_SUBDUAL:
			case Entity.ROW_NUMBER_INIT:
            case Entity.ROW_NUMBER_ROUNDS:
				return Integer.class;
			case Entity.ROW_NUMBER_MY_TURN:
				return Boolean.class;				
				
			default:
				return super.getColumnClass(columnIndex);
		}
		// TODO Auto-generated method stub
	}

	/**
	 * @see javax.swing.table.AbstractTableModel#setValueAt(java.lang.Object, int, int)
	 */
	@Override
	public void setValueAt(Object value, int rowIndex, int columnIndex) {
		// TODO Auto-generated method stub
		entities.get(rowIndex).setColumn(columnIndex, value);
	}

	/**
	 * @see com.ziroby.dmassist.model.EntityList#getInitCount()
	 */
	public final Integer getInitCount() {
		return initCount;
	}

	/**
	 * @see com.ziroby.dmassist.model.EntityList#setInitCount(int)
	 */
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
		else if (maximum != null)
			setInitCount(maximum);
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
	}

	/**
	 * @see com.ziroby.dmassist.model.EntityList#clear()
	 */
	public void clear() {
		enterPublicMethod();
		remove(0);
		entities.clear();
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
	}

    private AbstractListenable listenableImpl = new AbstractListenable();
    
    public void addlistener(Listener listener) {
        listenableImpl.addListener(listener);
    }

    private void alertListeners() {
        fireTableDataChanged();
        listenableImpl.alertListeners();
    }

}
