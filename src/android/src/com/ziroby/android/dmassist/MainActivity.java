package com.ziroby.android.dmassist;


import java.util.ArrayList;

import android.app.ListActivity;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.preference.PreferenceManager;
import android.text.Html;
import android.util.Log;
import android.view.ContextMenu;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.ContextMenu.ContextMenuInfo;
import android.view.View.OnClickListener;
import android.widget.AdapterView;
import android.widget.Button;
import android.widget.ListView;
import android.widget.TextView;
import android.widget.Toast;
import android.widget.AdapterView.AdapterContextMenuInfo;
import android.widget.AdapterView.OnItemClickListener;

import com.ziroby.android.util.AndroidUtils;
import com.ziroby.dmassist.gwtable.model.Entity;
import com.ziroby.dmassist.gwtable.model.EntityList;
import com.ziroby.dmassist.gwtable.util.Listener;
import com.ziroby.dmassist.gwtable.util.ObjectEvent;
import com.ziroby.dmassist.model.EntityListImpl;

public class MainActivity extends ListActivity {
    static final EntityList dataModel = new EntityListImpl();

    private static final int MENU_ITEM_ABOUT = 0;
    private static final int MENU_ITEM_ADD_CREATURE = 1;
    private static final int MENU_REMOVE = 2;
    private static final int MENU_ITEM_ADD_EFFECT = 3;
    private static final int MENU_HEAL_DAMAGE = 4;
    private static final int MENU_SUBDUE_UNSUBDUE = 5;
    private static final int MENU_ITEM_CLEAR = 6;
    private static final int MENU_ITEM_LOAD = 7;
    private static final int MENU_ITEM_HELP = 8;
	private static final int MENU_ITEM_SETTINGS = 9;

    private static final int REQUEST_CODE_ADD = 0;
    private static final int REQUEST_CODE_EDIT = 1;
    private static final int REQUEST_CODE_LOAD = 2;

    private EntityListAdapter listAdapter;
    private TextView initTextView;
    private TextView roundTextView;
    private TextView timeTextView;

    private AndroidEntityUtil androidEntityUtil;

    enum HealOrDamage {HEAL, DAMAGE}
    enum DamageOrSubdue {DAMAGE, SUBDUE}

    static {
        //dataModel.addSampleData();
    }

    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState) {
        try {
            super.onCreate(savedInstanceState);
            setContentView(R.layout.main);
            listAdapter = new EntityListAdapter(this, R.layout.initiative_item_row);
            setListAdapter(listAdapter);

            setViewVariables();

            addDataModelListener();

            setButtonClickListeners();

            registerForContextMenu(getListView());

            setListViewClickListener();

            setHtmlStrings();

            androidEntityUtil = new AndroidEntityUtil(this);

            getListView().setChoiceMode(ListView.CHOICE_MODE_SINGLE);
        }
        catch (Exception e) {
            AndroidUtils.displayErrorDialog(this, e);
            Log.e(this.getClass().toString(), "Exception: " + e.getLocalizedMessage(), e);
        }
    }

    private void setListViewClickListener() {
        getListView().setOnItemClickListener(new OnItemClickListener() {
            public void onItemClick(AdapterView<?> adapter, View view,
                    int position, long id) {
                editEntity(position, id);
            }
        });
    }

    protected void editEntity(int position, long id) {
        Entity entity = dataModel.getEntity(position);

        Bundle bundle = AndroidEntityUtil.putEntityFieldsInBundle(entity);

        Intent intent = new Intent(this, EditEntity.class);
        intent.putExtras(bundle);
        startActivityForResult(intent, REQUEST_CODE_EDIT);


    }

    private void addDataModelListener() {
        dataModel.addListener(new Listener() {
            public void objectChanged(ObjectEvent event) {
                redraw();
            }
        });
    }

    private void setViewVariables() {
        initTextView = (TextView) findViewById(R.id.initView);
        roundTextView = (TextView) findViewById(R.id.roundView);
        timeTextView = (TextView) findViewById(R.id.timeView);
    }

    private void setButtonClickListeners() {
        Button nextButton = (Button) findViewById(R.id.nextButton);
        nextButton.setOnClickListener(new OnClickListener() {
            public void onClick(View v) {
                handleNextButton();
            }
        });

        Button resetButton = (Button) findViewById(R.id.resetButton);
        resetButton.setOnClickListener(new OnClickListener() {
            public void onClick(View v) {
                handleResetButton();
            }
        });

        Button addSampleDataButton = (Button) findViewById(R.id.addSampleData);
        addSampleDataButton.setOnClickListener(new OnClickListener() {
            public void onClick(View v) {
                addSampleData();
            }
        });
    }

    protected void addSampleData() {
        dataModel.addSampleData();
    }

    protected void redraw() {
        try {
            final Integer initCount = dataModel.getInitCount();
            initTextView.setText(initCount == null? "" : initCount.toString());
            roundTextView.setText("round: " + dataModel.getNumRounds());
            timeTextView.setText(dataModel.formatRoundsAsTime());

            getListView().invalidate();
        }
        catch (Throwable t)
        {
            AndroidUtils.displayErrorDialog(this, null);
        }
    }


    protected void handleNextButton() {
        dataModel.gotoNextInitCount();
    }

    protected void handleResetButton() {
        dataModel.resetNumRounds();
    }

    public boolean onCreateOptionsMenu(Menu menu) {
        int position = 0;
        menu.add(/* group id*/ 0, MENU_ITEM_ADD_EFFECT, position++,
                R.string.add)
                .setIcon(android.R.drawable.ic_menu_add);

        menu.add(/* group id*/ 0, MENU_ITEM_ABOUT, position++,
                R.string.displayAboutBox)
                .setIcon(android.R.drawable.ic_menu_info_details);

        menu.add(/* group id*/ 0, MENU_ITEM_HELP, position++,
                R.string.help)
                .setIcon(android.R.drawable.ic_menu_help);

        menu.add(/* group id*/ 0, MENU_ITEM_LOAD, position++,
                R.string.load_item)
                .setIcon(R.drawable.ic_menu_archive);

        menu.add(/* group id*/ 0, MENU_ITEM_CLEAR, position++,
                R.string.clear_all)
                .setIcon(android.R.drawable.ic_menu_delete);
        menu.add(/* group id*/ 0, MENU_ITEM_SETTINGS, position++,
                R.string.settings)
                .setIcon(android.R.drawable.ic_menu_preferences);

        return super.onCreateOptionsMenu(menu);
    }

    public void onCreateContextMenu(ContextMenu menu, View v,
            ContextMenuInfo menuInfo) {
        super.onCreateContextMenu(menu, v, menuInfo);

        final int position = ((AdapterContextMenuInfo)menuInfo).position;
        Entity entity = dataModel.getEntity(position);

        menu.setHeaderTitle(entity.getName());
        int menuRow = 0;
        menu.add(/* group id*/ 0, MENU_HEAL_DAMAGE, menuRow++,
                R.string.heal_damage)
                .setIcon(android.R.drawable.ic_menu_delete);
        menu.add(/* group id*/ 0, MENU_SUBDUE_UNSUBDUE, menuRow++,
                R.string.subdue_unsubdue)
                .setIcon(android.R.drawable.ic_menu_delete);
        menu.add(/* group id*/ 0, MENU_REMOVE, menuRow++,
                R.string.remove_item)
                .setIcon(android.R.drawable.ic_menu_delete);
    }

    @Override
    public boolean onContextItemSelected(MenuItem item) {
        return onItemSelected(item);
    }

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
            case MENU_ITEM_ADD_EFFECT:
                addEffect();
                return true;
            case MENU_REMOVE:
                removeLine(item);
                return true;
            case MENU_HEAL_DAMAGE:
                healOrDamage(item, DamageOrSubdue.DAMAGE);
                return true;
            case MENU_SUBDUE_UNSUBDUE:
                healOrDamage(item, DamageOrSubdue.SUBDUE);
                return true;
            case MENU_ITEM_CLEAR:
                clearAll();
                return true;
            case MENU_ITEM_LOAD:
                loadEntity();
                return true;
            case MENU_ITEM_HELP:
                displayHelp();
                return true;
            case MENU_ITEM_SETTINGS:
            	showSettings();
            	return true;
            }
        }
        catch (Exception e) {
            AndroidUtils.displayErrorDialog(this, e);
        }

        return false;
    }

    private void showSettings() {
        Context context = getApplicationContext();
        Intent intent = new Intent(context, MyPreferencesActivity.class);
        startActivity(intent);
    	
	}

	private void displayHelp() {
        Intent intent = new Intent(this, Help.class);
        startActivity(intent);
    }

    private void clearAll() {
        String message = "Are you sure you want to remove all entries?";

        final DialogInterface.OnClickListener onClickListener = new DialogInterface.OnClickListener() {
            public void onClick(DialogInterface dialog, int id) {
                dataModel.clear();
            }
        };

        androidEntityUtil.displayConfirmationDialog("Clear All?", message, onClickListener);
    }

    private void addEffect() {
        startAddActivity(AddCreature.ADD_TYPE_EFFECT);
    }

    private void removeLine(MenuItem item) {

        final int position = ((AdapterContextMenuInfo)item.getMenuInfo()).position;

        final Entity entityToRemove = dataModel.getEntity(position);

        String message = "Are you sure you want to delete \""
            + entityToRemove.getName() + "\"?";

        final DialogInterface.OnClickListener onClickListener = new DialogInterface.OnClickListener() {
            public void onClick(DialogInterface dialog, int id) {
                removeEntity(position);
            }
        };
        androidEntityUtil.displayConfirmationDialog("Remove?", message, onClickListener);
    }

    protected void removeEntity(int position) {
        dataModel.remove(position);
    }

    private void addCreature() {
        startAddActivity(AddCreature.ADD_TYPE_CREATURE);
    }

    private void startAddActivity(final int addType) {
        Bundle bundle = new Bundle();

        bundle.putInt(AddCreature.ADD_TYPE_TAG, addType);

        Intent intent = new Intent(this, AddCreature.class);
        intent.putExtras(bundle);
        startActivityForResult(intent, REQUEST_CODE_ADD);
    }

    private void displayAboutBox() {
        Intent intent = new Intent(this, AboutBox.class);
        startActivity(intent);
    }

    private void loadEntity() {
        Intent intent = new Intent(this, QueryTypeForLoad.class);
        startActivityForResult(intent, REQUEST_CODE_LOAD);
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        try
        {
            switch (requestCode)
            {
            case REQUEST_CODE_ADD:
                addCreature(data);
                break;
            case REQUEST_CODE_EDIT:
                handleEditResult(data);
                break;
            case REQUEST_CODE_LOAD:
                addMultipleEntities(data);
                break;
            }
        }
        catch (RuntimeException e)
        {
            AndroidUtils.displayErrorDialog(this, e);
        }
    }
    
    @Override
    protected void onStart() {
    	super.onStart();
    	setPreferences();
    }

    private void setPreferences() {
    	SharedPreferences preferences 
    		= PreferenceManager
    		.getDefaultSharedPreferences(getApplicationContext());
    	
    	String roundTimeString = preferences.getString("round_time", "");
    	Toast toast = Toast.makeText(this, "round time = " + roundTimeString, Toast.LENGTH_LONG);
    	toast.show();
    	Integer secondsPerRound;
    	try {
    		secondsPerRound = Integer.parseInt(roundTimeString);
    	}
    	catch (NumberFormatException e)
    	{
    		secondsPerRound = null;
    	}
		MainActivity.dataModel.setTimePerRound(secondsPerRound);
    }

	private void handleEditResult(Intent data) {
        if (data == null)
            return;

        int position = data.getIntExtra("position", 0);
        boolean doRemove = data.getBooleanExtra("remove", false);

        if (doRemove)
            removeEntity(position);
        else {
            Entity entity = AndroidEntityUtil.getEntityFromBundle(data);

            dataModel.setEntity(position, entity);
        }
    }

    private void addCreature(Intent data) {
        if (data == null)
            return;

        Entity entity = AndroidEntityUtil.getEntityFromBundle(data);

        dataModel.addEntity(entity);

        redraw();
    }


    private void addMultipleEntities(Intent data) {
        if (data == null)
            return;

        ArrayList<Bundle> bundles = data.getParcelableArrayListExtra("Entities");

        for (Bundle bundle : bundles) {
            Entity entity = AndroidEntityUtil.getEntityFromBundle(bundle);
            dataModel.addEntity(entity);
        }
        redraw();
    }



    public void healOrDamage(MenuItem item, final DamageOrSubdue damageOrSubdue) {

        final int position = ((AdapterContextMenuInfo)item.getMenuInfo()).position;
        final Entity entity = dataModel.getEntity(position);
        androidEntityUtil.healOrDamage(damageOrSubdue, entity, new Runnable() {
            public void run() {
                getListView().invalidate();
            }
        });
    }

    /** The TextView XML file is stupid in that it doesn't accept HTML.  This is our hack */
    private void setHtmlStrings() {
        TextView emptyText = (TextView) findViewById(R.id.text_view_no_entities);
        String htmlText = getResources().getString(R.string.no_entities);

        emptyText.setText(Html.fromHtml(htmlText));
    }


}