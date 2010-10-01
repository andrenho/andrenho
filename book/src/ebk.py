import re, io, os, sys
import xml.etree.ElementTree as etree


class Format(str):
    def __init__(self, fmt):
        if fmt not in ('xml', 'txt'):
            raise Exception('Format ' + fmt + ' not supported.')
        self.fmt = fmt
        self.attributes = dict()


class Book:

    def __init__(self, file, fmt):
        self.xml = None
        if fmt.fmt == 'xml':
            self.import_xml(file, fmt)
        else:
            os.abort()
            

    def export(self, file, fmt):
        if fmt.fmt == 'xml':
            self.export_xml(file, fmt)
        elif fmt.fmt == 'txt':
            self.export_txt(file, fmt)
        else:
            os.abort()
            

    def import_xml(self, file, fmt):
        if file == None:
            f = sys.stdout
        else:
            f = open(file, 'r', io.DEFAULT_BUFFER_SIZE, 'utf-8')
        self.xml = etree.parse(file).getroot()
        f.close()
        

    def export_xml(self, file, fmt):
        f = None
        if file == None:
            f = sys.stdout
        else:
            f = open(file, 'w', io.DEFAULT_BUFFER_SIZE, 'utf-8')
        f.write("<?xml version='1.0' encoding='utf-8'?>\n")
        f.write(etree.tostring(self.xml))
        if file != None:
            f.close()


    def export_txt(self, file, fmt):
        pass


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

file_in = 'C:/andre/projects/andrenho/book/example/syntax.xml' # TODO
format_out = Format('txt')

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
        raise Exception('Invalid argument ' + arg + '.')

# find out file format
if format_in == None:
    if file_in == None or file_in.endswith('.xml'):
        format_in = Format('xml')
    else:
        raise Exception('Output file format could not be determined.')

if format_out == None:
    if file_out == None or file_out.endswith('.xml'):
        format_ou5t = Format('xml')
    else:
        raise Exception('Output file format could not be determined.')
    
# import file
book = Book(file_in, format_in)
book.export(file_out, format_out)
