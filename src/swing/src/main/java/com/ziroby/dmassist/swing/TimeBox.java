/*
 * Copyright 2009 Ron "Ziroby" Romero
 *
 * This file is part of DM Assist.
 *
 * DM Assist is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option) any later
 * version.
 *
 * DM Assist is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE. See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * DM Assist. If not, see <http://www.gnu.org/licenses/>.
 *
 */

package com.ziroby.dmassist.swing;

import java.awt.Component;
import java.awt.Font;
import java.awt.Insets;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;

import javax.swing.BorderFactory;
import javax.swing.JButton;
import javax.swing.JLabel;

import com.ziroby.dmassist.gwtable.util.Listener;
import com.ziroby.dmassist.gwtable.util.ObjectEvent;

/**
 * A box that displays the current "time" in the battle.
 *
 * @author Ron Romero
 *
 */
public class TimeBox extends StatusBar implements Listener
{

    private static final int BUTTON_FONT_SIZE = 12;

    EntityDataModel dataModel;

    private JLabel time;

    //int numRounds = 0;

    private JLabel rounds;

    public TimeBox(EntityDataModel dataModel2)
    {
        this.dataModel = dataModel2;

        setFont(new Font("Serif", Font.BOLD, 24)); //$NON-NLS-1$

        this.time = new JLabel();
        time.setBorder(BorderFactory.createEtchedBorder());
        resetButton = new JButton(Messages.getString("TimeBox.RESET")); //$NON-NLS-1$
        resetButton.setFont(new Font("Serif", Font.BOLD, BUTTON_FONT_SIZE)); //$NON-NLS-1$
//        resetButton.setAlignmentY(Component.TOP_ALIGNMENT);
        resetButton.setMnemonic(KeyEvent.VK_R);
        resetButton.addActionListener(new ActionListener() {

            public void actionPerformed(ActionEvent arg0) {
                dataModel.resetNumRounds();
                display();
            }

        });
        Insets insets = resetButton.getMargin();
        Insets newInsets = new Insets(insets.top / 3, insets.left / 3,
                insets.bottom / 3, insets.right / 3);
        resetButton.setMargin(newInsets);

        nextButton = new JButton(Messages.getString("TimeBox.NEXT")); //$NON-NLS-1$
        nextButton.setFont(new Font("Serif", Font.BOLD, BUTTON_FONT_SIZE)); //$NON-NLS-1$
        nextButton.setAlignmentY(Component.TOP_ALIGNMENT);
        nextButton.setMnemonic(KeyEvent.VK_N);
        nextButton.addActionListener(new ActionListener() {

            public void actionPerformed(ActionEvent arg0) {
                dataModel.gotoNextInitCount();
            }

        });
        nextButton.setMargin(newInsets);

//        buttonBox.add(nextButton);
//        buttonBox.add(resetButton);

        this.rounds = new JLabel();
        rounds.setBorder(BorderFactory.createEtchedBorder());
        time.setAlignmentX(Component.RIGHT_ALIGNMENT);

//        timeBox.add(time);
//        timeBox.add(Box.createVerticalStrut(2));
//        timeBox.add(roundsBox);
        // timeBox.add(resetButton);

        addLabel(time);
        addLabel(rounds);
        add(resetButton);
        addGlue();
        // add(resetButton);
        // add(nextButton);

        display();
        dataModel.getInitCount();
        dataModel.addListener(this);

    }

    void display() {
        int numRounds = dataModel.getNumRounds();

        time.setText(dataModel.formatRoundsAsTime());
        rounds.setText(Messages.getString("TimeBox.ROUND") + numRounds); //$NON-NLS-1$

        nextButton.setEnabled(dataModel.getEntities().size() > 1);
        resetButton.setEnabled(numRounds != 0 || dataModel.getInitCount() != null);
    }

    /**
     *
     */
    private static final long serialVersionUID = 2101807777010560792L;

    private JButton resetButton;

    private JButton nextButton;

    public void objectChanged(ObjectEvent event) {
        display();
    }
}
