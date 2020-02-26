#!/bin/bash -xe
#

sudo apt-get install build-essential libssl-dev libz-dev libsqlite3-dev \
    libcurl4-gnutls-dev libdaemon-dev automake autoconf pkg-confg libtool libcppunit-dev \
    libnl-3-dev libnl-cli-3-dev libnl-genl-3-dev libnl-nf-3-dev libnl-route-3-dev libarchive-dev \
    libarchive-dev

cd ..
DESTDIR="$(pwd)/linux-inst"

# set defaults
[ -z "${CLEAN}" ] && CLEAN=1
[ -z "${STRIP}" ] && STRIP=1
[ -z "${DEBUG}" ] && DEBUG=0
[ -z "${PROFILE}" ] && PROFILE=0

CXXFLAGS=""

if [ ${DEBUG} -eq 1 ]; then
    CXXFLAGS+=" -ggdb -g3 -Wall"
    STRIP=0
fi

if [ ${PROFILE} -eq 1 ]; then
    CXXFLAGS+=" -pg"
fi

# clean destdir
rm -rf ${DESTDIR}
mkdir linux-inst
chown -R $USER:$GROUPS linux-inst

cd ibrcommon
if [ ${CLEAN} -eq 1 ]; then
    [ -f Makefile ] && make clean
    bash autogen.sh
    ./configure --prefix=${DESTDIR} --with-openssl --with-lowpan
fi
make -j
make install
cd ..

cd ibrdtn/ibrdtn
if [ ${CLEAN} -eq 1 ]; then
    [ -f Makefile ] && make clean
    bash autogen.sh
    ./configure --prefix=${DESTDIR} --with-dtnsec --with-compression
fi
make -j
make install
cd ..

cd daemon
if [ ${CLEAN} -eq 1 ]; then
    [ -f Makefile ] && make clean
    bash autogen.sh
    ./configure --prefix=${DESTDIR} --with-curl --with-lowpan --with-sqlite --with-dtnsec --with-compression --with-tls --with-cppunit --without-vmime
fi
make -j
make install
cd ..
cd ..

if [ ${STRIP} -eq 1 ]; then
# strip binaries
BINARIES="sbin/dtnd"
for BINARY in ${BINARIES}; do
    strip ${DESTDIR}/${BINARY}
done
fi

echo "export LD_LIBRARY_PATH=/usr/local:/usr/local" >> ~/.bashrc
export LD_LIBRARY_PATH=/usr/local/:/usr/local