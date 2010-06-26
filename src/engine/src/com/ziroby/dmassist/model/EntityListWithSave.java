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

import com.ziroby.dmassist.gwtable.model.Entity;
import com.ziroby.dmassist.gwtable.model.EntityList;
import com.ziroby.dmassist.gwtable.util.Listenable;

/**
 * An abstract list of entities.  
 *
 * @see Entity
 * 
 * @author Ron Romero
 *
 */
public interface EntityListWithSave 
    extends Listenable, EntityList {

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

}