package com.ziroby.android.dmassist;

import java.util.ArrayList;
import java.util.List;
import java.util.Map;

import android.app.AlertDialog;
import android.app.ListActivity;
import android.content.Context;
import android.content.DialogInterface;
import android.graphics.Color;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.ListAdapter;
import android.widget.SimpleAdapter;
import android.widget.TextView;

import com.ziroby.dmassist.model.Entity;
import com.ziroby.dmassist.model.EntityList;
import com.ziroby.dmassist.model.EntityListImpl;
import com.ziroby.util.Listener;
import com.ziroby.util.ObjectEvent;

public class MainActivity extends ListActivity {
    static final EntityList dataModel = new EntityListImpl();
    private static final int HIGHLIGHT_COLOR = Color.YELLOW;
    private static final int NON_HIGHLIGHT_COLOR = Color.WHITE;
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
}
        catch (Exception e) {
            Log.e(this.getClass().toString(), "Exception: " + e.getLocalizedMessage(), e);
        }
    }
    
    protected void redraw() {
        try {            
            final Integer initCount = dataModel.getInitCount();
            initTextView.setText(initCount == null? "" : initCount.toString());
            roundTextView.setText("round: " + dataModel.getNumRounds());
            timeTextView.setText(dataModel.formatRoundsAsTime());
            
            getListView().invalidate();
            
            // Highlight the entities who's turn it is.
            int row = 0;
            for (Entity entity : dataModel.getEntities())
            {
                if (entity.getInitRoll() == initCount)
                    getListView().getChildAt(row).setBackgroundColor(HIGHLIGHT_COLOR);
                else
                    getListView().getChildAt(row).setBackgroundColor(NON_HIGHLIGHT_COLOR);
                ++row;
            }
        }
        catch (Throwable t)
        {
            AlertDialog.Builder builder = new AlertDialog.Builder(this);
            
            builder.setMessage("Error: " + t.getClass().toString()+ ": "+ t.toString())
                   .setCancelable(false)
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
    
    @SuppressWarnings("unchecked")
    private void showStupidDialog()
    {
        Map<String, String> item = (Map<String, String>) getListView().getItemAtPosition(0);
        AlertDialog.Builder builder = new AlertDialog.Builder(this);
        builder.setMessage(item.getClass().toString())
               .setCancelable(false)
               .setPositiveButton("OK", new DialogInterface.OnClickListener() {
                   public void onClick(DialogInterface dialog, int id) {
                        dialog.cancel();
                   }
               });
        AlertDialog alert = builder.create();
        
        alert.show();
    }

    protected void handleNextButton() {
        dataModel.gotoNextInitCount();
    }

    protected void handleresetButton() {
        dataModel.resetNumRounds();
    }
}