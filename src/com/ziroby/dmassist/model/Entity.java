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

import java.util.Arrays;
import java.util.List;

import com.ziroby.util.AbbrevUtil;
import com.ziroby.util.StringUtil;

/**
 * Holds one "row" in the initiative table.
 * 
 * @author Ziroby
 *
 */
public class Entity extends AbstractListenable {
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

	public final String getAbbreviation() {
		return abbreviation;
	}

	public final void setAbbreviation(String abbreviation) {
		if (this.abbreviation != null && this.abbreviation.equals(abbreviation))
		{
			// It's already that value.  Don't change it or alertListeners.
			return;			
		}
		this.abbreviation = (abbreviation == null)?  null : abbreviation.trim();
		this.dirty = true;
		alertListeners();
	}

	public final String getName() {
		return name;
	}

	public final void setName(String name) {
		if (this.name != null && this.name.equals(name))
		{
			// It's already that value.  Don't change it or alertListeners.
			return;			
		}
		this.name = (name == null)? null : name.trim();
		this.dirty = true;
		alertListeners();
	}

	public final Integer getInitRoll() {
		return initRoll;
	}

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

	public final Integer getHitpoints() {
		return hitpoints;
	}

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
     * @return the subdual
     */
    public final Integer getSubdual() {
        return subdual;
    }

    /**
     * @param subdual the subdual to set
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

	public Integer getRoundsLeft() {
        return roundsLeft;
    }

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
	 * Returns the entire row as a vector.
	 */
	public List<Object> getEntireRow()
	{
		Object a[] = { false /* my turn */, this.abbreviation, this.name,
                this.initRoll, this.hitpoints, this.subdual, this.roundsLeft };
		
		return Arrays.asList(a);
	}

	private final static String[] RowName = {" ", "##", "Name", "Init", "HP", "Sub", "Rnds"};
	public static final int ROW_NUMBER_MY_TURN = 0;
	public static final int ROW_NUMBER_NUM = 1; 
	public static final int ROW_NUMBER_NAME = 2; 
	public static final int ROW_NUMBER_INIT = 3; 
	public static final int ROW_NUMBER_HP = 4; 
	public static final int ROW_NUMBER_SUBDUAL = 5;
    public static final int ROW_NUMBER_ROUNDS = 6;
	
	public static String getColumnHeader(int column) {
		return RowName[column];
	}

	public static int getColumnCount() {
		return RowName.length;
	}

	public Object getColumn(int col) {
		// TODO Cache the row, so we're not regenerating it every time.
		return getEntireRow().get(col);
	}

	public void setInitRoll(String text) {
		Integer n = StringUtil.tryParseInt(text);
		setInitRoll(n);		
	}

	public void setHitpoints(String text) {
		Integer n = StringUtil.tryParseInt(text);
		setHitpoints(n);
	}

	public void setSubdual(String text) {
		Integer n = StringUtil.tryParseInt(text);
		setSubdual(n);
	}

	public void setColumn(int columnIndex, Object value) {
		switch (columnIndex) {
			case Entity.ROW_NUMBER_NAME:
				setName((String) value);
				break;
			case Entity.ROW_NUMBER_NUM:
				setAbbreviation((String) value);
				break;
			case Entity.ROW_NUMBER_HP:
				setHitpoints((Integer) value);
				break;
			case Entity.ROW_NUMBER_INIT:
				setInitRoll((Integer) value);
				break;
			case Entity.ROW_NUMBER_MY_TURN:
				throw new IllegalArgumentException("Can not edit 'my turn' value");
			case Entity.ROW_NUMBER_SUBDUAL:
				setSubdual((Integer) value);
				break;
            case Entity.ROW_NUMBER_ROUNDS:
                setRoundsLeft((Integer) value);
                break;

			default :
				throw new IllegalArgumentException("Invalid column number: " + columnIndex);
		}
	}

	/**
	 * Decreases the entity's hit points by the given amount.
	 * @param damage
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
	 * Increases the entity's subdual points by the given amount.
	 * @param damage
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
		if (subdual < 0)
		{
			subdual = null;
		}
		alertListeners();
	}
    
    
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
	 * Is subdual damage greater than hitpoints?
	 *  
	 * @return
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
     * @return
     */
    public boolean isExpired(int fudge) {
        return (getRoundsLeft() != null && getRoundsLeft() <= -fudge);
    }

	/**
	 * Alerts all listeners, but only if we're marked as dirty.
	 * 
	 * @see com.ziroby.dmassist.model.AbstractListenable#alertListeners()
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
	 * 
	 * @param otherEntities
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

    // TODO: This should be a method on the enum.
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
}

