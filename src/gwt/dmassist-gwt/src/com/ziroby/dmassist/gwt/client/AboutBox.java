package com.ziroby.dmassist.gwt.client;

import com.google.gwt.user.client.ui.DialogBox;

public class AboutBox extends DialogBox
{
    private static final String ABOUT_TEXT =
        "<h1>DM Assist</h1>" +
        "<p>Copyright © 2009, 2010 Ron \"Ziroby\" Romero</p>\n" +
        "\n" +
        "<p>This program comes with ABSOLUTELY NO WARRANTY.</p>\n" +
        "This is free software, and you are welcome to redistribute it under<br/>\n" +
        "certain conditions; see \"Help -> License. . . \" for details. DM Assist<br/>\n" +
        "contains:<p />\n" +
        "portions from GMGen/PCGen,copyright © 2002 Devon D. Jones</p>\n" +
        "PCGen Character Generator Copyright © 2001-2003, PCgen Data team<br/>\n" +
        "including, but not limited to, Rob Reed (Mynex), Patryk Adamski<br/>\n" +
        "(Ruemere), Hugo Perez (Emperorfranz), Andrew McDougall (Tir Gwaith)\n" +
        "<p>jYaml, copyright © 2005, Yu Cheung Ho</p>\n" +
        "";

    public AboutBox()
    {
        super(true /*autohide*/);

        setWidth("40em");

        setHTML(ABOUT_TEXT);
        setTitle("About DM Assist");
    }
}
