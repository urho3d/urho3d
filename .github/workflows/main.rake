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
    ENV['GENERATOR'] = 'mingw' if ENV['MODIFIER'] == 'gcc'
  else
    if ENV['MODIFIER'] == 'clang'
      ENV['CC'] = 'clang'
      ENV['CXX'] = 'clang++'
    end
  end
  ENV['BUILD_TREE'] = 'build/ci'
  ENV['URHO3D_64BIT'] = ENV['ARCH'] == '32bit' ? '0' : '1' unless ENV.fetch('ARCH', '').empty?
  ENV['URHO3D_LIB_TYPE'] = ENV['LIB_TYPE']
  # Enable all the bells and whistles
  %w[URHO3D_DATABASE_SQLITE URHO3D_EXTRAS].each { |it| ENV[it] = '1' }
end

# vi: set ts=2 sw=2 expandtab:
