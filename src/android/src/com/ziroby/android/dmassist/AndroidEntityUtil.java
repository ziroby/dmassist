package com.ziroby.android.dmassist;

import android.app.Activity;
import android.app.AlertDialog;
import android.content.DialogInterface;
import android.widget.EditText;

import com.ziroby.android.dmassist.MainActivity.DamageOrSubdue;
import com.ziroby.android.dmassist.MainActivity.HealOrDamage;
import com.ziroby.android.util.AndroidUtils;
import com.ziroby.dmassist.gwtable.model.Entity;
import com.ziroby.dmassist.model.DiceEquation;

public class AndroidEntityUtil
{
    private Activity activity;

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

    void healOrDamage(DamageOrSubdue damageOrSubdue, HealOrDamage healOrDamage, final Entity entity, final EditText input) {
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
}
