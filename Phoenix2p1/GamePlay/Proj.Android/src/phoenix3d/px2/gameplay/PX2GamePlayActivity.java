package phoenix3d.px2.gameplay;

import phoenix3d.px2.library.PX2Activity;
import android.content.pm.ActivityInfo;
import android.os.Bundle;
import android.util.Log;
import android.view.Window;
import android.view.WindowManager;

public class PX2GamePlayActivity extends PX2Activity
{	
    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState) 
    {
    	Log.d("phoenix3d.px2", "PX2GamePlayActivity::onCreate");
    	
		String packageName = getApplication().getPackageName();
		super.SetPX2PackageName(packageName);	
		
        super.onCreate(savedInstanceState);
    }
    
    @Override
	 protected void onPause() {  
		 Log.d("phoenix3d.px2", "PX2GamePlayActivity::onPause");
	     super.onPause();	   
	     mGLView.onPause();
	 }

	 @Override
	 protected void onResume() {
		 Log.d("phoenix3d.px2", "PX2GamePlayActivity::onResume");
	     mGLView.onResume();
		 super.onResume();
	 }
	 
	 @Override
	 public void onDestroy() {
		 mGLView.onDestory();
	     super.onDestroy();
	 }
    
    static
    {
        System.loadLibrary("PX2GamePlayJNI");
    }     
}