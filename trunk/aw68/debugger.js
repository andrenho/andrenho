function Debug(machine)
{
    this.machine = machine;

    // initialize debugger
    this.init = function()
    {
        init_cpu_debugger();
    }

    
    this.update_cpu_instructions = function(from, to)
    {
        tbl = [];
        pos = from;
        while(pos < to)
        {
            inst = machine.cpu.instruction_description(pos);
            
            if(machine.cpu.pc == pos)
                tbl.push('<tr class="pc">');
            else
                tbl.push('<tr>');
            tbl.push('<td style="width: 40px;">');
            tbl.push(pos.toString(16));
            tbl.push('</td>');
            tbl.push('<td style="width: 45px;">');
            for(i=0; i<inst.size; i++)
                tbl.push(machine.memory.get(pos+i).hex16());
            tbl.push('</td>');
            tbl.push('<td>' + inst.desc + '</td></tr>');

            pos += inst.size;
        }

        document.getElementById('instruction_table').innerHTML = tbl.join('');
    }


    function init_cpu_debugger()
    {
        // registers
        regs = [ 'D0', 'D1', 'D2', 'D3', 'D4', 'D5', 'D6', 'D7', 
                 'A0', 'A1', 'A2', 'A3', 'A4', 'A5', 'A6', 'A7' ];
        flags = [ 'C', 'V', 'Z', 'N', 'X', 'I0', 'I1', 'I2', 'M', 'S', 'T0', 'T1' ];

        tr_regs = [];
        tr_flags = [];
        for(n=0; n<regs.length; n++)
            tr_regs.push('<tr>' + 
                           '<td style="width:15px;">' + regs[n] + '</td>' +
                           '<td>0000</td>' +
                           '<td style="width:20px;text-align:right;">0</td>' +
                         '</tr>');
        for(n=0; n<flags.length; n++)
            tr_flags.push('<tr>' +
                           '<td style="width:15px;">' + flags[n] + '</td>' +
                           '<td>0</td>' +
                         '</tr>');
        document.getElementById('register_table').innerHTML = tr_regs.join('');
        document.getElementById('flag_table').innerHTML = tr_flags.join('');
    }
}


// screen events
function load_bios()
{
   if(machine.load_bios(document.getElementById('bios_name').value))
   {
      document.getElementById('message').innerHTML = 'ROM loaded successfully.';
      debug.update_cpu_instructions(machine.mmap.init_mem, machine.mmap.init_mem+500);
   }
   else
      document.getElementById('message').innerHTML = 'Error loading ROM.';
}


// util
Number.prototype.hex16 = function()
{
    s = '';
    if(this < 0x10)
        s = '0';
    return s + this.toString(16);
}
