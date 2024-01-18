# -----------------------------------------------------------
# Code by: Kelly Christensen
# Python script to map all the data of an ALTO file to the <sourceDoc> of a TEI file.
# -----------------------------------------------------------

from collections import defaultdict
from src.order_files import Files
from src.sourcedoc_attributes import Attributes
from src.sourcedoc_elements import SurfaceTree
from lxml import etree

NS = {'a':"http://www.loc.gov/standards/alto/ns-v4#"}  # namespace for the Alto xml


def labels(filepath):
    root = etree.parse(filepath).getroot()
    elements = [t.attrib for t in root.findall('.//a:OtherTag', namespaces=NS)]
    collect = defaultdict(dict)
    for d in elements:
        collect[d["ID"]] = d["LABEL"]
    tags = dict(collect)
    return tags


def sourcedoc(document_name, output_tei_root, filepath_list, tags, segmonto_zones, segmonto_lines):
    """Creates the <sourceDoc> for an XML-TEI file using data parsed from a series of ALTO files.
        The <sourceDoc> collates each ALTO file, which represents one page of a document, into a wholistic
        description of the document.
    """


    ordered_files = Files(document_name, filepath_list).order_files()
    
    # Create <sourceDoc> and its child <surfaceGrp>.
    sourceDoc = etree.SubElement(output_tei_root, "sourceDoc")

    for file in ordered_files:

        tags = labels(file.filepath)

        # Start count at 0 for number of entities on a page.
        blocks_on_page = 0
        lines_on_page = 0
        strings_on_page = 0
        glyphs_on_page = 0

        # Parse the XML tree for the ALTO file
        input_alto_root = etree.parse(file.filepath).getroot()
        # Instantiate the classes Attributes and SurfaceTree for the ALTO file
        attributes = Attributes(document_name, file.num, input_alto_root, tags)
        surface_tree = SurfaceTree(document_name, file.num, input_alto_root)

        # -- SURFACE --
        # For every page in the ALTO file, create a <surface> and assign its attributes.
        surface = surface_tree.surface(sourceDoc, attributes.surface())

        # -- TEXTBLOCK --
        # For every <TextBlock> in a <PrintSpace>, create a <zone> and assign it attributes.
        textblocks = attributes.zones("PrintSpace", "TextBlock", segmonto_zones)
        for tb in textblocks:
            # Only map the <TextBlock> to the XML-TEI tree if its @ID was found.
            if tb.id:
                blocks_on_page+=1
                textblock = surface_tree.zone1(surface, tb.attributes, tb.id, blocks_on_page)

            textlines = attributes.zones(f'TextBlock[@ID="{tb.id}"]', "TextLine", segmonto_lines)
            # "tl" concerns <TextLine> and its descendant <Polygon>
            for tl in textlines:
                # Only map the <TextLine> to the XML-TEI tree if its @ID was found.
                if tl.id:
                    lines_on_page+=1
                    textline = surface_tree.zone2(textblock, tb.id, tl.attributes, tl.id, lines_on_page)
                    words = ""

                    # If <TextLine> has child <String> that has all the line's textual content, map that to the TEI element <line>.
                    if input_alto_root.find(f'.//a:TextLine[@ID="{tl.id}"]/a:String', namespaces=NS).get("CONTENT") is not None\
                        and len(input_alto_root.find(f'.//a:TextLine[@ID="{tl.id}"]/a:String', namespaces=NS).getchildren()) == 0:
                        # Map the textual data to the TEI element <line>.
                        surface_tree.line(textline, tb.id, tl.id, lines_on_page, None)
                    
                    # If the line's textual content is expressed at the level of glyphs, map that textual data to TEI element <c>.
                    elif input_alto_root.find(f'.//a:TextLine[@ID="{tl.id}"]/a:String', namespaces=NS).get("CONTENT") is not None\
                        and input_alto_root.find(f'.//a:TextLine[@ID="{tl.id}"]/a:String', namespaces=NS).get("CONTENT") != ""\
                        and len(input_alto_root.find(f'.//a:TextLine[@ID="{tl.id}"]/a:String', namespaces=NS).getchildren()) > 0:

                        # Loop through all the <String> or <SP> children of a <TextLine>
                        textline_children = input_alto_root.find(f'.//a:TextLine[@ID="{tl.id}"]', namespaces=NS).getchildren()
                        for textline_child in textline_children:

                            # If child of <TextLine> is a space <SP>
                            if etree.QName(textline_child).localname == "SP":
                                textline_child_id = textline_child.attrib["ID"]
                                space_data = attributes.zones(f'TextLine[@ID="{tl.id}"]', f'SP[@ID="{textline_child_id}"]', None)[0]
                                strings_on_page+=1
                                surface_tree.zone3(textline, tb.id, tl.id, space_data.attributes, space_data.id, strings_on_page)

                            # If a child of <TextLine> is a segment of text <String>
                            elif etree.QName(textline_child).localname == "String":
                                textline_child_id = textline_child.attrib["ID"]
                                string_data = attributes.zones(f'TextLine[@ID="{tl.id}"]', f'String[@ID="{textline_child_id}"]', None)[0]
                                strings_on_page+=1
                                string = surface_tree.zone3(textline, tb.id, tl.id, string_data.attributes, string_data.id, strings_on_page)

                                # Loop through all the <Glyph> children of a <String>
                                string_children = input_alto_root.findall(f'.//a:String[@ID="{textline_child_id}"]/a:Glyph', namespaces=NS)
                                if words == "":
                                    words = words + "".join([g.get("CONTENT") for g in string_children])
                                else:
                                    words = words + " " + "".join([g.get("CONTENT") for g in string_children])
                                    
                                for glyph_child in string_children:
                                    glyph_id = glyph_child.attrib["ID"]
                                    glyph_data = attributes.zones(f'String[@ID="{textline_child_id}"]', f'Glyph[@ID="{glyph_id}"]', None)[0]
                                    glyphs_on_page+=1
                                    glyph = surface_tree.zone4(string, tb.id, tl.id, textline_child_id, glyph_data.attributes, glyph_id, glyphs_on_page)
                                    surface_tree.car(glyph, glyph_child, tb.id, tl.id, textline_child_id, glyph_id, glyphs_on_page)

                        surface_tree.line(textline, tb.id, tl.id, lines_on_page, words)
  
    return output_tei_root
    