package com.ziroby.dmassist.model;

import com.ziroby.dmassist.gwtable.model.Entity;
import com.ziroby.dmassist.gwtable.util.StringUtil;

public class EnhancedEntity extends Entity {
	private String initDiceString;
	private String hitDiceString;
	
	@Override
	public void setInitRoll(String text) {
		if (StringUtil.isBareModifier(text)) {
			Integer newInitValue = tryParseModifier(text);

			this.setInitDiceString(text);
			super.setInitRoll(newInitValue);
		
		} else if (StringUtil.isIntegerString(text)) {
			super.setInitRoll(text);
			this.setInitDiceString(null);
		} else {
			super.setInitRoll(DiceEquation.tryParseInt(text));
			this.setInitDiceString(text);
		}
		
		// I could check to see if it's actually changed, but I'm lazy.
		alertListeners();
	}

	private Integer tryParseModifier(String text) {
		if (StringUtil.isBareModifier(text)) {
			int modifier = StringUtil.tryParseInt(text);
			String diceString = "1d20 + " + modifier;
			Integer newInitValue = DiceEquation.tryParseInt(diceString);
			return newInitValue;
		}
		
		return DiceEquation.tryParseInt(text);
	}

	@Override
	public void setHitpoints(String text) {
		if (StringUtil.isIntegerString(text)) {
			super.setHitpoints(text);
			this.setHitDiceString(null);
		} else {
			super.setHitpoints(DiceEquation.tryParseInt(text));
			this.setHitDiceString(text);
		}	
	}
	
	public void reroll() {
		if (initDiceString != null)
			super.setInitRoll(tryParseModifier(initDiceString));
		if (hitDiceString != null)
			super.setHitpoints(DiceEquation.tryParseInt(hitDiceString));
	}

	public String getInitDiceString() {
		return initDiceString;
	}

	public void setInitDiceString(String initDiceString) {
		this.initDiceString = initDiceString;
	}

	public void setHitDiceString(String hitDiceString) {
		this.hitDiceString = hitDiceString;
	}

	public String getHitDiceString() {
		return hitDiceString;
	}

	@Override
	public int hashCode() {
		final int prime = 31;
		int result = 1;
		result = prime * result
				+ ((hitDiceString == null) ? 0 : hitDiceString.hashCode());
		result = prime * result
				+ ((initDiceString == null) ? 0 : initDiceString.hashCode());
		return result;
	}

	@Override
	public boolean equals(Object obj) {
		if (this == obj)
			return true;
		if (!super.equals(obj))
			return false;
		if (getClass() != obj.getClass())
			return false;
		EnhancedEntity other = (EnhancedEntity) obj;
		if (hitDiceString == null) {
			if (other.hitDiceString != null)
				return false;
		} else if (!hitDiceString.equals(other.hitDiceString))
			return false;
		if (initDiceString == null) {
			if (other.initDiceString != null)
				return false;
		} else if (!initDiceString.equals(other.initDiceString))
			return false;
		return true;
	}

}
