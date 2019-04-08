#!/usr/bin/env python3

'''
This script translates SaC code into a format that is reasonably parsable by Doxygen's C/C++ mode.
This reformating mainly replaces SaC-specific keywords with C-specific ones, or removes these. Some
attemps have been made to convert certain SaC syntax into something C-like (this formating makes no
difference to the underlying code, we *do not* expose sourcecode within the documentation. We are
only interested in Doxygen comments and the function signitures and other fields within modules.)

One nastiness comes from Doxygen not supporting abitrary symbols for function names. It allides these
implicitly, meaning if left unhandled, you get functions with strange names. We intentionally translate
such names into english and automatically add a Doxygen comment about this (FYI for the user).

The SaC source files are first passed through CPP, before being passed to Doxygen. We do this
so that we have all possible functions defined, meaning that documentation is more complete.
Additionally, this step removes all macros, some of which Doxygen does not handle well (SaCish macros
can be hellish).
'''

import sys
import re
import argparse
import subprocess
import tempfile

## Fixed patterns
# comments
comment = re.compile (r'^\s*(?:\/\/|\/\*|\*)')
# change external to extern
extern = re.compile (r'^\s*external\s')
# match SaC specifc keywards
sacisms = re.compile (r'^\s*(?:module|specialize|class|use|export|import)\s')
sacclass = re.compile (r'^\s*class\s+(\w+);')
eclasstype = re.compile (r'^\s*external\sclasstype')
classtype = re.compile (r'^\s*classtype\s')
objdef = re.compile (r'^\s*(?:external)?\s*objdef\s')
# match SaC functions
funcs = re.compile (r'(?:\w|\.)+(?:\[[\.\+\*,\d]+\])?\s+[\w\d_\-\+\\%]+\s*\([^\(\)]*\)')
funcargs = re.compile (r'\([^\(\)]*\)')
# match function names as symbols
symbfuncs = re.compile (r'\s(?:!|~|\^|&|&&|<<|>>|\||\|\||!|<|<=|>|>=|==|!=|\+|\+\+|\-|\-\-|\*|\/|%)\s*\([^\(\)]*\)')

# globals
CLASS = ''

def clean_line (line):
    global CLASS
    if re.match (comment, line):
        # skip any line that looks like a comment
        return (line, False)
    ma = re.match (sacclass, line)
    if ma:
        # capture class name for later use
        CLASS = ma.group(1)
    if re.match (sacisms, line):
        if not re.search (r';', line):
            # drop the next line
            return ('', True)
        else:
            # delete only this line
            return ('', False)
    if CLASS:
        line = re.sub (eclasstype, r'typedef classtype {}'.format(CLASS), line)
        line = re.sub (classtype, r'typedef classtype ', line)
        line = re.sub (objdef, r'', line)
    line = re.sub (extern, r'extern ', line)
    if re.search (symbfuncs, line):
        print ('/** @note The name of the function has been altered for documentation reasons, **make sure to use the appropriate symbol instead**, e.g. _operator+_ -> _+_ */')
        # we have to apply these throughout, as some functions might appear all on one line
        line = re.sub (r'\s\+\s*\(', r' operator+ (', line)
        line = re.sub (r'\s\+\+\s*\(', r' operator++ (', line)
        line = re.sub (r'\s\-\s*\(', r' operator- (', line)
        line = re.sub (r'\s\-\-\s*\(', r' operator-- (', line)
        line = re.sub (r'\s\/\s*\(', r' operator/ (', line)
        line = re.sub (r'\s\*\s*\(', r' operator* (', line)
        line = re.sub (r'\s\%\s*\(', r' operator% (', line)
        line = re.sub (r'\s<\s*\(', r' operator< (', line)
        line = re.sub (r'\s<=\s*\(', r' operator<= (', line)
        line = re.sub (r'\s>\s*\(', r' operator> (', line)
        line = re.sub (r'\s>=\s*\(', r' operator>= (', line)
        line = re.sub (r'\s==\s*\(', r' operator== (', line)
        line = re.sub (r'\s!=\s*\(', r' operator!= (', line)
        line = re.sub (r'\s\|\|\s*\(', r' operator|| (', line)
        line = re.sub (r'\s&&\s*\(', r' operator&& (', line)
        line = re.sub (r'\s!\s*\(', r' operator! (', line)
        line = re.sub (r'\s&\s*\(', r' operator& (', line)
        line = re.sub (r'\s\|\s*\(', r' operator| (', line)
        # these ones are not common (used at all?)
        line = re.sub (r'\s<<\s*\(', r' operator<< (', line)
        line = re.sub (r'\s>>\s*\(', r' operator>> (', line)
        line = re.sub (r'\s\^\s*\(', r' operator^ (', line)
        line = re.sub (r'\s~\s*\(', r' operator~ (', line)
    if re.search (funcs, line):
        # found function, lets remove commas between return types
        for m in re.finditer (funcargs, line):
            repl = m.group(0).replace (',', '?COMMA?')
            line = line.replace (m.group(0), repl)
        line = line.replace (',', '')
        line = line.replace ('?COMMA?', ',')
        # doxygen does not handle va_args in return type
        # XXX this is a kludge
        line = line.replace ('... ', 'VARGS ')
    return (line, False)

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Clean SaC (and xSaC) source file for Doxygen parsing')
    parser.add_argument('input', metavar='FILE', type=str,
                   help='SaC source file (use \'-\' for stdin)')
    parser.add_argument('-I', '--include', type=str, action='append', default=['.','include','src/include'],
            help='Include path for CPP (default: %(default)s)')
    parser.add_argument('-D', '--define', type=str, action='append', default=[],
            help='Macro definition for CPP')

    args = parser.parse_args()

    if args.input == '-':
        inpf = sys.stdin
    else:
    #args.input.endswith ('.xsac'):
        incs = []
        for inc in args.include:
            incs.append ('-I' + inc)
        defs = []
        for deff in args.define:
            defs.append ('-D' + deff)
        inpf = tempfile.TemporaryFile (mode='w+')
        proc = subprocess.run (['cpp', '-C', '-P', '-nostdinc', *incs, *defs, '-DSAC_BACKEND_C99', args.input], stdout=inpf)
        inpf.seek (0)
    #else:
    #    inpf = open (args.input)

    with inpf as inp:
        m = False
        for line in inp:
            if (m):
                # we skip over this line
                m = False
                continue
            out, m = clean_line (line)
            print (out.rstrip())
