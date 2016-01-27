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

import android.app.ListActivity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.view.Window;
import android.view.WindowManager;
import android.widget.ArrayAdapter;
import android.widget.ListView;

public class SampleLauncher extends ListActivity {

    public static final String LIBRARY_NAMES = "libraryNames";
    public static final String PICKED_LIBRARY = "pickedLibrary";
    private static final int OBTAINING_LIBNAMES = 1;

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        // Start Urho3D activity with the intention for obtaining the library name(s), except when a library is already being picked externally
        startActivityForResult(new Intent(this, Urho3D.class).putExtra(PICKED_LIBRARY, getIntent().getStringExtra(PICKED_LIBRARY)), OBTAINING_LIBNAMES);

        requestWindowFeature(Window.FEATURE_NO_TITLE);
        getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN, WindowManager.LayoutParams.FLAG_FULLSCREEN);

        // Prepare a list view for picking the sample library names
        ArrayAdapter<String> adapter = new ArrayAdapter<String>(this, R.layout.samples_list_text_view);
        setContentView(R.layout.samples_list);
        setListAdapter(adapter);
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        // The cancel result code means there are no multiple library names to choose from
        if (OBTAINING_LIBNAMES != requestCode || RESULT_CANCELED == resultCode)
            return;

        // Populate the list view with library names as pickable items
        String[] libraryNames = data.getStringArrayExtra(LIBRARY_NAMES);
        @SuppressWarnings("unchecked")
        ArrayAdapter<String> adapter = (ArrayAdapter<String>) getListAdapter();
        for (final String name : libraryNames)
            adapter.add(name);
    }

    @Override
    protected void onListItemClick(ListView l, View v, int position, long id) {
        // Start Urho3D activity with the intention to load the picked library name
        @SuppressWarnings("unchecked")
        ArrayAdapter<String> adapter = (ArrayAdapter<String>) getListAdapter();
        startActivity(new Intent(this, Urho3D.class).putExtra(PICKED_LIBRARY, adapter.getItem(position)));
    }

}
