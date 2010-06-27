package com.ziroby.dmassist.gwt.client;

import com.google.gwt.event.dom.client.ClickEvent;
import com.google.gwt.event.dom.client.ClickHandler;
import com.google.gwt.user.client.ui.Button;
import com.google.gwt.user.client.ui.DialogBox;
import com.google.gwt.user.client.ui.FlexTable;
import com.google.gwt.user.client.ui.FlowPanel;
import com.google.gwt.user.client.ui.Label;
import com.google.gwt.user.client.ui.Panel;
import com.google.gwt.user.client.ui.TextBox;
import com.google.gwt.user.client.ui.Widget;
import com.ziroby.dmassist.gwtable.model.Entity;
import com.ziroby.dmassist.gwtable.model.EntityList;

public class AddDialogBox extends DialogBox
{
    private FlexTable table;
    private int rowNum;
    private TextBox nameInput;
    private TextBox initInput;
    private TextBox hpInput;
    private TextBox abbrevInput;
    private TextBox subdualInput;
    private EntityList entityList;
    private TextBox roundsInput;

    public AddDialogBox(EntityList entityList, boolean effect)
    {
        super(true /*autohide*/);
        this.entityList = entityList;
        setText("Add a Creature");

        Panel panel = new FlowPanel();

        table = new FlexTable();
        rowNum = 0;

        nameInput = addInputRow("Name: ");
        initInput = addInputRow("Initiative Roll: ");
        hpInput = addInputRow("Hit Points: ");
        abbrevInput = addInputRow("Abbreviation: ");
        if (effect)
            roundsInput = addInputRow("Rounds: ");
        subdualInput = addInputRow("Subdual: ");

        panel.add(table);

        Button addButton = new Button("Add");
        addButton.addClickHandler(new ClickHandler() {

            @Override
            public void onClick(ClickEvent event) {
                doAdd();
                hide();
            }
        });
        panel.add(addButton);
        setWidget(panel);
    }

    protected void doAdd() {
        Entity entity = new Entity();

        entity.setName(nameInput.getText());
        entity.setAbbreviation(abbrevInput.getText());
        entity.setHitpoints(hpInput.getText());
        entity.setInitRoll(initInput.getText());
        entity.setSubdual(subdualInput.getText());
        if (roundsInput != null && roundsInput.getText() != null)
            entity.setRoundsLeft(roundsInput.getText());

        entityList.addEntity(entity);
    }

    private TextBox addInputRow(final String labelName) {
        Widget label = new Label(labelName);
        table.setWidget(rowNum, 0, label);
        TextBox input = new TextBox();
        table.setWidget(rowNum, 1, input);

        rowNum++;

        return input;
    }
}
