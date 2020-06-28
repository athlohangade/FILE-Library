# FILE Library
The project is implementation of file functions like fopen, fread, etc. as an interface for file handling in C. These functions are implemented using the concept of buffer for efficient working.

## Usage
Different functions implemented in the project can be used directly by adding *file.c* and *file.h* in the working directory. Then include *file.h* in the main program and make the calls to the function defined in *file.h* as required.

A demo testsuite has been written to test various mode (read, write, append, ...) of opening the file.
To run testsuite :
-   Change working directory to *src* folder.
-   Run command :
    >   make

    This will generate object files (.o) and an executable *project*.
-   Run command :
    >   ./project

    This will run testsuite and generate some data files in *testresults* folder for verification and also output results on the terminal
-   To delete the additional files generate, run command :
    >   make clean

After running the executable file 'project', datafiles are created for verification of output in the *testresults* folder. If the project file is executed more than once then, append mode datafiles may have different output than expected (because appending takes place on previous data. So datafile will contain previous output as well as the expected output). So every time, delete data files before re-execution of 'project' file to get the expected output.

## Implementation and Working
The buffer concept is used in the project. Buffer of size 1024 bytes is used.

1. **myfopen** : This function create a file structure variable which contain all the file handling parameters. It opens the file in specified mode and initializes all the file structure elements like buffer, buffer count, mode flag, buffer number, etc. as per the mode.

2. **myfread** : First the buffer is loaded with 1024 or less than that as per the file size. myfread function takes the data from the buffer and stores in the variable passed in the function. The data is stored in proper sequence with the help of rptr which moves along the buffer. Once the buffer count reaches at 1024, the new buffer is loaded by reading data from the file. If EOF is reached then it sets the eofflag to 1. According to the mode of file, cases are handled (Eg : no reading for write mode).

3. **myfwrite** : This function takes the data passed in the function and store it in the buffer. It increments the buffer count, file pointer position and filelength as the data is stored. Once the buffer count reaches to 1024, the data from the buffer is written in the file, buffer count is set to zero and all bytes in buffer are initialized to '\0'. Again the data is stored from 0th byte till 1023th byte and then made empty. myfwrite function write the data only if buffer gets fully filled. If at the end, the buffer remains incompletely filled then it is written in myfclose function. According to the mode of file, cases are handled (Eg : no writing for read mode).

4. **myftell** : This function simply return the file position pointer which is stored in the rpos variable in file structure.

5. **myfseek** : This function sets the file pointer at specified position. After changing the position, if the new position lies in the same buffer as that of old position, then buffer is keep as it is and just the buffer count, buffer pointer are set accordingly. If the new position lies in another buffer then :
    -    For w, w+, r+, a+ mode. the old buffer is made empty by writing it in the file, and new buffer is initialized to '\0'.
    -    For r mode, the new buffer is loaded by reading data from the file.
    -    For a mode, just the position is set. As of there is no use of myfseek in append(a) mode. Also this function resets the eofflag if the new position is less than or equal to filelength.

6. **myfgetpos** : This function stores the file pointer position in the variable passed through function arguments.

7. **myfsetpos** : This function set the file pointer position to the position stored in variable passed as function argument. myfgetpos and mysetpos always come in pair. User should call myfgetpos and then myfsetpos to get a desired output. As of there is no use of myfsetpos in append(a) mode.

8. **myfeof** : This function checks the eofflag and returns the value accordingly.

9. **myfclose** : This function writes the remaining incompletely filled buffer in the file and frees the malloced file structure.

## Authors
[Atharva Lohangade](https://github.com/athlohangade)

## License
[MIT](https://choosealicense.com/licenses/mit/)
