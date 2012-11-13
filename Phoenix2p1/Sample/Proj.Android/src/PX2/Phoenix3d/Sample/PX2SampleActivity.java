package PX2.Phoenix3d.Sample;

import PX2.Phoenix3d.Sample.R;
import PX2.Phoenix3d.Sample.R.layout;
import android.app.Activity;
import android.app.ActivityManager;
import android.content.Context;
import android.content.pm.ConfigurationInfo;
import android.os.Bundle;
import PX2.Phoenix3d.Library.PX2Activity;

public class PX2SampleActivity extends PX2Activity
{	
    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState) 
    {
        super.onCreate(savedInstanceState);
    }
    
    static
    {
        System.loadLibrary("PX2SampleJNI");
    }     
}