#include <stdio.h>
#include "types.h"
#include "view.h"
#include "edit.h"

int main(int argc, char* argv[])
{
    TagInfo mp3tagInfo;
    TagData mp3tagData;

    if (argc < 2)		
    {
        printf ("ERROR: Incorrect format of Command Line Arguments.\n");
        printf ("INFO: Use \"./mp3_tag_reader --help\" for Help menu.\n");
    }
    else
    {
        OperationType ret = check_operation (argv);		

        if (ret == p_view)				
        {
            printf ("--------------------------\n");
            printf ("MP3 Tag Reader and Editor\n");
            printf ("--------------------------\n");
            Status ret1 = read_and_validate_mp3_file (argv, &mp3tagInfo);	
            if (ret1 == p_success)			
            {
                Status ret2 = view_tag (argv, &mp3tagInfo);						
                if (ret2 == p_success)		
                {
                    printf ("INFO: Done.\n");
                    printf ("--------------------------\n");
                }
            }
        }
        else if (ret == p_edit)			
        {
            printf ("MP3 Tag Reader and Editor:\n");
            printf ("--------------------------\n");
            Status ret1 = read_and_validate_mp3_file_args (argv, &mp3tagData);	
            if (ret1 == p_success)			
            {
                Status ret2 = edit_tag (argv, &mp3tagData);						
                if (ret2 == p_success)		
                {
                    printf ("INFO: Done.\n");
                    printf ("--------------------------\n");
                    
                }
            }
        }
        else if (ret == p_help)			
        {
            printf ("INFO: Help Menu for Tag Reader and Editor:\n");
            printf ("INFO: For Viewing the Tags -> ./mp3_tag_reader -v <file_name.mp3>\n");
            printf ("INFO: For Editing the Tags -> ./mp3_tag_reader -e <modifier> \"New_Value\" <file_name.mp3>\n");
            printf ("INFO: Modifier Functions:\n");
            printf ("-t\tModify Title Tag\n-A\tModify Artist Tag\n-a\tModify Album Tag\n-y\tModify Year Tag\n-G\tModify Content Type Tag\n-c\tModify Comments Tag\n");
        }
        else if (ret == p_unsupported)	
        {
            printf ("ERROR: Unsupported Operation.\n");
            printf ("INFO: Use \"./mp3_tag_reader --help\" for Help menu.\n");
        }
    }

    return 0;
}