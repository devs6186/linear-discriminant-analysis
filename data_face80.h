#ifndef DATA_FACE80_H
#define DATA_FACE80_H

// Option 1: Static data (partially initialized)
unsigned char data_face80[80][400] = {
    { // First image (partial data)
      114,116,118,118,115,110,100,92,89,87,87,93,108,122,131,131,129,102,47,75,
      81,81,80,85,50 /* ... (remaining zeros) */
    },
    // ... (remaining images default to zeros)
};

// Option 2: Uncomment to enable random initialization in main()
// #define INIT_RANDOM_DATA 

#endif