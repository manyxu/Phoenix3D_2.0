package phoenix3d.px2.library;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;
import android.opengl.GLSurfaceView;
import phoenix3d.px2.library.PX2Natives;

class PX2Renderer implements GLSurfaceView.Renderer
{
	private int screenWidth;
	private int screenHeight;
    private PX2Activity mActivity;

    public PX2Renderer(PX2Activity activity)
    {
        mActivity = activity;
    }
    
    public void setScreenWidthAndHeight(int w, int h)
    {
    	this.screenWidth = w;
    	this.screenHeight = h;
    }

    // -process begin
    public void onSurfaceCreated(GL10 gl, EGLConfig config)
    {
    	PX2Natives.nativeInit(screenWidth, screenHeight); 
    }

    public void onSurfaceChanged(GL10 gl, int width, int height) 
    {
    }
    
    public void handleOnPause()
    {
    	PX2Natives.nativeOnPause();
    }
    
    public void handleOnResume()
    {
    	PX2Natives.nativeOnResume();
    }

    public void onDrawFrame(GL10 gl)
    {
    	// draw
    	PX2Natives.nativeOdle();
    }  
    // -process end
}
