function Debug(machine)
{
    this.machine = machine;

    // initialize debugger
    this.init = function()
    {
        init_cpu_debugger();
    }

    function init_cpu_debugger()
    {
        regs = [ 'D0', 'D1', 'D2', 'D3', 'D4', 'D5', 'D6', 'D7', 
                 'A0', 'A1', 'A2', 'A3', 'A4', 'A5', 'A6', 'A7' ];
        flags = [ 'C', 'V', 'Z', 'N', 'X', 'I0', 'I1', 'I2', 'M', 'S', 'T0', 'T1' ];

        for(n=0; n<regs.length; n++)
        {
            $('tr.register_names').append('<td class="register">' + regs[n] + '</td>');
            $('tr.register_hex').append('<td class="register">0000</td>');
            $('tr.register_dec').append('<td class="register" style="text-align: right;">0</td>');
        }
        for(n=0; n<flags.length; n++)
        {
            $('tr.flag_names').append('<td class="flag">' + flags[n] + '</td>');
            $('tr.flag_value').append('<td class="flag">&nbsp;</td>');
        }
    }
}
