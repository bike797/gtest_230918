git submodule update --init --recursive

if [ "$1" == "" ]; then
    echo pleas input with build project
    echo "ex) $ setup_buildenv.sh [test project]"
else
    cmake -S ./$1 -B ./build
fi
