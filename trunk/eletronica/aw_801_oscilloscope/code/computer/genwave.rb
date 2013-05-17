#!/usr/bin/ruby

$step = 1

def f(t)
    return Math.sin(Math::PI / (t.to_f % 100)) * 5.0
end

#------------------------------

$t = 1
while true
    begin
        puts (f($t) * 1024.0 / 5.0).to_i
    rescue FloatDomainError
        puts 0
    end
    $t += 1
end

# vim:set ts=4 sw=4 sts=4 expandtab:
