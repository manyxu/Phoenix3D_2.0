package phoenix3d.px2.library;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;
import android.opengl.GLSurfaceView;

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
    	nativeInit(screenWidth, screenHeight); 
    }

    public void onSurfaceChanged(GL10 gl, int width, int height) 
    {
    }
    
    public void handleOnPause()
    {
    	nativeOnPause();
    }
    
    public void handleOnResume()
    {
    	nativeOnResume();
    }

    public void onDrawFrame(GL10 gl)
    {
    	// draw
    	nativeOdle();
    }    
  
    // -process end
    
    private static native void nativeOdle();
    private static native void nativeInit(int w, int h);
    private static native void nativeOnPause();
    private static native void nativeOnResume();
    private static native void nativeTerm();
}
