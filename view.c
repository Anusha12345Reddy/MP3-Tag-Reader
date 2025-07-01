#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "view.h"
#include "types.h"


OperationType check_operation(char* argv[])
{
    if (strcmp(argv[1], "-v") == 0)
        return p_view;
    else if (strcmp(argv[1], "-e") == 0)
        return p_edit;
    else if (strcmp(argv[1], "--help") == 0)
        return p_help;
    else
        return p_unsupported;
}


Status read_and_validate_mp3_file(char* argv[], TagInfo* mp3tagInfo)
{
    if (argv[2] == NULL)
    {
        printf("ERROR: No MP3 file specified!\n");
        printf("Usage: ./mp3_tag_reader -v <file_name.mp3>\n");
        return p_failure;
    }

    mp3tagInfo->fptr_mp3 = fopen(argv[2], "r");
    if (mp3tagInfo->fptr_mp3 == NULL)
    {
        printf("ERROR: Unable to open file %s\n", argv[2]);
        return p_failure;
    }

    char str[3];
    fread(str, 1, 3, mp3tagInfo->fptr_mp3);
    if (strncmp(str, "ID3", 3) != 0)
    {
        printf("ERROR: %s is not a valid MP3 file!\n", argv[2]);
        fclose(mp3tagInfo->fptr_mp3);
        return p_failure;
    }

    return p_success;
}


Status view_tag(char* argv[], TagInfo* mp3tagInfo)
{
    mp3tagInfo->fptr_mp3 = fopen(argv[2], "r");
    fseek(mp3tagInfo->fptr_mp3, 10L, SEEK_SET);

    printf("\n--------------------------\n");
    printf(" MP3 Tag Information\n");
    printf("--------------------------\n");

    Status ret;
    ret = get_and_display_data("Title    : ", "TIT2", mp3tagInfo->frame_Id, &mp3tagInfo->title_tag_size, mp3tagInfo->title_tag, mp3tagInfo->fptr_mp3);
    ret = get_and_display_data("Artist   : ", "TPE1", mp3tagInfo->frame_Id, &mp3tagInfo->artist_tag_size, mp3tagInfo->artist_tag, mp3tagInfo->fptr_mp3);
    ret = get_and_display_data("Album    : ", "TALB", mp3tagInfo->frame_Id, &mp3tagInfo->album_tag_size, mp3tagInfo->album_tag, mp3tagInfo->fptr_mp3);
    ret = get_and_display_data("Year     : ", "TYER", mp3tagInfo->frame_Id, &mp3tagInfo->year_size, mp3tagInfo->year, mp3tagInfo->fptr_mp3);
    ret = get_and_display_data("Genre    : ", "TCON", mp3tagInfo->frame_Id, &mp3tagInfo->content_type_size, mp3tagInfo->content_type, mp3tagInfo->fptr_mp3);
    ret = get_and_display_data("Comments : ", "COMM", mp3tagInfo->frame_Id, &mp3tagInfo->comment_size, mp3tagInfo->comments, mp3tagInfo->fptr_mp3);

    printf("--------------------------\n");

    fclose(mp3tagInfo->fptr_mp3);
    return p_success;
}


Status get_and_display_data(const char* str_frame, const char* str_Id, char* frame_Id, uint* tag_size, char* tag, FILE* fptr)
{
    char frame[4];
    uint size;
    
    while (fread(frame, 1, 4, fptr) == 4)
    {
        if (strncmp(frame, str_Id, 4) == 0)
        {
            fread(&size, 4, 1, fptr);

            
            size = ((size & 0xFF000000) >> 24) |
                   ((size & 0x00FF0000) >> 8) |
                   ((size & 0x0000FF00) << 8) |
                   ((size & 0x000000FF) << 24);

            fseek(fptr, 3L, SEEK_CUR); 

            char* tag_value = (char*) malloc(size);
            if (tag_value == NULL)
            {
                printf("ERROR: Memory allocation failed.\n");
                return p_failure;
            }
            
            fread(tag_value, 1, size - 1, fptr);
            tag_value[size - 1] = '\0'; 

            printf("%s %s\n", str_frame, tag_value);

            free(tag_value);
            return p_success;
        }

        
        fread(&size, 4, 1, fptr);
        fseek(fptr, size, SEEK_CUR);
    }

    return p_failure;
}
