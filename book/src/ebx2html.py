from optparse import OptionParser
from xml.sax.handler import ContentHandler
from xml.sax import make_parser
import sys

#
# get parameters
#
prs = OptionParser(usage="usage: %prog [options] [filename]",
                   version="%prog 0.1")
prs.add_option("-o", "--output", metavar="FILE",
               help="Output filename (default stdout)")
(options, args) = prs.parse_args()

if options.output == None:
    out_f = None
else:
    out_f = options.output

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
    
    def startDocument(self):
        print('<!DOCTYPE html>')
        print('<html>')

    def startElement(self, name, attrs):
        pass

    def characters(self, content):
        print(content)

    def endElement(self, name):
        pass

    def endDocument(self):
        print('</html>')

saxparser = make_parser()
saxparser.setContentHandler(EbookXMLHandler())
datasource = sys.stdin
if in_f != None:
    datasource = in_f
saxparser.parse(datasource)
