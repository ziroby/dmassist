package com.ziroby.jamis.test;

import static org.junit.Assert.*;

import org.junit.Test;

import com.ziroby.jamis.Npc;

public class TestNpc
{
    private final static int NUMBER_TO_TEST = 10;
    
    @Test
    public void testGen() {
        String npc = Npc.gen();
        assertNotNull(npc);
    }

    @Test
    public void testGenMany() {
        for (int i=0; i<NUMBER_TO_TEST; ++i) {
            String npc = Npc.gen();
            assertNotNull(npc);
        }
    }

    @Test
    public void testHelp() {
        
        String help = Npc.gen("npc -h");
        assertNotNull(help);
        help = Npc.gen("npc -h");
        assertNotNull(help);
    }

    @Test
    public void testBadClass() {
        String s1 = Npc.gen("npc -c foo");
        assertNotNull(s1);
        String s2 = Npc.gen("npc -c foo");
        assertNotNull(s2);
        assertEquals(s1, s2);
    }

    @Test
    public void testBadClass2() {
        String s1 = Npc.gen("npc -c foo");
        assertNotNull(s1);
        String npc = Npc.gen();
        assertNotNull(npc);
        String s2 = Npc.gen("npc -c foo");
        assertNotNull(s2);
        assertEquals(s1, s2);
    }

}
