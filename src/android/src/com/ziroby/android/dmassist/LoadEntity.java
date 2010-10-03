package com.ziroby.android.dmassist;

import java.util.ArrayList;
import java.util.Collection;

import android.app.ListActivity;
import android.content.DialogInterface;
import android.content.Intent;
import android.database.Cursor;
import android.database.sqlite.SQLiteCursor;
import android.os.Bundle;
import android.util.SparseBooleanArray;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.CheckedTextView;
import android.widget.ListView;
import android.widget.SimpleCursorAdapter;

import com.ziroby.android.util.AndroidUtils;
import com.ziroby.dmassist.gwtable.model.Entity;

public class LoadEntity extends ListActivity
{
    private EntityDbHelper dbHelper;
    private SimpleCursorAdapter adapter;
    private ArrayList<Bundle> allBundles = new ArrayList<Bundle>();
    private AndroidEntityUtil androidEntityUtil;
    private int type;
    private Cursor cursor;

    protected void onCreate(Bundle savedInstanceState) {
        try {
            super.onCreate(savedInstanceState);

            setContentView(R.layout.load_entity);

            dbHelper = new EntityDbHelper(this);
            dbHelper.open();

            type = getIntent().getExtras().getInt("position");
            fillData();

            setOnClickListeners();

            getListView().setChoiceMode(ListView.CHOICE_MODE_MULTIPLE);

            androidEntityUtil = new AndroidEntityUtil(this);

        }
        catch (RuntimeException e) {
            AndroidUtils.displayErrorDialog(this, e);
        }
    }

    private void setOnClickListeners() {
        Button loadButton = (Button) findViewById(R.id.button_load);
        loadButton.setOnClickListener(new OnClickListener() {
            public void onClick(View v) {
                handleLoadButton();
            }
        });
        Button cancelButton = (Button) findViewById(R.id.cancel);
        cancelButton.setOnClickListener(new OnClickListener() {
            public void onClick(View v) {
                setResult(RESULT_CANCELED);
                finish();
            }
        });
        Button deleteButton = (Button) findViewById(R.id.button_delete);
        deleteButton.setOnClickListener(new OnClickListener() {
            public void onClick(View v) {
                handleDeleteButton();
            }
        });
    }

    protected void handleDeleteButton() {
        android.content.DialogInterface.OnClickListener onClickListener =
            new DialogInterface.OnClickListener() {
            public void onClick(DialogInterface dialog, int which) {
                doDeleteEntities();
            }
        };
        String message = "Are you sure you want to delete these?";

        androidEntityUtil.displayConfirmationDialog("Remove?", message,
                onClickListener);
    }

    protected void doDeleteEntities() {
        Collection<Integer> checkedIds = getCheckedIds();

        dbHelper.deleteEntities(checkedIds);

        fillData();
        getListView().invalidate();
    }

    protected void handleLoadButton() {

        Collection<Integer> checkedIds = getCheckedIds();

        for (Integer id : checkedIds)
            loadItem(id);

        Bundle bundle = new Bundle();
        bundle.putParcelableArrayList("Entities", allBundles);

        Intent intent = new Intent();
        intent.putExtras(bundle);

        setResult(RESULT_OK, intent);
        finish();
    }

    private Collection<Integer> getCheckedIds() {
        Collection<Integer> checkedIds = new ArrayList<Integer>();

        for (int i = 0; i < getListView().getCount(); ++i) {
            View view = getListView().getChildAt(i);
            if (view == null) {
                //AndroidUtils.displayInfoBox(this, "Hmm...", "view " + i + " is null");
                break;
            }
        }

        SparseBooleanArray isChecked = getListView().getCheckedItemPositions();

        for (int i = 0; i < adapter.getCount(); ++i) {
            if (isChecked.get(i)) {
                final SQLiteCursor item = (SQLiteCursor)adapter.getItem(i);
                int id = item.getInt(0);
                checkedIds.add(id);
            }
        }

        return checkedIds;
    }

    private void loadItem(int itemId) {
        Entity entity = dbHelper.fetchEntity(itemId);

        Bundle bundle = AndroidEntityUtil.putEntityFieldsInBundle(entity);

        allBundles.add(bundle);
    }

    private void fillData() {
        cursor = dbHelper.fetchEntitiesOfType(type);
        startManagingCursor(cursor);

        adapter = new SimpleCursorAdapter(this, R.layout.load_entity_row, cursor,
                AndroidEntityUtil.ALL_COLUMN_NAMES, AndroidEntityUtil.ALL_RESOURCE_IDS);
        setListAdapter(adapter);
    }

    @Override
    protected void onListItemClick(ListView listView, View view, int position, long id) {
        CheckedTextView check = (CheckedTextView) view;
        check.setChecked(!check.isChecked());
    }
}
