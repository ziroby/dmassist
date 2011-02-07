package com.ziroby.android.dmassist;

import android.app.Activity;
import android.os.Bundle;
import android.widget.ImageView;

public class Help extends Activity {
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        // TODO Auto-generated method stub
        super.onCreate(savedInstanceState);
        setContentView(R.layout.help_image);

        ImageView image = (ImageView) findViewById(R.id.help_image);
        image.setImageResource(R.drawable.help_image);
    }
}
