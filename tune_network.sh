#!/bin/bash

# http://fasterdata.es.net/host-tuning/linux/
# https://fasterdata.es.net/network-tuning/udp-tuning/

# socket buffer size
echo '134217728' > /proc/sys/net/core/rmem_max
echo '134217728' > /proc/sys/net/core/wmem_max
echo '134217728' > /proc/sys/net/core/rmem_default
echo '134217728' > /proc/sys/net/core/wmem_default

# tcp buffer limit
echo "4096 87380 67108864" > /proc/sys/net/ipv4/tcp_rmem
echo "4096 87380 67108864" > /proc/sys/net/ipv4/tcp_wmem

# tcp congestion control
#echo 'htcp' > /proc/sys/net/ipv4/tcp_congestion_control

# jumbo frame enabled
echo 1 > /proc/sys/net/ipv4/tcp_mtu_probing

# qdisc
#echo 'fq' > /proc/sys/net/core/default_qdisc
