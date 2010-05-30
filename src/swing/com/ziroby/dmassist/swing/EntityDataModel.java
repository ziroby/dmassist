package com.ziroby.dmassist.swing;

import java.io.File;
import java.io.FileNotFoundException;
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
        //TODO: Switch to dependency injection
        entityList = new EntityListImpl();
        entityList.addListener(this);
        delegateListenable = new DelegateListenable();
    }    
    
    public int getColumnCount() {
        return entityList.getColumnCount();
    }
    
    public String getColumnName(int column) {
    	return entityList.getColumnHeader(column);
    }

    /**
     * @see javax.swing.table.AbstractTableModel#getColumnClass(int)
     */
    public Class<?> getColumnClass(int columnIndex) {
        Class<?> columnClass = entityList.getColumnClass(columnIndex);
        
        if (columnClass == null)
            columnClass = super.getColumnClass(columnIndex);
        
        return columnClass;
    }

    public boolean isCellEditable(int rowIndex, int columnIndex) {
        return entityList.isCellEditable(rowIndex, columnIndex);
    }
    
    /**
     * Returns all the attributed (the entire "row") as a <code>List</code>.
     */
    public List<Object> getEntireRow(Entity entity)
    {
        return entityList.getEntireRow(entity);
    }

    /** Returns the given virtual column. */
    public Object getColumn(Entity entity, int col) {
        return entityList.getColumn(entity, col);
    }

    /**
     * @see javax.swing.table.AbstractTableModel#setValueAt(java.lang.Object, int, int)
     */
    @Override
    public void setValueAt(Object value, int rowIndex, int columnIndex) {
        Entity entity = entityList.getEntity(rowIndex);  
        
        entityList.setColumn(entity, columnIndex, value);
    }

    public int getRowCount() {
        return entityList.getRowCount();
    }

    public Object getValueAt(int row, int col) {
        return entityList.getValueAt(row, col);
    }

    public void addEntities(Collection<Entity> list) {
        entityList.addEntities(list);
    }

    public void addEntity(Entity entity) {
        entityList.addEntity(entity);
    }

    public void clear() {
        entityList.clear();        
    }

    public Entity findByAbbrev(String abbrev) {
        return entityList.findByAbbrev(abbrev);
    }

    public Collection<Entity> getEntities() {
        return entityList.getEntities();
    }

    public Entity getEntity(int row) {
        return entityList.getEntity(row);
    }

    public Integer getInitCount() {
        return entityList.getInitCount();
    }

    public void gotoNextInitCount() {
        entityList.gotoNextInitCount();
    }

    public void importFile(File file) throws FileNotFoundException {
        entityList.importFile(file);
    }

    public boolean isMyTurn(int row) {
        return entityList.isMyTurn(row);
    }

    public void remove(int index) {
        entityList.remove(index);
    }

    public void save(File file) throws FileNotFoundException {
        entityList.save(file);
    }

    public void setInitCount(Integer initCount) {
        entityList.setInitCount(initCount);
    }

    public void objectChanged(ObjectEvent event) {
        fireTableDataChanged();
        delegateListenable.alertListeners();
    }

    public void addListener(Listener listener) {
        delegateListenable.addListener(listener);
    }

    public String getColumnHeader(int column) {
        return entityList.getColumnHeader(column);
    }
    /**
     * Sets the given virtual column.  Delegates to the correct setFoo() method.
     * 
     * @param columnIndex The index to set.
     * @param value The value; must be of the appropriate type (usually
     * String or Integer).
     */
    public void setColumn(Entity entity, int columnIndex, Object value) {
        entityList.setColumn(entity, columnIndex, value);
    }
}
