import re, io, os, sys


class Format(str):
    def __init__(self, fmt):
        if fmt not in ('ebk'):
            raise 'Format ' + fmt + ' not supported.'
        self.fmt = fmt
        self.attributes = dict()


class Tag(str):
    def __init__(self, tag):
        self.tag = tag
        self.attr = dict()


class Book:

    def __init__(self, file, fmt):
        self.title = None
        self.author = ''
        self.text = []
        if fmt.fmt == 'ebk':
            self.import_ebk(file, fmt)
        else:
            os.abort()
            

    def export(self, file, fmt):
        if fmt.fmt == 'ebk':
            self.export_ebk(file, fmt)
        else:
            os.abort()
            

    def import_ebk(self, file, fmt):
        if file == None:
            f = sys.stdin
        else:
            f = open(file, 'r', io.DEFAULT_BUFFER_SIZE, 'utf-8', 'strict')
        data = f.read()
        f.close()

        self.text = []
        for part in re.split("(\<.+?\>)", data):
            if part != '':
                if part[0] == '<':
                    cmd, attrs = part.split(' ', 1)
                    tag = Tag(cmd)
                    attrs = re.split("(?:([a-z]+)(?:\s*(=)\s*\"(.+?)\")?)\s*", attrs)
                    
                    self.text.append(Tag(part))
                else:
                    self.text.append(part)
        # TODO - test for everything
        

    def export_ebk(self, file, fmt):
        if file == None:
            f = sys.stdout
        else:
            f = open(file, 'w', io.DEFAULT_BUFFER_SIZE, 'utf-8')
        for txt in self.text:
            if type(txt) == str: 
                f.write(txt)
        if file != None:
            f.close()
    


def print_help():
    pass


def print_version():
    pass


#
# main
#
file_in = None
file_out = None
format_in = None
format_out = None

file_in = 'C:/andre/projects/andrenho/book/example/example.ebk' # TODO

# get arguments
args = sys.argv.reverse()
if args == None:
    args = []
while len(args) > 0:
    arg = args.pop()
    if arg == '-h':
        print_help()
    elif arg == 'v':
        print_version()
    elif arg == '-o':
        file_out = args.pop()
    elif arg == '-i':
        file_in = args.pop()
    elif arg == '-of':
        format_out = Format(args.pop())
    elif arg == '-if':
        format_in = Format(args.pop())
    else:
        raise 'Invalid argument ' + arg + '.'

# find out file format
if format_in == None:
    if file_in == None or file_in.endswith('.ebk'):
        format_in = Format('ebk')
    else:
        raise 'Output file format could not be determined.'

if format_out == None:
    if file_out == None or file_out.endswith('.ebk'):
        format_out = Format('ebk')
    else:
        raise 'Output file format could not be determined.'
    
# import file
book = Book(file_in, format_in)
book.export(file_out, format_out)
