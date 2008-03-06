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
user = sock.gets
puts "User: #{user}"

sock.putc '+'
pass = sock.gets
puts "Password: #{pass}"

buffer = sock.gets("OK")

puts 'file received'
