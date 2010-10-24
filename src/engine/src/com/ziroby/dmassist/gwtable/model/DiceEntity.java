package com.ziroby.dmassist.gwtable.model;

import com.ziroby.dmassist.model.DiceEquation;

/** An enhanced entity that accepts Dice Equations
 *
 * @author ziroby
 *
 */
public class DiceEntity extends Entity {
	private String initDiceString;
	private Integer initValue;

	@Override
	public void setInitRoll(String text) {
		this.initDiceString = text;
		DiceEquation.tryParseInitValue(text);
	}

	@Override
	public void startCombat() {
		if (initValue == null) {
			initValue = DiceEquation.tryParseInitValue(getInitDiceString());
			dirty = true;
			alertListeners();
		}
	}

	@Override
	public final Integer getInitRoll() {
		if (initValue != null)
			return initValue;
		
		return super.getInitRoll();
	}

	@Override
	public void endCombat() {
		initValue = null;
	}

	@Override
	public String getInitDiceString() {
		return initDiceString;
	}
}
