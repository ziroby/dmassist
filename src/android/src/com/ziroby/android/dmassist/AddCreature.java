package com.ziroby.android.dmassist;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.text.Editable;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.EditText;

import com.ziroby.android.util.AndroidUtils;
import com.ziroby.dmassist.model.DiceEquation;
import com.ziroby.dmassist.model.EntityList;

public class AddCreature extends Activity
{
    public static final String ADD_TYPE_TAG = "add_type";

    public static final int ADD_TYPE_CREATURE = 0;
    public static final int ADD_TYPE_EFFECT = 1;

    private EditText nameEdit;
    private EditText initEdit;
    private EditText hpEdit;
    private EditText abbrevEdit;
    private EditText subdualEdit;
    private EditText roundsEdit;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        try {
            int addType = getIntent().getExtras().getInt(AddCreature.ADD_TYPE_TAG);

            if (addType == AddCreature.ADD_TYPE_CREATURE)
                setContentView(R.layout.add_creature);
            else
                setContentView(R.layout.add_effect);

            nameEdit = (EditText) findViewById(R.id.name_edit);
            initEdit = (EditText) findViewById(R.id.init_roll_edit);
            hpEdit = (EditText) findViewById(R.id.hp_edit);
            abbrevEdit = (EditText) findViewById(R.id.abbrev_edit);
            subdualEdit = (EditText) findViewById(R.id.subdual_edit);
            roundsEdit = (EditText) findViewById(R.id.rounds_edit);

            Button addButton = (Button) findViewById(R.id.addDone);
            addButton.setOnClickListener(new OnClickListener() {
                public void onClick(View v) {
                    doAdd();
                }
            });
        }
        catch (Exception e) {
            AndroidUtils.displayErrorDialog(this, e);
        }

    }

    protected void doAdd() {
        try {
            String name = getTextOf(nameEdit);
            Integer init = getIntOf(initEdit);
            Integer hp = getIntOf(hpEdit);
            String abbrev = getTextOf(abbrevEdit);
            Integer subdual = getIntOf(subdualEdit);
            Integer rounds = getIntOf(roundsEdit);

            Bundle bundle = new Bundle();
            bundle.putString(EntityList.COLUMN_NAME_NAME, name);
            if (init != null)
                bundle.putInt(EntityList.COLUMN_NAME_INIT, init);
            if (hp != null)
                bundle.putInt(EntityList.COLUMN_NAME_HP, hp);
            bundle.putString(EntityList.COLUMN_NAME_ABBREV, abbrev);
            if (subdual != null)
                bundle.putInt(EntityList.COLUMN_NAME_SUBDUAL, subdual);
            if (rounds != null)
                bundle.putInt(EntityList.COLUMN_NAME_ROUNDS, rounds);

            Intent intent = new Intent();
            intent.putExtras(bundle);

            setResult(RESULT_OK, intent);
            finish();
        }
        catch (Exception e) {
            AndroidUtils.displayErrorDialog(this, e);
        }

    }

    private String getTextOf(EditText editText) {
        if (editText == null)
            return null;

        final Editable text = editText.getText();
        return text == null ? null : text.toString();
    }

    private Integer getIntOf(EditText editText) {
        if (editText == null)
            return null;

        final Editable text = editText.getText();
        return text == null ? null
                : DiceEquation.tryParseInt(text.toString());
    }

}
