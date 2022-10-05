require 'json'
pjson = JSON.parse(File.read('../package.json'))

Pod::Spec.new do |s|

  s.name            = "RCTPanel"
  s.version         = pjson["version"]
  s.homepage        = pjson["repository"]
  s.summary         = pjson["description"]
  s.license         = pjson["license"]
  s.author          = pjson["author"]
  s.osx.deployment_target = '11.0'

  s.source          = { :git => "https://github.com/jihoobyeon/react-native-macos-panel.git", :tag => "v#{s.version}" }
  s.source_files    = '*.{h,m}'
  s.preserve_paths  = "**/*.js"

  s.dependency 'React'
end
