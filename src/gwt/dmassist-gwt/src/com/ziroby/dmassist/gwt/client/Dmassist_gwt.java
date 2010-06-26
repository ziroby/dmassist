package com.ziroby.dmassist.gwt.client;

import com.google.gwt.core.client.EntryPoint;
import com.google.gwt.core.client.GWT;
import com.google.gwt.user.client.ui.FlexTable;
import com.google.gwt.user.client.ui.HorizontalPanel;
import com.google.gwt.user.client.ui.RootPanel;
import com.google.gwt.user.client.ui.VerticalPanel;
import com.ziroby.dmassist.gwtable.model.Entity;
import com.ziroby.dmassist.gwtable.model.EntityList;
import com.ziroby.dmassist.gwtable.model.EntityListGwtable;

/**
 * Entry point classes define <code>onModuleLoad()</code>.
 */
public class Dmassist_gwt implements EntryPoint
{
    private VerticalPanel mainPanel = new VerticalPanel();
    private HorizontalPanel topRowPanel = new HorizontalPanel();
    private FlexTable initListTable = new FlexTable();
    private VerticalPanel buttonBox = new VerticalPanel();

    private EntityList entityList = new EntityListGwtable();

    /**
     * The message displayed to the user when the server cannot be reached or
     * returns an error.
     */
    private static final String SERVER_ERROR = "An error occurred while "
            + "attempting to contact the server. Please check your network "
            + "connection and try again.";
    private static final int COLUMN_ABBREV = 0;
    private static final int COLUMN_NAME = 1;
    private static final int COLUMN_INIT = 2;
    private static final int COLUMN_HP = 3;
    private static final int COLUMN_SUB = 4;
    private static final int COLUMN_ROUNDS = 5;

    /**
     * Create a remote service proxy to talk to the server-side Greeting service.
     */
    private final GreetingServiceAsync greetingService = GWT
            .create(GreetingService.class);

    /**
     * This is the entry point method.
     */
    public void onModuleLoad() {
        setInitListTableHeadings();

        wireTogetherVisualElements();

        entityList.addSampleData();
        displayEntityList();
    }

    private void displayEntityList() {
        int row=1;
        for (Entity entity : entityList.getEntities())
        {
            initListTable.setText(row, COLUMN_ABBREV, entity.getAbbreviation());
            initListTable.setText(row, COLUMN_NAME, entity.getName());
            initListTable.setText(row, COLUMN_INIT, formatNumber(entity.getInitRoll()));
            initListTable.setText(row, COLUMN_HP, formatNumber(entity.getHitpoints()));
            initListTable.setText(row, COLUMN_SUB, formatNumber(entity.getSubdual()));
            initListTable.setText(row, COLUMN_ROUNDS, formatNumber(entity.getRoundsLeft()));

            row++;
        }
    }

    private String formatNumber(Integer number) {
        return (number == null)? "" : number.toString();
    }

    private void wireTogetherVisualElements() {
//        private VerticalPanel mainPanel = new VerticalPanel();
//        private HorizontalPanel topRowPanel = new HorizontalPanel();
//        private FlexTable initListTable = new FlexTable();
//        private VerticalPanel buttonBox = new VerticalPanel();

        topRowPanel.add(initListTable);
        topRowPanel.add(buttonBox);

        mainPanel.add(topRowPanel);

        RootPanel.get("mainPanel").add(mainPanel);
    }

    private void setInitListTableHeadings() {
        initListTable.setText(0, COLUMN_ABBREV, "##");
        initListTable.setText(0, COLUMN_NAME, "Name");
        initListTable.setText(0, COLUMN_INIT, "Init");
        initListTable.setText(0, COLUMN_HP, "HP");
        initListTable.setText(0, COLUMN_SUB, "Sub");
        initListTable.setText(0, COLUMN_ROUNDS, "Rounds");
    }
}
