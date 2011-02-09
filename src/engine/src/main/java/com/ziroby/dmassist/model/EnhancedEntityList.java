package com.ziroby.dmassist.model;

import java.util.ArrayList;
import java.util.Collection;

import com.ziroby.dmassist.gwtable.model.Entity;
import com.ziroby.dmassist.gwtable.model.Entity.Type;

public class EnhancedEntityList extends EntityListImpl {

	public static final String COLUMN_NAME_INIT_DICE = "initDice";
	public static final String COLUMN_NAME_HIT_DICE = "hitDice";

	public Collection<EnhancedEntity> getEnhancedEntities() {
		Collection<EnhancedEntity> returnValue = new ArrayList<EnhancedEntity>();

		// We assume this will work.
		for (Entity entity : getEntities()) {
			returnValue.add((EnhancedEntity) entity);
		}

		return returnValue;
	}

	@Override
	public void resetNumRounds() {
		enterPublicMethod();

		super.resetNumRounds();

		rerollEachCreature();

		leavePublicMethod();
	}

	private void rerollEachCreature() {
		for (EnhancedEntity entity : getEnhancedEntities()) {
			entity.reroll();
		}
	}

	
    @Override
    public void addSampleData() {
        Entity row1 = new EnhancedEntity();
        row1.setAbbreviation("O"); //$NON-NLS-1$
        row1.setName("Ogre"); //$NON-NLS-1$
        row1.setInitRoll(12);
        row1.setHitpoints(25);
        row1.setType(Type.MONSTER);
        addEntity(row1);

        Entity row2 = new EnhancedEntity();
        row2.setAbbreviation("G1"); //$NON-NLS-1$
        row2.setName("Goblin 1"); //$NON-NLS-1$
        row2.setInitRoll(4);
        row2.setHitpoints(8);
        row2.setSubdual(3);
        row2.setType(Type.SRD_MONSTER);
        addEntity(row2);

        Entity row4 = new EnhancedEntity();
        row4.setName("Acid Arrow"); //$NON-NLS-1$
        row4.setInitRoll(4);
        row4.setRoundsLeft(3);
        row4.setType(Type.SRD_SPELL);
        addEntity(row4);

        Entity row3 = new EnhancedEntity();
        row3.setAbbreviation("G2"); //$NON-NLS-1$
        row3.setName("Goblin 2"); //$NON-NLS-1$
        row3.setInitRoll(15);
        row3.setHitpoints(3);
        row3.setType(Type.SRD_MONSTER);
        addEntity(row3);

        Entity row5 = new EnhancedEntity();
        //row3.setAbbreviation("G2"); //$NON-NLS-1$
        row5.setName("Ziroby"); //$NON-NLS-1$
        row5.setInitRoll(25);
        row5.setHitpoints(54);
        row5.setType(Type.PC);
        addEntity(row5);

        Entity row6 = new EnhancedEntity();
        row6.setAbbreviation("CB"); //$NON-NLS-1$
        row6.setName("Summoned Celestial Badger"); //$NON-NLS-1$
        row6.setInitRoll(25);
        row6.setHitpoints(6);
        row6.setRoundsLeft(5);
        row6.setType(Type.EFFECT);
        addEntity(row6);
}

	/**
	 * We assume all the entities in the list are EnhancedEntity's, and cast
	 * without checking.
	 * 
	 * @throws IllegalCastException
	 *             if the entity is not an EnhancedEntity.
	 */
	public EnhancedEntity getEnhancedEntity(int position) {
		return (EnhancedEntity) getEntity(position);
	}
}
