package platinmods.menu.pmt;

import android.os.Build;
import android.os.Process;
import android.view.View;
import android.os.IBinder;
import android.os.Handler;
import android.util.Base64;
import android.app.Service;
import android.content.Intent;
import android.content.Context;
import android.widget.TextView;
import android.widget.ImageView;
import android.view.MotionEvent;
import android.view.WindowManager;
import android.app.ActivityManager;
import android.widget.RelativeLayout;
import android.graphics.BitmapFactory;
import android.annotation.SuppressLint;

import java.util.Objects;

public class Reborn extends Service {

    public int width;
    public int height;
    public ImageView pmtIcon;
    public TextView menuTitle;
    public RelativeLayout icon;
    public RelativeLayout menu;
    public boolean resetAvailable;
    public WindowManager windowManager;
    public WindowManager.LayoutParams iconOverlayParam;

    public native void resetMenu(int category, TextView textView);
    private static native void Initialize(Context context);
    public native void changingMenu(TextView textView);
    public native void submitPID(int processID);
    public native void createWindowParams();
    public native void toggleMenu();

    @Override
    public IBinder onBind(Intent intent) {
        return null;
    }

    public void setOnClickListener(boolean isTitle, final int id, final TextView textView) {
        if (isTitle) {
            this.menuTitle.setOnClickListener(view -> Reborn.this.toggleMenu());
        } else {
            textView.setOnClickListener(view -> {
                Reborn.this.changingMenu(textView);
                new Handler().postDelayed(() -> Reborn.this.resetMenu(id, textView), 250L);
            });
        }
    }

    @SuppressLint("SetTextI18n")
    public native void createViews();

    @SuppressLint("ClickableViewAccessibility")
    public void menuSystem() {
        System.loadLibrary("platinmods");

        submitPID(Process.myPid());
        Initialize(this);

        this.windowManager = (WindowManager) getSystemService(Context.WINDOW_SERVICE);
        this.width = this.windowManager.getDefaultDisplay().getWidth();
        this.height = this.windowManager.getDefaultDisplay().getHeight();

        createWindowParams();

        this.icon.setOnTouchListener(new View.OnTouchListener() {
            private float initialTouchX;
            private float initialTouchY;
            private int initialX;
            private int initialY;

            @Override
            public boolean onTouch(View view, MotionEvent motionEvent) {
                switch (motionEvent.getAction()) {
                    case MotionEvent.ACTION_DOWN:
                        this.initialX = Reborn.this.iconOverlayParam.x;
                        this.initialY = Reborn.this.iconOverlayParam.y;
                        this.initialTouchX = motionEvent.getRawX();
                        this.initialTouchY = motionEvent.getRawY();
                        return true;

                    case MotionEvent.ACTION_UP:
                        int rawX = (int) (motionEvent.getRawX() - this.initialTouchX);
                        int rawY = (int) (motionEvent.getRawY() - this.initialTouchY);
                        if (rawX < 10 && rawY < 10) {
                            Reborn.this.menu.setVisibility(View.VISIBLE);
                            Reborn.this.icon.setVisibility(View.GONE);
                        }
                        return true;

                    case MotionEvent.ACTION_MOVE:
                        Reborn.this.iconOverlayParam.x = this.initialX + ((int) (motionEvent.getRawX() - this.initialTouchX));
                        Reborn.this.iconOverlayParam.y = this.initialY + ((int) (motionEvent.getRawY() - this.initialTouchY));
                        Reborn.this.windowManager.updateViewLayout(Reborn.this.icon, Reborn.this.iconOverlayParam);
                        return true;

                    default:
                        return false;
                }
            }
        });

        try {
            byte[] decode = Base64.decode(SetupActivity.image, Base64.DEFAULT);
            this.pmtIcon.setImageBitmap(BitmapFactory.decodeByteArray(decode, 0, decode.length));
        } catch (Exception ignored) {}

        createViews();
    }

    private boolean IsAppInBackground(Context context) {
        ActivityManager activityManager = (ActivityManager) context.getSystemService(Context.ACTIVITY_SERVICE);
        if (Build.VERSION.SDK_INT <= Build.VERSION_CODES.N_MR1)
            return !Objects.requireNonNull(activityManager.getRunningTasks(1).get(0).topActivity).getPackageName().equals(context.getPackageName());

        for (ActivityManager.RunningAppProcessInfo runningAppProcessInfo : activityManager.getRunningAppProcesses()) {
            if (runningAppProcessInfo.importance == 100) {
                for (String str : runningAppProcessInfo.pkgList) {
                    if (str.equals(context.getPackageName())) {
                        return false;
                    }
                }
            }
        }

        return true;
    }

    public void PerformLoop() {
        if (IsAppInBackground(this)) {
            this.icon.setVisibility(View.GONE);
            this.menu.setVisibility(View.GONE);
            this.resetAvailable = true;
        }

        if (!IsAppInBackground(this) && this.resetAvailable) {
            this.icon.setVisibility(View.VISIBLE);
            this.resetAvailable = false;
        }

        new Handler().postDelayed(Reborn.this::PerformLoop, 50L);
    }

    @Override
    public void onCreate() {
        super.onCreate();
        menuSystem();
        //PerformLoop();
    }

    @Override
    public void onTaskRemoved(Intent rootIntent) {
        stopSelf();
        try {
            Thread.sleep(100);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        super.onTaskRemoved(rootIntent);
    }

    @Override
    public int onStartCommand(Intent intent, int flags, int startId) {
        return START_NOT_STICKY;
    }

    @Override
    public void onDestroy() {
        super.onDestroy();

        RelativeLayout relativeLayout = this.icon;
        if (relativeLayout != null)
            this.windowManager.removeView(relativeLayout);

        relativeLayout = this.menu;
        if (relativeLayout != null)
            this.windowManager.removeView(relativeLayout);
    }
}