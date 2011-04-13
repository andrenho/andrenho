// video: 480x275


function CPU68k()
{
    this.D = [ 0, 0, 0, 0, 0, 0, 0 ];
    this.A = [ 0, 0, 0, 0, 0, 0, 0 ];
}


function Machine()
{
    // initialize video (character)
    function init_video()
    {
        for(y=0; y<25; y++)
            for(x=0; x<80; x++)
                $('div.video').append('<span name="c_'+x+'_'+y+'" ' +
                        'class="character" ' + 
                        'style="' + //position:absolute;' +
                            'left:' + (x*6) + 'px;' +
                            'top:' + (y*11) + 'px;' +
                            '"></span>');
    }

    init_video();
    this.cpu = CPU68k();
}
