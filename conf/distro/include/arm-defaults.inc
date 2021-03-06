# This function changes the default tune for machines which
# are based on armv7a to use common tune value, note that we enforce hard-float
# which is default on RPB for armv7+
# so if you have one of those machines which are armv7a but can't support
# hard-float, please change tune = 'armv7athf' to tune = 'armv7at'
# below but then this is for your own distro, RPB will not support
# it
#
# Imported from https://github.com/Angstrom-distribution/meta-angstrom/blob/master/conf/distro/include/arm-defaults.inc

def arm_tune_handler(d):
    features = d.getVar('TUNE_FEATURES', True).split()
    if 'armv7a' in features or 'armv7ve' in features:
        tune = 'armv7athf'
        if 'bigendian' in features:
            tune += 'b'
        if 'neon' in features:
            tune += '-neon'
    # cortexa* tune files only list 'arm' in features instead of 'armv7*', so
    # try matching it on neon
    elif 'arm' in features and 'neon' in features:
        tune = 'armv7athf'
        if 'bigendian' in features:
            tune += 'b'
        if 'neon' in features:
            tune += '-neon'
    else:
        tune = d.getVar('DEFAULTTUNE', True)
    return tune

# Should use a distro override
DEFAULTTUNE := "${@arm_tune_handler(d)}"
