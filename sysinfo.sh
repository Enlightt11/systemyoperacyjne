#!/bin/bash

get_cpu() {
    echo "CPU:" "$(grep 'model name' /proc/cpuinfo | head -n1 | cut -d ':' -f2-)"
}
get_ram() {
    echo -n "RAM: "
    free -m | awk '/Mem:/ {printf "%s/%s MiB (%.0f%% used)\n", $3, $2, ($3/$2*100)}'
}


get_load() {
       echo "Load:" $(uptime | awk -F, '{print $3",",$4",", $5}' | sed 's/load average//g') 
}

get_kernel() {
       echo "Kernel:" $(uname -a | awk '{print $1, $3}')
}

get_gpu() {
       echo "GPU:" $(lspci | grep -i 'vga' | sed 's/.*: //')
}

get_user() {
       echo "User:" $(echo "$USER")
}

get_shell() {
       echo "Shell:" $(basename "$SHELL")
}

get_processes() {
       echo "Processes:" $(ps -aux | wc -l)
}

get_threads() {
       echo "Threads:" $(ps -eLf | wc -l)
}

get_ip() {
       echo "IP:" $(ip -o -4 address | awk '{print $4}')
}

get_dns() {
       echo "DNS:" $(grep nameserver /etc/resolv.conf | awk '{print $2}')
}

get_internet() {
       echo $(timeout 1 ping -c1 8.8.8.8 >/dev/null && echo "Internet: OK" || echo "Internet: Fail")        
}

if [ $# -eq 0 ]; then
    get_cpu
    get_ram
    get_load
    get_kernel
    get_gpu
    get_user
    get_shell
    get_processes
    get_threads
    get_ip
    get_dns
    get_internet
else

    for arg in "$@"; do
    
        case "${arg,,}" in
            cpu) cpu ;;
            ram) ram ;;
            load) load ;;
            kernel) kernel ;;
            gpu) gpu ;;
            user) user ;;
            shell) shell ;;
            processes) processes ;;
            threads) threads ;;
            ip) ip ;;
            dns) dns ;;
            internet) internet ;;
       esac
   done
fi