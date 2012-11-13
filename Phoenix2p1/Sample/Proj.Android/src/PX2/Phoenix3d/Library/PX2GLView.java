package PX2.Phoenix3d.Library;


import android.app.Activity;
import android.opengl.GLSurfaceView;
import android.util.Log;
import android.view.MotionEvent;
import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import PX2.Phoenix3d.Library.PX2Activity;
import PX2.Phoenix3d.Library.PX2Renderer;

public class PX2GLView extends GLSurfaceView
{
    private PX2Activity mActivity;
    private PX2Renderer mRenderer;
	
    public PX2GLView(PX2Activity activity)
    {
        super(activity);
        
        mActivity = activity;
        
        mRenderer = new PX2Renderer(activity);        
        setRenderer(mRenderer);
    }

    public boolean onTouchEvent(final MotionEvent event)
    {
        if (mRenderer!=null) 
        {
        }
        
        return true;
    }
    
    protected void onSizeChanged(int w, int h, int oldw, int oldh)
    {
    	this.mRenderer.setScreenWidthAndHeight(w, h);
    }
}
