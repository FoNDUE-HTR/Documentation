# -----------------------------------------------------------
# Code by: Kelly Christensen
# Python class to map the document's and project's metadata to the default <teiHeader>.
# -----------------------------------------------------------

from lxml import etree
import re
from collections import namedtuple
from .sourcedoc_build import labels

class FullTree:
    def __init__(self, children, metadata):
        self.children = children
        self.sru = metadata["sru"]
        self.iiif = metadata["iiif"]

    def author_data(self):
        """Enter document's title and author into <titleStmt>.
        """        
        if self.sru["found"]:  # if the document's IIIF manifest had a valid catalogue ARK
            self.authors(self.children["titleStmt"], True, True)
            self.authors(self.children["bibl"], True, False)
        else:  # if the document's IIIF manifest didn't have a valid catalogue ARK
            self.authors(self.children["titleStmt"], False, True)
            self.authors(self.children["bibl"], False, False)

    def authors(self, parent, is_catologue_match, is_first_id):
        """Create elements about authorship in either fileDesc/titleStmt or fileDesc/sourceDesc/bibl.
        Args:
            parent (etree_Element): the parent element for the author data (<titleStmt> or <bibl>)
            is_catologue_match (boolean): True if the document's metadata was found in the BnF catalogue
            is_first_id (boolean): True if the author id is presented for the first time, aka "xml:id"
                                    if it's not the first time, the id will be "ref"
        """     

        if not parent.find('./author').text:  # if the default tree was not built for 0 authors and doesn't have default text
            xml_id = "{http://www.w3.org/XML/1998/namespace}id"
            if is_catologue_match:
                for count, author_root in enumerate(parent.findall('./author')):
                    if is_first_id:
                        author_root.attrib[xml_id] = self.sru["authors"][count]["xmlid"]
                    else:
                        ref = self.sru["authors"][count]["xmlid"]
                        author_root.attrib["ref"] = f"#{ref}"
                    persname = etree.SubElement(author_root, "persName")
                    if self.sru["authors"][count]["secondary_name"]:
                        forename = etree.SubElement(persname, "forename")
                        forename.text = self.sru["authors"][count]["secondary_name"]
                    if self.sru["authors"][count]["namelink"]:
                        namelink = etree.SubElement(persname,"nameLink")
                        namelink.text = self.sru["authors"][count]["namelink"]
                    if self.sru["authors"][count]["primary_name"]:
                        surname = etree.SubElement(persname, "surname")
                        surname.text = self.sru["authors"][count]["primary_name"]
                    if self.sru["authors"][count]["isni"]:
                        ptr = etree.SubElement(persname, "ptr")
                        ptr.attrib["type"] = "isni"
                        ptr.attrib["target"] = self.sru["authors"][count]["isni"]
            else:
                author_root = parent.find('./author')
                if self.iiif["Creator"] is not None:
                    a = self.iiif["Creator"]
                    if is_first_id:
                        author_root.attrib[xml_id] = f"{a[:2]}"
                    else:
                        author_root.attrib["ref"] = f"#{a[:2]}"
                    name = etree.SubElement(author_root, "name")
                    name.text = a

    def bib_data(self):
        """In the <bibl>, enter the document's catalogue pointer (ptr), author, title, publication place, publisher, date.
            In the <msDesc>, enter the institution's country code, settlement, repository name, shelfmark for the doc, and doc type.
        """

        Entry = namedtuple("Entry", ["tei_element","attribute","iiif_data","unimarc_data"])
        entries =   [
                    # <title> in <titleStmt>, data from IIIF or SRU
                    Entry("ts_title",None,"Title","title"),
                    # @target for <ptr> element in <bibl>, only data from SRU
                    Entry("ptr","target",None,"ptr"),
                    # <title> in <bibl>, data from IIIF or SRU
                    Entry("bib_title",None,"Title","title"),
                    # <pubPlace> in <sourceDesc>, only data from SRU
                    Entry("pubPlace",None,None,"pubplace"),
                    # @key for <pubPlace> in <sourceDesc>, only data from SRU
                    Entry("pubPlace","key",None,"pubplace_key"),
                    # <publisher> in <sourceDesc>, only data from SRU
                    Entry("publisher",None,None,"publisher"),
                    # <date> in <sourceDesc>, data from IIIF or SRU
                    Entry("date",None,"Date","date"),
                    # @when for <date> in <sourceDesc>, only data from SRU
                    Entry("date","when",None,"when"),
                    # @cert for <date> in <sourceDesc>, only data from SRU
                    Entry("date","cert",None,"date_cert"),
                    # @resp for <date> in <sourceDesc>, only data from SRU
                    Entry("date","resp",None,"date_resp"),
                    # @key for <country> in <msDesc>, onyl data from SRU
                    Entry("country","key",None,"country"),
                    # <settlement> in <msDesc>, only data from SRU
                    Entry("settlement", None, None, "settlement"),
                    # <respository> in <msDesc>, only data from IIIF
                    Entry("repository",None,"Repository","repo"),
                    # <idno> in <msDesc>, data from IIIF or SRU
                    Entry("idno",None,"Shelfmark","idno"),
                    # <p> in <objectDesc>, only data from SRU
                    Entry("p",None,None,"objectdesc"),
                    # <language> in <profileDesc>, only data from IIIF
                    Entry("language",None,"Language",None),
                    # @ident for <language> in <profileDesc>, only data from SRU
                    Entry("language","ident",None,"lang")]
        for e in entries:
            if self.sru and e.unimarc_data and self.sru[e.unimarc_data]:
                self.entry(self.sru[e.unimarc_data], self.children[e.tei_element], e.attribute)
            elif e.iiif_data and self.iiif[e.iiif_data]:
                self.entry(self.iiif[e.iiif_data], self.children[e.tei_element], e.attribute)
    
    def entry(self, data, tei_element, attribute):
        if attribute:
            tei_element.attrib[attribute] = data
        else:
            tei_element.text = data

    def segmonto_taxonomy(self, filepaths):
        # List all the SegmOnto tags and a URL pointing to their description.
        SegmOntoZones = {
                "CustomZone":"https://segmonto.github.io/gd/gdZ/CustomZone/",
                "DamageZone":"https://segmonto.github.io/gd/gdZ/DamageZone",
                "DecorationZone":"https://segmonto.github.io/gd/gdZ/DecorationZone",
                "DigitizationArtefactzone":"https://segmonto.github.io/gd/gdZ/DigitizationArtefactzone",
                "DropCapitalZone":"https://segmonto.github.io/gd/gdZ/DropCapitalZone",
                "MainZone":"https://segmonto.github.io/gd/gdZ/MainZone",
                "MusicZone":"https://segmonto.github.io/gd/gdZ/MusicZone",
                "NumberingZone":"https://segmonto.github.io/gd/gdZ/NumberingZone",
                "QuireMarksZone":"https://segmonto.github.io/gd/gdZ/QuireMarksZone",
                "RunningTitleZone":"https://segmonto.github.io/gd/gdZ/RunningTitleZone",
                "SealZone":"https://segmonto.github.io/gd/gdZ/SealZone",
                "StampZone":"https://segmonto.github.io/gd/gdZ/StampZone",
                "TableZone":"https://segmonto.github.io/gd/gdZ/TableZone",
                "TitlePageZone":"https://segmonto.github.io/gd/gdZ/TitlePageZone"
            }
        SegmOntoLines = {
                "CustomLine":"https://segmonto.github.io/gd/gdL/CustomLine/",
                "DefaultLine":"https://segmonto.github.io/gd/gdL/DefaultLine",
                "DropCapitalLine":"https://segmonto.github.io/gd/gdL/DropCapitalLine",
                "HeadingLine":"https://segmonto.github.io/gd/gdL/HeadingLine",
                "InterlinearLine":"https://segmonto.github.io/gd/gdL/InterlinearLine",
                "MusicLine":"https://segmonto.github.io/gd/gdL/MusicLine"
            }
        
        # Get all the tags used on the pages of this document.
        all_tag_dicts = [labels(f) for f in filepaths]

        # With regex, extract the main part (string before a colon, if present) of a label in the tag dictionary.
        # And use dictionary comprehension to parse all the labels in the document's tags dictionaries.
        unique_labels = list(set(re.match(r"(\w+):?(\w+)?#?(\d?)?", value).group(1)\
                                for dic in all_tag_dicts\
                                for value in dic.values()))

        # Create a list of zone tags used in this document.
        document_zones = [label for label in unique_labels if "Zone" in label]
        # Create a list of line tags used in this document.
        document_lines = [label for label in unique_labels if "Line" in label]

        # Descending directly from <taxonomy>, create the TEI element <category> for SegmOnto zones.
        cat_id = {"{http://www.w3.org/XML/1998/namespace}id":"SegmOntoZones"}
        category = etree.SubElement(self.children["taxonomy"], "category", cat_id)
        # Enter into the <category> every zone in the document that is also named in the SemOnto guidelines.
        for z in set(SegmOntoZones).intersection(set(document_zones)):
            self.enter_taxonomy_category(category, z, SegmOntoZones[z])
        
        # Descending directly from <taxonomy>, create the TEI element <category> for SegmOnto lines.
        cat_id = {"{http://www.w3.org/XML/1998/namespace}id":"SegmOntoLines"}
        category = etree.SubElement(self.children["taxonomy"], "category", cat_id)
        # Enter into the <category> every line in the document that is also named in the SemOnto guidelines.
        for l in set(SegmOntoLines).intersection(set(document_lines)):
            self.enter_taxonomy_category(category, l, SegmOntoLines[l])
        return document_zones, document_lines
            
    def enter_taxonomy_category(self, category, tag, url):
        """Enter into the TEI-XML tree a <catDesc> for a specific SegmOnto line or zone.

        Args:
            category (etree_Element): root for the element <category> in the TEI-XML document
            tag (string): name of the tag identified in the ALTO file
            url (string): URL pointing to a description fo the line or zone in the SegmOnto guidelines
        """        
        catDesc_id = {"{http://www.w3.org/XML/1998/namespace}id":f"{tag}"}
        catDesc = etree.SubElement(category, "catDesc", catDesc_id)
        title = etree.SubElement(catDesc, "title")
        title.text = tag
        ptr = etree.SubElement(catDesc, "ptr")
        ptr.attrib["target"] = url
            


        
