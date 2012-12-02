package phoenix3d.px2.library;

import android.opengl.GLSurfaceView;
import android.view.MotionEvent;

import phoenix3d.px2.library.PX2Activity;
import phoenix3d.px2.library.PX2Renderer;

public class PX2GLView extends GLSurfaceView
{
    private PX2Renderer mRenderer;
	
    public PX2GLView(PX2Activity activity)
    {
        super(activity);
        setEGLContextClientVersion(2);
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
