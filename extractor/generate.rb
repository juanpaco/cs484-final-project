destination_directory = "data"

32.times do |i|
  outfile = "#{destination_directory}/#{i+32}.dummy.txt"

  chunksize = 1073741824/(32-i)

  puts outfile

  `dd if=/dev/zero of=#{outfile} bs=#{chunksize} count=1`
end
