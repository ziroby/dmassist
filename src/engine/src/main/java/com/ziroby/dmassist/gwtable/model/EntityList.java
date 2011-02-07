package com.ziroby.dmassist.gwtable.model;

import java.util.Collection;
import java.util.List;
import java.util.Map;

import com.ziroby.dmassist.gwtable.util.Listenable;

public interface EntityList extends Listenable
{

    /** The number for the turn indicator column. */
    public static final int COLUMN_NUMBER_MY_TURN = 0;

    public static final String COLUMN_NAME_MY_TURN = "isMyTurn";

    /** The number for the abbreviation column. */
    public static final int COLUMN_NUMBER_NUM = 1;

    public static final String COLUMN_NAME_ABBREV = "abbrev";

    /** The number for the name column. */
    public static final int COLUMN_NUMBER_NAME = 2;

    public static final String COLUMN_NAME_NAME = "name";

    /** The number for the initiative count column. */
    public static final int COLUMN_NUMBER_INIT = 3;

    public static final String COLUMN_NAME_INIT = "init";

    /** The number for the hitpoint column. */
    public static final int COLUMN_NUMBER_HP = 4;

    public static final String COLUMN_NAME_HP = "hp";

    /** The number for the subdual damage column. */
    public static final int COLUMN_NUMBER_SUBDUAL = 5;

    public static final String COLUMN_NAME_SUBDUAL = "subdual";

    /** The number for the number of rounds left column. */
    public static final int COLUMN_NUMBER_ROUNDS = 6;

    public static final String COLUMN_NAME_ROUNDS = "rounds";

    public static final int COLUMN_NUMBER_TYPE = 7;

    public static final String COLUMN_NAME_TYPE = "type";

    /** Returns the human readable column heading for the given "column". */
    public abstract String getColumnHeader(int column);

    /** The number of virtual columns. */
    public abstract int getColumnCount();

    /**
     * Tells if it's this row's turn.  That is, is this row's initiative count
     * equal to the currently active initiative count?
     */
    public abstract boolean isMyTurn(int row);

    public abstract int getRowCount();

    public abstract void addEntity(Entity entity);

    public abstract Integer getInitCount();

    public abstract void setInitCount(Integer initCount);

    /**
     * Goes to the "next" initiative count.  The next highest number, or if this is
     * the highest number, then to the minimum number.
     */
    public abstract void gotoNextInitCount();

    public abstract void remove(int index);

    public abstract Entity getEntity(int row);

    public abstract Entity findByAbbrev(String abbrev);

    public abstract Collection<Entity> getEntities();

    public abstract void addEntities(Collection<Entity> list);

    public abstract void clear();

    public abstract boolean isCellEditable(int rowIndex, int columnIndex);

    /**
     * Sets the given virtual column.  Delegates to the correct setFoo() method.
     *
     * @param columnIndex The index to set.
     * @param value The value; must be of the appropriate type (usually
     * String or Integer).
     */
    public abstract void setColumn(Entity entity, int columnIndex, Object value);

    public abstract Class<?> getColumnClass(int columnIndex);

    /**
     * Returns all the attributed (the entire "row") as a <code>List</code>.
     */
    public abstract List<Object> getEntireRow(Entity entity);

    public abstract Object getValueAt(int row, int col);

    /** Returns the given virtual column. */
    public abstract Object getColumn(Entity entity, int col);

    public abstract void setValueAt(Object value, int rowIndex, int columnIndex);

    public abstract List<Map<String, String>> getListOfMaps();

    public abstract List<Map<String, String>> getListOfMaps(
            List<Map<String, String>> data);

    public abstract int getNumRounds();

    public abstract void resetNumRounds();

    public abstract String formatRoundsAsTime();

    public abstract void addSampleData();

    public abstract void setNumRounds(int result);

    public abstract void setEntity(int position, Entity entity);

	public abstract void setTimePerRound(Integer parseInt);

}