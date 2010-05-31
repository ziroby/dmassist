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
    private EditText nameEdit;
    private EditText initEdit;
    private EditText hpEdit;
    private EditText abbrevEdit;
    private EditText subdualEdit;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        setContentView(R.layout.add_creature);

        nameEdit = (EditText) findViewById(R.id.name_edit);
        initEdit = (EditText) findViewById(R.id.init_roll_edit);
        hpEdit = (EditText) findViewById(R.id.hp_edit);
        abbrevEdit = (EditText) findViewById(R.id.abbrev_edit);
        subdualEdit = (EditText) findViewById(R.id.subdual_edit);

        Button addButton = (Button) findViewById(R.id.addDone);
        addButton.setOnClickListener(new OnClickListener() {
            public void onClick(View v) {
                doAdd();
            }
        });

    }

    protected void doAdd() {
        try {
            String name = getTextOf(nameEdit);
            Integer init = getIntOf(initEdit);
            Integer hp = getIntOf(hpEdit);
            String abbrev = getTextOf(abbrevEdit);
            Integer subdual = getIntOf(subdualEdit);

            Bundle bundle = new Bundle();
            bundle.putString(EntityList.COLUMN_NAME_NAME, name);
            if (init != null)
                bundle.putInt(EntityList.COLUMN_NAME_INIT, init);
            if (hp != null)
                bundle.putInt(EntityList.COLUMN_NAME_HP, hp);
            bundle.putString(EntityList.COLUMN_NAME_ABBREV, abbrev);
            if (subdual != null)
                bundle.putInt(EntityList.COLUMN_NAME_SUBDUAL, subdual);

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
        final Editable text = editText.getText();
        return text == null ? null : text.toString();
    }

    private Integer getIntOf(EditText editText) {
        final Editable text = editText.getText();
        return text == null ? null
                : DiceEquation.tryParseInt(text.toString());
    }

}
