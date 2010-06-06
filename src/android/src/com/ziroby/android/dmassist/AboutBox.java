package com.ziroby.android.dmassist;

import android.app.Activity;
import android.os.Bundle;
import android.webkit.WebView;

public class AboutBox extends Activity
{
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.about_box);

        WebView blurb = (WebView) findViewById(R.id.author_blurb);

        blurb.loadData("<html><body>"
                + getResources().getText(R.string.author_blurb)
                +"</body></html>",
                "text/html", "utf-8");
    }
}
