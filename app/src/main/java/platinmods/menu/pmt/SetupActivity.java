package platinmods.menu.pmt;

import android.net.Uri;
import android.Manifest;
import android.os.Bundle;
import android.os.Handler;
import android.app.Activity;
import android.widget.Toast;
import android.content.Intent;
import android.view.ViewGroup;
import android.graphics.Color;
import android.app.AlertDialog;
import android.provider.Settings;
import android.widget.LinearLayout;
import android.content.pm.PackageManager;

public class SetupActivity extends Activity {

    public static String image;
    static final boolean IS_NEED_OVERLAY = true;
    static String gameMainActivity = "com.unity3d.player.UnityPlayerActivity";
    private static final String[] PERMISSIONS = { Manifest.permission.READ_EXTERNAL_STORAGE, Manifest.permission.WRITE_EXTERNAL_STORAGE, Manifest.permission.READ_PHONE_STATE };

    private void startUp() {
        try {
            new Handler().postDelayed(() -> {
                SetupActivity setupActivity = SetupActivity.this;
                setupActivity.startService(new Intent(setupActivity, Reborn.class));
            }, 4000L);

            startActivity(new Intent(this, Class.forName(gameMainActivity)));
        } catch (ClassNotFoundException ignored) {}
    }

    void _startEngine() {
        startUp();
        finish();
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        image = "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";

        boolean needRequestPermissions = false;
        for (String permission : PERMISSIONS) {
            if (checkSelfPermission(permission) == PackageManager.PERMISSION_DENIED) {
                needRequestPermissions = true;
            }
        }

        if (needRequestPermissions) {
            requestPermissions(PERMISSIONS, 101);
        }

        if (!IS_NEED_OVERLAY) {
            _startEngine();
        } else if (Settings.canDrawOverlays(this)) {
            _startEngine();
        } else {
            AlertDialog.Builder builder = new AlertDialog.Builder(this);
            builder.setMessage("Please grant draw over app permission to continue using our mod!");
            builder.setCancelable(false);
            builder.setPositiveButton("OK", (dialog, which) -> SetupActivity.this.startActivityForResult(new Intent("android.settings.action.MANAGE_OVERLAY_PERMISSION", Uri.parse("package:" + SetupActivity.this.getPackageName())), 102));
            builder.create().show();
        }

        Toast.makeText(this, "modded by Jasmur \nwww.platinmods.com - Gamehacks & more!", Toast.LENGTH_LONG).show();
        Toast.makeText(this, "modded by Jasmur \nwww.platinmods.com - Gamehacks & more!", Toast.LENGTH_LONG).show();
        Toast.makeText(this, "modded by Jasmur \nwww.platinmods.com - Gamehacks & more!", Toast.LENGTH_LONG).show();
        Toast.makeText(this, "modded by Jasmur \nwww.platinmods.com - Gamehacks & more!", Toast.LENGTH_LONG).show();
        Toast.makeText(this, "modded by Jasmur \nwww.platinmods.com - Gamehacks & more!", Toast.LENGTH_LONG).show();
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);

        if (requestCode == 102 && resultCode == -1) {
            if (Settings.canDrawOverlays(this)) {
                _startEngine();
                return;
            }

            AlertDialog.Builder builder = new AlertDialog.Builder(this, 5);
            builder.setMessage("We cannot continue without draw overlay permission!");
            builder.setCancelable(false);
            builder.setPositiveButton("OK", (dialog, which) -> System.exit(0));
            builder.create().show();
        }
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        finish();
    }

    @Override
    public void onRequestPermissionsResult(int requestCode, String[] permissions, int[] grantResults) {
        super.onRequestPermissionsResult(requestCode, permissions, grantResults);
        if (requestCode != 101)
            return;

        for (int i = 0; i < PERMISSIONS.length; i++) {
            if (grantResults[i] == PackageManager.PERMISSION_DENIED) {
                AlertDialog.Builder builder = new AlertDialog.Builder(this);
                builder.setMessage("We cannot continue without needed permission!");
                builder.setCancelable(false);
                builder.setPositiveButton("OK", (dialog, which) -> System.exit(0));
                builder.create().show();
            }
        }
    }
}