package com.ziroby.dmassist.gwt.client;

import com.google.gwt.core.client.EntryPoint;
import com.google.gwt.core.client.GWT;
import com.google.gwt.event.dom.client.ClickEvent;
import com.google.gwt.event.dom.client.ClickHandler;
import com.google.gwt.user.client.Timer;
import com.google.gwt.user.client.rpc.AsyncCallback;
import com.google.gwt.user.client.ui.Anchor;
import com.google.gwt.user.client.ui.Button;
import com.google.gwt.user.client.ui.DialogBox;
import com.google.gwt.user.client.ui.FlexTable;
import com.google.gwt.user.client.ui.FlowPanel;
import com.google.gwt.user.client.ui.HorizontalPanel;
import com.google.gwt.user.client.ui.Label;
import com.google.gwt.user.client.ui.Panel;
import com.google.gwt.user.client.ui.RootPanel;
import com.google.gwt.user.client.ui.VerticalPanel;
import com.google.gwt.user.client.ui.Widget;
import com.ziroby.dmassist.gwtable.model.Entity;
import com.ziroby.dmassist.gwtable.model.EntityList;
import com.ziroby.dmassist.gwtable.model.EntityListGwtable;
import com.ziroby.dmassist.gwtable.util.Listener;
import com.ziroby.dmassist.gwtable.util.ObjectEvent;

/**
 * Entry point classes define <code>onModuleLoad()</code>.
 */
public class MainPanel implements EntryPoint
{
    private static final int SCHEDULE_REPEAT_MS = 5 * 1000;
    VerticalPanel mainPanel = new VerticalPanel();
    private HorizontalPanel topRowPanel = new HorizontalPanel();
    private FlexTable initListTable = new FlexTable();
    private VerticalPanel buttonBox = new VerticalPanel();

    EntityList entityList = new EntityListGwtable();

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

    final InitListServiceAsync initListService =
        GWT.create(InitListService.class);

    DialogBox addBox;
    private Widget initCountBox;
    private FlexTable statusBar;
    private Panel footer;

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

        initCountBox = createInitCount();

        createStatusBar();

        createFooter();

        wireTogetherVisualElements();

        registerCallbacks();

        displayEntityList();

        RootPanel.get("splash").setStyleName("hidden");
    }

    private void registerCallbacks() {
        Timer timer = new Timer() {
            public void run() {
                getInitCountFromServer();
            }
        };
        timer.scheduleRepeating(SCHEDULE_REPEAT_MS);
        getInitCountFromServer();
    }

    void getInitCountFromServer() {
        initListService.getInitCount(new AsyncCallback<Integer>() {
            public void onSuccess(Integer result) {
                entityList.setInitCount(result);
            }
            public void onFailure(Throwable caught) {
                // TODO: display an error
                //entityList.setInitCount(-555);
            }
        });
        initListService.getNumRounds(new AsyncCallback<Integer>() {
            public void onSuccess(Integer result) {
                entityList.setNumRounds(result);
            }
            public void onFailure(Throwable caught) {
                // TODO Auto-generated method stub

            }
        });
    }

    private void createFooter() {
        footer = new HorizontalPanel();

        Anchor aboutLink = new Anchor("About");
        aboutLink.setStyleName("hyperlink");
        aboutLink.addClickHandler(new ClickHandler() {
            public void onClick(ClickEvent event) {
                displayAboutBox();
            }
        });

        footer.add(aboutLink);
        Widget gplLink = new Anchor("GPL", "http://www.gnu.org/licenses/gpl.html");
        gplLink.setStyleName("hyperlink");
        footer.add(gplLink);
        Widget oglLink = new Anchor("OGL", "http://www.opengamingfoundation.org/ogl.html");
        oglLink.setStyleName("hyperlink");
        footer.add(oglLink);

        footer.setStyleName("footer");


    }

    protected void displayAboutBox() {
        AboutBox box = new AboutBox();
        int left = mainPanel.getAbsoluteLeft();
        int top = mainPanel.getAbsoluteTop() + 10;
        box.setPopupPosition(left, top);
        box.show();
    }

    private void createStatusBar() {
        statusBar = new FlexTable();

        int column = 0;
        final Label timeWidget = new Label("00:00");
        statusBar.setWidget(0, column++, timeWidget);
        final Label roundWidget = new Label("round 0");
        statusBar.setWidget(0, column++, roundWidget);

        for (int i=0; i<column; ++i)
            statusBar.getCellFormatter().addStyleName(0, i, "statusElement");

        entityList.addListener(new Listener() {
            public void objectChanged(ObjectEvent event) {
                timeWidget.setText(entityList.formatRoundsAsTime());
            }
        });

        entityList.addListener(new Listener() {
            public void objectChanged(ObjectEvent event) {
                roundWidget.setText("round " + entityList.getNumRounds());
            }
        });


        statusBar.setStyleName("statusBar");
    }

    private void createButtonBox() {

        Button addButton = new Button("Add");
        Button effectButton = new Button("Effect");
        //Button removeButton = new Button("Remove");
        Button nextButton = new Button("Next");

        createButtonHandlers(addButton, effectButton, nextButton);

        addButton.setStyleName("rightSideButton");
        effectButton.setStyleName("rightSideButton");
        nextButton.setStyleName("rightSideButton");

        buttonBox.add(addButton);
        buttonBox.add(effectButton);
        //buttonBox.add(removeButton);
        buttonBox.add(nextButton);

        buttonBox.setStyleName("buttonBox");
    }

    private Widget createInitCount() {
        Panel panel = new FlowPanel();

        Widget label = new Label("Init Count");
        panel.add(label);

        final Label initCountLabel = new Label("-");
        initCountLabel.setStyleName("initBox");
        initCountLabel.setWidth("3em");
        panel.add(initCountLabel);

        label.setStyleName("initLabel");
        initCountLabel.setStyleName("initBox");
        panel.setStyleName("initPanel");

        entityList.addListener(new Listener() {
            public void objectChanged(ObjectEvent event) {
                Integer initCount = entityList.getInitCount();
                initCountLabel.setText(
                        (initCount == null)? "-"
                                : initCount.toString());
            }
        });

        return panel;
    }

    private void createButtonHandlers(Button addButton, Button effectButton,
            Button nextButton) {
        nextButton.addClickHandler(new ClickHandler() {
            public void onClick(ClickEvent event) {
                entityList.gotoNextInitCount();
                initListService.setInitCount(entityList.getInitCount(), new AsyncCallback<Void>() {
                    public void onSuccess(Void result) {
                        // Do nothing
                        // entityList.setInitCount(null);
                    }
                    public void onFailure(Throwable caught) {
                        // TODO: We should log an error
                        //entityList.setInitCount(null);
                    }
                });
                initListService.setNumRounds(entityList.getNumRounds(), new AsyncCallback<Void>() {
                    public void onFailure(Throwable caught) {
                        // Do nothing
                    }
                    public void onSuccess(Void result) {
                        // TODO: log an error
                    }
                });
            }
        });
        addButton.addClickHandler(new ClickHandler() {
            public void onClick(ClickEvent event) {
                makeAddDialog(false);
                addBox.show();
            }
        });
        effectButton.addClickHandler(new ClickHandler() {
            public void onClick(ClickEvent event) {
                makeAddDialog(true);
                addBox.show();
            }
        });
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
            final String styleName = isItsTurn(entity) ? "myTurn" : "notMyTurn";

            initListTable.getRowFormatter().setStyleName(row, styleName);

            initListTable.setText(row, COLUMN_ABBREV, entity.getAbbreviation());
            initListTable.setText(row, COLUMN_NAME, entity.getName());
            initListTable.setText(row, COLUMN_INIT, formatNumber(entity.getInitRoll()));
            final Integer hitpoints = entity.getHitpoints();
            setCell(row, COLUMN_HP, hitpoints);
            final Integer subdual = entity.getSubdual();
            final boolean shouldHighlightSubdual
                = subdual != null && hitpoints != null && subdual >= hitpoints;
            setCell(row, COLUMN_SUB, subdual, shouldHighlightSubdual);
            setCell(row, COLUMN_ROUNDS, entity.getRoundsLeft());

            setInitTableFormatters(row);

            row++;
        }
    }

    private void setCell(int row, final int column, final Integer number) {
        final boolean shouldHighlight = number != null && number <= 0;
        setCell(row, column, number, shouldHighlight);
    }

    private void setCell(int row, final int column, final Integer number,
            final boolean shouldHighlight) {
        final Label roundLabel = new Label(formatNumber(number));
        initListTable.setWidget(row, column, roundLabel);

        if (shouldHighlight)
            roundLabel.setStyleName("nonpositive");
    }

    private boolean isItsTurn(Entity entity) {
        return entity.getInitRoll() == entityList.getInitCount()
                && entityList.getInitCount() != null;
    }

    private String formatNumber(Integer number) {
        return (number == null)? "" : number.toString();
    }

    private void wireTogetherVisualElements() {
        topRowPanel.add(initListTable);
        topRowPanel.add(buttonBox);

        topRowPanel.setSpacing(20);

        mainPanel.setStyleName("mainPanel");
        mainPanel.add(initCountBox);
        mainPanel.add(topRowPanel);
        mainPanel.add(statusBar);
        mainPanel.add(footer);

        RootPanel.get("mainPanel").add(mainPanel);
    }

    void makeAddDialog(boolean effect) {
        Panel dialogPanel = new FlowPanel();
        addBox = new AddDialogBox(entityList, effect);
        int left = mainPanel.getAbsoluteLeft() + 50;
        int top = mainPanel.getAbsoluteTop() + 10;
        addBox.setPopupPosition(left, top);
        dialogPanel.add(addBox);
        dialogPanel.setStyleName("mainPanel");
        RootPanel.get("popupArea").add(dialogPanel);
    }

}
