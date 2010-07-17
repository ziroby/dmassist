/*
 *   Copyright 2010 Ron "Ziroby" Romero
 *
 *   This file is part of dmassist-android.
 *
 *   dmassist-android is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   dmassist-android is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with dmassist-android.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

package com.ziroby.android.dmassist;

import java.util.ArrayList;
import java.util.List;
import java.util.Map;

import android.content.Context;
import android.graphics.Color;
import android.graphics.Typeface;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ListAdapter;
import android.widget.SimpleAdapter;
import android.widget.TextView;

import com.ziroby.dmassist.gwtable.model.Entity;
import com.ziroby.dmassist.gwtable.util.Listener;
import com.ziroby.dmassist.gwtable.util.ObjectEvent;

public class EntityListAdapter
extends SimpleAdapter
implements ListAdapter
{
    private static final int HIGHLIGHT_COLOR = Color.YELLOW;
    private static final int NON_HIGHLIGHT_COLOR = Color.WHITE;

    static List<Map<String, String>> data = new ArrayList<Map<String, String>>();

    public EntityListAdapter(Context context, int resource)
    {
        super(context, MainActivity.dataModel.getListOfMaps(data), resource,
                AndroidEntityUtil.ALL_COLUMN_NAMES,
                AndroidEntityUtil.ALL_RESOURCE_IDS
            );

        MainActivity.dataModel.addListener(new Listener() {
            public void objectChanged(ObjectEvent event) {
                MainActivity.dataModel.getListOfMaps(data);
                notifyDataSetChanged();
            }
        });
    }

    public View getView(int position, View convertView, ViewGroup parent) {
        final View view = super.getView(position, convertView, parent);

        Entity entity = MainActivity.dataModel.getEntity(position);
        highlightEntity(entity, view, view.isSelected());
        return view;
    }

    private void highlightEntity(Entity entity, final View view, boolean forceSelected) {

        highlightIfCurrentTurn(entity, view, forceSelected);
        highlightNegativeHitpoints(entity, view);
        highlightSubdued(entity, view);
        highlightExpired(entity, view);
    }

    private void highlightNegativeHitpoints(Entity entity, final View view) {
        TextView hpView = (TextView) view.findViewById(R.id.hp);
        if (hpView != null) {
            final Integer hitpoints = entity.getHitpoints();
            final boolean shouldHighlight = hitpoints != null && hitpoints < 1;
            highlightText(hpView, shouldHighlight);
        }
    }

    private void highlightSubdued(Entity entity, final View view) {
        TextView subView = (TextView) view.findViewById(R.id.sub);
        if (subView != null) {
            final boolean shouldHighlight = entity.isSubdued();
            highlightText(subView, shouldHighlight);
        }
    }

    private void highlightExpired(Entity entity, final View view) {
        TextView roundsView = (TextView) view.findViewById(R.id.rounds);
        if (roundsView != null) {
            final boolean shouldHighlight = entity.isExpired(0);
            highlightText(roundsView, shouldHighlight);
        }
    }

    private void highlightText(TextView view,
            final boolean shouldHighlight) {
        if (shouldHighlight) {
            view.setTextColor(Color.BLUE);
            view.setTypeface(Typeface.DEFAULT_BOLD);
        }
        else {
            view.setTextColor(Color.BLACK);
            view.setTypeface(Typeface.DEFAULT);
        }
    }

    private void highlightIfCurrentTurn(Entity entity, final View view, boolean forceSelected) {
        final Integer initCount = MainActivity.dataModel.getInitCount();
        final Integer initRoll = entity.getInitRoll();
        if (initRoll != null && initRoll == initCount || forceSelected)
            view.setBackgroundColor(HIGHLIGHT_COLOR);
        else
            view.setBackgroundColor(NON_HIGHLIGHT_COLOR);
    }

}