cd newhope
zip -r newhope.love *
cd ..
copy /b win64\love64.exe+newhope\newhope.love NewHope.exe
del newhope\newhope.love
