package phoenix3d.px2.library;

import android.opengl.GLSurfaceView;
import android.util.Log;
import android.view.KeyEvent;
import android.view.MotionEvent;
import phoenix3d.px2.library.PX2Natives;
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
   
    protected void onSizeChanged(int w, int h, int oldw, int oldh)
    {
    	this.mRenderer.setScreenWidthAndHeight(w, h);
    }
    
    public void onPause(){
    	
    	queueEvent(new Runnable() {

            public void run() {
            	PX2Natives.nativeOnPause();
            }
        });
    	
    	super.onPause();
    }
    
    public void onResume(){
    	
    	super.onResume();   	 
    	
    	queueEvent(new Runnable() {

            public void run() {
            	PX2Natives.nativeOnResume();
            }
        });
    }
    
    
    public boolean onTouchEvent(final MotionEvent event) 
    {
    	// these data are used in ACTION_MOVE and ACTION_CANCEL
    	final int pointerNumber = event.getPointerCount();
    	final int[] ids = new int[pointerNumber];
    	final float[] xs = new float[pointerNumber];
    	final float[] ys = new float[pointerNumber];

    	for (int i = 0; i < pointerNumber; i++) 
    	{
            ids[i] = event.getPointerId(i);
            xs[i] = event.getX(i);
            ys[i] = event.getY(i);
        }
        
        switch (event.getAction() & MotionEvent.ACTION_MASK)
        {
        case MotionEvent.ACTION_POINTER_DOWN:
        	final int indexPointerDown = event.getAction() >> MotionEvent.ACTION_POINTER_ID_SHIFT;
        	final int idPointerDown = event.getPointerId(indexPointerDown);
            final float xPointerDown = event.getX(indexPointerDown);
            final float yPointerDown = event.getY(indexPointerDown);

            queueEvent(new Runnable() {
                public void run() {
                	PX2Natives.nativeTouchPressed(idPointerDown, xPointerDown, yPointerDown);
                }
            });
            break;
            
        case MotionEvent.ACTION_DOWN:
        	// there are only one finger on the screen
        	final int idDown = event.getPointerId(0);
            final float xDown = xs[0];
            final float yDown = ys[0];
            
            queueEvent(new Runnable() {
                public void run() {
                	PX2Natives.nativeTouchPressed(idDown, xDown, yDown);
                }
            });
            break;

        case MotionEvent.ACTION_MOVE:
            queueEvent(new Runnable() {
                public void run() {
                	PX2Natives.nativeTouchMoved(ids, xs, ys);
                }
            });
            break;

        case MotionEvent.ACTION_POINTER_UP:
        	final int indexPointUp = event.getAction() >> MotionEvent.ACTION_POINTER_ID_SHIFT;
        	final int idPointerUp = event.getPointerId(indexPointUp);
            final float xPointerUp = event.getX(indexPointUp);
            final float yPointerUp = event.getY(indexPointUp);
            
            queueEvent(new Runnable() {
  
                public void run() {
                	PX2Natives.nativeTouchReleased(idPointerUp, xPointerUp, yPointerUp);
                }
            });
            break;
            
        case MotionEvent.ACTION_UP:  
        	final int idUp = event.getPointerId(0);
            final float xUp = xs[0];
            final float yUp = ys[0];
            
            queueEvent(new Runnable() {
                public void run() {
                	PX2Natives.nativeTouchReleased(idUp, xUp, yUp);
                }
            });
            break;

        case MotionEvent.ACTION_CANCEL:
            queueEvent(new Runnable() {
                public void run() {
                	PX2Natives.nativeTouchCancelled(ids, xs, ys);
                }
            });
            break;
        }
        return true;
    }
    
    public boolean onKeyDown(int keyCode, KeyEvent event)
    {
    	final int kc = keyCode;
    	if (keyCode == KeyEvent.KEYCODE_BACK || keyCode == KeyEvent.KEYCODE_MENU)
    	{
    		queueEvent(new Runnable() {
	            public void run() {
	            	PX2Natives.nativeKeyDown(kc);
	            }
    		});
    		return true;
    	}
        return super.onKeyDown(keyCode, event);
    }
}
