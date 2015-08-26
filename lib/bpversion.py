import subprocess, os, re

class VersionError(Exception):
    pass
class ExecutionError(VersionError):
    def __init__(self, errcode):
        self.error_code = errcode

def _check(process):
    if process.returncode != 0:
        raise ExecutionError(process.returncode)

def get_rel_spec_stable(rel):
    """
    Returns release specs for a linux-stable backports based release.
    """
    m = None
    if ("rc" in rel):
        m = re.match(r"v*(?P<VERSION>\d+)\.+" \
                     "(?P<PATCHLEVEL>\d+)[.]*" \
                     "(?P<SUBLEVEL>\d*)" \
                     "[-rc]+(?P<RC_VERSION>\d+)",
                     rel)
    else:
        m = re.match(r"(?P<VERSION>\d+)\.+" \
                     "(?P<PATCHLEVEL>\d+)[.]*" \
                     "(?P<SUBLEVEL>\d*)",
                     rel)
    if (not m):
        return m
    return m.groupdict()

def kernelversion(tree):
    cmd = ['make', '--no-print-directory', '-C', tree, 'kernelversion' ]
    process = subprocess.Popen(cmd,
                               stdout=subprocess.PIPE, stderr=subprocess.STDOUT,
                               close_fds=True, universal_newlines=True)
    stdout = process.communicate()[0]
    process.wait()
    _check(process)
    return stdout.strip()

def genkconfig_versions(rel_specs):
    def gen_versions(version, patchlevel, max_patchlevel=20):
        versions = ''
        for i in range(patchlevel, max_patchlevel):
            versions += "config BACKPORT_KERNEL_%s_%s\n" % (version, i)
            versions += "    def_bool y\n"
        return versions

    data = ''
    data += gen_versions(int(rel_specs['VERSION']), int(rel_specs['PATCHLEVEL']) + 1)
    data += gen_versions(4, 0, 3)
    return data
