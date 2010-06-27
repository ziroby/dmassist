package com.ziroby.dmassist.gwt.client;

import com.google.gwt.core.client.EntryPoint;
import com.google.gwt.core.client.GWT;
import com.google.gwt.event.dom.client.ClickEvent;
import com.google.gwt.event.dom.client.ClickHandler;
import com.google.gwt.user.client.ui.Button;
import com.google.gwt.user.client.ui.DialogBox;
import com.google.gwt.user.client.ui.FlexTable;
import com.google.gwt.user.client.ui.FlowPanel;
import com.google.gwt.user.client.ui.HorizontalPanel;
import com.google.gwt.user.client.ui.Panel;
import com.google.gwt.user.client.ui.RootPanel;
import com.google.gwt.user.client.ui.VerticalPanel;
import com.ziroby.dmassist.gwtable.model.Entity;
import com.ziroby.dmassist.gwtable.model.EntityList;
import com.ziroby.dmassist.gwtable.model.EntityListGwtable;
import com.ziroby.dmassist.gwtable.util.Listener;
import com.ziroby.dmassist.gwtable.util.ObjectEvent;

/**
 * Entry point classes define <code>onModuleLoad()</code>.
 */
public class Dmassist_gwt implements EntryPoint
{
    VerticalPanel mainPanel = new VerticalPanel();
    private HorizontalPanel topRowPanel = new HorizontalPanel();
    private FlexTable initListTable = new FlexTable();
    private VerticalPanel buttonBox = new VerticalPanel();

    EntityList entityList = new EntityListGwtable();

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
    DialogBox addBox;

    /**
     * This is the entry point method.
     */
    public void onModuleLoad() {
        setupInitList();
        entityList.addListener(new Listener() {

            @Override
            public void objectChanged(ObjectEvent event) {
                displayEntityList();
            }
        });

        entityList.addSampleData();


        createButtonBox();

        wireTogetherVisualElements();

        displayEntityList();
    }

    private void createButtonBox() {
        Button addButton = new Button("Add");
        Button effectButton = new Button("Effect");
        //Button removeButton = new Button("Remove");
        Button nextButton = new Button("Next");

        nextButton.addClickHandler(new ClickHandler() {

            @Override
            public void onClick(ClickEvent event) {
                entityList.gotoNextInitCount();
            }
        });

        addButton.addClickHandler(new ClickHandler() {

            @Override
            public void onClick(ClickEvent event) {
                if (addBox == null) {
                    Panel dialogPanel = new FlowPanel();
                    addBox = new AddDialogBox(entityList);
                    int left = mainPanel.getAbsoluteLeft() + 50;
                    int top = mainPanel.getAbsoluteTop() + 10;
                    addBox.setPopupPosition(left, top);
                    dialogPanel.add(addBox);
                    dialogPanel.setStyleName("mainPanel");
                    RootPanel.get("popupArea").add(dialogPanel);
                }
                addBox.show();
            }
        });

        addButton.setStyleName("rightSideButton");
        effectButton.setStyleName("rightSideButton");
        nextButton.setStyleName("rightSideButton");

        buttonBox.add(addButton);
        buttonBox.add(effectButton);
        //buttonBox.add(removeButton);
        buttonBox.add(nextButton);

        buttonBox.setStyleName("buttonBox");
    }

    private void setupInitList() {
        initListTable.getRowFormatter().addStyleName(0, "initListHeader");
        initListTable.addStyleName("initList");

        initListTable.setText(0, COLUMN_ABBREV, "##");
        initListTable.setText(0, COLUMN_NAME, "Name");
        initListTable.setText(0, COLUMN_INIT, "Init");
        initListTable.setText(0, COLUMN_HP, "HP");
        initListTable.setText(0, COLUMN_SUB, "Sub");
        initListTable.setText(0, COLUMN_ROUNDS, "Rounds");

        setInitTableFormatters(0);
}

    private void setInitTableFormatters(final int row) {
        initListTable.getCellFormatter().addStyleName(row, COLUMN_ABBREV, "initColumn");
        initListTable.getCellFormatter().addStyleName(row, COLUMN_NAME, "initColumn");
        initListTable.getCellFormatter().addStyleName(row, COLUMN_INIT, "initColumn");
        initListTable.getCellFormatter().addStyleName(row, COLUMN_HP, "initColumn");
        initListTable.getCellFormatter().addStyleName(row, COLUMN_SUB, "initColumn");
        initListTable.getCellFormatter().addStyleName(row, COLUMN_ROUNDS, "initColumn");

        initListTable.setCellSpacing(0);
    }

    void displayEntityList() {

        initListTable.removeAllRows();
        setupInitList();

        int row=1;
        for (Entity entity : entityList.getEntities())
        {
            final String styleName;
            if (entity.getInitRoll() == entityList.getInitCount()
                    && entityList.getInitCount() != null)
                styleName = "myTurn";
            else
                styleName = "notMyTurn";

            initListTable.getRowFormatter().setStyleName(row, styleName);

            initListTable.setText(row, COLUMN_ABBREV, entity.getAbbreviation());
            initListTable.setText(row, COLUMN_NAME, entity.getName());
            initListTable.setText(row, COLUMN_INIT, formatNumber(entity.getInitRoll()));
            initListTable.setText(row, COLUMN_HP, formatNumber(entity.getHitpoints()));
            initListTable.setText(row, COLUMN_SUB, formatNumber(entity.getSubdual()));
            initListTable.setText(row, COLUMN_ROUNDS, formatNumber(entity.getRoundsLeft()));

            setInitTableFormatters(row);

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

        topRowPanel.setSpacing(20);

        mainPanel.setStyleName("mainPanel");
        mainPanel.add(topRowPanel);

        RootPanel.get("mainPanel").add(mainPanel);
    }

}
