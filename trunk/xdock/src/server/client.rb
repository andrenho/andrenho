require 'socket'

s = TCPSocket.new('localhost', 52530)

puts s.gets

s.puts <<EOF
HELLO HELLO

# create panel
PANEL 5 5 86 86
UPDATE

# write chars
WRITE led3 10 30 "HELLO_WORLD"
UPDATE

# sending XPM
SEND_XPM blarg
16 7 2 1
* c #000000 s lit
. c #ffffff s panel_bg
**..*...........
*.*.*...........
**..*..**.**..**
*.*.*.*.*.*..*.*
**..*..**.*...**
...............*
.............**.
.
DRAW_IMAGE blarg 10 10
UPDATE
EOF

puts s.gets

while true; sleep 1; end
