require 'socket'

s = TCPSocket.new('localhost', 52530)
s.puts <<EOF
# create panel
PANEL 4 4 88 88
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

while true; end
