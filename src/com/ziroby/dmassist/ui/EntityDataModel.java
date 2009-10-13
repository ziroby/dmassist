package com.ziroby.dmassist.ui;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Arrays;
import java.util.Collection;
import java.util.List;

import javax.swing.table.AbstractTableModel;

import com.ziroby.dmassist.model.Entity;
import com.ziroby.dmassist.model.EntityList;
import com.ziroby.dmassist.model.EntityListImpl;
import com.ziroby.util.DelegateListenable;
import com.ziroby.util.Listener;
import com.ziroby.util.ObjectEvent;

public class EntityDataModel extends AbstractTableModel 
    implements EntityList, Listener {

    private EntityList entityList;
    
    private DelegateListenable delegateListenable;
    
    public EntityDataModel() {
        super();
        entityList = new EntityListImpl();
        entityList.addListener(this);
        delegateListenable = new DelegateListenable();
    }

    /** The number for the turn indicator column. */
    public static final int COLUMN_NUMBER_MY_TURN = 0;
    /** The number for the abbreviation column. */
    public static final int COLUMN_NUMBER_NUM = 1; 
    /** The number for the name column. */
    public static final int COLUMN_NUMBER_NAME = 2; 
    /** The number for the initiative count column. */
    public static final int COLUMN_NUMBER_INIT = 3; 
    /** The number for the hitpoint column. */
    public static final int COLUMN_NUMBER_HP = 4; 
    /** The number for the subdual damage column. */
    public static final int COLUMN_NUMBER_SUBDUAL = 5;
    /** The number for the number of rounds left column. */
    public static final int COLUMN_NUMBER_ROUNDS = 6;
    
    private final static String[] ColumnName = {" ", "##", "Name", "Init", "HP", "Sub", "Rnds"};
    
    
    /** Returns the human readable column heading for the given "column". */
    public static String getColumnHeader(int column) {
        return ColumnName[column];
    }

    /** The number of virtual columns. */
    public int getColumnCount() {
        return ColumnName.length;
    }


    @Override
    public String getColumnName(int column) {
    	return getColumnHeader(column);
    }

    /**
     * @see javax.swing.table.AbstractTableModel#getColumnClass(int)
     */
    @Override
    public Class<?> getColumnClass(int columnIndex) {
    	switch (columnIndex) {
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
    			
    		default:
    			return super.getColumnClass(columnIndex);
    	}
    }

    @Override
    public boolean isCellEditable(int rowIndex, int columnIndex) {
    	if (columnIndex == COLUMN_NUMBER_MY_TURN)
    		return false;
    
    	return true;
    }

    /**
     * Returns all the attributed (the entire "row") as a <code>List</code>.
     */
    public List<Object> getEntireRow(Entity entity)
    {
        Object a[] = { false /* my turn */, entity.getAbbreviation(),
                entity.getName(), entity.getInitRoll(), entity.getHitpoints(),
                entity.getSubdual(), entity.getRoundsLeft() };
        
        return Arrays.asList(a);
    }

    /**
     * Sets the given virtual column.  Delegates to the correct setFoo() method.
     * 
     * @param columnIndex The index to set.
     * @param value The value; must be of the appropriate type (usually
     * String or Integer).
     */
    public void setColumn(Entity entity, int columnIndex, Object value) {
        switch (columnIndex) {
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

            default :
                throw new IllegalArgumentException("Invalid column number: " + columnIndex);
        }
    }

    /** Returns the given virtual column. */
    public Object getColumn(Entity entity, int col) {
        // TODO Cache the row, so we're not regenerating it every time.
        return getEntireRow(entity).get(col);
    }

    /**
     * @see javax.swing.table.AbstractTableModel#setValueAt(java.lang.Object, int, int)
     */
    @Override
    public void setValueAt(Object value, int rowIndex, int columnIndex) {
        Entity entity = entityList.getEntity(rowIndex);  
        
        setColumn(entity, columnIndex, value);
    }

    @Override
    public int getRowCount() {
        return entityList.getRowCount();
    }

    /**
     * @see javax.swing.table.TableModel#getValueAt(int, int)
     */
    public Object getValueAt(int row, int col) {
        Entity entity = entityList.getEntity(row);  
        
        if (col == COLUMN_NUMBER_MY_TURN)
        {
            return isMyTurn(row);
        }
        
        return getColumn(entity, col);
    }

    @Override
    public void addEntities(Collection<Entity> list) {
        entityList.addEntities(list);
    }

    @Override
    public void addEntity(Entity entity) {
        entityList.addEntity(entity);
    }

    @Override
    public void clear() {
        entityList.clear();        
    }

    @Override
    public Entity findByAbbrev(String abbrev) {
        return entityList.findByAbbrev(abbrev);
    }

    @Override
    public Collection<Entity> getEntities() {
        return entityList.getEntities();
    }

    @Override
    public Entity getEntity(int row) {
        return entityList.getEntity(row);
    }

    @Override
    public Integer getInitCount() {
        return entityList.getInitCount();
    }

    @Override
    public void gotoNextInitCount() {
        entityList.gotoNextInitCount();
    }

    @Override
    public void importFile(File file) throws FileNotFoundException {
        entityList.importFile(file);
    }

    @Override
    public boolean isMyTurn(int row) {
        return entityList.isMyTurn(row);
    }

    @Override
    public void remove(int index) {
        entityList.remove(index);
    }

    @Override
    public void save(File file) throws FileNotFoundException {
        entityList.save(file);
    }

    @Override
    public void setInitCount(Integer initCount) {
        entityList.setInitCount(initCount);
    }

    @Override
    public void objectChanged(ObjectEvent event) {
        fireTableDataChanged();
        delegateListenable.alertListeners();
    }

    @Override
    public void addListener(Listener listener) {
        delegateListenable.addListener(listener);
    }
}
