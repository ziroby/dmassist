package com.ziroby.android.dmassist;

import android.app.ListActivity;
import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.ListAdapter;
import android.widget.ListView;

public class QueryTypeForLoad extends ListActivity {
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        setListAdapter();
    }

    private void setListAdapter() {
        final Context context = this;

        ListAdapter simpleAdapter = AndroidEntityUtil
                .getAdapterForTypes(context);

        setListAdapter(simpleAdapter);
    }

    @Override
    protected void onListItemClick(ListView l, View v, int position, long id) {
        Bundle bundle = new Bundle();
        bundle.putInt("position", position);

        Intent loadEntityIntent = new Intent(this, LoadEntity.class);
        loadEntityIntent.putExtras(bundle);
        startActivityForResult(loadEntityIntent, 0);
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        if (resultCode == RESULT_OK) {
            Intent intent = new Intent();
            intent.putExtras(data);

            setResult(RESULT_OK, intent);

            finish();
        }
    }
}
