#
# Copyright (c) 2008-2020 the Urho3D project.
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

desc 'Prepare environment for CI'
task :ci do
  ENV['URHO3D_PCH'] = '0' if ENV['PLATFORM'] == 'linux-gcc' # TODO - PCH causes cache miss on initial build for Linux/GCC, why?
  platform_modifier = /(.+?)-(.+)/.match(ENV['PLATFORM'])
  if platform_modifier
    ENV['PLATFORM'] = platform_modifier[1]
    ENV['MODIFIER'] = platform_modifier[2]
  end
  case ENV['HOST']
  when 'macOS'
    ENV['GENERATOR'] = ENV['URHO3D_DEPLOYMENT_TARGET'] = 'generic' if ENV['MODIFIER'] == 'make'
    ENV['BUILD_PARAMS'] = '-sdk iphonesimulator' if ENV['PLATFORM'] == 'iOS'
    ENV['BUILD_PARAMS'] = '-sdk appletvsimulator' if ENV['PLATFORM'] == 'tvOS'
  when 'windows'
    if ENV['MODIFIER'] == 'gcc'
      ENV['URHO3D_DEPLOYMENT_TARGET'] = 'generic'
      ENV['GENERATOR'] = 'mingw'
    end
  else
    ENV['URHO3D_DEPLOYMENT_TARGET'] = 'generic' if /linux|mingw/ =~ ENV['PLATFORM']
    if /clang/ =~ ENV['MODIFIER']
      ENV['CC'] = 'clang'
      ENV['CXX'] = 'clang++'
    end
  end
  ENV['BUILD_TREE'] = 'build/ci'
  ENV['CMAKE_BUILD_TYPE'] = ENV['BUILD_TYPE'] == 'dbg' ? 'Debug' : 'Release' unless ENV.fetch('BUILD_TYPE', '').empty?
  case ENV['GRAPHICS_API']
  when 'DX11'
    ENV['URHO3D_D3D11'] = '1'
  when 'DX9'
    ENV['URHO3D_OPENGL'] = '0' # Need to make this explicit because 'MINGW' default to use OpenGL otherwise
  when 'OpenGL'
    ENV['URHO3D_OPENGL'] = '1'
  else
    # Do nothing
  end
  ENV['URHO3D_LIB_TYPE'] = ENV['LIB_TYPE'].upcase
  ENV['URHO3D_TESTING'] = '1' if /linux|macOS|win/ =~ ENV['PLATFORM']
  ENV['URHO3D_LINT'] = '1' if ENV['MODIFIER'] == 'clang-tidy'
  ENV['URHO3D_STYLE'] = '1' if ENV['MODIFIER'] == 'clang-format'
  # Enable all the bells and whistles
  %w[URHO3D_DATABASE_SQLITE URHO3D_EXTRAS].each { |it| ENV[it] = '1' }
end

desc 'Generate the SHA256 digest based on all the C/C++ source files'
task :source_checksum do
  require 'digest'
  sha256_final = Digest::SHA256.new
  sha256_iter = Digest::SHA256
  Dir['Source/**/*.{c,h}*'].each { |it| sha256_final << sha256_iter.file(it).hexdigest }
  puts "::set-output name=hexdigest::#{sha256_final.hexdigest}"
end

desc 'Ensure all dot files are up-to-date'
task :update_dot_files do
  system 'bash', '-c', %q{
    perl -ne 'undef $/; print $1 if /(Build Option.*?(?=\n\n))/s' Docs/GettingStarted.dox \
      |tail -n +3 |cut -d'|' -f2 |tr -d [:blank:] >script/.build-options && \
    echo URHO3D_LINT >>script/.build-options && \
    cat script/.build-options <(perl -ne 'while (/([A-Z_]+):.+?/g) {print "$1\n"}' .github/workflows/main.yml) \
      <(perl -ne 'while (/ENV\[\x27(\w+)\x27\]/g) {print "$1\n"}' Rakefile) \
      <(perl -ne 'while (/System.getenv\\("(\w+)"\\)/g) {print "$1\n"}' android/urho3d-lib/build.gradle.kts) \
      |sort |uniq |grep -Ev '^(HOME|PATH)$' >script/.env-file
  } or abort 'Failed to update dot files'
end

# vi: set ts=2 sw=2 expandtab:
