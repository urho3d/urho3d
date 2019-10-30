//
// Copyright (c) 2008-2019 the Urho3D project.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

package com.github.urho3d.launcher

import com.github.urho3d.UrhoActivity
import android.widget.Toast
import org.json.JSONArray
import org.json.JSONException
import org.json.JSONObject
import android.app.ActivityManager
import android.content.Intent
import android.content.pm.PackageInfo
import android.content.pm.PackageManager
import android.net.Uri
import android.util.Log
import android.util.DisplayMetrics;
import android.content.*;
import android.view.*;
import android.os.*;
import java.util.Locale;
import android.provider.Settings;

class MainActivity : UrhoActivity() {

    companion object {
        const val argument = "argument"
    }

    private lateinit var arguments: List<String>

    override fun getArguments() = arguments.toTypedArray()

    override fun onLoadLibrary(libraryNames: MutableList<String>) {
        // All runtime shared libraries must always be loaded if available
        val regex = Regex("^(?:Urho3D|.+_shared)\$")
        libraryNames.retainAll { regex.matches(it) }

        // Parse the argument string
        val argumentString = intent.getStringExtra(argument)
        if (argumentString != null) arguments = argumentString.split(':')
        else throw IllegalArgumentException("The MainActivity requires an argument to start")

        // Must add the chosen sample library to the last of the list
        libraryNames.add(arguments[0])

        super.onLoadLibrary(libraryNames)
    }
    
    fun showToast(js:JSONObject) {
        try {
            val text = js.getString("text")
            val toast = Toast.makeText(this, "", Toast.LENGTH_SHORT)
            toast.setText(text)
            toast.setDuration(if (js.has("lengthLong") && js.getBoolean("lengthLong")) Toast.LENGTH_LONG else Toast.LENGTH_SHORT)
            toast.show()
        } catch (e:JSONException) {}
    }   
    // battery info part
    private val mBatInfoReceiver:BroadcastReceiver = object:BroadcastReceiver() {
        override fun onReceive(ctxt:Context, intent:Intent) {
            try {
                val js = JSONObject()
                val level = intent.getIntExtra(BatteryManager.EXTRA_LEVEL, 0)
                val scale = intent.getIntExtra(BatteryManager.EXTRA_SCALE, 100)
                val status = intent.getIntExtra(BatteryManager.EXTRA_STATUS, 0)
                val chargePlug = intent.getIntExtra(BatteryManager.EXTRA_PLUGGED, -1)
                js.put("level", Math.round(level.toFloat() / scale.toFloat() * 100.0))
                js.put("charging", status == BatteryManager.BATTERY_STATUS_CHARGING || status == BatteryManager.BATTERY_STATUS_FULL)
                js.put("usbCharge", chargePlug == BatteryManager.BATTERY_PLUGGED_USB)
                js.put("acCharge", chargePlug == BatteryManager.BATTERY_PLUGGED_AC)
                notifyGame("Battery", "status", js)
            } catch (e:JSONException) {}
        }
    }

    fun startReceiveBatteryStatus(@Suppress("UNUSED_PARAMETER") js:JSONObject) {
        this.registerReceiver(this.mBatInfoReceiver, IntentFilter(Intent.ACTION_BATTERY_CHANGED))
    }

    fun getSystemInfo(@Suppress("UNUSED_PARAMETER") js:JSONObject) {
        val js = JSONObject()
        try {
            js.put("language", Locale.getDefault().toString())
            val dm = DisplayMetrics()
            getWindowManager().getDefaultDisplay().getMetrics(dm)
            js.put("dpix", dm.xdpi)
            js.put("dpiy", dm.ydpi)
            val actManager = getSystemService(Context.ACTIVITY_SERVICE) as ActivityManager
            val memInfo = ActivityManager.MemoryInfo()
            actManager.getMemoryInfo(memInfo)
            js.put("totalMemory", memInfo.totalMem / 1024 / 1024)
            js.put("release", Build.VERSION.RELEASE)
            js.put("sdk", Build.VERSION.SDK_INT)
            js.put("model", Build.MODEL)
            js.put("device", Build.DEVICE)
            js.put("manufacturer", Build.MANUFACTURER)
            js.put("product", Build.PRODUCT)
            js.put("package", getPackageName())
            js.put("deviceId", Settings.Secure.getString(this.getContentResolver(), Settings.Secure.ANDROID_ID))
            try {
                val pInfo = getPackageManager().getPackageInfo(getPackageName(), 0)
                js.put("versionName", pInfo.versionName)
                if (android.os.Build.VERSION.SDK_INT >= Build.VERSION_CODES.P)
                    js.put("versionCode", pInfo.getLongVersionCode().and(0xFFFFFFFFL).toInt())
                else
                    js.put("versionCode", pInfo.versionCode)
            } catch (e:PackageManager.NameNotFoundException) {}
        } catch (e:JSONException) {}
        notifyGame("SysInfo", "dataReaded", js)
    }

    fun openUrl(js:JSONObject) {
        try {
            val urls = js.getString("url").split("\t")
            for (i in urls.indices) {
                try {
                    startActivity(Intent(Intent.ACTION_VIEW, Uri.parse(urls[i])))
                    break
                } catch (e:ActivityNotFoundException) {}
            }
        } catch (e:JSONException) {
            return
        }
    }

    fun shareText(js:JSONObject) {
        try {
            val i = Intent(Intent.ACTION_SEND)
            i.setType("text/plain")
            i.putExtra(Intent.EXTRA_SUBJECT, js.getString("subject"))
            i.putExtra(Intent.EXTRA_TEXT, js.getString("text"))
            startActivity(Intent.createChooser(i, js.getString("title")))
        } catch (e:Exception) {}
    }
}
