-- TODO: global variables

token = {}
reserved_words = { 'func' }
basic_types = { 'byte', 'int', 'real' }
line = 1
c = ''
fct = nil

function init()
   c = io.read(1)
   get_token()
end


function get_token(tp, text)
   token = { text = '' }

   -- EOF
   if c == nil then
      token = nil

   -- text
   elseif c:match('%a') or c == '_' then 
      while c:match('%a') or c:match('%d') do
         token.text = token.text .. c
         c = io.read(1)
      end
      token.type = 'id'
      for _,reserved in ipairs(reserved_words) do
         if token.text == reserved then token.type = 'reserved' end
      end
      for _,tp in ipairs(basic_types) do
         if token.text == tp then token.type = 'type' end
      end

   -- number
   elseif c:match('%d') or c == '.' then
      while c:match('%d') or c == '.' do
         token.text = token.text .. c
         c = io.read(1)
      end
      token.type = 'number'
      if c:match('%a') or c == '_' then
         _error('Invalid number ' .. token.text .. c)
      end
      token.text = tonumber(token.text)

   -- blank
   elseif c == ' ' or c == '\t' or c == '\n' then
      if c == '\n' then line = line + 1 end
      c = io.read(1)
      get_token()

   -- other
   else
      token.type = 'symbol'
      token.text = c
      c = io.read(1)
   end

   if tp and tp ~= token.type then expected(text or tp) end
   if text and text ~= token.text then expected(tp) end
end


-----------------------------------------------------


function expected(text)
   io.stderr:write(('error in line %d: expected %s, found %s.\n'):format(line, text, token.text))
   os.exit(1)
end


function _error(text)
   io.stderr:write(('error in line %d: %s.\n'):format(line, text))
   os.exit(1)
end


function is_type()
   return token.type == 'type'
end


function type_size(tp)
	if tp == 'byte' then
		return 8
	elseif tp == 'int' or tp == 'real' then
		return 32
	else
		error('unknown size for type %s', tp)
	end
end


-----------------------------------------------------


function primary_exp()
   if token.type == 'number' then
      if math.floor(token.text) ~= token.text then
         exp_type = 'real'
      elseif token.text <= 255 then
         exp_type = 'byte'
      else
         exp_type = 'int'
      end
      code('mov $a, %d  ; type: %s', token.text, exp_type)
	elseif token.type == 'id' then
	   var = fct.vars[token.text]
		if not var then error('Variable %s not found', token.text) end
		code('mov $a, $fp-%d', var.addr)
		if c ~= '(' then -- not a function
			code('mov $a, [$a]')
		end
   elseif token.text == '(' then
      get_token()
      exp_type = primary_exp()
      if token.text ~= ')' then expected(')') end
	else
		expected("'(', number or id")
   end
   get_token()
   return exp_type
end


function prefix_exp()
   if token.text == '-' then
      get_token()
      exp_type = primary_exp()
      code('neg $a')
      return exp_type
   elseif token.text == '!' then
      get_token()
      primary_exp()
      i = fct_label()
      code('bzr $a, %s_%d', fct.name, i)
      code('mov $a, 1')
      label('%s_%d:', fct.name, i)
      return 'byte'
   else
      return primary_exp()
   end
end


function postfix_exp()
	exp_type = prefix_exp()
	if token.text == '(' then
		-- TODO parameters
		get_token('symbol', ')')
		code('jsr $a')
	end
end


--[[
function cast_exp()
   if token.text == '<' then
      get_token()
      exp_type = prefix_
end
]]


function expression()
   postfix_exp()
end


-----------------------------------------------------


function return_stmt()
   get_token()
   expression()
   code("ret")
   if token.text ~= ';' then
      expected("';'")
   end
	get_token()
end


function statement()
   if is_type() then
      variable_decl()
   elseif token.text == 'if' then
      if_stmt()
   elseif token.text == 'while' then
      while_stmt()
   elseif token.text == 'return' then
      return_stmt()
   elseif token.text == 'asm' then
      asm_stmt()
   else
      expected('statement or variable declaration')
   end
end


function block()
   if token.text == '{' then
      get_token()
      repeat
         statement()
      until token.text == '}'
      get_token()
   else
      statement()
   end
end


function variable_decl()
   tp = token.text
	sz = type_size(tp)
   get_token('id')
   name = token.text
   get_token('symbol', '=')
	get_token()
   expression()
   if token.text ~= ';' then expected("';'") end
	get_token()
	
	if sz == 8 then
		code('push8 $a')
	elseif sz == 32 then
		code('push $a')
	else
		assert(false)
	end

	fct.var_addr = fct.var_addr + sz
	fct.vars[name] = { type = tp, addr = fct.var_addr }
end


function function_decl()
   get_token('id')
   fct_name = token.text
   get_token('symbol', '(')
   --TODO: parameters
   get_token('symbol', ')')
   get_token('symbol', ':')
   get_token('type')
   fct_type = token.text
   fct = { name = fct_name, 
	        type = fct_type, 
			  counter = 1, 
			  var_addr = 0, 
			  vars = {} }
   fct_open(fct)
   get_token()
   block()
   fct_close(fct)
end


function source()
   executable_open()
   while token do
      if is_type() then
         variable_decl()
      elseif token.text == 'func' then
         function_decl()
      elseif token.text == 'enum' then
         enum_decl()
      else
         expected("type, 'func' or 'enum'")
      end
      get_token()
   end
   executable_close()
end


-----------------------------------------------------


function code(format, ...)
   if arg[1] then
      io.stdout:write(string.format('\t'..format..'\n', unpack(arg)))
   elseif format then
      io.stdout:write('\t'..format..'\n')
   else
      io.stdout:write('\n')
   end
end

function label(format, ...)
   if arg[1] then
      io.stdout:write(string.format(format..'\n', unpack(arg)))
   elseif format then
      io.stdout:write(format..'\n')
   else
      io.stdout:write('\n')
   end
end

function executable_open()
end

function executable_close()
   code()
   code('jsr main')
   code('syscall EXIT')
end

function fct_open()
   code('jmp %s_exit', fct.name)
   code()
   label(fct.name..':')
end

function fct_label()
   fct.counter = fct.counter + 1
   return fct.counter - 1
end

function fct_close()
   label('%s_exit:', fct.name)
end


--------------------------------------------------


init()
source()
