# CptS122 PA9 README
### Team Members/Lab Sections: Anastasia Chepel(01), Sterling Angrish(04), Kadyn Norris(01), Aaron Johnson(01)

VIDEO EXAMPLE: TODO

# BEFORE YOU CAN PLAY
1. Download the zip file and select "Extract All"
2. Open Blocktris.slnx inside the Blocktris-master folder using Visual Studio 2026
3. Once inside the project, open the "Project" menu in the top left, and select "Propertes" (it may also be called "Blocktris Properties")
4. In C/C++->General, change the "Additional Include Directories" contents to your file directory for the include folder in SFML-3.1.0
   - the full directory will look different for everyone, but it should end with Blocktris-master\Blocktris\SFML-3.1.0\include
5. Next, navigate to Linker->General and change the "Additional Library Directories" contents to your file directory for the lib folder
   - Again it'll be different for everyone, but should end in Blocktris-master\Blocktris\SFML-3.1.0\lib
6. Hit "Apply" in the bottom right of the popup window, then "OK"
7. Attempt to run the debugger (this will fail but this is a necessary step trust the process)
8. Close the entire project
9. In your file manager, navigate all the way to the bin folder inside the SFML-3.1.0 folder
10. Select all the dll files and copy them with ctrl + c
11. Go back up the directory back to the Blocktris-master folder, and then open the newly created "x64" folder (make sure you are in Blocktris-master, as there are multiple "x64" folders)
12. Open the Debug folder, and paste all of the dll files with ctrl + v
13. Reopen Blocktris.slnx, run the debugger, and have fun!

###### This section only exists due to the suffering caused by trying to get this to work on everyone's devices

## Blocktris (our 'lil tetris clone)

### Controls:

Left Arrow Key (<-): Move falling block to the left

Right Arrow Key (->): Move falling block to the right

Down Arrow Key (\\/): Increase the speed of the falling block temporarily

Up Arrow Key (/\\): Instantly drop the falling block to the immediate lowest point it is on top of

X Key: Rotate the block clockwise

Z key: Rotate the block counter-clockwise



The goal of blocktris is to clear as many lines as possible as the blocks slowly fall faster and faster. 
You clear a line by filling every cell across a cell row with a block.
