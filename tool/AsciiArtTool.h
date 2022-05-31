

#ifndef HW1_ASCIIARTTOOL_H
#define HW1_ASCIIARTTOOL_H

#include <stdio.h>
#include <stdbool.h>
#include "../RLEList.h"

/**
* ASCII Art Tool
*
* Implements a tool for working with ASCII art.
*
* The following functions are available:
*   asciiArtRead	        - Creates a new RLE list representing the image given to it.
*   asciiArtPrint		    - Writes the represented image to a given output.
*   asciiArtPrintEncoded    - Writes an encoded version of the represented image to a given output.
*/


/**
* asciiArtRead: Reads the given file and compresses using RLE (Run Length Encoding).
*
* The function allocates and returns a new RLEList struct containing a list representing the characters 
* within the original file.
* Note that the user must free the returned list using RLEListDestroy() once it is no longer needed.
*
* @param in_stream - The file containing the image that will get compressed.
* @return
* 	NULL if allocations failed.
* 	A new RLEList containing the characters in the image in case of success.
*/
RLEList asciiArtRead(FILE* in_stream);


/**
* asciiArtPrint: Writes the given RLE list to a given output.
*
* @param list - The RLE list to write to the file.
* @param out_stream - The file to write the list to.
* @return
* 	RLE_LIST_NULL_ARGUMENT if a NULL was sent as one of the parameters
* 	RLE_LIST_SUCCESS if the image has been written successfully
*/
RLEListResult asciiArtPrint(RLEList list, FILE *out_stream);


/**
* asciiArtPrintEncoded: Writes the given RLE list to a given output in its encoded form.
*
* @param list - The RLE list to write to the file.
* @param out_stream - The file to write the list to.
* @return
* 	RLE_LIST_NULL_ARGUMENT if a NULL was sent as one of the parameters
* 	RLE_LIST_SUCCESS if the image has been written successfully
*/
RLEListResult asciiArtPrintEncoded(RLEList list, FILE *out_stream);


#endif // HW1_ASCIIARTTOOL_H