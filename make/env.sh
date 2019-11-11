# Environment settings for working on the HPSC stack with Bash
#
# May be setup to autoload on shell startup, since it is harmless as far as
# pollution that affects non-HPSC tasks.

SELF_DIR="$(cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd)"

# On some build hosts, the repository is cloned from a file system path.
# In order to allow multiple user to push and pull from that shared remote
# clone, the permissions of the files created by git need to be at least
# group readable and writable.
git() {
    # execute in a subshell with changed umask
    (umask g=rwx && command git "$@")
}

# Make all invocations of make parallel
NPROC=$(nproc)
if [ "${NPROC}" -ge 8 ] # hack to distinguish a shared server vs local box
then
    NPROC=$((NPROC - 4)) #  don't hog all cores on shared servers
fi
alias make="nice make -j${NPROC}"

USER_RC=${SELF_DIR}/.hpscrc
if [ -f "${USER_RC}" ]
then
    echo "Loading: ${USER_RC}"
    source "${USER_RC}"
fi

SDK_DEP_ENV=${SELF_DIR}/sdk/bld/dep-env.sh
if [ -f ${SDK_DEP_ENV} ]
then
    echo "Loading SDK deps: ${SDK_DEP_ENV}"
    source ${SDK_DEP_ENV}
fi

SDK_ENV=${SELF_DIR}/sdk/bld/env.sh
if [ -f ${SDK_ENV} ]
then
    echo "Loading SDK: ${SDK_ENV}"
    source ${SDK_ENV}
fi
