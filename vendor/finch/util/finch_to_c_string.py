#!/usr/bin/env python
# coding: utf-8

import argparse
import glob
import os.path
import re

# The source for the Finch modules that are built into the VM or CLI are turned
# include C string literals. This way they can be compiled directly into the
# code so that file IO is not needed to find and read them.
#
# These string literals are stored in files with a ".finch.inc" extension and
# #included directly by other source files. This generates a ".finch.inc" file
# given a ".finch" module.

PREAMBLE = """// Generated automatically from {0}. Do not edit.
static const char* {1}ModuleSource =
{2};
"""

def finch_to_c_string(input_path, finch_source_lines, module):
  finch_source = ""
  for line in finch_source_lines:
    line = line.replace("\\", "\\\\")
    line = line.replace('"', "\\\"")
    line = line.replace("\n", "\\n\"")
    if finch_source: finch_source += "\n"
    finch_source += '"' + line

  return PREAMBLE.format(input_path, module, finch_source)


def main():
  parser = argparse.ArgumentParser(
      description="Convert a Finch library to a C string literal.")
  parser.add_argument("output", help="The output file to write")
  parser.add_argument("input", help="The source .finch file")

  args = parser.parse_args()

  with open(args.input, "r") as f:
    finch_source_lines = f.readlines()

  module = os.path.splitext(os.path.basename(args.input))[0]
  module = module.replace("opt_", "")
  module = module.replace("finch_", "")

  c_source = finch_to_c_string(args.input, finch_source_lines, module)

  with open(args.output, "w") as f:
    f.write(c_source)


main()
