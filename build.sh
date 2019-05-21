#!/bin/sh
srcnames () {
    srcfiles=$(ls $1/*.c)
    for src in $srcfiles
    do
        echo $(printf '%s' "${src%.c}")
    done
}
objnames () {
    for src in $@
    do
        echo $build_dir/$src.o
    done
}
create_dir () {
    if ! [ -d $1 ]
    then
        mkdir $1
    fi
}
for arg in $@
do
    if [ $arg = clean ]
    then
        clean=1
    fi
    if [ $arg = debug ]
    then
        debug=1
    fi
    if [ $arg = test ]
    then
        test=1
    fi
done
srcs=$(srcnames .)
test_srcs=$(srcnames tests)
build_dir=build
create_dir $build_dir
objs=$(objnames $srcs)
if [ $((debug)) -eq 1 ]
then
    cflags="-std=c99 -O0 -g -Wall"
else
    cflags="-std=c99 -O3"
fi
echo $cflags
cc="clang -c $cflags"
ld="clang -flto"
for src in $srcs
do
    $cc "$src.c" -o "$build_dir/$src.o"
done

if [ $((test)) -eq 1 ]
then
    create_dir $build_dir/tests
    for test_src in $test_srcs
    do
        $cc "$test_src.c" -o "$build_dir/$test_src.o"
        $ld "$build_dir/$test_src.o" $objs -o "$build_dir/$test_src"
    done
fi
if [ $((clean)) -eq 1 ]
then
    rm -f $build_dir/*
    rm -f $build_dir/tests/*
    exit 0
fi
