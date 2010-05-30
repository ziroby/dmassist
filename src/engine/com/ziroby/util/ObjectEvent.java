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

/**
 * Notification of a change, generally in a Listenable, sent to Listener's.
 * 
 * @see Listenable
 * @see Listener
 * 
 * @author Ron Romero
 * 
 */
public class ObjectEvent {
    private Object source;

    /**
     * Creates a simple Object Event, with source set to the given value.
     * 
     * @param source
     *            The object which "generated", or is the source of, this event.
     */
    public ObjectEvent(Object source) {
        super();
        this.source = source;
    }

    /**
     * The source of an event is "what caused the event".  Generally,
     * it's then item whose change triggered the event.
     */
    public final Object getSource() {
        return source;
    }

    /**
     * The source of an event is "what caused the event".  Generally,
     * it's then item whose change triggered the event.
     */
    public final void setSource(Object source) {
        this.source = source;
    }
}
