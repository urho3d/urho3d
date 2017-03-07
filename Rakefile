#
# Copyright (c) 2008-2017 the Urho3D project.
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
require 'yaml'

### Tasks for general users ###

# Usage: rake scaffolding dir=/path/to/new/project/root [project=Scaffolding] [target=Main]
desc 'Create a new project using Urho3D as external library'
task :scaffolding do
  abort 'Usage: rake scaffolding dir=/path/to/new/project/root [project=Scaffolding] [target=Main]' unless ENV['dir']
  project = ENV['project'] || 'Scaffolding'
  target = ENV['target'] || 'Main'
  abs_path = scaffolding ENV['dir'], project, target
  puts "\nNew project created in #{abs_path}.\n\n"
  puts "In order to configure and generate your project build tree you may need to first set"
  puts "'URHO3D_HOME' environment variable or use 'URHO3D_HOME' build option to point to the"
  puts "Urho3D project build tree or custom Urho3D SDK installation location.\n\n"
  puts "Please see https://urho3d.github.io/documentation/HEAD/_using_library.html for more detail.\nFor example:\n\n"
  puts "$ cd #{abs_path}\n$ rake cmake URHO3D_HOME=/path/to/Urho3D/build-tree\n$ rake make\n\n"
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
  # TODO: Need to find a way to automatically populate the array with all the Urho3D supported build options, at the moment it only contains those being used in CI
  ['URHO3D_64BIT', 'URHO3D_LIB_TYPE', 'URHO3D_STATIC_RUNTIME', 'URHO3D_PCH', 'URHO3D_BINDINGS', 'URHO3D_OPENGL', 'URHO3D_D3D11', 'URHO3D_TESTING', 'URHO3D_TEST_TIMEOUT', 'URHO3D_UPDATE_SOURCE_TREE', 'URHO3D_TOOLS', 'URHO3D_DEPLOYMENT_TARGET', 'URHO3D_USE_LIB64_RPM', 'CMAKE_BUILD_TYPE', 'CMAKE_OSX_DEPLOYMENT_TARGET', 'IOS', 'IPHONEOS_DEPLOYMENT_TARGET', 'WIN32', 'MINGW', 'ANDROID', 'ANDROID_ABI', 'ANDROID_NATIVE_API_LEVEL', 'ANDROID_TOOLCHAIN_NAME', 'RPI', 'RPI_ABI', 'ARM', 'ARM_ABI_FLAGS', 'WEB', 'EMSCRIPTEN_SHARE_DATA', 'EMSCRIPTEN_SHARE_JS', 'EMSCRIPTEN_WASM', 'EMSCRIPTEN_EMRUN_BROWSER'].each { |var|
    ARGV << "#{var}=\"#{ENV[var]}\"" if ENV[var] && !ARGV.find { |arg| /#{var}=/ =~ arg }
  }
  ARGV.each { |option|
    task option.to_sym do ; end; Rake::Task[option].clear   # No-op hack
    case option
    when 'cmake', 'generic'
      # do nothing
    when 'clean', 'codeblocks', 'codelite', 'eclipse', 'ninja', 'vs2008', 'vs2010', 'vs2012', 'vs2013', 'vs2015', 'xcode'
      script = "cmake_#{option}" unless script == 'cmake_clean'
    when 'android', 'arm', 'ios', 'mingw', 'rpi', 'web'
      platform = option
      build_options = "#{build_options} -D#{option == 'mingw' ? 'WIN32' : option.upcase}=1" unless script == 'cmake_clean'
      script = 'cmake_xcode' if option == 'ios'
      script = 'cmake_mingw' if option == 'mingw' && ENV['OS']
    when 'fix_scm'
      build_options = "#{build_options} --fix-scm" if script == 'cmake_eclipse'
    else
      build_options = "#{build_options} -D#{option}" unless /build_tree=.*/ =~ option || script == 'cmake_clean'
    end
  }
  build_tree = ENV["#{platform}_build_tree"] || ENV['build_tree'] || "../#{platform}-Build"
  if ENV['OS']
    # CMake claims mingw32-make does not build correctly with MSYS shell in the PATH env-var and prevents build tree generation if so
    # Our CI on Windows host requires MSYS shell, so we cannot just simply remove it from the PATH globally
    # Instead, we modify the PATH env-var locally here just before invoking the CMake generator
    ENV['PATH'] = ENV['PATH'].gsub /Git\\usr\\bin/, 'GoAway'
  else
    ccache_envvar = ENV['CCACHE_SLOPPINESS'] ? '' : 'CCACHE_SLOPPINESS=pch_defines,time_macros'   # Only attempt to do the right thing when user hasn't done it
    ccache_envvar = "#{ccache_envvar} CCACHE_COMPRESS=1" unless ENV['CCACHE_COMPRESS']
  end
  system "#{ccache_envvar} ./#{script}#{ENV['OS'] ? '.bat' : '.sh'} \"#{build_tree}\" #{build_options}" or abort
end

# Usage: rake make [<platform>] [<option>=<value> [<option>=<value>]] [[<platform>_]build_tree=/path/to/build-tree] [numjobs=n] [clean_first] [unfilter]
# e.g.: rake make android; or rake make android doc; or rake make ios config=Debug sdk=iphonesimulator build_tree=~/ios-Build
desc 'Build the generated project in its corresponding build tree'
task :make do
  numjobs = ENV['numjobs'] || ''
  platform = 'native'
  cmake_build_options = ''
  build_options = ''
  unfilter = false
  ['config', 'target', 'sdk', 'ARCHS', 'ARGS', 'unfilter', 'verbosity'].each { |var|
    ARGV << "#{var}=\"#{ENV[var]}\"" if ENV[var] && !ARGV.find { |arg| /#{var}=/ =~ arg }
  }
  ARGV.each { |option|
    task option.to_sym do ; end; Rake::Task[option].clear   # No-op hack
    case option
    when 'codeblocks', 'codelite', 'eclipse', 'generic', 'make', 'ninja', 'vs2008', 'vs2010', 'vs2012', 'vs2013', 'vs2015', 'xcode'
      # do nothing
    when 'android', 'arm', 'ios', 'mingw', 'rpi', 'web'
      platform = option
    when 'clean_first'
      cmake_build_options = "#{cmake_build_options} --clean-first"
    when 'unfilter'
      unfilter = true
    else
      if /(?:config|target)=.*/ =~ option
        cmake_build_options = "#{cmake_build_options} --#{option.gsub(/=/, ' ')}"
      elsif /(?:ARCHS|ARGS)=.*/ =~ option
        # The ARCHS option is only applicable for xcodebuild, useful to specify a non-default arch to build when in Debug build configuration where ONLY_ACTIVE_ARCH is set to YES
        # The ARGS option is only applicable for make, useful to pass extra arguments while building a specific target, e.g. ARGS=-VV when the target is 'test' to turn on extra verbose mode
        build_options = "#{build_options} #{option}"
      elsif /unfilter=\W*?(?<unfilter_value>\w+)/ =~ option
        unfilter = !(/(?:true|yes|1)/i =~ unfilter_value).nil?
      elsif /verbosity=.*/ =~ option
        # The verbosity option is only applicable for msbuild when building RUN_TESTS, useful to specify the verbosity of the test output
        if ARGV.include?('target=RUN_TESTS')
          build_options = "#{build_options} /#{option.gsub(/=/, ':')}"
          unfilter = true
        end
      elsif /(?:build_tree|numjobs)=.*/ !~ option
        build_options = "#{build_options} #{/=/ =~ option ? '-' + option.gsub(/=/, ' ') : option}"
      end
    end
  }
  build_tree = ENV["#{platform}_build_tree"] || ENV['build_tree'] || "../#{platform}-Build"
  if ENV['OS']
    # While calling mingw-32-make itself does not require the PATH to be altered (as long as it is not inside an MSYS shell),
    # we have to do it again here because our build system invokes CMake internally to generate things on-the-fly as part of the build process
    ENV['PATH'] = ENV['PATH'].gsub /Git\\usr\\bin/, 'GoAway'
  else
    ccache_envvar = ENV['CCACHE_SLOPPINESS'] ? '' : 'CCACHE_SLOPPINESS=pch_defines,time_macros'   # Only attempt to do the right thing when user hasn't done it
    ccache_envvar = "#{ccache_envvar} CCACHE_COMPRESS=1" unless ENV['CCACHE_COMPRESS']
  end
  if !Dir.glob("#{build_tree}/*.xcodeproj").empty?
    # xcodebuild
    if !numjobs.empty?
      build_options = "-jobs #{numjobs}#{build_options}"
    end
    filter = !unfilter && !ARGV.include?('target=RUN_TESTS') && system('xcpretty -v >/dev/null 2>&1') ? '|xcpretty -c && exit ${PIPESTATUS[0]}' : ''
  elsif !Dir.glob("#{build_tree}\\*.sln".gsub(/\\/, '/')).empty?
    # msbuild
    numjobs = ":#{numjobs}" unless numjobs.empty?
    build_options = "/maxcpucount#{numjobs}#{build_options}"
    filter = unfilter ? '' : '/nologo /verbosity:minimal'
    filter = filter  + ' /logger:"C:\Program Files\AppVeyor\BuildAgent\Appveyor.MSBuildLogger.dll"' if ENV['APPVEYOR']
  elsif !Dir.glob("#{build_tree}/*.ninja").empty?
    # ninja
    if !numjobs.empty?
      build_options = "-j#{numjobs}#{build_options}"
    end
    filter = ''
  else
    # make
    if numjobs.empty?
      case RUBY_PLATFORM
      when /linux/
        numjobs = (platform == 'web' ? `grep 'core id' /proc/cpuinfo |sort |uniq |wc -l` : `grep -c processor /proc/cpuinfo`).chomp
      when /darwin/
        numjobs = `sysctl -n hw.#{platform == 'web' ? 'physical' : 'logical'}cpu`.chomp
      when /win32|mingw|mswin/
        require 'win32ole'
        WIN32OLE.connect('winmgmts://').ExecQuery("select NumberOf#{platform == 'web' ? '' : 'Logical'}Processors from Win32_ComputerSystem").each { |out| numjobs = platform == 'web' ? out.NumberOfProcessors : out.NumberOfLogicalProcessors }
      else
        numjobs = 1
      end
    end
    build_options = "-j#{numjobs}#{build_options}"
    filter = ''
  end
  system "cd \"#{build_tree}\" && #{ccache_envvar} cmake --build . #{cmake_build_options} -- #{build_options} #{filter}" or abort
end

# Usage: rake android [parameter='--es pickedLibrary Urho3DPlayer:Scripts/NinjaSnowWar.as'] [intent=.SampleLauncher] [package=com.github.urho3d] [success_indicator='Initialized engine'] [payload='sleep 30'] [api=21] [abi=armeabi-v7a] [avd=test_#{api}_#{abi}] [retries=10] [retry_interval=10] [install]
desc 'Test run APK in Android (virtual) device, default to Urho3D Samples APK if no parameter is given'
task :android do
  parameter = ENV['parameter'] || '--es pickedLibrary Urho3DPlayer:Scripts/NinjaSnowWar.as'
  intent = ENV['intent'] || '.SampleLauncher'
  package = ENV['package'] || 'com.github.urho3d'
  success_indicator = ENV['success_indicator'] || 'Initialized engine'
  payload = ENV['payload'] || 'sleep 30'
  api = ENV['api'] || 21
  abi = ENV['abi'] || 'armeabi-v7a'
  avd = ENV['avd'] || "test_#{api}_#{abi}"
  retries = ENV['retries'] || 10 # minutes
  retry_interval = ENV['retry_interval'] || 10 # seconds
  build_tree = ENV['android_build_tree'] || ENV['build_tree'] || '../android-Build'
  install = false
  ARGV.each { |option|
    task option.to_sym do ; end; Rake::Task[option].clear   # No-op hack
    case option
    when 'install'
      install = true
    end
  }
  android_prepare_device api, abi, avd or abort 'Failed to prepare Android (virtual) device for test run'
  if install
    system 'rake make android' or abort 'Failed to build shared library using Android NDK'
    Dir.chdir build_tree do
      system 'android update project -p .' unless File.exist? 'local.properties'
      system 'ant debug' or abort 'Failed to generate APK using Android SDK'
    end
  end
  android_wait_for_device retries, retry_interval or abort 'Failed to start Android (virtual) device'
  if install
    system "cd \"#{build_tree}\" && ant -Dadb.device.arg='-s #{$specific_device}' installd" or abort 'Failed to install APK'
  end
  android_test_run parameter, intent, package, success_indicator, payload or abort "Failed to test run #{package}/#{intent}"
end

### Tasks for Urho3D maintainers ###

# Usage: rake git remote_add|sync|subtree
desc 'Collections of convenience git commands, multiple git commands may be executed in one rake command'
task :git do
  success = true
  consumed = false
  ARGV.each_with_index { |command, index|
    task command.to_sym do ; end; Rake::Task[command].clear   # No-op hack
    next if consumed
    case command
    when 'remote_add', 'sync', 'subtree'
      success = system "rake git_#{ARGV[index, ARGV.length - index].delete_if { |arg| /=/ =~ arg }.join ' '}"
      consumed = true
    else
      abort 'Usage: rake git remote_add|sync|subtree' unless command == 'git' && ARGV.length > 1
    end
  }
  abort unless success
end

# Usage: rake git remote_add [remote=<local-name>] url=<remote-url>'
desc 'Add a new remote and configure it so that its tags will be fetched into a unique namespace'
task :git_remote_add do
  abort 'Usage: rake git remote_add [remote=<name>] url=<remote-url>' unless ENV['url']
  remote = ENV['remote'] || /\/(.*?)\.git/.match(ENV['url'])[1]
  system "git remote add #{remote} #{ENV['url']} && git config --add remote.#{remote}.fetch +refs/tags/*:refs/tags/#{remote}/* && git config remote.#{remote}.tagopt --no-tags && git fetch #{remote}" or abort
end

# Usage: rake git sync [master=master] [upstream=upstream]
desc "Fetch and merge an upstream's remote branch to a fork's local branch then pushing the local branch to the fork's corresponding remote branch"
task :git_sync do
  master = ENV['master'] || 'master'
  upstream = ENV['upstream'] || 'upstream'
  system "git fetch #{upstream} && git checkout #{master} && git merge -m 'Sync at #{Time.now.localtime}.' #{upstream}/#{master} && git push && git checkout -" or abort
end

# Usage: rake git subtree split|rebase|add|push|pull
desc 'Misc. sub-commands for git subtree operations'
task :git_subtree do
  ARGV.each { |subcommand|
    task subcommand.to_sym do ; end; Rake::Task[subcommand].clear   # No-op hack
    case subcommand
    when 'split'
      abort 'Usage: rake git subtree split subdir=</path/to/subdir/to/be/split> [split_branch=<name>]' unless ENV['subdir']
      ENV['split_branch'] = "#{Pathname.new(ENV['subdir']).basename}-split" unless ENV['split_branch']
      system "git subtree split --prefix #{ENV['subdir']} -b #{ENV['split_branch']}" or abort
    when 'rebase'
      abort 'Usage: rake git subtree rebase baseline=<commit|branch|tag> split_branch=<name>' unless ENV['baseline'] && ENV['split_branch']
      ENV['rebased_branch'] = "#{Pathname.new(ENV['baseline']).basename}-#{ENV['rebased_branch_suffix'] || 'modified-for-urho3d'}"
      head = `git log --pretty=format:'%H' #{ENV['split_branch']} |head -1`.chomp
      tail = `git log --reverse --pretty=format:'%H' #{ENV['split_branch']} |head -1`.chomp
      system "git rebase --onto #{ENV['baseline']} #{tail} #{head} && git checkout -b #{ENV['rebased_branch']}" or abort "After resolving all the conflicts, issue this command manually:\ngit checkout -b #{ENV['rebased_branch']}"
    when 'add'
      abort 'Usage: rake git subtree add subdir=</path/to/subdir/to/be/split> remote=<name> baseline=<commit|branch|tag>' unless ENV['subdir'] && ENV['remote'] && ENV['baseline']
      ENV['rebased_branch'] = "#{Pathname.new(ENV['baseline']).basename}-#{ENV['rebased_branch_suffix'] || 'modified-for-urho3d'}"
      system "git push -u #{ENV['remote']} #{ENV['rebased_branch']} && git rm -r #{ENV['subdir']} && git commit -qm 'Replace #{ENV['subdir']} subdirectory with subtree.' && git subtree add --prefix #{ENV['subdir']} #{ENV['remote']} #{ENV['rebased_branch']} --squash" or abort
    when 'push'
      abort 'Usage: rake git subtree push subdir=</path/to/subdir/to/be/split> remote=<name> baseline=<commit|branch|tag>' unless ENV['subdir'] && ENV['remote'] && ENV['baseline']
      ENV['rebased_branch'] = "#{Pathname.new(ENV['baseline']).basename}-#{ENV['rebased_branch_suffix'] || 'modified-for-urho3d'}"
      system "git subtree push --prefix #{ENV['subdir']} #{ENV['remote']} #{ENV['rebased_branch']}" or abort
    when 'pull'
      abort 'Usage: rake git subtree pull subdir=</path/to/subdir/to/be/split> remote=<name> baseline=<commit|branch|tag>' unless ENV['subdir'] && ENV['remote'] && ENV['baseline']
      ENV['rebased_branch'] = "#{Pathname.new(ENV['baseline']).basename}-#{ENV['rebased_branch_suffix'] || 'modified-for-urho3d'}"
      system "git subtree pull --prefix #{ENV['subdir']} #{ENV['remote']} #{ENV['rebased_branch']} --squash" or abort
    else
      abort 'Usage: rake git subtree split|rebase|add|push|pull' unless subcommand == 'git_subtree' && ARGV.length > 1
    end
  }
end

### Tasks for CI builds and tests ###

# Usage: NOT intended to be used manually
desc 'Build and run the Annotate tool (temporary)'
task :ci_annotate do
  system 'rake cmake URHO3D_CLANG_TOOLS=1 && rake make annotate' or abort 'Failed to annotate'
  system "git config user.name $GIT_NAME && git config user.email $GIT_EMAIL && git remote set-url --push origin https://$GH_TOKEN@github.com/$TRAVIS_REPO_SLUG.git && if git fetch origin clang-tools:clang-tools 2>/dev/null; then git push -qf origin --delete clang-tools; fi && git checkout -B clang-tools && git stash -q && git reset --hard HEAD~ && git stash pop -q && sed -i \"s/COVERITY_SCAN_THRESHOLD/URHO3D_PCH=0 URHO3D_BINDINGS=1 COVERITY_SCAN_THRESHOLD/g\" .travis.yml && git add -A .travis.yml Source/Urho3D && if git commit -qm 'Result of Annotator tool. [skip appveyor] [ci only: clang-tools]'; then git push -q -u origin clang-tools >/dev/null 2>&1; fi" or abort 'Failed to push clang-tools branch'
end

# Usage: NOT intended to be used manually
desc 'Push the generated binding source files to clang-tools branch (temporary)'
task :ci_push_bindings do
  abort "Skipped pushing to #{ENV['TRAVIS_BRANCH']} branch due to moving HEAD" unless `git fetch -qf origin #{ENV['TRAVIS_PULL_REQUEST'] == 'false' ? ENV['TRAVIS_BRANCH'] : %Q{+refs/pull/#{ENV['TRAVIS_PULL_REQUEST']}/head'}}; git log -1 --pretty=format:'%H' FETCH_HEAD` == ENV['TRAVIS_COMMIT']
  system "rm -rf fastcomp-clang && git config user.name $GIT_NAME && git config user.email $GIT_EMAIL && git remote set-url --push origin https://$GH_TOKEN@github.com/$TRAVIS_REPO_SLUG.git && git add -A Source/Urho3D && if git commit -qm 'Result of AutoBinder tool. [ci skip]'; then git push -q origin HEAD:#{ENV['TRAVIS_BRANCH']} >/dev/null 2>&1; fi" or abort "Failed to push #{ENV['TRAVIS_BRANCH']} branch"
end

# Usage: NOT intended to be used manually
desc 'Configure, build, and test Urho3D project'
task :ci do
  next if timeup    # Measure the VM overhead
  # Skip if only performing CI for selected branches and the current branch is not in the list
  unless ENV['RELEASE_TAG']
    next if ENV['TRAVIS'] && /\[skip travis\]/ =~ ENV['COMMIT_MESSAGE']   # For feature parity with AppVeyor's [skip appveyor]
    matched = /\[ci only:(.*?)\]/.match(ENV['COMMIT_MESSAGE'])
    next if matched && !matched[1].split(/[ ,]/).reject!(&:empty?).map { |i| /#{i}/ =~ (ENV['TRAVIS_BRANCH'] || ENV['APPVEYOR_REPO_BRANCH']) }.any?
  end
  # Obtain our custom data, if any
  if ENV['APPVEYOR']
    # AppVeyor does not provide job number environment variable in the same semantics as TRAVIS_JOB_NUMBER nor it supports custom data in its .appveyor.yml document
    if ENV['included_sample'] || ENV['excluded_sample']   # Inclusion has higher precedence
      pairs = (ENV['included_sample'] || ENV['excluded_sample']).split
      samples = pairs.pop.split ','
      matched = true
      pairs.each { |pair|
        kv = pair.split '='
        matched = false if ENV[kv.first] != kv.last
      }
      samples.each { |name| ENV["#{ENV['included_sample'] ? 'INCLUDED' : 'EXCLUDED'}_SAMPLE_#{name}"] = '1' } if matched
    end
  else
    data = YAML::load(File.open('.travis.yml'))['data']
    data['excluded_sample']["##{ENV['TRAVIS_JOB_NUMBER'].split('.').last}"].each { |name| ENV["EXCLUDED_SAMPLE_#{name}"] = '1' } if data && data['excluded_sample'] && data['excluded_sample']["##{ENV['TRAVIS_JOB_NUMBER'].split('.').last}"]
  end
  # Unshallow the clone's history when necessary
  if ENV['CI'] && ENV['PACKAGE_UPLOAD'] && !ENV['RELEASE_TAG']
    system 'git fetch --unshallow' or abort 'Failed to unshallow cloned repository'
  end
  # Show CMake version
  system 'cmake --version' or abort 'Failed to find CMake'
  puts
  # Using out-of-source build tree when using Travis-CI; 'build_tree' environment variable is already set when on AppVeyor
  ENV['build_tree'] = '../Build' unless ENV['APPVEYOR']
  # Always use a same build configuration to keep ccache's cache size small; single-config generator needs the option when configuring, while multi-config when building
  ENV[ENV['XCODE'] ? 'config' : 'CMAKE_BUILD_TYPE'] = 'Release' if ENV['USE_CCACHE']
  # Currently we don't have the infra to test run all the platforms; also skip when doing packaging build due to time constraint
  ENV['URHO3D_TESTING'] = '1' if ((ENV['LINUX'] && !ENV['URHO3D_64BIT']) || (ENV['OSX'] && !ENV['IOS']) || ENV['APPVEYOR']) && !ENV['PACKAGE_UPLOAD']
  # When not explicitly specified then use generic generator
  generator = ENV['XCODE'] ? 'xcode' : (ENV['APPVEYOR'] && !ENV['MINGW'] ? 'vs2015' : '')
  # LuaJIT on MinGW build is not possible on Travis-CI with Ubuntu LTS 12.04 as its GCC cross-compiler version is too old, wait until we have Ubuntu LTS 14.04
  # LuaJIT on Web platform is not possible
  jit = (ENV['WIN32'] && ENV['TRAVIS']) || ENV['WEB'] ? '' : 'JIT=1 URHO3D_LUAJIT_AMALG='
  system "rake cmake #{generator} URHO3D_LUA#{jit}=1 URHO3D_DATABASE_SQLITE=1 URHO3D_EXTRAS=1" or abort 'Failed to configure Urho3D library build'
  next if timeup    # Measure the CMake configuration overhead
  if ENV['AVD'] && !ENV['PACKAGE_UPLOAD']   # Skip APK test run when packaging
    # Prepare a new AVD in another process to avoid busy waiting
    android_prepare_device ENV['AVD'], ENV['ANDROID_ABI'] or abort 'Failed to prepare Android (virtual) device for test run'
  end
  # Temporarily put the logic here for clang-tools migration until everything else are in their places
  if ENV['URHO3D_BINDINGS']
    system 'rake make' or abort 'Failed to build or test Urho3D library with annotated source files'
    system 'rake ci_push_bindings' or abort
    next
  end
  if !wait_for_block { Thread.current[:subcommand_to_kill] = 'xcodebuild'; system 'rake make' }
    abort 'Failed to build Urho3D library' unless File.exists?('already_timeup.log')
    $stderr.puts "Skipped the rest of the CI processes due to insufficient time"
    next
  end
  if ENV['URHO3D_TESTING'] && !timeup
    # Multi-config CMake generators use different test target name than single-config ones for no good reason
    test = "rake make target=#{(ENV['OS'] && !ENV['MINGW']) || ENV['XCODE'] ? 'RUN_TESTS' : 'test'}"
    system "#{test}" or abort 'Failed to test Urho3D library'
    test = "&& echo#{ENV['OS'] ? '.' : ''} && #{test}"
  else
    test = ''
  end
  # Skip scaffolding test when time up or packaging for iOS and Web platform
  unless ENV['CI'] && (ENV['IOS'] || ENV['WEB']) && ENV['PACKAGE_UPLOAD'] || ENV['XCODE_64BIT_ONLY'] || timeup
    # Staged-install Urho3D SDK when on Travis-CI; normal install when on AppVeyor
    ENV['DESTDIR'] = ENV['HOME'] || Dir.home unless ENV['APPVEYOR']
    if !wait_for_block("Installing Urho3D SDK to #{ENV['DESTDIR'] ? "#{ENV['DESTDIR']}/usr/local" : 'default system-wide location'}...") { Thread.current[:subcommand_to_kill] = 'xcodebuild'; system "rake make target=install >#{ENV['OS'] ? 'nul' : '/dev/null'}" }
      abort 'Failed to install Urho3D SDK' unless File.exists?('already_timeup.log')
      $stderr.puts "Skipped the rest of the CI processes due to insufficient time"
      next
    end
    # Alternate to use in-the-source build tree for test coverage
    ENV['build_tree'] = '.' unless ENV['APPVEYOR']
    # Ensure the following variables are auto-discovered during scaffolding test
    ENV['URHO3D_64BIT'] = nil unless ENV['APPVEYOR']    # AppVeyor uses VS generator which always requires URHO3D_64BIT as input variable
    ['URHO3D_LIB_TYPE', 'URHO3D_STATIC_RUNTIME', 'URHO3D_OPENGL', 'URHO3D_D3D11', 'URHO3D_SSE', 'URHO3D_DATABASE_ODBC', 'URHO3D_DATABASE_SQLITE', 'URHO3D_LUAJIT', 'URHO3D_TESTING'].each { |var| ENV[var] = nil }
    # Alternate the scaffolding location between Travis CI and AppVeyor for test coverage; Travis CI uses build tree while AppVeyor using source tree
    # First scaffolding test uses absolute path while second test uses relative path, also for test converage
    # First test - create a new project on the fly that uses newly installed Urho3D SDK
    org = (ENV['TRAVIS_REPO_SLUG'] || ENV['APPVEYOR_PROJECT_SLUG']).split('/').first
    Dir.chdir scaffolding "#{ENV['APPVEYOR'] ? "C:/projects/#{org}/" : (ENV['TRAVIS'] ? "#{ENV['HOME']}/build/#{org}/Build/" : '../Build/')}UsingSDK" do   # The last rel path is for non-CI users, just in case
      puts "\nConfiguring downstream project using Urho3D SDK...\n\n"; $stdout.flush
      # SDK installation to a system-wide location does not need URHO3D_HOME to be defined, staged-installation does
      system "#{ENV['DESTDIR'] ? 'URHO3D_HOME=~/usr/local' : ''} rake cmake #{generator} URHO3D_LUA=1 && rake make #{test}" or abort 'Failed to configure/build/test temporary downstream project using Urho3D as external library'
    end
    next if timeup
    # Second test - create a new project on the fly that uses newly built Urho3D library in the build tree
    Dir.chdir scaffolding "#{ENV['APPVEYOR'] ? '' : '../Build/'}UsingBuildTree" do
      puts "Configuring downstream project using Urho3D library in its build tree...\n\n"; $stdout.flush
      system "rake cmake #{generator} URHO3D_HOME=#{ENV['APPVEYOR'] ? "../../#{ENV['build_tree']}" : '..'} URHO3D_LUA=1 && rake make #{test}" or abort 'Failed to configure/build/test temporary downstream project using Urho3D as external library'
    end
  end
  # Make, deploy, and test run Android APK in an Android (virtual) device
  if ENV['AVD'] && !ENV['PACKAGE_UPLOAD'] && !timeup
    puts "\nTest deploying and running Urho3D Samples APK..."
    Dir.chdir '../Build' do
      system 'android update project -p . && ant debug' or abort 'Failed to make Urho3D Samples APK'
      if android_wait_for_device
        system "ant -Dadb.device.arg='-s #{$specific_device}' installd" or abort 'Failed to deploy Urho3D Samples APK'
        android_test_run or abort 'Failed to test run Urho3D Samples APK'
      else
        puts 'Skipped test running Urho3D Samples APK as emulator failed to start in time'
      end
    end
  end
end

# Usage: NOT intended to be used manually
desc 'Setup build cache'
task :ci_setup_cache do
  clear = /\[cache clear\]/ =~ ENV['COMMIT_MESSAGE']
  # AppVeyor on Windows host has different kind of cache mechanism, not based on ccache
  if ENV['APPVEYOR']
    system "bash -c 'rm -rf #{ENV['build_tree']}'" if clear
    if File.exists?("#{ENV['build_tree']}/.commits")
      # Find the last valid commit SHA because the recorded commit SHAs may no longer be valid due to git reset/forced push
      last_commit = File.read("#{ENV['build_tree']}/.commits").split.find { |sha| system "git cat-file -e #{sha}" }
      # AppVeyor prefers CMD's FIND over MSYS's find, so we have to use fully qualified path to the MSYS's find
      system "bash -c '/c/Program\\ Files/Git/usr/bin/find CMakeLists.txt CMake Docs Source |xargs touch -r #{ENV['build_tree']}/CMakeCache.txt && touch $(git diff --name-only #{last_commit} #{ENV['APPVEYOR_REPO_COMMIT']})'"
    end
    next
  # Use internal cache store instead of using Travis CI one (this is a workaround for using ccache on Travis CI legacy build infra)
  elsif ENV['USE_CCACHE'].to_i == 2
    puts 'Setting up build cache'
    job_number = ".#{ENV['TRAVIS_JOB_NUMBER'].split('.').last}"
    repo_slug = "#{ENV['TRAVIS_REPO_SLUG'].split('/').first}/cache-store.git"
    matched = /.*-([^-]+-[^-]+)$/.match(ENV['TRAVIS_BRANCH'])
    base_mirror = matched ? matched[1] : nil
    # Do not abort even when it fails here
    system "if ! `git clone -q --depth 1 --branch #{ENV['TRAVIS_BRANCH']}#{job_number} https://github.com/#{repo_slug} ~/.ccache 2>/dev/null`; then if ! [ #{base_mirror} ] || ! `git clone -q --depth 1 --branch #{base_mirror}#{job_number} https://github.com/#{repo_slug} ~/.ccache 2>/dev/null`; then git clone -q --depth 1 https://github.com/#{repo_slug} ~/.ccache 2>/dev/null; fi && cd ~/.ccache && git checkout -qf -b #{ENV['TRAVIS_BRANCH']}#{job_number}; fi"
    # Preserving .git directory before clearing the cache on Linux host system (ccache on Mac OSX does not have this problem)
    `mv ~/.ccache/.git /tmp` if clear && ENV['OSX'].to_i != 1
  end
  # Clear ccache on demand
  system "ccache -z -M #{ENV['CCACHE_MAXSIZE']} #{clear ? '-C' : ''}"
  # Restoring .git directory if its backup exists
  `if [ -e /tmp/.git ]; then mv /tmp/.git ~/.ccache; fi`
end

# Usage: NOT intended to be used manually
desc 'Teardown build cache'
task :ci_teardown_cache do
  # AppVeyor on Windows host has different kind of cache mechanism, not based on ccache
  if ENV['APPVEYOR']
    # Keep the last 10 commit SHAs
    commits = (File.exists?("#{ENV['build_tree']}/.commits") ? File.read("#{ENV['build_tree']}/.commits").split : []).unshift(`git rev-parse #{ENV['APPVEYOR_REPO_COMMIT']}`.chomp).take 10
    File.open("#{ENV['build_tree']}/.commits", 'w') { |file| file.puts commits } if Dir.exist?(ENV['build_tree'])
    # Exclude build artifacts from being cached due to cache size limitation
    system "bash -c 'rm -f #{ENV['build_tree']}/bin/*.{exe,dll}'"
    next
  # Upload cache to internal cache store if it is our own
  elsif ENV['USE_CCACHE'].to_i == 2
    puts 'Storing build cache'
    job_number = ".#{ENV['TRAVIS_JOB_NUMBER'].split('.').last}"
    repo_slug = "#{ENV['TRAVIS_REPO_SLUG'].split('/').first}/cache-store.git"
    # Do not abort even when it fails here
    system "cd ~/.ccache && git config user.name $GIT_NAME && git config user.email $GIT_EMAIL && git remote set-url --push origin https://$GH_TOKEN@github.com/#{repo_slug} && git add -A . && git commit --amend -qm 'Travis CI: cache update at #{Time.now.utc}.' && git push -qf -u origin #{ENV['TRAVIS_BRANCH']}#{job_number} >/dev/null 2>&1"
  end
  system 'ccache -s'
end

# Usage: NOT intended to be used manually
desc 'Update site on GitHub Pages (and source tree on GitHub while we are at it)'
task :ci_site_update do
  # Skip when :ci rake task was skipped
  next unless File.exist?('../Build/CMakeCache.txt')
  next if timeup
  puts "Updating site...\n\n"
  system 'git clone --depth 1 -q https://github.com/urho3d/urho3d.github.io.git ../urho3d.github.io' or abort 'Failed to clone urho3d/urho3d.github.io'
  # Update credits from README.md to about.yml
  system "ruby -lne 'BEGIN { credits = false }; puts $_ if credits; credits = true if /bugfixes by:/; credits = false if /^$/' README.md |ruby -i -le 'credits = STDIN.read; puts ARGF.read.gsub(/(?<=contributors:\n).*?\n\n/m, credits)' ../urho3d.github.io/_data/about.yml" or abort 'Failed to update credits'
  # Setup doxygen to use minimal theme
  system "ruby -i -pe 'BEGIN { a = {%q{HTML_HEADER} => %q{minimal-header.html}, %q{HTML_FOOTER} => %q{minimal-footer.html}, %q{HTML_STYLESHEET} => %q{minimal-doxygen.css}, %q{HTML_COLORSTYLE_HUE} => 200, %q{HTML_COLORSTYLE_SAT} => 0, %q{HTML_COLORSTYLE_GAMMA} => 20, %q{DOT_IMAGE_FORMAT} => %q{svg}, %q{INTERACTIVE_SVG} => %q{YES}, %q{COLS_IN_ALPHA_INDEX} => 3} }; a.each {|k, v| gsub(/\#{k}\s*?=.*?\n/, %Q{\#{k} = \#{v}\n}) }' ../Build/Docs/generated/Doxyfile" or abort 'Failed to setup doxygen configuration file'
  system 'cp ../urho3d.github.io/_includes/Doxygen/minimal-* ../Build/Docs' or abort 'Failed to copy minimal-themed template'
  release = ENV['RELEASE_TAG'] || 'HEAD'
  unless release == 'HEAD'
    system "mkdir -p ../urho3d.github.io/documentation/#{release}" or abort 'Failed to create directory for new document version'
    system "ruby -i -pe 'gsub(/HEAD/, %q{#{release}})' ../Build/Docs/minimal-header.html" or abort 'Failed to update document version in YAML Front Matter block'
    append_new_release release or abort 'Failed to add new release to document data file'
  end
  # Generate and sync doxygen pages
  system "cd ../Build && make -j$numjobs doc >/dev/null 2>&1 && ruby -i -pe 'gsub(/(<\\/?h)3([^>]*?>)/, %q{\\14\\2}); gsub(/(<\\/?h)2([^>]*?>)/, %q{\\13\\2}); gsub(/(<\\/?h)1([^>]*?>)/, %q{\\12\\2})' Docs/html/_*.html && rsync -a --delete Docs/html/ ../urho3d.github.io/documentation/#{release}" or abort 'Failed to generate/rsync doxygen pages'
  # Supply GIT credentials to push site documentation changes to urho3d/urho3d.github.io.git
  system "cd ../urho3d.github.io && git config user.name $GIT_NAME && git config user.email $GIT_EMAIL && git remote set-url --push origin https://$GH_TOKEN@github.com/urho3d/urho3d.github.io.git && git add -A . && if git commit -qm \"Travis CI: site documentation update at #{Time.now.utc}.\n\nCommit: https://github.com/$TRAVIS_REPO_SLUG/commit/$TRAVIS_COMMIT\n\nMessage: $COMMIT_MESSAGE\"; then git push -q >/dev/null 2>&1 && echo Site updated successfully; fi" or abort 'Failed to update site'
  next if timeup
  # Skip detecting source tree changes when HEAD has moved or it is too late already as a release tag has just been pushed
  unless ENV['RELEASE_TAG'] || `git fetch -qf origin #{ENV['TRAVIS_BRANCH']}; git log -1 --pretty=format:'%H' FETCH_HEAD` != ENV['TRAVIS_COMMIT']
    puts "Updating source tree...\n\n"
    # Supply GIT credentials to push source tree changes to urho3d/Urho3D.git
    system 'git config user.name $GIT_NAME && git config user.email $GIT_EMAIL && git remote set-url --push origin https://$GH_TOKEN@github.com/$TRAVIS_REPO_SLUG.git'
    system "git add Source && git commit -qm 'Travis CI: source tree update at #{Time.now.utc}.' >/dev/null 2>&1"   # Use extra quiet mode as there could be no changes at all
    if /2008-([0-9]{4}) the Urho3D project/.match(File.read('Rakefile'))[1].to_i != Time.now.year
      # Automatically bump copyright when crossing a new year and give instruction to clear the cache if so since the cache is of no use anyway because of massive changes
      system "git add #{bump_copyright_year.join ' '} && if git commit -qm 'Travis CI: bump copyright to #{Time.now.year}.\n[cache clear]'; then git push origin HEAD:#{ENV['TRAVIS_BRANCH']} -q >/dev/null 2>&1 && echo Bumped copyright - Happy New Year!; fi" or abort "Failed to push copyright update for #{ENV['TRAVIS_BRANCH']}"
      ['urho3d.github.io master', 'android-ndk ndk-update-trigger', 'armhf-sysroot sysroot-update-trigger', 'arm64-sysroot sysroot-update-trigger', 'rpi-sysroot sysroot-update-trigger', 'emscripten-sdk sdk-update-trigger'].each { |var| pair = var.split; system "if [ ! -d ../#{pair.first} ]; then git clone -q --depth 1 --branch #{pair.last} https://github.com/urho3d/#{pair.first} ../#{pair.first}; fi" or abort "Failed to clone urho3d/#{pair.first}"; system "cd ../#{pair.first} && git config user.name $GIT_NAME && git config user.email $GIT_EMAIL && git remote set-url --push origin https://$GH_TOKEN@github.com/urho3d/#{pair.first} && git add #{bump_copyright_year("../#{pair.first}").join ' '} 2>/dev/null && git add #{bump_copyright_year("../#{pair.first}", '2014-[0-9]{4} Yao').join ' '} 2>/dev/null && if git commit -qm 'Travis CI: bump copyright to #{Time.now.year}.\n[ci skip]'; then git push -q >/dev/null 2>&1; fi" or abort "Failed to push copyright update for urho3d/#{pair.first}"; }
    elsif system("git add Docs/*API* && git commit -qm 'Test commit to detect API documentation changes'")
      # Automatically give instruction to do packaging when API has changed, unless the instruction is already given in this commit
      bump_soversion 'Source/Urho3D/.soversion' or abort 'Failed to bump soversion'
      system "git add Source/Urho3D/.soversion && git commit --amend -qm \"Travis CI: API documentation update at #{Time.now.utc}.\n#{ENV['PACKAGE_UPLOAD'] ? '' : '[ci package]'}\n\nCommit: https://github.com/$TRAVIS_REPO_SLUG/commit/$TRAVIS_COMMIT\n\nMessage: #{ENV['COMMIT_MESSAGE'].gsub(/\[.*\]/, '')}\" && echo Source tree updated successfully" or abort 'Failed to commit API documentation'
    end
  else
    puts 'Skipped detecting source tree changes due to moving HEAD' unless ENV['RELEASE_TAG']
  end
end

# Usage: NOT intended to be used manually
desc 'Update web samples to GitHub Pages'
task :ci_emscripten_samples_update do
  next if timeup
  puts 'Updating Web samples in main website...'
  system 'git clone --depth 1 -q https://github.com/urho3d/urho3d.github.io.git ../urho3d.github.io' or abort 'Failed to clone urho3d/urho3d.github.io'
  system "rsync -a --delete --exclude tool --exclude *.pak --exclude index.md ../Build/bin/ ../urho3d.github.io/samples" or abort 'Failed to rsync Web samples'
  Dir.chdir('../urho3d.github.io/samples') {
    next unless system 'git diff --quiet Urho3D.js.data'
    uuid = `git diff --color=never --word-diff-regex='\\w+' --word-diff=porcelain Urho3D.js`.split.grep(/^[+-]\w+-/).map { |it| it[0] = ''; it }
    system %Q(ruby -i.bak -pe "gsub '#{uuid.last}', '#{uuid.first}'" Urho3D.js)
    if system 'git diff --quiet Urho3D.js'
      File.unlink 'Urho3D.js.bak'
      Dir['*.js'].each { |file| system %Q(ruby -i -pe "gsub '#{uuid.last}', '#{uuid.first}'" #{file}) }
    else
      File.rename 'Urho3D.js.bak', 'Urho3D.js'
    end
  }
  update_web_samples_data or abort 'Failed to update Web json data file'
  root_commit, _ = get_root_commit_and_recipients
  system "cd ../urho3d.github.io && git config user.name $GIT_NAME && git config user.email $GIT_EMAIL && git remote set-url --push origin https://$GH_TOKEN@github.com/urho3d/urho3d.github.io.git && git add -A . && ( git commit -qm \"Travis CI: Web samples update at #{Time.now.utc}.\n\nCommit: https://github.com/$TRAVIS_REPO_SLUG/commit/#{root_commit}\n\nMessage: #{`git log --format=%B -n 1 #{root_commit}`}\" || true) && git push -q >/dev/null 2>&1" or abort 'Failed to update Web samples'
end

# Usage: NOT intended to be used manually
desc 'Create all CI mirror branches'
task :ci_create_mirrors do
  # Skip all CI branches creation if there are more commits externally
  abort 'Skipped creating mirror branches due to moving remote HEAD' unless `git fetch -qf origin #{ENV['TRAVIS_PULL_REQUEST'] == 'false' ? ENV['TRAVIS_BRANCH'] : %Q{+refs/pull/#{ENV['TRAVIS_PULL_REQUEST']}/head'}}; git log -1 --pretty=format:'%H' FETCH_HEAD` == ENV['TRAVIS_COMMIT']     # This HEAD movement detection logic is more complex than usual as the original intention was to allow mirror creation on PR, however, we have scaled it back for now
  # Skip non-mandatory branches if there are pending commits internally
  head = `git log -1 --pretty=format:'%H' HEAD`
  head_moved = head != ENV['TRAVIS_COMMIT']   # Local head may be moved because of API documentation update
  # Reset the head to the original commit position for mirror creation
  system 'git checkout -qf $TRAVIS_COMMIT' if head_moved
  system 'git config user.name $GIT_NAME && git config user.email $GIT_EMAIL && git remote set-url --push origin https://$GH_TOKEN@github.com/$TRAVIS_REPO_SLUG.git' or abort 'Failed to re-checkout commit'
  # Limit the scanning to only master branch and limit the frequency of scanning
  scan = ENV['TRAVIS_BRANCH'] == 'master' && ((/\[cache clear\]/ !~ ENV['COMMIT_MESSAGE'] && `ccache -s |grep 'cache miss'`.split.last.to_i >= ENV['COVERITY_SCAN_THRESHOLD'].to_i) || /\[ci scan\]/ =~ ENV['COMMIT_MESSAGE']) && /\[ci only:.*?\]/ !~ ENV['COMMIT_MESSAGE']
  # Check if it is time to generate annotation
  annotate = ENV['TRAVIS_BRANCH'] == 'master' && (ENV['PACKAGE_UPLOAD'] || /\[ci annotate\]/ =~ ENV['COMMIT_MESSAGE']) && /\[ci only:.*?\]/ !~ ENV['COMMIT_MESSAGE']
  # Determine which CI mirror branches to be auto created
  unless ENV['RELEASE_TAG']
    skip_travis = /\[skip travis\]/ =~ ENV['COMMIT_MESSAGE']   # For feature parity with AppVeyor's [skip appveyor]
    matched = /\[ci only:(.*?)\]/.match(ENV['COMMIT_MESSAGE'])
    ci_only = matched ? matched[1].split(/[ ,]/).reject!(&:empty?) : nil
    if ci_only
      ci_only.push('Coverity-Scan') if scan
      ci_only.push('Annotate') if annotate
    end
  else
    ci_only = nil
  end
  # Escape double quotes in the commit message so they do not interfere with the string interpolation below
  escaped_commit_message = ENV['COMMIT_MESSAGE'].gsub(/"/, '\"')
  # Obtain the whole stream and process the rest of documents except the first one since travis-build does not do that at the moment
  stream = YAML::load_stream(File.open('.travis.yml'))
  notifications = stream[0]['notifications']
  notifications['email']['recipients'] = get_root_commit_and_recipients().last unless notifications['email']['recipients']
  stream.drop(1).each { |doc| branch = doc.delete('branch'); ci = branch['name']; ci_branch = ENV['RELEASE_TAG'] || (ENV['TRAVIS_BRANCH'] == 'master' && ENV['TRAVIS_PULL_REQUEST'] == 'false') ? ci : (ENV['TRAVIS_PULL_REQUEST'] == 'false' ? "#{ENV['TRAVIS_BRANCH']}-#{ci}" : "PR ##{ENV['TRAVIS_PULL_REQUEST']}-#{ci}"); is_appveyor_ci = branch['appveyor']; next if skip_travis && !is_appveyor_ci; unless (branch['mandatory'] || !head_moved) && ((ci_only && ci_only.map { |i| /#{i}/ =~ ci }.any?) || (!ci_only && (branch['active'] || (scan && /Scan/ =~ ci) || (annotate && /Annotate/ =~ ci)))); system "if git fetch origin #{ci_branch}:#{ci_branch} 2>/dev/null; then git push -qf origin --delete #{ci_branch}; fi"; puts "Skipped creating #{ci_branch} mirror branch due to moving HEAD" if !ci_only && branch['active'] && head_moved; next; end; unless is_appveyor_ci; lastjob = [(doc['env']['matrix'] ? doc['env']['matrix'].length : 0) + (doc['matrix'] && doc['matrix']['include'] ? doc['matrix']['include'].length : 0), 1].max; doc['after_script'] = [*doc['after_script']] << (lastjob == 1 ? '%s' : "if [ ${TRAVIS_JOB_NUMBER##*.} == #{lastjob} ]; then %s; fi") % 'rake ci_delete_mirror'; doc['notifications'] = notifications unless doc['notifications']; doc_name = '.travis.yml'; File.open("#{doc_name}.new", 'w') { |file| file.write doc.to_yaml } else doc['on_finish'] = [*doc['on_finish']] << "if \"%PLATFORM%:%URHO3D_LIB_TYPE%\" == \"#{branch['last_job']}\" rake ci_delete_mirror"; doc_name = '.appveyor.yml'; File.open("#{doc_name}.new", 'w') { |file| file.write doc.to_yaml }; if ENV['TRAVIS']; replaced_content = File.read("#{doc_name}.new").gsub(/! /, ''); File.open("#{doc_name}.new", 'w') { |file| file.puts replaced_content }; end; end; puts "Creating #{ci_branch} mirror branch..."; system "git checkout -qB #{ci_branch} && rm .appveyor.yml .travis.yml && mv #{doc_name}.new #{doc_name} && git add -A . && git commit -qm \"#{escaped_commit_message}\" && git push -qf -u origin #{ci_branch} >/dev/null 2>&1 && git checkout -q - && sleep 5" or abort "Failed to create #{ci_branch} mirror branch" }
  # Push pending commits if any
  system "git push origin #{head}:#{ENV['TRAVIS_BRANCH']} -q >/dev/null 2>&1" or abort "Failed to push pending commits to #{ENV['TRAVIS_BRANCH']}" if head_moved
end

# Usage: NOT intended to be used manually
desc 'Delete CI mirror branch'
task :ci_delete_mirror do
  # Skip if the mirror branch has been forced pushed remotely or when we are performing a release (in case we need to rerun the job to recreate the package)
  unless `git fetch -qf origin #{ENV['TRAVIS_BRANCH'] || ENV['APPVEYOR_REPO_BRANCH']} && git log -1 --pretty=format:'%H' FETCH_HEAD`.gsub(/'/, '') == (ENV['TRAVIS_COMMIT'] || ENV['APPVEYOR_REPO_COMMIT']).chop && !ENV['RELEASE_TAG']
    # Do not use "abort" here because AppVeyor, unlike Travis, also handles the exit status of the processes invoked in the "on_finish" section of the .appveyor.yml
    # Using "abort" may incorrectly (or correctly, depends on your POV) report the whole CI as failed when the CI mirror branch deletion is being skipped
    $stderr.puts "Skipped deleting #{ENV['TRAVIS_BRANCH'] || ENV['APPVEYOR_REPO_BRANCH']} mirror branch"
    next
  end
  system "bash -c 'git config user.name #{ENV['GIT_NAME']} && git config user.email #{ENV['GIT_EMAIL']} && git remote set-url --push origin https://#{ENV['GH_TOKEN']}@github.com/#{ENV['TRAVIS_REPO_SLUG'] || ENV['APPVEYOR_REPO_NAME']}.git'"
  system "bash -c 'git push -qf origin --delete #{ENV['TRAVIS_BRANCH'] || ENV['APPVEYOR_REPO_BRANCH']} >/dev/null 2>&1'" or abort "Failed to delete #{ENV['TRAVIS_BRANCH'] || ENV['APPVEYOR_REPO_BRANCH']} mirror branch"
end

# Usage: NOT intended to be used manually
desc 'Make binary package and upload it to a designated central hosting server'
task :ci_package_upload do
  # Using out-of-source build tree when using Travis-CI; 'build_tree' environment variable is already set when on AppVeyor
  ENV['build_tree'] = '../Build' unless ENV['APPVEYOR']
  # Always use Release build configuration when using Xcode; 'config' environment variable is already set when on AppVeyor
  ENV['config'] = 'Release' if ENV['XCODE']
  # Skip when :ci rake task was skipped
  next unless File.exist?("#{ENV['build_tree']}/CMakeCache.txt")
  next if timeup
  # Generate the documentation if necessary
  if ENV['SITE_UPDATE']
    if File.exist?('.site_updated')
      # Skip if site is already updated before
      ENV['SITE_UPDATE'] = nil
    end
  elsif !File.exists?("#{ENV['build_tree']}/Docs/html/index.html")
    puts "Generating documentation...\n"; $stdout.flush
    # Ignore the exit status from 'make doc' on Windows host system because Doxygen may not return exit status correctly on Windows
    system "rake make target=doc >#{ENV['OS'] ? 'nul' : '/dev/null'}" or ENV['OS'] or abort 'Failed to generate documentation'
    next if timeup
  end
  # Make the package
  puts "Packaging artifacts...\n\n"; $stdout.flush
  if ENV['IOS']
    # There is a bug in CMake/CPack that causes the 'package' target failed to build for IOS platform, workaround by calling cpack directly; CMake 3.4 runs the target successfully, however, the result tarball is incomplete (somehow it misses packaging the library itself, another bug?)
    system 'cd ../Build && cpack -G TGZ 2>/dev/null' or abort 'Failed to make binary package'
  else
    if ENV['ANDROID']
      if !ENV['NO_SDK_SYSIMG']
        system 'cd ../Build && android update project -p . && ant debug' or abort 'Failed to make Urho3D Samples APK'
      end
      system 'rm -rf ~/usr/local $(dirname $(which android))/../*' if ENV['TRAVIS']   # Clean up some disk space before packaging on Travis CI
    end
    if ENV['URHO3D_USE_LIB64_RPM']
      system 'rake cmake' or abort 'Failed to reconfigure to generate 64-bit RPM package'
      system "rm #{ENV['build_tree']}/Urho3D-*" or abort 'Failed to remove previously generated artifacts'  # This task can be invoked more than one time
     end
    system "#{!ENV['OS'] && (ENV['URHO3D_64BIT'] || ENV['RPI'] || ENV['ARM']) ? 'setarch i686' : ''} rake make target=package" or abort 'Failed to make binary package'
  end
  next if timeup
  # Determine the upload location
  puts "Uploading artifacts...\n\n"; $stdout.flush
  setup_digital_keys
  repo = ENV[ENV['TRAVIS'] ? 'TRAVIS_REPO_SLUG' : 'APPVEYOR_REPO_NAME']
  unless ENV['RELEASE_TAG']
    upload_dir = "/home/frs/project/#{repo}/Snapshots"
    if ENV['SITE_UPDATE']
      # Download source packages from GitHub
      system "export SNAPSHOT_VER=$(git describe $TRAVIS_COMMIT |ruby -pe 'gsub(/-(?!g)/, %q{.})'); wget -q https://github.com/$TRAVIS_REPO_SLUG/tarball/$TRAVIS_COMMIT -O Urho3D-$SNAPSHOT_VER-Source-snapshot.tar.gz && wget -q https://github.com/$TRAVIS_REPO_SLUG/zipball/$TRAVIS_COMMIT -O Urho3D-$SNAPSHOT_VER-Source-snapshot.zip" or abort 'Failed to get source packages'
      # Only keep the snapshots from the last 30 revisions
      system "for v in $(sftp urho-travis-ci@frs.sourceforge.net <<EOF |tr ' ' '\n' |grep Urho3D- |cut -d '-' -f1,2 |uniq |tail -n +11
cd #{upload_dir}
ls -1t
bye
EOF
); do echo rm #{upload_dir}/${v}-*; done |sftp -b - urho-travis-ci@frs.sourceforge.net >/dev/null 2>&1" or abort 'Failed to housekeep snapshots'
    end
  else
    upload_dir = "/home/frs/project/#{repo}/#{ENV['RELEASE_TAG']}"
    if ENV['SITE_UPDATE']
      # Download source packages from GitHub
      system 'wget -q https://github.com/$TRAVIS_REPO_SLUG/archive/$RELEASE_TAG.tar.gz -O Urho3D-$RELEASE_TAG-Source.tar.gz && wget -q https://github.com/$TRAVIS_REPO_SLUG/archive/$RELEASE_TAG.zip -O Urho3D-$RELEASE_TAG-Source.zip' or abort 'Failed to get source packages'
    end
    # Make sure the release directory exists remotely, do this in all the build jobs as we don't know which one would start uploading first
    system "bash -c 'sftp urho-travis-ci@frs.sourceforge.net <<EOF >/dev/null 2>&1
mkdir #{upload_dir}
bye
EOF'" or abort 'Failed to create release directory remotely'
  end
  if ENV['SITE_UPDATE']
    # Upload the source package
    system "scp Urho3D-* urho-travis-ci@frs.sourceforge.net:#{upload_dir}" or abort 'Failed to upload source package'
    if ENV['RELEASE_TAG']
      # Mark the source tarball as default download for host systems other than Windows/Mac/Linux
      system "curl -H 'Accept: application/json' -X PUT -d 'default=bsd&default=solaris&default=others' -d \"api_key=$SF_API\" https://sourceforge.net/projects/%s/files/%s/#{ENV['RELEASE_TAG']}/Urho3D-#{ENV['RELEASE_TAG']}-Source.tar.gz" % ENV['TRAVIS_REPO_SLUG'].split('/') or abort 'Failed to set source tarball as default download'
    end
    # Sync readme and license files, just in case they are updated in the repo
    system 'for f in README.md LICENSE; do mtime=$(git log --format=%ai -n1 $f); touch -d "$mtime" $f; done' or abort 'Failed to acquire file modified time'
    system 'rsync -e ssh -az README.md LICENSE urho-travis-ci@frs.sourceforge.net:/home/frs/project/$TRAVIS_REPO_SLUG' or abort 'Failed to sync readme and license files'
    # Mark that the site has been updated
    File.open('.site_updated', 'w') {}
  end
  # Upload the binary package
  system "bash -c 'scp #{ENV['build_tree']}/Urho3D-* urho-travis-ci@frs.sourceforge.net:#{upload_dir}'" or abort 'Failed to upload binary package'
  if ENV['RELEASE_TAG'] && ENV['SF_DEFAULT']
    # Mark the corresponding binary package as default download for each Windows/Mac/Linux host systems
    system "bash -c \"curl -H 'Accept: application/json' -X PUT -d 'default=%s' -d \"api_key=$SF_API\" https://sourceforge.net/projects/%s/files/%s/#{ENV['RELEASE_TAG']}/Urho3D-#{ENV['RELEASE_TAG']}-%s\"" % ENV['SF_DEFAULT'].split(':').insert(1, repo.split('/')).flatten or abort 'Failed to set binary tarball/zip as default download'
  end
end

# Usage: NOT intended to be used manually
desc 'Start/stop the timer'
task :ci_timer do
  timeup
end

# Always call this function last in the multiple conditional check so that the checkpoint message does not being echoed unnecessarily
def timeup quiet = false, cutoff_time = 40.0
  unless File.exists?('start_time.log')
    system 'touch start_time.log split_time.log'
    return nil
  end
  current_time = Time.now
  elapsed_time = (current_time - File.atime('start_time.log')) / 60.0
  unless quiet
    lap_time = (current_time - File.atime('split_time.log')) / 60.0
    system 'touch split_time.log'
    puts "\n=== elapsed time: #{elapsed_time.to_i} minutes #{((elapsed_time - elapsed_time.to_i) * 60.0).round} seconds, lap time: #{lap_time.to_i} minutes #{((lap_time - lap_time.to_i) * 60.0).round} seconds ===\n\n" unless File.exists?('already_timeup.log'); $stdout.flush
  end
  return system('touch already_timeup.log') if elapsed_time > cutoff_time
end

def scaffolding dir, project = 'Scaffolding', target = 'Main'
  begin
    dir = Pathname.new(dir).realdirpath.to_s
  rescue
    abort "Failed to scaffolding due to invalid parent directory in '#{dir}'"
  end
  dir.gsub!(/\//, '\\') if ENV['OS']
  build_script = <<EOF
# Set CMake minimum version and CMake policy required by UrhoCommon module
cmake_minimum_required (VERSION 3.2.3)
if (COMMAND cmake_policy)
    # Libraries linked via full path no longer produce linker search paths
    cmake_policy (SET CMP0003 NEW)
    # INTERFACE_LINK_LIBRARIES defines the link interface
    cmake_policy (SET CMP0022 NEW)
    # Disallow use of the LOCATION target property - so we set to OLD as we still need it
    cmake_policy (SET CMP0026 OLD)
    # MACOSX_RPATH is enabled by default
    cmake_policy (SET CMP0042 NEW)
endif ()

# Set project name
project (#{project})

# Set CMake modules search path
set (CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMake/Modules)

# Include UrhoCommon.cmake module after setting project name
include (UrhoCommon)

# Define target name
set (TARGET_NAME #{target})

# Define source files
define_source_files ()

# Setup target with resource copying
setup_main_executable ()

# Setup test cases
if (URHO3D_ANGELSCRIPT)
    setup_test (NAME ExternalLibAS OPTIONS Scripts/12_PhysicsStressTest.as -w)
endif ()
if (URHO3D_LUA)
    setup_test (NAME ExternalLibLua OPTIONS LuaScripts/12_PhysicsStressTest.lua -w)
endif ()
EOF
  # TODO: Rewrite in pure Ruby when it supports symlink creation on Windows platform and avoid forward/backward slash conversion
  if ENV['OS']
    system("@echo off && mkdir \"#{dir}\"\\bin && copy Source\\Tools\\Urho3DPlayer\\Urho3DPlayer.* \"#{dir}\" >nul && (for %f in (*.bat Rakefile) do mklink \"#{dir}\"\\%f %cd%\\%f >nul) && mklink /D \"#{dir}\"\\CMake %cd%\\CMake && (for %d in (Autoload,CoreData,Data) do mklink /D \"#{dir}\"\\bin\\%d %cd%\\bin\\%d >nul)") && File.write("#{dir}/CMakeLists.txt", build_script) or abort 'Failed to scaffolding'
  else
    system("bash -c \"mkdir -p '#{dir}'/bin && cp Source/Tools/Urho3DPlayer/Urho3DPlayer.* '#{dir}' && for f in {.,}*.sh Rakefile CMake; do ln -sf `pwd`/\\$f '#{dir}'; done && ln -sf `pwd`/bin/{Autoload,CoreData,Data} '#{dir}'/bin\"") && File.write("#{dir}/CMakeLists.txt", build_script) or abort 'Failed to scaffolding'
  end
  return dir
end

def get_root_commit_and_recipients
  # Root commit is a commit submitted by human
  root_commit = `git show -s --format='%H' #{ENV['TRAVIS_COMMIT']}`.rstrip
  recipients = `git show -s --format='%ae %ce' #{root_commit}`.chomp.split.uniq
  if recipients.include? 'urho3d.travis.ci@gmail.com'
    matched = /Commit:.*commit\/(.*?)\n/.match(ENV['COMMIT_MESSAGE'])
    if (matched)
      root_commit = matched[1]
      recipients = `git show -s --format='%ae %ce' #{root_commit}`.chomp.split.uniq
    end
  end
  return root_commit, recipients
end

def android_find_device api = nil, abi = nil
  # Return the previously found matching device or if not found yet then try to find the matching device now
  return $specific_device if $specific_device
  $specific_api = api.to_s if api
  $specific_abi = abi.to_s if abi
  loop do
    for i in `adb devices |tail -n +2`.split "\n"
      device = i.split.first
      if `adb -s #{device} wait-for-device shell getprop ro.build.version.sdk`.chomp == $specific_api && `adb -s #{device} shell getprop ro.product.cpu.abi`.chomp == $specific_abi
        return $specific_device = device
      end
    end
    break if api
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

def android_test_run parameter = '--es pickedLibrary Urho3DPlayer:Scripts/NinjaSnowWar.as', intent = '.SampleLauncher', package = 'com.github.urho3d', success_indicator = 'Added resource path /apk/CoreData/', payload = 'sleep 30'
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

# Usage: wait_for_block('This is a long function call...') { call_a_func } or abort
#        wait_for_block('This is a long system call...') { system 'do_something' } or abort
def wait_for_block comment = '', retries = -1, retry_interval = 60
  # When not using Xcode, execute the code block in full speed
  unless ENV['XCODE']
    puts comment; $stdout.flush
    return yield
  end

  # Wait until the code block is completed or it is killed externally by user via Ctrl+C or when it exceeds the number of retries (if the retries parameter is provided)
  thread = Thread.new { rc = yield; Thread.main.wakeup; rc }
  thread.priority = 1   # Make the worker thread has higher priority than the main thread
  str = comment
  retries = retries * 60 / retry_interval unless retries == -1
  until thread.status == false
    if retries == 0 || timeup(true)
      thread.kill
      # Also kill the child subproceses spawned by the worker thread if specified
      system "killall #{thread[:subcommand_to_kill]}" if thread[:subcommand_to_kill]
      sleep 5
      break
    end
    print str; str = '.'; $stdout.flush   # Flush the standard output stream in case it is buffered to prevent Travis-CI into thinking that the build/test has stalled
    retries -= 1 if retries > 0
    sleep retry_interval
  end
  puts "\n" if str == '.'; $stdout.flush
  thread.join
  return thread.value
end

def append_new_release release, filename = '../urho3d.github.io/_data/urho3d.json'
  begin
    urho3d_hash = JSON.parse File.read filename
    unless urho3d_hash['releases'].last == release
      urho3d_hash['releases'] << release
    end
    File.open(filename, 'w') { |file| file.puts urho3d_hash.to_json }
    return 0
  rescue
    nil
  end
end

def update_web_samples_data dir = '../urho3d.github.io/samples', filename = '../urho3d.github.io/_data/web.json'
  begin
    web = { 'samples' => {} }
    Dir.chdir(dir) { web['samples']['Native'] = Dir['*.html'].sort }
    web['player'] = web['samples']['Native'].pop     # Assume the last sample after sorting is the Urho3DPlayer.html
    {'AngelScript' => 'Scripts', 'Lua' => 'LuaScripts'}.each { |lang, subdir|
      Dir.chdir("bin/Data/#{subdir}") {
        script_samples = Dir['[0-9]*'].sort
        deleted_samples = []    # Delete samples that do not have their native counterpart
        script_samples.each { |sample| deleted_samples.push sample unless web['samples']['Native'].include? "#{sample.split('.').first}.html" }
        web['samples'][lang] = (script_samples - deleted_samples).map { |sample| "#{subdir}/#{sample}" }
      }
    }
    File.open(filename, 'w') { |file| file.puts web.to_json }
    return 0
  rescue
    nil
  end
end

def bump_copyright_year dir='.', regex='2008-[0-9]{4} the Urho3D project'
  begin
    Dir.chdir dir do
      copyrighted = `git grep -El '#{regex}'`.split
      copyrighted.each { |filename|
        replaced_content = File.read(filename).gsub(/#{regex}/, regex.gsub('[0-9]{4}', Time.now.year.to_s))
        File.open(filename, 'w') { |file| file.puts replaced_content }
      }
      return copyrighted
    end
  rescue
    abort 'Failed to bump copyright year'
  end
end

def bump_soversion filename
  begin
    version = File.read(filename).split '.'
    bump_version version, 2
    File.open(filename, 'w') { |file| file.puts version.join '.' }
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
  system "bash -c 'mkdir -p ~/.ssh && chmod 700 ~/.ssh'" or abort 'Failed to create ~/.ssh directory'
  system "bash -c 'ssh-keyscan frs.sourceforge.net >>~/.ssh/known_hosts 2>/dev/null'" or abort 'Failed to append frs.sourceforge.net server public key to known_hosts'
  # Workaround travis encryption key size limitation. Rather than using the solution in their FAQ (using AES to encrypt/decrypt the file and check in the encrypted file into repo), our solution is more pragmatic. The private key below is incomplete. Only the missing portion is encrypted. Much less secure than the original 2048-bit RSA has to offer but good enough for our case.
  system "bash -c 'cat <<EOF >~/.ssh/id_rsa
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
EOF'" or abort 'Failed to create user private key to id_rsa'
  system "bash -c 'chmod 600 ~/.ssh/id_rsa'" or abort 'Failed to change id_rsa file permission'
end

# Load custom rake scripts
Dir['.rake/*.rake'].each { |r| load r }

# vi: set ts=2 sw=2 expandtab:
