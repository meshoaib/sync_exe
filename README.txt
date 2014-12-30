  cmsrel CMSSW_5_3_11
  cd CMSSW_5_3_11/src
  cmsenv
  git init
  git clone git@github.com:meshoaib/sync_exe

  ============================
  To initialize a local working copy 
  -- git init
  
  To add a file 
  -- git add <filename>
  
  To commit changes 
  -- git commit -m "first commit"
  
  To select the remote server to push your changes
  -- git remote add origin git@github.com:meshoaib/sync_exe.git
  
  To check the remote server
  -- git remote -v

  To push your changes to the selected remote server
  -- git push -u origin master
  
  Always update your sync_exe directory to get the last code
  -- git pull
        
  In case you did something wrong you can replace local changes using the command e.g.,
  -- git checkout README.txt 
             
  To view log 
  -- git log
  
  To unstage the commit
  -- git reset HEAD <file>           
  
  To check the status of your working copy
  -- git status             
