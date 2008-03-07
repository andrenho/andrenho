require 'socket'
serv = TCPServer.new(21)
begin
  sock = serv.accept_nonblock
rescue
  IO.select([serv])
  retry
end
puts 'Socket connected.'

sock.putc '+'
puts '>> +'
user = sock.gets
puts "<< #{user}"

sock.putc '+'
puts '>> +'
pass = sock.gets
puts "<< #{pass}"

sock.putc '+'
puts '>> +'
buffer = sock.gets("OK")

puts ">> #{buffer}"
