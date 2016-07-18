package com.github.urho3d;

import android.app.ExpandableListActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.ExpandableListView;
import android.widget.SimpleExpandableListAdapter;

import java.util.*;

public class ScriptPicker extends ExpandableListActivity {

    private static final String LANG = "lang";
    private static final String INFO = "info";
    private static final String SCRIPT = "script";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        // Prepare an expandable list view for picking the sample script names
        @SuppressWarnings("unchecked")
        final HashMap<String, ArrayList<String>> scripts = (HashMap<String, ArrayList<String>>) getIntent().getSerializableExtra(Urho3D.SCRIPTS);
        setListAdapter(new SimpleExpandableListAdapter(this,
                new ArrayList<Map<String, String>>() {{
                    for (final String lang : scripts.keySet()) {
                        add(new HashMap<String, String>() {{
                            put(LANG, lang);
                            put(INFO, "Click to expand/collapse");
                        }});
                    }
                }}, android.R.layout.simple_expandable_list_item_2, new String[]{LANG, INFO}, new int[]{android.R.id.text1, android.R.id.text2},
                new ArrayList<List<Map<String, String>>>() {{
                    for (final String lang : scripts.keySet()) {
                        add(new ArrayList<Map<String, String>>() {{
                            // Sort to make non-numbered samples on top
                            ArrayList<String> sortedScripts = scripts.get(lang);
                            Collections.sort(sortedScripts, new Comparator<String>() {
                                private String sortName(String name) {
                                    return name.contains("_") ? name : "00_" + name;
                                }

                                @Override
                                public int compare(String lhs, String rhs) {
                                    return sortName(lhs).compareTo(sortName(rhs));
                                }
                            });
                            for (final String script : sortedScripts) {
                                // Filter to exclude directory names from being listed
                                if (script.contains(".")) {
                                    add(new HashMap<String, String>() {{
                                        put(SCRIPT, script);
                                    }});
                                }
                            }
                        }});
                    }
                }}, R.layout.samples_list_text_view, new String[]{SCRIPT}, new int[]{android.R.id.text1}));
        setContentView(R.layout.scripts_list);
    }

    @Override
    public boolean onChildClick(ExpandableListView parent, View v, int groupPosition, int childPosition, long id) {
        @SuppressWarnings("unchecked")
        Map<String, String> map = (Map<String, String>) getExpandableListAdapter().getChild(groupPosition, childPosition);
        setResult(RESULT_OK, getIntent().putExtra(Urho3D.PICKED_SCRIPT, map.get(SCRIPT)));
        finish();
        return true;
    }

}
