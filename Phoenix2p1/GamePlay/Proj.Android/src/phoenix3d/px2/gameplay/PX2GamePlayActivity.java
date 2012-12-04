package phoenix3d.px2.gameplay;

import phoenix3d.px2.library.PX2Activity;
import android.os.Bundle;

public class PX2GamePlayActivity extends PX2Activity
{	
    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState) 
    {
		String packageName = getApplication().getPackageName();
		super.SetPX2PackageName(packageName);
		
		super.setTitle("Phoenix3d Android test demo");
		
        super.onCreate(savedInstanceState);
    }
    
    static
    {
        System.loadLibrary("PX2GamePlayJNI");
    }     
}