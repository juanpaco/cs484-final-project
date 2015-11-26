# This file will read the not-yet-transformed files, transform them, and then
# output the data contained in the files into our format.
#
# We assume that the source files are located in a directory 2 levels up from
# where this file lives.

require 'nokogiri'

source_path = "../../scriptures/bofm"
destination_directory = "data"

def book_and_chapter_from_path(path)
  { 
    :book => path.split('/')[-3],
    :chapter => path.split('/')[-2]
  }
end

def cleanse_string(str)
  str.gsub(/[,;()!:]/,"")
     .gsub(/[\.\u2013\u2014]/, ' ')
     .gsub('  ', ' ')
     .downcase
end

Dir.glob("#{source_path}/*/*/*.xml").each do |path|
  # Extract the book and chapter
  file_data = book_and_chapter_from_path(path)

  file_as_xml = File.open(path) { |f| Nokogiri::XML(f) }

  # Extract the header
  file_data[:header] = 
    cleanse_string(file_as_xml.xpath("//description")[0].children[0].to_s)

  # Clean out the bookmarks and such
  file_as_xml.xpath("//sup").remove
  file_as_xml.xpath("//verse-no").remove

  # remove the links, but keep the text inside of them
  nodes = file_as_xml.search("a")
  nodes.each {|node| node.replace(node.content) }

  # Extract the text of the chapter
  file_data[:body] =
    file_as_xml.xpath("//div[@class='bodyBlock']/block/text()").to_s

  file_data[:body] = cleanse_string(file_data[:body])

  output_path =
    "#{destination_directory}/#{file_data[:book]}.#{file_data[:chapter]}.txt"

  File.open(output_path, "w") do |f|
    f.puts file_data[:book]
    f.puts file_data[:chapter]
    f.puts file_data[:header]
    f.puts file_data[:body]
  end
end

