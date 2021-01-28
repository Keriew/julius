#ifndef ASSETS_XML_H
#define ASSETS_XML_H

#define XML_STRING_MAX_LENGTH 32

void xml_setup_base_folder_string(const char *base_folder);
void xml_process_assetlist_file(const char *xml_file_name);
void xml_get_current_full_path_for_image(char *full_path, const char *file_name);

#endif // ASSETS_XML_H
