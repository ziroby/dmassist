package com.ziroby.android.dmassist;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.TextView;

import com.ziroby.android.dmassist.MainActivity.DamageOrSubdue;
import com.ziroby.android.util.AndroidUtils;
import com.ziroby.dmassist.gwtable.model.Entity;

public class EditEntity extends EntityActivity
{
    private int originalPosition;
    AndroidEntityUtil androidEntityUtil;
    Entity entity;

    protected void onCreate(Bundle savedInstanceState) {
        try
        {
            super.onCreate(savedInstanceState);

            setContentView(R.layout.edit_entity);

            setViewVariables();

            entity = AndroidEntity.getEntityFromBundle(getIntent());

            fillEditBoxes(entity);

            originalPosition = getIntent().getIntExtra("position", 0);

            setTitle();

            wireInButtons();

            androidEntityUtil = new AndroidEntityUtil(this);
        }
        catch (Exception e)
        {
            AndroidUtils.displayErrorDialog(this, e);
        }

    }

    private void setTitle() {
        TextView titleView;

        titleView = (TextView) findViewById(R.id.edit_entity_title);

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

    @Override
    protected void wireInButtons() {
        super.wireInButtons();

        Button damageButton = (Button) findViewById(R.id.button_damage_heal);
        final Runnable runOnCompletion = new Runnable() {
            public void run() {
                fillEditBoxes(entity);
            }
        };
        damageButton.setOnClickListener(new OnClickListener() {
            public void onClick(View v) {
                androidEntityUtil.healOrDamage(DamageOrSubdue.DAMAGE, entity, runOnCompletion);
            }
        });
        Button subdualButton = (Button) findViewById(R.id.button_subdue_unsubdue);
        subdualButton.setOnClickListener(new OnClickListener() {
            public void onClick(View v) {
                androidEntityUtil.healOrDamage(DamageOrSubdue.SUBDUE, entity, runOnCompletion);
            }
        });
    }
}
