package com.ziroby.dmassist.model;

import com.ziroby.dmassist.gwtable.model.Entity;
import com.ziroby.dmassist.gwtable.util.StringUtil;

public class EnhancedEntity extends Entity {
	private String initDiceString;

	@Override
	public void setInitRoll(String text) {
		if (StringUtil.isBareModifier(text)) {
			int modifier = StringUtil.tryParseInt(text);
			String diceString = "1d20 + " + modifier;

			this.setInitDiceString(text);
			super.setInitRoll(DiceEquation.tryParseInt(diceString));
		
		} else if (StringUtil.isIntegerString(text)) {
			super.setInitRoll(text);
			this.setInitDiceString(null);
		} else {
			super.setInitRoll(DiceEquation.tryParseInt(text));
			this.setInitDiceString(text);
		}
	}

	public String getInitDiceString() {
		return initDiceString;
	}

	public void setInitDiceString(String initDiceString) {
		this.initDiceString = initDiceString;
	}
}
