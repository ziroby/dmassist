package com.ziroby.android.dmassist;

import android.app.Activity;
import android.os.Bundle;
import android.text.Editable;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Spinner;

import com.ziroby.dmassist.gwtable.model.Entity;
import com.ziroby.dmassist.gwtable.util.StringUtil;
import com.ziroby.dmassist.model.DiceEquation;
import com.ziroby.dmassist.model.EnhancedEntity;

public abstract class EntityActivity extends Activity
{

    private EditText nameEdit;
    private EditText initEdit;
    private EditText initDiceEdit;
    private EditText hitDiceEdit;
    private EditText hpEdit;
    private EditText abbrevEdit;
    private EditText subdualEdit;
    private EditText roundsEdit;
    private Spinner typeEdit;

    public EntityActivity()
    {
        super();
    }

    protected void fillEditBoxes(EnhancedEntity entity) {
        nameEdit.setText(entity.getName());
        nameEdit.invalidate();
        initDiceEdit.setText(entity.getInitDiceString());
        initDiceEdit.invalidate();
        initEdit.setText(StringUtil.toStringOrBlank(entity.getInitRoll()));
        initEdit.invalidate();
        hitDiceEdit.setText(entity.getHitDiceString());
        hitDiceEdit.invalidate();
        hpEdit.setText(StringUtil.toStringOrBlank(entity.getHitpoints()));
        hpEdit.invalidate();
        abbrevEdit.setText(entity.getAbbreviation());
        abbrevEdit.invalidate();
        subdualEdit.setText(StringUtil.toStringOrBlank(entity.getSubdual()));
        subdualEdit.invalidate();
        roundsEdit.setText(StringUtil.toStringOrBlank(entity.getRoundsLeft()));
        roundsEdit.invalidate();
        typeEdit.setSelection(entity.getType().ordinal());
    }

    protected void setViewVariables() {
        nameEdit = (EditText) findViewById(R.id.name_edit);
        initDiceEdit = (EditText) findViewById(R.id.init_dice_edit);
        initEdit = (EditText) findViewById(R.id.init_roll_edit);
        hitDiceEdit = (EditText) findViewById(R.id.hitdice_edit);
        hpEdit = (EditText) findViewById(R.id.hp_edit);
        abbrevEdit = (EditText) findViewById(R.id.abbrev_edit);
        subdualEdit = (EditText) findViewById(R.id.subdual_edit);
        roundsEdit = (EditText) findViewById(R.id.rounds_edit);
        typeEdit = (Spinner) findViewById(R.id.type_edit);

        final ArrayAdapter<CharSequence> adapter =
            AndroidEntityUtil.getArrayAdapterForTypes(this,
                    android.R.layout.simple_spinner_item);
        adapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
        typeEdit.setAdapter(adapter);
    }

    protected Bundle getEntityFromEditFields() {
        Bundle bundle = AndroidEntityUtil.putEntityFieldsInBundle(
                getTextOf(nameEdit),
                getTextOf(initDiceEdit),
                getIntOf(initEdit),
                getTextOf(hitDiceEdit),
                getIntOf(hpEdit),
                getTextOf(abbrevEdit),
                getIntOf(subdualEdit),
                getIntOf(roundsEdit),
                typeEdit.getSelectedItemPosition());
        return bundle;
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

    protected void wireInButtons() {
        Button addButton = (Button) findViewById(R.id.done);
        addButton.setOnClickListener(new OnClickListener() {
            public void onClick(View v) {
                finishSuccessfully();
            }
        });
        Button cancelButton = (Button) findViewById(R.id.cancel);
        cancelButton.setOnClickListener(new OnClickListener() {
            public void onClick(View v) {
                doCancel();
            }
        });
    }

    protected abstract void finishSuccessfully();

    protected void doCancel() {
        setResult(RESULT_CANCELED);
        finish();
    }

}