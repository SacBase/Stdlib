# This file inspects whether any existing module imports/uses
# an extended version of the module and if so, it generates
# an ext version of the file, where all the references to the
# regular modules are replaced with references to the corresponding
# ext modules.

import os
import re
import sys
import subprocess

SAC2C_SOURCE_DIR = "src"

SAC2C_FLAGS = ["-cppIinclude", "-DEXT_STDLIB"]

SAC2C_EXEC = "/tmp/sac2c/build/sac2c_p"

# A dictionary of files where the filename without extension
# is a key, and value True means that the module needs extended
# version and False that it doesn't
CHECKED_SAC = {}

SAC_CORE_FILES = []
SAC_EXT_FILES = []
DEPS = {}


def die (msg):
    print >>sys.stderr, msg
    sys.exit (-1)

def error (msg):
    die ("error: %s" % msg)

def warning (msg):
    print >>sys.stderr, "warning: %s" %msg

def info (msg):
    print "info: %s" % msg

def get_name_from_path (f):
    "Get the name we are going to add to the file"
    return os.path.splitext (os.path.basename (f))[0]

def get_path_from_name (f):
    for sf in SAC_CORE_FILES + SAC_EXT_FILES:
        #print f
        if re.match (r".*/%s.x?sac$" % f, sf):
            return sf
    error ("no sac path for name `%s'" % f)

def get_deps (f):
    deps_str = subprocess.check_output ([SAC2C_EXEC]
                                      + SAC2C_FLAGS
                                      + ["-M"]
                                      + [os.path.join (SAC2C_SOURCE_DIR, f)])
    deps = []
    for d in  deps_str.strip ().split ("\n"):
        if re.match (r".*\.o$", d) or re.match (r"^-l.*", d):
            continue
        dn = re.sub (r"lib([\w-]+)(Tree|Mod).so", r"\1",  d)
        if dn not in deps:
            deps.append (dn)

    if deps == [""]:
        deps = []

    return deps


def check_sac_file (name_we, lst):
    if name_we in CHECKED_SAC:
        return CHECKED_SAC[name_we]

    f = get_path_from_name (name_we)
    #print "checking deps for", f
    deps = get_deps (f)
    DEPS[f] = deps;

    #print "deps", f, deps
    needs_ext = False
    for d in deps:
        if d in lst:
            error ("there is a recursive cycle in your dependencies: `%s' -> %d "
                   % (" -> ".join (lst), d))
        #print "\trec call for `%s'" % d
        if check_sac_file (d, lst+[d]):
            needs_ext = True
            break

    CHECKED_SAC[name_we] = needs_ext
    return needs_ext


def parse_sac_sources (fname):
    f = open (fname, "r")
    lines = f.readlines ()
    for _n, l in enumerate (lines):
        n = _n + 1
        # get rid of comments
        l = re.sub (r"#.*$", "", l)
        l = l.strip ()
        if l == "":
            continue
        m = re.match (r"([\w\./]+)(\.x?sac)\s+(Ext|Core)", l)
        if m is None:
            error ("error in file %s:%i" % (fname, n))
        #print m.groups ()
        ext = m.groups ()[1]
        name = m.groups ()[0] + ext
        kind = m.groups ()[2]
        name_we = get_name_from_path (name)

        if kind == "Core" and ext == ".xsac" :
            CHECKED_SAC[name_we] = True

        if kind == "Ext":
            SAC_EXT_FILES.append (name)
        else:
            SAC_CORE_FILES.append (name)

    f.close ()

parse_sac_sources ("/tmp/Stdlib/cmake/sac-core-ext.txt")

# Check all the core files whether they depend on altered Core xsac files
for f in SAC_CORE_FILES:
    name_we = get_name_from_path (f)
    check_sac_file (name_we, [name_we])

# Remove the xsac files from CHECKED_SAC and check them
# against the dependencies propagated from these very files
for f in SAC_CORE_FILES:
    if re.match (r".*\.xsac$", f):
        name_we = get_name_from_path  (f)
        del CHECKED_SAC[name_we]

for f in SAC_CORE_FILES:
    if re.match (r".*\.xsac$", f):
        name_we = get_name_from_path (f)
        check_sac_file (name_we, [name_we])


def get_rename_pattern (deps):
    return ["%s -> %sExt"%(x,x) for x in DEPS[f] 
            if get_path_from_name (x) in SAC_CORE_FILES
               and (re.match (r".*\.xsac$", get_path_from_name (x))
                    or CHECKED_SAC[x])]

# core xsac files not in the list
for f in SAC_CORE_FILES:
    name_we = get_name_from_path (f)
    if re.match (r".*\.xsac", f):
        if not CHECKED_SAC[name_we]:
            print "rename `%s' into `%sExt.xsac' (add import \"%s\":all;)" \
                  % (f, name_we, name_we)
        else:
            print "rename `%s' into `%sExt.xsac' (add import \"%s\":all;) and" \
                  % (f, name_we, name_we)
            if f not in DEPS:
                DEPS[f] = get_deps (f)
            
            print "\t", get_rename_pattern (DEPS[f])

    elif re.match (r".*\.sac$", f):
        if CHECKED_SAC[name_we]:
            print "rename `%s' into `%sExt.sac' and" \
                  % (f, name_we)
            if f not in DEPS:
                DEPS[f] = get_deps (f)
            
            print "\t", get_rename_pattern (DEPS[f])

for f in SAC_EXT_FILES:
    name_we = get_name_from_path (f)
    
    if f not in DEPS:
        DEPS[f] = get_deps (f)

    rename_lst = get_rename_pattern (DEPS[f])
    if rename_lst != []:
        print "substitute in the `%s' external file" % f
        print "\t", rename_lst
    

# Now, we have computed which core files have to be turned into Ext files.
# For every xsac file:
#     * if it is a core xsac file, and it is not in the list
#       then generate <filename>Ext file by cnahging modulename/classname
#       to <filename>Ext and adding "import <filename>: all;" statement;
#     
#     * if it is a core xsac file and it is in the list
#       then we generate <filename>Ext file by changing modulename/class
#       to <filename>Ext, adding "import <filename>: all;" and by
#       changing "use <modname>", "import <modname>", "<modname>::x" to
#       "use <modname>Ext", "import <moname>Ext" and "<modname>Ext::x"
#       respectively.
#
#     * if it is an ext xsac file and it is in the list
#       then we substitute used/imported modules with Ext versions of
#       those modules.
#    
#     * if it is an ext xsac that is not in the list
#       we do nothing.
#     
# For every sac file that is in the list:
#     * if it is a core sac we generate <filename>Ext version
#       of the file where we change "class/module <filename>" into 
#      "class/module <filename>Ext" as well as 
#      "use <modname>", "import <modname>", "<modname>::x" into
#      "use <modname>Ext", "import <moname>Ext" and "<modname>Ext::x"
#      respectively.
#
#     * if it is an ext sac we substitute use/import for extended
#       versions.


