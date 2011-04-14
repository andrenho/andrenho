// video: 480x275


function CPU68k()
{
    this.D = [ 0, 0, 0, 0, 0, 0, 0 ];
    this.A = [ 0, 0, 0, 0, 0, 0, 0 ];
}


function Memory(size)
{
    this.data = [];
    for(i=0; i<size; i++)
        this.data[i] = 0;
}


function Machine()
{
    this.load_rom = function(url)
    {
        var req = new XMLHttpRequest();        
        req.open('GET', url, false);
        req.overrideMimeType('text/plain; charset=x-user-defined');
        req.send(null);
        if (req.status == 200)
        {
 //           for(i=0; i<req.responseText.length; i++)
   //             this.memory.data[i] = req.responseText.charAt(i);
            return true;
        }
        else
            return false;
    }

    // initialize video (character)
    function init_video()
    {
        s = '';
        for(y=0; y<25; y++)
            for(x=0; x<80; x++)
                s += '<span name="c_'+x+'_'+y+'" ' +
                        'class="character" ' + 
                        'style="' + //position:absolute;' +
                            'left:' + (x*6) + 'px;' +
                            'top:' + (y*11) + 'px;' +
                            '">.</span>';
        alert(document.getElementById('machine').getElementById('video'));
        document.getElementById('video').innerHTML = s;
    }

    init_video();
    this.cpu = CPU68k();
    this.memory = Memory(64*1024);
}
