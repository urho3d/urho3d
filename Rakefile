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

task default: 'build'

desc 'Invoke CMake to configure and generate a build tree'
task :cmake do
  if ENV['CI']
    system 'cmake --version' or abort 'Failed to find CMake'
    puts
  end
  ENV['PLATFORM'] = 'native' unless ENV['PLATFORM']
  build_tree = ENV["#{ENV['PLATFORM']}_BUILD_TREE"] || ENV['BUILD_TREE'] || "build/#{ENV['PLATFORM']}"
  next if Dir.exist?("'#{build_tree}'")
  unless ENV['GENERATOR']
    case ENV['HOST'] || RUBY_PLATFORM
    when /linux/
      ENV['GENERATOR'] = 'generic'
    when /darwin|macOS/
      ENV['GENERATOR'] = 'xcode'
    when /win32|mingw|mswin|windows/
      ENV['GENERATOR'] = 'vs'
    else
      abort "Unsupported host system: #{ENV['HOST'] || RUBY_PLATFORM}"
    end
  end
  script = "script/cmake_#{ENV['GENERATOR']}#{ENV['OS'] ? '.bat' : '.sh'}"
  build_options = ENV['PLATFORM'] == 'native' ? '' : "-D #{ENV['PLATFORM'].upcase}=1"
  File.readlines('script/.build-options').each { |var|
    var.chomp!
    build_options = "#{build_options} -D #{var}=#{ENV[var]}" if ENV[var]
  }
  system "#{script} '#{build_tree}' #{build_options}" or abort
end

desc 'Build the software'
task build: [:cmake] do
  puts "TODO: build #{ENV['CI']} #{ENV['PLATFORM']} #{ENV['MODIFIER']}"
end

# Load custom rake scripts
Dir['.github/workflows/*.rake'].each { |r| load r }
Dir['.rake/*.rake'].each { |r| load r }

# vi: set ts=2 sw=2 expandtab:
