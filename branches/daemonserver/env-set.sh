#! /bin/sh

setRunEnv()
{
	echo "setting ...."
	CURRENT_PATH=`pwd`
	LIB_PARENT_PATH=${CURRENT_PATH}/src
	LIB_DETAIL_PATH=${LIB_PARENT_PATH}/tinyxml:${LIB_PARENT_PATH}/threadpool:${LIB_PARENT_PATH}/communication
	export LD_LIBRARY_PATH=${LIB_DETAIL_PATH}:${LD_LIBRARY_PATH}
}


#///////////////////////////////
#// main
#///////////////////////////////
echo "Begin settting the env !"

if [ -d "src" ]; then
	echo "src checking ....ok!"
	setRunEnv
else
	echo "src checking ....failed!"
fi
