require 'socket'

s = TCPSocket.new('localhost', 52530)

puts s.gets

s.puts <<EOF
HELLO HELLO

# create panel
PANEL 5 5 86 86
UPDATE

# write chars
WRITE led2 10 10 "01234"
WRITE led2 10 36 "STUVWX"
WRITE led2 10 62 "YZ"
UPDATE

UPDATE
EOF

puts s.gets

while true; sleep 1; end
