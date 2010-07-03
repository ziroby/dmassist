package com.ziroby.android.dmassist;

import android.content.Intent;
import android.os.Bundle;
import android.widget.TextView;

import com.ziroby.android.util.AndroidUtils;
import com.ziroby.dmassist.gwtable.model.Entity;

public class EditEntity extends EntityActivity
{
    private int originalPosition;

    protected void onCreate(Bundle savedInstanceState) {
        try
        {
            super.onCreate(savedInstanceState);

            setContentView(R.layout.edit_entity);

            setViewVariables();

            fillEditBoxes(getIntent());

            originalPosition = getIntent().getIntExtra("position", 0);

            setTitle();

            wireInButtons();
        }
        catch (Exception e)
        {
            AndroidUtils.displayErrorDialog(this, e);
        }

    }

    private void setTitle() {
        TextView titleView;

        titleView = (TextView) findViewById(R.id.edit_entity_title);

        Entity entity = AndroidEntity.getEntityFromBundle(getIntent());

        titleView.setText(entity.getName());
    }

    protected void finishSuccessfully() {
        try
        {
            Bundle bundle = getEntityFromEditFields();
            bundle.putInt("position", originalPosition);

            Intent intent = new Intent();
            intent.putExtras(bundle);

            setResult(RESULT_OK, intent);
            finish();
        }
        catch (Exception e)
        {
            AndroidUtils.displayErrorDialog(this, e);
        }
    }
}
