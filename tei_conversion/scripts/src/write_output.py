# -----------------------------------------------------------
# Code by: Kelly Christensen
# Python class to generate the output XML-TEI file.
# -----------------------------------------------------------

from lxml import etree

class Write:
    def __init__(self, document, root):
        self.d = document
        self.r = root

    def write(self):
        with open(f'./content/data/{self.d}.xml', 'wb') as f:
                etree.ElementTree(self.r).write(f, encoding="utf-8", xml_declaration=True, pretty_print=True)
            
