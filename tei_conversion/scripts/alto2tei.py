import argparse, os
import yaml
from collections import namedtuple
from pathlib import Path
from time import perf_counter

from src.build import TEI
from src.write_output import Write

def file_path(string):
    """Verify if the string passed as the argument --config is a valid file path.

    Args:
        string (str): file path to YAML configuration file.

    Raises:
        FileNotFoundError: informs user that the file path is invalid.

    Returns:
        (str): validated path to configuration file
    """    
    if os.path.isfile(string):
        return string
    else:
        raise FileNotFoundError(string)


def get_args():
    """Parse command-line arguments and verify (1) the config file exist, (2) the TEI elements demanded can be constructed.
    """    
    parser = argparse.ArgumentParser()
    parser.add_argument("--config", nargs=1, type=file_path, required=True,
                        help="path to the YAML configuration file")
    parser.add_argument("--version", nargs=1, type=str, required=True,
                        help="version of Kraken used to create the ALTO-XML files")
    parser.add_argument("--header", default=False, action='store_true',
                        help="produce TEI-XML with <teiHeader>")
    parser.add_argument("--sourcedoc", default=False, action='store_true',
                        help="produce TEI-XML with <sourceDoc>")
    parser.add_argument("--body", default=False, action='store_true',
                        help="produce TEI-XML with <body>")
    args = parser.parse_args()
    if args.body and not args.sourcedoc: 
        print("Cannot produce <body> without <sourceDoc>.\nTo call the program with the --body option, include also the --sourcedoc option.")
    return args.config, args.version, args.header, args.sourcedoc, args.body
    Print("coucou")


if __name__ == "__main__":
    config, version, header, sourcedoc, body = get_args()
    with open(config[0]) as cf_file:
        config = yaml.safe_load(cf_file.read())

    # for every directory in the path indicated in the configuration file,
    # get the directory's name (str) and the paths of its ALTO files (os.path)
    Docs = namedtuple("Docs", ["doc_name", "filepaths"])
    docs = [Docs    (d.name,                                      # name of document folder
                    [f for f in d.iterdir() if f.suffix==".xml"]) # relative filepath for file
            for d in Path(config.get(("data"))["path"]).iterdir() if d.is_dir()]

    print("It starts")

    for d in docs:
        print("Doc being processed")
        # instantiate the class TEI for the current document in the loop
        tree = TEI(d.doc_name, d.filepaths)
        tree.build_tree()
        print("\n=====================================")
        print(f"\33[32m~ now processing document {d.doc_name} ~\x1b[0m")

        if header:
            print(f"\33[33mbuilding <teiHeader>\x1b[0m")
            t0 = perf_counter()
            tree.build_header(config, version[0])
            print("|________finished in {:.4f} seconds".format(perf_counter() - t0))
        
        if sourcedoc:
            print(f"\33[33mbuilding <sourceDoc>\x1b[0m")
            t0 = perf_counter()
            tree.build_sourcedoc()
            print("|________finished in {:.4f} seconds".format(perf_counter() - t0))
        
        if body:
            print(f"\33[33mbuilding <body>\x1b[0m")
            t0 = perf_counter()
            tree.build_body()
            print("|________finished in {:.4f} seconds".format(perf_counter() - t0))
    
        print("We save the file.")

        # -- output XML-TEI file --
        Write(d.doc_name, tree.root).write()