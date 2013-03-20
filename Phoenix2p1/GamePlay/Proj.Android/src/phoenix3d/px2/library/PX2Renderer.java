package phoenix3d.px2.library;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import android.graphics.PixelFormat;
import android.opengl.GLSurfaceView;
import android.util.Log;
import android.opengl.GLES20;
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
    
    	Log.d("phoenix3d.px2", "PX2Renderer::onSurfaceCreated");
    	PX2Natives.nativeInit(screenWidth, screenHeight); 
    }

    public void onSurfaceChanged(GL10 gl, int width, int height) 
    {
    	GLES20.glViewport(0, 0, width, height);
    } 

    public void onDrawFrame(GL10 gl)
    {
    	// draw
    	PX2Natives.nativeOdle();
    } 
    

    // -process end
}
