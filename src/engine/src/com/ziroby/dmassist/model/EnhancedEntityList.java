package com.ziroby.dmassist.model;

import java.util.ArrayList;
import java.util.Collection;

import com.ziroby.dmassist.gwtable.model.Entity;

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
