package com.ziroby.dmassist.swing;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Collection;
import java.util.List;
import java.util.Map;

import javax.swing.table.AbstractTableModel;

import com.ziroby.dmassist.gwtable.model.Entity;
import com.ziroby.dmassist.gwtable.util.DelegateListenable;
import com.ziroby.dmassist.gwtable.util.Listener;
import com.ziroby.dmassist.gwtable.util.ObjectEvent;
import com.ziroby.dmassist.model.EntityListImpl;
import com.ziroby.dmassist.model.EntityListWithSave;

public class EntityDataModel extends AbstractTableModel
    implements EntityListWithSave, Listener {

    private EntityListWithSave entityListWithSave;

    private DelegateListenable delegateListenable;

    public EntityDataModel() {
        super();
        //TODO: Switch to dependency injection
        entityListWithSave = new EntityListImpl();
        entityListWithSave.addListener(this);
        delegateListenable = new DelegateListenable();
    }

    public int getColumnCount() {
        return entityListWithSave.getColumnCount();
    }

    public String getColumnName(int column) {
    	return entityListWithSave.getColumnHeader(column);
    }

    /**
     * @see javax.swing.table.AbstractTableModel#getColumnClass(int)
     */
    public Class<?> getColumnClass(int columnIndex) {
        Class<?> columnClass = entityListWithSave.getColumnClass(columnIndex);

        if (columnClass == null)
            columnClass = super.getColumnClass(columnIndex);

        return columnClass;
    }

    public boolean isCellEditable(int rowIndex, int columnIndex) {
        return entityListWithSave.isCellEditable(rowIndex, columnIndex);
    }

    /**
     * Returns all the attributed (the entire "row") as a <code>List</code>.
     */
    public List<Object> getEntireRow(Entity entity)
    {
        return entityListWithSave.getEntireRow(entity);
    }

    /** Returns the given virtual column. */
    public Object getColumn(Entity entity, int col) {
        return entityListWithSave.getColumn(entity, col);
    }

    /**
     * @see javax.swing.table.AbstractTableModel#setValueAt(java.lang.Object, int, int)
     */
    public void setValueAt(Object value, int rowIndex, int columnIndex) {
        entityListWithSave.setValueAt(value, rowIndex, columnIndex);
    }

    public int getRowCount() {
        return entityListWithSave.getRowCount();
    }

    public Object getValueAt(int row, int col) {
        return entityListWithSave.getValueAt(row, col);
    }

    public void addEntities(Collection<Entity> list) {
        entityListWithSave.addEntities(list);
    }

    public void addEntity(Entity entity) {
        entityListWithSave.addEntity(entity);
    }

    public void clear() {
        entityListWithSave.clear();
    }

    public Entity findByAbbrev(String abbrev) {
        return entityListWithSave.findByAbbrev(abbrev);
    }

    public Collection<Entity> getEntities() {
        return entityListWithSave.getEntities();
    }

    public Entity getEntity(int row) {
        return entityListWithSave.getEntity(row);
    }

    public Integer getInitCount() {
        return entityListWithSave.getInitCount();
    }

    public void gotoNextInitCount() {
        entityListWithSave.gotoNextInitCount();
    }

    public void importFile(File file) throws FileNotFoundException {
        entityListWithSave.importFile(file);
    }

    public boolean isMyTurn(int row) {
        return entityListWithSave.isMyTurn(row);
    }

    public void remove(int index) {
        entityListWithSave.remove(index);
    }

    public void save(File file) throws FileNotFoundException {
        entityListWithSave.save(file);
    }

    public void setInitCount(Integer initCount) {
        entityListWithSave.setInitCount(initCount);
    }

    public void objectChanged(ObjectEvent event) {
        fireTableDataChanged();
        delegateListenable.alertListeners();
    }

    public void addListener(Listener listener) {
        delegateListenable.addListener(listener);
    }

    public String getColumnHeader(int column) {
        return entityListWithSave.getColumnHeader(column);
    }
    /**
     * Sets the given virtual column.  Delegates to the correct setFoo() method.
     *
     * @param columnIndex The index to set.
     * @param value The value; must be of the appropriate type (usually
     * String or Integer).
     */
    public void setColumn(Entity entity, int columnIndex, Object value) {
        entityListWithSave.setColumn(entity, columnIndex, value);
    }

    public List<Map<String, String>> getListOfMaps() {
        return entityListWithSave.getListOfMaps();
    }

    public List<Map<String,String>> getListOfMaps(List<Map<String, String>> data) {
        return entityListWithSave.getListOfMaps(data);
    }

    @Override
    public int getNumRounds() {
        return entityListWithSave.getNumRounds();
    }

    @Override
    public void resetNumRounds() {
        entityListWithSave.resetNumRounds();
    }

    @Override
    public String formatRoundsAsTime() {
        return entityListWithSave.formatRoundsAsTime();
    }

    @Override
    public void addSampleData() {
        entityListWithSave.addSampleData();
    }

    @Override
    public void setNumRounds(int result) {
        // TODO Auto-generated method stub

    }

    @Override
    public void setEntity(int position, Entity entity) {
        // TODO Auto-generated method stub

    }


}
