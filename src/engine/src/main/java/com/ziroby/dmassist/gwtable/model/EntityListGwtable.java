package com.ziroby.dmassist.gwtable.model;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collection;
import java.util.List;
import java.util.Map;
import java.util.Vector;

import com.ziroby.dmassist.gwtable.util.AbstractListenable;
import com.ziroby.dmassist.gwtable.util.Listenable;
import com.ziroby.dmassist.gwtable.util.Listener;
import com.ziroby.dmassist.gwtable.util.ObjectEvent;

/**
 * A special purpose entity list that only contains things that we can (and do) convert
 * to GWT.
 *
 * @author Ron "Ziroby" Romero
 *
 */
public class EntityListGwtable extends AbstractListenable implements Listener, Listenable,
        EntityList

{

    private static final int DEFAULT_SECONDS_PER_ROUND = 6;

	private static final String[] ColumnName = { " ", "##", "Name", "Init",
            "HP", "Sub", "Rnds", "Type" };

    private int secondsPerRound = DEFAULT_SECONDS_PER_ROUND;

    private List<Entity> entities = new Vector<Entity>();

    private Integer initCount = null;

    /**
     * How deep in the call stack are we? This is used to make sure we only send
     * one table changed event per public call.
     */
    private int depth = 0;

    private boolean dirty = false;

    private int numRounds;

    /**
     *
     */
    private static final long serialVersionUID = 5503046605866805606L;

    public EntityListGwtable()
    {
        super();
    }

    public int getRowCount() {
        return entities.size();
    }

    /**
     * @see com.ziroby.dmassist.model.EntityListWithSave#isMyTurn(int)
     */
    public boolean isMyTurn(int row) {
        final Integer initRoll = entities.get(row).getInitRoll();
        return initRoll != null && initRoll == this.initCount;
    }

    /**
     * @see com.ziroby.dmassist.model.EntityListWithSave#addEntity(com.ziroby.dmassist.gwtable.model.Entity)
     */
    public void addEntity(Entity entity) {
        if (entity == null)
        {
            // Silently do nothing.
            return;
        }

        enterPublicMethod();

        sanitizeValue(entity);

        // int newRowNum = entities.size();
        entities.add(entity);
        dirty = true;
        // fireTableRowsInserted(newRowNum - 1, newRowNum);
        entity.addListener(this);
        leavePublicMethod();
    }

    /**
     * Fixes the data in the entity, so it fits into the table well.
     *
     * @param entity
     */
    private void sanitizeValue(Entity entity) {

        if (entity.getName() == null || entity.getName().trim().length() == 0)
        {
            throw new NullPointerException("Blank names are not allowed");
        }

        entity.sanitizeAbbrev(entities);
    }

    /**
     * @see com.ziroby.dmassist.model.EntityListWithSave#getInitCount()
     */
    public final Integer getInitCount() {
        return initCount;
    }

    public final void setInitCount(Integer initCount) {
        if (this.initCount == initCount)
        {
            // Nothing to do.
            return;
        }

        enterPublicMethod();
        this.initCount = initCount;
        this.dirty = true;
        leavePublicMethod();
    }

    /**
     * @see com.ziroby.dmassist.model.EntityListWithSave#gotoNextInitCount()
     */
    public void gotoNextInitCount() {
        enterPublicMethod();

        // We count backwards, so we look for the highest total init count, and
        // the highest one
        // that's less than current.
        Integer oldInitCount = getInitCount();
        Integer maximumNext = null;
        Integer maximum = null;

        for (Entity row : entities)
        {
            Integer initRoll = row.getInitRoll();

            if (initRoll == null)
                continue;
            if (maximum == null || initRoll > maximum)
                maximum = initRoll;
            if ((oldInitCount == null || initRoll < oldInitCount)
                    && (maximumNext == null || initRoll > maximumNext))
                maximumNext = initRoll;

            if (initRoll == oldInitCount)
            {
                row.decrementRound();
            }
        }

        if (maximumNext != null)
            setInitCount(maximumNext);
        else if (maximum != null)
        {
            numRounds++;
            setInitCount(maximum);
        }
        else
            setInitCount(null);

        for (int i = entities.size() - 1; i >= 0; --i)
        {
            if (entities.get(i).isExpired(1))
            {
                entities.remove(i);
                dirty = true;
            }
        }

        leavePublicMethod();
    }

    /**
     * Call this any time you enter a publicly-callable. It takes care of
     * counting call depth and setting things up to fire table change events
     * appropriately.
     */
    protected void enterPublicMethod() {
        depth++;
    }

    /**
     * Call this at the end of a method that called enterPublicMethod(). It
     * decrements the depth and fires table changes if necessary.
     */
    protected void leavePublicMethod() {
        if (--depth == 0 && dirty)
        {
            // We only fire if we're at top level and something has changed.
            alertListeners();
            dirty = false;
        }
        if (depth < 0)
        {
            throw new IllegalStateException(
                    "Shouldn't have a negative depth in ");
        }
    }

    /**
     * @see com.ziroby.dmassist.model.EntityListWithSave#remove(int)
     */
    public void remove(int index) {
        enterPublicMethod();
        entities.remove(index);
        dirty = true;
        leavePublicMethod();
    }

    /**
     * @see com.ziroby.dmassist.model.EntityListWithSave#getEntity(int)
     */
    public Entity getEntity(int row) {
        return entities.get(row);
    }

    /**
     * @see com.ziroby.dmassist.model.EntityListWithSave#findByAbbrev(java.lang.String)
     */
    public Entity findByAbbrev(String abbrev) {
        // Linear search for now cuz I'm lazy & how long will it really be?
        for (Entity e : entities)
        {
            if (e.getAbbreviation().equalsIgnoreCase(abbrev))
            {
                return e;
            }
        }
        // Hmmm... Maybe they entered an entire name
        for (Entity e : entities)
        {
            if (e.getName().trim().equalsIgnoreCase(abbrev.trim()))
            {
                return e;
            }
        }

        // Couldn't find it.
        return null;
    }

    public void objectChanged(ObjectEvent event) {
        enterPublicMethod();
        dirty = true;
        leavePublicMethod();
    }

    /**
     * @see com.ziroby.dmassist.model.EntityListWithSave#getEntities()
     */
    public Collection<Entity> getEntities() {
        return entities;
    }

    /**
     * @see com.ziroby.dmassist.model.EntityListWithSave#addEntities(java.util.Collection)
     */
    public void addEntities(Collection<Entity> list) {
        enterPublicMethod();
        for (Entity entity : list)
        {
            addEntity(entity);
        }
        leavePublicMethod();
    }

    /**
     * @see com.ziroby.dmassist.model.EntityListWithSave#clear()
     */
    public void clear() {
        enterPublicMethod();
        if (entities.size() > 0)
        {
            entities.clear();
            dirty = true;
        }
        leavePublicMethod();
    }

    /** Returns the human readable column heading for the given "column". */
    public String getColumnHeader(int column) {
        return ColumnName[column];
    }

    /** The number of virtual columns. */
    public int getColumnCount() {
        return ColumnName.length;
    }

    public boolean isCellEditable(int rowIndex, int columnIndex) {
        if (columnIndex == COLUMN_NUMBER_MY_TURN)
            return false;

        return true;
    }

    /**
     * Sets the given virtual column. Delegates to the correct setFoo() method.
     *
     * @param columnIndex
     *            The index to set.
     * @param value
     *            The value; must be of the appropriate type (usually String or
     *            Integer).
     */
    public void setColumn(Entity entity, int columnIndex, Object value) {
        switch (columnIndex)
        {
        case COLUMN_NUMBER_NAME:
            entity.setName((String) value);
            break;
        case COLUMN_NUMBER_NUM:
            entity.setAbbreviation((String) value);
            break;
        case COLUMN_NUMBER_HP:
            entity.setHitpoints((Integer) value);
            break;
        case COLUMN_NUMBER_INIT:
            entity.setInitRoll((Integer) value);
            break;
        case COLUMN_NUMBER_MY_TURN:
            throw new IllegalArgumentException("Can not edit 'my turn' value");
        case COLUMN_NUMBER_SUBDUAL:
            entity.setSubdual((Integer) value);
            break;
        case COLUMN_NUMBER_ROUNDS:
            entity.setRoundsLeft((Integer) value);
            break;
        case COLUMN_NUMBER_TYPE:
            entity.setEntityType((Entity.EntityType) value);
            break;
        default:
            throw new IllegalArgumentException("Invalid column number: "
                    + columnIndex);
        }
    }

    public Class<?> getColumnClass(int columnIndex) {
        switch (columnIndex)
        {
        case COLUMN_NUMBER_NAME:
        case COLUMN_NUMBER_NUM:
            return String.class;
        case COLUMN_NUMBER_HP:
        case COLUMN_NUMBER_SUBDUAL:
        case COLUMN_NUMBER_INIT:
        case COLUMN_NUMBER_ROUNDS:
            return Integer.class;
        case COLUMN_NUMBER_MY_TURN:
            return Boolean.class;
        case COLUMN_NUMBER_TYPE:
            return Entity.EntityType.class;

        default:
            return null;
        }
    }

    /**
     * Returns all the attributed (the entire "row") as a <code>List</code>.
     */
    public List<Object> getEntireRow(Entity entity) {
        Object a[] = { false /* my turn */, entity.getAbbreviation(),
                entity.getName(), entity.getInitRoll(), entity.getHitpoints(),
                entity.getSubdual(), entity.getRoundsLeft(), entity.getEntityType() };

        return Arrays.asList(a);
    }

    public Object getValueAt(int row, int col) {
        Entity entity = getEntity(row);

        if (col == COLUMN_NUMBER_MY_TURN)
        {
            return isMyTurn(row);
        }

        return getColumn(entity, col);
    }

    /** Returns the given virtual column. */
    public Object getColumn(Entity entity, int col) {
        // TODO Cache the row, so we're not regenerating it every time.
        return getEntireRow(entity).get(col);
    }

    public void setValueAt(Object value, int rowIndex, int columnIndex) {
        Entity entity = getEntity(rowIndex);

        setColumn(entity, columnIndex, value);
    }

    public List<Map<String, String>> getListOfMaps() {
        List<Map<String, String>> list = new ArrayList<Map<String, String>>();

        getListOfMaps(list);

        return list;
    }

    @Override
    public List<Map<String, String>> getListOfMaps(
            List<Map<String, String>> data) {
        data.clear();

        for (Entity entity : getEntities())
        {
            data.add(entity.getAsMap());
        }

        return data;
    }

    public int getNumRounds() {
        return numRounds;
    }

    public void setNumRounds(int numRounds) {
        if (this.numRounds == numRounds)
        {
            // Nothing to do.
            return;
        }

        enterPublicMethod();
        this.numRounds = numRounds;
        this.dirty = true;
        leavePublicMethod();
    }

    public void resetNumRounds() {
        enterPublicMethod();
        if (numRounds != 0 || initCount != null)
        {
            numRounds = 0;
            setInitCount(null);
            this.dirty = true;
        }
        leavePublicMethod();
    }

    public String formatRoundsAsTime() {
        int seconds = (numRounds * secondsPerRound) % 60;
        int minutes = ((numRounds * secondsPerRound) / 60) % 60;
        int hours = (numRounds * secondsPerRound) / (60 * 60);

        StringBuilder builder = new StringBuilder();

        if (hours != 0) {
            builder.append(hours);
            builder.append (':');
        }

        builder.append(Integer.toString(100 + minutes).substring(1, 3));
        builder.append (':');
        builder.append(Integer.toString(100 + seconds).substring(1, 3));

        return builder.toString();
    }

    @Override
    public void addSampleData() {
        Entity row1 = new Entity();
        row1.setAbbreviation("O"); //$NON-NLS-1$
        row1.setName("Ogre"); //$NON-NLS-1$
        row1.setInitRoll(12);
        row1.setHitpoints(25);
        row1.setEntityType(Entity.EntityType.MONSTER);
        addEntity(row1);

        Entity row2 = new Entity();
        row2.setAbbreviation("G1"); //$NON-NLS-1$
        row2.setName("Goblin 1"); //$NON-NLS-1$
        row2.setInitRoll(4);
        row2.setHitpoints(8);
        row2.setSubdual(3);
        row2.setEntityType(Entity.EntityType.SRD_MONSTER);
        addEntity(row2);

        Entity row4 = new Entity();
        row4.setName("Acid Arrow"); //$NON-NLS-1$
        row4.setInitRoll(4);
        row4.setRoundsLeft(3);
        row4.setEntityType(Entity.EntityType.SRD_SPELL);
        addEntity(row4);

        Entity row3 = new Entity();
        row3.setAbbreviation("G2"); //$NON-NLS-1$
        row3.setName("Goblin 2"); //$NON-NLS-1$
        row3.setInitRoll(15);
        row3.setHitpoints(3);
        row3.setEntityType(Entity.EntityType.SRD_MONSTER);
        addEntity(row3);

        Entity row5 = new Entity();
        //row3.setAbbreviation("G2"); //$NON-NLS-1$
        row5.setName("Ziroby"); //$NON-NLS-1$
        row5.setInitRoll(25);
        row5.setHitpoints(54);
        row5.setEntityType(Entity.EntityType.PC);
        addEntity(row5);

        Entity row6 = new Entity();
        row6.setAbbreviation("CB"); //$NON-NLS-1$
        row6.setName("Summoned Celestial Badger"); //$NON-NLS-1$
        row6.setInitRoll(25);
        row6.setHitpoints(6);
        row6.setRoundsLeft(5);
        row6.setEntityType(Entity.EntityType.EFFECT);
        addEntity(row6);
}

    public void setEntity(int position, Entity entity) {
        enterPublicMethod();
        if (entity == null || entity.equals(entities.get(position)))
            return;

        entities.set(position, entity);
        dirty = true;
        leavePublicMethod();
    }

	@Override
	public void setTimePerRound(Integer seconds) {
		if (seconds == null || seconds < 1)
			secondsPerRound = DEFAULT_SECONDS_PER_ROUND;
		else
			secondsPerRound = seconds;
	}
}