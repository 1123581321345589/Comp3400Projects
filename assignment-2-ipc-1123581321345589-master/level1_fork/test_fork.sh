#!/bin/sh

# Check if program exists
if [ ! -f fork_main ]; then
    echo "fork_main doesn't exist!"
    exit 1;
fi

out=$(./fork_main)
child_pid=$(echo "$out" | sed -n 's/Child process PID is \([0-9]\+\)/\1/p')
parent_sees_childpid=$(echo "$out" | sed -n "s/I'm the parent. Their PID is \([0-9]\+\)/\1/p")
child_status=$(echo "$out" | sed -n "s/Child's status is \([0-9]\+\)/\1/p")

if [ -z "$child_pid" ]; then
    echo "Line1 output missing"
    exit 1
fi
if [ -z "$parent_sees_childpid" ]; then
    echo "Line2 output missing"
    exit 1
fi
if [ -z "$child_status" ]; then
    echo "Line3 output missing"
    exit 1
fi

if [ "$child_pid" -ne "$parent_sees_childpid" ]; then
    echo "ERROR: PID of child and child's PID by parent doesn't match?"
    exit 2
fi
if [ "$child_status" -ne 42 ]; then
    echo "ERROR: Child exit status not 42"
    exit 2
fi
