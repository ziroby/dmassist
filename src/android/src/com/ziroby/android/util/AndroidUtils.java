package com.ziroby.android.util;

import android.app.Activity;
import android.app.AlertDialog;
import android.app.AlertDialog.Builder;
import android.content.DialogInterface;
import android.content.DialogInterface.OnClickListener;
import android.util.Log;

public class AndroidUtils
{

    public static void displayErrorDialog(Activity activity, Exception e) {
        Log.e(activity.getClass().toString(), "Exception: " + e.getLocalizedMessage(), e);
    
        AlertDialog.Builder builder = new AlertDialog.Builder(activity);
        builder.setMessage(e.getLocalizedMessage())
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
