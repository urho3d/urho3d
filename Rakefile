require 'pathname'

# Usage: rake scaffolding dir=/path/to/new/project/root
desc 'Create a new project using Urho3D as external library'
task :scaffolding do
  abort 'Usage: rake scaffolding dir=/path/to/new/project/root' unless ENV['dir']
  abs_path = ENV['dir'][0, 1] == '/' ? ENV['dir'] : "#{Dir.pwd}/#{ENV['dir']}"
  scaffolding abs_path
  abs_path = Pathname.new(abs_path).realpath
  puts "\nNew project created in #{abs_path}\n\n"
  puts "To build the new project, you may need to first define and export either 'URHO3D_HOME' or 'URHO3D_INSTALL_PREFIX' environment variable"
  puts "Please see http://urho3d.github.io/documentation/a00004.html for more detail. For example:\n\n"
  puts "$ URHO3D_HOME=#{Dir.pwd}; export URHO3D_HOME\n$ cd #{abs_path}\n$ ./cmake_gcc.sh -DENABLE_64BIT=1 -DENABLE_LUAJIT=1\n$ cd Build\n$ make\n\n"
end

# Usage: NOT intended to be used manually (if you insist then try: rake travis_ci)
desc 'Configure, build, and test Urho3D project'
task :travis_ci do
  if ENV['WINDOWS']
    # LuaJIT on MinGW build is not possible on Ubuntu 12.04 LTS as its cross-compiler version is too old. Fallback to use Lua library instead.
    jit = ''
    amalg = ''
    # Lua on MinGW build requires tolua++ tool to be built natively first
    system 'MINGW_PREFIX= ./cmake_gcc.sh -DURHO3D_LIB_TYPE=$URHO3D_LIB_TYPE -DENABLE_64BIT=$ENABLE_64BIT -DENABLE_LUA=1 -DENABLE_TOOLS=0' or abort 'Failed to configure native build for tolua++ target'
    system 'cd Build/ThirdParty/toluapp/src/bin && make' or abort 'Failed to build tolua++ tool'
  else
    jit = 'JIT'
    amalg = '-DENABLE_LUAJIT_AMALG=1'
  end
  system "./cmake_gcc.sh -DURHO3D_LIB_TYPE=$URHO3D_LIB_TYPE -DENABLE_64BIT=$ENABLE_64BIT -DENABLE_LUA#{jit}=1 #{amalg} -DENABLE_SAMPLES=1 -DENABLE_TOOLS=1 -DENABLE_EXTRAS=1 -DENABLE_TESTING=1 -DCMAKE_BUILD_TYPE=Debug" or abort 'Failed to configure Urho3D library build'
  if ENV['ANDROID']
    # LuaJIT on Android build requires tolua++ and buildvm-android tools to be built natively first
    system 'cd Build/ThirdParty/toluapp/src/bin && make' or abort 'Failed to build tolua++ tool'
    system 'cd Build/ThirdParty/LuaJIT/generated/buildvm-android && make' or abort 'Failed to build buildvm-android tool'
    # Reconfigure Android build one more time now that we have the tools built
    ENV['SKIP_NATIVE'] = '1'
    system './cmake_gcc.sh' or abort 'Failed to reconfigure Urho3D library for Android build'
    platform_prefix = 'android-'
  elsif ENV['WINDOWS']
    platform_prefix = 'mingw-'
  else
    platform_prefix = ''
  end
  # Only 64-bit Linux environment with virtual framebuffer X server support and not MinGW build are capable to run tests
  if ENV['ENABLE_64BIT'].to_i == 1 and ENV['WINDOWS'].to_i != 1
    test = '&& make test'
  else
    test = ''
  end
  system "cd #{platform_prefix}Build && make #{test}" or abort 'Failed to build or test Urho3D library'
  # Create a new project on the fly that uses newly built Urho3D library
  scaffolding "#{platform_prefix}Build/generated/externallib"
  system "URHO3D_HOME=`pwd`; export URHO3D_HOME && cd #{platform_prefix}Build/generated/externallib && echo '\nUsing Urho3D as external library in external project' && ./cmake_gcc.sh -DENABLE_64BIT=$ENABLE_64BIT -DENABLE_LUA#{jit}=1 -DENABLE_TESTING=1 -DCMAKE_BUILD_TYPE=Debug && cd #{platform_prefix}Build && make #{test}" or abort 'Failed to configure/build/test temporary project using Urho3D as external library' 
end

# Usage: NOT intended to be used manually (if you insist then try: GIT_NAME=... GIT_EMAIL=... GH_TOKEN=... TRAVIS_BRANCH=master SITE_UPDATE=1 rake travis_ci_site_update)
desc 'Update site documentation to GitHub Pages'
task :travis_ci_site_update do
  # Skip documentation update if one of the following conditions is met
  if ENV['TRAVIS_PULL_REQUEST'].to_i > 0 or ENV['TRAVIS_BRANCH'] != 'master' or ENV['SITE_UPDATE'] != '1'
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
  system "msg=`git log --format=%B -n 1 $TRAVIS_COMMIT`; export msg && cd doc-Build && pwd && git config user.name '#{ENV['GIT_NAME']}' && git config user.email '#{ENV['GIT_EMAIL']}' && git remote set-url --push origin https://#{ENV['GH_TOKEN']}@github.com/urho3d/urho3d.github.io.git && git add -A . && git commit -q -m \"Travis CI: site documentation update at #{Time.now.utc}.\n\nCommit: https://github.com/urho3d/Urho3D/commit/$TRAVIS_COMMIT\n\nMessage: $msg\" && git push -q >/dev/null 2>&1"
  # Supply GIT credentials and push API documentation to urho3d/Urho3D.git (the push may not be successful if detached HEAD is not a fast forward of remote master)
  system "pwd && git config user.name '#{ENV['GIT_NAME']}' && git config user.email '#{ENV['GIT_EMAIL']}' && git remote set-url --push origin https://#{ENV['GH_TOKEN']}@github.com/urho3d/Urho3D.git && git add Docs/*API* && git commit -q -m 'Travis CI: API documentation update at #{Time.now.utc}.\n[ci skip]' && git push origin HEAD:master -q >/dev/null 2>&1"
end

def scaffolding(dir)
  system "bash -c \"mkdir -p #{dir}/{Source,Bin} && cp Source/Tools/Urho3DPlayer/Urho3DPlayer.* #{dir}/Source && for f in {.,}*.sh; do ln -sf `pwd`/\\$f #{dir}; done && ln -sf `pwd`/Bin/{Core,}Data #{dir}/Bin\" && cat <<EOF >#{dir}/Source/CMakeLists.txt
# Set project name
project (Scaffolding)

# Set minimum version
cmake_minimum_required (VERSION 2.8.6)

if (COMMAND cmake_policy)
    cmake_policy (SET CMP0003 NEW)
endif ()

# Set CMake modules search path
set (CMAKE_MODULE_PATH
    \\$ENV{URHO3D_HOME}/Source/CMake/Modules
    \\$ENV{URHO3D_INSTALL_PREFIX}/share/Urho3D/CMake/Modules
    \\${CMAKE_INSTALL_PREFIX}/share/Urho3D/CMake/Modules
    CACHE PATH \"Path to Urho3D-specific CMake modules\")

# Include Urho3D cmake module
include (Urho3D-CMake-magic)

# Find Urho3D library
find_package (Urho3D REQUIRED)
include_directories (\\${URHO3D_INCLUDE_DIRS})

# Define target name
set (TARGET_NAME Main)

# Define source files
define_source_files ()

# Setup target with resource copying
setup_main_executable ()

# Setup test cases
add_test (NAME ExternalLibAS COMMAND \\${TARGET_NAME} Data/Scripts/12_PhysicsStressTest.as -w -timeout \\${TEST_TIME_OUT})
add_test (NAME ExternalLibLua COMMAND \\${TARGET_NAME} Data/LuaScripts/12_PhysicsStressTest.lua -w -timeout \\${TEST_TIME_OUT})
EOF" or abort 'Failed to create new project using Urho3D as external library'
end
