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

import java.awt.Dimension;
import java.awt.LayoutManager;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.io.IOException;

import javax.swing.BoxLayout;
import javax.swing.JButton;
import javax.swing.JEditorPane;
import javax.swing.JFrame;
import javax.swing.JScrollPane;

/**
 * @author Ron Romero
 *
 */
public class LicenseBox extends JFrame implements ActionListener
{
    public LicenseBox(final String filename)
    {
        final JEditorPane licenseInfo = new JEditorPane();
        licenseInfo.setEditable(false);
        LayoutManager layout = new BoxLayout(getContentPane(), BoxLayout.PAGE_AXIS);
        getContentPane().setLayout(layout);
        
        try
        {
            licenseInfo.setPage(filename);
        }
        catch (IOException e)
        {
            licenseInfo.setText("Could not find license file: " + e.getMessage());
//            getContentPane().add(new JLabel("Could not find license file: " + e.getMessage()));
            e.printStackTrace();
        }

        final JScrollPane scrollPane = new JScrollPane(licenseInfo);
        scrollPane.addKeyListener(new KeyAdapter() {
            @Override
            public void keyReleased(KeyEvent e) {
                if (e.getKeyCode() == KeyEvent.VK_ESCAPE || 
                        e.getKeyCode() == KeyEvent.VK_ENTER ||
                        e.getKeyCode() == KeyEvent.VK_SPACE)
                {
                    closeWindow();
                }
                super.keyReleased(e);
            }
        });
        getContentPane().add(scrollPane);
        
        final JButton ok = new JButton("OK");
        ok.addActionListener(this);
        this.addWindowFocusListener(new WindowAdapter() {
            @Override
            public void windowGainedFocus(WindowEvent e) {
                licenseInfo.requestFocusInWindow();
            }
        });

        getContentPane().add(ok);
        setPreferredSize(new Dimension(650,500));
        setMinimumSize(new Dimension(200,200));
        pack();
    }

    /**
     * 
     */
    private static final long serialVersionUID = -4674936870755546018L;

    public void actionPerformed(ActionEvent arg0) {
        closeWindow();        
    }

    void closeWindow() {
        this.setVisible(false);
        this.dispose();
    }
    
}
