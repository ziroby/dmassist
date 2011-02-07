package com.ziroby.android.dmassist;

import android.content.DialogInterface;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.TextView;

import com.ziroby.android.dmassist.MainActivity.DamageOrSubdue;
import com.ziroby.android.util.AndroidUtils;
import com.ziroby.dmassist.gwtable.model.Entity;
import com.ziroby.dmassist.model.EnhancedEntity;

public class EditEntity extends EntityActivity
{
    private int originalPosition;
    AndroidEntityUtil androidEntityUtil;
    EnhancedEntity entity;

    protected void onCreate(Bundle savedInstanceState) {
        try
        {
            super.onCreate(savedInstanceState);

            setContentView(R.layout.edit_entity);

            setViewVariables();

            entity = AndroidEntityUtil.getEnhancedEntityFromBundle(getIntent());

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
    protected void doRemoveEntity() {
        try
        {
            Bundle bundle = new Bundle();
            bundle.putBoolean("remove", true);
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

        Button removeButton = (Button) findViewById(R.id.button_remove);
        removeButton.setOnClickListener(new OnClickListener() {
            public void onClick(View v) {
                removeEntity();
            }
        });
        Button saveButton = (Button) findViewById(R.id.button_save);
        saveButton.setOnClickListener(new OnClickListener() {
            public void onClick(View v) {
                saveEntity();
            }
        });
    }

    protected void saveEntity() {
        try {
            EntityDbHelper dbHelper = new EntityDbHelper(this);

            dbHelper.open();

            dbHelper.saveEntity(entity);

            AndroidUtils.displayInfoBox(this, "Saved", entity.getName() + " successfully saved");
        }
        catch (Exception e)
        {
            AndroidUtils.displayErrorDialog(this, e);
        }
    }

    protected void removeEntity() {
        android.content.DialogInterface.OnClickListener onClickListener
            = new DialogInterface.OnClickListener() {
                public void onClick(DialogInterface dialog, int which) {
                    doRemoveEntity();
                }
        };
        String message = "Are you sure you want to delete \""
            + entity.getName() + "\"?";

        androidEntityUtil.displayConfirmationDialog("Remove?", message, onClickListener);
    }
}
