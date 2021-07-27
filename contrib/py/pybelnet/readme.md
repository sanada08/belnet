# pybelnet

belnet with python 3

    # python3 setup.py install

## bootserv

bootserv is a bootstrap server for accepting and serving RCs

    $ gunicorn -b 0.0.0.0:8000 pybelnet.bootserv:app

## pybelnet instance

obtain `libbelnet-shared.so` from a belnet build

run (root):
    
    # export BELNET_ROOT=/tmp/belnet-instance/
    # export BELNET_LIB=/path/to/libbelnet-shared.so
    # export BELNET_BOOTSTRAP_URL=http://bootserv.ip.address.here:8000/bootstrap.signed
    # export BELNET_PING_URL=http://bootserv.ip.address.here:8000/ping
    # export BELNET_SUBMIT_URL=http://bootserv.ip.address.here:8000/
    # export BELNET_IP=public.ip.goes.here
    # export BELNET_PORT=1090
    # export BELNET_IFNAME=eth0
    # python3 -m pybelnet