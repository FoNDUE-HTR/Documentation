# -----------------------------------------------------------
# Code by: Kelly Christensen
# Python class to organize the file paths in the data directory.
# -----------------------------------------------------------

import re
from collections import namedtuple

class Files:
    def __init__(self, document, filepaths):
        self.d = document
        self.fl = filepaths  # list

    def order_files(self):
        File = namedtuple("File", ["num", "filepath"])
        ordered_files = sorted([File(int(re.search(r"(\d+).xml$", f.name).group(1)), f)for f in self.fl])
        return ordered_files
