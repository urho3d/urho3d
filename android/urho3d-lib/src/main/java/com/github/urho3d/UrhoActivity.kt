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

package com.github.urho3d

import android.content.Context
import org.libsdl.app.SDLActivity
import java.io.File
import org.json.JSONArray
import org.json.JSONException
import org.json.JSONObject
import android.os.Handler
import android.os.Message
import android.util.Log
import android.os.Bundle

open class UrhoActivity : SDLActivity() {
    private fun processData(data: String) {
        try {
            val js = JSONObject(data)
            val methodName = js.getString("method")
            val method = javaClass.getDeclaredMethod(methodName, JSONObject::class.java!!)
            method.setAccessible(true)
            method.invoke(this, js)
        } catch (e:ClassCastException) {
            Log.e("Urho3D", "onUnhandledMessage ClassCastException", e)
        } catch (e:JSONException) {
            Log.e("Urho3D", "onUnhandledMessage JSONException", e)
        } catch (e:SecurityException) {
            Log.e("Urho3D", "onUnhandledMessage SecurityException", e)
        } catch (e:NoSuchMethodException) {
            Log.e("Urho3D", "onUnhandledMessage NoSuchMethodException", e)
        } catch (e:Exception) {
            Log.e("Urho3D", "onUnhandledMessage Exception", e)
        }
    }
    fun notifyGame(source:String, event:String, params:JSONObject) {
        try {
            params.put("source", source)
            params.put("event", event)
            nativeUserActivityCallback(params.toString())
        } catch (e:JSONException) {}
    }
    fun notifyGame(source:String, event:String) {
        notifyGame(source, event, JSONObject())
    }
    private val mHandler = object:Handler() {
        override fun handleMessage(msg:Message) {
            processData(msg.obj as String)
        }
    }
    
    companion object {
        private val regex = Regex("^lib(.*)\\.so$")

        @JvmStatic
        fun getLibraryNames(context: Context) = File(context.applicationInfo.nativeLibraryDir)
                    .listFiles { _, it -> regex.matches(it) }
                    .sortedBy { it.lastModified() }
                    .map {
                        regex.find(it.name)?.groupValues?.last() ?: throw IllegalStateException()
                    }
        @JvmStatic
        external fun nativeUserActivityCallback(json:String)
        @JvmStatic
        fun postDataToUI(data:String) {
            val msg = (SDLActivity.mSingleton as UrhoActivity).mHandler.obtainMessage()
            msg.obj = data
            (SDLActivity.mSingleton as UrhoActivity).mHandler.sendMessage(msg)
        }
    }
}
