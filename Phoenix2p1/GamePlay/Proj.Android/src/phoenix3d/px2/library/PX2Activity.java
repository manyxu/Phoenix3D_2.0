package phoenix3d.px2.library;

import android.app.Activity;
import android.app.ActivityManager;
import android.content.Context;
import android.content.pm.ApplicationInfo;
import android.content.pm.ConfigurationInfo;
import android.content.pm.PackageManager;
import android.content.pm.PackageManager.NameNotFoundException;
import android.os.Bundle;
import android.util.Log;
import android.view.Window;
import android.view.WindowManager;
import android.content.pm.ActivityInfo;
import phoenix3d.px2.library.PX2GLView;
import phoenix3d.px2.gameplay.R;
import phoenix3d.px2.library.PX2Natives;

public class PX2Activity extends Activity
{	
	 protected PX2GLView mGLView;
	 private static String mPackageName;
	
	 protected void onCreate(Bundle savedInstanceState) 
	 {
	     requestWindowFeature(Window.FEATURE_NO_TITLE);
	     getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN,
	    		 WindowManager.LayoutParams.FLAG_FULLSCREEN);
		 
		 super.onCreate(savedInstanceState); 
		 
		 if (DetectOpenGLES20())
		 {
			 mGLView = new PX2GLView(this);
			 setContentView(mGLView);
		 }
		 else 
		 {
			Log.d("PX2Activity", "Don't support gles2.0");
			finish();
		 }
	 }
	 
	public static String GetPX2PackageName ()
	{
		 return mPackageName;
	}
	
	// called in PX2GamePalyActivity
	protected void SetPX2PackageName (String packageName)
	{
		 mPackageName = packageName;
		 
		 String apkFilePath = "";
		 
	     ApplicationInfo appInfo = null;
	     PackageManager packMgmr = getApplication().getPackageManager();
	     try
	     {
	    	 appInfo = packMgmr.getApplicationInfo(packageName, 0);
	     }
	     catch (NameNotFoundException e)
	     {
	    	 e.printStackTrace();
	    	 throw new RuntimeException("Unable to locate assets, aborting...");
	     }
	     
	     apkFilePath = appInfo.sourceDir;
	     Log.w("PX2_APK_PATH", apkFilePath);
	     
	     // set apkPath
	     PX2Natives.nativeSetResourcePath(apkFilePath);
	}
	 
	private boolean DetectOpenGLES20() 
	{
		ActivityManager am =
		   		 (ActivityManager) getSystemService(Context.ACTIVITY_SERVICE);
		ConfigurationInfo info = am.getDeviceConfigurationInfo();
		    
		return (info.reqGlEsVersion >= 0x20000);
	}
	
}
