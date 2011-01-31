package com.ziroby.android.dmassist.android;

import android.os.Bundle;

import com.ziroby.android.dmassist.AndroidEntityUtil;
import com.ziroby.dmassist.gwtable.model.Entity;
import com.ziroby.dmassist.gwtable.model.Entity.Type;
import com.ziroby.dmassist.model.EnhancedEntity;

import junit.framework.TestCase;

public class AndroidEntityUtilsTest extends TestCase {
	public void testDummy() throws Exception {
		assertTrue(true);
	}
	public void testEntityRemovedFromBundleShouldEqualEntityPutIn() throws Exception {
        EnhancedEntity entity = createSampleEntity1();

        Bundle bundle = AndroidEntityUtil.putEntityFieldsInBundle(entity);
        Entity entityFromBundle = AndroidEntityUtil.getEnhancedEntityFromBundle(bundle);
		
        assertEquals(entity, entityFromBundle);
	}
	private EnhancedEntity createSampleEntity1() {
		EnhancedEntity entity = new EnhancedEntity();
        entity.setAbbreviation("O"); //$NON-NLS-1$
        entity.setName("Ogre"); //$NON-NLS-1$
        entity.setInitRoll(12);
        entity.setHitDiceString("1d4");
        entity.setHitpoints(25);
        entity.setInitDiceString("+12");
        entity.setType(Type.MONSTER);
		return entity;
	}
}
