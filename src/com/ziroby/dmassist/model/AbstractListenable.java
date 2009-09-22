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

import java.util.Collection;
import java.util.Vector;

import com.ziroby.dmassist.model.test.ObjectEvent;

/**
 * @author Ziroby
 *
 */
public class AbstractListenable implements Listenable {
	private Collection<Listener> listeners = new Vector<Listener>();

	/**
	 * @see com.ziroby.dmassist.model.Listenable#addListener(com.ziroby.dmassist.model.Listener)
	 */
	public void addListener(Listener listener) {
		listeners.add(listener);
	}		
	protected void alertListeners() {
		ObjectEvent event = new ObjectEvent(this);
		for (Listener listener : listeners) {
			listener.objectChanged(event);			
		}
	}
}
