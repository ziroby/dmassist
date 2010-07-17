package com.ziroby.android.dmassist;

import android.app.Activity;
import android.app.AlertDialog;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.DialogInterface.OnClickListener;
import android.os.Bundle;
import android.widget.EditText;

import com.ziroby.android.dmassist.MainActivity.DamageOrSubdue;
import com.ziroby.android.dmassist.MainActivity.HealOrDamage;
import com.ziroby.android.util.AndroidUtils;
import com.ziroby.dmassist.gwtable.model.Entity;
import com.ziroby.dmassist.gwtable.model.EntityList;
import com.ziroby.dmassist.model.DiceEquation;

public class AndroidEntityUtil
{
    private Activity activity;
    public static final String[] ALL_COLUMN_NAMES = new String[] {
        "_id",
        EntityList.COLUMN_NAME_NAME,
        EntityList.COLUMN_NAME_ABBREV,
        EntityList.COLUMN_NAME_INIT,
        EntityList.COLUMN_NAME_HP,
        EntityList.COLUMN_NAME_SUBDUAL,
        EntityList.COLUMN_NAME_ROUNDS
    };

    public static final int[] ALL_RESOURCE_IDS = new int[]{
            0, R.id.name, R.id.abbrev, R.id.init, R.id.hp, R.id.sub, R.id.rounds};

    private static final int INT_SENTINEL = -1000;

    public AndroidEntityUtil(Activity activity)
    {
        this.activity = activity;
    }

    public void healOrDamage(final DamageOrSubdue damageOrSubdue,
            final Entity entity, final Runnable runOnCompletion) {
        final EditText input = new EditText(activity);

        boolean isSubdue = damageOrSubdue == DamageOrSubdue.SUBDUE;
        final int title = isSubdue? R.string.subdue_unsubdue : R.string.heal_damage;
        final int message = isSubdue? R.string.subdue_unsubdue_by : R.string.damage_heal_by;

        final int positiveButtonText = isSubdue? R.string.subdue : R.string.damage;
        final int nuetralButtonText = isSubdue? R.string.unsubdue : R.string.heal;
        AlertDialog alert = new AlertDialog.Builder(activity)
        .setTitle(title)
        .setMessage(message)
        .setView(input)
        .setPositiveButton(positiveButtonText, new DialogInterface.OnClickListener() {
            public void onClick(DialogInterface dialog, int which) {
                healOrDamage(damageOrSubdue, HealOrDamage.DAMAGE, entity, input);
                dialog.cancel();
                runOnCompletion.run();
            }
        })
        .setNeutralButton(nuetralButtonText, new DialogInterface.OnClickListener() {
            public void onClick(DialogInterface dialog, int which) {
                healOrDamage(damageOrSubdue, HealOrDamage.HEAL, entity, input);
                dialog.cancel();
                runOnCompletion.run();
            }
        })
        .setNegativeButton(R.string.cancel, new DialogInterface.OnClickListener() {
            public void onClick(DialogInterface dialog, int id) {
                dialog.cancel();
            }
        })
        .create();

        alert.show();
    }

    void healOrDamage(DamageOrSubdue damageOrSubdue, HealOrDamage healOrDamage,
            final Entity entity, final EditText input) {
        try {
            DiceEquation amount = new DiceEquation(input.getText().toString());
            if (damageOrSubdue == DamageOrSubdue.DAMAGE) {
                if (healOrDamage == HealOrDamage.HEAL)
                    entity.heal(amount.roll());
                else
                    entity.damage(amount.roll());
            }
            else
                if (healOrDamage == HealOrDamage.HEAL)
                    entity.healSubdual(amount.roll());
                else
                    entity.subdue(amount.roll());
        }
        catch (Exception e) {
            AndroidUtils.displayErrorDialog(activity, e);
        }
    }

    public void displayConfirmationDialog(final String title,
            String message, final DialogInterface.OnClickListener onClickListener) {
        AlertDialog.Builder builder = new AlertDialog.Builder(activity);

        builder.setMessage(message)
        .setCancelable(true)
        .setTitle(title)
        .setNegativeButton("No", cancelClickListener())
        .setPositiveButton("Yes", onClickListener);
        AlertDialog alert = builder.create();

        alert.show();
    }

    private OnClickListener cancelClickListener() {
        return new DialogInterface.OnClickListener() {
            public void onClick(DialogInterface dialog, int id) {
                dialog.cancel();
            }
        };
    }

    public static Entity getEntityFromBundle(Intent data) {
        Bundle bundle = data.getExtras();

        return getEntityFromBundle(bundle);
    }

    public static Entity getEntityFromBundle(Bundle bundle) {
        Entity entity = new Entity();
        final String name = bundle.getString(EntityList.COLUMN_NAME_NAME);
        final int init = bundle.getInt(EntityList.COLUMN_NAME_INIT, AndroidEntityUtil.INT_SENTINEL);
        final int hp = bundle.getInt(EntityList.COLUMN_NAME_HP, AndroidEntityUtil.INT_SENTINEL);
        final String abbrev = bundle.getString(EntityList.COLUMN_NAME_ABBREV);
        final int subdual = bundle.getInt(EntityList.COLUMN_NAME_SUBDUAL, AndroidEntityUtil.INT_SENTINEL);
        final int rounds= bundle.getInt(EntityList.COLUMN_NAME_ROUNDS, AndroidEntityUtil.INT_SENTINEL);

        if (name != null) entity.setName(name);
        if (init != AndroidEntityUtil.INT_SENTINEL) entity.setInitRoll(init);
        if (hp != AndroidEntityUtil.INT_SENTINEL) entity.setHitpoints(hp);
        if (abbrev != null) entity.setAbbreviation(abbrev);
        if (subdual != AndroidEntityUtil.INT_SENTINEL) entity.setSubdual(subdual);
        if (rounds != AndroidEntityUtil.INT_SENTINEL) entity.setRoundsLeft(rounds);
        return entity;
    }

    public static Bundle putEntityFieldsInBundle(Entity entity) {
        return putEntityFieldsInBundle(
                entity.getName(),
                entity.getInitRoll(),
                entity.getHitpoints(),
                entity.getAbbreviation(),
                entity.getSubdual(),
                entity.getRoundsLeft());
    }

    public static Bundle putEntityFieldsInBundle(String name, Integer init,
            Integer hp, String abbrev, Integer subdual, Integer rounds) {
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
        return bundle;
    }
}
