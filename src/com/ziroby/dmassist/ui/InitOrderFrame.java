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

import java.awt.Component;
import java.awt.Dimension;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.Insets;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.io.File;
import java.io.FileNotFoundException;

import javax.swing.Box;
import javax.swing.BoxLayout;
import javax.swing.JButton;
import javax.swing.JComponent;
import javax.swing.JFileChooser;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JPopupMenu;
import javax.swing.JScrollPane;
import javax.swing.JSplitPane;
import javax.swing.JTable;
import javax.swing.JTextField;
import javax.swing.SwingConstants;
import javax.swing.table.TableCellRenderer;
import javax.swing.table.TableColumn;

import com.ziroby.dmassist.model.DiceEquation;
import com.ziroby.dmassist.model.Entity;
import com.ziroby.dmassist.model.EntityList;
import com.ziroby.dmassist.model.InitOrderDataModel;
import com.ziroby.dmassist.model.Entity.DamageType;
import com.ziroby.parser.Interpreter;
import com.ziroby.parser.Parser;

/**
 * @author Ziroby
 *
 */
public class InitOrderFrame extends JFrame 
	implements ActionListener {

	private static final long serialVersionUID = -833599596108997845L;
	private InitOrderDataModel dataModel;
	JTable table;
	private Interpreter interpreter;
	private Parser parser;
    JPopupMenu popup;
    private ResultsBox resultsBox;


	public InitOrderFrame() {
	    this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	    dataModel = new InitOrderDataModel();

	    createMenus();
	    
	    final JComponent contentPane1 = (JComponent) this.getContentPane();
	    
	    final JComponent upperPane = new JPanel();
	    final JComponent lowerPane = new JPanel();
	    
	    upperPane.setLayout(new GridBagLayout());
	    lowerPane.setLayout(new GridBagLayout());
	    
        Box titleBox = Box.createHorizontalBox();
        
	    JLabel title = new JLabel("<html><h1>DM&nbsp;Assist</h1></html>");
	    //title.setAlignmentX(Component.CENTER_ALIGNMENT);
        
        titleBox.add(Box.createHorizontalStrut(30));
        titleBox.add(title);
        titleBox.add(Box.createHorizontalStrut(10));
        JComponent timeBox = new TimeBox(dataModel);
        //titleBox.add(timeBox);
        
	    GridBagConstraints labelConstraints = new GridBagConstraints();
	    labelConstraints.gridx = 0;
	    labelConstraints.gridy = 0;
	    labelConstraints.weighty = 0;
        //labelConstraints.fill = GridBagConstraints.HORIZONTAL;
	    //labelConstraints.insets = new Insets(10, 10, 10, 10);
	    upperPane.add(title, labelConstraints);

	    Box countBox = Box.createVerticalBox();
	    
	    JLabel label2 = new JLabel("Init Count");
	    label2.setVerticalTextPosition(SwingConstants.BOTTOM);
	    //label2.setHorizontalTextPosition(SwingConstants.LEFT);
	    label2.setAlignmentX(Component.CENTER_ALIGNMENT);
	    
	    countBox.add(label2);

	    JLabel initCount = new InitCountLabel(dataModel);
	    //initCount.setHorizontalTextPosition(SwingConstants.CENTER);
	    countBox.add(Box.createVerticalStrut(5));
	    countBox.add(initCount);
	    
	    GridBagConstraints label2Constraints = new GridBagConstraints();
	    label2Constraints.gridx = 1;
	    label2Constraints.gridy = 0;
	    label2Constraints.insets = new Insets(5, 10, 10, 10);
	    label2Constraints.anchor = GridBagConstraints.CENTER;
	    label2Constraints.weighty = 0.0;
	    label2Constraints.fill = GridBagConstraints.BOTH;
	    upperPane.add(countBox, label2Constraints);

		addSampleData(dataModel);

        popup = new JPopupMenu();
        addMenuItem(popup, "Damage", KeyEvent.VK_D, "Damage");
        addMenuItem(popup, "Heal", KeyEvent.VK_H, "Heal");
        addMenuItem(popup, "Subdue", KeyEvent.VK_S, "Subdue");
        addMenuItem(popup, "Recover", KeyEvent.VK_R, "Recover");
        
        table = new JTable(dataModel);
		table.setAutoCreateRowSorter(true);
	    table.setPreferredScrollableViewportSize(new Dimension(500, 70));
        table.addMouseListener(new MouseAdapter () {
            public void mousePressed(MouseEvent e) {
                maybeShowPopup(e);
            }

            public void mouseReleased(MouseEvent e) {
                maybeShowPopup(e);
            }

            private void maybeShowPopup(MouseEvent e) {
                if (e.isPopupTrigger()) {
                    int col = table.columnAtPoint(e.getPoint());
                    int row = table.rowAtPoint(e.getPoint());
                    table.changeSelection(row, col, false, false);
                    popup.show(e.getComponent(),
                               e.getX(), e.getY());
                }
            }
        });
	    setupTable(table);
	    
	    // table.setAutoResizeMode(JTable.AUTO_RESIZE_ALL_COLUMNS);
	    JScrollPane InitOrderPane = new JScrollPane(table); 
	    InitOrderPane.setMinimumSize(new Dimension(30,30));
	    // 	table.setFillsViewportHeight(true);
	    
	    GridBagConstraints tableContraints = new GridBagConstraints();
	    tableContraints.gridx = 0;
	    tableContraints.gridy = 1;
	    tableContraints.weightx = 1.0;
	    tableContraints.weighty = 1.0;
	    tableContraints.fill = GridBagConstraints.BOTH;
	    tableContraints.anchor = GridBagConstraints.FIRST_LINE_START;
	    upperPane.add(InitOrderPane, tableContraints);
	    
	    Box box2 = new Box(BoxLayout.PAGE_AXIS);
	        
        JButton addButton = new JButton("Add");
        addButton.setMnemonic(KeyEvent.VK_A);
        addButton.setActionCommand("Add");
        addButton.addActionListener(this);
        box2.add(addButton);

        JButton effectButton = new JButton("Effect");
        effectButton.setMnemonic(KeyEvent.VK_E);
        effectButton.setActionCommand("effect");
        effectButton.addActionListener(this);
        box2.add(Box.createVerticalStrut(10));
        box2.add(effectButton);

	    JButton button2 = new RemoveButton(table);
	    button2.setMnemonic(KeyEvent.VK_R);
	    button2.setActionCommand("Remove");
	    button2.addActionListener(this);
        box2.add(Box.createVerticalStrut(10));
	    box2.add(button2);
	    
	    JButton nextButton = new NextButton(this.dataModel);
	    nextButton.setMnemonic(KeyEvent.VK_N);
	    nextButton.setActionCommand("Next");
	    nextButton.addActionListener(this);
	    box2.add(Box.createVerticalStrut(15));
        timeBox.setAlignmentX(Component.LEFT_ALIGNMENT);
	    box2.add(timeBox);
	    
//	    JButton button4 = new JButton("Button4");
//	    box2.add(Box.createVerticalStrut(10));
//	    box2.add(button4);
	    //box.add(Box.createVerticalGlue());

	    GridBagConstraints box1Constraints = new GridBagConstraints();
	    box1Constraints.gridx = 1;
	    box1Constraints.gridy = 1;
	    box1Constraints.insets = new Insets(0, 10, 10, 10);
	    box1Constraints.anchor = GridBagConstraints.PAGE_START;
	    box1Constraints.weighty = 0.0;
	    box1Constraints.fill = GridBagConstraints.VERTICAL;
	    upperPane.add(box2, box1Constraints);
	    
	    resultsBox = new ResultsBox();
        GridBagConstraints resultsConstraints = new GridBagConstraints();
	    resultsConstraints.gridx = 0;
	    resultsConstraints.gridy = 3;
	    resultsConstraints.gridwidth = 2;
	    resultsConstraints.insets = new Insets(10, 10, 10, 10);
	    resultsConstraints.fill = GridBagConstraints.BOTH;
	    resultsConstraints.weighty = 1;
	    resultsConstraints.weightx = 1;
	    resultsConstraints.ipady = 50;
	    lowerPane.add(resultsBox, resultsConstraints);
	    
	    JComponent resultsDisplay = resultsBox.getResultDisplay();
	    GridBagConstraints resultBoxConstraints = new GridBagConstraints();
	    resultBoxConstraints.gridx = 1;
	    resultBoxConstraints.gridy = 2;
	    resultBoxConstraints.insets = new Insets(10, 10, 10, 10);
	    resultBoxConstraints.fill = GridBagConstraints.CENTER;
	    lowerPane.add(resultsDisplay, resultBoxConstraints);
	    
	    // Hook up the command window
	    this.interpreter = new Interpreter(dataModel, resultsBox);
	    this.parser = new Parser(interpreter, resultsBox);

	    Box box1 = Box.createHorizontalBox();
	    
	    final JTextField commandLine = new CommandLine();
	    commandLine.addActionListener(this.parser);	    

	    //Make textField get the focus whenever frame is activated.
	    this.addWindowFocusListener(new WindowAdapter() {
	        @Override
			public void windowGainedFocus(WindowEvent e) {
	            commandLine.requestFocusInWindow();
	        }
	    });
	    
	    JLabel commandLabel = new JLabel("Command:");
	    commandLabel.setDisplayedMnemonic(KeyEvent.VK_C);
	    commandLabel.setLabelFor(commandLine);
	    
	    box1.add(commandLabel);
	    box1.add(Box.createHorizontalStrut(5));
	    box1.add(commandLine);
	    
	    GridBagConstraints text1Constraints = new GridBagConstraints();
	    text1Constraints.gridx = 0;
	    text1Constraints.gridy = 2;
	    text1Constraints.weightx = 1;
	    text1Constraints.insets = new Insets(10, 10, 10, 10);
	    text1Constraints.fill = GridBagConstraints.HORIZONTAL;
	    lowerPane.add(box1, text1Constraints);	    
	
	    JSplitPane splitPane = new JSplitPane(JSplitPane.VERTICAL_SPLIT);
	    splitPane.setOneTouchExpandable(true);
	    splitPane.setTopComponent(upperPane);
	    splitPane.setBottomComponent(lowerPane);
	    contentPane1.add(splitPane);
	    
	    this.setTitle("DM Assist");
	    
	    this.pack();
	}

    private void createMenus() {
		JMenuBar menubar = new JMenuBar();
		
		// File menu
		JMenu fileMenu = new JMenu("File");
		fileMenu.setMnemonic(KeyEvent.VK_F);
		menubar.add(fileMenu);	

		addMenuItem(fileMenu, "Clear", KeyEvent.VK_C, "Clear");
		addMenuItem(fileMenu, "Load...", KeyEvent.VK_L, "load");
//		addMenuItem(fileMenu, "Save", KeyEvent.VK_S, "save");
        addMenuItem(fileMenu, "Save As...", KeyEvent.VK_A, "saveas");
		fileMenu.addSeparator();
		addMenuItem(fileMenu, "Import...", KeyEvent.VK_I, "import");
		fileMenu.addSeparator();
		addMenuItem(fileMenu, "Quit", KeyEvent.VK_Q, "quit");
		
		//Help menu
		JMenu helpMenu = new JMenu("Help");
		helpMenu.setMnemonic(KeyEvent.VK_H);
		menubar.add(helpMenu);
		
		addMenuItem(helpMenu, "License...", KeyEvent.VK_L, "license");
		addMenuItem(helpMenu, "About DM Assist...", KeyEvent.VK_A, "About");
		
		setJMenuBar(menubar);
	}

	private void addMenuItem(JComponent menu, final String itemName, final int key, final String command) {
		JMenuItem item = new JMenuItem(itemName);
		item.setMnemonic(key);
		item.setActionCommand(command);
		item.addActionListener(this);
		menu.add(item);
	}

	/**
	 * Set up the stuff in the table.
	 * @param table
	 */
	private static void setupTable(JTable table) {
		final TableColumn numColumn = table.getColumnModel().getColumn(Entity.COLUMN_NUMBER_NUM);
		smartResizeColumn(numColumn);
		final TableColumn nameColumn = table.getColumnModel().getColumn(Entity.COLUMN_NUMBER_NAME);
		nameColumn.setMinWidth(75);
		nameColumn.setPreferredWidth(300);
		final TableColumn initColumn = table.getColumnModel().getColumn(Entity.COLUMN_NUMBER_INIT);
		smartResizeColumn(initColumn);
		initColumn.setMaxWidth(initColumn.getPreferredWidth());
		final TableColumn hpColumn = table.getColumnModel().getColumn(Entity.COLUMN_NUMBER_HP);
		smartResizeColumn(hpColumn);
        final TableColumn subdualColumn = table.getColumnModel().getColumn(Entity.COLUMN_NUMBER_SUBDUAL);
        smartResizeColumn(subdualColumn);
        final TableColumn roundsColumn = table.getColumnModel().getColumn(Entity.COLUMN_NUMBER_ROUNDS);
        smartResizeColumn(roundsColumn);
        final TableColumn myTurnColumn = table.getColumnModel().getColumn(Entity.COLUMN_NUMBER_MY_TURN);
        smartResizeColumn(myTurnColumn);
        myTurnColumn.setMaxWidth(initColumn.getMinWidth());
		
		final TableCellRenderer stringRenderer = table.getDefaultRenderer(String.class);
		table.setDefaultRenderer(String.class, new HighlightingTableCellRenderer(stringRenderer));

		final TableCellRenderer integerRenderer = table.getDefaultRenderer(Integer.class);
		table.setDefaultRenderer(Integer.class, new HighlightingTableCellRenderer(integerRenderer));

		final TableCellRenderer boolRenderer = table.getDefaultRenderer(Boolean.class);
		table.setDefaultRenderer(Boolean.class, new HighlightingTableCellRenderer(boolRenderer));
		
	}


	private static void smartResizeColumn(final TableColumn column) {
		column.sizeWidthToFit();
		column.setMaxWidth(column.getPreferredWidth());
		column.setPreferredWidth((int) (column.getPreferredWidth() * 0.7));
		column.setMinWidth((int) (column.getMinWidth() *  1.3));
	}


	private static void addSampleData(EntityList dataModel) {
		Entity row1 = new Entity();	
		row1.setAbbreviation("O");
		row1.setName("Ogre");
		row1.setInitRoll(12);
		row1.setHitpoints(25);
		dataModel.addEntity(row1);

		Entity row2 = new Entity();	
		row2.setAbbreviation("G1");
		row2.setName("Goblin 1");
		row2.setInitRoll(4);
		row2.setHitpoints(8);
		row2.setSubdual(3);
		dataModel.addEntity(row2);

        Entity row4 = new Entity();
        row4.setName("Melf's acid arrow");
        row4.setInitRoll(4);
        row4.setRoundsLeft(3);
        dataModel.addEntity(row4);
        
		Entity row3 = new Entity();	
		row3.setAbbreviation("G2");
		row3.setName("Goblin 2");
		row3.setInitRoll(15);
		row3.setHitpoints(3);
		dataModel.addEntity(row3);
	}

	@SuppressWarnings("unchecked")
	public void actionPerformed(ActionEvent e) {
        final String actionCommand = e.getActionCommand();
        if ("add".equalsIgnoreCase(actionCommand))
        {
            AddDialog addDialog = new AddDialog(this, this.dataModel, AddDialog.AddType.CREATURE);
            addDialog.setVisible(true);
        
        }
        else if ("effect".equalsIgnoreCase(actionCommand))
        {
            AddDialog addDialog = new AddDialog(this, this.dataModel, AddDialog.AddType.EFFECT, this.dataModel.getInitCount());
            addDialog.setVisible(true);
        
        }
        else if ("next".equalsIgnoreCase(actionCommand))
        {
        	dataModel.gotoNextInitCount();
        }
        else if ("remove".equalsIgnoreCase(actionCommand))
        {
        	removeSelected();
        }
        else if ("quit".equalsIgnoreCase(actionCommand))
        {
            this.setVisible(false);
            this.dispose();
        }
        else if ("about".equalsIgnoreCase(actionCommand))
        {
            AboutBox about = new AboutBox();
            about.setVisible(true);
        }
        else if ("license".equalsIgnoreCase(actionCommand))
        {
            JFrame license = new LicenseBox ();
            license.setVisible(true);
        }
        else if ("import".equalsIgnoreCase(actionCommand))
        {
        	importFile();
        }
        else if ("load".equalsIgnoreCase(actionCommand))
        {
        	if (clear())
        		importFile();
        }
        else if ("saveas".equalsIgnoreCase(actionCommand))
        {
        	saveAs();
        }
        else if ("clear".equalsIgnoreCase(actionCommand))
        {
            clear();
        }
        else if (Entity.stringToDamageType(actionCommand) != null)
        {
            damage(actionCommand);
        }
        else
        {
        	JOptionPane.showMessageDialog(this, "Unknown action type: \"" + actionCommand + "\"" , "Internal Error", JOptionPane.ERROR_MESSAGE);
        }
		
	}

    private void damage(final String actionCommand) {
        int row = table.getSelectedRow();
        int modelRow = table.convertRowIndexToModel(row);
        Entity entity = dataModel.getEntity(modelRow);

        DamageType type = Entity.stringToDamageType(actionCommand);
        final String damageTypeString = Entity.damageTypeToString(type);
        String message = damageTypeString + " " + entity.getName() + " by: ";
        DiceEquation damage = null;
        do
        { 
            String amount = JOptionPane.showInputDialog(this, message,
                    damageTypeString, JOptionPane.PLAIN_MESSAGE);
            if (amount == null) break;
            try
            {
                damage = new DiceEquation(amount);
            }
            catch (IllegalArgumentException e)
            {
                JOptionPane.showMessageDialog(this, "Invalid amount: " + e.getLocalizedMessage(), "Error",
                        JOptionPane.ERROR_MESSAGE);
            }

            if (amount.trim().length() == 0)
            {
                damage = null;
                break;
            }
        } while (damage == null);

        try
        {            
            if (damage != null)
            {
                entity.damage(type, damage.value());
                resultsBox.setResult("" + damage.value());
                resultsBox.addLine(Entity.damageTypeToString(type) + " \""
                        + entity.getName() + "\" by " + damage.toLongString());
            }

        }
        catch (Exception except)
        {
            JOptionPane.showMessageDialog(this, except.getMessage(), "Error",
                    JOptionPane.ERROR_MESSAGE);                
        }
    }

    /**
     * 
     */
    private void saveAs() {
		JFileChooser chooser = new JFileChooser();
		int retVal = chooser.showSaveDialog(this);
		if (retVal == JFileChooser.APPROVE_OPTION)
		{
			File file = chooser.getSelectedFile();
			
			try {
				dataModel.save(file);
			} catch (FileNotFoundException e1) {
				JOptionPane.showMessageDialog(this, "Error", "File not found: " + e1.getLocalizedMessage(), 
						JOptionPane.ERROR_MESSAGE);
				e1.printStackTrace();
			}
		}
	}

	/**
	 * 
	 */
	private void importFile() {
		JFileChooser chooser = new JFileChooser();
		chooser.setDialogTitle("Import");			
		int retVal = chooser.showOpenDialog(this);
		if (retVal == JFileChooser.APPROVE_OPTION)
		{
			File file = chooser.getSelectedFile();
			try {
				dataModel.importFile(file);
			} catch (FileNotFoundException e1) {
				JOptionPane.showMessageDialog(this, "Error", "File not found: " + e1.getLocalizedMessage(), JOptionPane.ERROR_MESSAGE);
				e1.printStackTrace();
			}
		}
	}

	/**
	 * Erases all entries.  Asks for confirmation first.
	 */
	private boolean clear() {
		int retVal = JOptionPane.showConfirmDialog(this, "This will delete the current entries.  Are you sure?", 
				"Confirm", JOptionPane.YES_NO_OPTION, JOptionPane.QUESTION_MESSAGE);
		if (retVal == JFileChooser.APPROVE_OPTION)
		{
			dataModel.clear();
			return true;
		}
		return false;
	}

	private void removeSelected() {
		int[] selectedRows = table.getSelectedRows();
		
		// Going backwards so we don't stomp on ourselves
		for (int i = selectedRows.length - 1;
			i >= 0;
			--i)
		{
			int modelIndex = table.convertRowIndexToModel(selectedRows[i]);
			dataModel.remove(modelIndex);
		}
		
	}	
}
