#ifndef EDIT_H
#define EDIT_H

#include "types.h"    



typedef struct _TagData
{
   
    FILE* fptr_mp3;

	
    FILE* fptr_temp;

	
    char frame_Id [5];
    char frame_Id_value[100] ;
    uint frame_Id_size;
} TagData;


Status read_and_validate_mp3_file_args (char* argv[], TagData* mp3tagData);


Status edit_tag (char* argv[], TagData* mp3tagData);


Status copy_data (TagData* mp3tagData, char flag);


Status copy_remaining_data (TagData* mp3tagData);

/* Copy the complete Data from the Temporary to Source MP3 file */
Status copy_back_to_src (TagData* mp3tagData);

#endif