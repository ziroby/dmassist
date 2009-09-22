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

public interface EntityList {

	/**
	 * Tells if it's this row's turn.  That is, is this row's initiative count
	 * equal to the currently active initiative count? 
	 */
	public boolean isMyTurn(int row);

	public void addEntity(Entity entity);

	public int getInitCount();

	public void setInitCount(int initCount);

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
	@SuppressWarnings("unchecked")
	public void importFile(File file) throws FileNotFoundException;

}