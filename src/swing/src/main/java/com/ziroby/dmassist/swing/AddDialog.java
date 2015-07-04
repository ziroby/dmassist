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
package com.ziroby.dmassist.swing;

import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.Insets;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;

import javax.swing.Box;
import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JComponent;
import javax.swing.JDialog;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JTextField;
import javax.swing.WindowConstants;

import com.ziroby.dmassist.gwtable.model.Entity;
import com.ziroby.dmassist.gwtable.model.EntityList;
import com.ziroby.dmassist.gwtable.model.Entity.EntityType;
import com.ziroby.dmassist.model.DiceEquation;

/**
 * @author Ron Romero
 *
 */
public class AddDialog extends JDialog implements ActionListener {

    private static final String DIALOG_TITLE_CREATURE = Messages.getString("AddDialog.dialogTitleAddCreature"); //$NON-NLS-1$
    private static final String DIALOG_TITLE_EFFECT = Messages.getString("AddDialog.dialogTitleAddEffect"); //$NON-NLS-1$

    private static final String TITLE_TEXT_CREATURE = Messages.getString("AddDialog.HeadingAddCreature"); //$NON-NLS-1$
    private static final String TITLE_TEXT_EFFECT = Messages.getString("AddDialog.HeadingAddEffect"); //$NON-NLS-1$

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
    private JComboBox typeField;

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
        addField(nameField, 30, Messages.getString("AddDialog.promptName"), KeyEvent.VK_N); //$NON-NLS-1$

        if (this.initCount == null)
		{
            initRollField = new JTextField();
            addField(initRollField, 4, Messages.getString("AddDialog.promptInitRoll"), KeyEvent.VK_I); //$NON-NLS-1$
		}

        this.hpField = new JTextField();
        addField(hpField, 4, Messages.getString("AddDialog.promptHitPoints"), KeyEvent.VK_H); //$NON-NLS-1$
        abrevField = new JTextField();
        addField(abrevField, 4, Messages.getString("AddDialog.promptsAbbrev"), KeyEvent.VK_A); //$NON-NLS-1$

        if (addType == AddType.EFFECT)
        {
            roundsField = new JTextField();
            addField(roundsField, 4, Messages.getString("AddDialog.promptRounds"), KeyEvent.VK_R); //$NON-NLS-1$
        }

        subdualField = new JTextField();
        addField(subdualField, 4, Messages.getString("AddDialog.promptSubdual"), KeyEvent.VK_S); //$NON-NLS-1$

        typeField = new JComboBox();
        for (EntityType entityType : EntityType.values())
            typeField.addItem(entityType);
        addField(typeField, Messages.getString("AddDialog.promptType"), KeyEvent.VK_T);

		Box buttonBox = Box.createHorizontalBox();
		JButton okButton = new JButton(Messages.getString("AddDialog.buttonLabelOK")); //$NON-NLS-1$
		okButton.setActionCommand("ok"); //$NON-NLS-1$
		okButton.addActionListener(this);
		JButton cancelButton = new JButton(Messages.getString("AddDialog.buttonLabelCancel")); //$NON-NLS-1$
		cancelButton.setActionCommand("cancel"); //$NON-NLS-1$
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
        field.setColumns(columns);
        addField(field, label, mnemonic);
    }

    private void addField(final JComponent field, final String label,
            final int mnemonic) {
        JLabel jlabel = new JLabel(label);
        jlabel.setLabelFor(field);
        jlabel.setDisplayedMnemonic(mnemonic);

        final JComponent contentPane1 = (JComponent) this.getContentPane();
        c1.gridx=0;
        c1.gridy=rowNum;
        contentPane1.add(jlabel, c1);
        c2.gridx=1;
        c2.gridy=rowNum++;
        contentPane1.add(field, c2);
    }

	public void actionPerformed(ActionEvent e) {
		if ("ok".equalsIgnoreCase(e.getActionCommand())) //$NON-NLS-1$
		{
			try
			{
				Entity entity = new Entity();
				entity.setName(this.nameField.getText());
				entity.setHitpoints(DiceEquation.tryParseInt(this.hpField.getText()));
				entity.setSubdual(DiceEquation.tryParseInt(this.subdualField.getText()));
				entity.setEntityType((EntityType) this.typeField.getSelectedItem());
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
				JOptionPane.showMessageDialog(this, exception.getMessage(), Messages.getString("AddDialog.windowTitleErrorInData"), JOptionPane.ERROR_MESSAGE); //$NON-NLS-1$
			}
		}
		else if ("cancel".equalsIgnoreCase(e.getActionCommand())) //$NON-NLS-1$
		{
			dispose();
		}
		else
		{
			JOptionPane.showMessageDialog(this, Messages.getString("AddDialog.errorUnknownActionType") + e.getActionCommand() + "\"" , Messages.getString("AddDialog.windowTitleInternalError"), JOptionPane.ERROR_MESSAGE); //$NON-NLS-1$ //$NON-NLS-2$ //$NON-NLS-3$
		}
	}

    private static final long serialVersionUID = 3758512305033825791L;
    private int rowNum = 0;
    private final GridBagConstraints c0 = new GridBagConstraints();
    private final GridBagConstraints c1 = new GridBagConstraints();
    private final GridBagConstraints c2 = new GridBagConstraints();

}
