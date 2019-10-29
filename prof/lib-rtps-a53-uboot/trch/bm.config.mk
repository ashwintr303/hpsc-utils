# TODO: issue is that we might not be using lib-trch-bm-min but -default, in
# which case HPPS mailbox will get enabled... need to have a
# "partially-minimal" overlay, applied for all profiles, including for
# -default; this partial overlay will modify the default from the child
# repository (which is not appropriate for the profiling system).
# As it is right now, this profile is incompatible with HPPS profiles.
#
CONFIG_HPPS_TRCH_MAILBOX_ATF 		= 0
# TODO: when the above is done, this will go away too (will be in
# partially-minimal)
CONFIG_RTPS_A53_TRCH_MAILBOX_ATF 	= 0
