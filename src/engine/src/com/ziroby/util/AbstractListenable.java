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
package com.ziroby.util;

import java.util.ArrayList;
import java.util.Collection;


/**
 * A default implementation of Listenable.  Keeps a collection of
 * Listeners and provides a way to alert them.
 * 
 * @author Ron Romero
 *
 */
public class AbstractListenable implements Listenable {
	private Collection<Listener> listeners = new ArrayList<Listener>();

	public void addListener(Listener listener) {
		listeners.add(listener);
	}		
    
    /**
     * Calls all the listeners'
     * {@link com.ziroby.util.Listener#objectChanged objectChanged} method.
     * 
     */
	protected void alertListeners() {
		ObjectEvent event = new ObjectEvent(this);
		for (Listener listener : listeners) {
			listener.objectChanged(event);			
		}
	}
}
