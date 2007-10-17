#!/bin/bash


################################################################################
#                                                                              #
#                                   rbkt usage                                 #
#                                                                              #
################################################################################


function usage ()
{
  echo "rbkt.sh [-b bucketName [-q queryName]] [-h]"
  echo
  echo "Run a single query, or all the queries inside a directory (bucket), or all"
  echo "the queries that can be found anywhere inside the Queries dir."
  echo 
  echo "-b bucketName: bucketName is a relative pathname used to construct full"
  echo " pathnames for the directories that contain a group of queries, their"
  echo " expected results, and their actual results. For example, if bucketName"
  echo " is foo, rbkt will run queries in "
  echo "specify 3 directories:"
  echo "     (a) a directory where files containing query strings are located;"
  echo "            in this case the pathname is relative to the Queries directory"
  echo "            in the test environment"
  echo "        (b) the directory where the query-results files will be written;"
  echo "            in this case the pathname is relative to Output/dump"
  echo "            If not specified, all of the directories under Queries will be "
  echo "            visited, and the queries in them run."
  echo "-q : The query to run. The query string is in file <queryName>.xq inside"
  echo "         the bucketName directory."
  echo "-h : help"
}


################################################################################
#                                                                              #
#                                 Test Directories                             #
#                                                                              #
################################################################################

#
# Function to check the existence of the required test dirs and to create
# the results dir.
#
function buildDirEnv
{
  echo; echo "buildDirEnv: Checking/Building Environment Directories"

  if [ ! -d ${zorbaRepos} ]; then
     echo "ERROR 5 buildDirEnv: zorba root directory ${sorbaRepos} does not exist"
     return 5
  fi

  if [ ! -d ${testRootDir} ]; then
     echo "ERROR 10 buildDirEnv: test root directory ${testRootDir} does not exist"
     return 10
  fi

  if [ ! -d ${queriesDir} ]; then
     echo "ERROR 12 buildDirEnv: queries directory ${queriesDir} does not exist"
     return 12
  fi
  if [ ! -d ${expResultsDir} ]; then
     echo "ERROR 13 buildDirEnv: expected results directory ${expResultsDir} does not exist"
     return 13
  fi
  if [ ! -d $scriptsDir ]; then
     echo "ERROR 14 buildDirEnv: test scripts directory $scriptsDir does not exist"
     return 14
  fi

  mkdir -p ${resultsDir}

  return 0
}


################################################################################
#                                                                              #
#                                 Running Queries                              #
#                                                                              #
################################################################################


#params: 
#
# $1 - queryFile  : Full pathname of the file that contains the query string
function run_query
{
  local error=0

  local queryFile="$1"

  local EXE=${binPath}/query_exec

  if [ ! -e "${EXE}" ]; then
    echo "ERROR 1 run_query: binary executable ${EXE} not found"
    exit 17
  fi

  ${EXE} -o "${queryFile}"
  error=$?
  if [ ${error} != 0 ]; then
    echo "ERROR 2 run_query: ${EXE} $1 failed with error code ${error}"
    # To allow more queries to be run by the caller, do not propagate error
  fi

  return 0
}


#params
#
# $1 bucketName         : See run_bucket() function
# $2 queryName          : The query name.
function run_query_in_bucket
{
  local error=0

  local bucketName="$1"
  local queryName="$2"

  local queryDir="${queriesDir}/${bucketName}"
  local queryFile="${queryDir}/${queryName}.xq"

  local expResultDir="${expResultsDir}/${bucketName}"
  local expResultFile="${expResultDir}/${queryName}.res"

  local resultDir="${resultsDir}/${bucketName}"
  local resultFile="${resultDir}/${queryName}.res"
  local diffFile="${resultDir}/${queryName}.diff"

  if [ ! -e "${queryFile}" ]; then
    echo "ERROR 1 run_query_in_bucket: query file ${queryFile} does not exist"
    return 17
  fi

  #
  # Create results directory, if it doesn't exist already.
  # If it exists, then clean it up.
  #
  mkdir -p "${resultDir}"
  if [ $? != 0 ]; then echo "ERROR 2 run_query_in_bucket: mkdir -p failed"; exit 19; fi
  rm -f "${resultDir}"/${queryName}.*

  #
  # Run the query
  #
  run_query "${queryFile}"
  error=$?
  if [ ${error} != 0 ]; then
    echo "ERROR 3 run_query_in_bucket: run_query failed with error code ${error}"
    return ${error}
  fi

  #
  # query_exec creates the result file in the same dir as the query file.
  # So, we must move the result file to the result dir.
  #
  # If no result file was generated, then we create an empty one.
  #
  if [ -e "${queryDir}/${queryName}.xq.res" ]; then
    mv "${queryDir}/${queryName}.xq.res" "${resultFile}"
    if [ $? != 0 ]; then echo "ERROR 12 run_query_in_bucket: mv failed"; exit 19; fi
  else
    touch "${resultFile}"
    if [ $? != 0 ]; then echo "ERROR 13 run_query_in_bucket: touch failed"; exit 19; fi
  fi

  #
  # Do the diffs
  #
  if [ -e "${expResultFile}" ]; then
    diff -I 'Duration.*' "${resultFile}" "${expResultFile}" > "${diffFile}"
  else
    echo "unknown expected results for ${queryName}"
    cp "${queryFile}" "${diffFile}"
    if [ $? != 0 ]; then echo "ERROR 21 run_query_in_bucket: cp failed"; exit 19; fi
  fi

  if [ -s "${diffFile}" ]; then
    echo
    echo "FAILURE : -bucket ${bucketName} -query ${queryName}"
    echo
    echo >> rbkt_summary.txt
    echo "FAILURE : -bucket ${bucketName} -query ${queryName}" >> rbkt_summary.txt
    echo >> rbkt_summary.txt
    let failedQueries=failedQueries+1 
  else
    echo
    echo "SUCCESS : -bucket ${bucketName} -query ${queryName}"
    echo
    echo >> rbkt_summary.txt
    echo "SUCCESS : -bucket ${bucketName} -query ${queryName}" >> rbkt_summary.txt
    echo >> rbkt_summary.txt
  fi

  let totalQueries=totalQueries+1

  return 0
}


#
# params:
#
# $1 bucketName : This is a relative pathname that specifies 2 directories:
#                 (a) a directory that contains query files; in this case the
#                     pathname is relative to the Queries directory in the test
#                     environment.
#                 (b) a directory where the query-results file will be written;
#                     in this case the pathname is relative to the Results
#                     directory in the test environment.
#
function run_bucket() 
{
  local error=0
  local queryList=""
  local q=""
  local queryName=""
  local bucketName="$1"

  if [ ! -e "${queriesDir}/${bucketName}" ]; then
    echo "ERROR 1 run_bucket: bucket ${queriesDir}/${bucketName} does not exist"
    return 17
  fi

  cd "${queriesDir}/${bucketName}"
  #queryList=`find . -maxdepth 1 -name "*.query" -printf "%f\n"`
  queryList=`ls *.xq`
  cd -

  for q in $queryList
  do
    echo ${q} | sed -e s/".xq"/""/g  > tmp_queryFile
    for queryName in `cat tmp_queryFile`
    do 
      run_query_in_bucket "${bucketName}" "${queryName}"
      error=$?
      if [ ${error} != 0 ]; then
        echo "ERROR 3 run_bucket: run_query failed with error code ${error}"
        return ${error}
      fi
    done
    rm -f tmp_queryFile
  done  

  return 0
}

