export NuFlatAna_WD=`pwd`
export NuFlatAna_LIB_PATH=$NuFlatAna_WD/lib/
mkdir -p $NuFlatAna_LIB_PATH

MY_OS_REL=$(cat /etc/os-release | grep ^NAME | sed -e 's/NAME=//g' -e 's/"//g')

if [ "$MY_OS_REL" = "AlmaLinux" ]; then
  source /cvmfs/larsoft.opensciencegrid.org/spack-v0.22.0-fermi/setup-env.sh
  spack load root@6.28.12 arch=linux-almalinux9-x86_64_v3
  spack load gcc@12.2.0
elif [ "$MY_OS_REL" = "Scientific Linux" ]; then

  #Check if PRODUCTS is undefined -- if so, set up relevant ups area
  if [[ -z $PRODUCTS ]]; then
    if [[ $HOSTNAME == "dunegpvm"* ]]; then
      echo DUNE
      source /cvmfs/dune.opensciencegrid.org/products/dune/setup_dune.sh
    elif [[ $HOSTNAME == "uboonegpvm"* ]]; then
      echo "uboone"
      source /cvmfs/uboone.opensciencegrid.org/products/setup_uboone.sh
    elif [[ $HOSTNAME == "sbndgpvm"* ]]; then
      echo "sbnde"
      source /cvmfs/uboone.opensciencegrid.org/products/setup_sbnd.sh
    else
      echo "Warning: Unrecognized hostname $HOSTNAME"
    fi
  fi

  setup root v6_28_12 -q e26:p3915:prof 
  setup cmake v3_27_4
else
  echo "WARNING: Unrecognized OS name \"${MY_OS_REL}\""
  echo "Unable to automatically set up ROOT"
  echo "It is okay if you already have a working ROOT"
fi

export ROOT_INCLUDE_PATH=`root-config --incdir`:$NuFlatAna_WD/plotter/include:$ROOT_INCLUDE_PATH
export LD_LIBRARY_PATH=$NuFlatAna_LIB_PATH:`root-config --libdir`:$LD_LIBRARY_PATH
