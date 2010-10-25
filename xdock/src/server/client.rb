require 'socket'

s = TCPSocket.new('localhost', 52530)
s.puts <<EOF
# create panel
PANEL 4 4 88 88
UPDATE

# sending XPM
SEND_XPM
16 7 2 1
* c #000000
. c #ffffff
**..*...........
*.*.*...........
**..*..**.**..**
*.*.*.*.*.*..*.*
**..*..**.*...**
...............*
.............**.
.
DRAW_IMAGE 0 10 10
UPDATE
EOF
print s.gets

while true; end
