#!/bin/bash

usage() { echo " Usage: $0 :-b <Debug/Release> -c (for clean build)" 1>&2; exit 1;}
createfolders() { #take build type parameter

if [[ ! -d  "build" ]]; then
    mkdir build
    mkdir build/$1
else
    cd build
     [ ! -d  $1 ]  && mkdir $1
     cd ..

fi
}

callcmake(){
    cmakerootdir=$(pwd)
    build_dir=${cmakerootdir}"/build/"$1

    if [[ $# -eq 1 ]]; then

        echo "Its not a clean build"

        if [[ $1 == "Debug" ]]; then
            echo "Debug build"
            echo ${cmakerootdir}
            echo ${build_dir}
            cmake -S ${cmakerootdir} -DCMAKE_BUILD_TYPE=$1 -B ${build_dir}
        else
         echo "Release build"
         echo ${cmakerootdir}
            echo ${build_dir}
            cmake -s ${cmakerootdir} -DCMAKE_BUILD_TYPE=$1 -b ${build_dir}
        fi

    else
        echo "its a clean build "

        if [[ $1 == "Debug" ]]; then
            cmake -S ${cmakerootdir} -DCMAKE_BUILD_TYPE=$1  -B ${build_dir}
            cmake --build ${build_dir} --clean-first
        else
            echo "$1"
             cmake -S ${cmakerootdir} -DCMAKE_BUILD_TYPE=$1  -B ${build_dir}
             #cmake --build ${build_dir} --clean-first
        fi

    fi

}


while getopts ":b:ch" flag; do

    case ${flag} in
        b )
            build_flag=${OPTARG}
            ;;
        c)
            clean_build_flag=true
            ;;

        h)
        usage;
        ;;
        *)
        usage
        ;;

    esac

done

if [[ -z "$build_flag" ]]; then
    echo "build_flag is empty; setting build flag to debug"
    build_flag="Debug"
fi

if [[ ${build_flag} != "Debug" ]]; then

    if [[ ${build_flag} != "Release" ]]; then
        echo "set a correct build flag: Debug/Release"
        exit 1
    fi
fi



    if [[ ${clean_build_flag} == true ]]
    then
        echo "clean build flag"

        createfolders ${build_flag}
        callcmake ${build_flag} ${clean_build_flag}

    else
        echo "no clean build flag"
        createfolders ${build_flag}
        callcmake ${build_flag}
    fi


