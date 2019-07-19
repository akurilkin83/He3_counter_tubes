echo
echo ----------------------------------
echo Terminal set to use Geant4-10.03
echo ----------------------------------
echo

export TOOLS=/home/lnf_user/CERN

#CLHEP
export CLHEP_DIR=${TOOLS}/clhep/install
export CLHEP_INCLUDE_DIR=${CLHEP_DIR}/include/
export CLHEP_LIBRARY=${CLHEP_DIR}/lib/
export LD_LIBRARY_PATH=${CLHEP_LIBRARY}:${LD_LIBRARY_PATH}
export PATH=${CLHEP_DIR}/bin/:${PATH}




export ROOTSYS=/home/lnf_user/CERN/root6.14.06_install
export PATH=$PATH:$ROOTSYS/bin


# Geant4 installation path
export G4INSTALLPATH=/home/lnf_user/CERN/geant4_install
# Variable which may be imported as a 'cmake' variable
export Geant4_DIR=$G4INSTALLPATH/lib64/Geant4-10.4.2
echo On this terminal Geant4_DIR=$Geant4_DIR
# Working directory
export G4WORKDIR=~/g4work/10.4.2
export PATH=$G4WORKDIR/bin/Linux-g++:$PATH
#JMQ 16072012 --------------------------
export G4BIN=$G4WORKDIR/bin
export G4SYSTEM=Linux-g++
export G4INSTALL=/home/lnf_user/CERN/Geant4/geant4.10.04.p02
#---------------------
echo On this terminal G4WORKDIR=$G4WORKDIR

# Environment variables of the data files
export G4DATADIR=$G4INSTALLPATH/share/Geant4-10.4.2/data

export G4PROTONHPDATA=/home/lnf_user/CERN/geant4_install/share/Geant4-10.4.2/data/G4TENDL1.3/Proton
echo On this terminal G4PROTONHPDATA=$G4PROTONHPDATA
export G4DEUTERONHPDATA=/home/lnf_user/CERN/geant4_install/share/Geant4-10.4.2/data/G4TENDL1.3/Deuteron
echo On this terminal G4DEUTERONHPDATA=$G4DEUTERONHPDATA
export G4TRITONHPDATA=/home/lnf_user/CERN/geant4_install/share/Geant4-10.4.2/data/G4TENDL1.3/Triton
echo On this terminal G4TRITONHPDATA=$G4TRITONHPDATA
export G4HE3HPDATA=/home/lnf_user/CERN/geant4_install/share/Geant4-10.4.2/data/G4TENDL1.3/He3
echo On this terminal G4HE3HPDATA=$G4HE3HPDATA
export G4ALPHAHPDATA=/home/lnf_user/CERN/geant4_install/share/Geant4-10.4.2/data/G4TENDL1.3/Alpha
echo On this terminal G4ALPHAHPDATA=$G4ALPHAHPDATA
export G4NEUTRONHP_SKIP_MISSING_ISOTOPES=1
echo On this terminal G4NEUTRONHP_SKIP_MISSING_ISOTOPES=1
export G4PHP_DO_NOT_ADJUST_FINAL_STATE=1
echo On this terminal G4PHP_DO_NOT_ADJUST_FINAL_STATE=1
export AllowForHeavyElements=1
echo On this terminal AllowForHeavyElements=1
export G4NEUTRONHP_USE_ONLY_PHOTONEVAPORATION=0
echo On this terminal G4NEUTRONHP_USE_ONLY_PHOTONEVAPORATION=0
export G4NEUTRONHP_PRODUCE_FISSION_FRAGMENTS=1
echo On this terminal G4NEUTRONHP_PRODUCE_FISSION_FRAGMENTS=1
export G4PHP_NEGLECT_DOPPLER=0
echo On this terminal G4PHP_NEGLECT_DOPPLER=0

export G4ABLADATA=$G4DATADIR/G4ABLA3.0
echo On this terminal G4ABLADATA=$G4ABLADATA
export G4LEDATA=$G4DATADIR/G4EMLOW6.50
echo On this terminal G4LEDATA=$G4LEDATA
export G4LEVELGAMMADATA=$G4DATADIR/PhotonEvaporation4.3
echo On this terminal G4LEVELGAMMADATA=$G4LEVELGAMMADATA
#export G4NEUTRONHPDATA=$G4DATADIR/G4NDL4.5
#export G4NEUTRONHPDATA=$G4DATADIR/JENDL-4.0
#export G4NEUTRONHPDATA=$G4DATADIR/JEFF31N
#export G4NEUTRONHPDATA=$G4DATADIR/ENDF-VII0
#echo On this terminal G4NEUTRONHPDATA=$G4NEUTRONHPDATA
#export G4NEUTRONXSDATA=$G4DATADIR/G4NEUTRONXS1.4
#echo On this terminal G4NEUTRONXSDATA=$G4NEUTRONXSDATA
export G4PIIDATA=$G4DATADIR/G4PII1.3
echo On this terminal G4PIIDATA=$G4PIIDATA
export G4RADIOACTIVEDATA=$G4DATADIR/RadioactiveDecay5.1
echo On this terminal G4RADIOACTIVEDATA=$G4RADIOACTIVEDATA
export G4REALSURFACEDATA=$G4DATADIR/RealSurface1.0
echo On this terminal G4REALSURFACEDATA=$G4REALSURFACEDATA
export G4SAIDDATA=$G4DATADIR/G4SAIDDATA1.1
echo On this terminal G4SAIDDATA=$G4SAIDDATA
export G4NEUTRONHP_SKIP_MISSING_ISOTOPES=1
echo On this terminal G4NEUTRONHP_SKIP_MISSING_ISOTOPES=1
export G4NEUTRONHP_DO_NOT_ADJUST_FINAL_STATE=1
echo On this terminal G4NEUTRONHP_DO_NOT_ADJUST_FINAL_STATE=1
export AllowForHeavyElements=1
echo On this terminal AllowForHeavyElements=1

export G4ROOT_USE=1
echo On this terminal G4ROOT_USE=1

# Remaining environment variables
source $G4INSTALLPATH/bin/geant4.sh
echo '--------------------------------------------------------'
echo ' Further information on cmake configuration of the'
echo ' loaded Geant4 compilation may be found at $Geant4_DIR.'
echo '--------------------------------------------------------'
echo
##JMQ para correr test30iaea 31032013
#export REFERENCE=geant4.9.6.p03 

