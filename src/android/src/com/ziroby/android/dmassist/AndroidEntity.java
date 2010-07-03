package com.ziroby.android.dmassist;

import android.content.Intent;
import android.os.Bundle;

import com.ziroby.dmassist.gwtable.model.Entity;
import com.ziroby.dmassist.gwtable.model.EntityList;

public class AndroidEntity
{
    private static final int INT_SENTINEL = -1000;

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

    public static Bundle putEntityFieldsInBundle(Entity entity) {
        return putEntityFieldsInBundle(
                entity.getName(),
                entity.getInitRoll(),
                entity.getHitpoints(),
                entity.getAbbreviation(),
                entity.getSubdual(),
                entity.getRoundsLeft());
    }
    public static Entity getEntityFromBundle(Intent data) {
        Entity entity = new Entity();

        final String name = data.getStringExtra(EntityList.COLUMN_NAME_NAME);
        final int init = data.getIntExtra(EntityList.COLUMN_NAME_INIT, AndroidEntity.INT_SENTINEL);
        final int hp = data.getIntExtra(EntityList.COLUMN_NAME_HP, AndroidEntity.INT_SENTINEL);
        final String abbrev = data.getStringExtra(EntityList.COLUMN_NAME_ABBREV);
        final int subdual = data.getIntExtra(EntityList.COLUMN_NAME_SUBDUAL, AndroidEntity.INT_SENTINEL);
        final int rounds= data.getIntExtra(EntityList.COLUMN_NAME_ROUNDS, AndroidEntity.INT_SENTINEL);

        if (name != null) entity.setName(name);
        if (init != AndroidEntity.INT_SENTINEL) entity.setInitRoll(init);
        if (hp != AndroidEntity.INT_SENTINEL) entity.setHitpoints(hp);
        if (abbrev != null) entity.setAbbreviation(abbrev);
        if (subdual != AndroidEntity.INT_SENTINEL) entity.setSubdual(subdual);
        if (rounds != AndroidEntity.INT_SENTINEL) entity.setRoundsLeft(rounds);
        return entity;
    }


}
