/*
 *   Copyright 2009 Ron "Ziroby" Romero
 * 
 *   This file is part of DM Assist.
 *
 *   DM Assist is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   DM Assist is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with DM Assist.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
package com.ziroby.dmassist.ui;

import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.Insets;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;

import javax.swing.Box;
import javax.swing.JButton;
import javax.swing.JComponent;
import javax.swing.JDialog;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JTextField;
import javax.swing.WindowConstants;

import com.ziroby.dmassist.model.DiceEquation;
import com.ziroby.dmassist.model.Entity;
import com.ziroby.dmassist.model.EntityList;

/**
 * @author Ziroby
 *
 */
public class AddDialog extends JDialog implements ActionListener {

    private static final String DIALOG_TITLE_CREATURE = "Add Creature";
    private static final String DIALOG_TITLE_EFFECT = "Add Effect";

    private static final String TITLE_TEXT_CREATURE = "<html><h3>Add a Creature</h3></html>";
    private static final String TITLE_TEXT_EFFECT = "<html><h3>Add an Effect</h3></html>";

    enum AddType
    {
        CREATURE,
        EFFECT
    }
    
	private JTextField nameField;

	private JTextField initRollField;

	private JTextField hpField;

	private JTextField subdualField;

	private JTextField abrevField;

	private EntityList initOrderDataModel;
    private JTextField roundsField;
    private Integer initCount;
	
    public AddDialog(InitOrderFrame frame,
            EntityList initOrderDataModel, AddType addType, Integer initCount)
    {
        super(frame, addType == AddType.CREATURE? DIALOG_TITLE_CREATURE : DIALOG_TITLE_EFFECT, true);
        
        this.initOrderDataModel = initOrderDataModel;
        
        setupDialog(addType, initCount);
    }

    public AddDialog(InitOrderFrame frame,
            EntityList initOrderDataModel, AddType addType)
    {
        super(frame, addType == AddType.CREATURE? DIALOG_TITLE_CREATURE : DIALOG_TITLE_EFFECT, true);
        
        this.initOrderDataModel = initOrderDataModel;
        
        setupDialog(addType, null);
    }

    private void setupDialog(AddType addType, Integer initCount) {
        this.initCount = initCount;

        this.setDefaultCloseOperation(WindowConstants.DISPOSE_ON_CLOSE);
		
	    final JComponent contentPane = (JComponent) this.getContentPane();

	    contentPane.setLayout(new GridBagLayout());
		
        c0.anchor = GridBagConstraints.PAGE_START;
		c0.insets = new Insets(10, 10, 10, 10);
		c0.gridwidth = 2;

		c1.anchor = GridBagConstraints.FIRST_LINE_END;
		c1.insets = new Insets(5, 5, 5, 5);

		c2.anchor = GridBagConstraints.FIRST_LINE_START;
		c2.insets = new Insets(5, 5, 5, 5);

		JLabel titleField = new JLabel(addType == AddType.CREATURE? TITLE_TEXT_CREATURE : TITLE_TEXT_EFFECT);
		c0.gridx=0;
		c0.gridy=rowNum++;
		Insets oldInsets = c0.insets;
		c0.insets = new Insets(0, 0, 0, 0);
		contentPane.add(titleField, c0);
		c0.insets = oldInsets;

        nameField = new JTextField();
        addField(nameField, 30, "Name:", KeyEvent.VK_N);

        if (this.initCount == null)
		{
            initRollField = new JTextField();
            addField(initRollField, 4, "Initiative Roll:", KeyEvent.VK_I);
		}

        this.hpField = new JTextField();
        addField(hpField, 4, "Hit Points:", KeyEvent.VK_H);
        abrevField = new JTextField();
        addField(abrevField, 4, "Abreviation:", KeyEvent.VK_A);

        if (addType == AddType.EFFECT)
        {
            roundsField = new JTextField();
            addField(roundsField, 4, "Rounds:", KeyEvent.VK_R);
        }
        
        subdualField = new JTextField();
        addField(subdualField, 4, "Subdual:", KeyEvent.VK_S);
		
		Box buttonBox = Box.createHorizontalBox();
		JButton okButton = new JButton("OK");
		okButton.setActionCommand("ok");
		okButton.addActionListener(this);
		JButton cancelButton = new JButton("Cancel");
		cancelButton.setActionCommand("cancel");
		cancelButton.addActionListener(this);

		buttonBox.add(okButton);
		buttonBox.add(Box.createHorizontalStrut(10));
		buttonBox.add(cancelButton);
		
		c0.gridx=0;
		c0.gridy=rowNum++;
		contentPane.add(buttonBox, c0);
		
		getRootPane().setDefaultButton(okButton);
		
		pack();
    }

    private void addField(final JTextField field, final int columns, final String label, final int mnemonic) {
        final JComponent contentPane1 = (JComponent) this.getContentPane();

        field.setColumns(columns);
        JLabel jlabel = new JLabel(label);
        jlabel.setLabelFor(field);
        jlabel.setDisplayedMnemonic(mnemonic);

        c1.gridx=0;
        c1.gridy=rowNum;
        contentPane1.add(jlabel, c1);
        c2.gridx=1;
        c2.gridy=rowNum++;
        contentPane1.add(field, c2);
    }

	public void actionPerformed(ActionEvent e) {
		if ("ok".equalsIgnoreCase(e.getActionCommand()))
		{
			try
			{
				Entity entity = new Entity();
				entity.setName(this.nameField.getText());
				entity.setHitpoints(DiceEquation.tryParseInt(this.hpField.getText()));
				entity.setSubdual(DiceEquation.tryParseInt(this.subdualField.getText()));
				entity.setAbbreviation(this.abrevField.getText());
				if (this.roundsField != null)
				{
					entity.setRoundsLeft(DiceEquation.tryParseInt(this.roundsField.getText()));
				}

                if (this.initCount != null)
                {
                    entity.setInitRoll(initCount);
                }
                else
                {
                    entity.setInitRoll(DiceEquation.tryParseInt(this.initRollField.getText()));
                }

				this.initOrderDataModel.addEntity(entity);			
				dispose();
			}
			catch (RuntimeException exception)
			{
				exception.printStackTrace();
				JOptionPane.showMessageDialog(this, exception.getMessage(), "Error in data", JOptionPane.ERROR_MESSAGE);
			}
		}
		else if ("cancel".equalsIgnoreCase(e.getActionCommand()))
		{
			dispose();
		}
		else
		{
			JOptionPane.showMessageDialog(this, "Unknown action type: \"" + e.getActionCommand() + "\"" , "Internal Error", JOptionPane.ERROR_MESSAGE);
		}		
	}

    private static final long serialVersionUID = 3758512305033825791L;
    private int rowNum = 0;
    private final GridBagConstraints c0 = new GridBagConstraints();
    private final GridBagConstraints c1 = new GridBagConstraints();
    private final GridBagConstraints c2 = new GridBagConstraints();

}
