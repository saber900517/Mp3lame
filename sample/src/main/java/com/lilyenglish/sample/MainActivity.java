package com.lilyenglish.sample;

import android.os.Environment;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;

import com.lilyenglish.library.MP3Recorder;

import java.io.File;
import java.io.IOException;

public class MainActivity extends AppCompatActivity {
    private MP3Recorder mRecorder;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        mRecorder = new MP3Recorder(new File(Environment.getExternalStorageDirectory(), "mp3lame.mp3"));
    }

    public void onClick(View v) {
        switch (v.getId()) {
            case R.id.start:
                try {
                    mRecorder.start();
                } catch (IOException e) {
                    e.printStackTrace();
                }
                break;
            case R.id.stop:
                mRecorder.stop();
                break;
        }
    }
}
