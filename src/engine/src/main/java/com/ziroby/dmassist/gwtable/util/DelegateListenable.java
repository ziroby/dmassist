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
 * A delegate version of {@link AbstractListenable}.
 * 
 * @author Ron Romero
 * 
 */
public class DelegateListenable implements Listenable {
    /*
     * We can access protected methods on AbstractListenable because we're in
     * the same package.
     */
    private AbstractListenable delegate = new AbstractListenable();

    public void addListener(Listener listener) {
        delegate.addListener(listener);
    }

    /**
     * Calls all the listeners' {@link com.ziroby.dmassist.gwtable.util.Listener#objectChanged
     * objectChanged} method.
     * 
     * @see AbstractListenable#alertListeners()
     * 
     */
    public void alertListeners() {
        delegate.alertListeners();
    }

}
