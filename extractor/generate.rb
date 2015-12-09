require 'faker'

destination_directory = "data"

100.times do |i|
  outfile = "#{destination_directory}/#{i}.dummy.txt"

  File.open(outfile, "w") do |f|
    1000.times do |who_cares|
      f.puts Faker::Lorem.characters(1024)
    end
  end
end
