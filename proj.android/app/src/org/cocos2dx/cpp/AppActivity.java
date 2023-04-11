/****************************************************************************
 Copyright (c) 2015-2016 Chukong Technologies Inc.
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/
package org.cocos2dx.cpp;

import android.os.Bundle;
import android.view.View;
import org.cocos2dx.lib.Cocos2dxActivity;


import android.Manifest;
import android.app.Activity;
import android.app.AlertDialog;
import android.content.ContextWrapper;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.net.Uri;
import android.os.Build;
import android.os.Bundle;
import android.os.Environment;
import android.provider.MediaStore;
import android.support.v4.app.ActivityCompat;
import android.support.v4.content.ContextCompat;
import android.util.Log;
import android.view.WindowManager;
import android.widget.Toast;


import org.cocos2dx.lib.Cocos2dxActivity;
import org.cocos2dx.lib.Cocos2dxHelper;
import org.cocos2dx.lib.Cocos2dxRenderer;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.ArrayList;
import java.util.ResourceBundle;
import android.support.v4.content.FileProvider;

import com.yourcompany.fourpiconeword.BuildConfig; //add your package name after write .BuildConfig
import com.yourcompany.fourpiconeword.R;

public class AppActivity extends Cocos2dxActivity {

    private static AdManager admanager =  null;
    private static AppActivity _this;
    public static boolean admobfullpageavailable =  false;

    public static native void  coinReward();
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.setEnableVirtualButton(false);
        super.onCreate(savedInstanceState);
        if (!isTaskRoot()) {
            return;
        }

        admanager =  new AdManager(this);
        _this = this;

    }


    public static void bannerEnabled(){

        _this. runOnUiThread(new Runnable() {
            @Override
            public void run() {
                admanager.ShowBanner();
            }
        });

    }

    public static  void HideBanner(){

        _this. runOnUiThread(new Runnable() {
            @Override
            public void run() {
                admanager.HideBanner();
            }
        });

    }

    public static boolean isInterstitialAvailable(){

        return admobfullpageavailable;
    }

    public static void showInterstitial(){

        _this. runOnUiThread(new Runnable() {
            @Override
            public void run() {
                admanager.ShowInterstitial();
            }
        });

    }

    public static void ShowReward(){

        _this. runOnUiThread(new Runnable() {
            @Override
            public void run() {
                admanager.ShowReward();
            }
        });

    }

    public static void OpenMoreGame()
    {
        String url="";
        Intent storeintent=null;


        String moreURL = getContext().getApplicationContext().getString(R.string.more_game_url);
        url = moreURL;
        storeintent = new Intent(Intent.ACTION_VIEW, Uri.parse(url));
        storeintent.addFlags(Intent.FLAG_ACTIVITY_NEW_TASK | Intent.FLAG_ACTIVITY_RESET_TASK_IF_NEEDED);
        _this.startActivity(storeintent);

    }
    public static void openRateGame()
    {
        String url="";
        Intent storeintent=null;

        String rateURL = getContext().getApplicationContext().getString(R.string.rate_game_url);
        url = rateURL;
        storeintent = new Intent(Intent.ACTION_VIEW, Uri.parse(url));
        storeintent.addFlags(Intent.FLAG_ACTIVITY_NEW_TASK | Intent.FLAG_ACTIVITY_RESET_TASK_IF_NEEDED);
        _this.startActivity(storeintent);
    }

    @Override
    public void onStart() {
        super.onStart();

    }

    @Override
    public void onResume() {
        super.onResume();


    }

    @Override
    public void onPause() {
        super.onPause();
        if(admanager != null)
            admanager.onPause();
    }

    @Override
    public void onStop() {
        super.onStop();

    }

    @Override
    public void onDestroy() {
        super.onDestroy();
        if(admanager != null)
            admanager.onDESTROY();
    }

    @Override
    public void onBackPressed() {
            super.onBackPressed();
    }

    public static void BackButtonClicked(){

        _this.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                AlertDialog.Builder builder = new AlertDialog.Builder(_this,
                        R.style.MyAlertDialogStyle);
                builder.setTitle(_this.getResources().getString(R.string.app_name));
                builder.setCancelable(false);
                builder.setMessage("Do you want to EXIT");
                builder  .setPositiveButton("Yes", new DialogInterface.OnClickListener()
                {
                    @Override
                    public void onClick(DialogInterface dialog, int which) {
                        _this.finish();
                    }

                })
                        .setNegativeButton("No", null);

                builder.show();
            }
        });

    }


}
