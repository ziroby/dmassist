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

import junit.framework.TestCase;

import org.junit.Test;

import com.ziroby.dmassist.gwtable.model.Entity;
import com.ziroby.dmassist.gwtable.model.Entity.DamageType;
import com.ziroby.dmassist.gwtable.util.Listener;
import com.ziroby.dmassist.gwtable.util.ObjectEvent;

public class EntityTest extends TestCase{

    /**
     * @see junit.framework.TestCase#setUp()
     */
    @Override
    protected void setUp() throws Exception {
        super.setUp();

        listener = new MockListener();
        entity = new Entity();
        entity.addListener(listener);
        listener.expectNoEvents();
    }

    private MockListener listener;
    private Entity entity;

    /**
     * A primitive mock listener. This should really be using a mock framework,
     * but oh well.
     *
     * @author Ron "Ziroby" Romero
     *
     */
    class MockListener implements Listener
    {
        /**
         * Do we expect to get events sent to us?  Set to false when we're not supposed
         * to get events, then set to true when we are.
         */
        private boolean expectEvents = false;

        /**
         */
        public void objectChanged(ObjectEvent event) {
            if (!expectEvents)
            {
                throw new junit.framework.AssertionFailedError("Received a table changed event when we shouldn't have");
            }
            // OK, we expected that.  But don't get any more.
            expectEvents = false;
        }

        void expectNoEvents()
        {
            if (expectEvents == true)
            {
                //Oops, we expected an event and didn't get it.
                throw new junit.framework.AssertionFailedError("Did not get expected event");
            }
            expectEvents = false;
        }

        /**
         * The mock object should expect exactly one event.
         */
        public void expectEvent() {
            if (expectEvents == true)
            {
                //Oops, we expected an event and didn't get it.
                throw new junit.framework.AssertionFailedError("Did not get expected event");
            }
            expectEvents = true;
        }
    }
    @Test
    public final void testSetAbbreviation() {
        listener.expectEvent();
        entity.setAbbreviation("F");
        listener.expectNoEvents();

        assertEquals("F", entity.getAbbreviation());
        listener.expectNoEvents();
    }
    @Test
    public final void testSetAbbreviationUnchanged() {
        listener.expectEvent();
        entity.setAbbreviation("F");
        listener.expectNoEvents();
        assertEquals("F", entity.getAbbreviation());

        listener.expectNoEvents();
        entity.setAbbreviation("F");
        listener.expectNoEvents();
        assertEquals("F", entity.getAbbreviation());
    }


    @Test
    public final void testSetAbbreviationNullUnchanged() {
        listener.expectNoEvents();
        entity.setAbbreviation(null);
        listener.expectNoEvents();
        assertEquals(null, entity.getAbbreviation());

        listener.expectNoEvents();
        entity.setAbbreviation(null);
        listener.expectNoEvents();
        assertEquals(null, entity.getAbbreviation());
    }


    @Test
    public final void testSetName() {
        listener.expectEvent();
        entity.setName("Ziroby");
        listener.expectNoEvents();

        assertEquals("Ziroby", entity.getName());
        listener.expectNoEvents();
    }

    @Test
    public final void testSetNameUnchanged() {
        listener.expectEvent();
        entity.setName("Ziroby");
        listener.expectNoEvents();

        assertEquals("Ziroby", entity.getName());
        listener.expectNoEvents();
        entity.setName("Ziroby");
        listener.expectNoEvents();
    }

    @Test
    public final void testSetNameNullUnchanged() {
        listener.expectNoEvents();
        entity.setName(null);
        listener.expectNoEvents();

        assertEquals(null, entity.getName());
        listener.expectNoEvents();
        entity.setName(null);
        listener.expectNoEvents();
        assertEquals(null, entity.getName());
    }

    @Test
    public final void testSetInitRollInteger() {
        listener.expectEvent();
        entity.setInitRoll(new Integer(5));
        listener.expectNoEvents();

        assertEquals(new Integer(5), entity.getInitRoll());
        listener.expectNoEvents();
    }

    @Test
    public final void testSetInitRollIntegerUnchanged() {
        listener.expectEvent();
        entity.setInitRoll(new Integer(5));
        listener.expectNoEvents();

        assertEquals(new Integer(5), entity.getInitRoll());
        listener.expectNoEvents();
        entity.setInitRoll(new Integer(5));

        assertEquals(new Integer(5), entity.getInitRoll());
        listener.expectNoEvents();
        entity.setInitRoll("  5");

        assertEquals(new Integer(5), entity.getInitRoll());
        listener.expectNoEvents();
        entity.setInitRoll(new Integer(5));

        listener.expectNoEvents();
    }
    @Test
    public final void testSetInitRollIntegerNullUnchanged() {
        Integer i = null;
        listener.expectNoEvents();
        entity.setInitRoll(i);
        listener.expectNoEvents();

        assertEquals(null, entity.getInitRoll());
        listener.expectNoEvents();
        entity.setInitRoll(i);

        assertEquals(null, entity.getInitRoll());
        listener.expectNoEvents();
        String s = null;
        entity.setInitRoll(s);

        assertEquals(null, entity.getInitRoll());
        listener.expectNoEvents();
        entity.setInitRoll(s);

        assertEquals(null, entity.getInitRoll());
        listener.expectNoEvents();
    }

    @Test
    public final void testSetHitpointsInteger() {
        listener.expectEvent();
        entity.setHitpoints(new Integer(5));
        listener.expectNoEvents();

        assertEquals(new Integer(5), entity.getHitpoints());
        listener.expectNoEvents();
        entity.setHitpoints(new Integer(5));
        listener.expectNoEvents();
    }


    @Test
    public final void testSetHitpointsIntegerUnchanged() {
        listener.expectEvent();
        entity.setHitpoints(new Integer(5));
        listener.expectNoEvents();

        assertEquals(new Integer(5), entity.getHitpoints());
        listener.expectNoEvents();
        entity.setHitpoints(new Integer(5));

        assertEquals(new Integer(5), entity.getHitpoints());
        listener.expectNoEvents();
        entity.setHitpoints(" 5 ");

        listener.expectNoEvents();
        entity.setHitpoints("5");
        listener.expectNoEvents();
    }

    @Test
    public final void testSetHitpointsNullUnchanged() {
        Integer i = null;
        listener.expectNoEvents();
        entity.setHitpoints(i);
        listener.expectNoEvents();

        assertEquals(null, entity.getHitpoints());
        listener.expectNoEvents();
        entity.setHitpoints(i);

        assertEquals(null, entity.getHitpoints());
        listener.expectNoEvents();
        String s = null;
        entity.setHitpoints(s);

        assertEquals(null, entity.getHitpoints());
        listener.expectNoEvents();
        entity.setHitpoints(s);
        listener.expectNoEvents();
        assertEquals(null, entity.getHitpoints());
    }

    @Test
    public final void testSetInitRollString() {
        listener.expectEvent();
        entity.setInitRoll(" 5 ");
        listener.expectNoEvents();

        assertEquals(new Integer(5), entity.getInitRoll());
        listener.expectNoEvents();
        entity.setInitRoll(" 5");
        listener.expectNoEvents();
    }

    @Test
    public final void testSetInitRollStringBadString() {
        listener.expectNoEvents();
        entity.setInitRoll(" x5 ");
        listener.expectNoEvents();

        assertEquals(null, entity.getInitRoll());
        listener.expectNoEvents();
        entity.setInitRoll(" x5 ");
        listener.expectNoEvents();

    }

    @Test
    public final void testSetHitpointsStringBadString() {
        listener.expectNoEvents();
        entity.setHitpoints(" x5 ");
        listener.expectNoEvents();

        assertEquals(null, entity.getHitpoints());
        listener.expectNoEvents();
    }

    @Test
    public final void testSetSubdualString() {
        listener.expectEvent();
        entity.setSubdual(" 5 ");
        listener.expectNoEvents();

        assertEquals(new Integer(5), entity.getSubdual());
        listener.expectNoEvents();
        entity.setSubdual(" 5 ");
        listener.expectNoEvents();
    }

    @Test
    public final void testSetSubdualNullUnchanged() {
        Integer i = null;
        listener.expectNoEvents();
        entity.setSubdual(i);
        listener.expectNoEvents();

        assertEquals(null, entity.getSubdual());
        listener.expectNoEvents();
        entity.setSubdual(i);
        listener.expectNoEvents();
        assertEquals(null, entity.getSubdual());

        String s = null;
        listener.expectNoEvents();
        entity.setSubdual(s);
        listener.expectNoEvents();

        assertEquals(null, entity.getSubdual());
        listener.expectNoEvents();
        entity.setSubdual(s);
        listener.expectNoEvents();
        assertEquals(null, entity.getSubdual());
    }

    //	@Test
    //	@Ignore // I don't want to bother with this right now.
    //	public final void testSetColumn() {
    //		fail("Not yet implemented");
    //	}

    @Test
    public final void testDamage() {
        listener.expectEvent();
        entity.setHitpoints(new Integer(5));
        listener.expectNoEvents();

        assertEquals(new Integer(5), entity.getHitpoints());
        listener.expectEvent();
        entity.damage(3);
        assertEquals(new Integer(2), entity.getHitpoints());
        listener.expectNoEvents();
    }

    @Test
    public final void testDamage2() {
        listener.expectEvent();
        entity.setHitpoints(new Integer(5));
        listener.expectNoEvents();

        assertEquals(new Integer(5), entity.getHitpoints());
        listener.expectEvent();
        entity.damage(DamageType.NORMAL_DAMAGE, 3);
        assertEquals(new Integer(2), entity.getHitpoints());
        listener.expectNoEvents();
    }

    @Test
    public final void testDamageZero() {
        listener.expectEvent();
        entity.setHitpoints(new Integer(5));
        listener.expectNoEvents();

        assertEquals(new Integer(5), entity.getHitpoints());
        listener.expectNoEvents();
        entity.damage(0);
        assertEquals(new Integer(5), entity.getHitpoints());
        listener.expectNoEvents();
    }

    @Test
    public final void testSubdue() {
        listener.expectEvent();
        entity.setSubdual(new Integer(5));
        listener.expectNoEvents();

        assertEquals(new Integer(5), entity.getSubdual());
        listener.expectEvent();
        entity.subdue(3);
        assertEquals(new Integer(8), entity.getSubdual());
        listener.expectNoEvents();
    }

    @Test
    public final void testSubdue2() {
        listener.expectEvent();
        entity.setSubdual(new Integer(5));
        listener.expectNoEvents();

        assertEquals(new Integer(5), entity.getSubdual());
        listener.expectEvent();
        entity.damage(DamageType.SUBDUAL, 3);
        assertEquals(new Integer(8), entity.getSubdual());
        listener.expectNoEvents();
    }

    @Test
    public final void testSubdueNull() {
        assertEquals(null, entity.getSubdual());
        listener.expectEvent();
        entity.subdue(7);
        assertEquals(new Integer(7), entity.getSubdual());
        listener.expectNoEvents();
    }

    @Test
    public final void testSubdueZero() {
        listener.expectEvent();
        entity.setHitpoints(new Integer(5));
        listener.expectNoEvents();

        assertEquals(new Integer(5), entity.getHitpoints());
        listener.expectNoEvents();
        entity.subdue(0);
        assertEquals(new Integer(5), entity.getHitpoints());
        listener.expectNoEvents();
    }

    @Test
    public final void testHeal() {
        listener.expectEvent();
        entity.setHitpoints(new Integer(5));
        listener.expectNoEvents();

        assertEquals(new Integer(5), entity.getHitpoints());
        listener.expectEvent();
        entity.damage(4);
        assertEquals(new Integer(1), entity.getHitpoints());
        listener.expectEvent();
        entity.heal(6);
        assertEquals(new Integer(7), entity.getHitpoints());
    }

    @Test
    public final void testHeal2() {
        listener.expectEvent();
        entity.setHitpoints(new Integer(5));
        listener.expectNoEvents();

        assertEquals(new Integer(5), entity.getHitpoints());
        listener.expectEvent();
        entity.damage(4);
        assertEquals(new Integer(1), entity.getHitpoints());
        listener.expectEvent();
        entity.damage(DamageType.HEAL, 6);
        assertEquals(new Integer(7), entity.getHitpoints());
    }

    @Test
    public final void testHealZero() {
        listener.expectEvent();
        entity.setHitpoints(new Integer(5));
        listener.expectNoEvents();

        assertEquals(new Integer(5), entity.getHitpoints());
        listener.expectNoEvents();
        entity.heal(0);
        assertEquals(new Integer(5), entity.getHitpoints());
        listener.expectNoEvents();
    }

    @Test
    public final void testHealSubdualZero() {
        listener.expectEvent();
        entity.setHitpoints(new Integer(5));
        listener.expectNoEvents();

        assertEquals(new Integer(5), entity.getHitpoints());
        listener.expectNoEvents();
        entity.healSubdual(0);
        assertEquals(new Integer(5), entity.getHitpoints());
        listener.expectNoEvents();
    }

    @Test
    public final void testHealSubdual() {
        listener.expectEvent();
        entity.setSubdual(new Integer(5));
        listener.expectNoEvents();

        assertEquals(new Integer(5), entity.getSubdual());
        listener.expectEvent();
        entity.subdue(3);
        assertEquals(new Integer(8), entity.getSubdual());
        listener.expectEvent();
        entity.healSubdual(6);
        assertEquals(new Integer(2), entity.getSubdual());
        listener.expectNoEvents();
    }

    @Test
    public final void testHealSubdual2() {
        listener.expectEvent();
        entity.setSubdual(new Integer(5));
        listener.expectNoEvents();

        assertEquals(new Integer(5), entity.getSubdual());
        listener.expectEvent();
        entity.subdue(3);
        assertEquals(new Integer(8), entity.getSubdual());
        listener.expectEvent();
        entity.damage(DamageType.HEAL_SUBDUAL, 6);
        assertEquals(new Integer(2), entity.getSubdual());
        listener.expectNoEvents();
    }


    @Test
    public final void testHealSubdualToNone() {
        listener.expectEvent();
        entity.setSubdual(new Integer(5));
        listener.expectNoEvents();

        assertEquals(new Integer(5), entity.getSubdual());
        listener.expectEvent();
        entity.subdue(3);
        assertEquals(new Integer(8), entity.getSubdual());
        listener.expectEvent();
        entity.healSubdual(9);
        assertEquals(null, entity.getSubdual());
        listener.expectNoEvents();
    }


    @Test
    public final void testHealSubdualToNone2() {
        listener.expectEvent();
        entity.setSubdual(new Integer(5));
        listener.expectNoEvents();

        assertEquals(new Integer(5), entity.getSubdual());
        listener.expectEvent();
        entity.subdue(3);
        assertEquals(new Integer(8), entity.getSubdual());
        listener.expectEvent();
        entity.healSubdual(8);
        assertEquals(null, entity.getSubdual());
        listener.expectNoEvents();
    }


    @Test
    public final void testHealSubdualFromNull() {
        assertEquals(null, entity.getSubdual());
        listener.expectEvent();
        entity.healSubdual(3);
        listener.expectNoEvents();
    }

    @Test
    public final void testHealSubdualFromNone() {
        listener.expectEvent();
        entity.setSubdual(new Integer(0));
        listener.expectNoEvents();

        assertEquals(new Integer(0), entity.getSubdual());
        listener.expectEvent();
        entity.healSubdual(3);
        listener.expectNoEvents();
    }

    @Test
    public final void testSetSubdualInteger() {
        listener.expectEvent();
        entity.setSubdual(new Integer(5));
        listener.expectNoEvents();

        assertEquals(new Integer(5), entity.getSubdual());
        listener.expectNoEvents();
    }
    @Test
    public final void testSetType() {
        listener.expectEvent();
        entity.setEntityType(Entity.EntityType.MONSTER);
        listener.expectNoEvents();

        assertEquals(Entity.EntityType.MONSTER, entity.getEntityType());
        listener.expectNoEvents();
    }
    @Test
    public final void testSettypeUnchanged() {
        listener.expectEvent();
        entity.setEntityType(Entity.EntityType.NPC);
        listener.expectNoEvents();
        assertEquals(Entity.EntityType.NPC, entity.getEntityType());

        listener.expectNoEvents();
        entity.setEntityType(Entity.EntityType.NPC);
        listener.expectNoEvents();
        assertEquals(Entity.EntityType.NPC, entity.getEntityType());
    }
}

