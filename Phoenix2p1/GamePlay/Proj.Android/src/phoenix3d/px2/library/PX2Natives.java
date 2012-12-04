package phoenix3d.px2.library;

import android.view.MotionEvent;

public class PX2Natives
{
	public static native void nativeOdle ();
	public static native void nativeInit (int width, int height);
	public static native void nativeOnPause ();
	public static native void nativeOnResume ();
	public static native void nativeOnTerm ();
	public static native void nativeSetResourcePath(String path);
}
