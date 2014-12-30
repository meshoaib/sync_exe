cmsrel CMSSW_5_3_11
cd CMSSW_5_3_11/src
cmsenv
git init
git clone git@github.com:meshoaib/sync_exe

git init
git add README.md
git commit -m "first commit"
git remote add origin git@github.com:meshoaib/sync_exe.git
git push -u origin master
