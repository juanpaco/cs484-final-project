destination_directory = "data"

# Yanked this from the Faker gem.  We can't seem to install gems on the open
# labs, so I just grabbed the function that we need.
def characters(char_count = 255)
  rand(36**char_count).to_s(36).rjust(char_count, '0').chars.to_a.shuffle.join
end

1000.times do |i|
  outfile = "#{destination_directory}/#{i}.dummy.txt"

  File.open(outfile, "w") do |f|
    5000.times do |who_cares|
      f.puts characters(1024)
    end
  end
end
