//
// Copyright (c) 2008-2016 the Urho3D project.
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

package com.github.urho3d;

import android.content.Intent;
import android.content.res.AssetManager;
import android.util.Log;
import org.libsdl.app.SDLActivity;

import java.io.IOException;
import java.util.*;

public class Urho3D extends SDLActivity {

    public static final String SCRIPTS = "scripts";
    public static final String PICKED_SCRIPT = "pickedScript";
    private static final String TAG = "Urho3D";
    private static final int OBTAINING_SCRIPT = 1;
    private static String[] mArguments = new String[0];

    @Override
    protected String[] getArguments() {
        return mArguments;
    }

    @Override
    protected boolean onLoadLibrary(ArrayList<String> libraryNames) {
        // Ensure "Urho3D" (in case of Urho3D shared lib type is used) and "Urho3DPlayer" are being sorted to the top of the list 
        Collections.sort(libraryNames, new Comparator<String>() {
            private String sortName(String name) {
                return name.startsWith("Urho3D") ? "00_" + name : name;
            }

            @Override
            public int compare(String lhs, String rhs) {
                return sortName(lhs).compareTo(sortName(rhs));
            }
        });

        // Urho3D shared library must always be loaded if available, so exclude it from return result and all list operations below 
        int startIndex = "Urho3D".equals(libraryNames.get(0)) ? 1 : 0;

        // Determine the intention
        Intent intent = getIntent();
        String pickedLibrary = intent.getStringExtra(SampleLauncher.PICKED_LIBRARY);
        if (pickedLibrary == null) {
            // Intention for obtaining library names
            String[] array = libraryNames.subList(startIndex, libraryNames.size()).toArray(new String[libraryNames.size() - startIndex]);
            if (array.length > 1) {
                setResult(RESULT_OK, intent.putExtra(SampleLauncher.LIBRARY_NAMES, array));

                // End Urho3D activity lifecycle
                finish();

                // Return false to indicate no library is being loaded yet
                return false;
            } else {
                // There is only one library available, so cancel the intention for obtaining the library name and by not returning any result
                // However, since we have already started Urho3D activity, let's the activity runs its whole lifecycle by falling through to call the super implementation 
                setResult(RESULT_CANCELED);
            }
        } else {
            // Intention for loading a picked library name (and remove all others)
            libraryNames.subList(startIndex, libraryNames.size()).clear();
            mArguments = pickedLibrary.split(":");
            libraryNames.add(mArguments[0]);
            if ("Urho3DPlayer".equals(mArguments[0]) && mArguments.length == 1) {
                // Urho3DPlayer needs a script name to play
                try {
                    final AssetManager assetManager = getContext().getAssets();
                    HashMap<String, ArrayList<String>> scripts = new HashMap<String, ArrayList<String>>(2) {{
                        put("AngleScript", new ArrayList<String>(Arrays.asList(assetManager.list("Data/Scripts"))));
                        put("Lua", new ArrayList<String>(Arrays.asList(assetManager.list("Data/LuaScripts"))));
                    }};
                    startActivityForResult(new Intent(this, ScriptPicker.class).putExtra(SCRIPTS, scripts), OBTAINING_SCRIPT);
                } catch (IOException e) {
                    Log.e(TAG, "Could not scan assets directory for playable scripts", e);
                }
            }
        }

        return super.onLoadLibrary(libraryNames);
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        if (OBTAINING_SCRIPT != requestCode || RESULT_CANCELED == resultCode)
            return;
        String script = data.getStringExtra(PICKED_SCRIPT);
        script = (script.endsWith(".as") ? "Scripts/" : "LuaScripts/") + script;
        mArguments = new String[]{mArguments[0], script};
    }

}
