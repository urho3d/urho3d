package io.urho3d

import android.content.Context
import org.libsdl.app.SDLActivity
import java.io.File

open class UrhoActivity : SDLActivity() {

    companion object {
        private val regex = Regex("^lib(.*)\\.so$")

        @JvmStatic
        fun getLibraryNames(context: Context) = File(context.applicationInfo.nativeLibraryDir)
            .listFiles { _, it -> regex.matches(it) }!!
            .sortedBy { it.lastModified() }
            .map {
                regex.find(it.name)?.groupValues?.last() ?: throw IllegalStateException()
            }
    }

}
