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
package com.ziroby.dmassist.model.test;

import junit.framework.AssertionFailedError;

import com.ziroby.util.Listener;
import com.ziroby.util.ObjectEvent;

/**
 * @author Ron Romero
 *
 */
public class MockTableModelListener implements Listener {

	/**
	 * Do we expect to get events sent to us?  Set to false when we're not supposed
	 * to get events, then set to true when we are.
	 */
	private int expectEvents = 0;

	public MockTableModelListener() {
		super();
//		System.out.println("Mock listener creation.  Don't expect events");
	}
	
    @Override
    public void objectChanged(ObjectEvent event) {
		if (expectEvents < 1)
		{
			unexpectedEvent();
		}
		// OK, we expected that.  But don't get any more.
		--expectEvents;
//		System.out.println("Got an expected event; expect " + expectEvents + "more");

	}

	void expectNoEvents()
	{
		if (expectEvents > 0)
		{
			didNotGetExpected();
		}
		expectEvents = 0;
//		System.out.println("Don't expect events");
	}

	/**
	 * The mock object should expect exactly one event.
	 */
	public void expectEvent() {
		if (expectEvents > 0)
		{
			didNotGetExpected();
		}
		expectEvents = 1;
//		System.out.println("expected an event");
	}

//	public void expectEvents(int i) {
//		expectEvents = i;
//	}
	/**
	 * We got an event we shouldn't have.
	 * 
	 * @throws AssertionFailedError
	 */
	private void unexpectedEvent() throws AssertionFailedError {
//		System.out.println("ERROR: Got an UNexpected event");			
		throw new junit.framework.AssertionFailedError("Received a table changed event when we shouldn't have");
	}

	/**
	 * We did not get an event that we expected.
	 * 
	 * @throws AssertionFailedError
	 */
	private void didNotGetExpected() throws AssertionFailedError {
		//Oops, we expected an event and didn't get it.
//		System.out.println("ERROR: Did not get expected event");
		throw new junit.framework.AssertionFailedError("Did not get expected event");
	}

}
