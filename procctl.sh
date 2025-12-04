#!/bin/bash

list_processes_by_cpu_usage() {
       ps aux --sort=-%cpu | head -n 6
}

list_processes_by_memory_usage() {
       ps aux --sort=-%mem | head -n 6
}

show_process_tree() {
       pstree -p
}

show_process_name_by_PID() {
       read -p "Pid: " PID
       ps -p "$PID"
}

show_process_PID_by_name() {
       read -p "Process name: " name
       ps aux | grep "$name" | awk '{print $2}'
}

kill_process_by_pid() {
       read -p "PID to kill: " pid
       kill "$pid"
}

kill_proccess_by_name() {
       read -p "Process name to kill: " name
       pkill "$name"
}

while true; do
    echo "Process Control:"
    echo "1) List top 5 processes by CPU usage"
    echo "2) List top 5 processes by memory usage" 
    echo "3) Show process tree"
    echo "4) Show process name by PID"
    echo "5) Show process PID(s) by name"
    echo "6) Kill process by PID"
    echo "7) Kill process by name"
    echo "q) Exit"
    echo -n "Choice: "
    read choice

    case $choice in
        1) list_processes_by_cpu_usage ;;
        2) list_processes_by_memory_usage ;;
        3) show_process_tree ;;
        4) show_process_name_by_PID ;;
        5) show_process_PID_by_name ;;
        6) kill_process_by_pid ;;
        7) kill_proccess_by_name ;;
        q) exit 0 ;;
        *) echo "Invalid argument" ;;
    esac
done