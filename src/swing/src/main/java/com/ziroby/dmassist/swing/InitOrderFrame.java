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

import java.awt.BorderLayout;
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
import javax.swing.DefaultCellEditor;
import javax.swing.JButton;
import javax.swing.JComboBox;
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

import com.ziroby.dmassist.gwtable.model.Entity;
import com.ziroby.dmassist.gwtable.model.EntityList;
import com.ziroby.dmassist.gwtable.model.EntityListGwtable;
import com.ziroby.dmassist.gwtable.model.Entity.DamageType;
import com.ziroby.dmassist.model.DiceEquation;
import com.ziroby.dmassist.parser.Interpreter;
import com.ziroby.dmassist.parser.Parser;

/**
 * The main visible frame.
 *
 * @author Ron Romero
 *
 */
public class InitOrderFrame extends JFrame
	implements ActionListener {

	private static final String ACTION_EXIT = "exit";
    private static final String ACTION_REMOVE = "remove";
    private static final String ACTION_NEXT = "next";
    private static final String ACTION_EFFECT = "effect";
    private static final String ACTION_ADD = "add";
    private static final String ACTION_ABOUT = "about";
    private static final String ACTION_OGL_LICENSE = "ogllicense";
    private static final String ACTION_LICENSE = "license";
    private static final String ACTION_QUIT = "quit";
    private static final String ACTION_IMPORT = "import";
    private static final String ACTION_SAVE_AS = "saveas";
    private static final String ACTION_LOAD = "load";
    private static final String ACTION_CLEAR = "clear";
    private static final String ACTION_RECOVER = "recover";
    private static final String ACTION_SUBDUE = "subdue";
    private static final String ACTION_HEAL = "heal";
    private static final String ACTION_DAMAGE = "damage";
    private static final long serialVersionUID = -833599596108997845L;
	private EntityDataModel dataModel;
	JTable table;
	private Interpreter interpreter;
	private Parser parser;
    JPopupMenu popup;
    private ResultsBox resultsBox;
    private final static String ABOUT_FILENAME = "file:resources/about.html"; //$NON-NLS-1$
    private final static String GPL_FILENAME = "file:resources/LICENSE.txt"; //$NON-NLS-1$
    private final static String OGL_FILENAME = "file:resources/OGL.txt"; //$NON-NLS-1$

    public InitOrderFrame() {
	    this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	    dataModel = new EntityDataModel();

	    createMenus();

	    this.getContentPane().setLayout(new BorderLayout());

	    final JComponent contentPane1 = new JPanel();

	    this.getContentPane().add(contentPane1, BorderLayout.CENTER);
	    this.getContentPane().add(new TimeBox(dataModel), BorderLayout.SOUTH);

	    final JComponent upperPane = new JPanel();
	    final JComponent lowerPane = new JPanel();

	    upperPane.setLayout(new GridBagLayout());
	    lowerPane.setLayout(new GridBagLayout());

	    JLabel title = new JLabel(Messages.getString("InitOrderFrame.heading")); //$NON-NLS-1$
	    //title.setAlignmentX(Component.CENTER_ALIGNMENT);

	    GridBagConstraints labelConstraints = new GridBagConstraints();
	    labelConstraints.gridx = 0;
	    labelConstraints.gridy = 0;
	    labelConstraints.weighty = 0;
        //labelConstraints.fill = GridBagConstraints.HORIZONTAL;
	    //labelConstraints.insets = new Insets(10, 10, 10, 10);
	    upperPane.add(title, labelConstraints);

	    Box countBox = Box.createVerticalBox();

	    JLabel label2 = new JLabel(Messages.getString("InitOrderFrame.initCount")); //$NON-NLS-1$
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
        addMenuItem(popup, Messages.getString("InitOrderFrame.damage"), KeyEvent.VK_D, ACTION_DAMAGE); //$NON-NLS-1$
        addMenuItem(popup, Messages.getString("InitOrderFrame.heal"), KeyEvent.VK_H, ACTION_HEAL); //$NON-NLS-1$
        addMenuItem(popup, Messages.getString("InitOrderFrame.subdueLabel"), KeyEvent.VK_S, ACTION_SUBDUE); //$NON-NLS-1$
        addMenuItem(popup, Messages.getString("InitOrderFrame.recoverLabel"), KeyEvent.VK_R, ACTION_RECOVER); //$NON-NLS-1$

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

        JButton addButton = new JButton(Messages.getString("InitOrderFrame.addLabel")); //$NON-NLS-1$
        addButton.setMnemonic(KeyEvent.VK_A);
        addButton.setActionCommand("Add"); //$NON-NLS-1$
        addButton.addActionListener(this);
        box2.add(addButton);

        JButton effectButton = new JButton(Messages.getString("InitOrderFrame.effectLabel")); //$NON-NLS-1$
        effectButton.setMnemonic(KeyEvent.VK_E);
        effectButton.setActionCommand(ACTION_EFFECT);
        effectButton.addActionListener(this);
        box2.add(Box.createVerticalStrut(10));
        box2.add(effectButton);

	    JButton button2 = new RemoveButton(table);
	    button2.setMnemonic(KeyEvent.VK_R);
	    button2.setActionCommand(ACTION_REMOVE);
	    button2.addActionListener(this);
        box2.add(Box.createVerticalStrut(10));
	    box2.add(button2);

	    JButton nextButton = new NextButton(this.dataModel);
	    nextButton.setMnemonic(KeyEvent.VK_N);
	    nextButton.setActionCommand(ACTION_NEXT);
	    nextButton.addActionListener(this);
	    box2.add(Box.createVerticalStrut(10));
	    box2.add(nextButton);

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

	    JLabel commandLabel = new JLabel(Messages.getString("InitOrderFrame.command")); //$NON-NLS-1$
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

	    this.setTitle(Messages.getString("InitOrderFrame.title")); //$NON-NLS-1$

	    this.pack();
	}

    private void createMenus() {
		JMenuBar menubar = new JMenuBar();

		// File menu
		JMenu fileMenu = new JMenu(Messages.getString("InitOrderFrame.fileMenuName")); //$NON-NLS-1$
		fileMenu.setMnemonic(KeyEvent.VK_F);
		menubar.add(fileMenu);

		addMenuItem(fileMenu, Messages.getString("InitOrderFrame.clearMenuName"), KeyEvent.VK_C, ACTION_CLEAR); //$NON-NLS-1$
		addMenuItem(fileMenu, Messages.getString("InitOrderFrame.loadMenu"), KeyEvent.VK_L, ACTION_LOAD); //$NON-NLS-1$
//		addMenuItem(fileMenu, "Save", KeyEvent.VK_S, "save");
        addMenuItem(fileMenu, Messages.getString("InitOrderFrame.saveAsMenu"), KeyEvent.VK_A, ACTION_SAVE_AS); //$NON-NLS-1$
		fileMenu.addSeparator();
		addMenuItem(fileMenu, Messages.getString("InitOrderFrame.importMenu"), KeyEvent.VK_I, ACTION_IMPORT); //$NON-NLS-1$
		fileMenu.addSeparator();
		addMenuItem(fileMenu, Messages.getString("InitOrderFrame.QuitMenuOption"), KeyEvent.VK_Q, ACTION_QUIT); //$NON-NLS-1$

		//Help menu
		JMenu helpMenu = new JMenu(Messages.getString("InitOrderFrame.helpMenuOption")); //$NON-NLS-1$
		helpMenu.setMnemonic(KeyEvent.VK_H);
		menubar.add(helpMenu);

        addMenuItem(helpMenu, Messages.getString("InitOrderFrame.licenseMenuOption"), KeyEvent.VK_L, ACTION_LICENSE); //$NON-NLS-1$
        addMenuItem(helpMenu, Messages.getString("InitOrderFrame.OGLMenuOption"), KeyEvent.VK_O, ACTION_OGL_LICENSE); //$NON-NLS-1$
		addMenuItem(helpMenu, Messages.getString("InitOrderFrame.aboutMenuOption"), KeyEvent.VK_A, ACTION_ABOUT); //$NON-NLS-1$

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
		final TableColumn numColumn = table.getColumnModel().getColumn(EntityListGwtable.COLUMN_NUMBER_NUM);
		smartResizeColumn(numColumn);
		final TableColumn nameColumn = table.getColumnModel().getColumn(EntityListGwtable.COLUMN_NUMBER_NAME);
		nameColumn.setMinWidth(75);
		nameColumn.setPreferredWidth(300);
		final TableColumn initColumn = table.getColumnModel().getColumn(EntityListGwtable.COLUMN_NUMBER_INIT);
		smartResizeColumn(initColumn);
		initColumn.setMaxWidth(initColumn.getPreferredWidth());
		final TableColumn hpColumn = table.getColumnModel().getColumn(EntityListGwtable.COLUMN_NUMBER_HP);
		smartResizeColumn(hpColumn);
        final TableColumn subdualColumn = table.getColumnModel().getColumn(EntityListGwtable.COLUMN_NUMBER_SUBDUAL);
        smartResizeColumn(subdualColumn);
        final TableColumn roundsColumn = table.getColumnModel().getColumn(EntityListGwtable.COLUMN_NUMBER_ROUNDS);
        smartResizeColumn(roundsColumn);
        final TableColumn myTurnColumn = table.getColumnModel().getColumn(EntityListGwtable.COLUMN_NUMBER_MY_TURN);
        smartResizeColumn(myTurnColumn);
        final TableColumn typeColumn = table.getColumnModel().getColumn(EntityListGwtable.COLUMN_NUMBER_TYPE);

        JComboBox comboBox = new JComboBox();
        for (Entity.EntityType entityType : Entity.EntityType.values())
            comboBox.addItem(entityType);
        typeColumn.setCellEditor(new DefaultCellEditor(comboBox));

        smartResizeTypeColumn(table, typeColumn);

        smartResizeColumn(typeColumn);

        myTurnColumn.setMaxWidth(initColumn.getMinWidth());

		final TableCellRenderer stringRenderer = table.getDefaultRenderer(String.class);
		table.setDefaultRenderer(String.class, new HighlightingTableCellRenderer(stringRenderer));

		final TableCellRenderer integerRenderer = table.getDefaultRenderer(Integer.class);
		table.setDefaultRenderer(Integer.class, new HighlightingTableCellRenderer(integerRenderer));

		final TableCellRenderer boolRenderer = table.getDefaultRenderer(Boolean.class);
		table.setDefaultRenderer(Boolean.class, new HighlightingTableCellRenderer(boolRenderer));

	}


	/**
	 * Resize the type column to fit the widest element in the enum.
	 *
	 * Code originally from http://www.exampledepot.com/egs/javax.swing.table/PackCol.html#
	 * @param typeColumn
	 */
    private static void smartResizeTypeColumn(JTable table, TableColumn typeColumn) {

        //table.setAutoResizeMode(JTable.AUTO_RESIZE_OFF);
        // Get width of column header
        TableCellRenderer renderer = typeColumn.getHeaderRenderer();
        if (renderer == null) {
            renderer = table.getTableHeader().getDefaultRenderer();
        }
        Component comp = renderer.getTableCellRendererComponent(table,
                typeColumn.getHeaderValue(), false, false, -1,
                EntityListGwtable.COLUMN_NUMBER_TYPE);
        int width = comp.getPreferredSize().width;

        for (Entity.EntityType entityType : Entity.EntityType.values()) {
            for (int row = 0; row < 5; ++row) {
                renderer = table.getCellRenderer(row, EntityListGwtable.COLUMN_NUMBER_TYPE);
                comp = renderer.getTableCellRendererComponent(table,
                        entityType.toString(), true, true, row,
                        EntityListGwtable.COLUMN_NUMBER_TYPE);
                int preferredSize = comp.getMaximumSize().width;
                if (preferredSize > width)
                    width = preferredSize;
            }
        }

        width *= 1.3;

        typeColumn.setPreferredWidth(width);
        typeColumn.setMinWidth(width);
    }

    private static void smartResizeColumn(final TableColumn column) {
		column.sizeWidthToFit();
		column.setMaxWidth(column.getPreferredWidth());
		column.setPreferredWidth((int) (column.getPreferredWidth() * 0.7));
		column.setMinWidth((int) (column.getMinWidth() *  1.3));
	}


	private static void addSampleData(EntityList dataModel) {
	    dataModel.addSampleData();
	}

	public void actionPerformed(ActionEvent e) {
        final String actionCommand = e.getActionCommand();
        if (ACTION_ADD.equalsIgnoreCase(actionCommand))
        {
            AddDialog addDialog = new AddDialog(this, this.dataModel, AddDialog.AddType.CREATURE);
            addDialog.setVisible(true);

        }
        else if (ACTION_EFFECT.equalsIgnoreCase(actionCommand))
        {
            AddDialog addDialog = new AddDialog(this, this.dataModel, AddDialog.AddType.EFFECT, this.dataModel.getInitCount());
            addDialog.setVisible(true);

        }
        else if (ACTION_NEXT.equalsIgnoreCase(actionCommand))
        {
        	dataModel.gotoNextInitCount();
        }
        else if (ACTION_REMOVE.equalsIgnoreCase(actionCommand))
        {
        	removeSelected();
        }
        else if (ACTION_QUIT.equalsIgnoreCase(actionCommand) ||
                 ACTION_EXIT.equalsIgnoreCase(actionCommand))
        {
            this.setVisible(false);
            this.dispose();
        }
        else if (ACTION_ABOUT.equalsIgnoreCase(actionCommand))
        {
            LicenseBox about = new LicenseBox (ABOUT_FILENAME);
            about.setVisible(true);
        }
        else if (ACTION_LICENSE.equalsIgnoreCase(actionCommand))
        {
            JFrame license = new LicenseBox (GPL_FILENAME);
            license.setVisible(true);
        }
        else if (ACTION_OGL_LICENSE.equalsIgnoreCase(actionCommand))
        {
            JFrame license = new LicenseBox (OGL_FILENAME);
            license.setVisible(true);
        }
        else if (ACTION_IMPORT.equalsIgnoreCase(actionCommand))
        {
        	importFile();
        }
        else if (ACTION_LOAD.equalsIgnoreCase(actionCommand))
        {
        	if (clear())
        		importFile();
        }
        else if (ACTION_SAVE_AS.equalsIgnoreCase(actionCommand))
        {
        	saveAs();
        }
        else if (ACTION_CLEAR.equalsIgnoreCase(actionCommand))
        {
            clear();
        }
        else if (Entity.stringToDamageType(actionCommand) != null)
        {
            damage(actionCommand);
        }
        else
        {
        	JOptionPane.showMessageDialog(this, Messages.getString("InitOrderFrame.errorUnknownActionType") + actionCommand + Messages.getString("InitOrderFrame.60") , Messages.getString("InitOrderFrame.windowTitleInternalError"), JOptionPane.ERROR_MESSAGE); //$NON-NLS-1$ //$NON-NLS-2$ //$NON-NLS-3$
        }

	}

    private void damage(final String actionCommand) {
        int row = table.getSelectedRow();
        int modelRow = table.convertRowIndexToModel(row);
        Entity entity = dataModel.getEntity(modelRow);

        DamageType type = Entity.stringToDamageType(actionCommand);
        final String damageTypeString = Entity.damageTypeToString(type);
        String message = damageTypeString + " " + entity.getName() + Messages.getString("InitOrderFrame.by"); //$NON-NLS-1$ //$NON-NLS-2$
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
                JOptionPane.showMessageDialog(this, Messages.getString("InitOrderFrame.errorInvalidAmount") + e.getLocalizedMessage(), Messages.getString("InitOrderFrame.windowTitleError"), //$NON-NLS-1$ //$NON-NLS-2$
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
                resultsBox.setResult("" + damage.value()); //$NON-NLS-1$
                resultsBox.addLine(Entity.damageTypeToString(type) + " \"" //$NON-NLS-1$
                        + entity.getName() + "\"" + Messages.getString("InitOrderFrame.by") + damage.toLongString()); //$NON-NLS-1$
            }

        }
        catch (Exception except)
        {
            JOptionPane.showMessageDialog(this, except.getMessage(),
                    Messages.getString("InitOrderFrame.windowTitleError"), //$NON-NLS-1$
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
				JOptionPane.showMessageDialog(this, Messages.getString("InitOrderFrame.windowTitleError"),
				        Messages.getString("InitOrderFrame.errorFileNotFound") + e1.getLocalizedMessage(),  //$NON-NLS-1$
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
		chooser.setDialogTitle(Messages.getString("InitOrderFrame.windowTitleImport"));			 //$NON-NLS-1$
		int retVal = chooser.showOpenDialog(this);
		if (retVal == JFileChooser.APPROVE_OPTION)
		{
			File file = chooser.getSelectedFile();
			try {
				dataModel.importFile(file);
			} catch (FileNotFoundException e1) {
				JOptionPane.showMessageDialog(this, Messages.getString("InitOrderFrame.windowTitleError"), Messages.getString("InitOrderFrame.errorFileNotFound") + e1.getLocalizedMessage(), JOptionPane.ERROR_MESSAGE); //$NON-NLS-1$ //$NON-NLS-2$
				e1.printStackTrace();
			}
		}
	}

	/**
	 * Erases all entries.  Asks for confirmation first.
	 */
	private boolean clear() {
		int retVal = JOptionPane.showConfirmDialog(this, Messages.getString("InitOrderFrame.confirmDeleteAllEntries"),  //$NON-NLS-1$
				Messages.getString("InitOrderFrame.windowTitleConfirm"), JOptionPane.YES_NO_OPTION, JOptionPane.QUESTION_MESSAGE); //$NON-NLS-1$
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
