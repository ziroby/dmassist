package com.ziroby.dmassist.ui;

import java.util.MissingResourceException;
import java.util.ResourceBundle;

public class Messages {
    private static final String BUNDLE_NAME = "com.ziroby.dmassist.ui.messages"; //$NON-NLS-1$

    private static final ResourceBundle RESOURCE_BUNDLE  = ResourceBundle
    .getBundle(BUNDLE_NAME);
//    = ResourceBundle
//    .getBundle(BUNDLE_NAME, new Locale("en", "", "x-pig-latin"));

    private Messages() {
    }

    public static String getString(String key) {
        try {
            return RESOURCE_BUNDLE.getString(key);
        } catch (MissingResourceException e) {
            return '!' + key + '!';
        }
    }
}
