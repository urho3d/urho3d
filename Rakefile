require "rubygems"

# Usage: NOT intended to be used manually (if you insist then try: GIT_NAME=... GIT_EMAIL=... GH_TOKEN=... TRAVIS_BRANCH=master rake travis)
desc 'Update site documentation to GitHub Pages'
task :travis do
  # Skip documentation update if one of the following conditions is met
  if ENV['TRAVIS_PULL_REQUEST'].to_i > 0 or ENV['TRAVIS_BRANCH'] != 'master' or ENV['TEST_LIB_TYPE'] == 'SHARED'
    next
  end
  # Pull or clone
  system 'cd doc-Build 2>/dev/null && git pull -q -r || git clone -q https://github.com/urho3d/urho3d.github.io.git doc-Build' or abort 'Failed to pull/clone'
  # Update credits from Readme.txt to about.md
  system "ruby -lne 'BEGIN { credits = false }; puts $_ if credits; credits = true if /bugfixes by:/; credits = false if /^$/' Readme.txt |ruby -i -le 'credits = STDIN.read; puts ARGF.read.gsub(/(?<=bugfixes by\n).*?(?=##)/m, credits)' doc-Build/about.md" or abort 'Failed to update credits'
  # Setup doxygen to use minimal theme
  system "ruby -i -pe 'BEGIN { a = {%q{HTML_HEADER} => %q{minimal-header.html}, %q{HTML_FOOTER} => %q{minimal-footer.html}, %q{HTML_STYLESHEET} => %q{minimal-doxygen.css}, %q{HTML_COLORSTYLE_HUE} => 200, %q{HTML_COLORSTYLE_SAT} => 0, %q{HTML_COLORSTYLE_GAMMA} => 20, %q{DOT_IMAGE_FORMAT} => %q{svg}, %q{INTERACTIVE_SVG} => %q{YES}} }; a.each {|k, v| gsub(/\#{k}\s*?=.*?\n/, %Q{\#{k} = \#{v}\n}) }' Docs/Doxyfile" or abort 'Failed to setup doxygen configuration file'
  system 'cp doc-Build/_includes/Doxygen/minimal-* Docs' or abort 'Failed to copy minimal-themed template'
  # Generate and sync doxygen pages
  system 'cd Build && make doc >/dev/null 2>&1 && rsync -a --delete ../Docs/html/ ../doc-Build/documentation' or abort 'Failed to generate/rsync doxygen pages'
  # Supply GIT credentials and push site documentation to urho3d/urho3d.github.io.git
  system "msg=`git log --format=%B -n 1 $TRAVIS_COMMIT`; export msg && cd doc-Build && git config user.name '#{ENV['GIT_NAME']}' && git config user.email '#{ENV['GIT_EMAIL']}' && git remote set-url --push origin https://#{ENV['GH_TOKEN']}@github.com/urho3d/urho3d.github.io.git && git add -A . && git commit -q -m \"Travis CI: site documentation update at #{Time.now.utc}.\n\nCommit: https://github.com/urho3d/Urho3D/commit/$TRAVIS_COMMIT\n\nMessage: $msg\" && git push -q >/dev/null 2>&1" or abort 'Failed or nothing to push'
  # Supply GIT credentials and push API documentation to urho3d/Urho3D.git
  system "git config user.name '#{ENV['GIT_NAME']}' && git config user.email '#{ENV['GIT_EMAIL']}' && git remote set-url --push origin https://#{ENV['GH_TOKEN']}@github.com/urho3d/Urho3D.git && git pull && git add Docs/*API* && git commit -q -m 'Travis CI: API documentation update at #{Time.now.utc}.\n[ci skip]' && git push origin HEAD:master -q >/dev/null 2>&1"
end
