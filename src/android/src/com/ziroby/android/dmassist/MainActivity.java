package com.ziroby.android.dmassist;

import java.util.ArrayList;
import java.util.List;
import java.util.Map;

import android.app.AlertDialog;
import android.app.ListActivity;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.graphics.Color;
import android.os.Bundle;
import android.util.Log;
import android.view.ContextMenu;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.ContextMenu.ContextMenuInfo;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.ListAdapter;
import android.widget.SimpleAdapter;
import android.widget.TextView;

import com.ziroby.android.util.AndroidUtils;
import com.ziroby.dmassist.model.Entity;
import com.ziroby.dmassist.model.EntityList;
import com.ziroby.dmassist.model.EntityListImpl;
import com.ziroby.util.Listener;
import com.ziroby.util.ObjectEvent;

public class MainActivity extends ListActivity {
    private static final int INT_SENTINEL = -1000;

    static final EntityList dataModel = new EntityListImpl();

    private static final int HIGHLIGHT_COLOR = Color.YELLOW;
    private static final int NON_HIGHLIGHT_COLOR = Color.WHITE;

    private static final int MENU_ITEM_ABOUT = 0;
    private static final int MENU_ITEM_ADD_CREATURE = 1;

    private static final int REQUEST_CODE_ADD = 0;

    private MyListAdapter listAdapter;
    private TextView initTextView;
    private TextView roundTextView;
    private TextView timeTextView;

    private static void addSampleData(EntityList aDataModel) {
        Entity row1 = new Entity();
        row1.setAbbreviation("O"); //$NON-NLS-1$
        row1.setName("Ogre"); //$NON-NLS-1$
        row1.setInitRoll(12);
        row1.setHitpoints(25);
        aDataModel.addEntity(row1);

        Entity row2 = new Entity();
        row2.setAbbreviation("G1"); //$NON-NLS-1$
        row2.setName("Goblin 1"); //$NON-NLS-1$
        row2.setInitRoll(4);
        row2.setHitpoints(8);
        row2.setSubdual(3);
        aDataModel.addEntity(row2);

        Entity row4 = new Entity();
        row4.setName("Melf's acid arrow"); //$NON-NLS-1$
        row4.setInitRoll(4);
        row4.setRoundsLeft(3);
        aDataModel.addEntity(row4);

        Entity row3 = new Entity();
        row3.setAbbreviation("G2"); //$NON-NLS-1$
        row3.setName("Goblin 2"); //$NON-NLS-1$
        row3.setInitRoll(15);
        row3.setHitpoints(3);
        aDataModel.addEntity(row3);
    }


    static {
        addSampleData(dataModel);
    }

    private static class MyListAdapter
    extends SimpleAdapter
    implements ListAdapter
    {
        static List<Map<String, String>> data = new ArrayList<Map<String, String>>();

        public MyListAdapter(Context context, int resource)
        {
            super(context, dataModel.getListOfMaps(data), resource,
                    new String[] {
                EntityList.COLUMN_NAME_NAME,
                EntityList.COLUMN_NAME_INIT,
                EntityList.COLUMN_NAME_HP,
                EntityList.COLUMN_NAME_SUBDUAL,
                EntityList.COLUMN_NAME_ROUNDS},
                new int[] {R.id.name, R.id.init, R.id.hp, R.id.sub, R.id.rounds});

            dataModel.addListener(new Listener() {
                public void objectChanged(ObjectEvent event) {
                    dataModel.getListOfMaps(data);
                    notifyDataSetChanged();
                }
            });
        }

    }

    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState) {
        try {
            super.onCreate(savedInstanceState);
            setContentView(R.layout.main);
            listAdapter = new MyListAdapter(this, R.layout.initiative_item_row);
            setListAdapter(listAdapter);

            initTextView = (TextView) findViewById(R.id.initView);
            roundTextView = (TextView) findViewById(R.id.roundView);
            timeTextView = (TextView) findViewById(R.id.timeView);

            dataModel.addListener(new Listener() {
                public void objectChanged(ObjectEvent event) {
                    redraw();
                }
            });

            Button nextButton = (Button) findViewById(R.id.nextButton);
            nextButton.setOnClickListener(new OnClickListener() {
                public void onClick(View v) {
                    handleNextButton();
                }
            });

            Button resetButton = (Button) findViewById(R.id.resetButton);
            resetButton.setOnClickListener(new OnClickListener() {
                public void onClick(View v) {
                    handleresetButton();
                }
            });

            registerForContextMenu(getListView());
        }
        catch (Exception e) {
            AndroidUtils.displayErrorDialog(this, e);
            Log.e(this.getClass().toString(), "Exception: " + e.getLocalizedMessage(), e);
        }
    }

    protected void redraw() {
        char point='a';
        try {
            final Integer initCount = dataModel.getInitCount();
            initTextView.setText(initCount == null? "" : initCount.toString());
            roundTextView.setText("round: " + dataModel.getNumRounds());
            timeTextView.setText(dataModel.formatRoundsAsTime());

            point = 'b';
            getListView().invalidate();

            point = 'c';
            // Highlight the entities who's turn it is.
            int row = 0;
            for (Entity entity : dataModel.getEntities())
            {
                point = (char) (row % 10 + '1');
                final Integer initRoll = entity.getInitRoll();
                final View child = getListView().getChildAt(row);
                if (child == null)
                    break;
                if (initRoll != null && initRoll == initCount)
                    child.setBackgroundColor(HIGHLIGHT_COLOR);
                else
                    child.setBackgroundColor(NON_HIGHLIGHT_COLOR);
                ++row;
            }
            point = 'e';

        }
        catch (Throwable t)
        {
            AlertDialog.Builder builder = new AlertDialog.Builder(this);

            builder.setMessage("Error in redraw: " + point + ": " + t.getClass().toString()+ ": "+ t.toString())
            .setCancelable(true)
            .setPositiveButton("OK", new DialogInterface.OnClickListener() {
                public void onClick(DialogInterface dialog, int id) {
                    dialog.cancel();
                }
            });
            AlertDialog alert = builder.create();

            alert.show();
        }

        //        getListView().getChildAt(1).setBackgroundColor(Color.YELLOW);
    }

    protected void handleNextButton() {
        dataModel.gotoNextInitCount();
    }

    protected void handleresetButton() {
        dataModel.resetNumRounds();
    }

    public boolean onCreateOptionsMenu(Menu menu) {
        int position = 0;
        menu.add(/* group id*/ 0, MENU_ITEM_ADD_CREATURE, position++,
                R.string.add_creature)
                .setIcon(android.R.drawable.ic_menu_add);

        menu.add(/* group id*/ 0, MENU_ITEM_ABOUT, position++,
                R.string.displayAboutBox)
                .setIcon(android.R.drawable.ic_menu_info_details);
        return super.onCreateOptionsMenu(menu);
    }

    public void onCreateContextMenu(ContextMenu menu, View v,
            ContextMenuInfo menuInfo) {
        super.onCreateContextMenu(menu, v, menuInfo);
        int position = 0;
        menu.add(/* group id*/ 0, MENU_ITEM_ABOUT, position++,
                R.string.displayAboutBox);
    }

    @Override
    public boolean onContextItemSelected(MenuItem item) {
        return onItemSelected(item);
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        return onItemSelected(item);
    }

    private boolean onItemSelected(MenuItem item) {
        try {
            switch (item.getItemId()) {
            case MENU_ITEM_ABOUT:
                displayAboutBox();
                return true;
            case MENU_ITEM_ADD_CREATURE:
                addCreature();
                return true;
            }
        }
        catch (Exception e) {
            AndroidUtils.displayErrorDialog(this, e);
        }

        return false;
    }

    private void addCreature() {
        Intent intent = new Intent(this, AddCreature.class);
        startActivityForResult(intent, REQUEST_CODE_ADD);
    }

    private void displayAboutBox() {
        Intent intent = new Intent(this, AboutBox.class);
        startActivity(intent);
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {

        switch (requestCode) {
        case REQUEST_CODE_ADD:
            addCreature(data);
        }
    }

    private void addCreature(Intent data) {
        try {
            if (data == null)
                return;

            Entity entity = new Entity();

            final String name = data.getStringExtra(EntityList.COLUMN_NAME_NAME);
            final int init = data.getIntExtra(EntityList.COLUMN_NAME_INIT, INT_SENTINEL);
            final int hp = data.getIntExtra(EntityList.COLUMN_NAME_HP, INT_SENTINEL);
            final String abbrev = data.getStringExtra(EntityList.COLUMN_NAME_ABBREV);
            final int subdual = data.getIntExtra(EntityList.COLUMN_NAME_SUBDUAL, INT_SENTINEL);

            if (name != null) entity.setName(name);
            if (init != INT_SENTINEL) entity.setInitRoll(init);
            if (hp != INT_SENTINEL) entity.setHitpoints(hp);
            if (abbrev != null) entity.setAbbreviation(abbrev);
            if (subdual != INT_SENTINEL) entity.setSubdual(subdual);

            dataModel.addEntity(entity);

            redraw();
        } catch (RuntimeException e)
        {
            AndroidUtils.displayErrorDialog(this, e);
        }
    }
}