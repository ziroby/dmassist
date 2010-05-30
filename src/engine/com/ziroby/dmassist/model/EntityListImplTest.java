package com.ziroby.dmassist.model;

import junit.framework.TestCase;

import org.junit.Before;
import org.junit.Test;

import com.ziroby.dmassist.model.test.MockTableModelListener;


public class EntityListImplTest extends TestCase
{
    private EntityList dataModel;
    private MockTableModelListener mockListener;

    /**
     * @throws java.lang.Exception
     */
    @Override
    @Before
    public void setUp() throws Exception {
        dataModel = new EntityListImpl();
        
        mockListener = new MockTableModelListener();
        dataModel.addListener(mockListener);
        assertEquals(0, dataModel.getRowCount());
        
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

}
