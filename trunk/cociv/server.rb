#!/usr/bin/env ruby

require 'socket'
require 'readline'

$: << '.'
require 'cociv/driver'


class Connection

  def initialize(session)
    @session = session
    @joined = nil
    puts "connected!"
  end

  def listen(drivers)
    while line = recv
      if @joined
        joined_input(line)
      else
        non_joined_input(line, drivers)
      end
    end
  end

  def recv
    @session.gets
  end

  def send(s)
    @session.puts(s)
  end

  def non_joined_input(line, drivers)
    cmd, *pars = line.split
    if cmd == 'START'
      @driver = Driver.new
      drivers << @driver
      send "OK #{driver.number}"
    elsif cmd == 'LIST'
    elsif cmd == 'JOIN'
      @driver.join(self)
      @joined = @driver
    else
      syntax_error(line)
    end
  end

  def syntax_error(line)
    send "ERR Syntax error.\n"
  end

end


class Server

  def initialize
    @connections = []
    @drivers = []
  end

  def run_on_background!
    Thread.abort_on_exception = true
    Thread.start do
      server = TCPServer.new(20011)
      while (session = server.accept)
        Thread.start do
          c = Connection.new(session)
          c.listen(@drivers)
        end
      end
    end
  end

  def start_interface!
    while line = Readline.readline('> ', true)
    end  
  end

end


server = Server.new
server.run_on_background!
server.start_interface!

