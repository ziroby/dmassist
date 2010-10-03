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
package com.ziroby.dmassist.swing;

import java.io.File;
import java.io.IOException;

import junit.framework.TestCase;

import org.junit.After;
import org.junit.Before;
import org.junit.Test;

import com.ziroby.dmassist.gwtable.model.Entity;
import com.ziroby.dmassist.gwtable.model.EntityList;
import com.ziroby.dmassist.gwtable.model.EntityListGwtable;
import com.ziroby.dmassist.model.MockTableModelListener;

/**
 * @author Ron Romero
 *
 */
public class InitOrderDataModelTest extends TestCase {

	private EntityDataModel dataModel;
	private MockTableModelListener mockListener;


	/**
	 * @throws java.lang.Exception
	 */
	@Override
	@Before
	public void setUp() throws Exception {
		dataModel = new EntityDataModel();

		mockListener = new MockTableModelListener();
		dataModel.addListener(mockListener);
		assertEquals(0, dataModel.getRowCount());

	}

	/**
	 * @throws java.lang.Exception
	 */
	@Override
	@After
	public void tearDown() throws Exception {
	    // Nothing
	}

	@Test
	public void testGotoNextInitCount() {
		fillTable();

		for (int i = 0; i < 10; ++i)
		{
			mockListener.expectEvent();
			dataModel.setInitCount(1);
			mockListener.expectNoEvents();

			mockListener.expectEvent();
			dataModel.gotoNextInitCount();
			assertEquals(false, dataModel.getValueAt(0, EntityList.COLUMN_NUMBER_MY_TURN));
			assertEquals(false, dataModel.getValueAt(1, EntityList.COLUMN_NUMBER_MY_TURN));
			assertEquals(false, dataModel.getValueAt(2, EntityList.COLUMN_NUMBER_MY_TURN));
			assertEquals(true, dataModel.getValueAt(3, EntityList.COLUMN_NUMBER_MY_TURN));
			mockListener.expectNoEvents();

			mockListener.expectEvent();
			dataModel.gotoNextInitCount();
			assertEquals(true, dataModel.getValueAt(0, EntityList.COLUMN_NUMBER_MY_TURN));
			assertEquals(false, dataModel.getValueAt(1, EntityList.COLUMN_NUMBER_MY_TURN));
			assertEquals(true, dataModel.getValueAt(2, EntityList.COLUMN_NUMBER_MY_TURN));
			assertEquals(false, dataModel.getValueAt(3, EntityList.COLUMN_NUMBER_MY_TURN));
			mockListener.expectNoEvents();

			mockListener.expectEvent();
			dataModel.gotoNextInitCount();
			assertEquals(false, dataModel.getValueAt(0, EntityList.COLUMN_NUMBER_MY_TURN));
			assertEquals(true, dataModel.getValueAt(1, EntityList.COLUMN_NUMBER_MY_TURN));
			assertEquals(false, dataModel.getValueAt(2, EntityList.COLUMN_NUMBER_MY_TURN));
			assertEquals(false, dataModel.getValueAt(3, EntityList.COLUMN_NUMBER_MY_TURN));
			mockListener.expectNoEvents();
		}
		mockListener.expectNoEvents();
	}

    private void fillTable() {
        Entity row1 = new Entity();
		row1.setAbbreviation("G");
		row1.setName("Ogre 1");
		row1.setInitRoll(12);
		row1.setHitpoints(25);
		mockListener.expectEvent();
		dataModel.addEntity(row1);
		mockListener.expectNoEvents();

		Entity row2 = new Entity();
		row2.setAbbreviation("G");
		row2.setName("Ogre 2");
		row2.setInitRoll(10);
		row2.setHitpoints(27);
		mockListener.expectNoEvents();
		mockListener.expectEvent();
		dataModel.addEntity(row2);
		mockListener.expectNoEvents();

		Entity row3 = new Entity();
		//row3.setAbbreviation("G");
		row3.setName("Ogre 3");
		row3.setInitRoll(12);
		row3.setHitpoints(28);
		mockListener.expectEvent();
		dataModel.addEntity(row3);
		mockListener.expectNoEvents();

		Entity row4 = new Entity();
		//row4.setAbbreviation("G");
		row4.setName("Ogre 3");
		row4.setInitRoll(-3);
		row4.setHitpoints(28);
		mockListener.expectEvent();
		dataModel.addEntity(row4);
		mockListener.expectNoEvents();
    }


	/**
	 * Test method for {@link com.ziroby.dmassist.model.EntityListImpl#gotoNextInitCount()}.
	 */
	@Test
	public void testGotoNextInitCountEmptyTable() {

		for (int i = 0; i < 10; ++i)
		{
			mockListener.expectNoEvents();
			dataModel.gotoNextInitCount();
			mockListener.expectNoEvents();
			assertEquals(0, dataModel.getRowCount());
		}
		assertEquals(0, dataModel.getRowCount());
		mockListener.expectNoEvents();
	}

	/**
	 * Test method for {@link com.ziroby.dmassist.model.EntityListImpl#gotoNextInitCount()}.
	 */
	@Test
	public void testGotoNextInitCountFillThenEmptyTable() {
		Entity row1 = new Entity();
		row1.setAbbreviation("G");
		row1.setName("Ogre 1");
		row1.setInitRoll(12);
		row1.setHitpoints(25);
		mockListener.expectEvent();
		dataModel.addEntity(row1);
		mockListener.expectNoEvents();

		Entity row2 = new Entity();
		row2.setAbbreviation("G");
		row2.setName("Ogre 2");
		row2.setInitRoll(10);
		row2.setHitpoints(27);
		mockListener.expectNoEvents();
		mockListener.expectEvent();
		dataModel.addEntity(row2);
		mockListener.expectNoEvents();

		Entity row3 = new Entity();
		//row3.setAbbreviation("G");
		row3.setName("Ogre 3");
		row3.setInitRoll(12);
		row3.setHitpoints(28);
		mockListener.expectEvent();
		dataModel.addEntity(row3);
		mockListener.expectNoEvents();

		Entity row4 = new Entity();
		//row4.setAbbreviation("G");
		row4.setName("Ogre 3");
		row4.setInitRoll(-3);
		row4.setHitpoints(28);

		mockListener.expectEvent();
		dataModel.setInitCount(-3);
		mockListener.expectNoEvents();

		mockListener.expectEvent();
		dataModel.addEntity(row4);
		mockListener.expectNoEvents();

		mockListener.expectEvent();
		dataModel.remove(3);
		mockListener.expectNoEvents();

		mockListener.expectEvent();
		dataModel.remove(1);
		mockListener.expectNoEvents();

		mockListener.expectEvent();
		dataModel.remove(1);
		mockListener.expectNoEvents();

		mockListener.expectEvent();
		dataModel.remove(0);
		mockListener.expectNoEvents();

		mockListener.expectEvent();
		dataModel.gotoNextInitCount();
		mockListener.expectNoEvents();
		assertEquals(null, dataModel.getInitCount());
		assertEquals(0, dataModel.getRowCount());

		mockListener.expectNoEvents();
		dataModel.gotoNextInitCount();
		mockListener.expectNoEvents();
		assertEquals(null, dataModel.getInitCount());

		mockListener.expectNoEvents();

	}


	@Test
	public void testAddEntity()
	{
		Entity row1 = new Entity();
		row1.setAbbreviation("G");
		row1.setName("Ogre 1");
		row1.setInitRoll(12);
		row1.setHitpoints(25);
		mockListener.expectEvent();
		dataModel.addEntity(row1);
		mockListener.expectNoEvents();
		assertEquals(1, dataModel.getRowCount());
		Entity entity0 = dataModel.getEntity(0);
		assertEquals("G", entity0.getAbbreviation());
		assertEquals("Ogre 1", entity0.getName());
		assertEquals(new Integer(12), entity0.getInitRoll());
		assertEquals(new Integer(25), entity0.getHitpoints());
		mockListener.expectNoEvents();

		Entity row2 = new Entity();
		row2.setAbbreviation("G");
		row2.setName("Ogre 2");
		row2.setInitRoll(10);
		row2.setHitpoints(27);
		mockListener.expectEvent();
		dataModel.addEntity(row2);
		mockListener.expectNoEvents();
		entity0 = dataModel.getEntity(0);
		assertEquals(2, dataModel.getRowCount());
		assertEquals("G1", entity0.getAbbreviation());
		assertEquals("Ogre 1", entity0.getName());
		assertEquals(new Integer(12), entity0.getInitRoll());
		assertEquals(new Integer(25), entity0.getHitpoints());
		mockListener.expectNoEvents();

		Entity entity1 = dataModel.getEntity(1);
		assertEquals("G2", entity1.getAbbreviation());
		assertEquals("Ogre 2", entity1.getName());
		assertEquals(new Integer(10), entity1.getInitRoll());
		assertEquals(new Integer(27), entity1.getHitpoints());
		mockListener.expectNoEvents();

		Entity row3 = new Entity();
		//row3.setAbbreviation("G");
		row3.setName("Ogre 3");
		row3.setInitRoll(12);
		row3.setHitpoints(28);
		mockListener.expectEvent();
		dataModel.addEntity(row3);
		mockListener.expectNoEvents();
		entity0 = dataModel.getEntity(0);
		assertEquals(3, dataModel.getRowCount());
		assertEquals("G1", entity0.getAbbreviation());
		assertEquals("Ogre 1", entity0.getName());
		assertEquals(new Integer(12), entity0.getInitRoll());
		assertEquals(new Integer(25), entity0.getHitpoints());
		mockListener.expectNoEvents();

		entity1 = dataModel.getEntity(1);
		assertEquals("G2", entity1.getAbbreviation());
		assertEquals("Ogre 2", entity1.getName());
		assertEquals(new Integer(10), entity1.getInitRoll());
		assertEquals(new Integer(27), entity1.getHitpoints());
		mockListener.expectNoEvents();

		Entity entity2 = dataModel.getEntity(2);
		assertEquals("O", entity2.getAbbreviation());
		assertEquals("Ogre 3", entity2.getName());
		assertEquals(new Integer(12), entity2.getInitRoll());
		assertEquals(new Integer(28), entity2.getHitpoints());
		mockListener.expectNoEvents();
}
	@Test
	public void testAddEntityNull()
	{

		mockListener.expectNoEvents();
		dataModel.addEntity(null);
		mockListener.expectNoEvents();
}

	@Test
	public void testAddEntity2()
	{
		Entity row1 = new Entity();
		//row1.setAbbreviation("G");
		row1.setName("   Ogre 1  ");
		row1.setInitRoll(12);
		row1.setHitpoints(25);
		mockListener.expectEvent();
		dataModel.addEntity(row1);
		mockListener.expectNoEvents();
		assertEquals(1, dataModel.getRowCount());
		Entity entity0 = dataModel.getEntity(0);
		assertEquals("O", entity0.getAbbreviation());
		assertEquals("Ogre 1", entity0.getName());
		assertEquals(new Integer(12), entity0.getInitRoll());
		assertEquals(new Integer(25), entity0.getHitpoints());
		mockListener.expectNoEvents();
}


	@Test
	public void testAddEntity3()
	{
		Entity row1 = new Entity();
		row1.setAbbreviation(" G ");
		row1.setName("   Ogre 1  ");
		row1.setInitRoll(12);
		row1.setHitpoints(25);
		mockListener.expectEvent();
		dataModel.addEntity(row1);
		mockListener.expectNoEvents();
		assertEquals(1, dataModel.getRowCount());
		Entity entity0 = dataModel.getEntity(0);
		assertEquals("G", entity0.getAbbreviation());
		assertEquals("Ogre 1", entity0.getName());
		assertEquals(new Integer(12), entity0.getInitRoll());
		assertEquals(new Integer(25), entity0.getHitpoints());
		mockListener.expectNoEvents();
}


	@Test
	public void testAddEntityNoNull()
	{
		Entity row1 = new Entity();
		row1.setAbbreviation("G");
		row1.setName("Ogre 1");
		row1.setInitRoll(12);
		row1.setHitpoints(42);
		mockListener.expectEvent();
		dataModel.addEntity(row1);
		mockListener.expectNoEvents();
		assertEquals(1, dataModel.getRowCount());
		Entity entity0 = dataModel.getEntity(0);
		assertEquals("G", entity0.getAbbreviation());
		assertEquals("Ogre 1", entity0.getName());
		assertEquals(new Integer(12), entity0.getInitRoll());
		assertEquals(new Integer(42), entity0.getHitpoints());
		mockListener.expectNoEvents();
	}


	@Test
	public void testAddEntityNullHp()
	{
		Entity row1 = new Entity();
		row1.setAbbreviation("G");
		row1.setName("Ogre 1");
		row1.setInitRoll(12);
		Integer n = null;
		row1.setHitpoints(n);
		mockListener.expectEvent();
		dataModel.addEntity(row1);
		mockListener.expectNoEvents();
		assertEquals(1, dataModel.getRowCount());
		Entity entity0 = dataModel.getEntity(0);
		assertEquals("G", entity0.getAbbreviation());
		assertEquals("Ogre 1", entity0.getName());
		assertEquals(new Integer(12), entity0.getInitRoll());
		assertNull(entity0.getHitpoints());
		mockListener.expectNoEvents();
	}

	@Test
	public void testAddEntityNullInit()
	{
		Entity row1 = new Entity();
		row1.setAbbreviation("G");
		row1.setName("Ogre 1");
		Integer n = null;
		row1.setInitRoll(n);
		row1.setHitpoints(42);
		mockListener.expectEvent();
		dataModel.addEntity(row1);
		mockListener.expectNoEvents();
		assertEquals(1, dataModel.getRowCount());
		Entity entity0 = dataModel.getEntity(0);
		assertEquals("G", entity0.getAbbreviation());
		assertEquals("Ogre 1", entity0.getName());
		assertNull(entity0.getInitRoll());
		assertEquals(new Integer(42), entity0.getHitpoints());
		mockListener.expectNoEvents();
	}


	@Test
	public void testAddEntityNullInitNextInit()
	{
		Entity row1 = new Entity();
		row1.setAbbreviation("G");
		row1.setName("Ogre 1");
		Integer n = null;
		row1.setInitRoll(n);
		row1.setHitpoints(42);
		mockListener.expectEvent();
		dataModel.addEntity(row1);
		mockListener.expectNoEvents();
		assertEquals(1, dataModel.getRowCount());
		Entity entity0 = dataModel.getEntity(0);
		assertEquals("G", entity0.getAbbreviation());
		assertEquals("Ogre 1", entity0.getName());
		assertNull(entity0.getInitRoll());
		assertEquals(new Integer(42), entity0.getHitpoints());
		mockListener.expectNoEvents();

		mockListener.expectEvent();
		dataModel.setInitCount(1);
		mockListener.expectNoEvents();
		assertEquals(false, dataModel.getValueAt(0, EntityListGwtable.COLUMN_NUMBER_MY_TURN));

		mockListener.expectEvent();
		dataModel.gotoNextInitCount();
		assertEquals(false, dataModel.getValueAt(0, EntityListGwtable.COLUMN_NUMBER_MY_TURN));
		assertEquals(null, dataModel.getInitCount());
		mockListener.expectNoEvents();
	}

	@Test
	public void testAddEntityNullAbbrev()
	{
		Entity row1 = new Entity();
		row1.setAbbreviation(null);
		row1.setName("Ogre 1");
		row1.setInitRoll(12);
		row1.setHitpoints(42);
		mockListener.expectEvent();
		dataModel.addEntity(row1);
		mockListener.expectNoEvents();
		assertEquals(1, dataModel.getRowCount());
		Entity entity0 = dataModel.getEntity(0);
		assertEquals("O", entity0.getAbbreviation());
		assertEquals("Ogre 1", entity0.getName());
		assertEquals(new Integer(12), entity0.getInitRoll());
		assertEquals(new Integer(42), entity0.getHitpoints());
		mockListener.expectNoEvents();
	}


	@Test
	public void testAddEntityNullAbbrev3()
	{
		Entity row1 = new Entity();
		row1.setAbbreviation(null);
		row1.setName("ogre 1");
		row1.setInitRoll(12);
		row1.setHitpoints(42);
		mockListener.expectEvent();
		dataModel.addEntity(row1);
		mockListener.expectNoEvents();
		assertEquals(1, dataModel.getRowCount());
		Entity entity0 = dataModel.getEntity(0);
		assertEquals("O", entity0.getAbbreviation());
		assertEquals("ogre 1", entity0.getName());
		assertEquals(new Integer(12), entity0.getInitRoll());
		assertEquals(new Integer(42), entity0.getHitpoints());
		mockListener.expectNoEvents();
	}


	@Test
	public void testAddEntityNullName()
	{
		Entity row1 = new Entity();
		row1.setAbbreviation("G");
		row1.setName(null);
		row1.setInitRoll(12);
		row1.setHitpoints(42);
		mockListener.expectNoEvents();
		try
		{
			dataModel.addEntity(row1);
			fail("null name should've failed");
		}
		catch (NullPointerException e)
		{
			// that's right.
		}
		assertEquals(0, dataModel.getRowCount());
		mockListener.expectNoEvents();
	}

	@Test
	public void testAddEntityBlankName()
	{
		Entity row1 = new Entity();
		row1.setAbbreviation("G");
		row1.setName("");
		row1.setInitRoll(12);
		row1.setHitpoints(42);
		mockListener.expectNoEvents();
		try
		{
			dataModel.addEntity(row1);
			fail("null name should've failed");
		}
		catch (NullPointerException e)
		{
			// that's right.
		}
		assertEquals(0, dataModel.getRowCount());
		mockListener.expectNoEvents();
	}
	@Test
	public void testAddEntityBlankName2()
	{
		Entity row1 = new Entity();
		row1.setAbbreviation("G");
		row1.setName("   ");
		row1.setInitRoll(12);
		row1.setHitpoints(42);
		mockListener.expectNoEvents();
		try
		{
			dataModel.addEntity(row1);
			fail("null name should've failed");
		}
		catch (NullPointerException e)
		{
			// that's right.
		}
		assertEquals(0, dataModel.getRowCount());
		mockListener.expectNoEvents();
	}
	@Test
	public void testSubdual()
	{
		Entity row1 = new Entity();
		row1.setAbbreviation("G");
		row1.setName("Ogre 1");
		row1.setInitRoll(12);
		row1.setHitpoints(25);
		row1.setSubdual(5);
		mockListener.expectEvent();
		dataModel.addEntity(row1);
		mockListener.expectNoEvents();
		assertEquals(1, dataModel.getRowCount());
		Entity entity0 = dataModel.getEntity(0);
		assertEquals("G", entity0.getAbbreviation());
		assertEquals("Ogre 1", entity0.getName());
		assertEquals(new Integer(12), entity0.getInitRoll());
		assertEquals(new Integer(25), entity0.getHitpoints());
		assertEquals(new Integer(5), entity0.getSubdual());
		mockListener.expectNoEvents();
	}
	@Test
	public void testSubdual1()
	{
		Entity row1 = new Entity();
		row1.setAbbreviation("G");
		row1.setName("Ogre 1");
		row1.setInitRoll(12);
		row1.setHitpoints(25);
//		row1.setSubdual(5);
		mockListener.expectEvent();
		dataModel.addEntity(row1);
		mockListener.expectNoEvents();
		assertEquals(1, dataModel.getRowCount());
		Entity entity0 = dataModel.getEntity(0);
		assertEquals("G", entity0.getAbbreviation());
		assertEquals("Ogre 1", entity0.getName());
		assertEquals(new Integer(12), entity0.getInitRoll());
		assertEquals(new Integer(25), entity0.getHitpoints());
		assertEquals(null, entity0.getSubdual());
		mockListener.expectNoEvents();
	}
	@Test
	public void testSubdualDamage()
	{
		Entity row1 = new Entity();
		row1.setAbbreviation("G");
		row1.setName("Ogre 1");
		row1.setInitRoll(12);
		row1.setHitpoints(25);
//		row1.setSubdual(5);
		mockListener.expectEvent();
		dataModel.addEntity(row1);
		mockListener.expectNoEvents();
		assertEquals(1, dataModel.getRowCount());
		Entity entity0 = dataModel.getEntity(0);
		assertEquals("G", entity0.getAbbreviation());
		assertEquals("Ogre 1", entity0.getName());
		assertEquals(new Integer(12), entity0.getInitRoll());
		assertEquals(new Integer(25), entity0.getHitpoints());
		assertEquals(null, entity0.getSubdual());
		mockListener.expectEvent();
		entity0.subdue(3);
		mockListener.expectNoEvents();
		assertEquals(1, dataModel.getRowCount());
		Entity entity1 = dataModel.getEntity(0);
		assertEquals("G", entity1.getAbbreviation());
		assertEquals("Ogre 1", entity1.getName());
		assertEquals(new Integer(12), entity1.getInitRoll());
		assertEquals(new Integer(25), entity1.getHitpoints());
		assertEquals(new Integer(3), entity1.getSubdual());
	}
	@Test
	public void testDamage()
	{
		Entity row1 = new Entity();
		row1.setAbbreviation("G");
		row1.setName("Ogre 1");
		row1.setInitRoll(12);
		row1.setHitpoints(25);
//		row1.setSubdual(5);
		mockListener.expectEvent();
		dataModel.addEntity(row1);
		mockListener.expectNoEvents();
		assertEquals(1, dataModel.getRowCount());
		Entity entity0 = dataModel.getEntity(0);
		assertEquals("G", entity0.getAbbreviation());
		assertEquals("Ogre 1", entity0.getName());
		assertEquals(new Integer(12), entity0.getInitRoll());
		assertEquals(new Integer(25), entity0.getHitpoints());
		assertEquals(null, entity0.getSubdual());
		mockListener.expectEvent();
		entity0.damage(4);
		mockListener.expectNoEvents();
		assertEquals(1, dataModel.getRowCount());
		Entity entity1 = dataModel.getEntity(0);
		assertEquals("G", entity1.getAbbreviation());
		assertEquals("Ogre 1", entity1.getName());
		assertEquals(new Integer(12), entity1.getInitRoll());
		assertEquals(new Integer(21), entity1.getHitpoints());
		//assertEquals(new Integer(3), entity1.getSubdual());
	}
	@Test
	public void testHealDamage()
	{
		Entity row1 = new Entity();
		row1.setAbbreviation("G");
		row1.setName("Ogre 1");
		row1.setInitRoll(12);
		row1.setHitpoints(25);
//		row1.setSubdual(5);
		mockListener.expectEvent();
		dataModel.addEntity(row1);
		mockListener.expectNoEvents();
		assertEquals(1, dataModel.getRowCount());
		Entity entity0 = dataModel.getEntity(0);
		assertEquals("G", entity0.getAbbreviation());
		assertEquals("Ogre 1", entity0.getName());
		assertEquals(new Integer(12), entity0.getInitRoll());
		assertEquals(new Integer(25), entity0.getHitpoints());
		assertEquals(null, entity0.getSubdual());
		mockListener.expectEvent();
		entity0.heal(4);
		mockListener.expectNoEvents();
		assertEquals(1, dataModel.getRowCount());
		Entity entity1 = dataModel.getEntity(0);
		assertEquals("G", entity1.getAbbreviation());
		assertEquals("Ogre 1", entity1.getName());
		assertEquals(new Integer(12), entity1.getInitRoll());
		assertEquals(new Integer(29), entity1.getHitpoints());
		//assertEquals(new Integer(3), entity1.getSubdual());
		mockListener.expectEvent();
		entity0.heal(3);
		mockListener.expectNoEvents();
		assertEquals(new Integer(32), entity1.getHitpoints());

	}
	@Test
	public void testHealSubdual()
	{
		Entity row1 = new Entity();
		row1.setAbbreviation("G");
		row1.setName("Ogre 1");
		row1.setInitRoll(12);
		row1.setHitpoints(25);
		row1.setSubdual(5);
		mockListener.expectEvent();
		dataModel.addEntity(row1);
		mockListener.expectNoEvents();
		assertEquals(1, dataModel.getRowCount());
		Entity entity0 = dataModel.getEntity(0);
		assertEquals("G", entity0.getAbbreviation());
		assertEquals("Ogre 1", entity0.getName());
		assertEquals(new Integer(12), entity0.getInitRoll());
		assertEquals(new Integer(25), entity0.getHitpoints());
		assertEquals(new Integer(5), entity0.getSubdual());
		mockListener.expectEvent();
		entity0.healSubdual(3);
		mockListener.expectNoEvents();
		assertEquals(1, dataModel.getRowCount());
		Entity entity1 = dataModel.getEntity(0);
		assertEquals("G", entity1.getAbbreviation());
		assertEquals("Ogre 1", entity1.getName());
		assertEquals(new Integer(12), entity1.getInitRoll());
		assertEquals(new Integer(25), entity1.getHitpoints());
		assertEquals(new Integer(2), entity1.getSubdual());
		mockListener.expectEvent();
		entity0.healSubdual(1);
		mockListener.expectNoEvents();
		assertEquals(1, dataModel.getRowCount());
		assertEquals(new Integer(1), dataModel.getEntity(0).getSubdual());
	}
	@Test
	public void testSubdualDamageZero()
	{
		Entity row1 = new Entity();
		row1.setAbbreviation("G");
		row1.setName("Ogre 1");
		row1.setInitRoll(12);
		row1.setHitpoints(25);
//		row1.setSubdual(5);
		mockListener.expectEvent();
		dataModel.addEntity(row1);
		mockListener.expectNoEvents();
		assertEquals(1, dataModel.getRowCount());
		Entity entity0 = dataModel.getEntity(0);
		assertEquals("G", entity0.getAbbreviation());
		assertEquals("Ogre 1", entity0.getName());
		assertEquals(new Integer(12), entity0.getInitRoll());
		assertEquals(new Integer(25), entity0.getHitpoints());
		assertEquals(null, entity0.getSubdual());
		mockListener.expectNoEvents();
		entity0.subdue(0);
		mockListener.expectNoEvents();
		assertEquals(1, dataModel.getRowCount());
		Entity entity1 = dataModel.getEntity(0);
		assertEquals("G", entity1.getAbbreviation());
		assertEquals("Ogre 1", entity1.getName());
		assertEquals(new Integer(12), entity1.getInitRoll());
		assertEquals(new Integer(25), entity1.getHitpoints());
		assertEquals(new Integer(0), entity1.getSubdual());
	}
	@Test
	public void testDamageZero()
	{
		Entity row1 = new Entity();
		row1.setAbbreviation("G");
		row1.setName("Ogre 1");
		row1.setInitRoll(12);
		row1.setHitpoints(25);
//		row1.setSubdual(5);
		mockListener.expectEvent();
		dataModel.addEntity(row1);
		mockListener.expectNoEvents();
		assertEquals(1, dataModel.getRowCount());
		Entity entity0 = dataModel.getEntity(0);
		assertEquals("G", entity0.getAbbreviation());
		assertEquals("Ogre 1", entity0.getName());
		assertEquals(new Integer(12), entity0.getInitRoll());
		assertEquals(new Integer(25), entity0.getHitpoints());
		assertEquals(null, entity0.getSubdual());
		mockListener.expectNoEvents();
		entity0.damage(0);
		mockListener.expectNoEvents();
		assertEquals(1, dataModel.getRowCount());
		Entity entity1 = dataModel.getEntity(0);
		assertEquals("G", entity1.getAbbreviation());
		assertEquals("Ogre 1", entity1.getName());
		assertEquals(new Integer(12), entity1.getInitRoll());
		assertEquals(new Integer(25), entity1.getHitpoints());
		//assertEquals(new Integer(3), entity1.getSubdual());
	}
	@Test
	public void testHealDamageZero()
	{
		Entity row1 = new Entity();
		row1.setAbbreviation("G");
		row1.setName("Ogre 1");
		row1.setInitRoll(12);
		row1.setHitpoints(25);
//		row1.setSubdual(5);
		mockListener.expectEvent();
		dataModel.addEntity(row1);
		mockListener.expectNoEvents();
		assertEquals(1, dataModel.getRowCount());
		Entity entity0 = dataModel.getEntity(0);
		assertEquals("G", entity0.getAbbreviation());
		assertEquals("Ogre 1", entity0.getName());
		assertEquals(new Integer(12), entity0.getInitRoll());
		assertEquals(new Integer(25), entity0.getHitpoints());
		assertEquals(null, entity0.getSubdual());
		mockListener.expectEvent();
		entity0.damage(4);
		mockListener.expectNoEvents();
		assertEquals(1, dataModel.getRowCount());
		Entity entity1 = dataModel.getEntity(0);
		assertEquals("G", entity1.getAbbreviation());
		assertEquals("Ogre 1", entity1.getName());
		assertEquals(new Integer(12), entity1.getInitRoll());
		assertEquals(new Integer(21), entity1.getHitpoints());
		//assertEquals(new Integer(3), entity1.getSubdual());
		mockListener.expectNoEvents();
		entity0.heal(0);
		mockListener.expectNoEvents();
		assertEquals(new Integer(21), entity1.getHitpoints());

	}
	@Test
	public void testHealSubdualZero()
	{
		Entity row1 = new Entity();
		row1.setAbbreviation("G");
		row1.setName("Ogre 1");
		row1.setInitRoll(12);
		row1.setHitpoints(25);
//		row1.setSubdual(5);
		mockListener.expectEvent();
		dataModel.addEntity(row1);
		mockListener.expectNoEvents();
		assertEquals(1, dataModel.getRowCount());
		Entity entity0 = dataModel.getEntity(0);
		assertEquals("G", entity0.getAbbreviation());
		assertEquals("Ogre 1", entity0.getName());
		assertEquals(new Integer(12), entity0.getInitRoll());
		assertEquals(new Integer(25), entity0.getHitpoints());
		assertEquals(null, entity0.getSubdual());
		mockListener.expectEvent();
		entity0.subdue(3);
		mockListener.expectNoEvents();
		assertEquals(1, dataModel.getRowCount());
		Entity entity1 = dataModel.getEntity(0);
		assertEquals("G", entity1.getAbbreviation());
		assertEquals("Ogre 1", entity1.getName());
		assertEquals(new Integer(12), entity1.getInitRoll());
		assertEquals(new Integer(25), entity1.getHitpoints());
		assertEquals(new Integer(3), entity1.getSubdual());
		mockListener.expectNoEvents();
		entity0.healSubdual(0);
		mockListener.expectNoEvents();
		assertEquals(1, dataModel.getRowCount());
		assertEquals(new Integer(3), dataModel.getEntity(0).getSubdual());
		mockListener.expectNoEvents();
	}


	public void testSetValueAt()
	{
		Entity row1 = new Entity();
		row1.setAbbreviation("G");
		row1.setName("Ogre 1");
		row1.setInitRoll(12);
		row1.setHitpoints(25);
		row1.setSubdual(5);
		mockListener.expectEvent();
		dataModel.addEntity(row1);
		mockListener.expectNoEvents();

		mockListener.expectEvent();
		dataModel.setValueAt(new Integer(7), 0, EntityListGwtable.COLUMN_NUMBER_HP);
		mockListener.expectNoEvents();

		{
			Entity entity1 = dataModel.getEntity(0);
			assertEquals("G", entity1.getAbbreviation());
			assertEquals("Ogre 1", entity1.getName());
			assertEquals(new Integer(12), entity1.getInitRoll());
			assertEquals(new Integer(7), entity1.getHitpoints());
			assertEquals(new Integer(5), entity1.getSubdual());
		}

		mockListener.expectNoEvents();
		dataModel.setValueAt(new Integer(7), 0, EntityListGwtable.COLUMN_NUMBER_HP);
		mockListener.expectNoEvents();



	}

	@Test
	public void testSetInitCount()
	{
		mockListener.expectEvent();
		dataModel.setInitCount(5);
		assertEquals(new Integer(5), dataModel.getInitCount());

		mockListener.expectEvent();
		dataModel.setInitCount(-3);
		assertEquals(new Integer(-3), dataModel.getInitCount());

		mockListener.expectNoEvents();
		dataModel.setInitCount(-3);
		assertEquals(new Integer(-3), dataModel.getInitCount());

		mockListener.expectEvent();
		dataModel.setInitCount(0);
		assertEquals(new Integer(0), dataModel.getInitCount());

	}

	@Test
	public void testRemove()
	{
		Entity row1 = new Entity();
		row1.setAbbreviation("G");
		row1.setName("Ogre 1");
		row1.setInitRoll(12);
		row1.setHitpoints(25);
		mockListener.expectEvent();
		dataModel.addEntity(row1);
		mockListener.expectNoEvents();
		assertEquals(1, dataModel.getRowCount());
		Entity entity0 = dataModel.getEntity(0);
		assertEquals("G", entity0.getAbbreviation());
		assertEquals("Ogre 1", entity0.getName());
		assertEquals(new Integer(12), entity0.getInitRoll());
		assertEquals(new Integer(25), entity0.getHitpoints());
		mockListener.expectNoEvents();

		Entity row2 = new Entity();
		row2.setAbbreviation("G");
		row2.setName("Ogre 2");
		row2.setInitRoll(10);
		row2.setHitpoints(27);
		mockListener.expectEvent();
		dataModel.addEntity(row2);
		mockListener.expectNoEvents();
		entity0 = dataModel.getEntity(0);
		assertEquals(2, dataModel.getRowCount());
		assertEquals("G1", entity0.getAbbreviation());
		assertEquals("Ogre 1", entity0.getName());
		assertEquals(new Integer(12), entity0.getInitRoll());
		assertEquals(new Integer(25), entity0.getHitpoints());
		mockListener.expectNoEvents();

		mockListener.expectEvent();
		dataModel.remove(1);
		mockListener.expectNoEvents();
		assertEquals(1, dataModel.getRowCount());
		Entity entity1 = dataModel.getEntity(0);
		assertEquals("G1", entity1.getAbbreviation());
		assertEquals("Ogre 1", entity1.getName());
		assertEquals(new Integer(12), entity1.getInitRoll());
		assertEquals(new Integer(25), entity1.getHitpoints());
		mockListener.expectNoEvents();

		mockListener.expectEvent();
		dataModel.remove(0);
		mockListener.expectNoEvents();
		assertEquals(0, dataModel.getRowCount());

		mockListener.expectNoEvents();
		try
		{
			dataModel.remove(0);
		}
		catch(Exception e)
		{
			// Whatever, don't really care if there's an exception or not.
		}
		mockListener.expectNoEvents();
		assertEquals(0, dataModel.getRowCount());

		mockListener.expectNoEvents();
	}

	@Test
    public final void testClear() {
	    fillTable();

        assertEquals(4, dataModel.getRowCount());
	    mockListener.expectEvent();
        dataModel.clear();
        assertEquals(0, dataModel.getRowCount());
        mockListener.expectNoEvents();
        dataModel.clear();
        assertEquals(0, dataModel.getRowCount());
    }

	@Test
	public final void testImportExport() throws IOException {
	    fillTable();
        assertEquals(4, dataModel.getRowCount());
	    File tmpfile = File.createTempFile("dmassist-test-1", null);
	    mockListener.expectNoEvents();
	    dataModel.save(tmpfile);
	    mockListener.expectEvent();
	    dataModel.clear();
        assertEquals(0, dataModel.getRowCount());
	    mockListener.expectEvent();
	    dataModel.importFile(tmpfile);
        assertEquals(4, dataModel.getRowCount());
	}
}


