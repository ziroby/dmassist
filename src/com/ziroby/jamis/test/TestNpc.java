package com.ziroby.jamis.test;

import static org.junit.Assert.*;

import org.junit.Test;

import com.ziroby.jamis.Npc;

public class TestNpc
{

    @Test
    public void testGen() {
        String npc = Npc.gen();
        assertNotNull(npc);
    }

}
