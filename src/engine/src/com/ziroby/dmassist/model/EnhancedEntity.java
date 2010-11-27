package com.ziroby.dmassist.model;

import com.ziroby.dmassist.gwtable.model.Entity;
import com.ziroby.dmassist.gwtable.util.StringUtil;

public class EnhancedEntity extends Entity {
	private String initDiceString;

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

	public String getInitDiceString() {
		return initDiceString;
	}

	public void setInitDiceString(String initDiceString) {
		this.initDiceString = initDiceString;
	}

	public void reroll() {
		if (initDiceString != null)
			super.setInitRoll(tryParseModifier(initDiceString));
	}
}
