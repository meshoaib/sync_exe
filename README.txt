  cmsrel CMSSW_5_3_11
  cd CMSSW_5_3_11/src
  cmsenv
  git init
  git clone git@github.com:meshoaib/sync_exe

  git init
  git add <filename>
  git commit -m "first commit"
  git remote add origin git@github.com:meshoaib/sync_exe.git
  git push -u origin master

  ============================
    
  Always update your sync_exe directory to get the last code
  -- git pull
        
  In case you did something wrong you can replace local changes using the command e.g.,
  -- git checkout README.txt 
             
