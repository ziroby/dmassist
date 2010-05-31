/*
 *   Copyright 2009 Ron "Ziroby" Romero
 * 
 *   This file is part of DM Assist.
 *
 *   DM Assist is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   DM Assist is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with DM Assist.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
package com.ziroby.dmassist.model;

import java.util.List;
import java.util.Map;
import java.util.TreeMap;

import com.ziroby.util.AbbrevUtil;
import com.ziroby.util.AbstractListenable;
import com.ziroby.util.StringUtil;

/**
 * A character or effect.  This is one "row" in the initiative table.
 * Holds the attributes we care about.  If a value is not relevant,
 * it should be null.
 * 
 * @author Ron Romero
 *
 * @todo This class should be split into pure entity, and the stuff for
 * initiative table row.  The latter would inherit from the former. 
 */

public class Entity extends AbstractListenable {
    
    /**
     * The different type of damage or healing which can be done
     * to an entity.
     * 
     * @author Ron Romero
     *
     */
    public enum DamageType
    {
        NORMAL_DAMAGE,
        SUBDUAL,
        HEAL,
        HEAL_SUBDUAL
    }

    private String abbreviation;
	private String name;
	private Integer initRoll;
	private Integer hitpoints;
	private Integer subdual;
    private Integer roundsLeft;
	
    private boolean dirty = false;

    /**
     * The abbreviation by which the entity is called.  Abbreviations
     * shuld be unique.
     */
	public final String getAbbreviation() {
		return abbreviation;
	}

    /**
     * The short abbreviation by which the entity is called. Abbreviations shuld
     * be a few characters long and should/must be unique. Alerts listeners if
     * the abbreviation changed.
     */
	public final void setAbbreviation(String abbreviation) {
		if ((this.abbreviation != null && this.abbreviation.equals(abbreviation))
                || (abbreviation == null && this.abbreviation == null))
		{
			// It's already that value.  Don't change it or alertListeners.
			return;			
		}
		this.abbreviation = (abbreviation == null)?  null : abbreviation.trim();
		this.dirty = true;
		alertListeners();
	}

    /**
     * The name by which the entity is called.  Names do not need to be
     * unique.
     */
	public final String getName() {
		return name;
	}

    /**
     * The name by which the entity is called.  Names do not need to be
     * unique.  Alerts listeners if the name changed.
     */
	public final void setName(String name) {
		if ((this.name != null && this.name.equals(name))
                || (name == null && this.name == null))
		{
			// It's already that value.  Don't change it or alertListeners.
			return;			
		}
		this.name = (name == null)? null : name.trim();
		this.dirty = true;
		alertListeners();
	}

    /**
     * The initiative count for the entity.  Null means it's not
     * in the combat yet.
     */
	public final Integer getInitRoll() {
		return initRoll;
	}

    /**
     * The initiative count for the entity.  Null means it's not
     * in the combat yet.  Alerts listeners if changed.
     */
	public final void setInitRoll(Integer initRoll) {
		if (initRoll == null && this.initRoll == null)
			return;
		
		if (this.initRoll != null && this.initRoll.equals(initRoll))
		{
			// It's already that value.  Don't change it or alertListeners.
			return;			
		}
		this.initRoll = initRoll;
		this.dirty = true;
		alertListeners();
	}

    /**
     * The number of hitpoints the entity has left.
     */
	public final Integer getHitpoints() {
		return hitpoints;
	}

    /**
     * The number of hitpoints the entity has left.  Alerts listeners
     * if changed.
     */
	public final void setHitpoints(Integer hitpoints) {
		if (hitpoints == null && this.hitpoints == null)
			return;
		
		if (this.hitpoints != null && this.hitpoints.equals(hitpoints))
		{
			// It's already that value.  Don't change it or alertListeners.
			return;			
		}
		this.hitpoints = hitpoints;
		this.dirty = true;
		alertListeners();
	}
	
    /**
     * The amount of subdual damage the entity has sustained.  Note that 
     * subdual damage starts at null or 0, and increases as the entity
     * is subdued.
     */
    public final Integer getSubdual() {
        return subdual;
    }

    /**
     * The amount of subdual damage the entity has sustained.  Note that 
     * subdual damage starts at null or 0, and increases as the entity
     * is subdued.  Alerts listeners if changed.
     */
    public final void setSubdual(Integer subdual) {
		if (this.subdual == subdual)
		{
			// It's already that value.  Don't change it or alertListeners.
			return;			
		}    	
        this.subdual = subdual;
		this.dirty = true;
        alertListeners();
    }

    /**
     * The number of rounds until the entity is expired.  Null means the 
     * entity is permanent.  Generally, effects are temporary (have rounds
     * left), and characters are permanent (rounds left is null).
     */
	public Integer getRoundsLeft() {
        return roundsLeft;
    }

    /**
     * The number of rounds until the entity is expired.  Null means the 
     * entity is permanent.  Generally, effects are temporary (have rounds
     * left), and characters are permanent (rounds left is null).
     */
    public void setRoundsLeft(Integer roundsLeft) {
		if (this.roundsLeft == roundsLeft)
		{
			// It's already that value.  Don't change it or alertListeners.
			return;			
		}
        this.roundsLeft = roundsLeft;
		this.dirty = true;
        alertListeners();
    }

    /**
     * Sets the initiative count for the entity to the given string. If the
     * string is not a valid
     * {@link com.ziroby.dmassist.model.DiceEquation DiceEquation}, sets it to
     * null. Null means it's not in the combat yet. Alerts listeners if changed.
     */
	public void setInitRoll(String text) {
		Integer n = StringUtil.tryParseInt(text);
		setInitRoll(n);		
	}

    /**
     * The number of hitpoints the entity has left. If the string is not a valid
     * {@link com.ziroby.dmassist.model.DiceEquation DiceEquation}, sets it to
     * null. Alerts listeners if changed.
     */
	public void setHitpoints(String text) {
		Integer n = StringUtil.tryParseInt(text);
		setHitpoints(n);
	}

    /**
     * The amount of subdual damage the entity has sustained. If the string is
     * not a valid {@link com.ziroby.dmassist.model.DiceEquation DiceEquation},
     * sets it to null. Note that subdual damage starts at null or 0, and
     * increases as the entity is subdued. Alerts listeners if changed.
     */
	public void setSubdual(String text) {
		Integer n = StringUtil.tryParseInt(text);
		setSubdual(n);
	}

	/**
     * Decreases the entity's hit points by the given amount. Alerts listeners
     * if it results in a changed value.
     * 
     * @throws NullPointerException
     *             if the Entity's hitpoints were null
     */
	public void damage(Integer dmg) {
		if (hitpoints == null)
		{
			throw new NullPointerException("Hitpoints are null; can't be damaged.");
		}
		
		if (dmg != 0)
		{
			this.dirty = true;
		}
		hitpoints -= dmg;
		alertListeners();
	}

	/**
     * Increases the entity's subdual points by the given amount. Alerts
     * listeners if it results in a changed value. If the old subdual damage
     * value was null, it is converted to 0. Alerts listeners if it results in a
     * changed value.
     */
	public void subdue(Integer dmg) {
		if (subdual == null)
		{
			subdual = 0;
		}
		if (dmg != 0)
		{
			this.dirty = true;
		}
		subdual += dmg; // subdual points go opposite to hitpoints; damage goes up
		alertListeners();
	}

    /**
     * Increases the entity's hit points by the given amount. Note that there is
     * no concept of "maximum hitpoints". DM's must keep track of that manually,
     * and change the value if it exceeds maximum hitpoints. Alerts listeners if
     * it results in a changed value.
     * 
     * @throws NullPointerException
     *             if the Entity's hitpoints were null
     */
	public void heal(Integer amt) {
		if (hitpoints == null)
		{
			throw new NullPointerException("Hitpoints are null; can't be healed.");
		}
		if (amt != 0)
		{
			this.dirty = true;
		}
		hitpoints += amt;
		alertListeners();
	}

    /**
     * Decreases the entity's subdual points by the given amount. Alerts
     * listeners if it results in a changed value. If subdual goes negative, it
     * is changed to null. If the old subdual damage value was null, it is
     * converted to 0. Alerts listeners if it results in a changed value.
     */
	public void healSubdual(Integer amt) {
		if (subdual == null)
		{
			subdual = 0;
		}
		if (amt != 0)
		{
			this.dirty = true;
		}
		subdual -= amt;
		if (subdual <= 0)
		{
			subdual = null;
		}
		alertListeners();
	}
    

    /**
     * Decrements roundsLeft by one. Alerts listeners if it results in a changed
     * value.
     */
    public void decrementRound()
    {
        if (roundsLeft != null)
        {
            --roundsLeft;
            dirty = true;
        }
        alertListeners();
    }

	/**
	 * Is subdual damage greater than hitpoints?  If so, the entity is "subdued".
	 */
	public boolean isSubdued() {
		
		return (getSubdual() != null && getHitpoints() != null) 
			&& (getSubdual() >= getHitpoints());
	}

    /**
     * Is this a limited time effect which has expired?
     * 
     * @param fudge
     *            How many extra rounds to give it before it's "expired".
     * @return true if the time limitted effect is expired. False if it's not
     *         expired or it's not limitted.
     */
    public boolean isExpired(int fudge) {
        return (getRoundsLeft() != null && getRoundsLeft() <= -fudge);
    }

	/**
	 * Alerts all listeners, but only if we're marked as dirty.
	 */
	@Override
	protected void alertListeners() {
		if (dirty)
		{
			super.alertListeners();
			dirty = false;
		}
	}

	/**
	 * Makes sure that this entity has an abbreviation and that it's unique.
     * If it has no abbreviation, the first letter of its name is used.
     * If it's not unique, it is renamed to be unique; it may also rename
     * one other entity if necessary.
	 * 
	 * @param otherEntities A list of all the other entities.  The uniqueness
     * is guaranteed relative to this set.
	 */
	public void sanitizeAbbrev(List<Entity> otherEntities)
	{
		if (this.getAbbreviation() == null || this.getAbbreviation().trim().length() == 0)
		{			
			if (this.getName().trim() != null && this.getName().trim().length() > 0)
			{
				String str = this.getName().trim().substring(0, 1).toUpperCase();
				this.setAbbreviation(str);
			}
		}

		// Make sure we have an abbreviation
		String abbrev = AbbrevUtil.getAplhaPrefix(this.getAbbreviation());
		if (abbrev.length() == 0)
		{
			this.setAbbreviation("X" + this.getAbbreviation());
			abbrev = "X";
		}

		// Make sure the abbreviation is unique.
		boolean postfixChanged = false;
		Integer postfix =   StringUtil.tryParseInt(
				this.getAbbreviation().substring(abbrev.length()));
		for (Entity other : otherEntities) {
			if (abbrev.equalsIgnoreCase(AbbrevUtil.getAplhaPrefix(other.getAbbreviation())))
			{
				String otherPostfix = other.getAbbreviation().substring(abbrev.length());
				if (otherPostfix.length() == 0)
				{
					otherPostfix = "1";
					other.setAbbreviation(other.getAbbreviation() + otherPostfix);
				}
				int otherPostfixValue;
				if (otherPostfix.trim().length() == 0)
				{
					otherPostfixValue = 0;
				}
				else
				{
					otherPostfixValue = StringUtil.tryParseInt(otherPostfix);
				}

				if (postfix == null || postfix <= otherPostfixValue)
				{
					postfix = otherPostfixValue + 1;
					postfixChanged = true;
				}
			}
		}

		if (postfixChanged)
		{
			this.setAbbreviation(abbrev + postfix);
		}
	}

    /**
     * Damages or heals with the specified type.
     * 
     * @param type
     *            The type of damage to deal. 
     * 
     * @param damage
     *            The amount to damage or heal.
     */
    public void damage(DamageType type, Integer damage) {
        switch (type)
        {
        	case NORMAL_DAMAGE:
        		damage(damage);
        		break;
        	case SUBDUAL:
        		subdue(damage);
        		break;
        	case HEAL:
        		heal(damage);
        		break;
            case HEAL_SUBDUAL:
        		healSubdual(damage);
        		break;
        }
    }

    /**
     * Returns the damage type for the given string.
     * 
     * @return a damage type or null if the string does not refer to a damage
     *         type.
     * @todo This should be a method on the enum.
     */
    public static DamageType stringToDamageType(String command)
    {
        if ("dmg".equalsIgnoreCase(command)
                || "d".equalsIgnoreCase(command)
                || "damage".equalsIgnoreCase(command))
        {
            return DamageType.NORMAL_DAMAGE;
        }
        else if ("sub".equalsIgnoreCase(command)
                || "s".equalsIgnoreCase(command)
                || "subdue".equalsIgnoreCase(command))
        {
            return DamageType.SUBDUAL;
        }
        else if ("heal".equalsIgnoreCase(command)
                || "h".equalsIgnoreCase(command))
        {
            return DamageType.HEAL;
        }
        else if ("healsubdual".equalsIgnoreCase(command)
                || "hs".equalsIgnoreCase(command)
                || "subheal".equalsIgnoreCase(command)
                || "recover".equalsIgnoreCase(command)
                || "rec".equalsIgnoreCase(command)
                || "healsub".equalsIgnoreCase(command))
        {
            return DamageType.HEAL_SUBDUAL;
        }
        else
        {
            return null;
        }
    }
    
    /**
     * Returns the canonical string representation of the damage type.
     * 
     * @todo This should be a method on the enum.
     */
    public static String damageTypeToString(DamageType type)
    {
        switch (type)
        {
            case NORMAL_DAMAGE:
                return "Damage";
            case SUBDUAL:
                return "Subdue";
            case HEAL:
                return "Heal";
            case HEAL_SUBDUAL:
                return "Recover";
            default:
                return null;
        }
        
    }

    public Map<String, String> getAsMap() {
        Map<String, String> map = new TreeMap<String, String>();
        map.put(EntityList.COLUMN_NAME_ABBREV, getAbbreviation());
        map.put(EntityList.COLUMN_NAME_NAME, getName());
        map.put(EntityList.COLUMN_NAME_HP, toStringOrBlank(getHitpoints()));
        map.put(EntityList.COLUMN_NAME_SUBDUAL, toStringOrBlank(getSubdual()));
        map.put(EntityList.COLUMN_NAME_INIT, toStringOrBlank(getInitRoll()));
        map.put(EntityList.COLUMN_NAME_ROUNDS, toStringOrBlank(getRoundsLeft()));
        return map;
    }
    
   private String toStringOrBlank(Integer i)
   {
       if (i == null) 
           return "";
       
       return i.toString();
   }
}

