token = {}
reserved_words = { 'func' }
basic_types = { 'byte', 'int' }
double_symbols = { '<<', '>>', '<=', '>=' }
line = 1
c = ''
global = { name = '__global', 
        type = 'global', 
        counter = 1, 
        var_addr = 0, 
        vars = {} }


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
   elseif c:match('%a') or c == '_' or c == '$' then 
      while c:match('%a') or c:match('%d') or c == '_' or c == '$' do
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

      dbl = token.text .. c
      for _,symbol in ipairs(double_symbols) do
         if dbl == symbol then
            token.text = token.text .. c
            c = io.read(1)
         end
      end
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
   elseif tp == 'int' then
      return 32
   else
      _error('unknown size for type %s', tp)
   end
end


-----------------------------------------------------


function primary_exp()
   local exp_type
   if token.type == 'number' then
      if token.text >= 0 and token.text <= 255 then
         exp_type = 'byte'
      else
         exp_type = 'int'
      end
      code('mov #a, %d  ; type: %s', token.text, exp_type)
   elseif token.type == 'id' then
      local var
      if token.text:sub(1,1) == '$' then
         var = global.vars[token.text]
         code('mov #a, %s', token.text)
         exp_type = var.type
      else
         var = fct.vars[token.text]
         code('mov #a, $fp-%d', var.addr)
         exp_type = var.type
      end
      if not var then _error('Variable %s not found', token.text) end
      if c ~= '(' then -- not a function
         code('mov #a, [#a]')
      end
   elseif token.text == '(' then
      get_token()
      exp_type = expression()
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
      local exp_type = primary_exp()
      code('neg #a')
      return exp_type
   elseif token.text == '!' then
      get_token()
      primary_exp()
      local i = fct_label()
      code('bzr %s_%d', fct.name, i)
      code('mov #a, 1')
      label('%s_%d:', fct.name, i)
      return 'byte'
   else
      return primary_exp()
   end
end


function postfix_exp()
   local exp_type = prefix_exp()
   if token.text == '(' then
      -- TODO parameters
      get_token('symbol', ')')
      code('jsr #a')
      get_token()
   end
   return exp_type
end


function cast_exp()
   -- TODO convert to type
   if token.text == '<' then
      get_token('type')
      get_token('symbol', '>')
      get_token()
   end
   return postfix_exp()
end


function mul_exp()
   local exp_type1 = cast_exp()
   while token.text == '*' or token.text == '/' or token.text == '%' do
      local op = token.text
      code('push #a')
      get_token()
      local exp_type2 = cast_exp()
      code('pop #b')
      if op == '*' then
         code('mul')
      elseif op == '/' then
         code('swap')
         code('div')
      elseif op == '%' then
         code('mod')
      end
   end
   return exp_type1
end


function add_exp()
   local exp_type1 = mul_exp()
   while token.text == '+' or token.text == '-' do
      local op = token.text
      code('push #a')
      get_token()
      local exp_type2 = mul_exp()
      code('pop #b')
      if op == '+' then
         code('add')
      elseif op == '-' then
         code('sub')
      end
   end
   return exp_type1
end


function shift_exp()
   local exp_type1 = add_exp()
   while token.text == '<<' or token.text == '>>' do
      local op = token.text
      code('push #a')
      get_token()
      local exp_type2 = add_exp()
      code('pop #b')
      if op == '<<' then
         code('shl')
      elseif op == '>>' then
         code('shr')
      end
   end
   return exp_type1
end


function relational_exp()
   local exp_type1 = shift_exp()
   while token.text == '<' or token.text == '>' or token.text == '<=' or token.text == '>=' do
      local op = token.text
      code('push #a')
      get_token()
      local exp_type2 = shift_exp()
      code('pop #b')
      local i = fct_label()
      if op == '<' then
         code('bl %s_%d', fct.name, i)
      elseif op == '>' then
         code('bg %s_%d', fct.name, i)
      elseif op == '<=' then
         code('ble %s_%d', fct.name, i)
      elseif op == '>=' then
         code('bge %s_%d', fct.name, i)
      end
      code('mov #a, 0')
      label('%s_%d:', fct.name, i)
   end
   return exp_type1
end


function expression()
   relational_exp()
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
   if fct.name ~= '__global' and name:sub(1,1) == '$' then
      _error('Global ' .. name .. ' can\'t be declared inside a function.')
   end

   get_token('symbol', '=')
   get_token()
   expression()
   if token.text ~= ';' then expected("';'") end
   get_token()
   
   if sz == 8 then
      code('push8 #a')
   elseif sz == 32 then
      code('push #a')
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

   -- register global
   global.vars[fct_name] = { type = fct_type }
   
   fct = { name = fct_name, 
           type = fct_type, 
           counter = 1, 
           var_addr = 0, 
           vars = {} }
   fct_open(fct)
   get_token()
   block()
   fct_close(fct)
   fct = nil
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
