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

import org.ho.yaml.Yaml;

import com.ziroby.dmassist.gwtable.model.Entity;
import com.ziroby.dmassist.gwtable.model.EntityListGwtable;
import com.ziroby.dmassist.gwtable.util.Listener;

/**
 * The data model for our main initiative order table.
 * 
 * @author Ron Romero
 *
 * @todo Inherits from a Swing class.  We should break that link.
 */
public class EntityListImpl extends EntityListGwtable
		implements
			Listener,
			EntityListWithSave 
{
    /**
	 * @see com.ziroby.dmassist.model.EntityListWithSave#save(java.io.File)
	 */
	public void save(File file) throws FileNotFoundException {
		Yaml.dump(getEntities(), file, true);
	}

	/**
	 * @see com.ziroby.dmassist.model.EntityListWithSave#importFile(java.io.File)
	 */
	@SuppressWarnings("unchecked")
	public void importFile(File file) throws FileNotFoundException {
		enterPublicMethod();
		Collection<Entity> list = (Collection<Entity>) Yaml.load(file);
		addEntities(list);
        leavePublicMethod();
	}
    
}
