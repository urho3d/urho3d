require "rubygems"

# Usage: NOT intended to be used manually (if you insist then try: GIT_NAME=... GIT_EMAIL=... GH_TOKEN=... rake travis)
desc 'Update site documentation to GitHub Pages'
task :travis do
  # Skip documentation update if it is a pull request
  if ENV['TRAVIS_PULL_REQUEST'].to_i > 0
    next
  end
  # Pull or clone
  system 'cd doc-Build 2>/dev/null && git pull -q -r || git clone -q https://github.com/urho3d/urho3d.github.io.git doc-Build'
  # Update credits from Readme.txt to about.md
  system "ruby -lne 'BEGIN { credits = false }; puts $_ if credits; credits = true if /bugfixes by:/; credits = false if /^$/' Readme.txt |ruby -i -le 'BEGIN { credits = STDIN.read }; puts ARGF.read.gsub(/(?<=bugfixes by\n).*?(?=##)/m, credits)' doc-Build/about.md"
  # Sync generated doxygen pages (the trailing '/' is significant)
  # \todo Do this without leaving file changes history in GIT
  system 'rsync -a --delete Docs/html/ doc-Build/documentation'
  # Supply GIT credentials for pushing to GitHub
  system "cd doc-Build && git config user.name '#{ENV['GIT_NAME']}'"
  system "cd doc-Build && git config user.email '#{ENV['GIT_EMAIL']}'"
  system 'cd doc-Build && git config credential.helper "store --file=.git/credentials"'
  File.open('doc-Build/.git/credentials', 'w') do |f|
    f.write("https://#{ENV['GH_TOKEN']}:@github.com")
  end
  system "cd doc-Build && git add -A && git commit -q -a -m 'Travis CI automated site documentation update at #{Time.now.utc}.' && git push -q"
  # Debug start
  system "echo GIT_NAME='#{ENV['GIT_NAME']}'"
  system "echo GIT_EMAIL='#{ENV['GIT_EMAIL']}'"
  system "GH_TOKEN='#{ENV['GH_TOKEN']}' echo GH_TOKEN=${GH_TOKEN:0:5}"
  system 'cd doc-Build && git config --list'
  # Debug end
  File.delete 'doc-Build/.git/credentials'
end
