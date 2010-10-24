package com.ziroby.android.dmassist;

import android.content.Intent;
import android.os.Bundle;

import com.ziroby.android.util.AndroidUtils;

public class AddCreature extends EntityActivity
{
    public static final String ADD_TYPE_TAG = "add_type";

    public static final int ADD_TYPE_CREATURE = 0;
    public static final int ADD_TYPE_EFFECT = 1;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        try {
            setContentView(R.layout.add_effect);

            setViewVariables();

            wireInButtons();
        }
        catch (Exception e) {
            AndroidUtils.displayErrorDialog(this, e);
        }

    }

    protected void doAdd() {
        try {
            Bundle bundle = getEntityFromEditFields();

            Intent intent = new Intent();
            intent.putExtras(bundle);

            setResult(RESULT_OK, intent);
            finish();
        }
        catch (Exception e) {
            AndroidUtils.displayErrorDialog(this, e);
        }

    }

    protected void finishSuccessfully() {
        doAdd();
    }

}
