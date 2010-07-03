package com.ziroby.android.util;

import android.app.Activity;
import android.app.AlertDialog;
import android.content.DialogInterface;
import android.util.Log;

public class AndroidUtils
{

    public static void displayErrorDialog(Activity activity, Exception e) {
        String message = e.getLocalizedMessage();
        if (message == null || message == "") {
            message = e.getClass().getName();
        }
        else {
            message = e.getClass().getName() + ": " + message;
        }

        Log.e(activity.getClass().toString(), "Exception: " + message, e);

        AlertDialog.Builder builder = new AlertDialog.Builder(activity);
        builder.setMessage(message)
        .setCancelable(false)
        .setTitle("Error")
        .setPositiveButton("OK", new DialogInterface.OnClickListener() {
            public void onClick(DialogInterface dialog, int id) {
                dialog.cancel();
            }
        });
        AlertDialog alert = builder.create();

        alert.show();
    }

}
