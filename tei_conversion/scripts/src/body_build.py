# -----------------------------------------------------------
# Code by: Kelly Christensen
# Python script to build the <body> of a TEI file with an ALTO File's MainZone text.
# -----------------------------------------------------------

from lxml import etree


def body(root, data):
    text = etree.SubElement(root, "text")
    body = etree.SubElement(text, "body")
    div = etree.SubElement(body, "div")
    for line in data:
        # prepare attributes for the text block's zone
        zone_atts = {"corresp":f"#{line.zone_id}", "type":line.zone_type}
        # prepare <lb/> with this line's xml:id as @corresp
        lb = etree.Element("lb", corresp=f"#{line.id}")
        lb.tail = f"{line.text}"

        # if this is the page's first line, create a <pb> with the page's xml:id
        if int(line.n) == 1:
            pb = etree.Element("pb", corresp=f"#{line.page_id}")
            div.append(pb)
        
        # find the last element added to the div
        last_element = div[-1]

        # NumberingZone, QuireMarksZone, and RunningTitleZone line
        if line.zone_type == "NumberingZone" or line.zone_type == "QuireMarksZone" or line.zone_type == "RunningTitleZone":
            # enclose any page number, quire marks, or running title inside a <fw>
            fw = etree.Element("fw", zone_atts)
            last_element.addnext(fw)
            fw.append(lb)

        # MarginTextZone line
        elif line.zone_type == "MarginTextZone":
            # create a <note> if one is not already the preceding sibling
            if last_element.tag != "note":
                note = etree.Element("note", zone_atts)
                last_element.addnext(note)
                note.append(lb)
            else:
                last_element.append(lb)
            
        # MainZone line
        elif line.zone_type == "MainZone":
            # create an <ab> if one is not already the preceding sibling 
            if last_element.tag != "ab":
                ab = etree.Element("ab", zone_atts)
                last_element.addnext(ab)
                ab.append(lb)
                # update the last element in div
                last_element = div[-1]

            # if the line is emphasized for being 
            if line.line_type == "DropCapitalLine" or line.line_type == "HeadingLine":
                # check if there is already an emphasized line in this MainZone
                ab_children = last_element.getchildren()
                if len(ab_children) == 0 or ab_children[-1].tag != "hi" or ab_children[-1].get("rend") != line.line_type:
                    hi = etree.Element("hi", rend=line.line_type)
                    last_element.append(hi)
                    hi.append(lb)
                elif ab_children[-1].tag == "hi":
                    ab_children[-1].append(lb)
            
            # if the line is not emphasized, append it to the last element in the <ab>
            else:
                last_element.append(lb)
                