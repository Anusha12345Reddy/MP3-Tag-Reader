# MP3-Tag-Reader

📘 MP3 Tag Reader & Editor – Explanation

This project is a command-line based utility written in C that reads and modifies metadata (ID3v1 tags) embedded in MP3 audio files. These tags store information such as the song title, artist name, album, year of release, and genre. The objective of this project is to explore binary file manipulation by working directly with the last 128 bytes of an MP3 file, where ID3v1 tags are located.

The program supports both read and edit modes. In read mode, it extracts and displays metadata fields in a human-readable format. In edit mode, users can modify specific fields, such as changing the title or artist name, and the program updates the binary data in-place without corrupting the audio content.

Core functionalities include:

- Verifying the presence of ID3v1 tags
- Reading and displaying all metadata fields
- Editing specific fields (e.g., title, artist, album)
- Writing updated metadata back to the MP3 file
- Ensuring original audio remains untouched

This project demonstrates low-level file I/O operations (`fseek`, `fread`, `fwrite`), binary data parsing, and character array manipulation in C. It offers practical exposure to working with multimedia file formats, structured data reading, and direct binary modifications — valuable skills in embedded systems and systems programming.

🔹 What This Project Showcases:

- Proficiency in binary file I/O and pointer arithmetic
- Working with structured metadata in real-world file formats
- Strong attention to byte-level data integrity
- Building user-driven command-line utilities with edit capabilities
