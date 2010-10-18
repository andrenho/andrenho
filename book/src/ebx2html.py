# TODO:
#  - DTD validation

from optparse import OptionParser
from xml.sax.handler import ContentHandler
from xml.sax import make_parser
import io, sys

#
# get parameters
#
prs = OptionParser(usage="usage: %prog [options] [filename]",
                   version="%prog 0.1")
prs.add_option("-o", "--output", metavar="FILE",
               help="Output filename (default stdout)")
(options, args) = prs.parse_args()

if options.output == None:
    out_f = sys.stdout
else:
    out_f = open(options.output, 'wb', io.DEFAULT_BUFFER_SIZE, 'utf_8')

if len(args) == 0:
    in_f = None
elif len(args) == 1:
    in_f = args[0]
else:
    raise Exception('Too many arguments.')

#
# convert to HTML5
#
class EbookXMLHandler(ContentHandler):

    def __init__(self, file):
        ContentHandler.__init__(self)
        self.f = file
        self.writing = False
    
    def startDocument(self):
        print('<!DOCTYPE html>', file=self.f)

    def startElement(self, name, attrs):
        # book
        if name == 'book':
            if 'language' in attrs:
                print('<html lang="' + attrs['language'] + '">')
            else:
                print('<html>', file=self.f)
            print('  <head>', file=self.f)
            print('    <meta charset="utf-8" />', file=self.f)
            if 'author' in attrs:
                print('    <meta name="author" content="' + attrs['author'] + '" />', file=self.f)
            if 'title' in attrs:
                print('    <title>' + attrs['title'] + '</title>', file=self.f)
            else:
                raise Exception('Attribute title expected in tag book.')
            print('  </head>', file=self.f)
            print('  <body>', file=self.f)
            print('    <h1>' + attrs['title'] + '</h1>', file=self.f)
            if 'author' in attrs:
                print('    <p><i>' + attrs['author'] + '</i></p>', file=self.f)
            print('    <hr>', file=self.f)

        # p
        elif name == 'p':
            self.f.write('    <p>')
            self.writing = True

        # center
        elif name == 'center':
            self.f.write('    <p align="center">')
            self.writing = True

        # b, u, i
        elif name in ('b', 'i', 'u'):
            if len(attrs) > 0:
                raise Exception(name + ' tag can\'t have attributes.')
            self.f.write('<' + name + '>')

        # quote
        elif name == 'quote':
            self.f.write('    <blockquote>')
            self.writing = True

        # separator
        elif name == 'separator':
            print('    <hr>', file=self.f)

    def characters(self, content):
        if self.writing:
            self.f.write(str(content))

    def endElement(self, name):
        if name in ('p', 'center'):
            print('</p>', file=self.f)
            self.writing = False
        elif name in ('b', 'i', 'u'):
            self.f.write('</' + name + '>')
        elif name == 'quote':
            print('</blockquote>', file=self.f)
            self.writing = False

    def endDocument(self):
        print('  </body>', file=self.f)
        print('</html>', file=self.f)

saxparser = make_parser()
datasource = sys.stdin
if in_f != None:
    datasource = open(in_f, 'r', encoding='utf-8')
saxparser.setContentHandler(EbookXMLHandler(out_f))
saxparser.parse(datasource)
