package com.ziroby.android.dmassist;

import java.util.Collection;
import java.util.Map;

import android.content.ContentValues;
import android.content.Context;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;
import android.util.Log;

import com.ziroby.dmassist.gwtable.model.Entity;
import com.ziroby.dmassist.gwtable.model.EntityList;



public class EntityDbHelper
{
    private static final String DATABASE_NAME = "dmassist";
    private static final int DATABASE_VERSION = 2;
    private static final String DATABASE_TABLE_NAME = "entities";

    public static class DatabaseHelper extends SQLiteOpenHelper
    {
        private static final String DATABASE_CREATE = "create table " + DATABASE_TABLE_NAME +
            "(_id integer primary key autoincrement," +
            EntityList.COLUMN_NAME_ABBREV + " text, " +
            EntityList.COLUMN_NAME_HP + " text, " +
            EntityList.COLUMN_NAME_INIT + " text, " +
            EntityList.COLUMN_NAME_NAME + " text not null, " +
            EntityList.COLUMN_NAME_ROUNDS + " text, " +
            EntityList.COLUMN_NAME_SUBDUAL + " text" +
            ");";

        public DatabaseHelper(Context context) {
            super(context, DATABASE_NAME, null, DATABASE_VERSION);
        }
        public void onCreate(SQLiteDatabase db) {
            db.execSQL(DATABASE_CREATE);
        }
        public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion) {
            Log.w(this.getClass().toString(), "Upgrading database from version " + oldVersion + " to "
                    + newVersion + ", which will destroy all old data");
            db.execSQL("DROP TABLE IF EXISTS " + DATABASE_TABLE_NAME);
            onCreate(db);
        }
    } // class DatabaseHelper

    private Context context;
    private DatabaseHelper dbHelper;
    private SQLiteDatabase db;

    EntityDbHelper(Context context) {
        this.context = context;
    }

    public void open() {
        this.dbHelper = new DatabaseHelper(context);
        this.db = dbHelper.getWritableDatabase();
    }

    public void saveEntity(Entity entity) {
        createEntity(entity);
    }

    private long createEntity(Entity entity) {
        ContentValues initialValues = getContentValues(entity);

        return db.insert(DATABASE_TABLE_NAME, null, initialValues);
    }

    private ContentValues getContentValues(Entity entity) {
        ContentValues initialValues = new ContentValues();

        final Map<String, String> entityAsMap = entity.getAsMap();
        for (String key : entityAsMap.keySet()) {
            initialValues.put(key, entityAsMap.get(key));
        }

        return initialValues;
    }

    public Cursor fetchAllEntities() {
        return db.query(DATABASE_TABLE_NAME, AndroidEntityUtil.ALL_COLUMN_NAMES, null, null, null, null, null);
    }

    public Entity fetchEntity(int itemId) {
        Cursor cursor = db.query(
                /*distinct*/ true,
                DATABASE_TABLE_NAME,
                AndroidEntityUtil.ALL_COLUMN_NAMES,
                idEquals(itemId),
                /*selectionArgs*/ null,
                /*groupBy*/ null,
                /*having*/ null,
                /*orderBy*/ null,
                /*limit*/ null);

        if (cursor == null)
            return null;

        cursor.moveToFirst();

        Entity entity = readFromCursor(cursor);

        return entity;
    }

    private String idEquals(int itemId) {
        return "_id = " + itemId;
    }

    private Entity readFromCursor(Cursor cursor) {
        Entity entity = new Entity();

        entity.setName(getString(cursor, EntityList.COLUMN_NAME_NAME));
        entity.setAbbreviation(getString(cursor, EntityList.COLUMN_NAME_ABBREV));
        entity.setInitRoll(getString(cursor, EntityList.COLUMN_NAME_INIT));
        entity.setHitpoints(getString(cursor, EntityList.COLUMN_NAME_HP));
        entity.setSubdual(getString(cursor, EntityList.COLUMN_NAME_SUBDUAL));
        entity.setRoundsLeft(getString(cursor, EntityList.COLUMN_NAME_ROUNDS));

        return entity;
    }

    private String getString(Cursor cursor, final String columnName) {
        return cursor.getString(cursor.getColumnIndexOrThrow(columnName));
    }

    public void deleteEntities(Collection<Integer> checkedIds) {
        // delete one at a time for now.
        for (int id : checkedIds)
            deleteEntity(id);
    }

    private void deleteEntity(int id) {
        db.delete(DATABASE_TABLE_NAME, idEquals(id), null);
    }
}
