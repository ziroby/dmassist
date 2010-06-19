package com.ziroby.android.dmassist;

import android.app.Activity;
import android.os.Bundle;
import android.view.View;
import android.view.View.OnClickListener;
import android.webkit.WebView;
import android.widget.Button;

import com.ziroby.android.util.AndroidUtils;

public class AboutBox extends Activity
{
    private static final String ABOUT_HTML = "file:///android_asset/about.html";
    private static final String ZIROBY_HTML = "file:///android_asset/ziroby.html";
    private static final String OGL_HTML = "file:///android_asset/OGL.txt";
    private static final String GPL_HTML = "file:///android_asset/LICENSE.txt";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        try {
            super.onCreate(savedInstanceState);
            setContentView(R.layout.about_box);

            wireInButton(R.id.about_author_button, ZIROBY_HTML);
            wireInButton(R.id.display_copyright_button, ABOUT_HTML);
            wireInButton(R.id.display_gpl_button, GPL_HTML);
            wireInButton(R.id.display_ogl_button, OGL_HTML);
        }
        catch (Exception e) {
            AndroidUtils.displayErrorDialog(this, e);
        }



        //        WebView blurb = (WebView) findViewById(R.id.author_blurb);
        //
        //        blurb.loadData("<html><body>"
        //                + getResources().getText(R.string.author_blurb)
        //                +"</body></html>",
        //                "text/html", "utf-8");
    }

    private void wireInButton(final int buttonId, final String page) {
        Button button = (Button) findViewById(buttonId);
        button.setOnClickListener(new OnClickListener() {
            public void onClick(View v) {
                displayAboutBox(page);
            }
        });
    }

    void displayAboutBox(String htmlPage) {
        try {
            WebView webView = new WebView(this);
            webView.loadUrl(htmlPage);
            setContentView(webView);
        }
        catch (Exception e) {
            AndroidUtils.displayErrorDialog(this, e);
        }
    }
}
