# BRX assembler
#
# 1. Preprocess
#   - Remove comments
#   - Transform data
#   - Apply directives
#     - %include
#     - %define
#     - %ifdef, %ifndef, %else, %endif
#     - %func, %endfunc
#     - %pragma
# 2. First pass
#   - change labels
# 3. Second pass
#   - assemble

$defines = {}

def assemble
  code = STDIN.readlines
  code = preprocess(code)
  code = first_pass(code)
  code = second_pass(code)
  puts code.join("\n")
end

def preprocess(code)
  lines = []
  n = 1
  code.each do |line|
    line = transform_data(line, n)
    line = remove_comments(line.chomp, n)
    lines << apply_directives(line, n)
    n += 1
  end
  return lines
end

def first_pass(code)
  return code
end

def second_pass(code)
  return code
end

def transform_data(line, n)
  if line.split[0].downcase == 'data'
    dt = []
    line.split[1..-1].join(' ').split(',').each do |data|
      data.strip!
      if data[0] == '"' and data[-1] == '"'
        data[1..-2].each_char { |c| dt << c.ord }
      elsif data[0] == '$'
        dt << data[1..-1].to_i(16)
      elsif data[0] == '\'' and data[2] == '\''
        dt << data[1].ord
      elsif data =~ /\d+/
        dt << data.to_i
      else
        STDERR.puts "Invalid data in line #{n}: #{data}."
        exit 1
      end
    end
    return "\tdata #{dt.map{ |v| '$' + ('%02x' % v) }.join(', ')}"
  else
    return line
  end
end

def remove_comments(line, n)
  return line.split(';')[0]
end

def apply_directives(line, n)
  if line[0] == '%'
    directive = line.split[0]
    if directive == '%define'
      d = line.split[1]
      v = line.split[2..-1].join(' ')
      $defines[d] = v
    end
  else
    return line
  end
end

assemble
