#!/bin/bash

echo "Enter the new file name:"
read new_name

# Check if the input is not empty
if [ -z "$new_name" ]; then
    echo "Error: Please provide a non-empty file name."
    exit 1
fi

# Loop through each file in the directory
for file in *; do
    # Check if the file is a regular file (not a directory)
    if [ -f "$file" ]; then
        # Get the file extension
        extension="${file##*.}"
        # Get the file name without extension
        filename="${file%.*}"
        # Replace content in the file
        
        # Rename the file with preserving the extension
        mv "$file" "$filename"_"$new_name".$extension
        echo "Updated content and renamed '$file' to '$filename'_'$new_name'.$extension"
    fi
done

echo "All files updated with new content and renamed to '$new_name'"

mkdir materials
mkdir meshes
mkdir materials/textures
cp ../base_template/* ./
sed -i "s/kare_kar/$new_name/g" "model.config"
sed -i "s/kare_kar/$new_name/g" "model.sdf"
echo "Folders created"