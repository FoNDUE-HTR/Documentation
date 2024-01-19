from lxml import etree
from src.teiheader_metadata.clean_data import Metadata
from src.teiheader_build import teiheader
from src.sourcedoc_build import sourcedoc
from src.text_data import Text
from src.body_build import body

class TEI:
    metadata = {"sru":None, "iiif":None}
    tags = {}
    root = None
    segmonto_zones = None
    segmonto_lines = None
    def __init__(self, document, filepaths):
        self.d = document  # (str) this document's name / name of directory contiaining the ALTO files
        self.fp = filepaths  # (list) paths of ALTO files
        self.metadata  # (dict) dict with two keys ("iiif", "sru"), each of which is equal to its own dictionary of metadata
        self.tags  # (dict) a label-ref pair for each tag used in this document's ALTO files
        self.root  # (etree_Element) root for this document's XML-TEI tree
        self.segmonto_zones
        self.segmonto_lines


    def build_tree(self):
        """Parse and map data from ALTO files to an XML-TEI tree's <teiHeader> and <sourceDoc>.
        """   

        # instantiate the XML-TEI root for this document and assign the root basic attributes
        tei_root_att = {"xmlns":"http://www.tei-c.org/ns/1.0", "{http://www.w3.org/XML/1998/namespace}id":f"ark_12148_{self.d}"}
        self.root = etree.Element("TEI", tei_root_att)
    
    def build_header(self, config, version):
        # confirm that the metadata is being récupéré
        #Deleted for notebook version
        #self.metadata = Metadata(self.d).prepare()
        self.root, self.segmonto_zones, self.segmonto_lines = teiheader(self.metadata, self.d, self.root, len(self.fp), config, version, self.fp, self.segmonto_zones, self.segmonto_lines)
    
    def build_sourcedoc(self):
        sourcedoc(self.d, self.root, self.fp, self.tags, self.segmonto_zones, self.segmonto_lines)

    def build_body(self):
        text = Text(self.root)
        body(self.root, text.data)
