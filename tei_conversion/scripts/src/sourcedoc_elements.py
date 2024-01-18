# -----------------------------------------------------------
# Code by: Kelly Christensen
# Python class to build elements inside the <sourceDoc> and map data to them.
# -----------------------------------------------------------

from lxml import etree
import re

NS = {'a':"http://www.loc.gov/standards/alto/ns-v4#"}  # namespace for the Alto xml


class SurfaceTree:
    """Creates a <surface> element and its children for one page (ALTO file) of a document.
    """    
    
    def __init__(self, doc, folio, alto_root):
        self.doc = doc
        self.folio = folio
        self.root = alto_root

    def surface(self, surface_group, page_attributes):
        """Make the TEI <surface> element that will organize all of an ALTO file's data.

        Args:
            surface_group (_type_): _description_
            page_attributes (_type_): _description_

        Returns:
            _type_: _description_
        """        
        surface = etree.SubElement(surface_group, "surface", page_attributes)
        # create <graphic> and assign its attributes
        etree.SubElement(surface, "graphic", url=f"https://gallica.bnf.fr/iiif/ark:/12148/{self.doc}/f{self.folio}/full/full/0/native.jpg")
        return surface

    def zone1(self, surface, attributes, block_id, blocks_on_page):
        """Make the xml:id and TEI <zone> element for the ALTO file's <TextBlock>.

        Args:
            surface (etree_Element): _description_
            textblock_atts (dict): _description_
            block_id (str): _description_
            blocks_on_page (int): _description_

        Returns:
            _type_: _description_
        """        
        xml_id = {"{http://www.w3.org/XML/1998/namespace}id":f"f{self.folio}-{block_id}-blockCount{blocks_on_page}"}
        zone = etree.SubElement(surface, "zone", xml_id)
        for k,v in attributes.items():
            zone.attrib[k]=v
        return zone

    def zone2(self, textblock, block_parent, attributes, line_id, lines_on_page):   
        """Make the xml:id and TEI <zone> element for the second-level <zone> for the ALTO file's <TextLine>
            and make the xml:id for the second-level <zone>'s <path>.

        Args:
            textblock (_type_): _description_
            block_parent (_type_): _description_
            textline_atts (_type_): _description_
            line_id (_type_): _description_
            lines_on_page (_type_): _description_

        Returns:
            _type_: _description_
        """         
        # -------------------------------------------
        zone_id = {"{http://www.w3.org/XML/1998/namespace}id":f"f{self.folio}-{block_parent}-{line_id}-lineCount{lines_on_page}"}
        # Insert the <zone> with this xml:id into the TEI-XML tree.
        zone = etree.SubElement(textblock, "zone", zone_id)
        # Insert the 
        for k,v in attributes.items():
            zone.attrib[k]=v
        # -------------------------------------------
        path_id = {"{http://www.w3.org/XML/1998/namespace}id":f"f{self.folio}-{block_parent}-{line_id}-lineCount{lines_on_page}-baseline"}
        #
        baseline = etree.SubElement(zone, "path", path_id)
        #
        b = self.root.find(f'.//a:TextLine[@ID="{line_id}"]', namespaces=NS).get("BASELINE")
        #
        baseline.attrib["points"] = " ".join([re.sub(r"\s", ",", x) for x in re.findall(r"(\d+ \d+)", b)])
        return zone

    def line(self, textline, block_parent, line_parent, lines_on_page, extracted_words):
        """If the ALTO file stores all of a line's textual data in the <TextLine> attribute @CONTENT, 
            make the xml:id for <line>.

        Args:
            textline (_type_): _description_
            block_parent (_type_): _description_
            line_parent (_type_): _description_
            lines_on_page (_type_): _description_

        Returns:
            _type_: _description_
        """        
        xml_id = {"{http://www.w3.org/XML/1998/namespace}id":f"f{self.folio}-{block_parent}-{line_parent}-lineCount{lines_on_page}-text"}
        # If the 
        line = etree.SubElement(textline, "line", xml_id)
        line.attrib["n"] = str(lines_on_page)
        if extracted_words:
            line.text = extracted_words
        else:
            line.text = self.root.find(f'.//a:TextLine[@ID="{line_parent}"]/a:String', namespaces=NS).get("CONTENT")
        return line
        
    def zone3(self, textline, block_parent, line_parent, attributes, seg_id, strings_on_page):
        """Make the xml:id and TEI <zone> element for the ALTO file's <String> (segment/word).

        Args:
            textline (_type_): _description_
            block_parent (_type_): _description_
            line_parent (_type_): _description_
            attributes (_type_): _description_
            seg_id (_type_): _description_
            segments_on_page (_type_): _description_

        Returns:
            _type_: _description_
        """        
        xml_id = {"{http://www.w3.org/XML/1998/namespace}id":f"f{self.folio}-{block_parent}-{line_parent}-{seg_id}-segCount{strings_on_page}"}
        zone = etree.SubElement(textline, "zone", xml_id)
        for k,v in attributes.items():
            zone.attrib[k]=v

        if self.root.find(f'.//a:String[@ID="{seg_id}"]', namespaces=NS) is not None \
            and self.root.find(f'.//a:String[@ID="{seg_id}"]', namespaces=NS).get("WC") is not None:
            word_certainty = self.root.find(f'.//a:String[@ID="{seg_id}"]', namespaces=NS).get("WC")
            cert_attribs = {
                "{http://www.w3.org/XML/1998/namespace}id":f"f{self.folio}-{block_parent}-{line_parent}-{seg_id}-segCount{strings_on_page}-cert",
                "target":f"#f{self.folio}-{block_parent}-{line_parent}-{seg_id}-segCount{strings_on_page}-text",
                "locus":"value",
                "degree":word_certainty
            }
            etree.SubElement(zone, "certainty", cert_attribs)
        return zone

    def zone4(self, string, block_parent, line_parent, seg_parent, attributes, glyph_id, glyphs_on_page):
        """Make the xml:id and TEI <zone> element for the ALTO file's <String> (segment/word).

        Args:
            textline (_type_): _description_
            block_parent (_type_): _description_
            line_parent (_type_): _description_
            attributes (_type_): _description_
            seg_id (_type_): _description_
            segments_on_page (_type_): _description_

        Returns:
            _type_: _description_
        """        
        xml_id = {"{http://www.w3.org/XML/1998/namespace}id":f"f{self.folio}-{block_parent}-{line_parent}-{seg_parent}-{glyph_id}-glyphCount{glyphs_on_page}"}
        zone = etree.SubElement(string, "zone", xml_id)
        for k,v in attributes.items():
            zone.attrib[k]=v

        if self.root.find(f'.//a:Glyph[@ID="{glyph_id}"]', namespaces=NS).get("GC") is not None:
            glyph_certainty = self.root.find(f'.//a:Glyph[@ID="{glyph_id}"]', namespaces=NS).get("GC")
            cert_attribs = {
                "{http://www.w3.org/XML/1998/namespace}id":f"f{self.folio}-{block_parent}-{line_parent}-{seg_parent}-{glyph_id}-glyphCount{glyphs_on_page}-cert",
                "target":f"#f{self.folio}-{block_parent}-{line_parent}-{seg_parent}-{glyph_id}-glyphCount{glyphs_on_page}-text",
                "locus":"value",
                "degree":glyph_certainty
            }
            etree.SubElement(zone, "certainty", cert_attribs)
        return zone

    def car(self, zone,  glyph, block_parent, line_parent, seg_parent, glyph_id, glyphs_on_page):     
        xml_id = {"{http://www.w3.org/XML/1998/namespace}id":f"f{self.folio}-{block_parent}-{line_parent}-{seg_parent}-{glyph_id}-glyphCount{glyphs_on_page}-text"}
        car = etree.SubElement(zone, "c", xml_id)
        if self.root.find(f'.//a:Glyph[@ID="{glyph_id}"]', namespaces=NS).get("WC") is not None:
            word_certainty = self.root.find(f'.//a:Glyph[@ID="{glyph_id}"]', namespaces=NS).get("WC")
            cert_attribs = {
                "{http://www.w3.org/XML/1998/namespace}id":f"f{self.folio}-{block_parent}-{line_parent}-{seg_parent}-{glyph_id}-glyphCount{glyphs_on_page}-cert",
                "locus":"value",
                "degree":word_certainty
            }
            etree.SubElement(zone, "certainty", cert_attribs)
        car.text = glyph.attrib["CONTENT"]
        return car

