// video: 480x275

function CPU68k()
{
    this.D = [ 0, 0, 0, 0, 0, 0, 0 ];
    this.A = [ 0, 0, 0, 0, 0, 0, 0 ];
    this.pc = 0x40000;

    this.instruction_description = function(pos)
    {
        return { desc:'Not identified!', size:2 };
    }
}


function MemoryMap()
{
    this.init_mem = 0x40000;

    this.set = function(pos, data)
    {
    }
}


function Memory(mmap, size)
{
    this.data = [];
    this.size = size;
    this.mmap = mmap;
    for(i=0; i<size; i++)
        this.data[i] = 0;

    this.get = function(pos)
    {
        if(pos < 0 || pos > this.size)
            alert('Invalid memory position ' + pos + '.');
        return this.data[pos];
    }

    this.set = function(pos, data)
    {
        if(pos < 0 || pos > this.size)
            alert('Invalid memory position ' + pos + '.');
        if(data > 0xff || data < 0)
            alert('Invalid memory data ' + data + '.');
        this.mmap.set(pos, data);
        this.data[pos] = data;
    }
}


function Machine()
{
    this.load_bios = function(url)
    {
        var req = new XMLHttpRequest();        
        req.open('GET', url, false);
        req.overrideMimeType('text/plain; charset=x-user-defined');
        req.send(null);
        if (req.status == 200)
        {
            if(req.responseText.length + this.mmap.init_mem > this.memory.size)
                return false;
            for(i=0; i<req.responseText.length; i++)
                this.memory.data[i+this.mmap.init_mem] = req.responseText.charCodeAt(i);
            return true;
        }
        else
            return false;
    }

    this.cpu = new CPU68k();
    this.mmap = new MemoryMap();
    this.memory = new Memory(this.mmap, 1024*1024); // 1 Mb
}
