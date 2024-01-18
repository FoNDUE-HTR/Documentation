from src.teiheader_metadata.iiif_data import IIIF
from src.teiheader_metadata.sru_data import SRU

class Metadata:
    metadata = {"sru":None, "iiif":None}
    def __init__(self, document) -> None:
        self.d = document
        self.metadata

    def prepare(self):
        # -- Parse data from document's IIIF manifest --
        # instantiate the class IIIF for this document
        iiif = IIIF(self.d)
        # request the digital document's IIIF manifest data and clean it with methods from IIIF class
        iiif_data = iiif.clean(iiif.request())
        # add the cleaned IIIF data to this document's metadata
        self.metadata.update({"iiif":iiif_data})

        # -- Parse data from BnF's SRU API --
        # isntantiate the class SRU for this document
        sru = SRU(iiif_data["Catalogue ARK"])
        # request the physical document's catalogue data from the BnF (response) 
        # and/or a boolean confirming if the physical document was found (perfect_match)
        response, perfect_match = sru.request()
        # clean the MARCXML response and prepare a dictinoary of relevant metadata
        sru_data = sru.clean(response, perfect_match)
        # add the cleaned catalogue data to this document's metadata
        self.metadata.update({"sru":sru_data})

        return self.metadata