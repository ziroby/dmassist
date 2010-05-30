package com.ziroby.android.dmassist;

import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.TreeMap;

import android.app.ListActivity;
import android.content.Context;
import android.os.Bundle;
import android.util.Log;
import android.widget.ListAdapter;
import android.widget.SimpleAdapter;

public class MainActivity extends ListActivity {
    private static class MyListAdapter 
        extends SimpleAdapter 
        implements ListAdapter
    {

        private static final List<Map<String, String>> data
                = new ArrayList<Map<String,String>>();

        static {
            Map<String,String> datum = new TreeMap<String,String>();

            datum = new TreeMap<String,String>();
            datum.put("name", "Orge");
            datum.put("init", "12");
            datum.put("hp", "25");
            datum.put("sub", "");
            datum.put("rounds", "");
            data.add(datum);
            datum = new TreeMap<String,String>();
            datum.put("name", "Goblin 1");
            datum.put("init", "4");
            datum.put("hp", "8");
            datum.put("sub", "3");
            datum.put("rounds", "");
            data.add(datum);
            datum = new TreeMap<String,String>();
            datum.put("name", "Melf's acid arrow");
            datum.put("init", "4");
            datum.put("hp", "");
            datum.put("sub", "");
            datum.put("rounds", "3");
            data.add(datum);
            datum = new TreeMap<String,String>();
            datum.put("name", "Goblin 2");
            datum.put("init", "15");
            datum.put("hp", "3");
            datum.put("sub", "");
            datum.put("rounds", "");
            data.add(datum);
        }

        public MyListAdapter(Context context, int resource)
        {
            super(context, data, resource, 
                    new String[] {"name", "init","hp", "sub", "rounds"}, 
                    new int[] {R.id.name, R.id.init, R.id.hp, R.id.sub, R.id.rounds});
        }

    }

    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState) {
        try {
            super.onCreate(savedInstanceState);
            setContentView(R.layout.main);
            ListAdapter adapter 
            = new MyListAdapter(this, R.layout.initiative_item_row);
            setListAdapter(adapter);
        }
        catch (Exception e) {
            Log.e(this.getClass().toString(), "Exception: " + e.getLocalizedMessage(), e);
        }
    }
}