#!/usr/bin/ruby

$step = 1

def f(t)
    x = 0.3
    if (t/1000) % 2 == 0
        x = 5.0
    end
    return x - 0.2 + rand(0.4)
end

#------------------------------

$t = 0
while true
    puts f($t)
    $t += 1
end

# vim:set ts=4 sw=4 sts=4 expandtab:
