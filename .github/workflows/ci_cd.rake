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
  platform_modifier = /(.*)-(.+)/.match(ENV['PLATFORM'])
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
    if ENV['MODIFIER'] == 'clang'
      ENV['CC'] = 'clang'
      ENV['CXX'] = 'clang++'
    end
  end
  ENV['BUILD_TREE'] = 'build/ci'
  ENV['URHO3D_64BIT'] = ENV['ARCH'] == '32bit' ? '0' : '1' unless ENV.fetch('ARCH', '').empty?
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
  ENV['URHO3D_LIB_TYPE'] = ENV['LIB_TYPE']
  ENV['URHO3D_TESTING'] = '1' if /linux|macOS|win/ =~ ENV['PLATFORM']
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

# vi: set ts=2 sw=2 expandtab:
