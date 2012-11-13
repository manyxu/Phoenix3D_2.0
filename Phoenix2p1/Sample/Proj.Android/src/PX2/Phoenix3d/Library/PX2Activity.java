package PX2.Phoenix3d.Library;

import android.app.Activity;
import android.app.ActivityManager;
import android.content.Context;
import android.content.pm.ConfigurationInfo;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.util.DisplayMetrics;
import android.util.Log;
import PX2.Phoenix3d.Library.PX2GLView;

public class PX2Activity extends Activity
{	
	protected PX2GLView mGLView;
	
	 protected void onCreate(Bundle savedInstanceState) 
	 {
		 super.onCreate(savedInstanceState); 
		 
		 if (detectOpenGLES20())
		 {
			 mGLView = new PX2GLView(this);
			 setContentView(mGLView);
		 }
		 else 
		 {
			Log.d("activity", "don't support gles2.0");
			finish();
		 }
	 }
	 
	private boolean detectOpenGLES20() 
	{
		ActivityManager am =
		   		 (ActivityManager) getSystemService(Context.ACTIVITY_SERVICE);
		ConfigurationInfo info = am.getDeviceConfigurationInfo();
		    
		return (info.reqGlEsVersion >= 0x20000);
	}

}
