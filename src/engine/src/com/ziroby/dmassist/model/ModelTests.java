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


import junit.framework.Test;
import junit.framework.TestSuite;

public class ModelTests {

	public static Test suite() {
		TestSuite suite = new TestSuite(
				"Test for com.ziroby.dmassist.model.test");
		//$JUnit-BEGIN$
		suite.addTestSuite(DiceEquationTest.class);
		suite.addTestSuite(EntityTest.class);
		//$JUnit-END$
		return suite;
	}

}
