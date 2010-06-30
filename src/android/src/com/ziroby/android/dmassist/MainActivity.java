package com.ziroby.android.dmassist;


import android.app.AlertDialog;
import android.app.ListActivity;
import android.content.DialogInterface;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.ContextMenu;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.ContextMenu.ContextMenuInfo;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.AdapterView.AdapterContextMenuInfo;

import com.ziroby.android.util.AndroidUtils;
import com.ziroby.dmassist.gwtable.model.Entity;
import com.ziroby.dmassist.gwtable.model.EntityList;
import com.ziroby.dmassist.gwtable.util.Listener;
import com.ziroby.dmassist.gwtable.util.ObjectEvent;
import com.ziroby.dmassist.model.DiceEquation;
import com.ziroby.dmassist.model.EntityListImpl;

public class MainActivity extends ListActivity {
    private static final int INT_SENTINEL = -1000;

    static final EntityList dataModel = new EntityListImpl();

    private static final int MENU_ITEM_ABOUT = 0;
    private static final int MENU_ITEM_ADD_CREATURE = 1;
    private static final int MENU_REMOVE = 2;
    private static final int MENU_ITEM_ADD_EFFECT = 3;
    private static final int MENU_HEAL_DAMAGE = 4;
    private static final int MENU_SUBDUE_UNSUBDUE = 5;

    private static final int REQUEST_CODE_ADD = 0;


    private EntityListAdapter listAdapter;
    private TextView initTextView;
    private TextView roundTextView;
    private TextView timeTextView;

    enum HealOrDamage {HEAL, DAMAGE}
    enum DamageOrSubdue {DAMAGE, SUBDUE}

    static {
        dataModel.addSampleData();
    }

    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState) {
        try {
            super.onCreate(savedInstanceState);
            setContentView(R.layout.main);
            listAdapter = new EntityListAdapter(this, R.layout.initiative_item_row);
            setListAdapter(listAdapter);

            initTextView = (TextView) findViewById(R.id.initView);
            roundTextView = (TextView) findViewById(R.id.roundView);
            timeTextView = (TextView) findViewById(R.id.timeView);

            dataModel.addListener(new Listener() {
                public void objectChanged(ObjectEvent event) {
                    redraw();
                }
            });

            setButtonClickListeners();

            registerForContextMenu(getListView());
        }
        catch (Exception e) {
            AndroidUtils.displayErrorDialog(this, e);
            Log.e(this.getClass().toString(), "Exception: " + e.getLocalizedMessage(), e);
        }
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
                handleresetButton();
            }
        });
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

    protected void handleresetButton() {
        dataModel.resetNumRounds();
    }

    public boolean onCreateOptionsMenu(Menu menu) {
        int position = 0;
        menu.add(/* group id*/ 0, MENU_ITEM_ADD_CREATURE, position++,
                R.string.add_creature)
                .setIcon(android.R.drawable.ic_menu_add);

        menu.add(/* group id*/ 0, MENU_ITEM_ADD_EFFECT, position++,
                R.string.add_effect)
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
        menu.add(/* group id*/ 0, MENU_HEAL_DAMAGE, position++,
                R.string.heal_damage)
                .setIcon(android.R.drawable.ic_menu_delete);
        menu.add(/* group id*/ 0, MENU_SUBDUE_UNSUBDUE, position++,
                R.string.subdue_unsubdue)
                .setIcon(android.R.drawable.ic_menu_delete);
        menu.add(/* group id*/ 0, MENU_REMOVE, position++,
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
            }
        }
        catch (Exception e) {
            AndroidUtils.displayErrorDialog(this, e);
        }

        return false;
    }

    private void healOrDamage(MenuItem item, final DamageOrSubdue damageOrSubdue) {
        boolean isSubdue = damageOrSubdue == DamageOrSubdue.SUBDUE;

        final int position = ((AdapterContextMenuInfo)item.getMenuInfo()).position;
        final Entity entity = dataModel.getEntity(position);
        final EditText input = new EditText(this);

        final int title = isSubdue? R.string.subdue_unsubdue : R.string.heal_damage;
        final int message = isSubdue? R.string.subdue_unsubdue_by : R.string.damage_heal_by;

        final int positiveButtonText = isSubdue? R.string.subdue : R.string.damage;
        final int nuetralButtonText = isSubdue? R.string.unsubdue : R.string.heal;
        AlertDialog alert = new AlertDialog.Builder(this)
        .setTitle(title)
        .setMessage(message)
        .setView(input)
        .setPositiveButton(positiveButtonText, new DialogInterface.OnClickListener() {
            public void onClick(DialogInterface dialog, int which) {
                healOrDamage(damageOrSubdue, HealOrDamage.DAMAGE, entity, input);
                dialog.cancel();
            }
        })
        .setNeutralButton(nuetralButtonText, new DialogInterface.OnClickListener() {
            public void onClick(DialogInterface dialog, int which) {
                healOrDamage(damageOrSubdue, HealOrDamage.HEAL, entity, input);
                dialog.cancel();
            }
        })
        .setNegativeButton(R.string.cancel, new DialogInterface.OnClickListener() {
            public void onClick(DialogInterface dialog, int id) {
                dialog.cancel();
            }
        })
        .create();

        alert.show();
    }

    private void addEffect() {
        startAddActivity(AddCreature.ADD_TYPE_EFFECT);
    }

    private void removeLine(MenuItem item) {

        final int position = ((AdapterContextMenuInfo)item.getMenuInfo()).position;

        final Entity entityToRemove = dataModel.getEntity(position);

        String message = "Are you sure you want to delete \""
            + entityToRemove.getName() + "\"?";

        AlertDialog.Builder builder = new AlertDialog.Builder(this);
        builder.setMessage(message)
        .setCancelable(true)
        .setTitle("Remove?")
        .setNegativeButton("No", new DialogInterface.OnClickListener() {
            public void onClick(DialogInterface dialog, int id) {
                dialog.cancel();
            }
        })
        .setPositiveButton("Yes", new DialogInterface.OnClickListener() {
            public void onClick(DialogInterface dialog, int id) {
                removeEntity(position);
            }
        });
        AlertDialog alert = builder.create();

        alert.show();
    }

    protected void removeEntity(int position) {
        dataModel.remove(position);
    }

    private void addCreature() {
        final int addType = AddCreature.ADD_TYPE_CREATURE;
        startAddActivity(addType);
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
            final int rounds= data.getIntExtra(EntityList.COLUMN_NAME_ROUNDS, INT_SENTINEL);

            if (name != null) entity.setName(name);
            if (init != INT_SENTINEL) entity.setInitRoll(init);
            if (hp != INT_SENTINEL) entity.setHitpoints(hp);
            if (abbrev != null) entity.setAbbreviation(abbrev);
            if (subdual != INT_SENTINEL) entity.setSubdual(subdual);
            if (rounds != INT_SENTINEL) entity.setRoundsLeft(rounds);

            dataModel.addEntity(entity);

            redraw();
        } catch (RuntimeException e)
        {
            AndroidUtils.displayErrorDialog(this, e);
        }
    }

    void healOrDamage(DamageOrSubdue damageOrSubdue, HealOrDamage healOrDamage, final Entity entity, final EditText input) {
        try {
            DiceEquation amount = new DiceEquation(input.getText().toString());
            if (damageOrSubdue == DamageOrSubdue.DAMAGE) {
                if (healOrDamage == HealOrDamage.HEAL)
                    entity.heal(amount.roll());
                else
                    entity.damage(amount.roll());
            }
            else
                if (healOrDamage == HealOrDamage.HEAL)
                    entity.healSubdual(amount.roll());
                else
                    entity.subdue(amount.roll());

            redraw();
        }
        catch (Exception e) {
            AndroidUtils.displayErrorDialog(this, e);
        }
    }
}