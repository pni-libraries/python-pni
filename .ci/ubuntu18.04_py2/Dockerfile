FROM ubuntu:18.04

MAINTAINER DESY, Jan Kotanski <jankotan@gmail.com>

RUN apt-get -qq update && export DEBIAN_FRONTEND=noninteractive && apt-get -qq install -y software-properties-common curl
RUN curl http://repos.pni-hdri.de/debian_repo.pub.gpg | apt-key add -
RUN add-apt-repository "deb http://repos.pni-hdri.de/apt/debian bionic main" -y
RUN apt-get -qq update && export DEBIAN_FRONTEND=noninteractive && apt-get -qq dist-upgrade
RUN apt-get -qq update && export DEBIAN_FRONTEND=noninteractive && apt-get -qq install -y python-sphinx apt-utils  net-tools
RUN apt-get -qq install -y libpnicore1.1.1-dev libpnicore1.1.1 libpniio1.2.10-dev libpniio1.2.10 libh5cpp0.4.0-dev libh5cpp0.4.0 python-numpy libhdf5-dev libboost-regex-dev libboost-program-options-dev libboost-system-dev libboost-date-time-dev libboost-filesystem-dev libblas-dev libatlas-base-dev cython python-setuptools libboost-python-dev python-numpy-abi9 g++ python-h5py
RUN apt-get -qq install -y hdf5-plugin-bshuf hdf5-plugin-bz2 hdf5-plugin-lz4 hdf5-plugins-common
RUN useradd -ms /bin/bash tango

ENV PKG_CONFIG_PATH=/home/tango/lib/pkgconfig
ENV HDF5_PLUGIN_PATH=/usr/lib/x86_64-linux-gnu/hdf5/plugins
USER tango
WORKDIR /home/tango

