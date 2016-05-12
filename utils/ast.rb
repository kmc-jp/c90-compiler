#! /usr/bin/ruby

require 'pry'
require 'erb'

content = File.read("src/ast.h")
m = content.gsub(/ /, "").match(/\{(.*)\}/m)

Tags = []

m[0].split("\n").slice(0..-3).each do |e|
  if e != "" && e != "{" && e != "}" then
    e.gsub!(/,/, "")
    Tags << e
  end
end

#puts Tags

content = File.read("src/ast/ast_impl.h")
m = content.match(/union AstData \{(.*)AstTokenRef token;/m)

Types = []
m[0].split("\n").slice(1..-1).each do |e|
  if e != "" && e != "{" && e != "}" then
    Types << e.split(/ /)[-1].gsub(/;/, "")
  end
end

@pairs = Tags.zip(Types)
fname = "utils/ast_visualizer.c.erb"
erb = ERB.new(File.read(fname))
erb.filename = fname
puts erb.result(binding)
