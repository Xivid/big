#!/bin/bash

if [ $# -ne 1 ]; then
        echo "Usage: $0 <op>"
        echo "- enable_did"
        echo "- disable_did"
        echo "- enable_dtid"
        echo "- disable_dtid"
        exit 1
fi
op=$1

modprobe msr

enable_dtid()
{
        local ncpus=$(nproc --all)
        local cpus=$((ncpus - 1))

        for i in `seq 0 $cpus`; do taskset -c $i ./run_did hc_setup_dtid; done
        for i in `seq 0 $cpus`; do wrmsr -p $i 0x838 0x616d; done
}

disable_dtid()
{
        local ncpus=$(nproc --all)
        local cpus=$((ncpus - 1))

        for i in `seq 0 $cpus`; do taskset -c $i ./run_did hc_restore_dtid; done
        for i in `seq 0 $cpus`; do wrmsr -p $i 0x838 0x616d; done
}

enable_did()
{
        local ncpus=$(nproc --all)
        local cpus=$((ncpus - 1))
        
        # use the physical x2APIC IDs
        for i in `seq 0 $cpus`; do taskset -c $i ./run_did hc_set_x2apic_id; done

        # enable DTID
        for i in `seq 0 $cpus`; do taskset -c $i ./run_did hc_setup_dtid; done
        for i in `seq 0 $cpus`; do taskset -c 0 ./run_did send_ipi $i 0xef; done

        # enable DIPI
        ./run_did set_apic_ipi
        for i in `seq 0 $cpus`; do taskset -c $i ./run_did set_x2apic_id; done
        for i in `seq 0 $cpus`; do taskset -c $i ./run_did hc_disable_intercept_wrmsr_icr; done

}

disable_did()
{
        local ncpus=$(nproc --all)
        local cpus=$((ncpus - 1))

        # disable DIPI
        for i in `seq 0 $cpus`; do taskset -c $i ./run_did hc_enable_intercept_wrmsr_icr; done
        for i in `seq 0 $cpus`; do taskset -c $i ./run_did restore_x2apic_id; done
        ./run_did restore_apic_ipi

        # disable DTID
        for i in `seq 0 $cpus`; do taskset -c $i ./run_did hc_restore_dtid; done
        for i in `seq 0 $cpus`; do wrmsr -p $i 0x838 0x616d; done

        # use the VCPU IDs as the x2APIC IDs
        for i in `seq 0 $cpus`; do taskset -c $i ./run_did hc_restore_x2apic_id; done
}

if [ $op = "enable_did" ]; then
        enable_did
elif [ $op = "disable_did" ]; then
        disable_did
elif [ $op = "enable_dtid" ]; then
        enable_dtid
elif [ $op = "disable_dtid" ]; then
        disable_dtid
else
        echo "no such operation"
fi
