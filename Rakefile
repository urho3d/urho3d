require "rubygems"

# Usage: NOT intended to be used manually (if you insist then try: GIT_NAME=... GIT_EMAIL=... GH_TOKEN=... TRAVIS_BRANCH=master rake travis)
desc 'Update site documentation to GitHub Pages'
task :travis do
  # Skip documentation update if it is a pull request or if it is a commit in topic branch
  if ENV['TRAVIS_PULL_REQUEST'].to_i > 0 or ENV['TRAVIS_BRANCH'] != 'master'
    next
  end
  # Pull or clone
  system 'cd doc-Build 2>/dev/null && git pull -q -r || git clone -q https://github.com/urho3d/urho3d.github.io.git doc-Build'
  # Update credits from Readme.txt to about.md
  system "ruby -lne 'BEGIN { credits = false }; puts $_ if credits; credits = true if /bugfixes by:/; credits = false if /^$/' Readme.txt |ruby -i -le 'BEGIN { credits = STDIN.read }; puts ARGF.read.gsub(/(?<=bugfixes by\n).*?(?=##)/m, credits)' doc-Build/about.md"
  # Setup doxygen to use minimal theme
  system "ruby -i -pe 'BEGIN { a = {%q{HTML_HEADER} => %q{minimal-header.html}, %q{HTML_FOOTER} => %q{minimal-footer.html}, %q{HTML_STYLESHEET} => %q{minimal-doxygen.css}, %q{HTML_COLORSTYLE_HUE} => 200, %q{HTML_COLORSTYLE_SAT} => 0, %q{HTML_COLORSTYLE_GAMMA} => 20, %q{DOT_IMAGE_FORMAT} => %q{svg}, %q{INTERACTIVE_SVG} => %q{YES}} }; a.each {|k, v| gsub(/\#{k}\s*?=.*?\n/, %Q{\#{k} = \#{v}\n}) }' Docs/Doxyfile"
  system 'cp doc-Build/_includes/Doxygen/minimal-* Docs'
  # Generate and sync doxygen pages
  system 'cd Build && make doc >/dev/null 2>&1 && rsync -a --delete ../Docs/html/ ../doc-Build/documentation'
  # Supply GIT credentials and push to GitHub
  system "cd doc-Build && git config user.name '#{ENV['GIT_NAME']}' && git config user.email '#{ENV['GIT_EMAIL']}' && git remote set-url --push origin https://#{ENV['GH_TOKEN']}@github.com/urho3d/urho3d.github.io.git && git add -A && git commit -q -a -m 'Travis CI: site documentation update at #{Time.now.utc}.' && git push -q"
end
