#
# Copyright (c) 2008-2014 the Urho3D project.
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
#

require 'pathname'
require 'json'
if ENV['IOS']
  require 'time'
end

# Usage: rake sync (only intended to be used in a fork with remote 'upstream' set to urho3d/Urho3D)
desc 'Fetch and merge upstream urho3d/Urho3D to a Urho3D fork'
task :sync do
  system "cwb=`git symbolic-ref -q --short HEAD || git rev-parse --short HEAD`; export cwb && git fetch upstream && git checkout master && git pull && git merge -m 'Sync at #{Time.now.localtime}.' upstream/master && git push && git checkout $cwb" or abort
end

# Usage: rake scaffolding dir=/path/to/new/project/root [project=Scaffolding] [target=Main]
desc 'Create a new project using Urho3D as external library'
task :scaffolding do
  abort 'Usage: rake scaffolding dir=/path/to/new/project/root [project=Scaffolding] [target=Main]' unless ENV['dir']
  abs_path = (ENV['OS'] ? ENV['dir'][1, 1] == ':' : ENV['dir'][0, 1] == '/') ? ENV['dir'] : "#{Dir.pwd}/#{ENV['dir']}"
  project = ENV['project'] || 'Scaffolding'
  target = ENV['target'] || 'Main'
  scaffolding(abs_path, project, target)
  abs_path = Pathname.new(abs_path).realpath
  puts "\nNew project created in #{abs_path}\n\n"
  puts "You may need to first set 'URHO3D_HOME' environment variable or use 'URHO3D_HOME' build option to point to your Urho3D build tree or your custom Urho3D SDK installation location."
  puts "Please see http://urho3d.github.io/documentation/HEAD/_using_library.html for more detail. For example:\n\n"
  if ENV['OS']
    puts "set \"URHO3D_HOME=/path/to/Urho3D/build-tree/or/SDK\"\ncd #{abs_path}\nrake cmake URHO3D_LUAJIT=1\nrake make\n\n"
    puts "Alternatively you can call one of the batch files directly, such as, cmake_generic.bat ../native-Build -DURHO3D_LUAJIT=1 and build using VS IDE"
  else
    puts "export URHO3D_HOME=/path/to/Urho3D/build-tree/or/SDK\ncd #{abs_path}\nrake cmake URHO3D_LUAJIT=1\nrake make\n\n"
    puts "Alternatively you can call one of the shell scripts directly, such as, ./cmake_generic.sh ../native-Build -DURHO3D_LUAJIT=1 && cd ../native-Build && make"
  end
  puts "to get a similar result as the last two rake tasks above.\n\n"
end

# Usage: rake cmake [<generator>] [<platform>] [<option>=<value> [<option>=<value>]] [[<platform>_]build_tree=/path/to/build-tree] [fix_scm]
# e.g.: rake cmake clean android; or rake cmake android URHO3D_LIB_TYPE=SHARED; or rake cmake ios URHO3D_LUA=1 build_tree=~/ios-Build
#
# To avoid repeating the customized build tree locations, you can set and export them as environment variables.
# e.g.: export native_build_tree=~/custom-native-Build android_build_tree=~/custom-android-Build mingw_build_tree=~/custom-mingw-Build rpi_build_tree=~/custom-rpi-Build
#       rake cmake rpi URHO3D_LUAJIT=1 URHO3D_LUAJIT_AMALG=1 && rake make rpi
#       The RPI build tree will be generated in the ~/custom-rpi-Build and then build from there
desc 'Invoke one of the build scripts with the build tree location predetermined based on the target platform'
task :cmake do
  script = 'cmake_generic'
  platform = 'native'
  build_options = ''
  ARGV.each { |option|
    task option.to_sym do ; end; Rake::Task[option].clear   # No-op hack
    case option
    when 'cmake', 'generic'
      # do nothing
    when 'clean', 'codeblocks', 'eclipse', 'macosx', 'vs2008', 'vs2010', 'vs2012', 'vs2013'
      script = "cmake_#{option}" unless script == 'cmake_clean'
    when 'android', 'ios', 'mingw', 'rpi'
      platform = option
      build_options = "#{build_options} -D#{option == 'mingw' ? 'WIN32' : option.upcase}=1" unless script == 'cmake_clean'
      script = 'cmake_macosx' if option == 'ios'
      script = 'cmake_mingw' if option == 'mingw' && ENV['OS']
    when 'fix_scm'
      build_options = "#{build_options} --fix-scm" if script == 'cmake_eclipse'
    else
      build_options = "#{build_options} -D#{option}" unless /build_tree=.*/ =~ option || script == 'cmake_clean'
    end
  }
  build_tree = ENV["#{platform}_build_tree"] || ENV['build_tree'] || "../#{platform}-Build"
  system "./#{script}#{ENV['OS'] ? '.bat' : '.sh'} #{build_tree} #{build_options}" or abort
end

# Usage: rake make [<platform>] [<option>=<value> [<option>=<value>]] [[<platform>_]build_tree=/path/to/build-tree] [numjobs=8] [clean_first] [unfilter]
# e.g.: rake make android; or rake make android doc; or rake make ios config=Debug sdk=iphonesimulator build_tree=~/ios-Build
desc 'Build the generated project in its corresponding build tree'
task :make do
  numjobs = '-j' + (ENV['numjobs'] || '8')
  platform = 'native'
  cmake_build_options = ''
  build_options = ''
  unfilter = false
  ARGV.each { |option|
    task option.to_sym do ; end; Rake::Task[option].clear   # No-op hack
    case option
    when 'codeblocks', 'eclipse', 'generic', 'macosx', 'make', 'vs2008', 'vs2010', 'vs2012', 'vs2013'
      # do nothing
    when 'android', 'ios', 'mingw', 'rpi'
      platform = option
    when 'clean_first'
      cmake_build_options = "#{cmake_build_options} --clean-first"
    when 'unfilter'
      unfilter = true
    else
      if /(?:config|target)=.*/ =~ option
        cmake_build_options = "#{cmake_build_options} --#{option.gsub(/=/, ' ')}"
      elsif /(?:build_tree|numjobs)=.*/ !~ option
        build_options = "#{build_options} #{/=/ =~ option ? '-' + option.gsub(/=/, ' ') : option}"
      end
    end
  }
  build_tree = ENV["#{platform}_build_tree"] || ENV['build_tree'] || "../#{platform}-Build"
  if !Dir.glob("#{build_tree}/*.xcodeproj").empty?
    filter = !unfilter && system('xcpretty -v >/dev/null 2>&1') ? '|xcpretty -c && exit ${PIPESTATUS[0]}' : ''
  elsif !Dir.glob("#{build_tree}/*.sln").empty?
    filter = ''
  else
    build_options = "#{numjobs}#{build_options}"
    filter = ''
  end
  system "cd #{build_tree} && cmake --build . #{cmake_build_options} -- #{build_options} #{filter}" or abort
end

# Usage: rake android [parameter='--es pickedLibrary Urho3DPlayer'] [intent=.SampleLauncher] [package=com.github.urho3d] [success_indicator='Initialized engine'] [payload='sleep 30'] [api=19] [abi=armeabi-v7a] [avd=test_#{api}_#{abi}] [retries=10] [retry_interval=10]
desc 'Test run already installed APK in Android (virtual) device, default to Urho3D Samples APK if no parameter is given'
task :android do
  parameter = ENV['parameter'] || '--es pickedLibrary Urho3DPlayer'
  intent = ENV['intent'] || '.SampleLauncher'
  package = ENV['package'] || 'com.github.urho3d'
  success_indicator = ENV['success_indicator'] || 'Initialized engine'
  payload = ENV['payload'] || 'sleep 30'
  api = ENV['api'] || 19
  abi = ENV['abi'] || 'armeabi-v7a'
  avd = ENV['avd'] || "test_#{api}_#{abi}"
  retries = ENV['retries'] || 10 # minutes
  retry_interval = ENV['retry_interval'] || 10 # seconds
  android_prepare_device api, abi, avd or abort 'Failed to prepare Android (virtual) device for test run'
  android_wait_for_device retries, retry_interval or abort 'Failed to start Android (virtual) device'
  android_test_run parameter, intent, package, success_indicator, payload or abort "Failed to test run #{package}/#{intent}, make sure the APK has been installed"
end

# Usage: NOT intended to be used manually (if you insist then try: rake ci)
desc 'Configure, build, and test Urho3D project'
task :ci do
  # Unshallow the clone's history when necessary
  if ENV['CI'] && ENV['PACKAGE_UPLOAD'] && !ENV['RELEASE_TAG']
    system 'git fetch --unshallow' or abort 'Failed to unshallow cloned repository'
  end
  # Packaging always use Release configuration (temporary workaround due to Travis-CI insufficient memory, also use Release configuration when CI build runs on a bad VM)
  if ENV['PACKAGE_UPLOAD'] || ENV['BAD_VM']
    $configuration = 'Release'
    $testing = 0
  else
    $configuration = 'Debug'
    # Only 64-bit Linux environment with virtual framebuffer X server support and not MinGW build; or OSX build environment and not iOS build are capable to run tests
    $testing = (ENV['LINUX'] && !ENV['URHO3D_64BIT']) || (ENV['OSX'] && ENV['IOS'].to_i != 1) ? 1 : 0
    if $testing
      ENV['URHO3D_PREFIX_PATH'] = `pwd`.chomp + '/bin'
    end
  end
  # Define the build option string only when the override environment variable is given
  $build_options = "-DURHO3D_64BIT=#{ENV['URHO3D_64BIT']}" if ENV['URHO3D_64BIT']
  $build_options = "#{$build_options} -DURHO3D_OPENGL=#{ENV['URHO3D_OPENGL']}" if ENV['URHO3D_OPENGL']
  $build_options = "#{$build_options} -DANDROID_ABI=#{ENV['ABI']}" if ENV['ABI']
  $build_options = "#{$build_options} -DANDROID_NATIVE_API_LEVEL=#{ENV['API']}" if ENV['API']
  $build_options = "#{$build_options} -DANDROID=#{ENV['ANDROID']}" if ENV['ANDROID']
  $build_options = "#{$build_options} -DRPI=#{ENV['RPI']}" if ENV['RPI']
  $build_options = "#{$build_options} -DWIN32=#{ENV['WINDOWS']}" if ENV['WINDOWS']
  if ENV['XCODE']
    # xcodebuild
    xcode_ci
  else
    # GCC or Clang
    makefile_ci
  end
end

# Usage: NOT intended to be used manually (if you insist then try: GIT_NAME=... GIT_EMAIL=... GH_TOKEN=... rake ci_site_update)
desc 'Update site documentation to GitHub Pages'
task :ci_site_update do
  # Pull or clone
  system 'cd ../doc-Build 2>/dev/null && git pull -q -r || git clone --depth 1 -q https://github.com/urho3d/urho3d.github.io.git ../doc-Build' or abort 'Failed to pull/clone'
  # Update credits from Readme.txt to about.md
  system "ruby -lne 'BEGIN { credits = false }; puts $_ if credits; credits = true if /bugfixes by:/; credits = false if /^$/' Readme.txt |ruby -i -le 'credits = STDIN.read; puts ARGF.read.gsub(/(?<=bugfixes by\n).*?(?=##)/m, credits)' ../doc-Build/about.md" or abort 'Failed to update credits'
  # Setup doxygen to use minimal theme
  system "ruby -i -pe 'BEGIN { a = {%q{HTML_HEADER} => %q{minimal-header.html}, %q{HTML_FOOTER} => %q{minimal-footer.html}, %q{HTML_STYLESHEET} => %q{minimal-doxygen.css}, %q{HTML_COLORSTYLE_HUE} => 200, %q{HTML_COLORSTYLE_SAT} => 0, %q{HTML_COLORSTYLE_GAMMA} => 20, %q{DOT_IMAGE_FORMAT} => %q{svg}, %q{INTERACTIVE_SVG} => %q{YES}} }; a.each {|k, v| gsub(/\#{k}\s*?=.*?\n/, %Q{\#{k} = \#{v}\n}) }' ../Build/Docs/Doxyfile" or abort 'Failed to setup doxygen configuration file'
  system 'cp ../doc-Build/_includes/Doxygen/minimal-* ../Build/Docs' or abort 'Failed to copy minimal-themed template'
  release = ENV['RELEASE_TAG'] || 'HEAD'
  unless release == 'HEAD'
    system "mkdir -p ../doc-Build/documentation/#{release}" or abort 'Failed to create directory for new document version'
    system "ruby -i -pe 'gsub(/HEAD/, %q{#{release}})' ../Build/Docs/minimal-header.html" or abort 'Failed to update document version in YAML Front Matter block'
    append_new_release release, '../doc-Build/_data/urho3d.json' or abort 'Failed to add new release to document data file'
  end
  # Generate and sync doxygen pages
  system "cd ../Build && make -j$NUMJOBS doc >/dev/null 2>&1 && ruby -i -pe 'gsub(/(<\\/?h)3([^>]*?>)/, %q{\\14\\2}); gsub(/(<\\/?h)2([^>]*?>)/, %q{\\13\\2}); gsub(/(<\\/?h)1([^>]*?>)/, %q{\\12\\2})' Docs/html/_*.html && rsync -a --delete Docs/html/ ../doc-Build/documentation/#{release}" or abort 'Failed to generate/rsync doxygen pages'
  # Supply GIT credentials and push site documentation to urho3d/urho3d.github.io.git
  system "cd ../doc-Build && pwd && git config user.name $GIT_NAME && git config user.email $GIT_EMAIL && git remote set-url --push origin https://$GH_TOKEN@github.com/urho3d/urho3d.github.io.git && git add -A . && ( git commit -q -m \"Travis CI: site documentation update at #{Time.now.utc}.\n\nCommit: https://github.com/$TRAVIS_REPO_SLUG/commit/$TRAVIS_COMMIT\n\nMessage: $COMMIT_MESSAGE\" || true) && git push -q >/dev/null 2>&1" or abort 'Failed to update site'
  # Automatically give instruction to do packaging when API has changed, unless the instruction is already given in this commit
  if ENV['PACKAGE_UPLOAD']
    instruction = 'skip'
  else
    instruction = 'package'
  end
  if !ENV['RELEASE_TAG']
    # Supply GIT credentials and push API documentation to urho3d/Urho3D.git (the push may not be successful if remote master has already diverged)
    system 'pwd && git config user.name $GIT_NAME && git config user.email $GIT_EMAIL && git remote set-url --push origin https://$GH_TOKEN@github.com/$TRAVIS_REPO_SLUG.git && git add Docs/*API*'
    if system("git commit -q -m 'Travis CI: API documentation update at #{Time.now.utc}.\n[ci #{instruction}]'") && !ENV['PACKAGE_UPLOAD']
      bump_soversion 'Source/Urho3D/.soversion' or abort 'Failed to bump soversion'
      system "git add Source/Urho3D/.soversion && git commit --amend -q -m 'Travis CI: API documentation update at #{Time.now.utc}.\n[ci #{instruction}]'" or abort 'Failed to stage .soversion file'
    end
    system 'git push origin HEAD:master -q >/dev/null 2>&1' or abort 'Failed to update API documentation, most likely due to remote master has diverged, the API documentation update will be performed again in the subsequent CI build'
  end
end

# Usage: NOT intended to be used manually (if you insist then try: GIT_NAME=... GIT_EMAIL=... GH_TOKEN=... TRAVIS_BRANCH=... rake ci_rebase)
desc 'Rebase all CI mirror branches'
task :ci_rebase do
  system 'git config user.name $GIT_NAME && git config user.email $GIT_EMAIL && git remote set-url --push origin https://$GH_TOKEN@github.com/$TRAVIS_REPO_SLUG.git'
  baseline = ENV['RELEASE_TAG'] || "origin/#{ENV['TRAVIS_BRANCH']}"
  enable = /\[ci rebase\]/ =~ ENV['COMMIT_MESSAGE']
  [ 'Android-CI', 'RPI-CI', 'OSX-CI' ].each { |ci| ci_branch = ENV['RELEASE_TAG'] || ENV['TRAVIS_BRANCH'] == 'master' ? ci : "#{ENV['TRAVIS_BRANCH']}-#{ci}"; system "if git fetch origin #{ci_branch}:#{ci_branch} 2>/dev/null; then git rebase #{baseline} #{ci_branch} && git push -qf -u origin #{ci_branch} >/dev/null 2>&1; elif [ #{enable} ]; then git checkout -b #{ci_branch} #{ENV['TRAVIS_BRANCH']} && rm .travis.yml && wget -q https://raw.githubusercontent.com/#{ENV['TRAVIS_REPO_SLUG']}/#{ci}/.travis.yml && cat <<EOF >README.md && git add -A . && git commit -m 'For Travis CI - switch CI build to use #{ci.split('-').first} build environment.' && git push -qf -u origin #{ci_branch} >/dev/null 2>&1; fi
This is a mirror branch which is constantly being \"rebased\" from #{ENV['TRAVIS_BRANCH']} branch. Please DO NOT checkout from this mirror branch! The purpose of this mirror branch is to perform CI build using #{ci.split('-').first} build environment on Travis-CI.org. See #{ENV['TRAVIS_BRANCH']} branch for CI build result using Ubuntu Linux build environment.

[![Build Status](https://travis-ci.org/#{ENV['TRAVIS_REPO_SLUG']}.png?branch=#{ci_branch})](https://travis-ci.org/#{ENV['TRAVIS_REPO_SLUG']}?branch=#{ci_branch})
EOF" or abort "Failed to rebase #{ci_branch} mirror branch" }
end

# Usage: NOT intended to be used manually (if you insist then try: rake ci_package_upload)
desc 'Make binary package and upload it to a designated central hosting server'
task :ci_package_upload do
  if ENV['XCODE']
    $configuration = 'Release'
    $testing = 0
  end
  # Generate the documentation if necessary
  if ENV['SITE_UPDATE']
    if File.exist?('.site_updated')
      # Skip if site is already updated before
      ENV['SITE_UPDATE'] = nil
    end
  else
    system 'echo Generate documentation'
    if ENV['XCODE']
      xcode_build(ENV['IOS'], '../Build/Urho3D.xcodeproj', 'doc', '>/dev/null') or abort 'Failed to generate documentation'
    else
      system 'cd ../Build && make -j$NUMJOBS doc >/dev/null' or abort 'Failed to generate documentation'
    end
  end
  # Make the package
  if ENV['IOS']
    # Skip Mach-O universal binary build if Travis-CI VM took too long to get here, as otherwise overall build time may exceed 50 minutes time limit
    if ENV['CI_START_TIME'] then
      elapsed_time = (Time.now - Time.parse(ENV['CI_START_TIME'])) / 60
      puts "\niOS checkpoint reached, elapsed time: #{elapsed_time}\n\n"
    end
    if !ENV['CI_START_TIME'] || elapsed_time < 15 # minutes
      # Build Mach-O universal binary consisting of iphoneos (universal ARM archs including 'arm64' if 64-bit is enabled) and iphonesimulator (i386 arch and also x86_64 arch if 64-bit is enabled)
      system 'echo Rebuild Urho3D library as Mach-O universal binary'
      xcode_build(0, '../Build/Urho3D.xcodeproj', 'Urho3D_universal') or abort 'Failed to build Mach-O universal binary'
    end
    # There is a bug in CMake/CPack that causes the 'package' target failed to build for IOS platform, workaround by calling cpack directly
    system 'cd ../Build && cpack -G TGZ 2>/dev/null' or abort 'Failed to make binary package'
  elsif ENV['XCODE']
    xcode_build(ENV['IOS'], '../Build/Urho3D.xcodeproj', 'package') or abort 'Failed to make binary package'
  else
    if ENV['ANDROID'] && !ENV['NO_SDK_SYSIMG']
      system "cd ../Build && android update project -p . -t $(android list target |grep android-$API |cut -d ' ' -f2) && ant debug" or abort 'Failed to make Urho3D Samples APK'
    end
    if ENV['URHO3D_USE_LIB64_RPM']
      system "cd ../Build && cmake . -DURHO3D_USE_LIB64_RPM=#{ENV['URHO3D_USE_LIB64_RPM']}" or abort 'Failed to reconfigure to generate 64-bit RPM package'
    end
    system 'cd ../Build && make package' or abort 'Failed to make binary package'
  end
  # Determine the upload location
  setup_digital_keys
  if !ENV['RELEASE_TAG']
    upload_dir = "/home/frs/project/#{ENV['TRAVIS_REPO_SLUG']}/Snapshots"
    if ENV['SITE_UPDATE']
      # Download source packages from GitHub
      system "export SNAPSHOT_VER=$(git describe $TRAVIS_COMMIT |ruby -pe 'gsub(/-(?!g)/, %q{.})'); wget -q https://github.com/$TRAVIS_REPO_SLUG/tarball/$TRAVIS_COMMIT -O Urho3D-$SNAPSHOT_VER-Source-snapshot.tar.gz && wget -q https://github.com/$TRAVIS_REPO_SLUG/zipball/$TRAVIS_COMMIT -O Urho3D-$SNAPSHOT_VER-Source-snapshot.zip" or abort 'Failed to get source packages'
      # Only keep the snapshots from the last 30 revisions
      system "for v in $(sftp urho-travis-ci@frs.sourceforge.net <<EOF |tr ' ' '\n' |grep Urho3D- |cut -d '-' -f1,2 |uniq |tail -n +31
cd #{upload_dir}
ls -1r
bye
EOF
); do echo rm #{upload_dir}/${v}*; done |sftp -b - urho-travis-ci@frs.sourceforge.net" or abort 'Failed to housekeep snapshots'
    end
  else
    upload_dir = "/home/frs/project/#{ENV['TRAVIS_REPO_SLUG']}/#{ENV['RELEASE_TAG']}"
    if ENV['SITE_UPDATE']
      # Download source packages from GitHub
      system 'wget -q https://github.com/$TRAVIS_REPO_SLUG/archive/$RELEASE_TAG.tar.gz -O Urho3D-$RELEASE_TAG-Source.tar.gz && wget -q https://github.com/$TRAVIS_REPO_SLUG/archive/$RELEASE_TAG.zip -O Urho3D-$RELEASE_TAG-Source.zip' or abort 'Failed to get source packages'
    end
    # Make sure the release directory exists remotely, do this in all the build jobs as we don't know which one would start uploading first
    system "sftp urho-travis-ci@frs.sourceforge.net <<EOF >/dev/null 2>&1
mkdir #{upload_dir}
bye
EOF" or abort 'Failed to create release directory remotely'
  end
  if ENV['SITE_UPDATE']
    # Upload the source package
    system "scp Urho3D-* urho-travis-ci@frs.sourceforge.net:#{upload_dir}" or abort 'Failed to upload source package'
    # Sync readme and license files, just in case they are updated in the repo
    system 'for f in Readme.txt License.txt; do mtime=$(git log --format=%ai -n1 $f); touch -d "$mtime" $f; done' or abort 'Failed to acquire file modified time'
    system 'rsync -e ssh -az Readme.txt License.txt urho-travis-ci@frs.sourceforge.net:/home/frs/project/$TRAVIS_REPO_SLUG' or abort 'Failed to sync readme and license files'
    # Mark that the site has been updated
    File.open('.site_updated', 'w') {}
  end
  # Upload the package
  system "scp ../Build/Urho3D-* urho-travis-ci@frs.sourceforge.net:#{upload_dir} && rm ../Build/Urho3D-*" or abort 'Failed to upload binary package'
end

def scaffolding(dir, project = 'Scaffolding', target = 'Main')
  build_script = <<EOF
# Set project name
project (#{project})

# Set minimum version
cmake_minimum_required (VERSION 2.8.6)

if (COMMAND cmake_policy)
    cmake_policy (SET CMP0003 NEW)
    if (CMAKE_VERSION VERSION_GREATER 2.8.12 OR CMAKE_VERSION VERSION_EQUAL 2.8.12)
        # INTERFACE_LINK_LIBRARIES defines the link interface
        cmake_policy (SET CMP0022 NEW)
    endif ()
    if (CMAKE_VERSION VERSION_GREATER 3.0.0 OR CMAKE_VERSION VERSION_EQUAL 3.0.0)
        # Disallow use of the LOCATION target property - therefore we set to OLD as we still need it
        cmake_policy (SET CMP0026 OLD)
        # MACOSX_RPATH is enabled by default
        cmake_policy (SET CMP0042 NEW)
    endif ()
endif ()

# Set CMake modules search path
set (CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMake/Modules)

# Include Urho3D CMake common module
include (Urho3D-CMake-common)

# Find Urho3D library
find_package (Urho3D REQUIRED)
include_directories (${URHO3D_INCLUDE_DIRS})

# Define target name
set (TARGET_NAME #{target})

# Define source files
define_source_files ()

# Setup target with resource copying
setup_main_executable ()

# Setup test cases
if (URHO3D_ANGELSCRIPT)
    add_test (NAME ExternalLibAS COMMAND ${TARGET_NAME} Scripts/12_PhysicsStressTest.as -w -timeout ${URHO3D_TEST_TIME_OUT})
endif ()
if (URHO3D_LUA)
    add_test (NAME ExternalLibLua COMMAND ${TARGET_NAME} LuaScripts/12_PhysicsStressTest.lua -w -timeout ${URHO3D_TEST_TIME_OUT})
endif ()
EOF
  # TODO: Rewrite in pure Ruby when it supports symlink creation on Windows platform
  if ENV['OS']
    system("@echo off && mkdir #{dir}\\bin && copy Source\\Tools\\Urho3DPlayer\\Urho3DPlayer.* #{dir} >nul && (for %f in (*.bat Rakefile) do mklink #{dir}\\%f %cd%\\%f >nul) && mklink /D #{dir}\\CMake %cd%\\CMake && (for %d in (CoreData,Data) do mklink /D #{dir}\\bin\\%d %cd%\\bin\\%d >nul)") && File.write("#{dir}/CMakeLists.txt", build_script) or abort 'Failed to create new project using Urho3D as external library'
  else
    system("bash -c \"mkdir -p #{dir}/bin && cp Source/Tools/Urho3DPlayer/Urho3DPlayer.* #{dir} && for f in {.,}*.sh Rakefile CMake; do ln -sf `pwd`/\\$f #{dir}; done && ln -sf `pwd`/bin/{Core,}Data #{dir}/bin\"") && File.write("#{dir}/CMakeLists.txt", build_script) or abort 'Failed to create new project using Urho3D as external library'
  end
end

def makefile_ci
  if ENV['WINDOWS'] && ENV['CI']
    # MinGW package on Ubuntu 12.04 LTS does not come with d3dcompiler.h file which is required by our CI build with URHO3D_OPENGL=0.
    # Temporarily workaround the problem by downloading the missing header from Ubuntu 14.04 LTS source package.
    if ENV['URHO3D_OPENGL']
      system "sudo wget -P $(echo |$MINGW_PREFIX-gcc -v -E - 2>&1 |grep -B 1 'End of search list' |head -1) http://bazaar.launchpad.net/~ubuntu-branches/ubuntu/trusty/mingw-w64/trusty/download/package-import%40ubuntu.com-20130624192537-vzn12bb7qd5w3iy8/d3dcompiler.h-20120402093420-bk10a737hzitlkgj-65/d3dcompiler.h" or abort 'Failed to download d3dcompiler.h header'
    end
    # LuaJIT on MinGW build is not possible on Ubuntu 12.04 LTS as its GCC cross-compiler version is too old. Fallback to use Lua library instead.
    jit = ''
    amalg = ''
  elsif ENV['ANDROID'] && ENV['ABI'] == 'arm64-v8a'
    # The upstream LuaJIT library does not support this Android ABI at the moment, fallback to use Lua library instead
    jit = ''
    amalg = ''
  else
    jit = 'JIT'
    amalg = '-DURHO3D_LUAJIT_AMALG=1'
  end
  system "./cmake_generic.sh ../Build -DURHO3D_LIB_TYPE=$URHO3D_LIB_TYPE #{$build_options} -DURHO3D_LUA#{jit}=1 #{amalg} -DURHO3D_SAMPLES=1 -DURHO3D_TOOLS=1 -DURHO3D_EXTRAS=1 -DURHO3D_TESTING=#{$testing} -DCMAKE_BUILD_TYPE=#{$configuration}" or abort 'Failed to configure Urho3D library build'
  if ENV['AVD'] && !ENV['PACKAGE_UPLOAD']   # Skip APK test run when packaging
      android_prepare_device ENV['API'], ENV['ABI'], ENV['AVD'] or abort 'Failed to prepare Android (virtual) device for test run'
  end
  test = $testing == 1 ? '&& make test' : ''
  system "cd ../Build && make -j$NUMJOBS #{test}" or abort 'Failed to build or test Urho3D library'
  # Create a new project on the fly that uses newly built Urho3D library in the build tree
  scaffolding "../Build/generated/UsingBuildTree"
  system "cd ../Build/generated/UsingBuildTree && echo '\nExternal project referencing Urho3D library in its build tree' && ./cmake_generic.sh . #{$build_options} -DURHO3D_HOME=../.. -DURHO3D_LUA#{jit}=1 -DURHO3D_TESTING=#{$testing} -DCMAKE_BUILD_TYPE=#{$configuration} && make -j$NUMJOBS #{test}" or abort 'Failed to configure/build/test temporary project using Urho3D as external library' 
  ENV['DESTDIR'] = ENV['HOME'] || Dir.home
  puts "\nInstalling Urho3D SDK to #{ENV['DESTDIR']}/usr/local...\n"  # The default CMAKE_INSTALL_PREFIX is /usr/local
  system 'cd ../Build && make -j$NUMJOBS install >/dev/null' or abort 'Failed to install Urho3D SDK'
  # Create a new project on the fly that uses newly installed Urho3D SDK
  scaffolding "../Build/generated/UsingSDK"
  system "export URHO3D_HOME=~/usr/local && cd ../Build/generated/UsingSDK && echo '\nExternal project referencing Urho3D SDK' && ./cmake_generic.sh . #{$build_options} -DURHO3D_LUA#{jit}=1 -DURHO3D_TESTING=#{$testing} -DCMAKE_BUILD_TYPE=#{$configuration} && make -j$NUMJOBS #{test}" or abort 'Failed to configure/build/test temporary project using Urho3D as external library'
  # Make, deploy, and test run Android APK in an Android (virtual) device
  if ENV['AVD'] && !ENV['PACKAGE_UPLOAD']
    system "echo '\nTest deploying and running Urho3D Samples APK...' && cd ../Build && android update project -p . -t $( android list target |grep android-$API |cut -d ' ' -f2 ) && ant debug" or abort 'Failed to make Urho3D Samples APK'
    if android_wait_for_device ENV['CI'] ? 1 : 10 # minutes
      system "cd ../Build && ant -Dadb.device.arg='-s #{$specific_device}' installd" or abort 'Failed to deploy Urho3D Samples APK'
      android_test_run or abort 'Failed to test run Urho3D Samples APK'
    else
      puts 'Skipped test running Urho3D Samples APK as emulator failed to start in time'
    end
  end
end

def android_find_device api = nil, abi = nil
  # Return the previously found matching device or if not found yet then try to find the matching device now
  return $specific_device if $specific_device
  wait = api ? '' : 'wait-for-device'
  $specific_api = api.to_s if api
  $specific_abi = abi.to_s if abi
  for i in `adb #{wait} devices |tail -n +2`.split "\n"
    device = i.split.first
    if `adb -s #{device} wait-for-device shell getprop ro.build.version.sdk`.chomp == $specific_api && `adb -s #{device} shell getprop ro.product.cpu.abi`.chomp == $specific_abi
      return $specific_device = device
    end
  end
  nil
end

def android_prepare_device api, abi = 'armeabi-v7a', name = 'test'
  system 'if ! ps |grep -cq adb; then adb start-server; fi'
  if !android_find_device api, abi
    # Don't have any matching (virtual) device attached, try to attach the named device (create the named device as AVD if necessary)
    if !system "android list avd |grep -cq 'Name: #{name}$'"
      system "echo 'no' |android create avd -n #{name} -t android-#{api} --abi #{abi}" or abort "Failed to create '#{name}' Android virtual device"
    end
    system "if [ $CI ]; then export OPTS='-no-skin -no-audio -no-window -no-boot-anim -gpu off'; else export OPTS='-gpu on'; fi; emulator -avd #{name} $OPTS &"
  end
  return 0
end

def android_wait_for_device retries = -1, retry_interval = 10, package = 'android.process.acore'  # Waiting for HOME by default
  # Wait until the indicator process is running or it is killed externally by user via Ctrl+C or when it exceeds the number of retries (if the retries parameter is provided)
  str = "\nWaiting for device..."
  thread = Thread.new { android_find_device }; sleep 0.5
  process_ready = false
  retries = retries * 60 / retry_interval unless retries == -1
  until retries == 0
    if thread.status == false
      thread.join
      break if process_ready
      process_ready = thread = Thread.new { `adb -s #{$specific_device} shell 'until ps |grep -c #{package} >/dev/null; do sleep #{retry_interval}; done; while ps |grep -c bootanimation >/dev/null; do sleep 1; done'` }; sleep 0.5
      next
    end
    print str; str = '.'; $stdout.flush   # Flush the standard output stream in case it is buffered to prevent Travis-CI into thinking that the build/test has stalled
    sleep retry_interval
    retries -= 1 if retries > 0
  end
  puts "\n\n" if str == '.'; $stdout.flush
  return retries == 0 ? nil : 0
end

def android_test_run parameter = '--es pickedLibrary Urho3DPlayer', intent = '.SampleLauncher', package = 'com.github.urho3d', success_indicator = 'Added resource path /apk/CoreData/', payload = 'sleep 30'
  # The device should have been found at this point
  return nil unless $specific_device
  # Capture adb's stdout and interpret it because adb neither uses stderr nor returns proper exit code on error
  begin
    IO.popen("adb -s #{$specific_device} shell <<EOF
# Try to unlock the device just in case it is locked
input keyevent 82; input keyevent 4
# Clear the log
logcat -c
# Start the app
am start -a android.intent.action.MAIN -n #{package}/#{intent} #{parameter}
# Wait until the process is running
until ps |grep -c #{package} 1>/dev/null; do sleep 1; done
# Execute the payload
#{payload}
# Exit and stop the app
input keyevent 4 && am force-stop #{package}
# Dump the log
logcat -d
# Bye bye
exit
##
EOF") { |stdout| echo = false; while output = stdout.gets do if echo && /#\s#/ !~ output then puts output else echo = true if /^##/ =~ output end; return nil if /^error/i =~ output end }
    # Result of the test run is determined based on the presence of the success indicator string in the log
    system "adb -s #{$specific_device} logcat -d |grep -cq '#{success_indicator}'"
  rescue
    nil
  end
end

def xcode_ci
  if ENV['IOS']
    # IOS platform does not support LuaJIT
    jit = ''
    amalg = ''
    deployment_target = "-DIPHONEOS_DEPLOYMENT_TARGET=#{ENV['DEPLOYMENT_TARGET']}"
  else
    jit = 'JIT'
    amalg = '-DURHO3D_LUAJIT_AMALG=1'
    deployment_target = "-DCMAKE_OSX_DEPLOYMENT_TARGET=#{ENV['DEPLOYMENT_TARGET']}"
  end
  system "./cmake_macosx.sh ../Build -DIOS=$IOS #{deployment_target} -DURHO3D_LIB_TYPE=$URHO3D_LIB_TYPE #{$build_options} -DURHO3D_LUA#{jit}=1 #{amalg} -DURHO3D_SAMPLES=1 -DURHO3D_TOOLS=1 -DURHO3D_EXTRAS=1 -DURHO3D_TESTING=#{$testing}" or abort 'Failed to configure Urho3D library build'
  xcode_build(ENV['IOS'], '../Build/Urho3D.xcodeproj') or abort 'Failed to build or test Urho3D library'
  # Create a new project on the fly that uses newly built Urho3D library in the build tree
  scaffolding "../Build/generated/UsingBuildTree"
  system "cd ../Build/generated/UsingBuildTree && echo '\nExternal project referencing Urho3D library in its build tree' && ./cmake_macosx.sh . -DIOS=$IOS #{deployment_target} #{$build_options} -DURHO3D_HOME=../.. -DURHO3D_LUA#{jit}=1 -DURHO3D_TESTING=#{$testing}" or abort 'Failed to configure temporary project using Urho3D as external library'
  xcode_build(ENV['IOS'], '../Build/generated/UsingBuildTree/Scaffolding.xcodeproj') or abort 'Failed to build/test temporary project using Urho3D as external library'
  ENV['DESTDIR'] = ENV['HOME'] || Dir.home
  puts "\nInstalling Urho3D SDK to #{ENV['DESTDIR']}/usr/local...\n"  # The default CMAKE_INSTALL_PREFIX is /usr/local
  xcode_build(ENV['IOS'], '../Build/Urho3D.xcodeproj', 'install', '>/dev/null') or abort 'Failed to install Urho3D SDK'
  # Create a new project on the fly that uses newly installed Urho3D SDK
  scaffolding "../Build/generated/UsingSDK"
  system "export URHO3D_HOME=~/usr/local && cd ../Build/generated/UsingSDK && echo '\nExternal project referencing Urho3D SDK' && ./cmake_macosx.sh . -DIOS=$IOS #{deployment_target} #{$build_options} -DURHO3D_LUA#{jit}=1 -DURHO3D_TESTING=#{$testing}" or abort 'Failed to configure temporary project using Urho3D as external library'
  xcode_build(ENV['IOS'], '../Build/generated/UsingSDK/Scaffolding.xcodeproj') or abort 'Failed to build/test temporary project using Urho3D as external library'
end

def xcode_build(ios, project, target = 'ALL_BUILD', extras = '')
  sdk = ios.to_i == 1 ? '-sdk iphonesimulator' : ''
  # Use xcpretty to filter output from xcodebuild when building
  system "xcodebuild -project #{project} -target #{target} -configuration #{$configuration} #{sdk} |xcpretty -c #{extras} && exit ${PIPESTATUS[0]}" or return nil
  if $testing == 1 && target == 'ALL_BUILD'     # Disable testing for other targets such as 'doc', 'package', etc
    # Use vanila xcodebuild when testing as its output is instantaneous (ensure Travis-CI does not kill the process during testing)
    system "xcodebuild -project #{project} -target RUN_TESTS -configuration #{$configuration} #{sdk} #{extras}" or return nil
  end
  return 0
end

def append_new_release release, filename
  begin
    urho3d_hash = JSON.parse File.read filename
    unless urho3d_hash['releases'].last == release
      urho3d_hash['releases'] << release
    end
    File.open filename, 'w' do |file|
      file.puts urho3d_hash.to_json
    end
    return 0
  rescue
    nil
  end
end

def bump_soversion filename
  begin
    version = File.read(filename).split '.'
    bump_version version, 2
    File.open filename, 'w' do |file|
      file.puts version.join '.'
    end
    return 0
  rescue
    nil
  end
end

def bump_version version, index
  if index > 0 && version[index].to_i == 255
    version[index] = 0
    bump_version version, index - 1
  else
    version[index] = version[index].to_i + 1
  end
end

def setup_digital_keys
  system 'mkdir -p ~/.ssh && chmod 700 ~/.ssh' or abort 'Failed to create ~/.ssh directory'
  system 'cat <<EOF >>~/.ssh/known_hosts
frs.sourceforge.net,216.34.181.57 ssh-rsa AAAAB3NzaC1yc2EAAAABIwAAAQEA2uifHZbNexw6cXbyg1JnzDitL5VhYs0E65Hk/tLAPmcmm5GuiGeUoI/B0eUSNFsbqzwgwrttjnzKMKiGLN5CWVmlN1IXGGAfLYsQwK6wAu7kYFzkqP4jcwc5Jr9UPRpJdYIK733tSEmzab4qc5Oq8izKQKIaxXNe7FgmL15HjSpatFt9w/ot/CHS78FUAr3j3RwekHCm/jhPeqhlMAgC+jUgNJbFt3DlhDaRMa0NYamVzmX8D47rtmBbEDU3ld6AezWBPUR5Lh7ODOwlfVI58NAf/aYNlmvl2TZiauBCTa7OPYSyXJnIPbQXg6YQlDknNCr0K769EjeIlAfY87Z4tw==
EOF' or abort 'Failed to append frs.sourceforge.net server public key to known_hosts'
  # Workaround travis encryption key size limitation. Rather than using the solution in their FAQ (using AES to encrypt/decrypt the file and check in the encrypted file into repo), our solution is more pragmatic. The private key below is incomplete. Only the missing portion is encrypted. Much less secure than the original 2048-bit RSA has to offer but good enough for our case. 
  system 'cat <<EOF >~/.ssh/id_rsa
-----BEGIN RSA PRIVATE KEY-----
MIIEpQIBAAKCAQEAnZGzFEypdXKY3KDT0Q3NLY4Bv74yKgJ4LIgbXothx8w4CfM0
VeWBL/AE2iRISEWGB07LruM9y+U/wt58WlCVu001GuJuvXwWenlljsvH8qQlErYi
oXlCwAeVVeanILGL8CPS7QlyzOwwnVF6NdcmfDJjTthBVFbvHrWGo5if86zcZyMR
2BB5QVEr5fU0yOPFp0+2p7J3cA6HQSKwjUiDtJ+lM62UQp7InCCT3qeh5KYHQcYb
KVJTyj5iycVuBujHDwNAivLq82ojG7LcKjP+Ia8fblardCOQyFk6pSDM79NJJ2Dg
3ZbYIJeUmqSqFhRW/13Bro7Z1aNGrdh/XZkkHwIDAQABAoIBACHcBFJxYtzVIloO
yVWcFKIcaO3OLjNu0monWVJIu1tW3BfvRijLJ6aoejJyJ4I4RmPdn9FWDZp6CeiT
LL+vn21fWvELBWb8ekwZOCSmT7IpaboKn4h5aUmgl4udA/73iC2zVQkQxbWZb5zu
vEdDk4aOwV5ZBDjecYX01hjjnEOdZHGJlF/H/Xs0hYX6WDG3/r9QCJJ0nfd1/Fk2
zdbZRtAbyRz6ZHiYKnFQ441qRRaEbzunkvTBEwu9iqzlE0s/g49LJL0mKEp7rt/J
4iS3LZTQbJNx5J0ti8ZJKHhvoWb5RJxNimwKvVHC0XBZKTiLMrhnADmcpjLz53F8
$SF_KEY
sx27yCaeBeKXV0tFOeZmgK664VM9EgesjIX4sVOJ5mA3xBJBOtz9n66LjoIlIM58
dvsAnJt7MUBdclL/RBHEjbUxgGBDcazfWSuJe0sGczhnXMN94ox4MSECgYEAx5cv
cs/2KurjtWPanDGSz71LyGNdL/xQrAud0gi49H0tyYr0XmzNoe2CbZ/T5xGSZB92
PBcz4rnHQ/oujo/qwjNpDD0xVLEU70Uy/XiY5/v2111TFC4clfE/syZPywKAztt3
y2l5z+QdsNigRPDhKw+7CFYaAnYBEISxR6nabT8CgYEAqHrM8fdn2wsCNE6XvkZQ
O7ZANHNIKVnaRqW/8HW7EFAWQrlQTgzFbtR4uNBIqAtPsvwSx8Pk652+OR1VKfSv
ya3dtqY3rY/ErXWyX0nfPQEbYj/oh8LbS6zPw75yIorP3ACIwMw3GRNWIvkdAGTn
BMUgpWHUDLWWpWRrSzNi90ECgYEAkxxzQ6vW5OFGv17/NdswO+BpqCTc/c5646SY
ScRWFxbhFclOvv5xPqYiWYzRkmIYRaYO7tGnU7jdD9SqVjfrsAJWrke4QZVYOdgG
cl9eTLchxLGr15b5SOeNrQ1TCO4qZM3M6Wgv+bRI0h2JW+c0ABpTIBzehOvXcwZq
6MhgD98CgYEAtOPqc4aoIRUy+1oijpWs+wU7vAc8fe4sBHv5fsv7naHuPqZgyQYY
32a54xZxlsBw8T5P4BDy40OR7fu+6miUfL+WxUdII4fD3grlIPw6bpNE0bCDykv5
RLq28S11hDrKf/ZetXNuIprfTlhl6ISBy+oWQibhXmFZSxEiXNV6hCQ=
-----END RSA PRIVATE KEY-----
EOF' or abort 'Failed to create user private key to id_rsa'
  system 'chmod 600 ~/.ssh/id_rsa' or abort 'Failed to change id_rsa file permission'
end

# Load custom rake scripts
Dir['.rake/*.rake'].each { |r| load r }

# vi: set ts=2 sw=2 expandtab:
