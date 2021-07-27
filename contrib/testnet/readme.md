loopback testnet scripts

requirements:

* bash
* python3
* supervisord


setup:

make a testnet compatable belnet build:

    $ cmake -DWITH_TESTNET=ON -B build-testnet -S .
    $ make -C build-testnet belnet

usage:

from root of repo run:

    $ ./contrib/testnet/testnet.sh build-testnet/daemon/belnet 20 200
    
this will spin up 20 master nodes and 200 clients
