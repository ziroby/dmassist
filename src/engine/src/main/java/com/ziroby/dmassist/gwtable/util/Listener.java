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
package com.ziroby.dmassist.gwtable.util;


/**
 * A listener listening to a {@link Listenable}. It receives events when the
 * Listenable changes in some way, as defined by the Listenable.
 * 
 * @see Listenable
 * 
 * @author Ron Romero
 * 
 */
public interface Listener {
    /**
     * Notification that the Listenable has changed in a way it wants its
     * listeners to know about.
     * 
     * @param event
     *            Information about the change.
     */
    public void objectChanged(ObjectEvent event);
}